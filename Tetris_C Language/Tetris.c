#include "library.h"
#include "shapes.h"
#include "tetris_function.h"
#include "show.h"


/*
Method to make random int from 0 to limit-1
Returns an integer that determines one of the seven shapes of the block.
*/
int make_randint(int limit)
{
	srand((unsigned)time(NULL));
	return rand() % limit;		//returns random number below the limit; //todo: should not restore the formula immediately.
}

BLOCK* first_block(void)
{
	BLOCK* block;

	block = (BLOCK*)malloc(sizeof(BLOCK));

	//state == 0 is touched base 1 is falling
	block->shape = make_randint(7);		//Store a random number below 7 in block -> shape.
	block->block_x = 5;		//todo: Use a constant
	block->block_y = 0; // Specify where the block will occur. //todo: Use a constant
	block->direction = 0; // Specify the rotating state of the block.//todo: Use a constant

	return block;
}
/*
Method of making and returning new blocks.
Return a block that will appear next while the game is running
*/
BLOCK* make_block(BLOCK* pre)
{
	BLOCK* block;

	block = (BLOCK*)malloc(sizeof(BLOCK));

	//state == 0 is touched base 1 is falling
	block->shape = next_shape; //Save the next_shape value in block - > shape.
	next_shape = rand() % 7; //Save the new random number below 7 in the next-shape.
	block->block_x = 5; //todo: Use a constant
	block->block_y = 0; //Specify where the block will occur. //todo: Use a constant
	block->direction = 0; //Specify the rotating state of the block.//todo: Use a constant
	free(pre); //eliminate the previous block

	return block;
}
/*
Method to change the part of the screen array where the block exists to 1.
*/
void input_block(BLOCK* block)
{
	int x, y, shape, direction;	//todo: Each variable is declared in one row

	shape = block->shape;
	direction = block->direction;	//Save the block's state in each x, y, shape, direction.

	//update the screen array
	for (y = 0; y < 4; y++) {	//If the block exists,(if the value is 1)
		for (x = 0; x < 4; x++) {
			if (shapes[shape][direction][y][x] == 1) {
				screen[block->block_y + y][block->block_x + x] = 1;//Store 1 in the corresponding location on the screen array.
				//block_x, block_y is the current location of the block
			}
		}
	}
}
/*
Method to change the part of the screen array where the block exists to 0.
*/
void Remove_Block(BLOCK* block)		//todo: Replace the first letter with a lowercase letter
{
	int x, y, shape, direction;		//todo: Each variable is declared in one row

	shape = block->shape;
	direction = block->direction;	//Save the block's state in each x, y, shape,

	if (checkdown(block) != 0)
	{
		//update the screen array
		for (y = 0; y < 4; y++) {
			for (x = 0; x < 4; x++) {
				if (shapes[shape][direction][y][x] == 1) {	//If the block exists,(if the value is 1)	
					screen[block->block_y + y][block->block_x + x] = 0;		//Store 0 in the corresponding location on the screen array.
					//block_x, block_y is the current location of the block
				}
			}
		}
	}
}
/*
Method to check down side of block
if somthing in downside return 0
*/
int checkdown(BLOCK* block)
{
	int x, y, shape, direction;
	int edge[4] = { 0,0,0,0 };// use for marking edge
							  //setting local variable from factor
	shape = block->shape;
	direction = block->direction;

	for (x = 0; x < 4; x++) {
		for (y = 3; y>0; y--) {
			if (shapes[shape][direction][y][x] == 1) {
				edge[x] = y; //set fill edge num
				break;
			}
		}
	}
	//if next place is filled return 0; else return 1;
	for (x = 0; x < 4; x++) {
		if (edge[x] != 0) {
			if (screen[block->block_y + edge[x] + 1][block->block_x + x] == 1)
				return 0;
		}
	}
	return 1;
}
/*
Method to check left side of block
if somthing in leftside return 0
*/
int checkleft(BLOCK* block)
{
	int x, y, shape, direction;
	int edge[4] = { -1,-1,-1,-1 };// use for marking edge
								  //setting local variable from factor
	shape = block->shape;
	direction = block->direction;

	for (y = 0; y < 4; y++) {
		for (x = 0; x < 4; x++) {
			if (shapes[shape][direction][y][x] == 1)
			{
				edge[y] = x; //set fill edge num
				break;
			}

		}
	}

	//if next place is filled return 0; else return 1;
	for (y = 0; y < 4; y++) {
		if (edge[y] != -1) {
			if (screen[block->block_y + y][block->block_x + edge[y] - 1] == 1)
				return 0;
		}
	}
	return 1;
}
/*
Method to check right side of block
if somthing in rightside return 0
*/
int checkright(BLOCK* block)
{
	int x, y, shape, direction;
	int edge[4] = { -1,-1,-1,-1 }; // use for marking edge
								   //setting local variable from factor
	shape = block->shape;
	direction = block->direction;

	for (y = 0; y < 4; y++) {
		for (x = 3; x >0; x--) {
			if (shapes[shape][direction][y][x] == 1)
			{
				edge[y] = x; //set fill edge num
				break;
			}

		}
	}

	//if next place is filled return 0; else return 1;
	for (y = 0; y < 4; y++) {
		if (edge[y] != -1) {
			if (screen[block->block_y + y][block->block_x + edge[y] + 1] == 1)
				return 0;
		}
	}
	return 1;
}

//check the next shape place
int checkshape(BLOCK* block)
{
	int x, y, shape, direction, next_direction;
	int i, flag, plus_y = 0, plus_x = 0;
	int Next_shape[4][4] = { 0 }; // all thing set 0
	int edge[4] = { -1, -1, -1, -1 };
	//setting local variable from factor
	shape = block->shape;
	direction = block->direction;
	next_direction = block->direction + 1;
	//limit direction number 3
	next_direction %= 4;

	//current_shape -> next_shape  scan (4*4)
	for (y = 0; y < 4; y++) {
		for (x = 0; x < 4; x++) {
			if (shapes[shape][direction][y][x] != 1) {
				Next_shape[y][x] = shapes[shape][next_direction][y][x];
			}
		}
	}

	//0 is check left 1 is check right 2 is check down 3is check up
	for (flag = 0; flag < 4; flag++) {
		//make edge by flag
		switch (flag)
		{
		case 0://left 
			   /*
			   TODO: if x<3 -> do not rotate
			   */
			for (y = 0; y < 4; y++) {
				for (x = 0; x < 4; x++) {
					if (Next_shape[y][x] == 1)
					{
						edge[y] = x;
						break;
					}
				}
			}
			break;

		case 1://right
			for (y = 0; y < 4; y++) {
				for (x = 3; x >0; x--) {
					if (Next_shape[y][x] == 1)
					{
						edge[y] = x;
						break;
					}

				}
			}
			break;

		case 2://down
			for (x = 0; x < 4; x++) {
				for (y = 3; y>0; y--) {
					if (Next_shape[y][x] == 1) {
						edge[x] = y;
						break;
					}
				}
			}
			break;
		case 3://up
			for (x = 0; x < 4; x++) {
				for (y = 0; y<4; y++) {
					if (Next_shape[y][x] == 1) {
						edge[x] = y;
						break;
					}
				}
			}
			break;

		}

		//check edge by flag
		for (i = 0; i < 4; i++) {
			if (edge[i] != 0)
			{
				if (i < 2) {
					if (screen[block->block_y + i][block->block_x + edge[i]] == 1)
						return 0;
				}
				else {
					if (screen[block->block_y + edge[i]][block->block_x + i] == 1)
						return 0;
				}
			}
		}
		//clear edge
		for (i = 0; i < 4; i++) {
			edge[i] = -1; //reset
		}
	}
	return 1;
}
//Method to control block according to the movement keys pressed
void control_shape(BLOCK* block)
{
	char key; // user pressed key

	while (_kbhit()) {
		key = _getch();

		switch (key)
		{
		case UP://rotate block
			if (checkshape(block) == 1) {
				block->direction++;
				block->direction %= 4; // limit rotate
			}
			break;

		case DOWN:
			if (checkdown(block) == 1)
				block->block_y++;
			break;

		case RIGHT:
			if (checkright(block) == 1) {
				block->block_x++;
			}
			break;

		case LEFT:
			if (checkleft(block) == 1) {
				block->block_x--;
			}
			break;
		case SPACEBAR:
			while (checkdown(block))
				block->block_y++;
		}
	}
}

//if game is voer return 1 else return 0
int Check_Over(void)
{
	int i;

	for (i = 0; i < 4; i++) {
		if (screen[1][5 + i] == 1)
		{
			system("cls");
			set_cursor(30, 10);
			printf("ÂìÂì ·çÀú»õ³¢");
			return 1;
		}
	}
	return 0;
}
/*
Method to carry out the overall execution of tetris
Function:	Move blocks down, Change the block according to the keyboard input,
Print the block, Remove the completed line, Check whether the game is over
*/
void run_game(BLOCK* block)
{
	int i = 0, line; //Initializing for Repetition

	remove_cursor(); //remove cursor on screen

	show_nextshape(); //print the next block

	while (1) { //the loop ends when the game is over
		while (1) { //the loop ends when the block is collide bottom
			//to move block fast
			i++;
			if (i == 3) {
				i = 0;
				block->block_y++;	//if (i==3) move block one down
			}

			control_shape(block);	// If there is a keyboard input, change the shape of the block.
			
			input_block(block);		//Fill the screen array with blocks.
			
			show_screen();		//print screen
			//change place(side) and direction
			

			//if next place(down) is filled break while and make new block
			if (checkdown(block) == 0)
				break;
			//remove current block
			Remove_Block(block);
			Sleep(100);		//Do nothing for 0.1 seconds.
		while (1)
		{
			line = Clear_Line();	/*Check how many lines are cleared, and then insert the value into the line variable. */
			if (line == 0)	// If there are no lines to erase, break.
				break;
			Shift_Screen(line);	//Erase the line and print out the screen.
		}

		if (Check_Over())	//Check to see if the game is over.
			break;

		//make new block
		block = make_block(block);
		next_shape = make_randint(7);	//make random integer 0~6

		remove_cursor();
		show_nextshape();
		//TODO: have to change line between ¡°show_nextshape()¡± and ¡°if(block->shpe == next_shape¡¦)¡± because as the shape may change after you have already printed the next one on the screen, the next one may appear different from the next one on the screen.
		if (block->shape == next_shape && next_shape != 6)	//Make a variety of shapes.
			next_shape += 1;
	}
}
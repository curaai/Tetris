#include "library.h"
#include "shapes.h"
#include "tetris_function.h"
#include "show.h"


//make random int from 0~limit-1 
int make_randint(int limit)
{
	srand((unsigned)time(NULL));
	return rand() % limit;
}

BLOCK* first_block(void)
{
	BLOCK* block;

	block = (BLOCK*)malloc(sizeof(BLOCK));

	//state == 0 is touched base 1 is falling
	block->shape = make_randint(7);
	block->block_x = 5;
	block->block_y = 0;
	block->direction = 0;

	return block;
}

BLOCK* make_block(BLOCK* pre)
{
	BLOCK* block;

	block = (BLOCK*)malloc(sizeof(BLOCK));

	//state == 0 is touched base 1 is falling
	block->shape = next_shape;
	next_shape = rand() % 7;
	block->block_x = 5;
	block->block_y = 0;
	block->direction = 0;

	//eliminate before block
	free(pre);

	return block;
}

void input_block(BLOCK* block)
{
	int x, y, shape, direction;

	shape = block->shape;
	direction = block->direction;

	//shape's fill part to move screen
	for (y = 0; y < 4; y++) {
		for (x = 0; x < 4; x++) {
			if (shapes[shape][direction][y][x] == 1) {
				screen[block->block_y + y][block->block_x + x] = 1;
			}
		}
	}
}

void Remove_Block(BLOCK* block)
{
	int x, y, shape, direction;

	shape = block->shape;
	direction = block->direction;

	if (checkdown(block) != 0)
	{
		for (y = 0; y < 4; y++) {
			for (x = 0; x < 4; x++) {
				if (shapes[shape][direction][y][x] == 1) {
					screen[block->block_y + y][block->block_x + x] = 0;
				}
			}
		}
	}
}

int checkdown(BLOCK* block)
{
	int x, y, shape, direction;
	int edge[4] = { 0,0,0,0 };

	shape = block->shape;
	direction = block->direction;

	for (x = 0; x < 4; x++) {
		for (y = 3; y>0; y--) {
			if (shapes[shape][direction][y][x] == 1) {
				edge[x] = y;
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

int checkleft(BLOCK* block)
{
	int x, y, shape, direction;
	int edge[4] = { -1,-1,-1,-1 };

	shape = block->shape;
	direction = block->direction;

	for (y = 0; y < 4; y++) {
		for (x = 0; x < 4; x++) {
			if (shapes[shape][direction][y][x] == 1)
			{
				edge[y] = x;
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

int checkright(BLOCK* block)
{
	int x, y, shape, direction;
	int edge[4] = { -1,-1,-1,-1 };

	shape = block->shape;
	direction = block->direction;

	for (y = 0; y < 4; y++) {
		for (x = 3; x >0; x--) {
			if (shapes[shape][direction][y][x] == 1)
			{
				edge[y] = x;
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
	int Next_shape[4][4] = { 0 };
	int edge[4] = { -1, -1, -1, -1 };

	shape = block->shape;
	direction = block->direction;
	next_direction = block->direction + 1;

	next_direction %= 4;

	//current-shape - next_shape
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
		case 0:
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

		case 1:
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

		case 2:
			for (x = 0; x < 4; x++) {
				for (y = 3; y>0; y--) {
					if (Next_shape[y][x] == 1) {
						edge[x] = y;
						break;
					}
				}
			}
			break;
		case 3:
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
			if (edge != 0)
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
			edge[i] = -1;
		}
	}
	return 1;
}

void control_shape(BLOCK* block)
{
	char key;

	while (_kbhit()) {
		key = _getch();

		switch (key)
		{
		case UP:
			if (checkshape(block) == 1) {
				block->direction++;
				block->direction %= 4;
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

void run_game(BLOCK* block)
{
	int i = 0, line;

	remove_cursor();

	show_nextshape();

	while (1) {
		while (1) {
			//to move block fast
			i++;
			if (i == 3) {
				i = 0;
				block->block_y++;
			}

			control_shape(block);
			//fill that block to array
			input_block(block);
			//print screen
			show_screen();
			//change place(side) and direction

			//if next place(down) is filled break while and make new block
			if (checkdown(block) == 0)
				break;
			//remove current block
			Remove_Block(block);
			Sleep(100);
		}
		while (1)
		{
			line = Clear_Line();
			if (line == 0)
				break;
			Shift_Screen(line);
		}

		if (Check_Over())
			break;

		//make new block
		block = make_block(block);
		next_shape = make_randint(7);

		remove_cursor();
		show_nextshape();

		if (block->shape == next_shape && next_shape != 6)
			next_shape += 1;
	}
}
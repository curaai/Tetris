#include "library.h"
#include "shapes.h"
#include "tetris_function.h"
#include "show.h"
#define first_x 5
#define first_y 0
#define first_direction 0
int score = 0; // game score
int bombsignal = 0; // signal of bombitem
int erasesignal = 0; // signal of erase item
int itemcnt = 0; //count for using item
int reverse_item_on = 0; // 0 is off , 1 is on
int reverse_item_time_count = 0;
int speed = 100; // initial speed
int speed_item_time_count = 0;

/*
Method to make random int from 0 to limit-1
Returns an integer that determines one of the seven shapes of the block.
*/
int make_randint(int limit)
{
	int rand_int;
	srand((unsigned)time(NULL));
	rand_int = rand() % limit;
	return rand_int;      //returns random number below the limit; //todo: should not restore the formula immediately.
}

BLOCK* first_block(void)
{
	BLOCK* block;

	block = (BLOCK*)malloc(sizeof(BLOCK));

	//state == 0 is touched base 1 is falling
	block->shape = make_randint(7);      //Store a random number below 7 in block -> shape.
	block->block_x = first_x;      //todo: Use a constant
	block->block_y = first_y; // Specify where the block will occur. //todo: Use a constant
	block->direction = first_direction; // Specify the rotating state of the block.//todo: Use a constant

	return block;
}

BLOCK* item_first_block(void)
{
	BLOCK* block;

	block = (BLOCK*)malloc(sizeof(BLOCK));

	//state == 0 is touched base 1 is falling
	block->shape = make_randint(9);      //Store a random number below 9 in block -> shape.
	block->block_x = first_x;      //todo: Use a constant
	block->block_y = first_y; // Specify where the block will occur. //todo: Use a constant
	block->direction = first_direction; // Specify the rotating state of the block.//todo: Use a constant

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
	block->block_x = first_x; //todo: Use a constant
	block->block_y = first_y; //Specify where the block will occur. //todo: Use a constant
	block->direction = first_direction; //Specify the rotating state of the block.//todo: Use a constant
	free(pre); //eliminate the previous block

	return block;
}

BLOCK* item_make_block(BLOCK* pre)
{
	BLOCK* block;

	block = (BLOCK*)malloc(sizeof(BLOCK));

	//state == 0 is touched base 1 is falling
	block->shape = next_shape; //Save the next_shape value in block - > shape.
	next_shape = rand() % 9; //Save the new random number below 9 in the next-shape.
	block->block_x = first_x; //todo: Use a constant
	block->block_y = first_y; //Specify where the block will occur. //todo: Use a constant
	block->direction = first_direction; //Specify the rotating state of the block.//todo: Use a constant
	free(pre); //eliminate the previous block

	return block;
}
/*
Method to change the part of the screen array where the block exists to 1.
*/
void input_block(BLOCK* block)
{
	int x, y;
	int shape;
	int direction;   //todo: Each variable is declared in one row

	shape = block->shape;
	direction = block->direction;   //Save the block's state in each x, y, shape, direction.

									//update the screen array
	for (y = 0; y < 4; y++) {   //If the block exists,(if the value is 1)
		for (x = 0; x < 4; x++) {
			if (shapes[shape][direction][y][x] == 1) {
				screen[block->block_y + y][block->block_x + x] = 1;//Store 1 in the corresponding location on the screen array.
																   //block_x, block_y is the current location of the block
			}
			if (shapes[shape][direction][y][x] == 3) {
				screen[block->block_y + y][block->block_x + x] = 3;//Store 3 in the corresponding location on the screen array.
																   //block_x, block_y is the current location of the block
			}
			if (shapes[shape][direction][y][x] == 4) {
				screen[block->block_y + y][block->block_x + x] = 4;//Store 4 in the corresponding location on the screen array.
																   //block_x, block_y is the current location of the block
			}
		}
	}
}
/*
Method to change the part of the screen array where the block exists to 0.
*/
void remove_Block(BLOCK* block)      //todo: Replace the first letter with a lowercase letter
{
	int x, y;
	int shape;
	int direction;      //todo: Each variable is declared in one row

	shape = block->shape;
	direction = block->direction;   //Save the block's state in each x, y, shape,

	if (checkdown(block) != 0)
	{
		//update the screen array
		for (y = 0; y < 4; y++) {
			for (x = 0; x < 4; x++) {
				if (shapes[shape][direction][y][x] == 1) {   //If the block exists,(if the value is 1)   
					screen[block->block_y + y][block->block_x + x] = 0;      //Store 0 in the corresponding location on the screen array.
																			 //block_x, block_y is the current location of the block
				}
				if (shapes[shape][direction][y][x] == 3) {   //If the reverse_item block exists,(if the value is 3)   
					screen[block->block_y + y][block->block_x + x] = 0;      //Store 0 in the corresponding location on the screen array.
																			 //block_x, block_y is the current location of the block
				}
				if (shapes[shape][direction][y][x] == 4) {   //If the reverse_item block exists,(if the value is 4)   
					screen[block->block_y + y][block->block_x + x] = 0;      //Store 0 in the corresponding location on the screen array.
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
	int x, y;
	int shape;
	int direction;
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
			if (shapes[shape][direction][y][x] == 3) {
				edge[x] = y; //set fill edge num
				break;
			}
			if (shapes[shape][direction][y][x] == 4) {
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
			if (screen[block->block_y + edge[x] + 1][block->block_x + x] == 3)

				return 0;
			if (screen[block->block_y + edge[x] + 1][block->block_x + x] == 4)

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
	int x, y;
	int shape;
	int direction;
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
			if (shapes[shape][direction][y][x] == 3)
			{
				edge[y] = x; //set fill edge num
				break;
			}
			if (shapes[shape][direction][y][x] == 4)
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
			if (screen[block->block_y + y][block->block_x + edge[y] - 1] == 3)
				return 0;
			if (screen[block->block_y + y][block->block_x + edge[y] - 1] == 4)
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
	int x, y;
	int shape;
	int direction;
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
			if (shapes[shape][direction][y][x] == 3)
			{
				edge[y] = x; //set fill edge num
				break;
			}
			if (shapes[shape][direction][y][x] == 4)
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
			if (screen[block->block_y + y][block->block_x + edge[y] + 1] == 3)
				return 0;
			if (screen[block->block_y + y][block->block_x + edge[y] + 1] == 4)
				return 0;
		}
	}
	return 1;
}

//check the next shape place
int checkrotate(BLOCK* block)
{
	int x, y;
	int shape;
	int direction;
	int next_direction;
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
			if (shapes[shape][direction][y][x] != 3) {
				Next_shape[y][x] = shapes[shape][next_direction][y][x];
			}
			if (shapes[shape][direction][y][x] != 4) {
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
					if (Next_shape[y][x] == 3)
					{
						edge[y] = x;
						break;
					}
					if (Next_shape[y][x] == 4)
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
					if (Next_shape[y][x] == 3)
					{
						edge[y] = x;
						break;
					}
					if (Next_shape[y][x] == 4)
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
					if (Next_shape[y][x] == 3) {
						edge[x] = y;
						break;
					}
					if (Next_shape[y][x] == 4) {
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
					if (Next_shape[y][x] == 3) {
						edge[x] = y;
						break;
					}
					if (Next_shape[y][x] == 4) {
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
					if (block->block_x > 2)
					{
						if (screen[block->block_y + i][block->block_x + edge[i]] == 1)
							return 0;
						if (screen[block->block_y + i][block->block_x + edge[i]] == 3)
							return 0;
						if (screen[block->block_y + i][block->block_x + edge[i]] == 4)
							return 0;
					}
					else
					{
						if (screen[block->block_y + i][block->block_x + edge[i] + 2] == 1)
							return 0;
						if (screen[block->block_y + i][block->block_x + edge[i] + 2] == 3)
							return 0;
						if (screen[block->block_y + i][block->block_x + edge[i] + 2] == 4)
							return 0;
					}
				}
				else {
					if (screen[block->block_y + edge[i]][block->block_x + i] == 1)
						return 0;
					if (screen[block->block_y + edge[i]][block->block_x + i] == 3)
						return 0;
					if (screen[block->block_y + edge[i]][block->block_x + i] == 4)
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
/*
Method to make block destination for use screen[y][x]=2
and show block detination
*/
void blockdestination(BLOCK *future)
{

	int x, y;
	int shape;
	int direction;

	while (checkdown(future)) // blcok down while screen[y][x]=1
		future->block_y++;

	shape = future->shape;
	direction = future->direction;

	//shape's fill part to move screen
	for (y = 0; y < 4; y++) {
		for (x = 0; x < 4; x++) {
			if (shapes[shape][direction][y][x] == 1) {
				screen[future->block_y + y][future->block_x + x] = 2;
			}
			if (shapes[shape][direction][y][x] == 3) {
				screen[future->block_y + y][future->block_x + x] = 2;
			}
			if (shapes[shape][direction][y][x] == 4) {
				screen[future->block_y + y][future->block_x + x] = 2;
			}
		}
	}

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
			if (checkrotate(block) == 1) {
				block->direction++;
				block->direction %= 4; // limit rotate
			}
			break;

		case DOWN:
			if (checkdown(block) == 1)
				block->block_y++;
			break;

		case RIGHT:
			if (reverse_item_on == 0) {
				if (checkright(block) == 1) {
					block->block_x++;
				}
			}
			else {
				if (checkleft(block) == 1) {
					block->block_x--;
				}
			}
			break;

		case LEFT:
			if (reverse_item_on == 0) {
				if (checkleft(block) == 1) {
					block->block_x--;
				}
			}
			else {
				if (checkright(block) == 1) {
					block->block_x++;
				}
			}
			break;
		case SPACEBAR:
			while (checkdown(block))
				block->block_y++;
		}
	}
}
//Method to control block according to the AI algorithms.
void aicontrol_shape(BLOCK* block, int * rotateIndex, int * xIndex)
{
	*rotateIndex = 0;
	*xIndex = 0;
	float max_score = 0;	//최대 점수값 저장할 변수
	BLOCK *future = (BLOCK*)malloc(sizeof(BLOCK));

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			copyblock(block, future); // set future block

			future->block_x = j;							//future를 x축의 j좌표로 이동시킨다

			future->direction = (future->direction + i) % 4;//future를 i만큼 회전시킨다
			future->block_y = 0;

			if (checkright(future) == 0 || checkleft(future) == 0)
			{
				scoremap[i][j] = 0;
				continue;
			}
			blockdestination(future); //make destination


									  //if (block_exist(future,i,j) == 0) //블록이 scoremap[i][j]의 경우 존재할 수 없을 때
									  //{
									  //	scoremap[i][j] = 0;
									  //	continue;
									  //}

									  /*for (int a = 0; a < SCREEN_HEIGHT; a++) {
									  set_cursor(70, a);
									  for (int b = 0; b < SCREEN_WIDTH; b++) {
									  printf("%d ", screen[a][b]);
									  }
									  }*/
									  //printf("%d %d", future->block_x, future->block_y);
			int max_height = option_maxheight(future);		//블럭 최대 높이
															//printf("%d\n", max_height);
			int empty_space = option_emptyspace(future);	//빈공간 개수
															//printf("%d\n", empty_space);
			int make_empty = option_blocking_block(future);	//빈공간을 막고 있는 블럭의 수
			int clear_line = option_clearline(future);		//완성된 줄의 개수
			int contact_block = option_blockside(future);	//기존블럭들과 닿는 면의 개수
			int contact_wall = option_wallside(future);		//벽면과 닿는 면의 개수
			int contact_bottom = option_downside(future);	//바닥면과 닿는 면의 개수

			for (int y = 0; y < SCREEN_HEIGHT; y++) // remove pre destination
			{
				for (int x = 0; x < SCREEN_WIDTH; x++)
				{
					if (screen[y][x] == 2)
						screen[y][x] = 0;
				}
			}

			scoremap[i][j] = /*(max_height*(-0.5)) + (empty_space*(-0.4)) + (make_empty*(-0.59)) */
				+(clear_line*8.2) + (contact_block*3.5) + (contact_wall*3.0) + (contact_bottom*4.0); //공식

																									 //printf("%f\n",scoremap[i][j]);


			if (max_score < scoremap[i][j])
			{
				max_score = scoremap[i][j];
				*rotateIndex = i;
				*xIndex = j;
			}
		}
	}



}
int block_exist(BLOCK *block, int i, int j)
{
	int x, y;
	int get_x[2] = { 0 }; // x좌우 좌표


	for (x = 0; x < 4; x++) //left
	{
		for (y = 0; y < 3; y++)
		{
			if (shapes[block->shape][block->direction][y][x] == 1) // 모양 확인
			{
				get_x[0] = x; //가장 왼쪽
				break;
			}
		}
		if (get_x[0] != 0)
			break;
	}
	for (x = 0; x < 4; x++)//right
	{
		for (y = 3; y >= 0; y--) // 오른쪽부터 검사
		{
			if (shapes[block->shape][block->direction][y][x] == 1) // 모양 확인
			{
				get_x[1] = x; //가장 오른쪽
				break;
			}
		}
		if (get_x[1] != 0)
			break;
	}
	if (block->block_x + get_x[1] >= 13)  // 맵 우측과 접촉 확인문
	{
		return 0;
	}
	if (block->block_x + get_x[0] < 1) // 맵 좌측과 접촉 확인문
	{
		return 0;
	}
	else
		return 1;

}
int option_emptyspace(BLOCK *clone)
{
	int i, j, k;//반복문
	int count = 0;// 비어있는 칸의 갯수를 측정하여 return해줄 값
	int flag = 0; // 생성된 블록에서 가장 낮은부분

	for (i = 0; i < SCREEN_WIDTH; i++)//x축 이동
	{
		flag = 0;
		for (j = 0; j < SCREEN_HEIGHT; j++)//y축 위에서 밑으로 이동
		{
			if (screen[j][i] > 0)//y축 0이 아닌값 발견
			{
				for (k = j; k < SCREEN_HEIGHT; k++)//그 부분부터 다시 y축 아래로 이동
				{
					if (screen[j][i] == 0)//0을 발견하면 카운트 1 증가
						count++;
				}
				flag = 1;//끝까지 훑었음을 체크
			}
			if (flag = 1)//끝까지 훑었으므로 y축 내릴 필요 없어서 break
				break;
		}
	}
	return count;
}
int option_downside(BLOCK *clone) //바닥과 닿는면
{
	int i, j;
	int y_flag = 0; //y좌표 저장용
	int cnt = 0; //면의수
	for (j = 3; j >= 0; j--) // 하단부터 검사
	{
		for (i = 0; i < 4; i++)
		{
			if (shapes[clone->shape][clone->direction][j][i] == 1) // 모양 확인
			{
				y_flag = j; // 고정시 가장 하단의 값
				break;
			}
		}
		if (y_flag != 0)
			break;
	}

	if (clone->block_y + y_flag == 24) //가장 하단의 블록이 바닥과 닿을시
	{
		for (i = 0; i < 4; i++)
		{
			if (shapes[clone->shape][clone->direction][y_flag][i] == 1)
				cnt++;
		}
		return cnt;
	}
}

int option_wallside(BLOCK *clone) // 좌우 벽과 닿는 면의 수
{
	int i, j;
	int get_x[2] = { 0,0 }; //[0]은 가장왼쪽 , [1]은 가장오른쪽
	int cnt = 0; // 면의수
	for (i = 0; i < 4; i++) //left
	{
		for (j = 0; j < 3; j++)
		{
			if (shapes[clone->shape][clone->direction][j][i] == 1) // 모양 확인
			{
				get_x[0] = j; //가장 왼쪽
				break;
			}
		}
		if (get_x[0] != 0)
			break;
	}
	for (i = 0; i < 4; i++)//right
	{
		for (j = 3; j >= 0; j--) // 오른쪽부터 검사
		{
			if (shapes[clone->shape][clone->direction][j][i] == 1) // 모양 확인
			{
				get_x[1] = j; //가장 오른쪽
				break;
			}
		}
		if (get_x[1] != 0)
			break;
	}
	if (clone->block_x + get_x[1] == 12)  // 맵 우측과 접촉 확인문
	{
		for (i = 0; i < 4; i++)
		{
			if (shapes[clone->shape][clone->direction][i][get_x[1]] == 1)
				cnt++;
		}
	}
	if (clone->block_x + get_x[0] == 1) // 맵 좌측과 접촉 확인문
	{
		for (i = 0; i < 4; i++)
		{
			if (shapes[clone->shape][clone->direction][i][get_x[0]] == 1)
				cnt++;
		}
	}
	return cnt;

}

int option_blockside(BLOCK *clone) //기존 블록과 닿는 면의수
{
	int i, j, k;// 반복문을 위한 변수들
	int cnt = 0; // 면의 수 반환
	int x[4], y[4];  //각각 구성 블록의 x,y좌표를 저장할것
	int pass = 0; //위 x,y배열을 다음으로 넘기기위한 변수

	for (i = 0; i < 4; i++) // 블록 위치들 추출
	{
		for (j = 0; j < 4; j++)
		{
			if (shapes[clone->shape][clone->direction][i][j] == 1) //블록 있을시
			{
				x[pass] = j;
				y[pass] = i;
				pass++;
			}
		}
	}

	for (i = 0; i < pass; i++) // 해당 블록에 이미 쌓여있는 screen배열과 접촉이 있는지 상하좌우 확인
	{
		if (screen[clone->block_y + y[i] + 1][clone->block_x + x[i]] == 1 //아래
			&& clone->block_y + y[i] + 1< 25)// 맵과 접촉은 제외
			cnt++;
		if (screen[clone->block_y + y[i] - 1][clone->block_x + x[i]] == 1) //위
			cnt++;
		if (screen[clone->block_y + y[i]][clone->block_x + x[i] + 1] == 1 //오른쪽
			&& clone->block_x + x[i] + 1< 13)// 맵과 접촉은 제외
			cnt++;
		if (screen[clone->block_y + y[i]][clone->block_x + x[i] - 1] == 1 //왼쪽
			&& clone->block_x + x[i] - 1 > 0)// 맵과 접촉은 제외
			cnt++;
	}

	return cnt;
}

int option_maxheight(BLOCK *clone) // 블럭 높이 반환
{
	int i, j;
	int y_flag = 0; // 생성된 블록에서 가장 높은부분
	int height = 0; //높이
	for (j = 0; j < 4; j++) // 상단부터 검사
	{
		for (i = 0; i < 4; i++)
		{
			if (shapes[clone->shape][clone->direction][j][i] == 1) // 모양 확인
			{
				y_flag = j; // 도형 가장 상단의 값
				break;
			}
		}
		if (y_flag != 0)
			break;
	}

	height = SCREEN_HEIGHT - (clone->block_y + y_flag);
	return height;
}

int option_clearline(BLOCK *clone) // 완성된 줄의 개수
{
	int i, j;
	int line_cnt = 0; //완성된 줄수
	int block_cnt = 0; // 한 줄당 블록 수
	for (i = SCREEN_HEIGHT - 2; i >= clone->block_y; i--)
	{
		for (j = 1; j < SCREEN_WIDTH - 1; j++)
		{
			if (screen[i][j] != 0) // 줄 안에 블록이 있는지 확인
			{
				block_cnt++;
			}
		}
		if (block_cnt == SCREEN_WIDTH - 2) // 줄에 블록이 12개 있다면
		{
			line_cnt++; // 완성된 줄수 반환
		}
		block_cnt = 0;
	}
	return line_cnt;
}

int option_blocking_block(BLOCK *clone) // 막고 있는 블록 수
{
	int i, j, k;
	int block_cnt = 0; // 막고있는 블록 수
	int x_check[13] = { 0 }; // 해당x위 검사했는지 표시

	for (i = SCREEN_HEIGHT - 2; i > 0; i--)
	{
		for (j = 1; j < SCREEN_WIDTH - 1; j++)
		{
			if (x_check[j] != 0) // 이미 위 블록 검사를 끝낸 x좌표
			{
				break;
			}
			if (x_check[j] == 0 && screen[i][j] == 0)
			{
				for (k = i; k > 0; k--) // 해당 x좌표에서 윗부분 검사
				{
					if (screen[k][j] > 0) //블록이 있으면
					{
						block_cnt++;
					}
				}
				x_check[j] = 1;
			}
		}
	}
	return block_cnt;
}

//if game is voer return 1 else return 0
int check_Over(int score)
{
	int i;

	for (i = 0; i < 4; i++) {
		if (screen[1][5 + i] == 1)
		{
			system("cls");
			set_cursor(30, 10);
			printf("YOU LOSE!");
			set_cursor(30, 11);
			printf("최종 점수:%d", score);
			set_cursor(30, 12);
			return 1;
		}
		if (screen[1][5 + i] == 3)
		{
			system("cls");
			set_cursor(30, 10);
			printf("YOU LOSE!");
			set_cursor(30, 11);
			printf("최종 점수:%d", score);
			set_cursor(30, 12);
			return 1;
		}
		if (screen[1][5 + i] == 4)
		{
			system("cls");
			set_cursor(30, 10);
			printf("YOU LOSE!");
			set_cursor(30, 11);
			printf("최종 점수:%d", score);
			set_cursor(30, 12);
			return 1;
		}
	}
	return 0;
}
/*
Method to set future block for set dstination
*/
void copyblock(BLOCK *block, BLOCK *copy)
{
	copy->block_y = 0;
	copy->block_x = block->block_x;
	copy->direction = block->direction;
	copy->shape = block->shape;
}
/*
Method to carry out the overall execution of tetris
Function:   Move blocks down, Change the block according to the keyboard input,
Print the block, Remove the completed line, Check whether the game is over
*/
void run_game(BLOCK* block)
{
	int i = 0;
	int line_num;//Initializing for Repetition
	int score = 0; // game score
	BLOCK *future = (BLOCK*)malloc(sizeof(BLOCK));
	int x, y;
	remove_cursor(); //remove cursor on screen

	show_nextshape(); //print the next block
	show_score(score); // print game score
	while (1) { //the loop ends when the game is over
		while (1) { //the loop ends when the block is collide bottom
					//to move block fast
			i++;
			if (i == 3) {
				i = 0;
				block->block_y++;   //if (i==3) move block one down
			}
			copyblock(block, future); // set future block
			blockdestination(future); //make destination
			control_shape(block);   // If there is a keyboard input, change the shape of the block.

			input_block(block);      //Fill the screen array with blocks.

			show_screen();      //print screen
			show_score(score); // print game score
							   //change place(side) and direction


							   //if next place(down) is filled break while and make new block
			if (checkdown(block) == 0)
				break;
			//remove current block
			remove_Block(block);
			for (y = 0; y < SCREEN_HEIGHT; y++) // remove pre dstination
			{
				for (x = 0; x < SCREEN_WIDTH; x++)
				{
					if (screen[y][x] == 2)
						screen[y][x] = 0;
				}
			}
			Sleep(100);      //Do nothing for 0.1 seconds.
		}
		while (1)
		{
			line_num = Clear_Line();   /*Check how many lines are cleared, and then insert the value into the line variable. */
			if (line_num == 0)   // If there are no lines to erase, break.
				break;
			Shift_Screen(line_num);   //Erase the line and print out the screen.
			score = score + 10 * 12;
		}

		if (check_Over(score))   //Check to see if the game is over.
			break;

		//make new block
		block = make_block(block);
		next_shape = make_randint(7);   //make random integer 0~6

		remove_cursor();


		if (block->shape == next_shape && next_shape != 6)   //Make a variety of shapes.
			next_shape += 1;

		show_nextshape();
	}
}
BLOCK *bombitem(BLOCK *pre)
{
	BLOCK* block;

	block = (BLOCK*)malloc(sizeof(BLOCK));

	//state == 0 is touched base 1 is falling
	block->shape = 9; //Save the next_shape value in block - > shape.
	next_shape = rand() % 9; //Save the new random number below 7 in the next-shape.
	block->block_x = first_x; //todo: Use a constant
	block->block_y = first_y; //Specify where the block will occur. //todo: Use a constant
	block->direction = first_direction; //Specify the rotating state of the block.//todo: Use a constant
	free(pre);
	return block;
}
BLOCK *eraseitem(BLOCK *pre)
{
	BLOCK* block;

	block = (BLOCK*)malloc(sizeof(BLOCK));

	//state == 0 is touched base 1 is falling
	block->shape = 9; //Save the next_shape value in block - > shape.
	next_shape = rand() % 9; //Save the new random number below 7 in the next-shape.
	block->block_x = first_x; //todo: Use a constant
	block->block_y = first_y; //Specify where the block will occur. //todo: Use a constant
	block->direction = first_direction; //Specify the rotating state of the block.//todo: Use a constant
	free(pre);
	return block;
}
void effectbomb(BLOCK *bomb) // effect bomb item
{
	int x, y;
	for (y = 1; y < 4; y++) // delete point
	{
		for (x = 1; x < 4; x++)
		{
			if (bomb->block_y + y < SCREEN_HEIGHT - 1 && bomb->block_x + x >= 1 && bomb->block_x + x < SCREEN_WIDTH - 1)
			{
				if (screen[bomb->block_y + y][bomb->block_x + x] == 1) // if block in the point
				{
					screen[bomb->block_y + y][bomb->block_x + x] = 0; // delete

				}
				if (screen[bomb->block_y + y][bomb->block_x + x] == 3) // if block in the point
				{
					screen[bomb->block_y + y][bomb->block_x + x] = 0; // delete

				}
				if (screen[bomb->block_y + y][bomb->block_x + x] == 4) // if block in the point
				{
					screen[bomb->block_y + y][bomb->block_x + x] = 0; // delete

				}
			}
			score = score + 10; // plus point
		}
	}
	score = score - 10; // minus bomb point
	for (; y > 0; y--) // for fiil after delete (not yet)
	{
		for (x = bomb->block_x + 1; x < bomb->block_x + 4; x++)
		{
			if (x >= 1 && x < SCREEN_WIDTH - 1)
			{
				screen[y][x] = screen[y - 1][x]; // move to down // fill empty line after use bomb.
			}
		}
	}
}
void effecterase(BLOCK *erase) //erase item
{
	int x, y;
	for (y = erase->block_y + 1; y > 0; y--) {//check from down to up
		for (x = 1; x < SCREEN_WIDTH - 1; x++)  //one line in the map
		{
			if (screen[y][x] == 1)
			{
				score = score + 10;
				screen[y][x] = 0;
			}
			if (screen[y][x] == 3)
			{
				score = score + 10;
				screen[y][x] = 0;
			}
			if (screen[y][x] == 4)
			{
				score = score + 10;
				screen[y][x] = 0;
			}
		}
	}
	screen[erase->block_y + 2][erase->block_x + 2] = 0;
}
void run_itemgame(BLOCK* block) // ITEM mode 
{

	int i = 0; //Initializing for Repetition
	int line_num;
	BLOCK *future = (BLOCK*)malloc(sizeof(BLOCK));
	int x, y;
	remove_cursor(); //remove cursor on screen

	show_nextshape(); //print the next block
	show_score(score); // print game score
	while (1) { //the loop ends when the game is over
		while (1) { //the loop ends when the block is collide bottom
					//to move block fast
			i++;
			if (i == 3) {
				i = 0;
				block->block_y++;   //if (i==3) move block one down
			}
			copyblock(block, future); // set future block
			blockdestination(future); //make destination
			control_shape(block);   // If there is a keyboard input, change the shape of the block.

			input_block(block);      //Fill the screen array with blocks.

			show_screen();      //print screen
			show_score(score); // print game score
							   //change place(side) and direction


							   //if next place(down) is filled break while and make new block
			if (checkdown(block) == 0)
			{
				if (bombsignal == 1) // if block it bomb
				{
					effectbomb(block); // using item
					bombsignal = 0; // reset condition
					break;
				}
				if (erasesignal == 1)
				{
					effecterase(block);
					erasesignal = 0; //reset erasesignal condition
					break;
				}
				break;
			}
			//remove current block
			remove_Block(block);
			for (y = 0; y < SCREEN_HEIGHT - 1; y++) // remove pre dstination
			{
				for (x = 1; x < SCREEN_WIDTH - 1; x++)
				{
					if (screen[y][x] == 2)
						screen[y][x] = 0;
				}
			}
			Sleep(speed);      //Do nothing for 0.1 seconds.
			if (reverse_item_time_count != 0)
			{
				reverse_item_time_count--; // decrease reverse_item_time_count
			}
			else
			{
				reverse_item_on = 0;   //reverse_item_time finish
			}
			if (speed_item_time_count != 0)
			{
				speed_item_time_count--;
			}
			else
			{
				speed = 100;
			}

		}
		while (1)
		{
			line_num = Clear_Line();   /*Check how many lines are cleared, and then insert the value into the line variable. */
			if (line_num == 0)   // If there are no lines to erase, break.
			{
				itemcnt = 0; // reset item count after checking line over
				break;
			}
			else
			{
				itemcnt++;

			}
			Shift_Screen(line_num);   //Erase the line and print out the screen.
			score = score + 10 * 12;

			if (itemcnt == 2)
			{
				bombsignal = 1;
			}
			else if (itemcnt >= 3)
			{
				bombsignal = 0;
				erasesignal = 1;
			}

		}

		if (check_Over(score))   //Check to see if the game is over.
			break;

		//make new block
		if (bombsignal == 0 && erasesignal == 0) // no anyitem
		{
			if (block->shape == 7)
			{
				if (reverse_item_on == 0)
				{
					reverse_item_on = 1; //reverse_item active
					reverse_item_time_count = 60; // reverse_item active 10 sec.   
				}
				else
					reverse_item_on = 0;
			}
			if (block->shape == 8)
			{
				speed_item_time_count = 60; //speed_item active 10 sec.
				speed = 30;
			}
			block = item_make_block(block);
			next_shape = make_randint(9);   //make random integer 0~8
		}
		else if (bombsignal == 1 && erasesignal == 0) // make bombitem
		{
			set_cursor(5, 0);
			block = bombitem(block);
		}
		else if (bombsignal == 0 && erasesignal == 1) // make bombitem
		{
			set_cursor(5, 0);
			block = eraseitem(block);
		}
		remove_cursor();


		if (block->shape == next_shape && next_shape != 8)   //Make a variety of shapes.
			next_shape += 1;

		show_nextshape();
	}
}
void run_AIgame(BLOCK* block) // AI mode 
{
	int i = 0, line; //Initializing for Repetition
	int score = 0; // game score

	int x, y;
	int rotateIndex;
	int xIndex;
	int isitDown = 0;
	remove_cursor(); //remove cursor on screen

	show_nextshape(); //print the next block
	show_score(score); // print game score
	while (1) { //the loop ends when the game is over

		aicontrol_shape(block, &rotateIndex, &xIndex);   // change the shape of the block according to AI algorithms.

														 //xIndex를 이용해 몇칸 이동해야하는지 계산하여 그만큼 좌 또는 우로 이동
		int movecount = xIndex - 5;//movecount: 좌 또는 우로 몇번 이동할것인지 계산한 값 저장함 , 5: 블록 등장 x좌표

		while (1)
		{
			Sleep(100);      //Do nothing for 0.1 seconds.
			input_block(block);      //Fill the screen array with blocks.

			show_screen();      //print screen
			show_score(score); // print game score
							   //change place(side) and direction


							   //remove current block
			if (isitDown == 0)
				remove_Block(block);

			//rotateIndex만큼 회전해줌
			if (rotateIndex > 0)
			{
				if (checkrotate(block) == 1) {
					block->direction++;
					block->direction %= 4; // limit rotate
				}
				rotateIndex--;
				//printf("%d %d\n", rotateIndex, movecount);
				continue;
			}


			//좌로이동
			if (movecount < 0) //movecount가 음수면 좌로 이동해야 함
			{
				if (checkleft(block) == 1) {
					block->block_x--;
				}
				movecount++;
				//printf("%d %d\n", rotateIndex, movecount);
				continue;
			}
			//우로 이동
			else if (movecount>0) {
				if (checkright(block) == 1) {
					block->block_x++;
				}
				movecount--;
				continue;
			}

			//알맞은 위치로 이동 완료, 블록 하강
			if (rotateIndex == 0 && movecount == 0 && isitDown == 0) {
				while (checkdown(block))
					block->block_y++;
				isitDown = 1;
				continue;
			}
			if (isitDown == 1) //블록하강까지 완료되었을 경우, while문 break;
			{
				isitDown = 0;
				break;
			}

		}


		while (1)
		{
			line = Clear_Line();   /*Check how many lines are cleared, and then insert the value into the line variable. */
			if (line == 0)   // If there are no lines to erase, break.
				break;
			Shift_Screen(line);   //Erase the line and print out the screen.
			score = score + 10 * 12;
		}

		if (check_Over(score))   //Check to see if the game is over.
			break;

		//make new block
		block = make_block(block);
		next_shape = make_randint(7);   //make random integer 0~6

		remove_cursor();


		if (block->shape == next_shape && next_shape != 6)   //Make a variety of shapes.
			next_shape += 1;

		show_nextshape();
	}

}

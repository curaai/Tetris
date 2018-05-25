#include "show.h"	
#include "library.h"
#include "tetris_function.h"
#include "shapes.h"
//set cursor point
void set_cursor(int x, int y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
//remove cursor point
void remove_cursor()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}
//Method to make tetris map use array
void fill_screen()
{
	int i;

	//fill the edge right,left to array number
	for (i = 0; i < SCREEN_HEIGHT; i++) {
		screen[i][0] = 1;
		screen[i][SCREEN_WIDTH - 1] = 1;
	}
	//fill the edge of downside to array number
	for (i = 1; i < SCREEN_WIDTH; i++) {
		screen[SCREEN_HEIGHT - 1][i] = 1;
	}
}
//Method to draw block if screen[][]=1 
void show_screen(void)
{
	int i, j;

	//print screen
	for (i = 0; i < SCREEN_HEIGHT; i++) {
		set_cursor(5, 2 + i);

		for (j = 0; j < SCREEN_WIDTH; j++) {
			if (screen[i][j] == 2) // block destination
			{
				printf("﹤");
			}
			else if (screen[i][j] == 1)
			{
				if (j == SCREEN_LEFT_EDGE && i == SCREEN_DOWN_EDGE)
					printf("〧");  //map
				else if (j == SCREEN_RIGHT_EDGE && i == SCREEN_DOWN_EDGE)
					printf("〨");  //map
				else if (j == SCREEN_LEFT_EDGE || j == SCREEN_RIGHT_EDGE)
					printf("〦");  //map
				else if (i == SCREEN_DOWN_EDGE)
					printf("〥");  //map
				else
					printf("﹥"); //user block
			}
			else
				printf("  ");
		}
	}

}

/*
check all line from SCREEN_HEIGHT - 2 to 0
and if line is full then Return y(line number)
*/
int Clear_Line(void)
{
	int x, y; //
	int count = 0;// count to block number in one line

	for (y = SCREEN_HEIGHT - 2; y > 0; y--) {
		if (Check_line(y))
		{
			count = 0; // reset count
			for (x = 1; x < SCREEN_WIDTH - 1; x++) {
				if (screen[y][x] == 1) {
					count += 1; //count to block (1*1)
				}
			}
			if (count == SCREEN_WIDTH - 2) {// if fill line
				return y; //return line number
			}
		}
	}

	return 0;
}

//Method to move down block ,if fill line delete
void Shift_Screen(int y)
{
	int x; // width

	for (; y > 0; y--) {//check from down to up
		for (x = 1; x < SCREEN_WIDTH - 1; x++) {//one line in the map
			screen[y][x] = screen[y - 1][x]; // move to down
		}
	}
}

/*
if something in the line return 1
*/
int Check_line(int line)
{
	int i;

	for (i = 1; i < SCREEN_WIDTH - 2; i++) {// check in one line
		if (screen[line][i] == 1) { // whatever in line
			return 1;
		}
	}
	return 0;
}

//Intro, Game Start
int Intro(void)
{
	int mode; // select mode
	int userkey;// user pressd
	set_cursor(20, 5);
	puts("﹥﹥﹥﹥﹥ ﹥﹥﹥﹥﹥ ﹥﹥﹥﹥﹥ ﹥﹥﹥﹥   ﹥﹥﹥﹥﹥ ﹥﹥﹥﹥﹥");
	set_cursor(20, 6);
	puts("    ﹥     ﹥             ﹥     ﹥     ﹥      ﹥    ﹥");
	set_cursor(20, 7);
	puts("    ﹥     ﹥             ﹥     ﹥     ﹥      ﹥    ﹥");
	set_cursor(20, 8);
	puts("    ﹥     ﹥﹥﹥﹥﹥     ﹥     ﹥﹥﹥﹥       ﹥     ﹥﹥﹥﹥﹥");
	set_cursor(20, 9);
	puts("    ﹥     ﹥             ﹥     ﹥  ﹥         ﹥		    ﹥");
	set_cursor(20, 10);
	puts("    ﹥     ﹥             ﹥     ﹥    ﹥       ﹥		    ﹥");
	set_cursor(20, 11);
	puts("    ﹥     ﹥﹥﹥﹥﹥     ﹥     ﹥      ﹥ ﹥﹥﹥﹥﹥ ﹥﹥﹥﹥﹥");
	set_cursor(20, 14);
	printf("CHOOSE GAME MODE");
	set_cursor(20, 15);
	printf("1.Classic");
	set_cursor(20, 16);
	printf("2.Item");
	set_cursor(20, 17);
	printf("3.AI");
	userkey = _getch();// step for game start
				// we need for select mode
	switch (userkey)
	{
		case 49:
			mode= 1;
			break;
		case 50:
			mode= 2;
			break;
		case 51:
			mode= 3;
			break;
	}
	return mode;
}

//show next shape
void show_nextshape(void)
{
	int i, j;

	set_cursor(45, 2);
	puts("Next Shape");

	set_cursor(45, 3);
	puts("﹤﹤﹤﹤﹤﹤");
	//draw next blcok
	for (i = 0; i < 4; i++) {
		// left side cast
		set_cursor(45, 4 + i);
		printf("﹤");

		for (j = 0; j < 4; j++) {
			if (shapes[next_shape][0][i][j] == 1)
				printf("﹤");
			else
				printf("  ");

		}
		//right side cast
		puts("﹤");

	}
	set_cursor(45, 8);
	puts("﹤﹤﹤﹤﹤﹤");
}

void show_score(int score)
{
	int i, j;
	set_cursor(45, 10);
	puts("GAME SCORE");

	set_cursor(45, 11);
	puts("忙式式式式式式式式式忖");
	//draw next blcok
	for (i = 0; i < 1; i++) {
		// left side cast
		if(i==0)
		{
			set_cursor(47,12+i);
			printf("%d", score);
		}
		set_cursor(45, 12 + i);
		printf("弛");
		set_cursor(55, 12 + i);
		//right side cast
		puts("弛");
	}
	
	set_cursor(45, 13);
	puts("戌式式式式式式式式式戎");
}
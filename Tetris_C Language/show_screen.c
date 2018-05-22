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
				printf("бр");
			}
			else if (screen[i][j] == 1)
			{
				if (j == SCREEN_LEFT_EDGE && i == SCREEN_DOWN_EDGE)
					printf("в╔");  //map
				else if (j == SCREEN_RIGHT_EDGE && i == SCREEN_DOWN_EDGE)
					printf("в╩");  //map
				else if (j == SCREEN_LEFT_EDGE || j == SCREEN_RIGHT_EDGE)
					printf("в╚");  //map
				else if (i == SCREEN_DOWN_EDGE)
					printf("в╟");  //map
				else
					printf("бс"); //user block
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
	char start[10] = { 0 };// for user key pressed
	char compare[10] = "start"; // for checking to start

	set_cursor(20, 5);
	puts("бсбсбсбсбс бсбсбсбсбс бсбсбсбсбс бсбсбсбс   бсбсбсбсбс бсбсбсбсбс");
	set_cursor(20, 6);
	puts("    бс     бс             бс     бс     бс      бс    бс");
	set_cursor(20, 7);
	puts("    бс     бс             бс     бс     бс      бс    бс");
	set_cursor(20, 8);
	puts("    бс     бсбсбсбсбс     бс     бсбсбсбс       бс     бсбсбсбсбс");
	set_cursor(20, 9);
	puts("    бс     бс             бс     бс  бс         бс		    бс");
	set_cursor(20, 10);
	puts("    бс     бс             бс     бс    бс       бс		    бс");
	set_cursor(20, 11);
	puts("    бс     бсбсбсбсбс     бс     бс      бс бсбсбсбсбс бсбсбсбсбс");

	set_cursor(20, 14);
	printf("If you want to start game input \"start\" : ");
	gets(start);// step for game start
				// we need for select mode
	if (!strcmp(start, compare))
		return 1;
	else
		return 0;
}

//show next shape
void show_nextshape(void)
{
	int i, j;

	set_cursor(45, 2);
	puts("Next Shape");

	set_cursor(45, 3);
	puts("брбрбрбрбрбр");
	//draw next blcok
	for (i = 0; i < 4; i++) {
		// left side cast
		set_cursor(45, 4 + i);
		printf("бр");

		for (j = 0; j < 4; j++) {
			if (shapes[next_shape][0][i][j] == 1)
				printf("бр");
			else
				printf("  ");

		}
		//right side cast
		puts("бр");

	}
	set_cursor(45, 8);
	puts("брбрбрбрбрбр");
}
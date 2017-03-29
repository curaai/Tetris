#include "show.h"	
#include "library.h"
#include "tetris_function.h"
#include "shapes.h"

void set_cursor(int x, int y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void remove_cursor()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}

void fill_screen()
{
	int i;

	//fill the edge of width
	for (i = 0; i < SCREEN_HEIGHT; i++) {
		screen[i][0] = 1;
		screen[i][SCREEN_WIDTH - 1] = 1;
	}
	//fill the array's base
	for (i = 1; i < SCREEN_WIDTH; i++) {
		screen[SCREEN_HEIGHT - 1][i] = 1;
	}
}

void show_screen(void)
{
	int i, j;

	//print screen
	for (i = 0; i < SCREEN_HEIGHT; i++) {
		set_cursor(5, 2 + i);

		for (j = 0; j < SCREEN_WIDTH; j++) {
			if (screen[i][j] == 1)
			{
				if (j == SCREEN_LEFT_EDGE && i == SCREEN_DOWN_EDGE)
					printf("▨");
				else if (j == SCREEN_RIGHT_EDGE && i == SCREEN_DOWN_EDGE)
					printf("▧");
				else if (j == SCREEN_LEFT_EDGE || j == SCREEN_RIGHT_EDGE)
					printf("▥");
				else if (i == SCREEN_DOWN_EDGE)
					printf("▤");
				else
					printf("■");
			}
			else
				printf("  ");
		}
	}

}

//find the filled line in screen
int Clear_Line(void)
{
	int x, y;
	int count = 0;

	for (y = SCREEN_HEIGHT - 2; y > 0; y--) {
		if (Check_line(y))
		{
			count = 0;
			for (x = 1; x < SCREEN_WIDTH - 1; x++) {
				if (screen[y][x] == 1) {
					count += 1;
				}
			}
			if (count == SCREEN_WIDTH - 2) {
				return y;
			}
		}
	}

	return 0;
}

//나중에 memcpy로 바꾸기
void Shift_Screen(int y)
{
	int x;

	for (; y > 0; y--) {
		for (x = 1; x < SCREEN_WIDTH - 1; x++) {
			screen[y][x] = screen[y - 1][x];
		}
	}
}

//if something in the line return 1
int Check_line(int line)
{
	int i;

	for (i = 1; i < SCREEN_WIDTH - 2; i++) {
		if (screen[line][i] == 1) {
			return 1;
		}
	}
	return 0;
}

//Intro, Game Start
int Intro(void)
{
	char start[10] = { 0 };
	char compare[10] = "start";

	set_cursor(20, 5);
	puts("■■■■■ ■■■■■ ■■■■■ ■■■■   ■■■■■ ■■■■■");
	set_cursor(20, 6);
	puts("    ■     ■             ■     ■     ■      ■    ■");
	set_cursor(20, 7);
	puts("    ■     ■             ■     ■     ■      ■    ■");
	set_cursor(20, 8);
	puts("    ■     ■■■■■     ■     ■■■■       ■     ■■■■■");
	set_cursor(20, 9);
	puts("    ■     ■             ■     ■  ■         ■		    ■");
	set_cursor(20, 10);
	puts("    ■     ■             ■     ■    ■       ■		    ■");
	set_cursor(20, 11);
	puts("    ■     ■■■■■     ■     ■      ■ ■■■■■ ■■■■■");

	set_cursor(20, 14);
	printf("If you want to start game input \"start\" : ");
	gets(start);

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
	puts("□□□□□□");

	for (i = 0; i < 4; i++) {
		set_cursor(45, 4 + i);
		printf("□");

		for (j = 0; j < 4; j++) {
			if (shapes[next_shape][0][i][j] == 1)
				printf("□");
			else
				printf("  ");

		}
		puts("□");

	}
	set_cursor(45, 8);
	puts("□□□□□□");
}
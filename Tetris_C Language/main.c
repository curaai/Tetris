#include "library.h"
#include "tetris_function.h"
#include "show.h"
#include "shapes.h"

int main(void)
{
	BLOCK* block;


	if (Intro())
	{
		system("cls");
		block = first_block();
		fill_screen();
		show_screen();

		run_game(block);
	}
	return 0;
}
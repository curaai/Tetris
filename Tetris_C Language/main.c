#include "library.h"
#include "tetris_function.h"
#include "show.h"
#include "shapes.h"

int main(void)
{
	BLOCK* block;


	if (Intro()==1) // origin mode
	{
		system("cls");
		block = first_block(); //make first block
		fill_screen();// make the tetris map
		show_screen();// make all thing 
					  
		run_game(block);// run the game
	}
	else if (Intro() == 2) // using Item mode
	{
		system("cls");
		block = first_block(); //make first block
		fill_screen();// make the tetris map
		show_screen();// make all thing 

		run_game(block);// run the game
	}
	else if (Intro() == 3) // show AI mode
	{
		system("cls");
		block = first_block(); //make first block
		fill_screen();// make the tetris map
		show_screen();// make all thing 

		run_game(block);// run the game
	}
	return 0;
}
#ifndef _TETRIS_
#define _TETRIS_

int make_randint(int limit);
BLOCK* first_block(void);
BLOCK* item_first_block(void);
BLOCK* make_block(BLOCK* pre);
BLOCK* item_make_block(BLOCK* pre);
void input_block(BLOCK* block);
int checkdown(BLOCK* block);
void Remove_Block(BLOCK* block);
void control_shape(BLOCK* block);
void run_game(BLOCK* block);
void run_itemgame(BLOCK* block);
int checkleft(BLOCK* block);
int checkright(BLOCK* block);
int checkshape(BLOCK* block);
int Check_Over(void);

#endif // !_TETRIS_
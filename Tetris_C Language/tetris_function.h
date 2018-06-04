#ifndef _TETRIS_
#define _TETRIS_

int make_randint(int limit);
BLOCK* first_block(void);
BLOCK* item_first_block(void);
BLOCK* make_block(BLOCK* pre);
BLOCK* item_make_block(BLOCK* pre);
void input_block(BLOCK* block);
int checkdown(BLOCK* block);
void remove_Block(BLOCK* block);
void control_shape(BLOCK* block);
void run_game(BLOCK* block);
void run_itemgame(BLOCK* block);
int checkleft(BLOCK* block);
int checkright(BLOCK* block);
int checkrotate(BLOCK* block);
int check_Over(int score);

void aicontrol_shape(BLOCK* block, int * rotateIndex, int * xIndex);
int block_exist(BLOCK *clone, int rotate, int x);
void blockdestination(BLOCK *future);
BLOCK *bombitem(BLOCK *pre);
void copyblock(BLOCK *block, BLOCK *copy);
void effectbomb(BLOCK *bomb);
void effecterase(BLOCK *erase);
BLOCK *eraseitem(BLOCK *pre);
int option_blocking_block(BLOCK *clone);
int option_clearline(BLOCK *clone);
int option_maxheight(BLOCK *clone);
int option_blockside(BLOCK *clone);
int option_wallside(BLOCK *clone);
int option_downside(BLOCK *clone);
int option_emptyspace(BLOCK *clone);

void run_AIgame(BLOCK* block);
void run_itemgame(BLOCK* block);
#endif // !_TETRIS_
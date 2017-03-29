#ifndef _SHOW_H__
#define _SHOW_H__

void set_cursor(int x, int y);
void remove_cursor();
void fill_screen();
void show_screen(void);
int Clear_Line(void);
int Check_line(int line);
void Shift_Screen(int y);
void show_nextshape(void);

#endif // !_SHOW_H__
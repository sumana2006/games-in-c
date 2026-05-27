#ifndef PLATFORM_H
#define PLATFORM_H
void sleep_ms(int ms);
void clear_screen();
int get_key();
int kbhit();
void move_cursor(int x, int y);
void hide_cursor();
void show_cursor();
#endif

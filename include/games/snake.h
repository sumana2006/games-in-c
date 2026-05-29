#ifndef SNAKE_H
#define SNAKE_H

#define SNAKE_MAX_TAIL 50
#define SNAKE_DEFAULT_HEIGHT 20
#define SNAKE_DEFAULT_WIDTH 20

#define SNAKE_HEAD 'O'
#define SNAKE_BODY 'o'
#define SNAKE_FRUIT '@'
#define SNAKE_BORDER '*'


typedef enum {
    DIR_NONE,
    DIR_UP,
    DIR_DOWN,
    DIR_LEFT,
    DIR_RIGHT
} SnakeDirection;


typedef struct {
    int x, y;
    int fruit_x, fruit_y;
    int score;
    int pieces;
    int tailx[SNAKE_MAX_TAIL];
    int taily[SNAKE_MAX_TAIL];
    int game_over;
    SnakeDirection direction;
    int height;
    int width;
    int tick_delay;
} SnakeState;

void snake_startup();

void snake_init(SnakeState *s);
void snake_input(SnakeState *s);
void snake_update(SnakeState *s);
void snake_render(SnakeState *s);

void snake_cleanup();

int snake_is_over(SnakeState *s);

#endif

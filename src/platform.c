#include "platform.h"
#include <stdlib.h>

#ifdef _WIN32

    #include <windows.h>
    #include <conio.h>

    int kbhit() {
    return _kbhit();
}

    void sleep_ms(int ms) {
        Sleep(ms);
    }

    void clear_screen() {
        system("cls");
    }

    int get_key() {
        return _getch();
    }

    void move_cursor(int x, int y) {
    }

    void hide_cursor() {
    }

#else

    #include <unistd.h>
    #include <termios.h>
    #include <stdio.h>
    #include <fcntl.h>

      int kbhit() {
        struct termios oldt, newt;
        int ch;
        int oldf;

        tcgetattr(STDIN_FILENO, &oldt);

        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);

        tcsetattr(STDIN_FILENO, TCSANOW, &newt);

        oldf = fcntl(STDIN_FILENO, F_GETFL, 0);

        fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

        ch = getchar();

        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

        fcntl(STDIN_FILENO, F_SETFL, oldf);

        if(ch != EOF) {
            ungetc(ch, stdin);
            return 1;
        }

        return 0;
    }

    void sleep_ms(int ms) {
        usleep(ms * 1000);
    }

    void clear_screen() {
        system("clear");
    }

    int get_key() {
        struct termios oldt, newt;
        int ch;

        tcgetattr(STDIN_FILENO, &oldt);

        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);

        tcsetattr(STDIN_FILENO, TCSANOW, &newt);

        ch = getchar();

        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

        return ch;
    }

    void move_cursor(int x, int y) {
    printf("\033[%d;%dH", y + 1, x + 1);
}

    void hide_cursor() {
    printf("\033[?25l");
}
    void show_cursor() {
    printf("\033[?25h");
}
#endif


#include "print.h"
#include <unistd.h>

void print_grid(int **grid, int size)
{
    char buf[2];
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            buf[0] = grid[i][j] + '0';
            write(1, buf, 1);
            if (j < size - 1) {
                buf[0] = ' ';
                write(1, buf, 1);
            }
        }
        buf[0] = '\n';
        write(1, buf, 1);
    }
}

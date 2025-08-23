#include "utils.h"
#include <stdlib.h>
#include <ctype.h>

int parse_views(const char *str, int *views, int size)
{
    int i = 0, j = 0;
    int max = size * 4;
    while (str[i]) {
        if (isdigit(str[i])) {
            if (j >= max)
                return 0;
            views[j++] = str[i] - '0';
        }
        else if (str[i] != ' ')
            return 0;
        i++;
    }
    return (j == max);
}

static int count_visible(int *line, int size)
{
    int max = 0, count = 0;
    for (int i = 0; i < size; i++) {
        if (line[i] > max) {
            max = line[i];
            count++;
        }
    }
    return count;
}

int check_all_views(int **grid, int *views, int size)
{
    int *line = malloc(sizeof(int) * size);
    // Top views
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++)
            line[j] = grid[j][i];
        if (count_visible(line, size) != views[i]) {
            free(line);
            return 0;
        }
    }
    // Bottom views
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++)
            line[j] = grid[size-1-j][i];
        if (count_visible(line, size) != views[size+i]) {
            free(line);
            return 0;
        }
    }
    // Left views
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++)
            line[j] = grid[i][j];
        if (count_visible(line, size) != views[size*2+i]) {
            free(line);
            return 0;
        }
    }
    // Right views
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++)
            line[j] = grid[i][size-1-j];
        if (count_visible(line, size) != views[size*3+i]) {
            free(line);
            return 0;
        }
    }
    free(line);
    return 1;
}


#include "utils.h"
#include <stdlib.h>

static int g_idx = 0;

static int fill_line(int *line, int **grid, int size, int mode) {
    int j = 0;
    while (j < size) {
        if (mode == 0) // Top
            line[j] = grid[j][g_idx];
        else if (mode == 1) // Bottom
            line[j] = grid[size-1-j][g_idx];
        else if (mode == 2) // Left
            line[j] = grid[g_idx][j];
        else if (mode == 3) // Right
            line[j] = grid[g_idx][size-1-j];
        j++;
    }
    return 0;
}

int parse_views(const char *str, int *views, int size)
{
    int i = 0, j = 0;
    int max = size * 4;
    while (str[i]) {
        if (str[i] >= '0' && str[i] <= '9') {
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
    int i = 0;
    while (i < size) {
        if (line[i] > max) {
            max = line[i];
            count++;
        }
        i++;
    }
    return count;
}

int check_all_views(int **grid, int *views, int size)
{
	int *line = malloc(sizeof(int) * size);
	if (!line)
		return 0;
	int mode = 0, offset = 0;
	while (mode < 4) {
		int i = 0;
		while (i < size) {
			g_idx = i;
			fill_line(line, grid, size, mode);
			if (count_visible(line, size) != views[offset + i]) {
				free(line);
				return 0;
			}
			i++;
		}
		offset += size;
		mode++;
	}
	free(line);
	return 1;
}

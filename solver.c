
#include "solver.h"
#include "utils.h"

static int is_valid(int **grid, int row, int col, int num, int size);
static int check_views(int **grid, int *views, int size);

int solve(int **grid, int *views, int size)
{
    int row, col, num;
    for (row = 0; row < size; row++) {
        for (col = 0; col < size; col++) {
            if (grid[row][col] == 0) {
                for (num = 1; num <= size; num++) {
                    if (is_valid(grid, row, col, num, size)) {
                        grid[row][col] = num;
                        if (solve(grid, views, size))
                            return 1;
                        grid[row][col] = 0;
                    }
                }
                return 0;
            }
        }
    }
    return check_views(grid, views, size);
}

static int is_valid(int **grid, int row, int col, int num, int size)
{
    for (int i = 0; i < size; i++) {
        if (grid[row][i] == num || grid[i][col] == num)
            return 0;
    }
    return 1;
}

static int check_views(int **grid, int *views, int size)
{
    return check_all_views(grid, views, size);
}

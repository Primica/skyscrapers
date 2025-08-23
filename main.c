#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "solver.h"
#include "utils.h"
#include "print.h"


int main(int argc, char **argv)
{
	if (argc != 2) {
		write(2, "Error\n", 6);
		return 1;
	}
	// Count digits in input to determine size
	int count = 0;
	for (int i = 0; argv[1][i]; i++)
		if (argv[1][i] >= '1' && argv[1][i] <= '9')
			count++;
	int size = 0;
	for (int n = 4; n <= 9; n++) {
		if (count == n * 4) {
			size = n;
			break;
		}
	}
	if (size == 0) {
		write(2, "Error\n", 6);
		return 1;
	}
	int *views = malloc(sizeof(int) * size * 4);
	int **grid = malloc(sizeof(int *) * size);
	for (int i = 0; i < size; i++) {
		grid[i] = calloc(size, sizeof(int));
	}
	if (!parse_views(argv[1], views, size)) {
		write(2, "Error\n", 6);
		goto cleanup;
	}
	if (solve(grid, views, size))
		print_grid(grid, size);
	else
		write(2, "Error\n", 6);
cleanup:
	for (int i = 0; i < size; i++)
		free(grid[i]);
	free(grid);
	free(views);
	return 0;
}

/*
 * Created by 0xEDD1E on 2016-05-16.
 *
 * Given a m x n grid filled with non-negative numbers,
 * find a path from top left to bottom right which minimizes the sum of all numbers along its path.
 * Note: You can only move either down or right at any point in time.
 *
 * function signature:
 *
 * int minPathSum(int** grid, int gridRowSize, int gridColSize) {}
 */

#include <stdio.h>
#include <stdlib.h>

#define min(A, B) (A < B) ? (A) : (B)

int minPathSum(int **, int, int);
int **gridGenerator(int, int);
int **get2DArray(int rows, int cols);

int main(void)
{
    int n = 5, m = 4;
    scanf("%d %d", &n, &m);

    int **grid = gridGenerator(n, m);

    printf("%d\n", minPathSum(grid, n, m));

    return 0;
}

int **get2DArray(int rows, int cols)
{
    int **mat = (int **) malloc((size_t) rows * sizeof (int *));

    for (int i = 0; i < rows; i++)
        mat[i] = (int *) malloc((size_t) cols * sizeof (int));

    return mat;
}

int **gridGenerator(int rows, int cols)
{
    int **grid = get2DArray(rows, cols);

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            grid[i][j] = rand() % 50;

    return grid;
}

int minPathSum(int **grid, int rows, int cols)
{
    int **pathSumGrid = get2DArray(rows, cols);

    /* idea is very simple, maintain an additional grid containing the
     * path sums for all points, let pathSumGrid represent that grid
     * then pathSumGrid[i][j] be an arbitrary element from pathSumGrid.
     * Then pathSumGrid[i][j] = minimum sum of the path to grid[i][j] from grid[0][0]
     * Hence, pathSumGrid[row-1][col-1] is the needed sum
     */

    pathSumGrid[0][0] = grid[0][0]; // initially copy the very first number of the grid to pathSumGrid

    // second step: phase one: fill the top row, just accumulate the left elements
    for (int zero_col_idx = 1; zero_col_idx < cols; zero_col_idx++)
        pathSumGrid[0][zero_col_idx] = grid[0][zero_col_idx] + pathSumGrid[0][zero_col_idx - 1];

    // second step: phase two: fill the leftmost column, just accumulate the upper elements
    for (int zero_row_idx = 1; zero_row_idx < rows; zero_row_idx++)
        pathSumGrid[zero_row_idx][0] = grid[zero_row_idx][0] + pathSumGrid[zero_row_idx - 1][0];

    // fill the array below from (1, 1); Dynamic solution
    for (int i = 1; i < rows; i++)
        for (int j = 1; j < cols; j++)
            pathSumGrid[i][j] = min(pathSumGrid[i - 1][j] + grid[i][j], pathSumGrid[i][j - 1] + grid[i][j]);

    // return the last element of pathSumGrid
    return pathSumGrid[rows - 1][cols -1];
}


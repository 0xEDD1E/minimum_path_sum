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

/**
 * Driver Function:
 *      Get n and m from the user
 *      Generates an random grid of user-given dimensions
 *      prints the minimum path sum
 */
int main(void)
{
    int rows, cols;
    scanf("%d %d", &rows, &cols);

	rows = (rows < 0) ? -rows : rows; // get the absolute values
	cols = (cols < 0) ? -cols : cols; // of `rows` and `cols`

    //int **grid = gridGenerator(n, m);
	int **grid = get2DArray(rows, cols);

	// read user's grid 'space-separrated' columns and 'new-line separated' rows
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++) {
			int tmp;                       // if user input ,
			scanf("%d", &tmp);             // a negative integer,
			tmp = (tmp < 0) ? -tmp : tmp;  // take the absolute value.
			grid[i][j] = tmp;
		}

    printf("%d\n", minPathSum(grid, rows, cols));

    return 0;
}

/**
 * get2DArray(rows, columns) : int**
 *      allocator for a 2D array of dimensions rowsxcolumns
 */
int **get2DArray(int rows, int cols)
{
    int **mat = (int **) malloc((size_t) rows * sizeof (int *));

    for (int i = 0; i < rows; i++)
        mat[i] = (int *) malloc((size_t) cols * sizeof (int));

    return mat;
}

/**
 * gridGenerator(rows, columns) : int**
 *      create a 2D array,
 *      fill the grid with random integers between 0 and 49
 *      return the array
 */
int **gridGenerator(int rows, int cols)
{
    int **grid = get2DArray(rows, cols);

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            grid[i][j] = rand() % 50;

    return grid;
}

/**
 * minPathSum(grid, rows, columns) : int
 *      create new `pathSumGrid` of same dimensions as `grid`
 *      fill the first row:
 *          for idx = 0 to cols:
 *              pathSumGrid[0][idx] = grid[0][idx] + pathSumGrid[0][idx - 1]
 *
 *      fill the leftmost column:
 *          for idx = 0 to rows:
 *              pathSumGrid[idx][0] = grid[idx][0] + pathSumGrid[idx - 1][0]
 *
 *      At this point if we get an element from the top row or leftmost column of pathSumGrid,
 *      that element contains the sum of the path from grid[0][0] to that point.
 *      Now we can complete filling pathSumGrid from pathSumGrid[1][1], Generally,
 *          pathSumGrid[i][j] = min(pathSumGrid[i][j-1], pathSumGrid[i-1][j]) + grid[i][j] ; i, j >= 1
 *
 *      Finally, after filling the pathSumGrid, we can get the answer (minimum path sum) by simply
 *      looking at the last element of the pathSumGrid
 */
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

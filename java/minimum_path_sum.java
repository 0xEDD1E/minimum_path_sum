/**
 * Created by 0xEDD1E on 2016-05-17.
 */
import java.util.*;

class MinPathSum {
    private int rows, cols;
    private int grid[][];

    public MinPathSum() {
        rows = -1;
        cols = -1;
    }

    public void readgrid() {
        Scanner stdin = new Scanner(System.in);
        rows = Math.abs(stdin.nextInt());
        cols = Math.abs(stdin.nextInt());

        grid = new int[rows][cols];

        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                grid[i][j] = Math.abs(stdin.nextInt());
    }

    public int minPathSum() {

        if (rows == -1 || cols == -1) {
            System.out.println("Trying to access uninitialized grid: \n\tuser readGrid() before calling minPathSum()");
            return -1;
        }
        int pathSumGrid[][] = new int[rows][cols];

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
                pathSumGrid[i][j] = Math.min(pathSumGrid[i - 1][j] + grid[i][j], pathSumGrid[i][j - 1] + grid[i][j]);

        // return the last element of pathSumGrid
        return pathSumGrid[rows - 1][cols -1];
    }
}

public class minimum_path_sum {
    public static void main(String [] args) {
        MinPathSum grid = new MinPathSum();
        grid.readgrid();
        System.out.println(grid.minPathSum());
    }
}

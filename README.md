# Solution for Minimum Path Sum Challenge

### Problem Statement
I found this programming question at [leetcode.com](https://leetcode.com/problems/minimum-path-sum/ "Goto original problem statement"). Just for clarity let me write it down here.

>Given a m x n grid filled with non-negative numbers, find a path from top left to bottom right which minimizes the sum of all numbers along its path.
>Note: You can only move either down or right at any point in time.

### My Solution
I found an quite interesting *Dynamic Programming* solution after struggling with this problem. 

My solution is to maintain another same-dimension grid as the given grid, which contains the minimum path sums for every point (if we start travel from (0,0))

This is my *Dynamic Programming* equation for this problem

![PSG[i][j] = min(PSG[i][j-1], PSG[i-1][j]) + G[i][j]](http://s19.postimg.org/eyhv6zbcz/Code_Cogs_Eqn.png)

here `PSG` is the additional path Sum grid, and `G` is the given grid. Initially `PSG[0][0] = G[0][0]`

You can find a solution in `C` in `minimum_path_sum.c`

:pencil2: 0xEDD1E

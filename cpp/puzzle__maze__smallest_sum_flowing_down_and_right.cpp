/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
25 Sept. 2022

Solve this "Minimum path sum" LeetCode problem: https://leetcode.com/problems/minimum-path-sum/

[my wording]:
Given an `n x m` grid filled with numbers, find a path from the top left to bottom right, which
minimizes the sum of all numbers along its path.

Note: You can only move either down or right at any point in time.

Example 1:
Input: grid = [[1, 3, 1],
               [1, 5, 1],
               [4, 2, 1]]
Output: 7
Explanation: Because the path 1 → 3 → 1 → 1 → 1 minimizes the sum.

Example 2:
Input: grid = [[1, 2, 3],
               [4, 5, 6]]
Output: 12; path: 1 -> 2 -> 3 -> 6

Example 3:
Input: grid = [[1,   2, 3],
               [4, -10, 6]]
Output: -1; path: 1 -> 2 -> -10 -> 6

Example 4:
Input: grid = [
    [1,     2,  3, 7],
    [4,   -10,  6, 3],
    [4,    -1, -5, 6],
    [-12,   3,  8, 9],
]
Output: 2; path: 1 -> 2 -> −10 -> −1 -> −5 -> 6 -> 9


Try to also print out all possible paths to solve this "maze", traversing through the end, to ensure
my brute-force technique is working!

I'm not a premium member, so the official LeetCode solution and explanation
(https://leetcode.com/problems/minimum-path-sum/solution/) is blocked from me. However, the
community **discussion** is available
(https://leetcode.com/problems/minimum-path-sum/discuss/?currentPage=1&orderBy=hot&query=), and
here's a good solution I found there. I left a comment:
https://leetcode.com/problems/minimum-path-sum/discuss/2622619/C%2B%2BorDPorEasy-to-Understand

Their code:
Note: I think `dp` means "dynamic programming".
```cpp
int minPathSum(vector<vector<int>>& grid) {
    int x = grid.size();
    int y = grid[0].size();
    vector<vector<int>> dp(x, vector<int>(y, 0));
    int i = 0, j = 0;
    for(i = 0; i < x; ++i)
        for(j = 0; j < y; ++j)
        {
            if(i == 0 && j == 0)
                dp[i][j] = grid[0][0];
            else if(j == 0)
                dp[i][j] = dp[i-1][j]+ grid[i][j];
            else if(i == 0)
                dp[i][j] = dp[i][j-1]+ grid[i][j];
            else
                dp[i][j] = min(dp[i-1][j], dp[i][j-1]) + grid[i][j];
        }
    return dp[x-1][y-1];
}
```


STATUS: wip: it runs as-is and works, but needs a ton of clean-up and work to accomplish all of my
TODOs and stated objectives!

To compile and run (assuming you've already `cd`ed into this dir):
```bash
# NB: you may need to use `-std=gnu++17` instead of `-std=c++17` in order to obtain extra GNU
# gcc features, including gcc extensions, POSIX cmds, and Linux sytem cmds.
# See: [my answer]: https://stackoverflow.com/a/71801111/4561887

# 1. In C++
time g++ -Wall -Wextra -Werror -O3 -std=c++17 puzzle__maze__smallest_sum_flowing_down_and_right.cpp -o bin/a && bin/a
```

References:
1. https://leetcode.com/problems/minimum-path-sum/
    1. https://leetcode.com/problems/minimum-path-sum/discuss/2622619/C%2B%2BorDPorEasy-to-Understand
1. algorithm - Programming theory: Solve a maze - Stack Overflow [NEED TO STUDY & READ: MAZE SOLVING
   ALGORITHM--LIKE A BINARY TREE]: https://stackoverflow.com/q/3097556/4561887
1. Google search for "stack overflow maze":
   https://www.google.com/search?q=stack+overflow+maze&oq=stack+overflow+maze&aqs=chrome..69i57j69i64l2.7102j0j7&sourceid=chrome&ie=UTF-8

*/

// C++ includes
#include <algorithm> // `std::min()`
#include <cassert>
#include <climits>  // `INT_MAX`
#include <cstdint>  // For `uint8_t`, `int8_t`, etc.
#include <cstdio>   // For `printf()`
#include <iostream>  // For `std::cin`, `std::cout`, `std::endl`, etc.
#include <vector>


// The user-contributed LeetCode example solution from here:
// https://leetcode.com/problems/minimum-path-sum/discuss/2622619/C%2B%2BorDPorEasy-to-Understand
// TODO: CLEAN THIS UP!
// - I really like this solution because it is easy to conceptualize, and it is optimized to store
//   the shortest sum to ANY x/y position in that x/y position of the dp (dynamic programming)
//   grid.
// - Basically, it just walks through the 2D array over all rows and all columns in the grid.
//      - For the starting position in the top-left, the sum for that cell is equal to the value in
//        that cell.
//      - For the first row in all columns, there is only one way to get to that cell (from the
//        left), so it just sums the cell to the left with this cell.
//      - For the first column in all rows, there is only one way to get to that cell (from the
//        top), so it just sums the cell above with this cell.
//      - For all other cells, however, there are **two** ways to get to this cell (either from
//        above OR from the left), so it chooses the path with the shortest sum, adding that value
//        to the current cell!
//      - Finally, when done iterating over the entire grid, the shortest sum is stored in the last
//        cell in the very bottom-right!
int MinPathSum1(const std::vector<std::vector<int>>& grid)
{
    int x = grid.size();
    int y = grid[0].size();
    std::vector<std::vector<int>> dp(x, std::vector<int>(y, 0));
    int i = 0, j = 0;
    for(i = 0; i < x; ++i)
        for(j = 0; j < y; ++j)
        {
            if(i == 0 && j == 0)
                dp[i][j] = grid[0][0];
            else if(j == 0)
                dp[i][j] = dp[i-1][j]+ grid[i][j];
            else if(i == 0)
                dp[i][j] = dp[i][j-1]+ grid[i][j];
            else
                dp[i][j] = std::min(dp[i-1][j], dp[i][j-1]) + grid[i][j];
        }

    int min_path_sum = dp[x-1][y-1];
    printf("min_path_sum = %i\n", min_path_sum);

    return min_path_sum;
}


// TODO: Use the same approach as `MinPathSum1()` just above, but also store the (i,j) trail of the
// best path taken (in a new vector), to print it out and visually inspect it! I think this will
// require starting at the end and manually walking backwards. Have it also print, at the end, the
// path **graphically** with Xs, like this, for instance, to quickly see the shortest path taken!:
//
//      X X . .
//      . X X .
//      . . X X
//      . . . X
//
int MinPathSum2(const std::vector<std::vector<int>>& grid)
{
    (void) grid;
    return 5; /////
}


// TODO: make this an example which will brute-force print ALL possible paths! Notice that the
// approach above will only be able to print the BEST path easily. But, I'd like to also find and
// visualize ALL paths and get their resulting sums, to ensure I can brute-force this as well, as
// that's the beginning of a maze-solving algorithm.
// - Also, study this: https://stackoverflow.com/questions/3097556/programming-theory-solve-a-maze <========== STUDY THIS TOO! AND LEARN HOW TO TRAVERSE BINARY TREES!
//   You can think of a maze as a tree, which has occurred to me before.
// - To get me started on this, some of my thoughts and notes I emailed to myself are in the
//   comments here:

/// A node in the grid maze
struct MazeNode
{
    size_t i_x;
    size_t i_y;
    bool can_go_right = true;
    bool can_go_down = true;
    int64_t sum; // sum on this path as of this node
};

/// A vector of maze nodes to form a maze path
using MazePath = std::vector<MazeNode>;

/// This is a list of ALL possible maze paths. I'll brute-force populate this list, then graphically
/// print it in dots and Xs as well, and print the resulting sum.
std::vector<MazePath> mazePaths;

// TODO: my approach here will be to go right until I can't go right anymore. Then, go down. Always
// favor right first. Calculate the sum as you go, and store the maze path as you go. Since you can
// ONLY go right and down, you already know that the length of ALL maze paths is the same, and is
// equal to `n + m` for an `n x m` grid. So, pre-size the vectors so you can just index into them
// easily with the `operator[]` withOUT going out of bounds in the grid.
//
// Once I've gotten to the end (which will just be straight right and then straight down for the
// first maze path), then I must go back one, and check for a different route, repeatedly, until I
// find a new, unexplored route. I'll keep a total tracker of the grid somehow with bool values for
// `can_go_right` and `can_go_down`. As I explore a given route I'll set those to false so I don't
// go in that direction that I've already gone, again.
int MinPathSum3(const std::vector<std::vector<int>>& grid)
{
    (void) grid;
    return 5; /////
}


// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("Minimum path sum\n");

    // Unit tests
    assert(MinPathSum1({{1, 3, 1}, {1, 5, 1}, {4, 2, 1}}) == 7);
    assert(MinPathSum1({{1, 2, 3}, {4, 5, 6}}) == 12);
    assert(MinPathSum1({{1, 2, 3}, {4, -10, 6}}) == -1);
    assert(MinPathSum1({{1, 2, 3, 7}, {4, -10, 6, 3}, {4, -1, -5, 6}, {-12, 3, 8, 9}}) == 2);

    printf("TESTS COMPLETED **SUCCESSFULLY**!\n");


    return 0;
}



/*
SAMPLE OUTPUT:

    eRCaGuy_hello_world/cpp$ time g++ -Wall -Wextra -Werror -O3 -std=c++17 puzzle__maze__smallest_sum_flowing_down_and_right.cpp -o bin/a && bin/a

    real    0m0.442s
    user    0m0.412s
    sys 0m0.030s
    Minimum path sum
    min_path_sum = 7
    min_path_sum = 12
    min_path_sum = -1
    min_path_sum = 2
    TESTS COMPLETED **SUCCESSFULLY**!


*/

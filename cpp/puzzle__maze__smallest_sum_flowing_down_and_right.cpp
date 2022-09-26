/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
25 Sept. 2022

Solve this "Minimum path sum" LeetCode problem: https://leetcode.com/problems/minimum-path-sum/

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
    int minsum = INT_MAX;
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


STATUS: wip: it runs as-is, but needs a ton of clean-up and work!

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

*/

// C++ includes
#include <algorithm> // `std::min()`
#include <cassert>
#include <climits>  // `INT_MAX`
#include <cstdint>  // For `uint8_t`, `int8_t`, etc.
#include <cstdio>   // For `printf()`
#include <iostream>  // For `std::cin`, `std::cout`, `std::endl`, etc.
#include <vector>

// TODO: CLEAN THIS UP!
int MinPathSum(const std::vector<std::vector<int>>& grid) {
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
    return dp[x-1][y-1];
}


// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("Minimum path sum\n");

    // Unit tests
    assert(MinPathSum({{1, 3, 1}, {1, 5, 1}, {4, 2, 1}}) == 7);
    assert(MinPathSum({{1, 2, 3}, {4, 5, 6}}) == 12);

    printf("TESTS COMPLETED **SUCCESSFULLY**!\n");


    return 0;
}



/*
SAMPLE OUTPUT:

    eRCaGuy_hello_world/cpp$ time g++ -Wall -Wextra -Werror -O3 -std=c++17 puzzle__maze__smallest_sum_flowing_down_and_right.cpp -o bin/a && bin/a

    real    0m0.448s
    user    0m0.407s
    sys 0m0.041s
    Minimum path sum
    TESTS COMPLETED **SUCCESSFULLY**!


*/

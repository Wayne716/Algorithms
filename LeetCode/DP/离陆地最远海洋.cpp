/*
 * https://leetcode-cn.com/problems/as-far-from-land-as-possible/
 * 从左上到右下 最优解从上方或者左方来
 * f(i, j) = 1 + min( f(i-1, j), f(i, j-1) )
 * 从右下到左上 最优解从右方或者下方来
 * f(i，j) = 1 + min( f(i+1, j), f(i, j+1) )
 * 最优解来自右上方的个时候
 * 第二阶段我们就需要用到第一阶段的计算结果
 */
 

class Solution {
public:
    int maxDistance(vector<vector<int>>& grid) {
        int mxN = 101;
        int M = grid.size(), N = grid[0].size();
        for (int i=0; i<M; ++i) {
            for (int j=0; j<N; ++j) {
                if (grid[i][j] == 1)
                    grid[i][j] = 0;
                else grid[i][j] = mxN;
            }
        }
        for (int i=0; i<M; ++i) {
            for (int j=0; j<N; ++j) {
                if (i>0)
                    grid[i][j] = min(grid[i][j], grid[i-1][j]+1);
                if (j>0)
                    grid[i][j] = min(grid[i][j], grid[i][j-1]+1);
            }
        }
        for (int i=M-1; i>=0; --i) {
            for (int j=N-1; j>=0; --j) {
                if (i<M-1)
                    grid[i][j] = min(grid[i][j], grid[i+1][j]+1);
                if (j<N-1)
                    grid[i][j] = min(grid[i][j], grid[i][j+1]+1);
            }
        }
        int res = 0;
        for (int i=0; i<M; ++i)
            for (int j=0; j<N; ++j)
                res = max(res, grid[i][j]);
        if (res==mxN || res==0) // 全是陆地或海洋
            res = -1;
        return res;
    }
};

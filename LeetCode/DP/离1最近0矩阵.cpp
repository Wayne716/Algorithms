/*
 * https://leetcode-cn.com/problems/01-matrix/
 * 从左上到右下 最优解从上方或者左方来
 * f(i, j) = 1 + min( f(i-1, j), f(i, j-1) )
 * 从右下到左上 最优解从右方或者下方来
 * f(i，j) = 1 + min( f(i+1, j), f(i, j+1) )
 * 最优解来自右上方的个时候
 * 第二阶段我们就需要用到第一阶段的计算结果
 */


class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& matrix) {
        int M = matrix.size(), N = matrix[0].size();
        vector<vector<int>> dp(M, vector<int>(N, 0));
        for (int i=0; i<M; ++i)
            for (int j=0; j<N; ++j)
                if (matrix[i][j]==1)
                    dp[i][j] = 10000;
        for (int i=0; i<M; ++i) {
            for (int j=0; j<N; ++j) {
                if (i>0)
                    dp[i][j] = min(dp[i-1][j]+1, dp[i][j]);
                if (j>0)
                    dp[i][j] = min(dp[i][j-1]+1, dp[i][j]);
            }
        }
        for (int i=M-1; i>=0; --i) {
            for (int j=N-1; j>=0; --j) {
                if (i<M-1)
                    dp[i][j] = min(dp[i+1][j]+1, dp[i][j]);
                if (j<N-1)
                    dp[i][j] = min(dp[i][j+1]+1, dp[i][j]);
            }
        }
        return dp;
    }
};

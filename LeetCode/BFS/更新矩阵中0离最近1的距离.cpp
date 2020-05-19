/*
 *  https://leetcode-cn.com/problems/01-matrix/
 *  首先把每个源点 0 入队
 *  然后从各个 0 同时开始一圈一圈的向 1 扩散
 *  每个 1 都是被离它最近的 0 扩散到的
 *  这里要注意先把 matrix 数组中 1 的位置设置成 -1
 *  只要是个无效的距离值来标志这个位置的 1 没有被访问过就行辣~
 */


class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& matrix) {
        int M = matrix.size(), N = matrix[0].size();
        queue<pair<int, int>> Q;
        for (int i=0; i<M; ++i) {
            for (int j=0; j<N; ++j) {
                if (matrix[i][j] == 0)
                    Q.push({i, j});
                else
                    matrix[i][j] = -1;
            }
        }
        int d[4][2] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
        while (!Q.empty()) {
            int x = Q.front().first;
            int y = Q.front().second;
            Q.pop();
            for (int i=0; i<4; ++i) {
                int newX = x + d[i][0];
                int newY = y + d[i][1];
                if (newX<0 || newX==M || newY<0 || newY==N)
                    continue;
                if (matrix[newX][newY] == -1) {
                    matrix[newX][newY] = matrix[x][y]+1;
                    Q.push({newX, newY});
                }
            }
        }
        return matrix;
    }
};

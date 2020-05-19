// https://leetcode-cn.com/problems/01-matrix/

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

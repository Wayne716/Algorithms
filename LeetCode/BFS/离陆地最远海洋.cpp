https://leetcode-cn.com/problems/as-far-from-land-as-possible/

class Solution {
public:
    int maxDistance(vector<vector<int>>& grid) {
        int M = grid.size(), N = grid[0].size();
        queue<pair<int, int>> Q;
        for (int i=0; i<M; ++i) {
            for (int j=0; j<N; ++j) {
                if (grid[i][j] == 1)
                    Q.push({i, j});
            }
        }
        int d[4][2] = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};
        int res = 0;
        while (!Q.empty()) {
            int x = Q.front().first;
            int y = Q.front().second;
            Q.pop();
            for (int i=0; i<4; ++i) {
                int newX = x + d[i][0];
                int newY = y + d[i][1];
                if (newX<0 || newX==M || newY<0 || newY==N)
                    continue;
                if (grid[newX][newY] == 0) {
                    grid[newX][newY] = grid[x][y]+1;
                    res = max(res, grid[newX][newY]);
                    Q.push({newX, newY});
                }
            }
        }
        return res-1;
    }
};

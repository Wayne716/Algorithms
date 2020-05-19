/*
 * https://leetcode-cn.com/problems/as-far-from-land-as-possible
 * 只要先把所有的陆地都入队，
 * 然后从各个陆地同时开始一层一层的向海洋扩散，
 * 那么最后扩散到的海洋就是最远的海洋！
 * 并且这个海洋肯定是被离他最近的陆地给扩散到的！
 * 10000 12002 12332 12332
 * 00001 20021 23321 23321
 * 00000 00002 30032 34432
 * 00000 20000 23003 23443
 * 10000 12000 12300 12344
 */

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
                    res = grid[newX][newY];
                    Q.push({newX, newY});
                }
            }
        }
        return res-1;
    }
};

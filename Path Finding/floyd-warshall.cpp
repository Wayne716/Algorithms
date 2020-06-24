#define INF 100

vector<vector<int>> FloydWarshall(vector<vector<int>>& graph) {
    vector<vector<int>> dist = graph;
    int V = graph.size();
    for (int k=0; k<V; ++k)
        for (int i=0; i<V; ++i)
            for (int j=0; j<V; ++j)
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
    return dist;
}

void print(vector<vector<int>> dist) {
    for (auto& v : dist) {
        for (auto &i : v)
            if (i == INF) cout << "INF" << '\t';
            else cout << i << '\t';
        cout << endl;
    }
}

int main()
{
    vector<vector<int>> G = { {0, 5, INF, 10},
                              {INF, 0, 3, INF},
                              {INF, INF, 0, 1},
                              {INF, INF, INF, 0} };
    print(FloydWarshall(G));
    return 0;
}

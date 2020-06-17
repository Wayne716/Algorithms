class Graph {
    int N;
    list<pair<int, int>>* adj;

public:
    Graph(int N) : N(N) {
        adj = new list<pair<int, int>>[N];
    }

    void addEdge(int u, int v, int w) {
        adj[u].push_back(make_pair(v, w));
        adj[v].push_back(make_pair(u, w));
    }

    void shortestPath(int start) {
        priority_queue<pair<int, int>> Q;
        int* distance = new int[N];
        for (int i=0; i<N; ++i)
            distance[i] = INT_MAX;
        Q.push(make_pair(0, start));
        distance[0] = 0;
        bool* visited = new bool[N];
        while (!Q.empty()) {
            int u = Q.top().second;
            Q.pop();
            if (visited[u]) continue;
            visited[u] = true;
            for (auto p : adj[u]) {
                int v = p.first;
                int w = p.second;
                if (distance[u] + w < distance[v]) {
                    distance[v] = distance[u] + w;
                    Q.push(make_pair(distance[v], v));
                }
            }
        }
        for (int i=0; i<N; ++i)
            cout << distance[i] << ' ';
    }
};

int main()
{
    int N = 9;
    Graph g(N);

    g.addEdge(0, 1, 4);
    g.addEdge(0, 7, 8);
    g.addEdge(1, 2, 8);
    g.addEdge(1, 7, 11);
    g.addEdge(2, 3, 7);
    g.addEdge(2, 8, 2);
    g.addEdge(2, 5, 4);
    g.addEdge(3, 4, 9);
    g.addEdge(3, 5, 14);
    g.addEdge(4, 5, 10);
    g.addEdge(5, 6, 2);
    g.addEdge(6, 7, 1);
    g.addEdge(6, 8, 6);
    g.addEdge(7, 8, 7);

    g.shortestPath(0);

    return 0;
}

class Graph {
public:
    Graph(int _N) : N(_N) {
        adj = new list<pair<int, int>>[_N];
    }

    void addEdge(int u, int v, int w) {
        adj[u].emplace_back(v, w);
    }

    void SPFA(int src) {
        int* dist = new int[N];
        for (int i=0; i<N; ++i)
            dist[i] = INT_MAX;
        dist[src] = 0;

        queue<int> Q;
        Q.push(src);

        bool* inQ = new bool[N];
        inQ[src] = true;

        while (!Q.empty()) {
            int u = Q.front();
            Q.pop();
            inQ[u] = false;
            for (auto it :adj[u]) {
                int v = it.first;
                int w = it.second;
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    if (!inQ[v]) {
                        Q.push(v);
                        inQ[v] = true;
                    }
                }
            }
        }

        print(dist);
        delete[] dist;
    }

    void print(int dist[]) const {
        for (int i=1; i<N; ++i)
            cout << dist[i] << endl;
    }

    ~Graph() {
        delete[] adj;
    }

public:
    int N;
    list<pair<int, int>>* adj;
};

int main()
{
    auto* graph = new Graph(6);

    graph->addEdge(1, 2, 1);
    graph->addEdge(2, 3, 7);
    graph->addEdge(2, 4, -2);
    graph->addEdge(1, 3, 8);
    graph->addEdge(1, 4, 9);
    graph->addEdge(3, 4, 3);
    graph->addEdge(2, 5, 3);
    graph->addEdge(4, 5, -3);

    graph->SPFA(1);

    delete graph;
    return 0;
}

/*

0
1
8
-1
-4

*/

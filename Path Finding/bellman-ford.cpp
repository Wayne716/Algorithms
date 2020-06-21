struct Edge {
    int src, dest, weight;
};

class Graph {
public:
    Graph(int _V, int _E) : V(_V), E(_E) {
        edge = new Edge[E];
    };

    void BellmanFord(Edge* edge, int src) {
        int* dist = new int[V];
        for (int i=0; i<V; ++i)
            dist[i] = INT_MAX;
        dist[0] = 0;

        for (int i=1; i<V; ++i) {
            for (int j=0; j<E; ++j) {
                int u = edge[j].src;
                int v = edge[j].dest;
                int weight = edge[j].weight;
                if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
                    dist[v] = dist[u] + weight;
            }
        }

        print(dist);

        delete[] dist;
    }

    void print(int dist[]) {
        for (int i=0; i<V; ++i)
            cout << dist[i] << ' ';
    }

    ~Graph() {
        delete[] edge;
    }

public:
    int V, E;
    Edge* edge;
};

int main()
{
    int V = 5, E = 8;
    Graph* graph = new Graph(V, E);

    graph->edge[0].src = 0;
    graph->edge[0].dest = 1;
    graph->edge[0].weight = -1;

    graph->edge[1].src = 0;
    graph->edge[1].dest = 2;
    graph->edge[1].weight = 4;

    graph->edge[2].src = 1;
    graph->edge[2].dest = 2;
    graph->edge[2].weight = 3;

    graph->edge[3].src = 1;
    graph->edge[3].dest = 3;
    graph->edge[3].weight = 2;

    graph->edge[4].src = 1;
    graph->edge[4].dest = 4;
    graph->edge[4].weight = 2;

    graph->edge[5].src = 3;
    graph->edge[5].dest = 2;
    graph->edge[5].weight = 5;

    graph->edge[6].src = 3;
    graph->edge[6].dest = 1;
    graph->edge[6].weight = 1;

    graph->edge[7].src = 4;
    graph->edge[7].dest = 3;
    graph->edge[7].weight = -3;

    graph->BellmanFord(graph->edge, 0);

    return 0;
}

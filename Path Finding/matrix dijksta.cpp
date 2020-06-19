#define V 9

int minDistance(int* distance, bool* visited) {
    int minDist = INT_MAX, index;
    for (int i=0; i<V; ++i) {
        if (!visited[i] && distance[i] < minDist) {
            index = i;
            minDist = distance[i];
        }
    }
    return index;
}

int* parent;

void printPath(int* parent, int i) {
    if (parent[i] == -1) {
        cout << i << ' ';
        return;
    }
    printPath(parent, parent[i]);
    cout << i << ' ';
}

void dijkstra(int graph[V][V], int start) {
    bool* visited = new bool[V];
    int* distance = new int[V];
    parent = new int[V];
    for (int i=0; i<V; ++i) {
        distance[i] = INT_MAX;
        parent[i] = -1;
    }
    distance[start] = 0;

    for (int c=0; c<V; ++c) {
        int u = minDistance(distance, visited);
        visited[u] = true;
        for (int v=0; v<V; ++v) {
            if (!visited[v] && graph[u][v] && distance[u] + graph[u][v] < distance[v]) {
                distance[v] = distance[u] + graph[u][v];
                parent[v] = u;
            }

        }
    }

    for (int i=0; i<V; ++i) {
        printPath(parent, i);
        cout << endl;
    }

    delete[] parent;
    delete[] visited;
    delete[] distance;
}

int main()
{
    int graph[V][V] = { { 0, 4, 0, 0, 0, 0, 0, 8, 0 },
                        { 4, 0, 8, 0, 0, 0, 0, 11, 0 },
                        { 0, 8, 0, 7, 0, 4, 0, 0, 2 },
                        { 0, 0, 7, 0, 9, 14, 0, 0, 0 },
                        { 0, 0, 0, 9, 0, 10, 0, 0, 0 },
                        { 0, 0, 4, 14, 10, 0, 2, 0, 0 },
                        { 0, 0, 0, 0, 0, 2, 0, 1, 6 },
                        { 8, 11, 0, 0, 0, 0, 1, 0, 7 },
                        { 0, 0, 2, 0, 0, 0, 6, 7, 0 } };

    dijkstra(graph, 0);
    return 0;
}

#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <utility>

using namespace std;

class Graph
{
private:

    int vertices;

    // Each vertex stores:
    // destination vertex + edge weight
    vector<vector<pair<int, int>>> adjacencyList;

public:

    Graph(int v);

    void addEdge(
        int u,
        int v,
        int weight
    );

    vector<int> bfs(
        int start,
        int destination
    );

    vector<int> dijkstra(
        int start,
        int destination
    );

    void displayGraph() const;
};

#endif
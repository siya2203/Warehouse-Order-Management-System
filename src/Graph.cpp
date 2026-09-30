#include "../include/Graph.h"

#include <iostream>
#include <queue>
#include <limits>
#include <algorithm>

using namespace std;


Graph::Graph(int v)
{
    vertices = v;

    adjacencyList.resize(vertices);
}


void Graph::addEdge(
    int u,
    int v,
    int weight
)
{
    if (
        u < 0 ||
        v < 0 ||
        u >= vertices ||
        v >= vertices
    )
    {
        return;
    }

    // Warehouse paths are bidirectional
    adjacencyList[u].push_back({v, weight});
    adjacencyList[v].push_back({u, weight});
}


vector<int> Graph::bfs(
    int start,
    int destination
)
{
    vector<bool> visited(vertices, false);

    vector<int> parent(vertices, -1);

    queue<int> q;

    q.push(start);

    visited[start] = true;


    while (!q.empty())
    {
        int current = q.front();

        q.pop();


        if (current == destination)
        {
            break;
        }


        for (auto edge : adjacencyList[current])
        {
            int next = edge.first;


            if (!visited[next])
            {
                visited[next] = true;

                parent[next] = current;

                q.push(next);
            }
        }
    }


    vector<int> path;


    if (!visited[destination])
    {
        return path;
    }


    int current = destination;


    while (current != -1)
    {
        path.push_back(current);

        current = parent[current];
    }


    reverse(path.begin(), path.end());


    return path;
}


vector<int> Graph::dijkstra(
    int start,
    int destination
)
{
    const int INF =
        numeric_limits<int>::max();


    vector<int> distance(
        vertices,
        INF
    );

    vector<int> parent(
        vertices,
        -1
    );


    priority_queue<
        pair<int, int>,
        vector<pair<int, int>>,
        greater<pair<int, int>>
    > pq;


    distance[start] = 0;

    pq.push({0, start});


    while (!pq.empty())
    {
        int currentDistance =
            pq.top().first;

        int current =
            pq.top().second;

        pq.pop();


        if (
            currentDistance >
            distance[current]
        )
        {
            continue;
        }


        for (auto edge :
             adjacencyList[current])
        {
            int next = edge.first;

            int weight = edge.second;


            if (
                distance[current] + weight
                < distance[next]
            )
            {
                distance[next] =
                    distance[current] + weight;

                parent[next] = current;


                pq.push({
                    distance[next],
                    next
                });
            }
        }
    }


    vector<int> path;


    if (distance[destination] == INF)
    {
        return path;
    }


    int current = destination;


    while (current != -1)
    {
        path.push_back(current);

        current = parent[current];
    }


    reverse(path.begin(), path.end());


    return path;
}


void Graph::displayGraph() const
{
    cout << "\n========== WAREHOUSE GRAPH ==========\n";


    for (int i = 0; i < vertices; i++)
    {
        cout << "Location "
             << i
             << " -> ";


        for (auto edge :
             adjacencyList[i])
        {
            cout << "("
                 << edge.first
                 << ", weight="
                 << edge.second
                 << ") ";
        }


        cout << endl;
    }


    cout << "======================================\n";
}
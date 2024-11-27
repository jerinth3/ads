#include <iostream>
#include <algorithm>

#define MAX_EDGES 100
#define MAX_NODES 100

using namespace std;

class Edge {
public:
    int u, v, weight;
};

class Graph {
private:
    Edge edges[MAX_EDGES];
    Edge mst[MAX_EDGES];
    int parent[MAX_NODES];
    int rank[MAX_NODES];
    int numEdges;
    int numNodes;

public:
    Graph(int nodes, int edges) : numNodes(nodes), numEdges(edges) {}

    void addEdge(int index, int u, int v, int weight) {
        edges[index] = {u, v, weight};
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]); // Path compression
        }
        return parent[x];
    }

    void unionSet(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX != rootY) {
            if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }

    bool compareEdges(Edge a, Edge b) {
        return a.weight < b.weight;
    }

    void kruskal() {
        for (int i = 0; i < numNodes; i++) {
            parent[i] = i;
            rank[i] = 0;
        }

        sort(edges, edges + numEdges, compareEdges);

        int mstEdges = 0, mstWeight = 0;

        for (int i = 0; i < numEdges && mstEdges < numNodes - 1; i++) {
            int u = edges[i].u;
            int v = edges[i].v;

            if (find(u) != find(v)) {
                mst[mstEdges++] = edges[i];
                mstWeight += edges[i].weight;
                unionSet(u, v);
            }
        }

        cout << "Edges in the MST:\n";
        for (int i = 0; i < mstEdges; i++) {
            cout << mst[i].u << " - " << mst[i].v << " : " << mst[i].weight << "\n";
        }
        cout << "Total weight of MST: " << mstWeight << "\n";
    }
};

int main() {
    int numNodes, numEdges;

    cout << "Enter the number of nodes: ";
    cin >> numNodes;

    cout << "Enter the number of edges: ";
    cin >> numEdges;

    Graph graph(numNodes, numEdges);

    cout << "Enter the edges (u v weight):\n";
    for (int i = 0; i < numEdges; i++) {
        int u, v, weight;
        cin >> u >> v >> weight;
        graph.addEdge(i, u, v, weight);
    }

    graph.kruskal();

    return 0;
}

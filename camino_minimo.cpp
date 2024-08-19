#include <iostream>
#include <vector>
#include <limits.h>

using namespace std;

class Graph {
    int V; // Número de vértices
    vector<vector<pair<int, int> > > adj; // Lista de adyacencia (nodo, peso)

public:
    Graph(int V) : V(V), adj(V) {}
    
    void addEdge(int u, int v, int weight) {
        adj[u].push_back(make_pair(v, weight));
    }
    
    void topologicalSort(int v, vector<bool> &visited, vector<int> &stack) {
        visited[v] = true;
        for (size_t i = 0; i < adj[v].size(); ++i) {
            int node = adj[v][i].first;
            if (!visited[node]) {
                topologicalSort(node, visited, stack);
            }
        }
        stack.push_back(v);
    }
    
    void shortestPath(int src) {
        vector<int> stack;
        vector<bool> visited(V, false);
        
        // Realizar ordenación topológica
        for (int i = 0; i < V; ++i) {
            if (!visited[i]) {
                topologicalSort(i, visited, stack);
            }
        }
        
        vector<int> dist(V, INT_MAX);
        dist[src] = 0;
        
        // Procesar vértices en orden topológico
        while (!stack.empty()) {
            int u = stack.back();
            stack.pop_back();
            
            if (dist[u] != INT_MAX) {
                for (size_t i = 0; i < adj[u].size(); ++i) {
                    int v = adj[u][i].first;
                    int weight = adj[u][i].second;
                    if (dist[v] > dist[u] + weight) {
                        dist[v] = dist[u] + weight;
                    }
                }
            }
        }
        
        // Imprimir distancias
        for (int i = 0; i < V; ++i) {
            if (dist[i] == INT_MAX) {
                cout << "Distancia desde " << src << " a " << i << ": INFINITO" << endl;
            } else {
                cout << "Distancia desde " << src << " a " << i << ": " << dist[i] << endl;
            }
        }
    }
};

int main() {
    Graph g(6);
    g.addEdge(0, 1, 5);
    g.addEdge(0, 2, 3);
    g.addEdge(1, 3, 6);
    g.addEdge(1, 2, 2);
    g.addEdge(2, 4, 4);
    g.addEdge(2, 5, 2);
    g.addEdge(2, 3, 7);
    g.addEdge(3, 5, 1);
    g.addEdge(3, 4, -1);
    g.addEdge(4, 5, -2);
    
    int src = 1;
    cout << "Caminos más cortos desde el nodo " << src << ":" << endl;
    g.shortestPath(src);

    return 0;
}

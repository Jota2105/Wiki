#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

struct Node {
    int value;                 // Valor del objeto en el nodo
    vector<Node*> children;    // Hijos del nodo
};

// Mapa para almacenar el resultado de la DP para cada nodo
map<Node*, vector<int> > dp;

void dfs(Node* v) {
    dp[v][0] = 0;             // Caso en que no se incluye el nodo
    dp[v][1] = v->value;      // Caso en que se incluye el nodo

    for (size_t i = 0; i < v->children.size(); ++i) {
        Node* u = v->children[i];
        dfs(u);
        dp[v][0] += max(dp[u][0], dp[u][1]);  // Máximo valor sin incluir el nodo v
        dp[v][1] += dp[u][0];                 // Valor al incluir el nodo v (sin incluir a sus hijos)
    }
}

int knapsack_tree(Node* root) {
    dp[root][0] = 0;
    dp[root][1] = root->value;

    dfs(root);

    return max(dp[root][0], dp[root][1]);
}

int main() {
    // Ejemplo de creación de un árbol con 4 nodos
    Node* root = new Node;
    root->value = 10;  // Nodo raíz con valor 10
    Node* child1 = new Node;
    child1->value = 5; // Hijo 1 con valor 5
    Node* child2 = new Node;
    child2->value = 7; // Hijo 2 con valor 7
    Node* child3 = new Node;
    child3->value = 4; // Hijo 3 con valor 4

    root->children.push_back(child1);  // Añadir hijo1 a la raíz
    root->children.push_back(child2);  // Añadir hijo2 a la raíz
    child1->children.push_back(child3); // Añadir hijo3 a hijo1

    // Inicializar mapa DP
    dp[root] = vector<int>(2, 0);
    dp[child1] = vector<int>(2, 0);
    dp[child2] = vector<int>(2, 0);
    dp[child3] = vector<int>(2, 0);

    // Calcular el valor máximo
    int max_value = knapsack_tree(root);

    cout << "Valor máximo en la mochila: " << max_value << endl;

    // Liberar memoria
    delete root;
    delete child1;
    delete child2;
    delete child3;

    return 0;
}

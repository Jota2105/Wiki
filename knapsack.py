class Node:
    def __init__(self, value):
        self.value = value
        self.children = []

# Diccionario para almacenar los resultados de DP para cada nodo
dp = {}

def dfs(v):
    # Inicializar valores de DP para el nodo v
    dp[v] = [0, v.value]

    for u in v.children:
        dfs(u)
        # Máximo valor sin incluir el nodo v
        dp[v][0] += max(dp[u][0], dp[u][1])
        # Valor al incluir el nodo v (sin incluir a sus hijos)
        dp[v][1] += dp[u][0]

def knapsack_tree(root):
    dfs(root)
    # Retornar el máximo valor posible con o sin incluir la raíz
    return max(dp[root][0], dp[root][1])

# Ejemplo de creación de un árbol con 4 nodos
root = Node(10)  # Nodo raíz con valor 10
child1 = Node(5) # Hijo 1 con valor 5
child2 = Node(7) # Hijo 2 con valor 7
child3 = Node(4) # Hijo 3 con valor 4

root.children.append(child1)  # Añadir hijo1 a la raíz
root.children.append(child2)  # Añadir hijo2 a la raíz
child1.children.append(child3) # Añadir hijo3 a hijo1

# Calcular el valor máximo
max_value = knapsack_tree(root)

print("Valor máximo en la mochila:", max_value)

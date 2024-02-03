def tsp_bfs(graph, start):
    stack = [(start, [start])]

    min_cost = float('inf')

    while stack:
        current_node, current_path = stack.pop()

        if len(current_path) == len(graph):
            current_cost = sum(graph[current_path[i]][current_path[i + 1]] for i in range(len(current_path) - 1))
            current_cost += graph[current_path[-1]][current_path[0]]  

            min_cost = min(min_cost, current_cost)
        else:
            for neighbor, cost in graph[current_node].items():
                if neighbor not in current_path:
                    stack.append((neighbor, current_path + [neighbor]))

    return min_cost

graph = {
    'A': {'B': 2, 'C': 3, 'D': 1},
    'B': {'A': 2, 'C': 4, 'D': 2},
    'C': {'A': 3, 'B': 4, 'D': 3},
    'D': {'A': 1, 'B': 2, 'C': 3}
}

start_node = 'A'
min_cost = tsp_bfs(graph, start_node)
print("Minimum cost for TSP starting from node", start_node, ":", min_cost)

def bfs_topological_sort(graph):
    in_degree = {node: 0 for node in graph}
    
    for node in graph:
        for neighbor in graph[node]:
            in_degree[neighbor] += 1

    queue = [node for node in in_degree if in_degree[node] == 0]
    
    result = []

    while queue:
        current_node = queue.pop(0)
        result.append(current_node)

        for neighbor in graph[current_node]:
            in_degree[neighbor] -= 1
            if in_degree[neighbor] == 0:
                queue.append(neighbor)

    if len(result) != len(graph):
        raise ValueError("Graph has a cycle!")

    return result


sample_graph = {
    0 : [],
    1: [],
    2: [3],
    3: [1],
    4: [0,1],
    5: [0,2],
}

topological_order = bfs_topological_sort(sample_graph)
print("Topological Order:", topological_order)

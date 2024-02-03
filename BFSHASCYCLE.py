def has_cycle(graph, start):
    visited = set()
    traversal_set = set()
    queue = [start]

    while queue:
        current_node = queue.pop(0)

        if current_node in traversal_set:
            return True

        traversal_set.add(current_node)

        queue.extend(neighbor for neighbor in graph.get(current_node, []) if neighbor not in visited)

        visited.add(current_node)

    return False

sample_graph = {
    0: [1, 2],
    1: [2],
    2: [3],
    3: [3],
}

start_node = 2

has_cycle_result = has_cycle(sample_graph, start_node)
print("Does the graph have a cycle starting from node", start_node, ":", has_cycle_result)

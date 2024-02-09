graph = {
    'D': {'B': 17},
    'B': {'D': 15},
    'H': {'B': 40, 'D': 53, 'T': 31},
    'F': {'B': 46, 'M': 11},
    'M': {'T': 8},
    'T': {'F': 3, 'C': 29},
    'C': {'M': 40, 'H': 17},
}

def ucs(graph, start, goal):
    frontier = [(0, start)]  
    visited = set()  
    came_from = {} 
    cost_so_far = {start: 0} 

    while frontier:
        priority, current = min(frontier)
        frontier.remove((priority, current))
        visited.add(current)

        if current == goal:
            break

        for next_node, cost in graph[current].items():
            new_cost = cost_so_far[current] + cost
            if next_node not in cost_so_far or new_cost < cost_so_far[next_node]:
                cost_so_far[next_node] = new_cost
                came_from[next_node] = current
                if next_node not in visited:
                    frontier.append((new_cost, next_node))

    path = []
    current = goal
    while current != start:
        path.append(current)
        current = came_from[current]
    path.append(start)
    path.reverse()

    return path

start_node = 'M'
goal_node = 'D'
shortest_path = ucs(graph, start_node, goal_node)
print("Shortest path from", start_node, "to", goal_node, ":", shortest_path)

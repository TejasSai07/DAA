graph = {
    's': {'a': 1, 'b': 4},
    'a': {'s': 1, 'b': 2, 'c': 5},
    'b': {'s': 4, 'a': 2, 'c': 2, 'd': 3},
    'c': {'a': 5, 'b': 2, 'd': 1, 'g': 3},
    'd': {'b': 3, 'c': 1, 'g': 4},
    'g': {'c': 3, 'd': 4}
}

def ucs(graph, start, goal):
    frontier = [(0, start)]  
    came_from = {}  
    cost_so_far = {start: 0}  

    while frontier:
        priority, current = min(frontier) 
        frontier.remove((priority, current))

        if current == goal:
            break

        for next_node, cost in graph[current].items():
            new_cost = cost_so_far[current] + cost
            if next_node not in cost_so_far or new_cost < cost_so_far[next_node]:
                cost_so_far[next_node] = new_cost
                came_from[next_node] = current
                frontier.append((new_cost, next_node))

    path = []
    current = goal
    while current != start:
        path.append(current)
        current = came_from[current]
    path.append(start)
    path.reverse()

    return path

start_node = 's'
goal_node = 'g'
best_path = ucs(graph, start_node, goal_node)
print("Best path from", start_node, "to", goal_node, ":", best_path)

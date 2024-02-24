def astar(graph, start, goals, heuristic):
    shortest_path = None
    min_cost = float('inf')

    for goal in goals:
        frontier = [(0, start)]
        came_from = {}
        cost_so_far = {start: 0}

        while frontier:
            _, current = min(frontier)

            if current == goal:
                if cost_so_far[current] < min_cost:
                    min_cost = cost_so_far[current]
                    shortest_path = reconstruct_path(start, current, came_from)
                break

            frontier.remove((_, current))

            for next_node, cost in graph[current].items():
                new_cost = cost_so_far[current] + cost
                if next_node not in cost_so_far or new_cost < cost_so_far[next_node]:
                    cost_so_far[next_node] = new_cost
                    priority = new_cost + heuristic[next_node]
                    frontier.append((priority, next_node))
                    came_from[next_node] = current

    return shortest_path

def reconstruct_path(start, goal, came_from):
    path = []
    current = goal
    while current != start:
        path.append(current)
        current = came_from[current]
    path.append(start)
    path.reverse()
    return path

def parse_graph_input():
    graph = {}
    while True:
        edge = input("Enter an edge in the format 'node1 node2 cost', or type 'done' to finish: ").split()
        if edge[0] == 'done':
            break
        node1, node2, cost = edge
        cost = int(cost)
        if node1 not in graph:
            graph[node1] = {}
        if node2 not in graph:
            graph[node2] = {}
        graph[node1][node2] = cost
    return graph

def parse_coordinates_input(nodes):
    coordinates = {}
    for node in nodes:
        x, y = map(int, input(f"Enter coordinates for node {node} (format: x y): ").split())
        coordinates[node] = (x, y)
    return coordinates

def parse_heuristic_input(nodes):
    heuristic = {}
    for node in nodes:
        h_value = int(input(f"Enter heuristic value for node {node}: "))
        heuristic[node] = h_value
    return heuristic

graph = parse_graph_input()
nodes = set(node for edge in graph for node in edge)
coordinates = parse_coordinates_input(nodes)
start_node = input("Enter the start node: ")

goal_nodes = input("Enter goal nodes separated by space: ").split()
heuristic = parse_heuristic_input(nodes)  
shortest_path = astar(graph, start_node, goal_nodes, heuristic)
print("Shortest path from", start_node, "to one of the goal nodes:", shortest_path)

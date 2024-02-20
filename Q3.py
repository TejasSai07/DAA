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

user_graph = parse_graph_input()
start_node = input("Enter the start node: ")
goal_node = input("Enter the goal node: ")
shortest_path = ucs(user_graph, start_node, goal_node)
print("Shortest path from", start_node, "to", goal_node, ":", shortest_path)

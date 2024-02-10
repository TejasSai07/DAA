edge = input("Enter an edge (format: 'start_node to end_node (cost)', or type 'done' to finish): ").strip()
        if edge.lower() == 'done':
            break
        start, end_cost = edge.split(' to ')
        end, cost = end_cost.split(' (')
        cost = int(cost[:-1])
        if start not in graph:
            graph[start] = {end: cost}
        else:
            graph[start][end] = cost
        if end not in graph:
            graph[end] = {}
    return graph

def calculate_heuristic(state, goal_state):
    """
    Calculate the heuristic value (Manhattan distance) for the given state.
    """
    heuristic = 0
    for i in range(3):
        for j in range(3):
            if state[i][j] != goal_state[i][j]:
                value = state[i][j]
                x_goal, y_goal = find_value_position(goal_state, value)
                heuristic += abs(i - x_goal) + abs(j - y_goal)
    return heuristic

def find_value_position(state, value):
    """
    Find the position (row, column) of a value in the given state.
    """
    for i in range(3):
        for j in range(3):
            if state[i][j] == value:
                return i, j

def get_possible_moves(state):
    """
    Get possible moves (up, down, left, right) for the empty tile.
    """
    moves = []
    x_empty, y_empty = find_value_position(state, 0)  
    if x_empty > 0:
        moves.append((x_empty - 1, y_empty))  # Move empty tile up
    if x_empty < 2:
        moves.append((x_empty + 1, y_empty))  # Move empty tile down
    if y_empty > 0:
        moves.append((x_empty, y_empty - 1))  # Move empty tile left
    if y_empty < 2:
        moves.append((x_empty, y_empty + 1))  # Move empty tile right
    return moves

def swap_tiles(state, pos1, pos2):
    """
    Swap tiles at positions pos1 and pos2 in the given state.
    """
    new_state = [row[:] for row in state]
    x1, y1 = pos1
    x2, y2 = pos2
    new_state[x1][y1], new_state[x2][y2] = new_state[x2][y2], new_state[x1][y1]
    return new_state

def astar_8_puzzle(initial_state, goal_state):
    """
    A* algorithm to solve the 8-puzzle problem.
    """
    visited_states = set()
    frontier = [(0 + calculate_heuristic(initial_state, goal_state), initial_state)]
    came_from = {}
    cost_so_far = {str(initial_state): 0}

    while frontier:
        _, current_state = min(frontier)
        frontier.remove((_, current_state))
        visited_states.add(str(current_state))

        if current_state == goal_state:
            break

        for next_move in get_possible_moves(current_state):
            new_state = swap_tiles(current_state, find_value_position(current_state, 0), next_move)
            if str(new_state) not in visited_states:
                new_cost = cost_so_far[str(current_state)] + 1
                if str(new_state) not in cost_so_far or new_cost < cost_so_far[str(new_state)]:
                    cost_so_far[str(new_state)] = new_cost
                    priority = new_cost + calculate_heuristic(new_state, goal_state)
                    frontier.append((priority, new_state))
                    came_from[str(new_state)] = current_state

    path = []
    current = goal_state
    while str(current) != str(initial_state):
        path.append(current)
        current = came_from[str(current)]
    path.append(initial_state)
    path.reverse()

    return path

def print_state(state):
    """
    Print the given state in a readable format.
    """
    for row in state:
        print(row)

initial_state = [[1, 2, 3], [0, 4, 5], [6, 7, 8]]
goal_state = [[1, 2, 3], [4, 5, 6], [7, 8, 0]]

print("Initial State:")
print_state(initial_state)
print("\nGoal State:")
print_state(goal_state)

path = astar_8_puzzle(initial_state, goal_state)
print("\nShortest path:")
for i, state in enumerate(path):
    print(f"\nStep {i+1}:")
    print_state(state)

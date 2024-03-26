def value(equation, x):
    ans = 0
    for i in equation.keys():
        ans += equation[i] * (x ** i)
    return ans

def hill_climbing(equation, source, l_range, h_range, max_iterations=1000, tolerance=1e-6):
    iterations = 0
    while iterations < max_iterations:
        if l_range < source < h_range:
            adList = [source - 1, source + 1]
        elif l_range == source:
            adList = [source + 1]
        else:
            adList = [source - 1]
        flag = True
        for i in adList:
            if value(equation, i) > value(equation, source):
                source = i
                flag = False
                break
        if flag:
            print(f'Maximum value = {value(equation, source)} at x = {source}')
            return
        iterations += 1
    print("Maximum iterations reached without convergence.")

if __name__ == '__main__':
    deg = int(input('Enter degree of equation: '))
    eq = {i: 0 for i in range(deg + 1)}
    for i in range(deg + 1):
        coeff = float(input(f'Enter coefficient of x^{i}: '))
        eq[i] = coeff
    src = float(input('Enter source: '))
    l = float(input('Enter lower range: '))
    h = float(input('Enter higher range: '))
    hill_climbing(eq, src, l, h)




---------------
import random

def generate_board():
    return [random.randint(0, 7) for _ in range(8)]  

def cost(board):
    attacking_pairs = 0
    for i in range(len(board)):
        for j in range(i + 1, len(board)):
            if board[i] == board[j] or abs(i - j) == abs(board[i] - board[j]):
                attacking_pairs += 1
    return attacking_pairs

def hill_climbing():
    current_board = generate_board()  
    current_cost = cost(current_board)  

    while current_cost > 0:  
        next_board = list(current_board)  
        min_cost = current_cost  
        
        for col in range(8):
            for row in range(8):
                if row != current_board[col]:  
                    next_board[col] = row  
                    new_cost = cost(next_board) 
                    if new_cost < min_cost:  
                        min_cost = new_cost  
                        current_board = list(next_board)  
        
        if min_cost >= current_cost:  
            break  
        
        current_cost = min_cost  
    
    return current_board

def print_board(board):
    for row in range(8):
        line = ""
        for col in range(8):
            if board[col] == row:
                line += "Q "
            else:
                line += ". "
        print(line)
    print()

if __name__ == "__main__":
    solution = hill_climbing()  
    print("Solution:")
    print_board(solution)  


---------------------------



def genlist(mat):
    adList = []
    for i in range(8):
        node = [[0, 0, 0, 0, 0, 0, 0, 0] for x in range(8)]
        for x in range(7):
            for y in range(8):
                if mat[x][i] == 1:
                    node[x + 1][i] = 1
                else:
                    node[x][y] = mat[x][y]
        adList.append(node)
    return adList


def test(mat):
    count = 0
    for i in range(8):
        row = mat[i]
        for x in row:
            if x == 1:
                count += 1
        if count > 1:
            return False
        count = 0

    for i in range(8):
        for j in range(8):
            if mat[j][i] == 1:
                count += 1
        if count > 1:
            return False
        count = 0
    for i in range(8):
        for j in range(8):
            if mat[i][j] == 1:
                for x, y in zip(range(i, -1, -1), range(j, -1, -1)):
                    if mat[x][y] == 1:
                        return False
    return True


def bfs():
    count = 0
    node = [[0, 0, 0, 0, 0, 0, 0, 0] for x in range(8)]
    for i in range(8):
        node[0][i] = 1
    queue = [node]
    while queue:
        queue = queue[::-1]
        curr = queue.pop()
        queue = queue[::-1]
        if test(curr):
            count += 1
        adList = genlist(curr)
        for x in adList:
            queue.append(x)
    print(count)


if __name__ == '__main__':
    bfs()

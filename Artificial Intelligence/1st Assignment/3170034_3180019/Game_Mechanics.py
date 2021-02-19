from util import*

def onBoard(x, y): #Returns true if coordinates are on board
    return x >= 0 and x <= 7 and y >= 0 and y <=7

def isValidMove(board, x, y, currentPlayer): #Returns false if move is NOT valid or an array with the tiles to be flipped if move is VALID

    if board[x][y] != 0:  #filled spot
        return False

    if currentPlayer == 1:
        enemy = -1
    else:
        enemy = 1

    board[x][y] = currentPlayer

    tilesToCapture = []
    for dx, dy in [[0, 1], [1, 1], [1, 0], [1, -1], [0, -1], [-1, -1], [-1, 0], [-1, 1]]:
        new_x = x
        new_y = y

        new_x += dx
        new_y += dy

        if onBoard(new_x, new_y) and board[new_x][new_y] == enemy:
            new_x += dx
            new_y += dy

        if not onBoard(new_x, new_y):
            continue

        while board[new_x][new_y] == enemy:
            new_x += dx
            new_y += dy
            if not onBoard(new_x, new_y):
                break
        if not onBoard(new_x, new_y):
            continue

        if board[new_x][new_y] == currentPlayer:

            while True:
                new_x -= dx
                new_y -= dy
                if new_x == x and new_y == y:
                    break
                tilesToCapture.append([new_x, new_y])

    board[x][y] = 0

    if len(tilesToCapture) == 0:
            return False
    return tilesToCapture

def getValidMoves(board, currentPlayer): #Returns list of available moves for the current player
    validMoves = []
    for x in range(8):
        for y in range(8):
            if isValidMove(board, x, y, currentPlayer) != False:
                validMoves.append([x, y])
    return validMoves

def move(board, x, y, currentPlayer, con=True): #Lets player make a move
    tilesToCapture = isValidMove(board, x, y, currentPlayer)

    if tilesToCapture == False: #no tiles flipped
        return False

    board[x][y] = currentPlayer

    for fx, fy in tilesToCapture:
        board[fx][fy] = currentPlayer

    if con == False: #if con==False move returns the new version of the board
        return board
    else: #else it returns true
        return True

def over(board): #Returns True if game is over
    return (getValidMoves(board, 1) == []) and (getValidMoves(board, -1) == [])

def noMove(game): #Returns True if there are no available moves for the player
    return (game.currentPlayer == -1 and (getValidMoves(game.board, -1) == [])) or (game.currentPlayer == 1 and (getValidMoves(game.board, 1) == []))

# # # END OF GAME UI # # #
def endgame(game): #End of Game
    clearScreen()
    width = get_terminal_width()
    line = ("-")*width

    print("FINAL SCORE:\n" + ("X: " + str(game.xscore) + " O: " + str(game.oscore)).center(width))

    print("\n"+ line)

    if game.xscore == game.oscore:
        print(("TIE").center(width))
    else:
        if game.xscore > game.oscore:
            winner = "X"
        else:
            winner = "O"
        print("\n" + (winner + " WINS!").center(width))

    print("\n" + line + "\n")

    beep(True)
    input(("PRESS <ENTER> TO EXIT GAME").center(width))
    clearScreen()
    exit()

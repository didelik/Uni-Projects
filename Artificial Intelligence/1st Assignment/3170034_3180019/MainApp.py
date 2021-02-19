from UI import *

def debug(g, op): # Starts the game in a specific way

    if op: # 3 moves before the end of game
        g.board[2][0] = 1
        g.board[0][2] = 1
        g.board[2][1] = 1
        g.board[2][2] = 1
        g.board[2][3] = 1
        g.board[2][4] = 1
        g.board[2][5] = 1
        g.board[2][6] = 1
        g.board[3][2] = 1
        g.board[3][3] = 1
        g.board[3][4] = 1
        g.board[3][5] = 1
        g.board[4][2] = 1
        g.board[4][3] = 1
        g.board[4][4] = 1
        g.board[0][4] = 1
        g.board[0][4] = 1
        g.board[1][4] = 1
        g.board[1][5] = 1
        g.board[2][7] = -1
        g.board[3][7] = -1
        g.board[4][7] = -1
        g.board[4][1] = -1
        g.board[0][5] = -1

    else: # No moves available for X
        g.board[3][3] = 1
        g.board[4][4] = 0
        g.board[4][3] = 0
        g.board[3][4] = 0
        g.board[2][0] = -1
        g.board[2][1] = 1
        g.board[6][6] = 1


def setUpGame(): # Sets up game
    beep(True)

    data = [0] * 2
    menu(data)

    difficulty = int(data[0])

    if int(data[1])==1:
        player = "X"
    else:
        player = "O"

    print("STARTING GAME WITH:\n   DIFFICULTY: "+ str(difficulty) +"\n   TILE: " + str(player) + "\nLOADING...")
    sleep(2)

    if int(data[1])==1:
        game = Game(False, difficulty)
    else:
        game = Game(True, difficulty)

    beep(True)
    return game

def main():
    game = setUpGame()
    #debug(game, True) #Debug mode

    gui(game)

    while(over(game.board)==False):
        if noMove(game):
            print("NO MOVE AVAILABLE, CONTINUING")
            sleep(1)

            game.changePlayer()
            gui(game, "no move")
            continue

        move = game.getMove() #move()
        gui(game, move) #gui

    endgame(game) #End of Game

if __name__ == "__main__":
    main()

from Game_Mechanics import *
import math
import copy


def static_eval(board): # Returns static evaluation
    val = 0
    for row in board:
        for pos in row:
            val += pos
    return val

def minimax(board, depth, alpha, beta, currentPlayer, difficulty):
    if (depth == 0) or (over(board)):
        return static_eval(board)

    if currentPlayer==1:
        maxEval = -math.inf

        moves = getValidMoves(board, 1)
        children = []

        for i in range(len(moves)):
            tmp_board = copy.deepcopy(board)
            eval = minimax(move(tmp_board, moves[i][0], moves[i][1], 1, False), depth-1, alpha, beta, -1, difficulty)

            alpha = max(alpha, eval)

            if eval >= maxEval:
                maxEval = eval
                bestMove = moves[i]

            if beta <= alpha:
                break

        if depth==difficulty:
            return bestMove
        else:
            return maxEval

    else:
        minEval = math.inf

        moves = getValidMoves(board, -1)
        children = []

        for i in range(len(moves)):
            tmp_board = copy.deepcopy(board)
            eval = minimax(move(tmp_board, moves[i][0], moves[i][1], -1, False), depth-1, alpha, beta, 1, difficulty)

            beta = min(beta,eval)

            if eval <= minEval:
                minEval = eval
                bestMove = moves[i]

            if beta <= alpha:
                break

        if depth==difficulty:
            return bestMove
        else:
            return minEval

from Minimax import *

class Game:

    def __init__(self, isX, difficulty):
        self.setup()
        self.isX = isX
        self.currentPlayer = 1
        self.difficulty = difficulty

        self.xscore = 2
        self.oscore = 2

        self.column_dict = {"a": 1,"b": 2,"c" : 3, "d" : 4 , "e" : 5 , "f" : 6, "g" : 7, "h" : 8}

    def setup(self):
        self.board = [[0]*8 for i in range(8)]

        #X
        self.board[3][3] = 1
        self.board[4][4] = 1

        #0
        self.board[4][3] = -1
        self.board[3][4] = -1

    def changePlayer(self):
        if self.currentPlayer == 1:
            self.currentPlayer = -1
        else:
            self.currentPlayer = 1

    def getScore(self):
        self.xscore = sum([i.count(1) for i in self.board])
        self.oscore = sum([i.count(-1) for i in self.board])

    def getMove(self): #Get input from user or ai
        if (self.currentPlayer == 1 and self.isX) or (self.currentPlayer == -1 and self.isX==False): #ai
            self.taunt()

            [x,y] = minimax(self.board, self.difficulty, -math.inf, math.inf, self.currentPlayer, self.difficulty)

            inp = str(list(self.column_dict.keys())[y]) + str(x+1)

            move(self.board, x, y, self.currentPlayer)

        else: #player
            inp = input(">> ")
            beep(False)

            if (len(re.findall("^([a-h][1-8])|[Q]$", inp)) != 1): # Checks user input
                while True:
                    print("INVALID INPUT")
                    inp = input(">> ")
                    beep(False)

                    if (len(re.findall("^([a-h][1-8])|[Q]$", inp)) == 1):
                        break

            if inp=="Q": #Forfeit the game
                cert= input("ARE YOU SURE YOU WANT TO FORFEIT THE GAME? (Y/N) ")
                beep(False)
                if (len(cert)!=1) or (cert!="Y" and cert!="N"):
                    while True:
                        print("INVALID INPUT")
                        cert = input(">> ")
                        beep(False)

                        if (len(cert)==1) and (cert=="Y" or cert=="N"):
                            break

                if cert=="Y": #Sets final score and forfeits Game
                    if self.currentPlayer==1 and self.isX==False:
                        self.oscore = max(64 - self.xscore, self.xscore+1)
                    elif self.currentPlayer==-1 and self.isX==True:
                        self.xscore = max(64 - self.oscore, self.oscore+1)

                    endgame(self)
                else:
                    return self.getMove()

            x = int(inp[1]) - 1
            y = int(self.column_dict[inp[0]]) - 1

            if [x,y] in getValidMoves(self.board, self.currentPlayer):
                move(self.board, x, y, self.currentPlayer)
            else:
                print("INVALID MOVE")
                self.getMove()

        self.getScore()
        self.changePlayer()
        return inp

    def taunt(self):

        if self.difficulty <= 2:
            dmessage = "Go Home, you're drunk..."
            vmessage = "Why don't you raise the difficulty..."
        elif self.difficulty > 2 and self.difficulty <= 5:
            dmessage = "You need some more practice..."
            vmessage = "You're better than I thought..."
        elif  self.difficulty > 5 and self.difficulty <= 7:
            dmessage = "Can't tell if you're too bad or I'm just too good..."
            vmessage = "Hmm..."
        else:
            dmessage = "You are a mortal after all..."
            vmessage = "Get a life..."

        if (self.isX and (self.xscore-self.oscore>=5)) or (self.isX==False and (self.oscore-self.xscore>=5)):
            print(dmessage)

        elif (self.isX==False and (self.xscore-self.oscore>5)) or (self.isX and (self.oscore-self.xscore>5)):
            print(vmessage)

        else:
            print("LOADING...")

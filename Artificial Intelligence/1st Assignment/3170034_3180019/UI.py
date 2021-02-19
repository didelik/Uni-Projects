from Game import *

# # # GAME UI # # #

def printBoard(game): #Prints Board
    width = get_terminal_width()

    CL = " a       b       c       d       e       f       g       h".center(width) + "\n"
    up_line = (" " + ("_"*8)*8 + "_").center(width) + "\n" + (" "+("|" + " "*7)*8+"|").center(width) + "\n"
    down_line = (" "+ ("\u203e"*8)*8 + "\u203e").center(width) + "\n"
    out = CL + up_line
    RC = 1

    for row in game.board:
        r = " " + str(RC) + "  |"
        for pos in row:
            if pos==0:
                r += "   _   |" #EMPTY
            elif pos==1:
                r += "   X   |" #X
            elif pos==-1:
                r += "   O   |" #O
        r += "  " + str(RC)
        out += r.center(width) + "\n"
        if RC<8:
            out+= (" "+("|" + " "*7)*8+"|").center(width) + "\n" + (" "+("|" + "-"*7)*8+"|").center(width) + (" "+("|" + " "*7)*8 + "|").center(width) + "\n"
        else:
            out+= (" "+("|" + " "*7)*8 + "|").center(width) + "\n"
        RC+=1

    out += down_line + CL
    print(out)

def playerTurnInfo(game, move, width):
    if game.currentPlayer == -1:
        prev = "X"
        next = "O"
    else:
        prev = "O"
        next = "X"

    if move != 0:
        print((prev + " played " + move).center(width))
    else:
        print()
    print((next + " plays now").center(width))

def scoreboard(game, width):
    game.xscore = sum([i.count(1) for i in game.board])
    game.oscore = sum([i.count(-1) for i in game.board])

    print("SCORE:\n" + ("X: " + str(game.xscore) + " O: " + str(game.oscore)).center(width))

def prompt(game, width):
    if (game.currentPlayer == 1 and game.isX) or (game.currentPlayer == -1 and game.isX==False):
        print(("WAITING FOR OPPONENT").center(width))
    else:
        print(("MAKE A MOVE BY ENTERING THE CORRESPONDING LETTER AND NUMBER (EX. "+ random.choice(["a", "b", "c", "d", "e", "f", "g", "h"]) + random.choice(["1", "2", "3", "4", "5", "6", "7", "8"]) +") AND PRESSING <ENTER> (OR FORFEIT THE GAME BY ENTERING 'Q')").center(width))

def gui(game, move=0): #Displays GAME UI
    clearScreen()
    width = get_terminal_width()
    line = ("-")*width

    scoreboard(game, width)

    print(line + "\n")

    printLogo(width)
    print("\n")
    printBoard(game)
    print("\n")

    print(line)

    playerTurnInfo(game, move, width)

    print(line)

    prompt(game, width)

# # # MENU UI # # #

def printLogo(width): #Displays Logo
    rl1 = "dY0Y00Y0Yb."
    rl2 = "Y00Y    Y00b."
    rl3 = "Y00Y     Y00b."
    rl4 = "Y00Y    Y00P."
    rl5 = "Y00Y000Y00b"
    rl6 = "Y00Y    Y00b."
    rl7 = "Y00Y      Y00b."
    rl8 = "T00T       Y00b."


    el1 = "d00Y00Y00Yb"
    el2 = "Y00Y00Y00Yb"
    el3 = "Y00I"
    el4 = "Y00Y00Yb"
    el5 = "Y00Y00YP"
    el6 = "Y00I"
    el7 = "Y00Y00Y00Yb"
    el8 = "T00Y00Y00YP"


    vl1 = "TY00YP         TY00YP"
    vl2 = " Y00b.         .d00Y"
    vl3 = "  Y00b.       .d00Y"
    vl4 = "   Y00b.     .d00Y"
    vl5 = "    Y00b.   .d00Y"
    vl6 = "     Y00b. .d00Y"
    vl7 = "      Y00Y0Y00Y"
    vl8 = "       'T0Y0T'"


    sl1 = "  .d00000b."
    sl2 = " d00P   Y00b"
    sl3 = " Y00b."
    sl4 = "  'Y00b."
    sl5 = "    'Y00b."
    sl6 = "      'Y00b."
    sl7 = " Y00b. d00P"
    sl8 = "  'Y0000P'"


    il1 = "dY00Yb"
    il2 = " Y00Y"
    il3 = " Y00Y"
    il4 = " Y00Y"
    il5 = " Y00Y"
    il6 = " Y00Y"
    il7 = " Y00Y"
    il8 = "TY00YT"


    l1 = rl1 + " "*9 + el1 + " "*4 + vl1 + " "*4 + el1 + " "*4 + rl1 + " "*8 + sl1 + " "*5 + il1
    l2 = rl2 + " "*7 + el2 + " "*4 + vl2 + " "*5 + el2 + " "*4 + rl2 + " "*6 + sl2 + " "*4 + il2
    l3 = rl3 + " "*6 + el3 + " "*11 + vl3 + " "*6 + el3 + " "*11 + rl3 + " "*5 + sl3 + " "*10 + il3
    l4 = rl4 + " "*7 + el4 + " "*7 + vl4 + " "*7 + el4 + " "*7 + rl4 + " "*7 + sl4 + " "*7 + il4
    l5 = rl5 + " "*9 + el5 + " "*7 + vl5 + " "*8 + el5 + " "*7 + rl5 + " "*8 + sl5 + " "*6 + il5
    l6 = rl6 + " "*7 + el6 + " "*11 + vl6 + " "*9 + el6 + " "*11 + rl6 + " "*6 + sl6 + " "*4 + il6
    l7 = rl7 + " "*5 + el7 + " "*4 + vl7 + " "*10 + el7 + " "*4 + rl7 + " "*4 + sl7 + " "*5 + il7
    l8 = rl8 + " "*4 + el8 + " "*4 + vl8 + " "*11 + el8 + " "*4 + rl8 + " "*3 + sl8 + " "*6 + il8

    logo = l1.center(width) + "\n" + l2.center(width) + "\n" + l3.center(width) + "\n" + l4.center(width) + "\n" + l5.center(width) + "\n" + l6.center(width) + "\n" + l7.center(width) + "\n" + l8.center(width) + "\n"

    print("\n"+logo)

def printHeader(width, opt): #Displays Header
    if opt==0: #Start Menu
        print("\n" + ("REVERSI - MAIN MENU").center(width) + "\n")

    elif opt==1: #DIFFICULTY Menu
        print("\n" + ("REVERSI - GAME DIFFICULTY").center(width) + "\n")

    elif opt==2: #TILE Picker Menu
        print("\n" + ("REVERSI - PICK TILE").center(width) + "\n")

def printBody(width, opt): #Displays Body
    printLogo(width)

    if opt==0:
        print("\n"+("YOU MUST CHOOSE...").center(width)+"\n")
    elif opt==1:
        print("\n"+("BUT CHOOSE WISELY...").center(width)+"\n")
    elif opt==2:
        print("\n"+("X ALWAYS PLAYS FIRST...").center(width)+"\n")

def printFooter(width, opt): #Displays Menu Footer
    if opt==0: #Start Menu
        print("\n" + ("1. START GAME").center(width) + "\n" + ("2. EXIT      ").center(width) + "\n")

    elif opt==1: #Difficulty Menu
        print("\n" + ("1 - 2 : EASY     ").center(width) + "\n" + ("3 - 5 : MEDIUM   ").center(width) + "\n" + ("6 - 7 : HARD     ").center(width) + "\n" + ("   8 : NIGHTMARE").center(width) + "\n")

    elif opt==2: #TILE Picker Menu
        print("\n" + ("1. PLAY AS X").center(width) + "\n" + ("2. PLAY AS O").center(width) + "\n")

def printPromptMessage(width, opt): #Displays Prompt
    print(("PICK AN OPTION BY ENTERING THE CORRESPONDING NUMBER AND PRESSING <ENTER>").center(width))

def getInput(opt, data): #Get User Input
    inp = input(">> ")

    ###
    beep(False)
    ###

    if opt==0: #Start Menu
        if len(re.findall("^[1-2]$", inp)) != 1:
            while True:
                print("INVALID INPUT")
                inp = input(">> ")
                beep(False)

                if len(re.findall("^[1-2]$", inp)) == 1:
                    break



        if inp=="1":
            menu(data, 1)
        elif inp=="2":
            print("EXITING...")
            beep(True)

            exit()

    elif opt==1: #Game Difficulty Menu
        if len(re.findall("^[1-8]$", inp)) != 1:
            while True:
                print("INVALID INPUT")
                inp = input(">> ")
                beep(False)

                if len(re.findall("^[1-9]$", inp)) == 1:
                    break

        data[0] = inp
        menu(data, 2)

    elif opt==2: #TILE Picker Menu
        if len(re.findall("^[1-2]$", inp)) != 1:
            while True:
                print("INVALID INPUT")
                inp = input(">> ")
                ###
                beep(False)
                ###

                if len(re.findall("^[1-2]$", inp)) == 1:
                    break

        data[1] = inp
        return 0

def menu(data, opt=0): #Displays Menu
    clearScreen()
    width = get_terminal_width()
    line = ("-")*width

    printHeader(width, opt)

    print(line)

    printBody(width, opt)

    print(line)

    printFooter(width, opt)

    print(line)

    printPromptMessage(width, opt)

    getInput(opt, data)

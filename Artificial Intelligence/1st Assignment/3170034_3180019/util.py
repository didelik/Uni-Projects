from os import system, name
import shutil
import winsound
import re
import random
from time import sleep
import math
import copy

def clearScreen(): # Clears screen
    #WINDOWS
    if name == 'nt':
        _ = system('cls')

    #MAC / LINUX
    else:
        _ = system('clear')

def get_terminal_width(): # Gets terminal width
    return shutil.get_terminal_size().columns

def beep(op): # Plays beep, only works on WINDOWS
    if name == 'nt':
        if op:
            winsound.Beep(880, 100)
            winsound.Beep(220, 100)
        else:
            winsound.Beep(220, 100)

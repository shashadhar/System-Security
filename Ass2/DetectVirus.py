import __main__
import base64
import sys
from io import StringIO ## for Python 3
from Crypto import Random
from Crypto.Cipher import AES
import io
import os

def is_infected(filename):
    f = open(filename, 'r')
    lines = f.readlines()
    return lines[len(lines - 1)].startswith("# ####### Magic Works Done by Shashadhar Das!")

# Gets the target
def check_target():
    path = '.'
    dirs = os.listdir(path)

    # For each file try to infect it
    for filename in dirs:
        if filename.endswith('.py') and (is_infected(filename)):
            print("Virus detected" + str(filename))


check_target()
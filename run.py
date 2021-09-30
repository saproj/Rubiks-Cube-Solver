#!/usr/bin/env python
import sys
import subprocess
from cube_convert import cube_string

def Run(Pos, DepthLimit):
    r = cube_string(Pos)
    return subprocess.run(["./solver", r, str(DepthLimit)])

#Run(sys.argv[1])
#exit()

SwitchCubies = [
    [1,18],
    [3,9],
    [4,15],
    [6,12],
    [20,27],
    [22,21],
    [24,23],
    [26,25]
]

MinDepth = 100

def Swap(str, i, j):
    str = list(str)
    str[i], str[j] = str[j], str[i]
    return ''.join(str)

for i in range(256):
    Swaps = 0
    Pos = "rryrrbrrbbwrwwggrgyybbwwggyybbbwwwgggyyyoooooooo"
    for bit in range(8):
        if (1 << bit) & i:
            Swaps += 1
            Pos = Swap(Pos, SwitchCubies[bit][0], SwitchCubies[bit][1])
    if Swaps % 2 == 0:
        print(Pos, "swaps", Swaps, "Min depth", MinDepth, flush = True)
        Status = Run(Pos, MinDepth)
        if Status.returncode < MinDepth:
            MinDepth = Status.returncode

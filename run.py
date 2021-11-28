#!/usr/bin/env python
import sys
import subprocess
from cube_convert import cube_string
import itertools
import time

def Run(Pos, DepthLimit):
    r = cube_string(Pos)
    return subprocess.run(["./solver", r, str(DepthLimit)])

#Run(sys.argv[1], 20)
#exit()

'''
                  1   2   3

                  4   R   5

                  6   7   8

     9  10  11   12  13  14   15  16  17    18  19  20

    21   B  22   23   W  24   25   G  26    27   Y  28

    29  30  31   32  33  34   35  36  37    38  39  40

                 41  42  43

                 44   O  45

                 46  47  48

rrrrrrrrbbbwwwgggyyybbwwggyybbbwwwgggyyyoooooooo
'''

Edges = [
    [12,6],
#    [22,21],
    [23,24],
    [32,41],

#    [3,9],
#    [4,15],
#    [43,29],
#    [44,35],

    [1,18],
    [20,27],
    [38,46],
#    [25,26]
]

def Swap(str, i, j):
    str = list(str)
    str[i], str[j] = str[j], str[i]
    return ''.join(str)

Pos = "rrrrrrrrbbbwwwgggyyybbwwggyybbbwwwgggyyyoooooooo"

for e in Edges:
    Pos = Swap(Pos, e[0], e[1])

print(Pos)
Run(Pos, 20)

'''
MinDepth = 12
#                  rrrrrrrrbbbwwwgggyyybbwwggyybbbwwwgggyyyoooooooo
PosPermutations = "rorrrrorbwbwwwgbgyyybbwwggyybbbwgwgggyyyorooooro"
PermutationCubies = SwitchCubies

for mask in range(4096):
    print("Flip mask", mask)
    Pos = PosPermutations
    Swaps = 0;
    for bit in range(12):
        if mask & (1<<bit):
            Pos = Swap(Pos, SwitchCubies[bit][0], SwitchCubies[bit][1])
            Swaps += 1
    Status = Run(Pos, MinDepth)
    if Status.returncode <= MinDepth:
        print(Pos, "Swaps", Swaps, "depth", MinDepth, "\n", flush = True)
        MinDepth = Status.returncode - 0
        if MinDepth < 1: exit()
'''

'''
for p in itertools.permutations(PermutationCubies):
    Parity = 0
    for i in range(4):
        for j in range(i + 1, 4):
            if p[i][0] > p[j][0]:
                Parity += 1
    if Parity % 2 == 0: continue

    charaters = list(PosPermutations)
    for i:
        charaters[PermutationCubies[i][0]] = PosPermutations[p[i][0]]
        charaters[PermutationCubies[i][1]] = PosPermutations[p[i][1]]


    for i in range(4):
        charaters[PermutationCubies[i][0]] = PosPermutations[p[i][0]]
        charaters[PermutationCubies[i][1]] = PosPermutations[p[i][1]]

    PosCorners = "".join(charaters)
    print(p, PosCorners, time.ctime(), "\n", flush = True)

    for rot1 in range(3):
        for rot2 in range(3):
            for rot3 in range(3):
                for rot4 in range(3):
                    for i in range(256):
                        Swaps = 0
                        Pos = PosCorners
                        for bit in range(8):
                            if (1 << bit) & i:
                                Swaps += 1
                                Pos = Swap(Pos, SwitchCubies[bit][0], SwitchCubies[bit][1])
                        if Swaps % 2 == 0:
                            Status = Run(Pos, MinDepth)
                            if Status.returncode <= MinDepth:
                                print(Pos, "swaps", Swaps, "depth", MinDepth, "\n", flush = True)
                                MinDepth = Status.returncode - 0
                                if MinDepth < 1: exit()
                    Swap(PosCorners, 7, 13)
                    Swap(PosCorners, 13, 14)
                Swap(PosCorners, 5, 10)
                Swap(PosCorners, 10, 11)
            Swap(PosCorners, 2, 17)
            Swap(PosCorners, 17, 16)
        Swap(PosCorners, 0, 19)
        Swap(PosCorners, 19, 8)
'''

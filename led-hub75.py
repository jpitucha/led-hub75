from gpiozero import OutputDevice
from time import sleep

A = OutputDevice(4)
B = OutputDevice(17)
C = OutputDevice(27)
D = OutputDevice(22)
R1 = OutputDevice(0)
R2 = OutputDevice(5)
G1 = OutputDevice(6)
G2 = OutputDevice(19)
B1 = OutputDevice(26)
B2 = OutputDevice(21)
CLK = OutputDevice(20)
LATCH = OutputDevice(16)
OE = OutputDevice(12)

BLANK_DELAY_TIME_US = 5000

vramR = [bytearray(64), bytearray(64)]
vramG = [bytearray(64), bytearray(64)]
vramB = [bytearray(64), bytearray(64)]

currentRow = 1

def nextRow():
    global currentRow
    if (currentRow == 1):
        A.off()
        B.off()
        C.off()
        D.off()
        currentRow = 2
    elif (currentRow == 2):
        A.on()
        B.off()
        C.off()
        D.off()
        currentRow = 3
    elif (currentRow == 3):
        A.off()
        B.on()
        C.off()
        D.off()
        currentRow = 4
    elif (currentRow == 4):
        A.on()
        B.on()
        C.off()
        D.off()
        currentRow = 5
    elif (currentRow == 5):
        A.off()
        B.off()
        C.on()
        D.off()
        currentRow = 6
    elif (currentRow == 6):
        A.on()
        B.off()
        C.on()
        D.off()
        currentRow = 7
    elif (currentRow == 7):
        A.off()
        B.on()
        C.on()
        D.off()
        currentRow = 8
    elif (currentRow == 8):
        A.on()
        B.on()
        C.on()
        D.off()
        currentRow = 9
    elif (currentRow == 9):
        A.off()
        B.off()
        C.off()
        D.on()
        currentRow = 10
    elif (currentRow == 10):
        A.on()
        B.off()
        C.off()
        D.on()
        currentRow = 11
    elif (currentRow == 11):
        A.off()
        B.on()
        C.off()
        D.on()
        currentRow = 12
    elif (currentRow == 12):
        A.on()
        B.on()
        C.off()
        D.on()
        currentRow = 13
    elif (currentRow == 13):
        A.off()
        B.off()
        C.on()
        D.on()
        currentRow = 14
    elif (currentRow == 14):
        A.on()
        B.off()
        C.on()
        D.on()
        currentRow = 15
    elif (currentRow == 15):
        A.off()
        B.on()
        C.on()
        D.on()
        currentRow = 16
    elif (currentRow == 16):
        A.on()
        B.on()
        C.on()
        D.on()
        currentRow = 1

def clkTick():
    CLK.on()
    CLK.off()

def latchTick():
    LATCH.on()
    LATCH.off()

def enableOutput():
    OE.off()

def disableOutput():
    OE.on()

def shiftInData():
    for i in range(64):
        if (isBitSet(vramR[0][64 - i], i)):
            R1.on()
        else:
            R1.off()
        if (isBitSet(vramR[1][64 - i], i)):
            R2.on()
        else:
            R2.off()

        if (isBitSet(vramG[0][64 - i], i)):
            G1.on()
        else:
            G1.off()
        if (isBitSet(vramG[1][64 - i], i)):
            G2.on()
        else:
            G2.off()

        if (isBitSet(vramB[0][64 - i], i)):
            B1.on()
        else:
            B1.off()
        if (isBitSet(vramB[1][64 - i], i)):
            B2.on()
        else:
            B2.off()

        clkTick()

def isBitSet(value, position):
    return value & (1 << position)

while True:
    enableOutput()
    shiftInData()
    latchTick()
    nextRow()
    disableOutput()
    sleep(BLANK_DELAY_TIME_US / 1000000)

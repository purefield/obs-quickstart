#!/usr/bin/env python3
# pip3 install pyserial
import argparse
import serial
import io
import os.path
from os import path
import serial
import termios

def main():
    arduino = '/dev/ttyACM0'
    brightnessFile = '/tmp/led.brightnes'

    parser = argparse.ArgumentParser(description='LED Brightnes')
    group = parser.add_mutually_exclusive_group(required=True)
    group.add_argument('--brightnes', '-b', type=int, help='brightnes 0 - 100')
    group.add_argument('--relative',  '-r', type=int, help='relative +/- int')
    args = parser.parse_args()
    #print(args.brightnes)
    #print(args.relative)

    with open(brightnessFile, 'r') as f:
        last = f.readline()
        print (last)
        if not last:
            last = 35

        if args.relative != None:
            brightnes = int(last) + int(args.relative)

        else:
            brightnes = int(args.brightnes)

        if brightnes > 100:
            brightnes = 100

        if brightnes < 0:
            brightnes = 0

        if brightnes == 0 and int(last) == 0:
            brightnes = 35

    with open(brightnessFile, 'w') as f:
        f.write(str(brightnes))

    f = open(arduino)
    attrs = termios.tcgetattr(f)
    attrs[2] = attrs[2] & ~termios.HUPCL
    termios.tcsetattr(f, termios.TCSAFLUSH, attrs)
    f.close()

    ser = serial.Serial()
    ser.port = arduino
    ser.baudrate = 9600
    ser.timeout = 1
    # print('dtr =', ser.dtr)
    ser.open()
    sio = io.TextIOWrapper(io.BufferedRWPair(ser, ser), newline=None)
    ser.isOpen()
    ser.isOpen()
    sio.write(str(brightnes))
    sio.flush()
    ser.close()
    #exit()

if __name__== "__main__":
    main()

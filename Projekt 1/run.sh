#!/bin/sh

make
./a.out $1
python main.py $1 $2


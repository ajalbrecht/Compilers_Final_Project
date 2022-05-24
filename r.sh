#!/bin/bash

# run main code
g++ -c  -Wall -m64 -std=c++17 -no-pie -o final.o final.cpp
g++ -m64  -no-pie -o final.out -std=c++17 final.o
./final.out

# run part 3 as its own code
echo # blank spot to space code
echo Compiled code
g++ -c  -Wall -m64 -std=c++17 -no-pie -o finalp3.o finalp3.cpp
g++ -m64  -no-pie -o finalp3.out -std=c++17 finalp3.o
./finalp3.out

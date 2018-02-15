#/bin/bash

gcc -Wall -o main main.c
#valgrind --leak-check=yes
./main 5

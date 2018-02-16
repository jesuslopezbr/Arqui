#/bin/bash

gcc -Wall -DDEBUG -o main main.c
#valgrind --leak-check=yes
./main 5

#/bin/bash

#gcc -Wall -DDEBUG -o main main.c
gcc -Wall -o main main.c
valgrind --leak-check=yes --track-origins=yes ./main 5
#./main 5

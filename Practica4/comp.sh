#bin/bash

rm main
gcc-4.9 -I. -c controlclientes.cpp
gcc-4.9 -o main controlclientes.o -lstdc++

./main 10

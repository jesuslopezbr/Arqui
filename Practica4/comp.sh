#bin/bash

rm main controlclientes.o
#Monitor Uni
#gcc-4.9 -I. -c controlclientes.cpp
#gcc-4.9 -o main controlclientes.o -lstdc++
#PC
gcc -I. -c controlclientes.cpp -pthread
gcc -o main controlclientes.o -lstdc++
./main 10

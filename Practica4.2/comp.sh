#!/bin/bash
#rm servidor.o interfazI.o controlclientes.o interfaz.o cliente.o servidor cliente


if [ $1 == "servidor" ]
then
  gcc-4.9 -std=c++11 -I. -c interfaz.cpp controlclientes.cpp servidor.cpp interfazI.cpp
  gcc-4.9  -o servidor servidor.o interfazI.o controlclientes.o interfaz.o -lIce -lIceUtil -pthread -lstdc++
  ./servidor $2
else
  gcc-4.9 -std=c++11 -I. -c interfaz.cpp controlclientes.cpp cliente.cpp interfazI.cpp
  gcc-4.9 -o cliente cliente.o interfazI.o controlclientes.o interfaz.o -lIce -lIceUtil -pthread -lstdc++
  ./cliente 2 $1 $2
fi

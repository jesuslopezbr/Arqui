#bin/bash
rm servidor.o interfazI.o controlclientes.o interfaz.o cliente.o

Servidor:
gcc-4.9 -I. -c interfaz.cpp controlclientes.cpp servidor.cpp interfazI.cpp
gcc-4.9 -o servidor servidor.o interfazI.o controlclientes.o interfaz.o -lIce -lIceUtil -pthread -lstdc++
./servidor

Cliente:
gcc-4.9 -I. -c interfaz.cpp controlclientes.cpp cliente.cpp interfazI.cpp
gcc-4.9 -o cliente cliente.o interfazI.o controlclientes.o interfaz.o -lIce -lIceUtil -pthread -lstdc++
./cliente 2

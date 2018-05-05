rm server.o testI.o test.o client.o

if [ $1 == "server" ]
then
  gcc-4.9 -I. -c test.cpp server.cpp testI.cpp
  gcc-4.9 -o server server.o testI.o test.o -lIce -lIceUtil -pthread -lstdc++
  ./server
else
  gcc-4.9 -I. -c test.cpp client.cpp testI.cpp
  gcc-4.9 -o client client.o testI.o test.o -lIce -lIceUtil -pthread -lstdc++
  ./client
fi

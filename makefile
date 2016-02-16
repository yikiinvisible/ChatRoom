all: Server

INCLUDE = .
Server: tcp_socket.o main.o epoll_server.o my_epoll.o
	g++ -o Server tcp_socket.o main.o epoll_server.o my_epoll.o

tcp_socket.o: tcp_socket.cpp tcp_socket.h 
	g++ -I$(INCLUDE) -c tcp_socket.cpp

my_epoll.o: my_epoll.h
	g++ -I$(INCLUDE) -c my_epoll.cpp

epoll_server.o: tcp_socket.h my_epoll.h
	g++ -I$(INCLUDE) -c epoll_server.cpp

main.o: epoll_server.h main.cpp
	g++ -I$(INCLUDE) -c main.cpp



make clean:
	-rm *.o

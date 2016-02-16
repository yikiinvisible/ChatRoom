#include "tcp_socket.h"

tcp_socket::tcp_socket()
:socketfd(-1)
{	
}

void tcp_socket::create(){
	socketfd = socket(AF_INET, SOCK_STREAM, 0) ;
	assert( socketfd>=0 );
}

tcp_socket::~tcp_socket(){
	close(socketfd);
}

int tcp_socket::get_fd() const{
	return socketfd;
}

void tcp_socket::bind(const char* ip, const int port){
	bzero( &address, sizeof( address ) );
	address.sin_family = AF_INET;
	inet_pton( AF_INET, ip, &address.sin_addr );
	address.sin_port = htons( port );
	int ret = ::bind( socketfd, (sockaddr*)&address,sizeof( address ) );
	assert( ret!=-1 );
}

void tcp_socket::listen(){
	int ret = ::listen( socketfd,5 );
	assert( ret!=-1 );
}

int tcp_socket::accept( struct sockaddr* &client ){
	socklen_t client_addrlength = sizeof( client );
	int connfd = ::accept( socketfd, (sockaddr*)&client, &client_addrlength );
	if( connfd < 0)
		std::cout<<"error is"<<errno<<std::endl;
	return connfd;
}




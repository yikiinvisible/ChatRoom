#include <stdio.h>
#include <string.h>
#include <string>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <iostream>


class tcp_socket
{
public:
	explicit tcp_socket();   
	int get_fd( )const;
	void create();
	void bind(const char* ip, const int port);
	void listen();
	int accept( struct sockaddr* &client );

	void set_noblock();

	~tcp_socket();
private:
    int socketfd;
    struct sockaddr_in address;
};

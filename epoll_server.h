#include "my_epoll.h"
#include "tcp_socket.h"
#include <cstring>
#include <map>


class epoll_server{
public:
	epoll_server(char *ip, int port);
	void run();
private:
	my_epoll poll;
	std::map<int , std::string >m;  //save client fd and ip;
	tcp_socket Server;
};

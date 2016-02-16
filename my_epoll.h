#include <sys/epoll.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#define EPOLLEVENTS 100

class my_epoll{
public:
	 my_epoll();
	~my_epoll();
	void create_epoll();
	int epoll_wait();
	void add_event(int fd );
	void delete_event(int fd);
	int get_events(int i);
	int get_events_occur_fd(int i);
	int get_wait_num();
private:
	int epollfd;
	int wait_num;
	struct epoll_event events[EPOLLEVENTS];
	void set_noblock( int fd );
};
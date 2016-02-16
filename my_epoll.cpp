
#include "my_epoll.h"



my_epoll::my_epoll() 
:epollfd(-1)
{
}

my_epoll::~my_epoll()
{
	close(epollfd);
}
void my_epoll::create_epoll(){
	epollfd = epoll_create(100);
}

int my_epoll::epoll_wait(){
	int wait_num = ::epoll_wait(epollfd, events, EPOLLEVENTS, -1);
	return wait_num;
}

void my_epoll::add_event(int fd){
	struct epoll_event ev;
	ev.events = EPOLLIN|EPOLLET;
	ev.data.fd = fd;
	epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev);
	set_noblock(fd);
}

void my_epoll::delete_event(int fd ){
	struct epoll_event ev;
	ev.events = EPOLLIN;
	ev.data.fd = fd;
	epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, &ev);
}



int my_epoll::get_events_occur_fd(int i){
	return events[i].data.fd;
}

int my_epoll::get_events(int i){
	return events[i].events;
}

int my_epoll::get_wait_num(){
	return wait_num;
}

void my_epoll::set_noblock(int fd){
	int old_option = fcntl( fd, F_GETFL );
	int new_option = old_option | O_NONBLOCK ;
	fcntl( fd, F_SETFL, new_option );
}
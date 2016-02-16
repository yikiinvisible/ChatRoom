#include "epoll_server.h"

epoll_server::epoll_server(char *ip, int port){
	Server.create();
	Server.bind(ip, port);
	Server.listen();

	poll.create_epoll();
	poll.add_event( Server.get_fd() );
}

void epoll_server::run(){
	char buf[1024];
 	while(1){
		int number = poll.epoll_wait();
		for( int i=0; i<number; ++i ){
			int socketfd = poll.get_events_occur_fd(i);
			if ( socketfd == Server.get_fd() ){
				std::cout<<"new client addrive!"<<std::endl;
				struct sockaddr* client_address;
				int connfd = Server.accept( client_address );
				poll.add_event( connfd );
 				
        			sockaddr_in sin;
      			memcpy(&sin, &client_address, sizeof(sin));    			// 将sockaddr强制转换为 sockaddr_in
      			std::string client_ip = inet_ntoa( sin.sin_addr );
 				m.insert( std::map<int, std::string>::value_type(connfd, client_ip) );

 				std::string hi = "Welcome\n";
				write( connfd, hi.c_str(), hi.size() );
			}

			else if( poll.get_events(i) & EPOLLIN ){
				bzero(buf,1024);
				int ret = recv(socketfd, buf, 1023, 0);
				if(ret <= 0){
					close(socketfd);
					continue;
				}
				for( std::map<int,std::string>::iterator i=m.begin(); i!=m.end(); ++i){
					if (i->first == Server.get_fd() )
						continue;
					std::string who = m[socketfd] +": ";
					write(i->first, who.c_str(), who.size() );
					int ret_ = write(i->first, buf, 1023);
				}

			}
			else if (poll.get_events(i) & EPOLLHUP ){
				close( socketfd );
				poll.delete_event( socketfd );
				std::cout<<"a client left"<<std::endl;
			}
			else
				std::cout<<"something else happen"<<std::endl;
		}
	}
}

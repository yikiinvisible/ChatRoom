#include "epoll_server.h"
#include <unistd.h>
#include <string.h>
#include <stdlib.h>


int main(int argc, char **argv){

    epoll_server Server( argv[1], atoi(argv[2]) );
    std::cout<<"ok! server start run!!!"<<std::endl;
    Server.run(  );
    return 0;
}

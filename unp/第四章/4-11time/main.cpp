#include<netinet/in.h>
#include<arpa/inet.h>
#include<ctime>
#include<memory.h>
#include<iostream>
#include<sstream>
using namespace std;
int main(int argc, char** argv)
{
	int listenfd, connfd;
	socklen_t len;
	sockaddr_storage servaddr, cliaddr;
	char buf[4096];
	stringstream buffer;
	time_t ticks;

	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.ss_family = AF_INET;
	((sockaddr_in*)&servaddr)->sin_addr.s_addr = htonl(INADDR_ANY);
	((sockaddr_in*)&servaddr)->sin_port = htons(13);

	bind(listenfd, (sockaddr*)&servaddr, sizeof(servaddr));
	listen(listenfd, 5);
	while (true)
	{
		len = sizeof(cliaddr);
		connfd = accept(listenfd, (sockaddr*)&cliaddr, &len);
		buffer << "connection from ip " << inet_ntop(AF_INET, &((sockaddr_in*)&cliaddr)->sin_addr, buf, 4096) << " port " << ntohs(((sockaddr_in*)&cliaddr)->sin_port) << std::endl;
		//cout << buffer.str() << endl;
		ticks = time(NULL);
		buffer << ctime(&ticks);
		send(connfd, buffer.str().c_str(), buffer.str().size(), 0);
	}
}



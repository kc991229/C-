#include <iostream>
#include <stdlib.h>
#include <winsock2.h>
#include <string>
#pragma comment(lib,"ws2_2.lib")
using std::string;
using std::cout;
using std::cin;
using std::endl;

class WinSockUdp
{
private:
	SOCKET sock;
public:
	WinSockUdp(){}
	~WinSockUdp(){}
	bool StartUp(WSAData wsadata){
		if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0){
			cout << "Start Error" << endl;
			return false;
		}
		return true;
	}
	bool CreateSocket(){
		sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		if (sock == SOCKET_ERROR){
			cout << "Socket Create Error" << endl;
			return false;
		}
		return true;
	}
	bool Bind(string ip, u_short port){
		struct sockaddr_in addr;
		addr.sin_port = htons(port);
		addr.sin_family = AF_INET;
		addr.sin_addr.s_addr = inet_addr(ip.c_str());

		int res = bind(sock, (struct sockaddr*)&addr, sizeof(sockaddr_in));
		if (res == SOCKET_ERROR){
			cout << "Bind Error" << endl;
			return false;
		}
		return true;
	}
	bool Send( string& data, struct sockaddr_in addr){
		int sendsize = sendto(sock, data.c_str(), data.size(), 0, (struct sockaddr*)&addr, sizeof(struct sockaddr_in));
		if (sendsize < 0){
			cout << "Send Error" << endl;
			return false;
		}
		return true;
	}
	bool Recv(string* data, sockaddr_in *addr){
		char tmp[1024];
		memset(tmp, '\0', sizeof(tmp));
		int fromlen = sizeof(struct sockaddr_in);
		int res = recvfrom(sock, tmp, sizeof(tmp), 0, (struct sockaddr_in*)addr, &fromlen);
		if (res < 0){
			cout << "Recv Error" << endl;
			return false;
		}
		else if (res == 0){
			cout << "Peer ShutDown Connect" << endl;
			return false;
		}
		else{
			(*data).assign(tmp, res);
			return true;
		}
	}
	void Close(){
		closesocket(sock);
	}
};
/*
Author: <Jingren Wang>
Class: ECE 6122
Last Date Modified: <2020/11/11>
Description:
header file of class ECE_UDPSocket
*/
#pragma once
#include <thread>
#include <list>
#include <string>
#include <mutex>
#include <iostream>


#ifdef _WIN32
/* See http://stackoverflow.com/questions/12765743/getaddrinfo-on-win32 */
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0501  /* Windows XP. */
#endif
#include <winsock2.h>
#include <Ws2tcpip.h>

#pragma comment (lib, "Ws2_32.lib")
#else
/* Assume that any non-Windows platform uses POSIX-style sockets instead. */
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>  /* Needed for getaddrinfo() and freeaddrinfo() */
#include <unistd.h> /* Needed for close() */

typedef int SOCKET;
#endif


using namespace std;

//create udpmsg
struct udpMessage
{
	unsigned short nVersion;
	unsigned short nType;
	unsigned short nMsgLen;
	unsigned long lSeqNum;
	char chMsg[1000];
};

class  ECE_UDPSocket
{
public:
	ECE_UDPSocket() = delete;
	//start a std::thread to receive messages.
	ECE_UDPSocket(unsigned short portno);
	//Closes the socket & Terminates the thread
	~ECE_UDPSocket();
	//Function called by thread
	bool getNextMessage(udpMessage& msg);
	//ini sending  func
	void sendMessage(const std::string& strTo, unsigned short usPortNum, const udpMessage& msg);
	//ini sending composite func
	void sendCompositeMsg();
	//ini display func
	void display();
	//ini clear func
	void clearCompositeMsg();
	//process and add source to Msg
	void processMessage();
	void addSource();

	list<udpMessage> m_msgs;
	list<udpMessage>::iterator it_msgs;
	//false is server, true is client
	bool clientorNot = false;

	int sockInit(void);
	int sockQuit(void);
	int sockClose();
	void error(const char* msg);
private:
	//determine the sequence
	friend bool compare(udpMessage a1, udpMessage a2);
	//receive socket msg
	friend void receiveSocketMsgs(ECE_UDPSocket* pUDpSocket);


	int fd;
	socklen_t fromlen;
	char buffer[1024];
	udpMessage sockMsg;
	string compositeMsgs;
	thread m_recvThread;

	list<sockaddr_in> m_lstSources;
	list<sockaddr_in>::iterator sources;
	mutex m_mutex;
};



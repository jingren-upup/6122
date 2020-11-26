/*
Author: <Jingren Wang>
Class: ECE 6122
Last Date Modified: <2020/11/11>
Description:
header file of class ECE_UDPSocket of client
*/
#include "ECE_UDPSocket.h"
#include<cstring>

//this func is used to find out the sequence
bool compare(udpMessage a1, udpMessage a2)
{
    return a1.lSeqNum < a2.lSeqNum;
}
// Function called by thread
void receiveSocketMsgs(ECE_UDPSocket* pUDpSocket)
{
    // Loop that waits on incoming messages
    udpMessage inMsg;
    int n;
    sockaddr_in from;
    socklen_t fromlen{ sizeof(struct sockaddr_in) };

    while (true)
    {

        //client
        if (pUDpSocket->clientorNot)
        {
            memset(pUDpSocket->buffer, 0, 1024);
             n = recvfrom(pUDpSocket->fd, pUDpSocket->buffer, 1023, 0, (struct sockaddr*)&from, &pUDpSocket->fromlen);
            pUDpSocket->buffer[n] = 0;
            if (n < 0)
            {
                pUDpSocket->error("recvfrom");
                break;
            }
            printf("%s\n", pUDpSocket->buffer);
        }
        //server
        else
        {
            // Insert message into list based on sequence number
            n = recvfrom(pUDpSocket->fd, (char*)&inMsg, sizeof(inMsg), 0, (struct sockaddr*)&from, &pUDpSocket->fromlen);
            pUDpSocket->m_lstSources.push_back(from);
            if (n < 0)
            {
                break;
            }
            //determine whether the version is correct
            if (inMsg.nVersion == 1)
            {
                string receivedMsg;
                receivedMsg.clear();
                receivedMsg = "Received Msg Type:" + to_string(inMsg.nType) + ", Seq:" + to_string(inMsg.lSeqNum) + ", Msg:" + inMsg.chMsg;
               //reurn the receive msg
                n = sendto(pUDpSocket->fd, receivedMsg.c_str(), receivedMsg.length(), 0, (struct sockaddr*) & from, pUDpSocket->fromlen);
                pUDpSocket->getNextMessage(inMsg);
            }
      ;
        }
    }
#ifdef _WIN32
    std::cin.get();
#endif
    return;
}
//ini UDP SOCKET
ECE_UDPSocket::ECE_UDPSocket(unsigned short portno)
{
    sockaddr_in serv_addr;
    // Setup socket
    sockInit();
    // Create the socket
    fd = socket(AF_INET, SOCK_DGRAM, 0);
    // Make sure the socket was created
    if (fd < 0)
        error("ERROR opening socket");
    // Zero out the variable serv_addr
    memset((char*)&serv_addr, sizeof(serv_addr), 0);
    // Initialize the serv_addr
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    if (bind(fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
    {
        error("ERROR on binding");
    }
    fromlen = sizeof(struct sockaddr_in);

    // Start thread that waits for messages 
    if (portno != 51717)
    {
        clientorNot = true;
    }
    m_recvThread = thread(receiveSocketMsgs, this);
}
//determine the type of msg
bool ECE_UDPSocket::getNextMessage(udpMessage& msg)
{
    //lock others thread
    m_mutex.lock();
    if (msg.nVersion == 1)
    {
        switch (msg.nType)
        {
        case 0:
            m_msgs.clear();//clear msg
            break;
        case 1:
            m_msgs.clear();
            m_msgs.push_back(msg);//put the msg
            break;
        case 2:
            m_msgs.push_back(msg);
            m_msgs.sort(compare);//add the new msg according sequence
            break;
        case 3:
            m_msgs.push_back(msg);
            addSource();
            processMessage();
            sendCompositeMsg();//return msg
            m_msgs.clear();
            break;
        default:
            break;
        }
        m_mutex.unlock();
        return true;
    }
    m_mutex.unlock();//restart other thread
    return false;
}
//send msg func
void ECE_UDPSocket::sendMessage(const string& strTo, unsigned short usPortNum, const udpMessage& msg)
{
    struct sockaddr_in addr;
    struct hostent* server;
    const char* ipAddr = strTo.c_str();

    server = gethostbyname(ipAddr);
    memset((char*)&addr, sizeof(addr), 0);
    addr.sin_family = AF_INET;
    memmove((char*)&addr.sin_addr.s_addr, (char*)server->h_addr, server->h_length);
    addr.sin_port = htons(usPortNum);

    int n = sendto(fd, (char*)&msg, sizeof(msg), 0, (struct sockaddr*)&addr, sizeof(addr));
    if (n < 0)
        error("ERROR writing to socket");
}
//process msg to composite 
void ECE_UDPSocket::processMessage()
{
    
    if (sizeof(compositeMsgs) > 1000)
    {
        string::iterator it;
        for (int i = 0; i < 1000; ++i)
        {
            compositeMsgs.erase(it);//erase it
        }
        for (sources = m_lstSources.begin(); sources != m_lstSources.end(); ++sources)
        {
            int n = sendto(fd, (char*)&compositeMsgs, sizeof(compositeMsgs), 0, (struct sockaddr*)&sources, sizeof(struct sockaddr_in));
        }
    }

}
//add source to composite msg
void ECE_UDPSocket::addSource()
{
    compositeMsgs.clear();
    for (it_msgs = m_msgs.begin(); it_msgs != m_msgs.end(); ++it_msgs)
    {
        compositeMsgs += it_msgs->chMsg;
    }
}
//after finish the composite msg£¬send it 
void ECE_UDPSocket::sendCompositeMsg()
{   
  
    string send;
    send.clear();
    send = "Composite Msg: " + compositeMsgs;
    int n;
    for (sources = m_lstSources.begin(); sources != m_lstSources.end(); ++sources)
    {
        n = sendto(fd, send.c_str(), send.length(), 0, (struct sockaddr*)&*sources, fromlen);
    }
}
//display composite msg
void ECE_UDPSocket::display()
{
    processMessage();
    cout << "Composite Msg is: " << compositeMsgs << endl;
}
//clear composite msg
void ECE_UDPSocket::clearCompositeMsg()
{
    m_mutex.lock();
    m_msgs.clear();
    m_mutex.unlock();
}
//if return 0,close the application
ECE_UDPSocket::~ECE_UDPSocket()
{
    sockClose();
    sockQuit();
    m_recvThread.join();
}

int ECE_UDPSocket::sockInit(void)
{
#ifdef _WIN32
    WSADATA wsa_data;
    return WSAStartup(MAKEWORD(1, 1), &wsa_data);
#else
    return 0;
#endif
}
// Cross-platform socket quit
int ECE_UDPSocket::sockQuit(void)
{
#ifdef _WIN32
    return WSACleanup();
#else
    return 0;
#endif
}
// Cross-platform socket close
int ECE_UDPSocket::sockClose(void)
{

    int status = 0;

#ifdef _WIN32
    status = shutdown(fd, SD_BOTH);
    if (status == 0)
    {
        status = closesocket(fd);
    }
#else
    status = shutdown(fd, SHUT_RDWR);
    if (status == 0)
    {
        status = close(fd);
    }
#endif

    return status;

}
// Output error message and exit
void ECE_UDPSocket::error(const char* msg)
{
    perror(msg);
    // Make sure any open sockets are closed before calling exit
    exit(0);
}



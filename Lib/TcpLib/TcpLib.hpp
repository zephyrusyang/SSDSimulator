/**
 * 
 *
 */

#ifndef TCP_LIB_HPP
#define TCP_LIB_HPP

#include <sys/socket.h>  //ソケット通信用
#include <errno.h>       //エラー解析用
#include <netinet/in.h>  //sockaddr_in用
#include <arpa/inet.h>   //inet_addr用

class TcpMaster{
public:
  TcpMaster(){
    InitMember();
  }
  virtual ~TcpMaster(){
    close(selfSock_);
  }
  bool isInit_;
  int selfSock_;
  int clientSock_;
}

#endif /* TCP_LIB_HPP */

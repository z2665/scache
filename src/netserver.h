#pragma once

#include <boost/asio.hpp>
#include <vector>

class RWHandle
{
public:
  RWHandle(boost::asio::io_context &ioc) : sock(ioc) {}
  ~RWHandle()
  {
  }
  boost::asio::ip::tcp::socket &GetSock()
  {
    return sock;
  }

private:
  boost::asio::ip::tcp::socket sock;
};

class NetServer
{

public:
  NetServer(int port, int maxcon = 20);
  void Start();
  void HandleAccept();
  ~NetServer();
  std::vector<std::shared_ptr<RWHandle>> conlist;

private:
  boost::asio::io_context mio;
  boost::asio::ip::tcp::acceptor acp;

  int _port;
  int _maxcon;
  int _nowcon;
};

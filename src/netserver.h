#pragma once

#include <array>
#include <boost/asio.hpp>
#include <vector>

class RWHandle {
   public:
    RWHandle(boost::asio::io_context &ioc) : sock(ioc) {}
    ~RWHandle() {}
    boost::asio::ip::tcp::socket &GetSock() { return sock; }
    void HandleRead();

   private:
    void eventHandle(std::string_view data);

   private:
    // static constexpr int buffer_len = 1024 * 1024 * 4;
    boost::asio::ip::tcp::socket sock;
    boost::asio::streambuf _buffer;
    static constexpr std::string_view GET = "get";
    static constexpr std::string_view SET = "set";
};

class NetServer {
   public:
    NetServer(int port, int maxcon = 20);
    void Start();
    void HandleAccept();
    ~NetServer();
    std::vector<std::shared_ptr<RWHandle>> conlist;

   private:
    boost::asio::io_context mio;
    int _port;
    int _maxcon;
    int _nowcon;
    boost::asio::ip::tcp::acceptor acp;
};

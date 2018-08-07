#include "netserver.h"
#include "helper.h"
#include <iostream>
using namespace boost;
using namespace Helper;
using std::cout;
using std::endl;
//当context传入1的时候只使用单线程。asio会跳过所有的锁
NetServer::NetServer(int port, int maxcon) : mio(1), _port(port), _maxcon(maxcon), _nowcon(0), acp(mio, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), _port))
{
}
NetServer::~NetServer()
{
}
void NetServer::Start()
{
    HandleAccept();
    mio.run();
}

//用于接受连接
void NetServer::HandleAccept()
{
    cout << "start listen!" << endl;
    //确定当前连接数没有超过最大连接数
    if (_nowcon > _maxcon)
    {
        //TODO 错误处理
        return;
    }
    //创建连接处理对象
    std::shared_ptr<RWHandle> handler = std::make_shared<RWHandle>(mio);
    acp.async_accept(handler->GetSock(), [this, handler](const boost::system::error_code &ec) {
        if (ec)
        {
            cout << ec.value() << " msg:" << ec.message() << endl;
        }
        //保存连接对象
        conlist.push_back(handler);
        //fuck 忘记启动read了
        handler->HandleRead();
        //启动下一个循环
        HandleAccept();
    });
}

//用于处理读取事件
void RWHandle::HandleRead()
{
    asio::async_read_until(sock, _buffer, "\r\n", [this](const boost::system::error_code &ec, std::size_t bytes_transferred) {
        if (ec)
        {
            cout << ec.value() << " msg:" << ec.message() << endl;
            //TODO 异常处理 连接断开会收到EOF
            return;
        }
        std::string data(buffers_begin(_buffer.data()), buffers_begin(_buffer.data()) + _buffer.size());
        cout << "trans :" << bytes_transferred << endl;
        cout << data << endl;
        _buffer.commit(bytes_transferred);
        _buffer.consume(bytes_transferred);
        eventHandle(data);
        HandleRead();
    });
}

//用于处理接收到的客户端字符串
void RWHandle::eventHandle(std::string_view data)
{
    static const std::string space = " ";
    static const std::string CRLF = "\r\n";
    //TODO 这里需要做异常处理，外部输入可能会比较诡异
    auto prestr_list = SplitString(data, CRLF);
    auto str_list = SplitString(prestr_list[0], space);
    for (auto &str : str_list)
    {
        cout << "str:" << str << endl;
    }
}
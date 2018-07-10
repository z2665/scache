#include "netserver.h"
#include <iostream>
using namespace boost;
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
    mio.run();
}

void NetServer::HandleAccept()
{
    cout << "start listen!" << endl;
    //确定当前连接数没有超过最大连接数
    if (_nowcon > _maxcon)
    {
        //TODO 错误处理
        return
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
        //启动下一个循环
        HandleAccept();
    })
}
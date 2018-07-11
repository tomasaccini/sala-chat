#ifndef __SERVERTHREAD__
#define __SERVERTHREAD__

#include "../common/common_Thread.h"
#include "../common/common_Socket.h"
#include "../common/common_BlockingQueue.h"
#include "server_ClientHandler.h"
#include "server_ChatThread.h"
#include <string>

#define SOCKETS_HOLDING 10

class ServerThread : public Thread {
private:
    BlockingQueue<std::string> blocking_queue;
    Socket socket;
    std::vector<ClientHandler*> clients;
    ChatThread chat_thread;
    bool keep_running;

    // No copiable.
    ServerThread(const ServerThread &other) = delete;
    ServerThread& operator=(const ServerThread &other) = delete;
public:
    ServerThread(const char* port);
    void run();
    void stop();

    // Destructor.
    ~ServerThread() override;
};



#endif

#ifndef __CHATTHREAD__
#define __CHATTHREAD__

#include <string>
#include <vector>
#include "../common/common_Thread.h"
#include "../common/common_BlockingQueue.h"
#include "server_ClientHandler.h"

class ChatThread : public Thread {
private:
    BlockingQueue<std::string>* blocking_queue;
    std::vector<ClientHandler*> clients;
    bool alive;
    // No copiable.
    ChatThread(const ChatThread &other) = delete;
    ChatThread& operator=(const ChatThread &other) = delete;

public:
    ChatThread();

    void add_client_handler(ClientHandler*);

    void run() override;

    void stop();

    ~ChatThread() override = default;
};


#endif

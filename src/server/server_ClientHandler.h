#ifndef __CLIENTHANDLER__
#define __CLIENTHANDLER__

#include <string>
#include <vector>
#include "../common/common_Thread.h"
#include "../common/common_Socket.h"
#include "../common/common_SocketProtocol.h"
#include "../common/common_BlockingQueue.h"


class ClientHandler : public Thread {
private:
    size_t id;
    bool alive;
    bool is_queue_enabled = false;
    BlockingQueue<std::string>* blocking_queue;
    SocketProtocol protocol;

    // No copiable.
    ClientHandler(const ClientHandler &other) = delete;
    ClientHandler& operator=(const ClientHandler &other) = delete;

public:
    ClientHandler(Socket&& socket, size_t id);
    ClientHandler(ClientHandler&& other) = default;

    void run() override;

    void stop();

    /* Indica si el hilo ya terminó su ejecución */
    bool is_alive() const;

    // Agrega una safe queue, en la cual va a agregar los eventos recibidos.
    void add_blocking_queue(BlockingQueue<std::string>* blocking_queue);

    void send_message(std::string message);

    ~ClientHandler() override = default;
};


#endif

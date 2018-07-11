#ifndef __SOCKETPROTOCOL__
#define __SOCKETPROTOCOL__

#include <string>
#include <vector>
#include "common_Socket.h"

#define PROTOCOL_LENGTHS_VALUE 4

/* Clase protocolo que abstrae al sistema de como se realiza la
 * comunicación entre los clientes y el servidor.
 * Esta implementación particular utiliza un socket para la comunicación
 */
class SocketProtocol {
private:
    Socket socket;

    /* Envía un número a través del socket */
    SocketProtocol& operator<<(int value);

    /* Envía un número a través del socket */
    void send_size(int size);

    /* Envía un número a través del socket */
    void send_numeric_value(int value);

    /* Recibe un número a través del socket */
    uint32_t receive_numeric_value();


public:
    /* Constructor que se conecta a la ip y puerto indicados */
    SocketProtocol(const char* ip, const char* port);

    /* Constructor que utiliza el socket recibido para la comunicación */
    explicit SocketProtocol(Socket&& other_socket);

    SocketProtocol(SocketProtocol&& other) noexcept = default;

    /* Recibe un string a través del socket */
    std::string receive_string();

    /* Envía un string a través del socket */
    void send_string(const std::string& message);

    void shutdown(int mode);
    ~SocketProtocol();
};

#endif

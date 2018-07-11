#ifndef __SOCKET__
#define __SOCKET__

#include <climits>
#include <netdb.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

#define GETADDRINFO_ERROR "Error en getaddrinfo"
#define SOCKET_CREATE_ERROR "Error al crear socket"
#define SOCKET_LISTEN_ERROR "Error en socket listen: "
#define SOCKET_ACCEPT_ERROR "Error en socket accept: "
#define SOCKET_SEND_ERROR "Error en socket send: "
#define SOCKET_RECV_ERROR "Error en socket receive: "
#define SOCKET_SHUTDOWN_ERROR "Error en socket shutdown: "

/* Clase socket.
 * Internamente, utiliza los sockets de unix.
 */
class Socket {
private:
    int file_descriptor;

    /* Constructor interno que recibe un file_descriptor
     * Resulta útil para crear un socket luego de un accept
     */
    explicit Socket(int file_descriptor);

    /* Método interno que inicializa el socket recibido.
     * En el puntero a función se espera recibir 'bind' o 'connect'
     */
    void initialize_socket(Socket& skt, const char* ip,
                           const char* port, int flags,
                           int function(int,
                                        const struct sockaddr*,
                                        socklen_t));

    /* Se evita que se copie un objeto de esta clase */
    Socket(const Socket&) = delete;
    Socket& operator=(const Socket&) = delete;

public:
    Socket(Socket&& other) noexcept;
    Socket& operator=(Socket &&other) noexcept;

    /* Crea un socket y realiza un bind al puerto indicado */
    explicit Socket(const char* port);

    /* Crea un socket y realiza un connect a la ip y puerto indicados */
    Socket(const char* ip, const char* port);

    /* Indica al socket cuantos clientes se pueden tener en espera */
    void listen(int holding);

    /* Bloquea el socket para aceptar nuevos clientes */
    Socket accept();

    /* Envía los datos del buffer mediante el socket */
    int send(const char* buffer, size_t length);

    /* Recibe datos mediante el socket y los escribe en el buffer */
    int receive(char* buffer, size_t length);

    /* Corta la comunicación del socket.
     * SHUT_RD: Cierra la comunicación de lectura
     * SHUT_WR: Cierra la comunicación de escritura
     * SHUT_RDWE: Cierra la comunicación de lectura y escritura
     */
    void shutdown(int mode);

    /* Destructor. Cierra el socket */
    ~Socket();
};


#endif //__SOCKET__

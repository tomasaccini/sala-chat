#define _POSIX_C_SOURCE 200112L

#include <netdb.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <cstring>
#include <algorithm>
#include <stdexcept>
#include <string>
#include <cerrno>
#include "common_Socket.h"

using std::string;

Socket::Socket(const char* port){
    initialize_socket(*this, nullptr, port, AI_PASSIVE, bind);
}

Socket::Socket(const char* ip, const char* port){
    initialize_socket(*this, ip, port, 0, connect);
}

Socket::Socket(int file_descriptor) : file_descriptor(file_descriptor) {}

Socket::Socket(Socket &&other) noexcept {
    this->file_descriptor = other.file_descriptor;
    other.file_descriptor = -1;
}

Socket& Socket::operator=(Socket &&other) noexcept {
    if (this == &other){
        return *this;
    }
    this->file_descriptor = other.file_descriptor;
    other.file_descriptor = -1;
    return *this;
}

void Socket::listen(int holding){
    int status = ::listen(this->file_descriptor, holding);
    if (status == -1) {
        string error = strerror(errno);
        error = SOCKET_LISTEN_ERROR + error;
        throw std::runtime_error(error);
    }
}

Socket Socket::accept(){
    int new_socket = ::accept(this->file_descriptor, nullptr, nullptr);
    if (new_socket == -1){
        string error = strerror(errno);
        error = SOCKET_ACCEPT_ERROR + error;
        throw std::runtime_error(error);
    }
    Socket skt(new_socket);
    return std::move(skt);
}

int Socket::send(const char* buffer, size_t length){
    size_t bytes_sent = 0;
    while (bytes_sent < length) {
        ssize_t status = ::send(this->file_descriptor,
                              &buffer[bytes_sent],
                              length - bytes_sent,
                              MSG_NOSIGNAL);

        if (status < 0) {
            string error = strerror(errno);
            error = SOCKET_SEND_ERROR + error;
            throw std::runtime_error(error);
        } else if (status == 0) {
            break;
        } else {
            bytes_sent += status;
        }
    }
    return bytes_sent;
}

int Socket::receive(char* buffer, size_t length){
    size_t bytes_received = 0;
    while (bytes_received < length) {
        ssize_t status = recv(this->file_descriptor,
                              &buffer[bytes_received],
                              length - bytes_received,
                              0);

        if (status < 0) {
            string error = strerror(errno);
            error = SOCKET_RECV_ERROR + error;
            throw std::runtime_error(error);
        } else if (status == 0){
            break;
        } else {
            bytes_received += status;
        }
    }
    return bytes_received;
}

void Socket::shutdown(int mode){
    if (this->file_descriptor > 0){
        int status = ::shutdown(this->file_descriptor, mode);
        if (status == -1){
            string error = strerror(errno);
            error = SOCKET_SHUTDOWN_ERROR + error;
            throw std::runtime_error(error);
        }
    }
}

Socket::~Socket(){
    if (this->file_descriptor > 0){
        ::close(this->file_descriptor);
    }
}

void Socket::initialize_socket(Socket& skt, const char* ip,
                               const char* port, int flags,
                               int function(int,
                                            const struct sockaddr*,
                                            socklen_t)){
    struct addrinfo hints;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = flags;

    struct addrinfo* addresses;
    int status = getaddrinfo(ip, port, &hints, &addresses);
    if (status != 0) {
        throw std::runtime_error(GETADDRINFO_ERROR);
    }

    struct addrinfo* remote;
    int socket_file_descriptor;
    bool connection_established = false;
    for (remote = addresses;
         remote != nullptr && !connection_established;
         remote = remote->ai_next) {
        socket_file_descriptor = socket(remote->ai_family,
                                        remote->ai_socktype,
                                        remote->ai_protocol);
        if (socket_file_descriptor == -1){
            continue;
        } else {
            status = function(socket_file_descriptor,
                              remote->ai_addr,
                              remote->ai_addrlen);
            if (status == -1) {
                ::close(socket_file_descriptor);
                continue;
            }

            connection_established = true;
            skt.file_descriptor = socket_file_descriptor;
        }
    }
    freeaddrinfo(addresses);
    if (!connection_established){
        throw std::runtime_error(SOCKET_CREATE_ERROR);
    }
}

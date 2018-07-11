#include <string>
#include <vector>
#include <cstring>
#include <syslog.h>
#include <iostream>
#include "common_SocketProtocol.h"

using std::string;
using std::vector;
using std::move;

SocketProtocol::SocketProtocol(const char *ip, const char *port) :
                                                socket(ip, port) {}

SocketProtocol::SocketProtocol(Socket &&other_socket) : \
                                socket(move(other_socket)) {}

SocketProtocol &SocketProtocol::operator<<(int value) {
    send_numeric_value(value);
    return *this;
}

void SocketProtocol::send_numeric_value(int value) {
    uint32_t value_big_endian = htonl(value);
    char value_big_endian_char[PROTOCOL_LENGTHS_VALUE];
    memcpy(value_big_endian_char, &value_big_endian, PROTOCOL_LENGTHS_VALUE);
    socket.send(value_big_endian_char, PROTOCOL_LENGTHS_VALUE);
}

uint32_t SocketProtocol::receive_numeric_value() {
    char value_big_endian_char[PROTOCOL_LENGTHS_VALUE];
    socket.receive(value_big_endian_char, PROTOCOL_LENGTHS_VALUE);
    uint32_t value_big_endian;
    memcpy(&value_big_endian, value_big_endian_char, PROTOCOL_LENGTHS_VALUE);
    uint32_t value = ntohl(value_big_endian);
    return value;
}

std::string SocketProtocol::receive_string(){
    uint32_t message_size = receive_numeric_value();
    char* message = (char*) malloc(message_size);
    socket.receive(message, message_size);
    string received_message(message, message_size);
    free(message);
    return received_message;
}

void SocketProtocol::send_size(int size) {
    uint32_t size_big_endian = htonl(size);
    char size_big_endian_char[PROTOCOL_LENGTHS_VALUE];
    memcpy(size_big_endian_char, &size_big_endian, PROTOCOL_LENGTHS_VALUE);
    socket.send(size_big_endian_char, PROTOCOL_LENGTHS_VALUE);
}

void SocketProtocol::send_string(const std::string& message) {
    int message_size = message.size();
    send_size(message_size);
    socket.send(message.data(), message.size());
}

void SocketProtocol::shutdown(int mode){
    socket.shutdown(mode);
}

SocketProtocol::~SocketProtocol() {
    try {
        socket.shutdown(SHUT_RDWR);
    }
    catch (std::exception& ex) {
        syslog(LOG_ERR, "%s", ex.what());
    }
}

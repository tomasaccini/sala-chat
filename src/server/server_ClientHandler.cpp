#include <string>
#include <iostream>
#include <vector>
#include <syslog.h>
#include "server_ClientHandler.h"

using std::move;

ClientHandler::ClientHandler(Socket&& socket, size_t id) : protocol(std::move(socket)) {
    alive = false;
    blocking_queue = NULL;
    this->id = id;
}

void ClientHandler::run() {
    alive = true;
    while (alive) {
      try {
          std::string message = this->protocol.receive_string();
          std::string aux = "Cliente " + std::to_string(id) + ": '" + message + "'.\n";
          blocking_queue->push(aux);
      } catch (std::exception& ex){
          syslog(LOG_ERR, "%s", ex.what());
      }
    }
}

void ClientHandler::stop(){
    alive = false;
    this->protocol.shutdown(SHUT_RDWR);
}

bool ClientHandler::is_alive() const {
    return alive;
}

void ClientHandler::add_blocking_queue(BlockingQueue<std::string>* blocking_queue) {
    this->blocking_queue = blocking_queue;
}

void ClientHandler::send_message(std::string message) {
    protocol.send_string(message);
}

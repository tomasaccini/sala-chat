#include "client_ChatDisplay.h"
#include <iostream>

ChatDisplay::ChatDisplay(SocketProtocol* socket_protocol) {
  alive = true;
  sp = socket_protocol;
}

void ChatDisplay::run() {
  std::string message;
  while (alive) {
    message = sp->receive_string();
    if (message != "")
      printf("%s", message.c_str());
      if (message == "Server: Se cierra la conexión"){
        this->stop();
      }
  }
}

void ChatDisplay::stop() {
  alive = false;
  sp->shutdown(SHUT_RDWR);
}

bool ChatDisplay::is_alive() {
  return alive;
}

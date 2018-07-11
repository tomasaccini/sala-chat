#include <string>
#include <vector>
#include <syslog.h>
#include "server_ChatThread.h"

using std::move;

ChatThread::ChatThread() {
  blocking_queue = new BlockingQueue<std::string>();
}

void ChatThread::add_client_handler(ClientHandler* client_handler){
  clients.push_back(client_handler);
  client_handler->add_blocking_queue(blocking_queue);
  client_handler->start();
}

void ChatThread::run() {
    alive = true;
    std::string message;
    while (alive) {
      try {
          this->blocking_queue->pop(message);
          for (size_t i = 0; i < clients.size(); i++) {
            clients[i]->send_message(message);
          }
      } catch (std::exception& ex){
          syslog(LOG_ERR, "%s", ex.what());
      }
    }
}

void ChatThread::stop(){
    alive = false;
    std::string final_message = "Server: Se cierra la conexión";
    this->blocking_queue->push(final_message);
}

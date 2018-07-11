#include "server_ServerThread.h"
#include <syslog.h>

ServerThread::ServerThread(const char* port) : socket(port) {
  socket.listen(SOCKETS_HOLDING);
  keep_running = true;
}

void ServerThread::run() {
  chat_thread.start();
  while (keep_running) {
    try {
      Socket client_socket = socket.accept();
      ClientHandler* client = new ClientHandler(std::move(client_socket), clients.size());
      clients.push_back(client);
      chat_thread.add_client_handler(client);
    } catch (std::exception& ex) {
      syslog(LOG_ERR, "%s", ex.what());
      if (!keep_running){
        return;
      }
    }
  }
}

void ServerThread::stop(){
    keep_running = false;
    chat_thread.stop();
    chat_thread.join();
    for (size_t i = 0; i < clients.size(); ++i) {
        clients[i]->stop();
        clients[i]->join();
        delete clients[i];
    }
    clients.clear();
    socket.shutdown(SHUT_RDWR);
}

ServerThread::~ServerThread() {

}

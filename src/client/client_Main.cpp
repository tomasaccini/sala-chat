#include "../common/common_SocketProtocol.h"
#include "client_ChatDisplay.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
  SocketProtocol sp("127.0.0.1", argv[1]);
  ChatDisplay cd(&sp);
  cd.start();
  while (cd.is_alive()){
    std::string input;
    std::getline(std::cin, input);
    if (cd.is_alive())
      sp.send_string(input);
  }
  cd.join();
  return 0;
}

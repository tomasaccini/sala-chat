#include <iostream>
#include <string>
#include "server_ServerThread.h"

int main(int argc, char* argv[]) {
  try {
    ServerThread st(argv[1]);
    st.start();
    while (true){
        std::string input;
        std::cin >> input;
        if (input.length() == 1 && input.at(0) == 'q'){
          st.stop();
          break;
        }
    }
    st.join();
    return 0;
  } catch (...){
    std::cout << "Ocurrió un problema" << std::endl;
    return -1;
  }
}

#ifndef __CHATDISPLAY__
#define __CHATDISPLAY__
#include <string>
#include "../common/common_Thread.h"
#include "../common/common_SocketProtocol.h"

class ChatDisplay : public Thread {
private:
  SocketProtocol* sp;
  bool alive;
public:
  ChatDisplay(SocketProtocol* socket_protocol);

  void run() override;

  void stop();

  bool is_alive();
};

#endif

#ifndef __MUNITIONSNOTIFICATION__
#define __MUNITIONSNOTIFICATION__

#include "server_INotification.h"

/*
 * Hereda de INotification. Envía información sobre las municiones del jugador.
 */
class MunitionsNotification : public INotification {
private:
    ClientHandler* client;
    int dynamite_m;
    int radiocontrolled_m;
    int teletransportation_m;

    MunitionsNotification(const MunitionsNotification&) = delete;
    MunitionsNotification& operator=(const MunitionsNotification&) = delete;
public:
    MunitionsNotification(ClientHandler* client, int dynamite_m, \
                            int radiocontrolled_m, int teletransportation_m);

    void run();

    ~MunitionsNotification() = default;
};


#endif //__MUNITIONSNOTIFICATION__

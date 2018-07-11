#ifndef __THREAD_H__
#define __THREAD_H__

#include <thread>

/* Clase abstracta que representa a un hilo de ejecución.
 * Mediante las clasess que hereden de ella,
 * permite ejecutar una tarea en múltiples hilos.
 */
class Thread {
private:
    std::thread thread;

    // No copiable.
    Thread(const Thread&) = delete;
    Thread& operator=(const Thread&) = delete;

public:
    Thread() = default;
    Thread(Thread&& other) = default;
    Thread& operator=(Thread&& other) = default;

    /* Comienza la ejecución de la tarea definida en 'run' */
    void start();

    /* Bloquea el hilo que llame a este método hasta
     * que el objeto hilo termine su ejecución.
     */
    void join();

    /* Indica si se le puede realizar un join al hilo */
    bool joinable();

    /* Método virtual que debe definirse en las clases que hereden de esta.
     * Representa la tarea a realizarse en la ejecución del hilo.
     */
    virtual void run() = 0;
    virtual ~Thread() = default;
};


#endif //__THREAD_H__

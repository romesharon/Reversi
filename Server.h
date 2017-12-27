/*aviv shisman 206558157 and rom sharon
 * the server:
 */

#ifndef Server_H
#define Server_H


class Server {
public:
    Server(int port);
    void start();
    void stop();
    static void* handleClient(void*);
private:
    int port;
    int serverSocket;
};

#endif
/*aviv shisman 206558157 and rom sharon*/

#include "Client.h"
using namespace std;
/*client constructor
 * creating the client
 */
Client::Client(const char *sIP, int sPort){
        serverIP=sIP;
        serverPort=sPort;
        clientSocket=0;
    cout << "Client constructor" << endl;
}

Point Client::sendMove(int arg1, int arg2) {
    // giving the chosen point to the server
    Point p(arg1,arg2);
    int n = write(clientSocket,&p, sizeof(p));
    if (n == -1) {
        throw "Error writing arg1 to socket";
    }

    // Read the new point from the server
    n = read(clientSocket, &p, sizeof(p));
    if (n == -1) {
        throw "Error reading result from socket";
    }
    return p;
}

void Client::connectToServer() {
    // Create a socket
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        throw "Error opening socket";
    }

    // Convert the ip string to a network address
    struct in_addr address;
    if (!inet_aton(serverIP, &address)) {
        throw "Can't parse IP address";
    }

    // Get a hostent structure for the given host address
    struct hostent *server;
    server = gethostbyaddr((const void *)&address, sizeof(address), AF_INET);
    if (server == NULL) {
        throw "Host is unreachable";
    }

    // Create a structure for the server address
    struct sockaddr_in serverAddress;
    bzero((char *)&address, sizeof(address));
    serverAddress.sin_family = AF_INET;
    memcpy((char *)&serverAddress.sin_addr.s_addr, (char*)server->h_addr, server->h_length);

    // htons converts values between host and network byt orders
    serverAddress.sin_port = htons(serverPort);

    // Establish a connection with the TCP server
    if (connect(clientSocket,(struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1){
        throw "Error connecting to server";
    }
    cout << "Connected to server" << endl;
}

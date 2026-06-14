# FT_IRC

# what is a socket ?

- A socket is an endpoint for where the data will be sent to and received.
- Sockets are used as a generalized means of communication between different processes on the same computer or on the same network.
- Since everything is a file in Unix systems, processes identify sockets by their file descriptors.

NB: socket() call does not specify where data will be coming from nor where it will be going to - it just creates the interface!
NB: listen() is used by the server only as a  way to get new sockets.

# TCP/IP Network Topology

- To send data from a computer to another there are 4 layers:
Application -> Transport -> Internet -> Network Access Layer

- The Application layer is the endpoint and it is represented in programming by the socket itself.

- In the Transport layer we choose the type of socket either TCP or UDP

- In the internet layer we choose the type of protocol with which the socket will work (IPv4 IPv6).

# The main goal is to create a Client-Server communication

- Server:
    passively waits for and responds to clients
    passive socket

- Client:
    initiates the communication
    must know the address and the port of the server
    active socket

# Main functions used

- socket()  :  Create a new communication endpoint
- bind()    :  Attach a local address to a socket
- listen()  :  Announce willingness to accept connections
- accept()  :  Block caller until a connection
- connect() :  Actively attempt to establish a connection
- send()    :  Send some data over the connection
- recv()    :  Receive some data over the connection

* The TCP client's function call order:
    socket()
    connect()
    read() / write()
    close(client)

* The TCP server's function call order:
    socket()
    bind()
    listen()
    accept()
    read() /write()
    close()


1. Create a Socket:
    To perform network I/O the first thing a process must do is call the socket() function to create a specific type of socket by specifying the type of communication protocol, protocol family, ..etc

-   function:

#include <sys/socket.h>

int     socket(int domain, int type, int protocol);


int main()
{
    int sockID = socket(domain, type, protocol);
    
    => in case of failure returns -1 

    close(sockID);     //ounce we finish with the socket we close it.

}
    //domain: (family) types:
        AF_UNIX (local communication) (#include <sys/un.h>)
        PF_XXX: PF_INET(protocol family internet IPv4), PF_INET6 (protocol family internet IPv6)
        AF_XXX: AF_INET (address family internet IPv4), AF_INET6 (address family internet IPv6) (typically used)

    //type: defines socket type
        SOCK_STREAM -> TCP (Transmission Control Protocol)
        - reliable byte stream channel (in order, all arrive, no duplicates)
        - connection-oriented
        - bidirectional

        SOCK_DGRAM -> UDP (User Datagram Protocol)
        - out of order, duplicates possible
        - connectionless (faster)

    //protocol: network protocols are formal standards and policies comprised of rules and formats that define the communication between two or more devices over the network.
        (define here when there is any additional protocal. Otherwise define it as 0)

NB: computer (IP address) -> mobile (phone number) 
    to identify a specific process we need its port number 
    server and client need to have the same port number to communicate.

2. Bind a socket: associates and reserves a port for use by the socket
    Sockets dont have a complete address at the beginning

    int bind(int _fd, _CONST_SOCKADDR_ARG _addr, socklen_t _len);

    int main()
    {
        int status = bind(fd, (struct sockaddr *)&addrport, _len);

        //fd : the socket descriptor
        //addrport : we determine the address based on the used family
        //_len : sizeof*(sockAddress);

    NB: Before bind() we need to have initialized:
        addrport.sin_family = AF_INET;
        addrport.sin_port = htons(5100);
        addrport.sin_addr.s_addr = htonl(INADDR_ANY);

    }

NB:  
- htons() : Host TO Network Short
- htonl() : Host TO Network Long

3. Await incoming connections request
    listen() Instructs TCP protocol implementation to listen for connections.

    The process of converting unconnected socket into a passive socket, indicating that the kernal should accept incomming connections requests directed to this socket.

    int     status = listen(int _fd, int _n);

    //_fd : socket descriptor
    //_n : queue length, number of active participants that can "wait" for a connection.

    //status : 0 if listening -1 if error

    NB:
        listen() is non-blocking: returns immediately.
        Is used by the server only as a way to get new sockets. 

4. Connect to a server
    The client establishes a connection with the server by calling connect()
    
    To make a connection request just specify the address to Connect to and the socket descriptor

    int     connect(int _fd, const struct sockaddr * _addr, socklen_t _len);

    // _fd : socket descriptor 
    //_addr : the (IP) address and port of the machine.
    //_len : the size (in bytes) of the addrport structure

    NB: connect() is blocking

5. Write/Read data from the server

    int     send(int _fd, const void * _buf, size_t _n, int _flags);
    int     recv(int _fd, const void * _buf, size_t _n, int _flags);

    //_buf : array of characters containing a message to be transmitted or received
    //_n : length of the transmitted message / size of buffer
    //_flags : usually 0

    send() and recv() are blocking returns only after data is sent/ received

6. Accept the connection Request
    The server gets a socket for an incoming client connection by calling accept():

    Transition of the connection request from listen() method to an actual socket. (accept the connection request).
    After accepting the request, the data can be finally transfered between the nodes.

    int     accept(int _fd, struct sockaddr* _addr, socklen_t* client_addr_len);
    //return integer the new socket (used for data transfer)

    int main()
    {
        int s = accept(server_fd, (struct sockadd*)&client_addr, &_addr_len);

        //server_fd : server socket descriptor;
        //client_addr : where the address of the connecting socket shall be returned.
        //client_addr_len : the sizeof(_addr);

        NB: is blocking: waits for connection before returning.
            dequeues the next connection on the queue for socket (sockid)
    This function creates a new socket in case of success as the server will become passive, the new socket allows to send to client.
    }




# Ressources:
1. Beej’s Guide to Network Programming
(https://beej.us/guide/bgnet/pdf/bgnet_a4_c_1.pdf)

2. Socket Programming Using C language
(https://www.youtube.com/watch?v=CcyOq7p0LhE&list=PLOxPIrpPpCcsO9fCjxLveALSvel5azMOB&index=2)

3. Modèle Client-Serveur MQTT
(https://largo.lip6.fr/trac/sesi-peri/chrome/site/cours/IOC_C06_TCPIP-2p.pdf)

# AI Use:
1. To briefly explain subjet
2. To recommand ressources to read and watch
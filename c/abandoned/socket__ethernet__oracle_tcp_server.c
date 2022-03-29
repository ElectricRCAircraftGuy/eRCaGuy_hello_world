/*
This file is part of eRCaGuy_hello_world:
https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

See Oracle: Socket Tutorial: https://docs.oracle.com/cd/E19620-01/805-4041/6j3r8iu2l/index.html
"Example 2-2 Accepting an Internet Stream Connection (Server)"

STATUS: works, but has a ton of compilation warnings. Is *essentially* stock, from the link above,
except I added a missing parenthesis and `#include <stdlib.h> `.

To compile and run (assuming you've already `cd`ed into this dir):
1. In C:
```bash
# NB: I HAD TO REMOVE `-Werror` to make it compile! Put it back!
gcc -Wall -Wextra -O3 -std=c17 socket__ethernet__oracle_tcp_server.c -o bin/server -lm && bin/server
```
2. In C++
```bash
g++ -Wall -Wextra -Werror -O3 -std=c++17 socket__ethernet__oracle_tcp_server.c -o bin/server && bin/server
```

References:
1. Oracle: Socket Tutorial: https://docs.oracle.com/cd/E19620-01/805-4041/6j3r8iu2l/index.html
   "Example 2-2 Accepting an Internet Stream Connection (Server)"

*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>  // `exit()`

#define TRUE 1

/*
* This program creates a socket and then begins an infinite loop.
* Each time through the loop it accepts a connection and prints
* data from it. When the connection breaks, or the client closes
* the connection, the program accepts a new connection.
*/

main()
{
   int sock, length;
   struct sockaddr_in server;
   int msgsock;
   char buf[1024];
   int rval;

   /* Create socket. */
   sock = socket(AF_INET, SOCK_STREAM, 0);
   if (sock == -1) {
      perror("opening stream socket");
      exit(1);
   }
   /* Bind socket using wildcards.*/
   server.sin_family = AF_INET;
   server.sin_addr.s_addr = INADDR_ANY;
   server.sin_port = 0;
   if (bind(sock, (struct sockaddr *) &server, sizeof server)
         == -1) {
      perror("binding stream socket");
      exit(1);
   }
   /* Find out assigned port number and print it out. */
   length = sizeof server;
   if (getsockname(sock,(struct sockaddr *) &server,&length)
         == -1) {
      perror("getting socket name");
      exit(1);
   }
   printf("Socket port #%d\n", ntohs(server.sin_port));
   /* Start accepting connections. */
   listen(sock, 5);
   do {
      msgsock = accept(sock,(struct sockaddr *) 0,(int *) 0);
      if (msgsock == -1)
         perror("accept");
      else do {
         memset(buf, 0, sizeof buf);
         if ((rval = read(msgsock,buf, 1024)) == -1)
            perror("reading stream message");
         if (rval == 0)
            printf("Ending connection\n");
         else
            /* assumes the data is printable */
            printf("-->%s\n", buf);
      } while (rval > 0);
      close(msgsock);
   } while(TRUE);
   /*
    * Since this program has an infinite loop, the socket "sock" is
    * never explicitly closed. However, all sockets will be closed
    * automatically when a process is killed or terminates normally.
    */
   exit(0);
}

/*
SAMPLE OUTPUT:

In C:

    eRCaGuy_hello_world/c$ gcc -Wall -Wextra -O3 -std=c17 socket__ethernet__oracle_tcp_server.c -o bin/a -lm && bin/a
    socket__ethernet__oracle_tcp_server.c:43:1: warning: return type defaults to ‘int’ [-Wimplicit-int]
     main()
     ^~~~
    socket__ethernet__oracle_tcp_server.c: In function ‘main’:
    socket__ethernet__oracle_tcp_server.c:68:53: warning: pointer targets in passing argument 3 of ‘getsockname’ differ in signedness [-Wpointer-sign]
        if (getsockname(sock,(struct sockaddr *) &server,&length)
                                                         ^~~~~~~
    In file included from socket__ethernet__oracle_tcp_server.c:28:
    /usr/include/x86_64-linux-gnu/sys/socket.h:116:12: note: expected ‘socklen_t * restrict’ {aka ‘unsigned int * restrict’} but argument is of type ‘int *’
     extern int getsockname (int __fd, __SOCKADDR_ARG __addr,
                ^~~~~~~~~~~
    socket__ethernet__oracle_tcp_server.c:77:51: warning: pointer targets in passing argument 3 of ‘accept’ differ in signedness [-Wpointer-sign]
           msgsock = accept(sock,(struct sockaddr *) 0,(int *) 0);
                                                       ^~~~~~~~~
    In file included from socket__ethernet__oracle_tcp_server.c:28:
    /usr/include/x86_64-linux-gnu/sys/socket.h:232:12: note: expected ‘socklen_t * restrict’ {aka ‘unsigned int * restrict’} but argument is of type ‘int *’
     extern int accept (int __fd, __SOCKADDR_ARG __addr,
                ^~~~~~
    socket__ethernet__oracle_tcp_server.c:81:10: warning: implicit declaration of function ‘memset’ [-Wimplicit-function-declaration]
              memset(buf, 0, sizeof buf);
              ^~~~~~
    socket__ethernet__oracle_tcp_server.c:81:10: warning: incompatible implicit declaration of built-in function ‘memset’
    socket__ethernet__oracle_tcp_server.c:81:10: note: include ‘<string.h>’ or provide a declaration of ‘memset’
    socket__ethernet__oracle_tcp_server.c:33:1:
    +#include <string.h>

    socket__ethernet__oracle_tcp_server.c:81:10:
              memset(buf, 0, sizeof buf);
              ^~~~~~
    socket__ethernet__oracle_tcp_server.c:82:22: warning: implicit declaration of function ‘read’; did you mean ‘fread’? [-Wimplicit-function-declaration]
              if ((rval = read(msgsock,buf, 1024)) == -1)
                          ^~~~
                          fread
    socket__ethernet__oracle_tcp_server.c:90:7: warning: implicit declaration of function ‘close’; did you mean ‘fclose’? [-Wimplicit-function-declaration]
           close(msgsock);
           ^~~~~
           fclose
    Socket port #39113



OR, in C++:

    eRCaGuy_hello_world/c$ g++ -Wall -Wextra -Werror -O3 -std=c++17 socket__ethernet__oracle_tcp_server.c -o bin/a && bin/a
    Hello World.


*/

/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
Mar. 2022

Simple UDP server from: https://www.binarytides.com/programming-udp-sockets-c-linux/. Let's fix all
the compile errors and clean up the code.
---------------------------------------------------------------
CODE FLOW: socket() -> bind() -> recvfrom() -> sendto()
---------------------------------------------------------------

STATUS: wip

To compile and run (assuming you've already `cd`ed into this dir):
1. In C:
```bash
gcc -Wall -Wextra -Werror -O3 -std=c17 socket__ethernet__udp_binarytides_simple_udp_server_GS_edit.c -o bin/a -lm && bin/a
```
2. In C++
```bash
g++ -Wall -Wextra -Werror -O3 -std=c++17 socket__ethernet__udp_binarytides_simple_udp_server_GS_edit.c -o bin/a && bin/a
```

References:
1. *****https://www.binarytides.com/programming-udp-sockets-c-linux/
1. Oracle:
   1. What Are Sockets?: https://docs.oracle.com/cd/E19620-01/805-4041/6j3r8iu2k/index.html
   1. *****[LOOKS REALLY USEFUL!] Oracle "Socket Tutorial":
      https://docs.oracle.com/cd/E19620-01/805-4041/6j3r8iu2l/index.html
   1. *****Advanced Topics: https://docs.oracle.com/cd/E19620-01/805-4041/6j3r8iu2o/index.html
      Ex:
      1. Asynchronous IO
      1. Signals (interrupt-driven IO) to notify when sending is complete, etc.
======
1. [my answer] What is SOCK_DGRAM and SOCK_STREAM?: https://stackoverflow.com/a/71417876/4561887
1. ***** Google search for "Ethernet sockets demo in c":
   https://www.google.com/search?q=Ethernet+sockets+demo+in+c&oq=Ethernet+sockets+demo+in+c&aqs=chrome..69i57.156j0j9&sourceid=chrome&ie=UTF-8
    1. *****+ LOOKS LIKE THE BEST DEMO!: https://people.cs.rutgers.edu/~pxk/rutgers/notes/sockets/
    1. LOOKS LIKE A GREAT DEMO!:
       https://www.codeproject.com/Articles/586000/Networking-and-Socket-Programming-Tutorial-in-C
    1. https://www.csd.uoc.gr/~hy556/material/tutorials/cs556-3rd-tutorial.pdf
    1. Looks very useful!: https://www.geeksforgeeks.org/socket-programming-cc/
------
1. How to Code Raw Sockets in C on Linux: https://www.binarytides.com/raw-sockets-c-code-linux/
1. Google search for "linux socket ethernet packet example":
   https://www.google.com/search?q=linux+socket+ethernet+packet+example&oq=linux+socket+ethernet+packet+example&aqs=chrome..69i57.8472j0j4&sourceid=chrome&ie=UTF-8
    1. sendRawEth.c: Send a raw Ethernet frame in Linux:
       https://gist.github.com/austinmarton/1922600
------
1. https://linux.die.net/man/7/ip
1. https://linux.die.net/man/7/socket
1. https://linux.die.net/man/7/udp
1. https://www.ibm.com/docs/en/aix/7.1?topic=s-socket-subroutine
1. https://www.ibm.com/docs/en/aix/7.1?topic=domains-address-families
1. https://www.ibm.com/docs/en/aix/7.1?topic=protocols-socket-types
1. https://www.ibm.com/docs/en/aix/7.1?topic=s-send-subroutine
1. https://linux.die.net/man/3/htonl: convert hostlong type from host byte order to network
   byte order
1. https://en.wikipedia.org/wiki/List_of_TCP_and_UDP_port_numbers


*/


#include<stdio.h>       // `printf()`
#include<string.h>      // `memset()`
#include<stdlib.h>      // `exit()`
#include<arpa/inet.h>   // `htonl()`
#include<sys/socket.h>

#define BUFLEN 512   //Max length of buffer
#define PORT 8888 //The port on which to listen for incoming data

void die(char *s)
{
   perror(s);
   exit(1);
}

int main(void)
{
   struct sockaddr_in si_me, si_other;

   int s, i, slen = sizeof(si_other) , recv_len;
   char buf[BUFLEN];

   //create a UDP socket
   if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
   {
      die("socket");
   }

   // zero out the structure
   memset((char *) &si_me, 0, sizeof(si_me));

   si_me.sin_family = AF_INET;
   si_me.sin_port = htons(PORT);
   si_me.sin_addr.s_addr = htonl(INADDR_ANY);

   //bind socket to port
   if( bind(s , (struct sockaddr*)&si_me, sizeof(si_me) ) == -1)
   {
      die("bind");
   }

   //keep listening for data
   while(1)
   {
      printf("Waiting for data...");
      fflush(stdout);

      //try to receive some data, this is a blocking call
      if ((recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen)) == -1)
      {
         die("recvfrom()");
      }

      //print details of the client/peer and the data received
      printf("Received packet from %s:%d\n", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));
      printf("Data: %s\n" , buf);

      //now reply the client with the same data
      if (sendto(s, buf, recv_len, 0, (struct sockaddr*) &si_other, slen) == -1)
      {
         die("sendto()");
      }
   }

   close(s);
   return 0;
}

/*
SAMPLE OUTPUT:

In C:

   eRCaGuy_hello_world/c/TODO$ gcc -Wall -Wextra -O3 -std=c17 socket__ethernet__udp_binarytides_simple_udp_server_GS_edit.c -o bin/a -lm && bin/a
   socket__ethernet__udp_binarytides_simple_udp_server_GS_edit.c: In function ‘main’:
   socket__ethernet__udp_binarytides_simple_udp_server_GS_edit.c:78:82: warning: pointer targets in passing argument 6 of ‘recvfrom’ differ in signedness [-Wpointer-sign]
          if ((recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen)) == -1)
                                                                                     ^~~~~
   In file included from /usr/include/x86_64-linux-gnu/sys/socket.h:269,
                    from /usr/include/netinet/in.h:23,
                    from /usr/include/arpa/inet.h:22,
                    from socket__ethernet__udp_binarytides_simple_udp_server_GS_edit.c:33:
   /usr/include/x86_64-linux-gnu/bits/socket2.h:64:1: note: expected ‘socklen_t * restrict’ {aka ‘unsigned int * restrict’} but argument is of type ‘int *’
    recvfrom (int __fd, void *__restrict __buf, size_t __n, int __flags,
    ^~~~~~~~
   socket__ethernet__udp_binarytides_simple_udp_server_GS_edit.c:94:4: warning: implicit declaration of function ‘close’; did you mean ‘fclose’? [-Wimplicit-function-declaration]
       close(s);
       ^~~~~
       fclose
   socket__ethernet__udp_binarytides_simple_udp_server_GS_edit.c:49:11: warning: unused variable ‘i’ [-Wunused-variable]
       int s, i, slen = sizeof(si_other) , recv_len;
              ^
   Waiting for data...




OR, in C++:




*/

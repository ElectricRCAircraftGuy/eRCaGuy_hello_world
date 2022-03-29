/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

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
1. [my answer] What is SOCK_DGRAM and SOCK_STREAM?: https://stackoverflow.com/a/71417876/4561887

*/


#include<stdio.h>       // `printf()`
#include<string.h>      // `memset()`
#include<stdlib.h>      // `exit()`
#include<arpa/inet.h>
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

/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

Simple UDP client from: https://www.binarytides.com/programming-udp-sockets-c-linux/
Run the **C** cmd below!
---------------------------------------------------------------
CODE FLOW: socket() -> sendto()/recvfrom()
---------------------------------------------------------------

STATUS: the code is buggy as-is, and has a bunch of compilation warnings, but it does work!

To compile and run (assuming you've already `cd`ed into this dir):
1. In C:
```bash
# NB: add `-Werror` back in for safety! I removed it so it would compile as-is.
gcc -Wall -Wextra -O3 -std=c17 socket__ethernet__udp_binarytides_simple_udp_client.c -o bin/a -lm && bin/a
```
2. In C++
```bash
g++ -Wall -Wextra -Werror -O3 -std=c++17 socket__ethernet__udp_binarytides_simple_udp_client.c -o bin/a && bin/a
```

References:
1. *****https://www.binarytides.com/programming-udp-sockets-c-linux/
1. [my answer] What is SOCK_DGRAM and SOCK_STREAM?: https://stackoverflow.com/a/71417876/4561887
*/


/*
   Simple udp client
*/
#include<stdio.h> //printf
#include<string.h> //memset
#include<stdlib.h> //exit(0);
#include<arpa/inet.h>
#include<sys/socket.h>

#define SERVER "127.0.0.1"
#define BUFLEN 512   //Max length of buffer
#define PORT 8888 //The port on which to send data

void die(char *s)
{
   perror(s);
   exit(1);
}

int main(void)
{
   struct sockaddr_in si_other;
   int s, i, slen=sizeof(si_other);
   char buf[BUFLEN];
   char message[BUFLEN];

   if ( (s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
   {
      die("socket");
   }

   memset((char *) &si_other, 0, sizeof(si_other));
   si_other.sin_family = AF_INET;
   si_other.sin_port = htons(PORT);

   if (inet_aton(SERVER , &si_other.sin_addr) == 0)
   {
      fprintf(stderr, "inet_aton() failed\n");
      exit(1);
   }

   while(1)
   {
      printf("Enter message : ");
      gets(message);

      //send the message
      if (sendto(s, message, strlen(message) , 0 , (struct sockaddr *) &si_other, slen)==-1)
      {
         die("sendto()");
      }

      //receive a reply and print it
      //clear the buffer by filling null, it might have previously received data
      memset(buf,'\0', BUFLEN);
      //try to receive some data, this is a blocking call
      if (recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen) == -1)
      {
         die("recvfrom()");
      }

      puts(buf);
   }

   close(s);
   return 0;
}

/*
SAMPLE OUTPUT:

In C:

   eRCaGuy_hello_world/c/TODO$ gcc -Wall -Wextra -O3 -std=c17 socket__ethernet__udp_binarytides_simple_udp_client.c -o bin/a -lm && bin/a
   socket__ethernet__udp_binarytides_simple_udp_client.c: In function ‘main’:
   socket__ethernet__udp_binarytides_simple_udp_client.c:64:8: warning: implicit declaration of function ‘inet_aton’; did you mean ‘inet_pton’? [-Wimplicit-function-declaration]
       if (inet_aton(SERVER , &si_other.sin_addr) == 0)
           ^~~~~~~~~
           inet_pton
   socket__ethernet__udp_binarytides_simple_udp_client.c:73:7: warning: implicit declaration of function ‘gets’; did you mean ‘fgets’? [-Wimplicit-function-declaration]
          gets(message);
          ^~~~
          fgets
   socket__ethernet__udp_binarytides_simple_udp_client.c:85:70: warning: pointer targets in passing argument 6 of ‘recvfrom’ differ in signedness [-Wpointer-sign]
          if (recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen) == -1)
                                                                         ^~~~~
   In file included from /usr/include/x86_64-linux-gnu/sys/socket.h:269,
                    from /usr/include/netinet/in.h:23,
                    from /usr/include/arpa/inet.h:22,
                    from socket__ethernet__udp_binarytides_simple_udp_client.c:35:
   /usr/include/x86_64-linux-gnu/bits/socket2.h:64:1: note: expected ‘socklen_t * restrict’ {aka ‘unsigned int * restrict’} but argument is of type ‘int *’
    recvfrom (int __fd, void *__restrict __buf, size_t __n, int __flags,
    ^~~~~~~~
   socket__ethernet__udp_binarytides_simple_udp_client.c:93:4: warning: implicit declaration of function ‘close’; did you mean ‘fclose’? [-Wimplicit-function-declaration]
       close(s);
       ^~~~~
       fclose
   socket__ethernet__udp_binarytides_simple_udp_client.c:51:11: warning: unused variable ‘i’ [-Wunused-variable]
       int s, i, slen=sizeof(si_other);
              ^
   /tmp/ccrdmMYG.o: In function `main':
   socket__ethernet__udp_binarytides_simple_udp_client.c:(.text.startup+0xea): warning: the `gets' function is dangerous and should not be used.
   Enter message :





OR, in C++:




*/

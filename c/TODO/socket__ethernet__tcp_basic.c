/*


References:
1. [my answer] What is SOCK_DGRAM and SOCK_STREAM?: https://stackoverflow.com/a/71417876/4561887
   - see also the tons of references and links at the bottom of this answer!
1. https://linux.die.net/man/7/ip
1. How to Code Raw Sockets in C on Linux: https://www.binarytides.com/raw-sockets-c-code-linux/


*/


// See: https://linux.die.net/man/7/ip
#define SOCKET_TCP              AF_INET, SOCK_STREAM, 0
#define SOCKET_UDP              AF_INET, SOCK_DGRAM, 0
#define SOCKET_RAW(protocol)    AF_INET, SOCK_RAW, (protocol)

// Usage examples:

int socket_tcp = socket(SOCKET_TCP);
int socket_udp = socket(SOCKET_UDP);
// See also: https://www.binarytides.com/raw-sockets-c-code-linux/
int socket_raw = socket(SOCKET_RAW(IPPROTO_RAW));


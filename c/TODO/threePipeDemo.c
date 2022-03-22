/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

Copied from Matt Lewis:
mplewis/threePipeDemo.c - https://gist.github.com/mplewis/5279108

(description)
STATUS: DOES NOT COMPILE. I need to put a lot of time into this to understand and fix it.

To compile and run (assuming you've already `cd`ed into this dir):
1. In C:
```bash
gcc -Wall -Wextra -Werror -O3 -std=c17 threePipeDemo.c -o bin/a -lm && bin/a
```
2. In C++
```bash
g++ -Wall -Wextra -Werror -O3 -std=c++17 threePipeDemo.c -o bin/a && bin/a
```

References:
1. *****++ BEGIN BY STUDYING THIS!: 6.2.2 Creating Pipes in C: https://tldp.org/LDP/lpg/node11.html
  1. The link above is from this answer: https://stackoverflow.com/a/12033216/4561887
1. *****++ my comment and links:
   https://gist.github.com/mplewis/5279108?permalink_comment_id=4099186#gistcomment-4099186
1. *****++ EXCELLENT EXAMPLE HERE: https://man7.org/linux/man-pages/man2/pipe.2.html
1. *****+
   > RETURN VALUE
       On success, the PID of the child process is returned in the
       parent, and 0 is returned in the child.  On failure, -1 is
       returned in the parent, no child process is created, and errno is
       set to indicate the error.
  From: https://man7.org/linux/man-pages/man2/fork.2.html and
        https://linux.die.net/man/2/fork
  Code usage example here: https://pubs.opengroup.org/onlinepubs/9699919799/ <==========
1. *****+ [NEED TO STUDY & READ!] https://gist.github.com/mplewis/5279108
  1. *****+ This comment and its links:
     https://gist.github.com/mplewis/5279108?permalink_comment_id=2350290#gistcomment-2350290
1. https://stackoverflow.com/questions/12032323/piping-the-output-of-one-command-as-input-to-another-command#comment16060852_12032323
  1. ***** https://pubs.opengroup.org/onlinepubs/009604599/functions/pipe.html
1. https://unix.stackexchange.com/questions/148401/how-pipes-work-in-linux
1.

*/

// This program is an example of how to run a command such as
// ps aux | grep root | grep sbin
// using C and Unix.

#include <stdlib.h>
#include <unistd.h>

int pid;
int pipe1[2];
int pipe2[2];

void main() {

  // create pipe1
  if (pipe(pipe1) == -1) {
    perror("bad pipe1");
    exit(1);
  }

  // fork (ps aux)
  if ((pid = fork()) == -1) {
    perror("bad fork1");
    exit(1);
  } else if (pid == 0) {
    // stdin --> ps --> pipe1
    exec1();
  }
  // parent

  // create pipe2
  if (pipe(pipe2) == -1) {
    perror("bad pipe2");
    exit(1);
  }

  // fork (grep root)
  if ((pid = fork()) == -1) {
    perror("bad fork2");
    exit(1);
  } else if (pid == 0) {
    // pipe1 --> grep --> pipe2
    exec2();
  }
  // parent

  // close unused fds
  close(pipe1[0]);
  close(pipe1[1]);

  // fork (grep sbin)
  if ((pid = fork()) == -1) {
    perror("bad fork3");
    exit(1);
  } else if (pid == 0) {
    // pipe2 --> grep --> stdout
    exec3();
  }
  // parent


}


void exec1() {
  // input from stdin (already done)
  // output to pipe1
  dup2(pipe1[1], 1);
  // close fds
  close(pipe1[0]);
  close(pipe1[1]);
  // exec
  execlp("ps", "ps", "aux", NULL);
  // exec didn't work, exit
  perror("bad exec ps");
  _exit(1);
}

void exec2() {
  // input from pipe1
  dup2(pipe1[0], 0);
  // output to pipe2
  dup2(pipe2[1], 1);
  // close fds
  close(pipe1[0]);
  close(pipe1[1]);
  close(pipe2[0]);
  close(pipe2[1]);
  // exec
  execlp("grep", "grep", "root", NULL);
  // exec didn't work, exit
  perror("bad exec grep root");
  _exit(1);
}

void exec3() {
  // input from pipe2
  dup2(pipe2[0], 0);
  // output to stdout (already done)
  // close fds
  close(pipe2[0]);
  close(pipe2[1]);
  // exec
  execlp("grep", "grep", "sbin", NULL);
  // exec didn't work, exit
  perror("bad exec grep sbin");
  _exit(1);
}

/*
SAMPLE OUTPUT:

In C:

    eRCaGuy_hello_world/c$ gcc -Wall -Wextra -Werror -O3 -std=c17 threePipeDemo.c -o bin/a -lm && bin/a
    Hello World.


OR, in C++:

    eRCaGuy_hello_world/c$ g++ -Wall -Wextra -Werror -O3 -std=c++17 threePipeDemo.c -o bin/a && bin/a
    Hello World.


*/

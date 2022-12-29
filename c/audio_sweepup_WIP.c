/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

Try doing an audio frequency sweep.
Originally copied from: http://manuals.opensound.com/developer/sweepup.c.html

STATUS: wip

To compile and run (assuming you've already `cd`ed into this dir):
1. In C:
```bash
gcc -Wall -Wextra -Werror -O3 -std=c17 sweepup.c -o bin/a && bin/a
```
2. In C++
```bash
g++ -Wall -Wextra -Werror -O3 -std=c++17 sweepup.c -o bin/a && bin/a
```

References:
1. http://manuals.opensound.com/developer/sweepup.c.html <=======
    1.


eRCaGuy_hello_world/c$ gcc -Wall -Wextra -Werror -O3 -std=c17 sweepup.c -o bin/a && bin/a
sweepup.c:27:10: fatal error: soundcard.h: No such file or directory
 #include <soundcard.h>
          ^~~~~~~~~~~~~
compilation terminated.

--> sudo aptitude install libasound2-dev



*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <soundcard.h>

char *dspname = "/dev/dsp";

int fd;

int
main (int argc, char *argv[])
{
  int bits, channels, speed, tmp;
  int i, l, n;
#define BUFFSIZE    (64*1024)
  short buf[BUFFSIZE];
  int p, t;
  double freq = 10.0 /* Hz */ , phase = 0.0;
  int delay = 0;

  if (argc > 1)
    dspname = argv[1];

  if (argc > 2)
    delay = atoi (argv[2]);

  if ((fd = open (dspname, O_WRONLY, 0)) == -1)
    {
      perror (dspname);
      exit (-1);
    }

  speed = 48000;
  channels = 2;
  bits = AFMT_S16_NE;

  if (ioctl (fd, SNDCTL_DSP_CHANNELS, &channels) == -1)
    {
      perror ("SNDCTL_DSP_CHANNELS");
      exit (-1);
    }

  if (ioctl (fd, SNDCTL_DSP_SETFMT, &bits) == -1)
    {
      perror ("SNDCTL_DSP_SETFMT");
      exit (-1);
    }

  if (bits != AFMT_S16_NE)
    {
      fprintf (stderr,
           "Device %s doesn't support 16 bit (native endian) format\n",
           dspname);
      exit (-1);
    }

  if (ioctl (fd, SNDCTL_DSP_SPEED, &speed) == -1)
    {
      perror ("SNDCTL_DSP_SPEED");
      exit (-1);
    }

  fprintf (stderr, "Outputting sweep at %d Hz, %d channels, 16 bits\n", speed,
       channels);

  n = 0;
  p = 0;

  while (1)         /* Infinite loop */
    {
      int v;
      double step;

      v = sin (phase) * 16483.0;

      for (i = 0; i < channels; i++)
    {
      buf[p++] = v;

      if (p >= BUFFSIZE)
        {
//            write (1, buf, p * 2);

          if (write (fd, buf, p * 2) != p * 2)
        {
          perror ("write");
          exit (-1);
        }
          if (delay > 0)
        usleep (delay * 1000);
          fprintf (stderr, "\r%d ", (int) (freq));
          fflush (stderr);
          p = 0;
        }
    }

      step = 2.0 * M_PI * freq / (double) speed;

      phase += step;

      if (freq < (double) speed / 2.1)
    freq *= 1.000002;
      else
    break;
    }

  fprintf (stderr, "\n");
  if (p > 0)
    write (fd, buf, p * 2);

  exit (0);
}


/*
SAMPLE OUTPUT:

In C:

    eRCaGuy_hello_world/c$ gcc -Wall -Wextra -Werror -O3 -std=c17 sweepup.c -o bin/a && bin/a
    Hello World.


OR, in C++:

    eRCaGuy_hello_world/c$ g++ -Wall -Wextra -Werror -O3 -std=c++17 sweepup.c -o bin/a && bin/a
    Hello World.


*/

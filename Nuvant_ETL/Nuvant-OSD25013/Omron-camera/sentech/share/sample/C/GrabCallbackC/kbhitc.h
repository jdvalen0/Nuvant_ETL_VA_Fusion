/**
 Linux (POSIX) implementation of _kbhit().
 Modification of the original code of Morgan McGuire, morgan@cs.brown.edu
 */
#include <stdio.h>
#include <sys/select.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

int _kbhit() {
    static const int STDIN = 0;
    static char initialized = 0;

    if (0 == initialized) {
        /* Use termios to turn off line buffering */
        struct termios term;
        tcgetattr(STDIN, &term);
        term.c_lflag &= ~ICANON;
        tcsetattr(STDIN, TCSANOW, &term);
        setbuf(stdin, NULL);
        initialized = 1;
    }

    int bytesWaiting;
    ioctl(STDIN, FIONREAD, &bytesWaiting);
    return bytesWaiting;
}


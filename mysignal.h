#include <signal.h>

typedef void Sigfunc(int);
Sigfunc *signal(int signo, Sigfunc *func);

void myp(int signo);
void run_signal(void);
void sig_chld(int signo);

void run_signal_usr(void);
void run_my_alarm(void);
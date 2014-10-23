#include<stdio.h>
#include<stddef.h>
#include<signal.h>
#define timespec linux_timespec
#include<linux/time.h>
#undef timespec

struct itimerval old;
struct itimerval new;
 
void catch_alarm (int sig)
{
  //keep_going = 0;
  printf("Alarm event\n");
  signal (sig, catch_alarm);
}
void HandleCtrlC(int signum){
	signal(SIGALRM, SIG_IGN);
	signal(signum, HandleCtrlC);
}

 
int main(void)
{
  signal (SIGALRM, catch_alarm);
  signal(SIGINT, HandleCtrlC);
  new.it_interval.tv_sec = 1;
  new.it_interval.tv_usec = 500000;
  new.it_value.tv_sec = 1;
  new.it_value.tv_usec = 500000;
   
  old.it_interval.tv_sec = 0;
  old.it_interval.tv_usec = 0;
  old.it_value.tv_sec = 0;
  old.it_value.tv_usec = 0;
   
  if (setitimer (ITIMER_REAL, &new, &old) < 0)
      printf("timer init failed\n");
  else
      printf("timer init succeeded\n");
  while(1) {sleep(2);printf("Hi");}
return 0;
}

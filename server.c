#include <unistd.h> //Can remove later and replace with libft.
#include <stdio.h>
#include <signal.h>

void sigusr1_handler(int signum)
{

}

int main (void)
{
	int srv_pid;

	srv_pid = getpid();
	printf("%i\n", srv_pid);

	signal(SIGUSR1, sigusr1_handler);
}
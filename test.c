#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>

char	*c;

int	main(void)
{
	int	pid;
	int	d;

	c = malloc(sizeof(char));
	*c = 'a';
	printf("parents %p %c\n", c, *c);
	pid = fork();
	if (!pid)
	{
		printf("child %p %c\n", c, *c);
		free(c);
		exit(0);
	}
	waitpid(pid, NULL, 0);
	printf("parents %p %c\n", c, *c);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engooh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 12:15:29 by engooh            #+#    #+#             */
/*   Updated: 2022/07/05 13:55:21 by engooh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

/*void	handler(int signum)
{
	printf("End processs\n");
	exit(0);
}

int	main(void)
{
	int			pid;
	struct sigaction	act = {0};

	act.sa_handler = &handler;
	sigaction(SIGINT, &act, NULL);
	while (42)
		printf("Welcome to child process\n");
	return (0);
}*/


/*void	advenced_handler(int signum, siginfo_t *info, void *arg)
{
	printf("signal: %d, This is end process\n", signum);
	exit(0);
}

int	main(void)
{
	int			pid;
	struct sigaction	act = {0};

	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = &advenced_handler;
	sigaction(SIGINT, &act, NULL);
	while (42)
		printf("Welcome to child process\n");
	return (0);
}*/

void	ensemble_signaux(int signum, siginfo_t *info, void *arg)
{
	printf("signal: %d", signum);
}

int	main(void)
{
	struct sigaction	act = {0};
	sigset_t sigset; // ensemble de signaux

	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = &ensemble_signaux;
	//sigemptyset(&act.sa_mask);
	//sigaddset(&sigset, SIGCONT);
	sigaction(SIGINT, &act, NULL); // durant la gestion de SIGINT SIGCONT sera blocker
	while (42)
		printf("Welcome to process\n");
	return (0);
}

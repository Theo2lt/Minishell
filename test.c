/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: engooh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 14:24:16 by engooh            #+#    #+#             */
/*   Updated: 2022/08/19 15:15:06 by engooh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <wait.h>

int	main(void)
{
	int		fd;
	int		pid;
	char	*buf;

	buf = NULL;
	fd = open("./tmp", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
	if (fd == -1)
		return (1);
	//printf("before fd %d\n", fd);
	//printf("error write %s\n", strerror(errno));
	pid = fork();
	if (!pid)
	{
		printf("res write == %d\n", (int)write(fd, "hello la terre", 14));
		//close(fd);
		exit(0);
	}
	waitpid(pid, NULL, 0);
	printf("read == %d\n", (int)read(fd, buf, 14));
	//printf("error read %s\n", strerror(errno));
	printf("resultat %s\n", buf);
	//printf("after fd %d\n", fd);
=======
/*   By: engooh <engooh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 12:38:35 by engooh            #+#    #+#             */
/*   Updated: 2022/08/08 12:46:49 by engooh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

void *ft_function(void)
{
	int nbr;

	nbr = 4;
}

int main(void)
{
	char	*content;
	int	nbr;
	int	nbr1;

	nbr = 3;
	nbr1 = 5;
	printf("test %d, %d\n", nbr, nbr + (8 * 4));
>>>>>>> 09b6f6ff88e84cc7ac8e1ebbb102a06af2885634
	return (0);
}

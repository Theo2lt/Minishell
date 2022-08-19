/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
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
	return (0);
}

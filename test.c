/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engooh <engooh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 20:15:37 by engooh            #+#    #+#             */
/*   Updated: 2022/07/30 21:07:21 by engooh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>

int	print(int *str)
{
	int	i;

	i = 0;
	while (str[i * sizeof(char)])
	{
		printf("%c ", str[i]);
		i++;
	}
	printf("%c ", str[1]);
	printf("%c", str[2]);
	//printf("%c ", str[2]);
	//printf("%c ", str[3]);
	//printf("%c ", str[5]);
	/*
	while (*str)
		printf("%c\n", (char)*(str++));
		*/
	return (0);
}

int	main(void)
{
	print((int *)"hello");
	return (0);
}

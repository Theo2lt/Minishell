/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engooh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 13:07:34 by engooh            #+#    #+#             */
/*   Updated: 2022/07/06 13:11:25 by engooh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _XOPEN_SOURCE_EXTENDED 1
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int	main(void)
{
	printf("res = %d", ttyslot());
	return (0);
}


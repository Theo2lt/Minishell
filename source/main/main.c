/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engooh <engooh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 04:43:37 by engooh            #+#    #+#             */
/*   Updated: 2022/07/22 17:46:03 by engooh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

int	main(void)
{
	char	*input;

	while (1)
	{
		input = readline("minishell> ");
		add_history(input);
		parser(input);
	}
	return (0);
}

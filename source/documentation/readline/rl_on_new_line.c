/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_on_new_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engooh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 17:50:44 by engooh            #+#    #+#             */
/*   Updated: 2022/07/04 10:44:11 by engooh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> 
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h> 

/*
	PROTOTYPE:
				int rl_on_new_line(void);
	DEFINITION:
				Dites aux routines de mise à jour que nous sommes passés à une nouvelle ligne (vide),
				généralement après avoir sorti une nouvelle ligne.
	RETURN:
			int	
	NOTE:
*/

int	main(void)
{
	char	*input;

	while (1)
	{
		input = readline("minitest> ");
		add_history(input);
		if (!strcmp(input, "new_line"))
			rl_on_new_line();
	}
	return (0);
}

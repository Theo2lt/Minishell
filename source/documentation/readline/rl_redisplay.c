/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_redisplay.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engooh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 10:50:51 by engooh            #+#    #+#             */
/*   Updated: 2022/07/04 12:14:32 by engooh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> 
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h> 

/*
	PROTOYPE: 
			int rl_redisplay(void);
	DEFINITION:
			la fonction change se qui est afficher sur l'ecran pour pour corespondre au contene courant de rl_line_buffer 
	RETURN:
			int
	FLAGS:
			-lreadline
	NOTE:
			rien
*/

int	main(void)
{
	char	*input;

	while (1)
	{
		input = readline("minitest> ");
		add_history(input);
		if (!strcmp(input, "clear"))
			rl_clear_history();
	}
	return (0);
}

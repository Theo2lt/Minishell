/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_line_bufffer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engooh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 11:00:17 by engooh            #+#    #+#             */
/*   Updated: 2022/07/04 12:14:26 by engooh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> 
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h> 


/*
	PROTOYPE: 
			char *rl_line_bufffer(void);
	DEFINITION:
			Effacez la liste de l'historique en supprimant toutes les entrées,
			de la même manière que la clear_history()fonction de la bibliothèque Historique.
			Cela diffère de clear_historycar il libère les données privées que Readline enregistre dans la liste d'historique.
	RETURN:
			rien
	FLAGS:
			-lreadline
	NOTE:
			rien
*/


int	main(void)
{
	char	*input;
	char	*current;

	while (1)
	{
		input = readline("minitest> ");
		add_history(input);
		current = rl_line_bufffer();
		if (!strcmp(input, "clear"))
			rl_clear_history();
	}
	return (0);
}

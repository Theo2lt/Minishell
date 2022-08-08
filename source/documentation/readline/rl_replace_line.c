/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_replace_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engooh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 10:44:23 by engooh            #+#    #+#             */
/*   Updated: 2022/07/04 12:14:33 by engooh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> 
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h> 


/*
	PROTOYPE: 
			void rl_clear_history(void);
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

int main(void)
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

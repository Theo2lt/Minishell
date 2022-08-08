/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_history.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engooh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:38:03 by engooh            #+#    #+#             */
/*   Updated: 2022/06/23 14:25:51 by engooh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h> 
#include <readline/readline.h>
#include <readline/history.h> 

/* 
	PROTOTYPE:
		void add_history(const char *string);
	DEFINTION:
		add_history ajoutent chaque entre de readline dans le tampon d'historique.
		add_history permet maintenant faire défiler l'historique des commandes avec les flèches haut/bas,
		et même faire des recherches d'historique avec Ctrl+R.
	RETURN:
		rien;
	FLAGS: 
		-lreadline
	NOTE:
		si le nombre maximal d'entrées d'historique a été défini à l'aide stifle_history()
		et que le nouveau nombre d'entrées d'historique dépasse ce maximum,
		l'entrée d'historique la plus ancienne est supprimée.
*/

int	main(void)
{
	char	*input;

	while (1)
	{
		input = readline("minitest> ");
		if (input)
			add_history(input);
		if ()
	}
	return (0);
}

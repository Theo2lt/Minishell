/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engooh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 12:41:18 by engooh            #+#    #+#             */
/*   Updated: 2022/06/20 16:17:03 by engooh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h> 
#include <readline/readline.h>
#include <readline/history.h> 

/*
	PROTOTYPE:
			char	*readline(cont char *prompt);
	DEFINITION:
			readline lit l'invite de commande et la renvoie en utilisant char *prompt commme prompt.
	RETURN:
			revoin le texte lue ou NULL si EOF et rencontrer et que la ligne lue est vide.
	FLAG: 
		-lreadline 
	OUTPUT TEST:
		bash> ./a.out 
		minitest> Hello World
		Hello World
		minitest> $HOME 
		$HOME 
		minitest> echo "lulu"
		echo "lulu"
		minitest> ^C
		bash>
*/

int	main(void) 
{
	while (1)
		printf("%s\n", readline("minitest> "));
	return (0);
}

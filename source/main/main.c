/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engooh <engooh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 04:43:37 by engooh            #+#    #+#             */
/*   Updated: 2022/07/28 04:31:26 by engooh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_env	*env;
	char	*input;

	(void)ac;
	(void)av;
	env = NULL;
	ft_converte_tab_list(envp, &env, ft_push_env);
	//ft_print_env(env, 0);
	while (42)
	{
		input = readline("minishell> ");
		add_history(input);
		if (parser(input, env))
		{
			printf("input 1 %s\n", input);
			input = ft_parse_expende(input, env);
			printf("input 2 %s\n", input);
			//free(input);
		}
	}
	ft_converte_tab_list(envp, &env, ft_delete_env);
	return (0);
}

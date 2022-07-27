/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engooh <engooh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 04:43:37 by engooh            #+#    #+#             */
/*   Updated: 2022/07/27 20:25:40 by engooh           ###   ########.fr       */
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
	printf("TEST %s\n", ft_getenv(env, "HOME"));
	while (1 == 2)
	{
		input = readline("minishell> ");
		add_history(input);
		parser(input);
	}
	ft_converte_tab_list(envp, &env, ft_delete_env);
	return (0);
}

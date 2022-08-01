/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engooh <engooh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 04:43:37 by engooh            #+#    #+#             */
/*   Updated: 2022/08/01 07:11:25 by engooh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_env	*env;
	char	*input;

	(void)ac;
	(void)av;
	printf("ok\n");
	env = NULL;
	ft_converte_tab_list(envp, &env, ft_push_env);
	//ft_print_env(env, 0);
	while (42)
	{
		input = readline("minishell> ");
		if (!input)
			return (129);
		add_history(input);
		if (parser(input, env))
			free(input);
	}
	ft_converte_tab_list(envp, &env, ft_delete_env);
	return (0);
}

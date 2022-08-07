/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engooh <engooh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 04:43:37 by engooh            #+#    #+#             */
/*   Updated: 2022/08/07 07:56:20 by engooh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

void	ft_print_exec(t_exec *exec, int i)
{
	int	j;

	j = -1;
	if (exec)
	{
		printf("NBR MALLION:	%d\n", i);
		printf("INFILE		%d\n", exec->infile);
		printf("OUTFILE		%d\n", exec->outfile);
		if (exec->tabs_exeve)
			printf("CMD		%s\n", exec->tabs_exeve[++j]);
		printf("ARGUMENT	");
		while (exec->tabs_exeve && exec->tabs_exeve[++j])
			printf("%s ", exec->tabs_exeve[j]);
		printf("\n\n_____________________________\n\n");
		if (exec->next)
			ft_print_exec(exec->next, i + 1);
	}
}

t_exec	*ft_delete_exec(t_exec *exec)
{
	if (exec)
	{
		if (exec->infile > 0)
			close(exec->infile);
		if (exec->outfile > 1)
			close(exec->outfile);
		if (exec->args)
			free(exec->args);
		if (exec->tabs_exeve)
			ft_free_tab2(exec->tabs_exeve);
		if (exec->next)
			ft_delete_exec(exec->next);
		if (exec)
			free(exec);
		return (NULL);
	}
	return (NULL);
}

void	ft_delete_all(t_exec *exec, t_env *env)
{
	if (exec)
			exec = ft_delete_exec(exec);
	if (env)
		ft_converte_tab_list(NULL, &env, ft_delete_env);
}

int	main(int ac, char **av, char **envp)
{
	t_env	*env;
	t_exec	*exec;
	char	*input;

	(void)ac;
	(void)av;
	env = NULL;
	exec = NULL;
	ft_converte_tab_list(envp, &env, ft_push_env);
	while (42)
	{
		input = readline("minishell> ");
		if (!input)
			return (129);
		add_history(input);
		exec = parser(input, &exec, env);
		ft_print_exec(exec, 1);
		ft_delete_all(exec, env);
		exit(0);
		ft_delete_all(exec, NULL);
	}
	exit(0);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliot <tliot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 17:35:58 by tliot             #+#    #+#             */
/*   Updated: 2022/07/24 06:36:02 by tliot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"



char **ft_readline(void)
{
	char *cmd;
	char **cmd_arg;

	cmd_arg = NULL;
	cmd = NULL;
	cmd = readline("BOSH$> ");
	if (cmd[0])
	{
		cmd_arg = ft_split(cmd, ' ');
		add_history(cmd);
		free(cmd);
		return (cmd_arg);
	}

	return (NULL);
}

void ft_exit(t_env *lst)
{
	if (lst)
		ft_lst_env_free(lst);
	exit(0);
}

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;

	t_env *lst;
	char **cmd;
	char *exepath;
	cmd = NULL;
	lst = ft_init_env(env);
	
	/// TEST ENV CHAR ** ///
	cmd = ft_recreate_env(lst);
	if(cmd)
		cmd = ft_free_tab2(cmd);
	////// FIN DE TEST CHAR ** //////
	while (1)
	{
		cmd = ft_readline();
		if(cmd)
		{
			ft_manage_builting(cmd,&lst);
			exepath = ft_path_exec(lst,cmd);
			printf("exec : %s\n",exepath);
			
			cmd = ft_free_tab2(cmd);
			if (exepath)
				free(exepath);
		}
	}
	return (0);
}

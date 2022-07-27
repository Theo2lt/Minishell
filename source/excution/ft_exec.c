
#include "Minishell.h"


void	ft_commande_not_found(char	**cmd)
{
	ft_putstr_fd("command not found : '", 2);
	if (cmd[0])
		ft_putstr_fd(cmd[0], 2);
	ft_putstr_fd("'\n", 2);
}


void	ft_exec(t_env *lst ,char **cmd_arg)
{
	char *path;
	char **env;
	
	path = ft_path_exec(lst,cmd_arg);
	env = ft_recreate_env(lst);
	if(execve(path,cmd_arg,env) == -1)
	{
		ft_commande_not_found(cmd_arg);
		env = ft_free_tab2(env);
		cmd_arg = ft_free_tab2(cmd_arg);
		free(path);
		ft_lst_env_free(lst);
		exit(1);
	}
	exit(1);
}

#include "Minishell.h"

void    ft_execution(t_minishell *minishell)
{
	t_exec *cmd_tmp;

	cmd_tmp = minishell->exec;
	while(cmd_tmp)
	{
		cmd_tmp->pid = fork();
		if (cmd_tmp->pid == 0)
			ft_childs(minishell, cmd_tmp);
		cmd_tmp = cmd_tmp->next;
	}
}


void	ft_commande_not_found(char	**cmd)
{
	ft_putstr_fd("bash: command not found : '", 2);
	if (cmd)
		ft_putstr_fd(cmd[0], 2);
	ft_putstr_fd("'\n", 2);
}



void	ft_childs(t_minishell *minishell, t_exec *cmd_lst)
{
	if (cmd_lst->infile == -1 || cmd_lst->outfile == -1)
		ft_exit(minishell);
	if (cmd_lst->infile > 2)
		dup2(cmd_lst->infile,0);
	if (cmd_lst->outfile > 2)
		dup2(cmd_lst->outfile,1);

	ft_exec(minishell ,cmd_lst);
}

void	ft_exec(t_minishell *minishell, t_exec *cmd_lst)
{
	char *path;
	char **env;

	path = ft_path_exec(minishell->env_lst,cmd_lst->tabs_exeve);
	env = ft_recreate_env(minishell->env_lst);
	if(!cmd_lst->tabs_exeve)
	{
		ft_commande_not_found(cmd_lst->tabs_exeve);
		env = ft_free_tab2(env);
		if(path)
			free(path);
		ft_exit(minishell);
	}
	execve(path,cmd_lst->tabs_exeve,env);
	ft_putstr_fd("bash: ",2);
	ft_putstr_fd(cmd_lst->tabs_exeve[0],2);
	ft_putstr_fd(": ",2);
	ft_putstr_fd(strerror(errno),2);
	env = ft_free_tab2(env);
	if(path)
		free(path);
	ft_exit(minishell);
}

void	ft_wait_all_pid(t_exec *lst)
{
	t_exec	*lst2;

	lst2 = lst;
	while (lst2)
	{
		waitpid(lst2->pid, NULL, 0);
		lst2 = lst2->next;
	}
}
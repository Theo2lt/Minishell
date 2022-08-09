
#include "Minishell.h"

void    ft_execution(t_minishell *minishell)
{
	t_exec *cmd_tmp;

	cmd_tmp = minishell->exec;
	while(cmd_tmp)
	{
		//cmd_tmp->pid = fork();
		//if (cmd_tmp->pid == 0)
		ft_childs(minishell);
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



void	ft_childs(t_minishell *minishell)
{
	if (minishell->exec->infile == -1 || minishell->exec->outfile == -1)
		ft_exit(minishell);
	if (minishell->exec->infile > 2)
		dup2(minishell->exec->infile,0);
	if (minishell->exec->outfile > 2)
		dup2(minishell->exec->outfile,1);
	printf("1ici\n");
	
	ft_exec(minishell);
}

void	ft_exec(t_minishell *minishell)
{

	char *path;
	char **env;

 	ft_lst_env_BUG(minishell->env_lst);
	path = ft_path_exec(minishell->env_lst,minishell->exec->tabs_exeve);
	env = ft_recreate_env(minishell->env_lst);
	printf("OUT\n");
	if(!minishell->exec->tabs_exeve)
	{
		ft_commande_not_found(minishell->exec->tabs_exeve);
		env = ft_free_tab2(env);
		if(path)
			free(path);
		ft_exit(minishell);
	}
	execve(path,minishell->exec->tabs_exeve,env);
	ft_putstr_fd("bash: ",2);
	ft_putstr_fd(minishell->exec->tabs_exeve[0],2);
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
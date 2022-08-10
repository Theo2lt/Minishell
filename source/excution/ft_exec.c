
#include "Minishell.h"

void    ft_execution(t_minishell *minishell)
{
	t_exec *cmd_tmp;
	int fd[2];
	int tmp;
	
	cmd_tmp = minishell->exec;
	while(cmd_tmp)
	{	
		cmd_tmp->pid = fork();
		if (cmd_tmp->pid == 0)
			ft_childs(minishell,cmd_tmp);
		cmd_tmp = cmd_tmp->next;
	}
}


void	ft_commande_not_found(char	**cmd)
{
	ft_putstr_fd("bash: ", 2);
	if (cmd)
		ft_putstr_fd(cmd[0], 2);
	ft_putstr_fd(": command not found\n",2);
}



void	ft_childs(t_minishell *minishell, t_exec *cmd_tmp)
{
	if (cmd_tmp->infile == -1 || cmd_tmp->outfile == -1)
		ft_exit(minishell);
	if (cmd_tmp->infile != -1)
		dup2(cmd_tmp->infile,0);
	if (cmd_tmp->outfile > 2)
		dup2(cmd_tmp->outfile,1);

	if (ft_is_builting(cmd_tmp->tabs_exeve[0]))
	{
		ft_manage_builting(cmd_tmp->tabs_exeve,minishell);
		ft_exit(minishell);
	}
	else
		ft_exec(minishell,cmd_tmp);
}

void	ft_exec(t_minishell *minishell, t_exec *cmd_tmp)
{

	char *path;
	char **env;

	//ft_sim_exec_lst_BUG(cmd_tmp);

	path = ft_path_exec(minishell->env_lst,cmd_tmp->tabs_exeve);
	env = ft_recreate_env(minishell->env_lst);
	
	if(!cmd_tmp->tabs_exeve || (!ft_char_set(path, '/') && ft_return_path_value(minishell->env_lst)))
	{
		ft_commande_not_found(cmd_tmp->tabs_exeve);
		env = ft_free_tab2(env);
		if(path)
			free(path);
		ft_exit(minishell);
	}


	//ft_sim_exec_lst_BUG(cmd_tmp);
	if(execve(path,cmd_tmp->tabs_exeve,env) == -1)
	{
		ft_putstr_fd("bash: ",2);
		ft_putstr_fd(cmd_tmp->tabs_exeve[0],2);
		ft_putstr_fd(": ",2);
		ft_putstr_fd(strerror(errno),2);
		ft_putstr_fd("\n", 2);
		env = ft_free_tab2(env);
		if(path)
			free(path);
		ft_exit(minishell);
	}
	
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
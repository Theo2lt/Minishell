
#include "Minishell.h"


void	ft_r_infile(t_exec *cmd_tmp, int fd_previous)
{
	if(cmd_tmp->infile > 0)
	{
		dup2(cmd_tmp->infile,STDIN_FILENO);
		ft_putstr_fd("LA\n",2);
		if (cmd_tmp->infile > 0)
			close(cmd_tmp->infile);
		if(fd_previous > 0)
			close(fd_previous);
	}
	else if(cmd_tmp->num_cmd != 1)
	{
		dup2(fd_previous, STDIN_FILENO);
		if(fd_previous > 0)
			close(fd_previous);
	}
}


void	ft_r_out(t_minishell *minishell,t_exec *cmd_tmp, int *fd)
{
	if(cmd_tmp->outfile > 1)
		dup2(cmd_tmp->outfile,STDOUT_FILENO);
	else if(cmd_tmp->num_cmd != ft_exec_lstsize(minishell->exec))
		dup2(fd[1], STDOUT_FILENO);
	if(ft_exec_lstsize(minishell->exec) > 1 && fd[1] > 0)
		close(fd[1]);
	if(fd[0] > 0)
		close(fd[0]);
}


void    ft_execution(t_minishell *minishell)
{
	t_exec *cmd_tmp;
	//int fd[2];
	//int fd_previous;

	//fd[0] = 0;
	//fd[1] = 1;
	minishell->fd[0] = 0;
	minishell->fd[1] = 1;

	cmd_tmp = minishell->exec;
	while(cmd_tmp)
	{	
		
		minishell->fd_previous = minishell->fd[0];
		if(ft_exec_lstsize(minishell->exec) > 1 && pipe(minishell->fd) < 0)
		{
			printf("erreur pipe");
			ft_exit(minishell);
		}

		cmd_tmp->pid = fork();
		if (cmd_tmp->pid == 0)
			ft_childs(minishell,cmd_tmp,minishell->fd_previous,minishell->fd);
		cmd_tmp = cmd_tmp->next;
		if(minishell->fd[1] > 1 && ft_exec_lstsize(minishell->exec) > 1)
			close(minishell->fd[1]);
		if(minishell->fd_previous > 0)
			close(minishell->fd_previous);
	}
}


void	ft_commande_not_found(char	**cmd)
{
	ft_putstr_fd("bash: ", 2);
	if (cmd)
		ft_putstr_fd(cmd[0], 2);
	ft_putstr_fd(": command not found\n",2);
}



void	ft_childs(t_minishell *minishell, t_exec *cmd_tmp,int fd_previous,int *fd)
{
	ft_r_infile(cmd_tmp,fd_previous);
	ft_r_out(minishell,cmd_tmp, fd);
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
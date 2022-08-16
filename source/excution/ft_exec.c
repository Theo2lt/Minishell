/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliot <tliot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 21:15:49 by tliot             #+#    #+#             */
/*   Updated: 2022/08/15 22:32:45 by tliot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

void	ft_r_infile(t_exec *cmd_tmp, int fd_previous)
{
	if (cmd_tmp->infile > 0)
	{
		dup2(cmd_tmp->infile, STDIN_FILENO);
		if (cmd_tmp->infile > 0)
			close(cmd_tmp->infile);
		if (fd_previous > 0)
			close(fd_previous);
	}
	else if (cmd_tmp->num_cmd != 1)
	{
		dup2(fd_previous, STDIN_FILENO);
		if (fd_previous > 0)
			close(fd_previous);
	}
}

void	ft_r_out(t_minishell *minishell, t_exec *cmd_tmp, int *fd)
{
	if (cmd_tmp->outfile > 1)
		dup2(cmd_tmp->outfile, STDOUT_FILENO);
	else if (cmd_tmp->num_cmd != ft_exec_lstsize(minishell->exec))
		dup2(fd[1], STDOUT_FILENO);
	if (ft_exec_lstsize(minishell->exec) > 1 && fd[1] > 0)
		close(fd[1]);
	if (fd[0] > 0)
		close(fd[0]);
}

int	ft_is_dir(char *fileName)
{
	struct stat	path;
	int			res;

	res = stat(fileName, &path);
	if (res != 0)
		return (0);
	if (S_ISDIR(path.st_mode))
		return (1);
	return (0);
}

void	ft_execution(t_minishell *minishell)
{
	t_exec	*cmd_tmp;

	cmd_tmp = minishell->exec;
	while (cmd_tmp)
	{	
		minishell->fd_previous = minishell->fd[0];
		if (ft_exec_lstsize(minishell->exec) > 1 && pipe(minishell->fd) < 0)
		{
			ft_putstr_fd("erreur pipe\n", 2);
			ft_exit(minishell);
		}
		cmd_tmp->pid = fork();
		if (!cmd_tmp->tabs_exeve && cmd_tmp->pid == 0)
			ft_exit(minishell);
		if (cmd_tmp->pid == 0)
			ft_childs(minishell, cmd_tmp,
				minishell->fd_previous, minishell->fd);
		cmd_tmp = cmd_tmp->next;
		if (minishell->fd[1] > 1 && ft_exec_lstsize(minishell->exec) > 1)
			close(minishell->fd[1]);
		if (minishell->fd_previous > 0)
			close(minishell->fd_previous);
	}
}

void	ft_childs(t_minishell *minishell,
				t_exec *cmd_tmp, int fd_previous, int *fd)
{
	ft_r_infile(cmd_tmp, fd_previous);
	ft_r_out(minishell, cmd_tmp, fd);
	if (cmd_tmp->tabs_exeve && ft_is_builting(cmd_tmp->tabs_exeve[0]))
	{
		ft_manage_builting(cmd_tmp->tabs_exeve, minishell);
		ft_exit(minishell);
	}
	else if (cmd_tmp->tabs_exeve)
		ft_exec(minishell, cmd_tmp);
}

void	ft_commande_not_found(char	**cmd)
{
	char	*tmp;

	tmp = NULL;
	if (cmd)
		tmp = ft_joint_3str("bash: ", *cmd, ": command not found\n");
	else
		tmp = ft_joint_3str("bash: ", " ", ": command not found\n");
	ft_putstr_fd(tmp, 2);
	free(tmp);
}

void	ft_commande_error(char	**cmd, char *str_error)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_joint_3str(": ", str_error, "\n");
	tmp2 = ft_joint_3str("bash: ", cmd[0], tmp);
	write(2, tmp2, ft_strlen(tmp2));
	free(tmp);
	free(tmp2);
}

void	ft_exec_exit(t_minishell *minishell, char **env, char *path)
{
	env = ft_free_tab2(env);
	if (path)
		free(path);
	ft_exit(minishell);
}

void	ft_exec(t_minishell *minishell, t_exec *cmd_tmp)
{
	char	*path;
	char	**env;

	path = ft_path_exec(minishell->env_lst, cmd_tmp->tabs_exeve);
	env = ft_recreate_env(minishell->env_lst);
	if (!cmd_tmp->tabs_exeve || (!ft_char_set(path, '/')
			&& ft_return_path_value(minishell->env_lst)))
	{
		ft_commande_not_found(cmd_tmp->tabs_exeve);
		(*g_global)->exit_code = 127;
		ft_exec_exit(minishell, env, path);
	}
	if (ft_is_dir(cmd_tmp->tabs_exeve[0]))
	{
		ft_commande_error(cmd_tmp->tabs_exeve, "Is a directory");
		(*g_global)->exit_code = 126;
		ft_exec_exit(minishell, env, path);
	}
	(*g_global)->exit_code = 0;
	if (execve(path, cmd_tmp->tabs_exeve, env) == -1)
	{
		ft_commande_error(cmd_tmp->tabs_exeve, strerror(errno));
		(*g_global)->exit_code = 126;
		ft_exec_exit(minishell, env, path);
	}	
}

void	ft_wait_all_pid(t_exec *lst)
{
	t_exec	*lst2;
	int		status;

	lst2 = lst;
	while (lst2)
	{
		waitpid(lst2->pid, &status, 0);
		if (WIFEXITED(status))
			(*g_global)->exit_code = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
			(*g_global)->exit_code = WTERMSIG(status);
		lst2 = lst2->next;
	}
}

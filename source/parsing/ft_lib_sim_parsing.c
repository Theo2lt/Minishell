/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lib_sim_parsing.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliot <tliot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 00:35:07 by tliot             #+#    #+#             */
/*   Updated: 2022/07/31 00:30:36 by tliot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

int ft_fd_infile(char *name_infile)
{
	int fd;
	if(!name_infile)
		return (0);
	fd = open(name_infile, O_RDONLY);
	if(fd == -1)
	{
		ft_putstr_fd("ERROR FILEIN \n",2);
		ft_put_err_cd(NULL, name_infile, strerror(errno));
		return (-1);
	}
	return(fd);
}

int ft_fd_outfile(char *name_outfile)
{
	int fd;
	
	if(!name_outfile)
		return (1);
	fd = open(name_outfile,O_CREAT | O_RDWR | O_TRUNC, 0000644);
	if(fd == -1)
	{
		ft_putstr_fd("ERROR FILEOUT \n",2);
		ft_put_err_cd(NULL, name_outfile, strerror(errno));
		return (-1);
	}
	return(fd);
}


t_cmd	*ft_sim_cmd_new(char **cmd_args, char *name_infile ,char *name_outfile,int num_cmd)
{
	t_cmd	*new;

	new = (t_cmd *) malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->num_cmd = num_cmd;
    new->pid = -1;
	new->cmd_arg = cmd_args;
	new->in_fd = ft_fd_infile(name_infile);
	new->out_fd = ft_fd_outfile(name_outfile);
	if(new->cmd_arg)
        new->isbuiltin = ft_is_builting(new->cmd_arg[0]);
	else
		new->isbuiltin = 0;
	new->next = NULL;
	printf("fd : %d,%d \n", new->in_fd, new->out_fd);
	return (new);
}

/// Ajoute un nouveau node initialisé a la fin de lst. 
void	ft_sim_cmd_add(char **cmd_args, char *name_infile ,char *name_outfile, int num_cmd, t_cmd **lst_cmd)
{
	t_cmd	*new;

	new = ft_sim_cmd_new(cmd_args, name_infile , name_outfile, num_cmd);
	if (new)
		ft_sim_cmd_lst_add_back(lst_cmd, new);
}
/// PREND lst environement en PARAMETRE
/// RETURN dernier maillon de la chaine 

t_cmd	*ft_sim_cmd_lst_last(t_cmd *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

/// PREND t_env **alst, t_env *new
/// AJOUTE le nouveau noeud a la fin de lst
void	ft_sim_cmd_lst_add_back(t_cmd **alst, t_cmd *new)
{
	t_cmd	*last;

	if (*alst)
	{
		last = ft_sim_cmd_lst_last(*alst);
		last->next = new;
	}
	else
		*alst = new;
}

/// Returne la taille de lst
int	ft_sim_cmd_lst_size(t_cmd *lst)
{
	int	l;

	l = 0;
	while (lst && ++l)
		lst = lst->next;
	return (l);
}

/// PREND lst environement en PARAMETRE 
/// SUPPRIME ET FREE les différents maillon de la chaine

void	ft_sim_cmd_lst_free(t_cmd *lst)
{
	t_cmd	*lst2;

	while (lst)
	{
		lst2 = lst;
		lst = lst->next;
		if (lst2->cmd_arg)
			lst2->cmd_arg = ft_free_tab2(lst2->cmd_arg);
		if(lst2->in_fd > 2)
			close(lst2->in_fd);
		if(lst2->out_fd > 2)
			close(lst2->out_fd);
		free(lst2);
	}
}
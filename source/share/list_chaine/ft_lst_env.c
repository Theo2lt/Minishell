/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engooh <engooh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 02:25:09 by tliot             #+#    #+#             */
/*   Updated: 2022/07/22 02:54:47 by engooh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"


/// PREND *name, char *value, int init_value en PARAMETRE 
/// CREER une nouvelle node
/// RETURN node si ok sinon NULL

t_env	*ft_lst_env_new(char *name, char *value, int init_value)
{
	t_env	*new;
	
	if(!name)
		return(NULL);
	new = (t_env*)malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->variable_value = ft_init_variable_env(value);
	new->variable_name = ft_init_variable_env(name);
	new->init_value = init_value;
	new->next = NULL;
	return (new);
}

/// PREND lst environement en PARAMETRE
/// RETURN dernier maillon de la chaine 

t_env	*ft_lst_env_last(t_env *lst)
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
void	ft_lst_env_add_back(t_env **alst, t_env *new)
{
	t_env	*last;

	if (*alst)
	{
		last = ft_lst_env_last(*alst);
		last->next = new;
	}
	else
		*alst = new;
}


/// PREND lst environement en PARAMETRE 
/// SUPPRIME ET FREE les différents maillon de la chaine

void	ft_lst_env_free(t_env *lst)
{
	t_env	*lst2;

	while (lst)
	{
		lst2 = lst;
		lst = lst->next;
		if (lst2->variable_name)
			free(lst2->variable_name);
		if (lst2->variable_value)
			free(lst2->variable_value);
		free(lst2);
	}
}

/// PREND *name et lst environement en PARAMETRE 
/// RETURN un node de lst si "name = lst->name" et init_value = 0
t_env	*ft_lst_getenv(char *name, t_env *lst)
{
	while (lst)
	{
		if(lst->init_value != 0)
			if (ft_strncmp(lst->variable_name, name, ft_strlen(lst->variable_name)) == 0)
				return (lst);
		lst = lst->next;
	}
	return (NULL);
}

t_env	*ft_lst_getexport(char *name, t_env *lst)
{
	while (lst)
	{
		if(lst->init_value == 0)
			if (ft_strncmp(lst->variable_name, name, ft_strlen(lst->variable_name)) == 0)
				return (lst);
		lst = lst->next;
	}
	return (NULL);
}

void	ft_lst_setenv(char *name, char *value, int init_value, t_env **lst)
{
	t_env *tmp;
	
	if(ft_lst_getenv(name, *lst) )
	{   
		if(init_value == 1)
		{
			tmp = ft_lst_getenv(name, *lst);
			free(tmp->variable_value);
			tmp->variable_value = ft_init_variable_env(value);
		}
	}
	else if (ft_lst_getexport(name, *lst))
	{
		tmp = ft_lst_getexport(name, *lst);
		if(init_value == 1)
			tmp->init_value = 1;
		free(tmp->variable_name);
		tmp->variable_name = ft_init_variable_env(name);
		tmp->variable_value = ft_init_variable_env(value);
	}
	else
		ft_add_variable_env(name,value,init_value,lst);
}

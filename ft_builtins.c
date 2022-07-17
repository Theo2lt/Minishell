/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliot <tliot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 23:51:29 by tliot             #+#    #+#             */
/*   Updated: 2022/07/17 15:40:18 by tliot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exec_pwd(void)
{
	char *pwd;
	
	pwd = getcwd(NULL,0);
	if(!pwd)
	{
		perror("getcwd");
		return(1);
	}
	printf("%s\n",pwd);
	free(pwd);
	return(0);
}


int	ft_exec_echo(char **cmd) // GERER LES -NNNNNNNNNNNNN N INFINI // A REFAIRE CAR C'EST TRES MOCHE
{
	int i;
	
	i = 1;
	if (!cmd[i])
	{
		printf("\n");
		return(1);
	}
	if (ft_strcmp(cmd[i], "echo") == 0 && ft_strcmp(cmd[i+1], "-n") == 0)
	{
		i = 3;
		if(cmd[i] && i == 3)
			printf("%s",cmd[i++]);
		while(cmd[i])
			printf(" %s",cmd[i++]);
	}
	else if(ft_strcmp(cmd[i], "echo") == 0)
	{
		i = 2;
		if(cmd[i] && i == 2)
			printf("%s",cmd[i++]);
		while(cmd[i])
			printf(" %s",cmd[i++]);
		printf("\n");
	}
	return (0);
}

int	ft_exec_cd(char **cmd,  t_env *lst)
{
	char *pwd;
	
	pwd = ft_get_pwd();
	if (cmd[1][0] == '-')
	{
		if(chdir(ft_lst_getenv("OLDPWD", lst)->variable_value) != 0 ) // A GERER SANS ENVIRONMENT
		{
			printf("err OLDPWD\n");
			free(pwd);
			return(1);
		}
		printf("%s\n",ft_lst_getenv("OLDPWD", lst)->variable_value);
	}
	else if(cmd[1][0] == '~')
	{
		if (chdir(ft_lst_getenv("HOME", lst)->variable_value) != 0)
		{
			ft_putstr("bash: cd: no such file or directory: ~ \n",2);
			free(pwd);
			return (1);
		}
	}
	else if (chdir(cmd[1]) != 0)
	{
		ft_putstr("bash: cd: no such file or directory: ",2);
		ft_putstr(cmd[1],2);
		ft_putstr("\n",2);
		free(pwd);
		return (1);
	}
	printf("laaa\n");
	ft_lst_setenv(pwd,&lst);
	free(pwd);
	return (0);
}

int ft_exec_env(t_env *lst)
{
	while (lst)
	{
		if(ft_char_set(lst->variable_name,'=') != 0)
			printf("%s%s\n",lst->variable_name,lst->variable_value);
		lst = lst->next;
	}
	
	return (0);
}

int ft_exec_export(char *cmd, t_env **lst)
{
	t_env *lst2;
	
	lst2 = *lst;
	if(!cmd)
	{
		printf("export affichage pas encore ok\n");
		while (lst2)
		{
			if(ft_char_set(lst2->variable_name,'=') == 0)
				printf("%s->%s\n",lst2->variable_name,lst2->variable_value);
			lst2 = lst2->next;
		}
	}
	else
		ft_lst_setenv(cmd, lst);
	return (0);
}

char	*ft_get_pwd(void)
{
	char *pwd;
	
	pwd = getcwd(NULL,0);
	if(!pwd)
	{
		perror("getcwd");
		return(NULL);
	}
	return(pwd);
}
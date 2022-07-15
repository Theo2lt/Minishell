/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliot <tliot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 23:51:29 by tliot             #+#    #+#             */
/*   Updated: 2022/07/14 23:53:33 by tliot            ###   ########.fr       */
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

int	ft_exec_echo(char **cmd) // GERER LES -NNNNNNNNNNNNN N INFINI
{
	int i;
	
	i = 1;
	if (!cmd[i])
	{
		perror("pas de commande");
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

int	ft_exec_cd(char *cmd)
{
	if (cmd && cmd[0] == '-')
	{
		if(chdir(getenv("OLDPWD")) != 0 ) // A GERER SANS ENVIRONMENT
		{
			printf("err OLDPWD\n");
			return(1);
		}
		printf("%s\n",getenv("OLDPWD"));
		return (0);
	}
	if (!cmd || (cmd[0] == '~' && !cmd[1]))
	{
		if (chdir(getenv("HOME")) != 0)
		{
			ft_putstr("bash: cd: no such file or directory: ~ \n",2);
			return (1);
		}
	}
	else if (chdir(cmd) != 0)
	{
		ft_putstr("bash: cd: no such file or directory: ",2);
		ft_putstr(cmd,2);
		ft_putstr("\n",2);
		return (1);
	}
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
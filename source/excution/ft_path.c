/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliot <tliot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 21:20:02 by tliot             #+#    #+#             */
/*   Updated: 2022/08/23 17:48:32 by tliot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

// PREND deux str en parametre
// CONCATENE les deux chaine avec un / au milieu
// RETURN char* si OK sinon NULL
char	*ft_strjoin_path(char *s1, char *s2)
{
	int		i;
	int		len1;
	char	*str;

	if (s1 && s2)
	{
		len1 = ft_strlen(s1);
		str = (char *)malloc(sizeof(char) * (len1 + ft_strlen(s2) + 2));
		if (str == NULL)
			return (NULL);
		i = -1;
		while (s1[++i])
			str[i] = s1[i];
		str[len1] = '/';
		i = -1;
		while (s2[++i])
		{
			str[len1 + 1] = s2[i];
			len1++;
		}
		str[len1 + 1] = '\0';
		return (str);
	}
	return (NULL);
}

// PREND lst en parametre 
// VERIFIE si le noeud et le contenue de value
// RETURN value si ok sinon NULL

char	*ft_return_path_value(t_env *lst)
{
	if (ft_lst_getenv("PATH", lst)
		&& ft_lst_getenv("PATH", lst)->variable_value)
		return (ft_lst_getenv("PATH", lst)->variable_value);
	return (NULL);
}

char	*ft_path_exec(t_env *lst, char **cmd_arg, int i)
{
	char	*path;
	char	**paths;

	if (!cmd_arg || !cmd_arg[0] || !cmd_arg[0][0])
		return (ft_strjoin2("", ""));
	if (!ft_strncmp("./", cmd_arg[0], 2))
		return (ft_strjoin2(cmd_arg[0], ""));
	paths = ft_split(ft_return_path_value(lst), ':');
	if (paths)
	{
		while (paths[i] != NULL)
		{
			path = ft_strjoin_path(paths[i], cmd_arg[0]);
			if (path && access(path, X_OK) == 0)
			{
				paths = ft_free_tab2(paths);
				return (path);
			}
			free(path);
			i++;
		}
	}
	paths = ft_free_tab2(paths);
	return (ft_strjoin2(cmd_arg[0], ""));
}

// PREND 3 str en parametre
// CONCATENE le tout en une str
// RETURN char *dest si OK sinon NULL

char	*ft_joint_3str(char *str, char *str2, char *str3)
{
	char	*dest;
	int		len_dest;
	int		i;
	int		j;

	len_dest = ft_strlen3(str) + ft_strlen3(str2) + ft_strlen3(str3) + 1;
	dest = malloc(sizeof(char) * (len_dest));
	if (!dest)
		ft_exit((*g_global));
	ft_memset(dest, '\0', len_dest);
	i = -1;
	while (str && str[++i])
		dest[i] = str[i];
	j = -1;
	while (str2 && str2[++j])
		dest[i + j] = str2[j];
	i += j;
	j = -1;
	while (str3 && str3[++j])
		dest[i + j] = str3[j];
	return (dest);
}
// PREND lst en parametre
// CREER un ENV tmp pour chaque commande appeler 
// RETURN char *dest si OK sinon NULL

char	**ft_recreate_env(t_env *lst)
{
	char	**env;
	int		i;

	env = NULL;
	env = malloc(sizeof(char *) * (ft_lstsize_env(lst) + 1));
	if (!env)
		return (NULL);
	i = 0;
	while (lst)
	{
		if (lst->init_value == 1)
		{
			env[i] = ft_joint_3str(lst->variable_name,
					"=", lst->variable_value);
			i++;
		}
		lst = lst->next;
	}
	env[i] = NULL;
	return (env);
}

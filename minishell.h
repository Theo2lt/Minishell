/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliot <tliot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 21:39:22 by tliot             #+#    #+#             */
/*   Updated: 2022/07/15 04:23:10 by tliot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>

/// FONCTION BUILTINS ///
int		ft_exec_pwd(void);
int		ft_exec_echo(char **cmd);
int		ft_exec_cd(char *cmd);
char	*ft_get_pwd(void);

/// FONCTION AFFICHAGE ///
void	ft_putchar(char c, int fd);
void	ft_putstr(char *s, int fd);

/// FONCTION LIB //
int		ft_strlen(const char *s);
char	*ft_strcpy(char *dst, char *src);
char	*ft_strncpy(char *dst, char *src, int len);
char	*ft_strdup(char *s1);
int		ft_strcmp(char *s1, char *s2);
int		ft_char_set(char *str, char c);
char	*ft_strjoin(char  *s1,char  *s2);

// FONCTION LST_ENV ///

typedef struct s_env
{
	char	*variable_name;
	char	*variable_value;
	
	struct s_env	*next;
}	t_env;

t_env	*ft_lst_env_new(void);
t_env	*ft_lst_env_last(t_env *lst);
void	ft_lst_env_add_back(t_env **alst, t_env *new);
void	ft_lst_env_free(t_env *lst);


#endif
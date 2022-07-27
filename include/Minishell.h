/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliot <tliot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 21:39:22 by tliot             #+#    #+#             */
/*   Updated: 2022/07/27 05:03:34 by tliot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

/*
typedef struct s_token
{
	char *cmd;
	t_list *args;
	char    **bin; //bin = cmd + arguments
	t_redir *redirection;
	void    *next;
}

while (token)
{
	fork()
		if (token->redir != NULL)
			make_redir();
		execution();
	token = token->next;
}

while (waitpid(-1, &status, NULL))
*/
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <errno.h>

#include <libft.h>
#include <Env.h>
#include <Builtins.h>


/// STRUCT CMD ///
typedef struct s_cmd
{
	char            **cmd_arg;
	int             infile;
	int             outfile;
	int             isbuiltin;
	int             pid;
	struct s_cmd    *next;
} t_cmd;

	/// EXECUTION ///
char	*ft_path_exec(t_env *lst, char **cmd_arg);
char **ft_recreate_env(t_env *lst);
void	ft_exec(t_env *lst ,char **cmd_arg);

///// ERROR///
void ft_put_err(char *cmd, char *arg, char *strerrno);

/// FONCTION LIB //
int ft_strlen(const char *s);
int	ft_tablen(char **tab);
char *ft_strcpy(char *dst, char *src);
char *ft_strncpy(char *dst, char *src, int len);
char *ft_strdup(char *s1);
char *ft_substr(char const *s, int start, int len);
char *ft_strchr(const char *s, int c);
int ft_strcmp(char *s1, char *s2);
int ft_strncmp(const char *str1, const char *str2, int n);
int ft_char_set(char *str, char c);
char *ft_strjoin(char *s1, char *s2);
void *ft_memset(void *str, int c, int n);


/// SPLIT ///
char **ft_split(char const *s, char c);
char **ft_free_tab2(char **tab);


#endif

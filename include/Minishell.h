/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliot <tliot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 21:39:22 by tliot             #+#    #+#             */
/*   Updated: 2022/07/28 06:14:29 by tliot            ###   ########.fr       */
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


/// STRUCT CMD ///
typedef struct s_cmd
{
	pid_t             pid;
	char            **cmd_arg;
	int             infile;
	int             outfile;
	int             isbuiltin;
	struct s_cmd    *next;
} t_cmd;

//// STRUCT ENV //////
typedef struct s_env
{
	char *variable_name;
	char *variable_value;
	int  init_value;
	struct s_env *next;
} t_env;

////// STRUC MINISHELL ////// 
typedef struct		s_minishell
{
	struct s_env *env_lst;
	struct s_cmd *cmd_lst;
}t_minishell;


// FONCTION LST_ENV ///

t_env	*ft_lst_env_new(char *name, char *value, int init_value);
t_env   *ft_lst_env_last(t_env *lst);
void    ft_lst_env_add_back(t_env **alst, t_env *new);
void    ft_lst_env_free(t_env *lst);
char    *ft_init_variable_env(char *tmp);
void    ft_add_variable_env(char *name ,char *value, int init_value, t_env **lst_env);
t_env   *ft_lst_getenv(char *str, t_env *lst);
void    ft_lst_setenv(char *name, char *value, int init_value, t_env **lst);
int	    ft_lstsize_env(t_env *lst);
t_env   *ft_init_env(char **env);
void    ft_parsing_setenv(char *cmd, t_env **lst);
void    ft_unset(char *name, t_env **lst);

//// RECREATE ENV /////
char **ft_recreate_env(t_env *lst);

////// DEBUG /////
void    ft_lst_env_BUG(t_env *lst);

/// FONCTION BUILTINS ///
int ft_exec_pwd(void);
int ft_exec_echo(char **cmd);
int	ft_exec_cd(char **cmd, t_env **lst);
char *ft_get_pwd(void);
int ft_exec_env(t_env *lst);
int ft_exec_export(char **cmd, t_env **lst);
void ft_exec_unset(char **name, t_env **lst);
int	ft_is_built(char **cmd);
int ft_manage_builting(char **cmd, t_minishell *minishell);
void ft_exit(t_minishell *mini);

/// PARSING EXPORT UNSET ///

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

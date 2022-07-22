/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engooh <engooh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 19:57:17 by engooh            #+#    #+#             */
/*   Updated: 2022/07/22 01:43:18 by engooh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHEL_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h> 
# include "libft.h"

//// STUCT ENV //////
typedef struct s_env
{
	int				init_value;
	char			*variable_name;
	char			*variable_value;
	struct s_env	*next;
}	t_env;

//// STRUCT DEFAULT //// 

//// FONCTION PARSING ////
void	ft_converte_quotes(char *str);
char	*ft_parser_pipe_utils(char *str, int stop);
char	*ft_parser_chevron_utils(char *str, char c);
int		ft_parser_quote_chevron_pipe(char *str);
int		parser(char *str);

/// FONCTION BUILTINS ///
int		ft_exec_pwd(void);
int		ft_exec_echo(char **cmd);
int		ft_exec_cd(char **cmd, t_env **lst);
char	*ft_get_pwd(void);
int		ft_exec_env(t_env *lst);
int		ft_exec_export(char **cmd, t_env **lst);
void	ft_exec_unset(char **name, t_env **lst);

void	ft_parsing_setenv(char *cmd, t_env **lst);
void	ft_unset(char *name, t_env **lst);

/// FONCTION AFFICHAGE ///
void	ft_putchar(char c, int fd);
void	ft_putstr(char *s, int fd);

// FONCTION LST_ENV ///
void	ft_lst_setenv(char *name, char *value, int init_value, t_env **lst);
void	ft_lst_env_add_back(t_env **alst, t_env *new);
void	ft_lst_env_free(t_env *lst);
char	*ft_init_variable_env(char *tmp);
void	ft_add_variable_env(char *name, char *value, int init_value,
			t_env **lst_env);
t_env	*ft_lst_env_new(char *name, char *value, int init_value);
t_env	*ft_lst_env_last(t_env *lst);
t_env	*ft_lst_getenv(char *str, t_env *lst);

////// DEBUG /////
void	ft_lst_env_BUG(t_env *lst);
#endif

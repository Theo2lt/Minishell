/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engooh <engooh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 19:57:17 by engooh            #+#    #+#             */
/*   Updated: 2022/07/28 04:24:51 by engooh           ###   ########.fr       */
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

/// STRUCT GARBANGE COLECTORE// 

/// STRUCT EXEC //// 
typedef struct s_exec
{
	int				pid;
	int				bultins;
	int				infile;
	int				outfile;
	char			*args;
	char			*path_cmd;
	char			**tabs_exeve;
	struct s_exec	*next;
}	t_exec;

//// STUCT ENV //////
typedef struct s_env
{
	int							init_value;
	char						*variable_name;
	char						*variable_value;
	struct s_env				*next;
}	t_env;

//// STRUCT DEFAULT //// 
typedef struct s_def
{
	int					value;
	char				*content;
	char				*content1;
	struct s_def		*next;
	char				*contente;
}	t_def;

//// FONCTION PARSING ////
void	ft_converte_quotes(char *str);
char	*ft_parser_pipe_utils(char *str, int stop);
char	*ft_parser_chevron_utils(char *str, char c);
char	*ft_parser_quote_chevron_pipe(char *str);
char	*parser(char *str, t_env *env);

/// FONCTION EXPANDE ////
char	*ft_parse_expende(char *str, t_env *env);

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
char	*ft_getenv(t_env *env, char *str, int len);
void	ft_print_env(t_env *env, int i);
void	ft_push_env(t_env *lst, char *str);
void	ft_delete_env(t_env *lst, char *str);
void	ft_converte_tab_list(char **tab, t_env **lst,
			void (f)(t_env *lst, char *str));
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliot <tliot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 19:57:17 by engooh            #+#    #+#             */
/*   Updated: 2022/08/10 07:46:00 by tliot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h> 
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "libft.h"
# include <wait.h>
# include <errno.h>




//// STUCT ENV //////
typedef struct s_env
{
	int							init_value;
	char						*variable_name;
	char						*variable_value;
	struct s_env				*next;
}	t_env;

typedef struct s_exec
{
	int				pid;
	int				bultins;
	int				infile;
	int				outfile;
	char			*args;
	char			**tabs_exeve;
	struct s_exec	*next;
	struct s_env	*env;
}	t_exec;

//// STRUCT DEFAULT //// 
typedef struct s_def
{
	int					value;
	char				*content;
	char				*content1;
	struct s_def		*next;
	char				*contente;
}	t_def;


////// STRUC MINISHELL ////// 
typedef struct		s_minishell
{
	struct s_env *env_lst;
	struct s_exec *exec;
}t_minishell;


//// FONCTION PARSING ////
void	ft_converte_str(char *str, int signe);
void	ft_converte_quotes(char *str, int signe);
char	*ft_parser_pipe_utils(char *str, int stop);
char	*ft_parser_chevron_utils(char *str, char c);
char	*ft_parser_quote_chevron_pipe(char *str);
char	*parser2(char *str, t_env *env);
t_exec	*parser(char *str, t_env *env);

//// FONCTION DE TOCKENISATION /// 
t_exec	*tocken(char *str, t_exec *exec, t_env *env, int cmd);

/// FONCTION EXPANDE ////
char	*parser_expende(char *str, t_env *env);

/// FONCTION BUILTINS ///
int		ft_exec_pwd(void);
int		ft_exec_echo(char **cmd);
int		ft_exec_cd(char **cmd, t_env **lst);
char	*ft_get_pwd(void);
int		ft_exec_env(t_env *lst);
int		ft_exec_export(char **cmd, t_env **lst);
void	ft_exec_unset(char **name, t_env **lst);

void	ft_parsing_setenv(char *cmd, t_env **lst);
int		ft_is_builting(char *cmd);
int		ft_manage_builting(char **cmd, t_minishell *minishell);
void	ft_unset(char *name, t_env **lst);
void	ft_exit(t_minishell *minishell);

/// FONCTION AFFICHAGE ///
void	ft_putchar(char c, int fd);
void	ft_putstr(char *s, int fd);

// FONCTION LST_ENV ///
char	*ft_get_env(t_env *env, int *str, int len);
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
int		ft_lstsize_env(t_env *lst);
t_env	*ft_init_env(char **env);


char **ft_recreate_env(t_env *lst);
////// EXECUTION /////
void    ft_execution(t_minishell *minishell);
void	ft_commande_not_found(char	**cmd);
void	ft_childs(t_minishell *minishell, t_exec *cmd_tmp);
void	ft_exec(t_minishell *minishell, t_exec *cmd_tmp);
char	*ft_strjoin_path(char *s1, char *s2);
char    *ft_return_path_value(t_env *lst);
char	*ft_path_exec(t_env *lst, char **cmd_arg);
char 	*ft_joint_3str(char *str, char *str2, char *str3);
char 	**ft_recreate_env(t_env *lst);
void	ft_wait_all_pid(t_exec *lst);

////// DEBUG /////
void	ft_lst_env_BUG(t_env *lst);
void 	ft_sim_exec_lst_BUG(t_exec *lst);
#endif

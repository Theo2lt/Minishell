/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliot <tliot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 19:57:17 by engooh            #+#    #+#             */
/*   Updated: 2022/08/23 14:08:36 by tliot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>  
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
# include <signal.h>

# define  LMAX = 9223372036854775807;
# define  LMIN = 9223372036854775808;

////// STRUC MINISHELL ////// 
typedef struct s_minishell
{
	struct s_env	*env_lst;
	struct s_exec	*exec;
	struct s_exec	*begin;
	int				fd[2];
	int				fd_previous;
	int				exit_code;
	pid_t			pid;
}	t_minishell;

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
	int				num_cmd;
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

typedef struct s_token
{
	struct s_env		*env;
	struct s_exec		*exec;
	struct s_exec		*begin;
	struct s_tocken		*next;
	char				*limiter;
	char				*file_name;
	int					type_redir;
	int					redir;
	int					cmd;
	pid_t				pid;
	int					status;
}	t_token;

/// GLOBAL ///
extern t_minishell	**g_global;

//// FONCTION PARSING ////
char			*ft_replace(char *str, char *node, int i, int j);
void			ft_converte_expende(char *str);
char			*ft_expende(t_env *env, char *str, int start, int end);
int				annule_exepend_heredoc(char *str, int i, int *heredoc);
char			*parser_expende(char *str, t_env *env, int heredoc);
char			*ft_create_name(void);
void			*ft_free2(char *str);
t_exec			*tocken(char *str, t_token *tkn, t_exec *exec);
void			exit_heredoc(t_token *tkn, int exit_code);
void			open_heredoc(t_token *tkn);
t_def			*def_lstnew(void *content);
void			def_lstadd_back(t_def **alst, t_def *new);
t_def			*def_lstlast(t_def *lst);
void			def_lstiter(t_def *lst, void (*f)(void *));
void			def_lstdelone(t_def *lst, void (*del)(void *));
void			def_lstclear(t_def **lst, void (*del)(void *));
char			*puterror(char *str);
char			*ft_parser_pipe_utils(char *str, int stop);
char			*ft_parser_chevron_utils(char *str, char c);
char			*ft_check_expend(char *str, char c);
void			ft_converte_quotes(char *str, int signe);
char			*print_syntaxe_error(char c);
char			*check_expende(char *str, int mode);
void			ft_converte_str(char *str, int signe);
int				parser_quote(char *str);
char			*parser_chevron_pipe_utils(char *str, int c, int *espace);
int				parser_chevron_pipe(char *str);
t_exec			*parser(char *str, t_env *env);
void			*ft_delete_exec(t_exec *exec);
void			*ft_delete_execs(t_exec *exec);
void			ft_positive_negative(char *str, int signe);
void			ft_print_error_file(char *str, char *sterr);
void			ft_exit_child(t_minishell *mini, int exit_code);
char			*set_arg(char *start, char *res, t_exec *exec);
char			*set_cmd(char *start, char *res, t_exec *exec);
t_exec			*add_exec(t_exec **exec, t_exec *new);
t_exec			*set_tocken(t_token *tkn, t_exec *exec, char *str);
t_exec			*tocken(char *str, t_token *tkn, t_exec *exec);
int				set_outfile(char *str, t_exec *exec, int mode);
char			*set_redir(char *str, int *type_redir);
char			*set_begin(char	*str);
int				if_expende_heredoc(char *str, t_token *tkn);
char			*set_file(char *start, char *res, t_token *tkn);
int				read_heredoc(t_token *tkn);
void			handler(int sig);
int				signal_heredoc(t_token *tkn, int mode);
int				set_heredoc(t_token *tkn, char *str);
int				set_infile(t_token *tkn, char *str, t_exec *exec);
/// FONCTION EXPANDE ////
char			*parser_expende(char *str, t_env *env, int heredoc);

/// FONCTION BUILTINS ///
int				ft_builtin_pwd(void);
void			ft_builtin_echo(char **cmd);
void			ft_builtin_cd(char **cmd, t_env **lst);
char			*ft_get_pwd(void);
void			ft_builtin_env(t_env *lst);
int				ft_builtin_export(char **cmd, t_env **lst);
void			ft_builtin_unset(char **name, t_env **lst);
void			ft_put_err_cd(char *cmd, char *arg, char *strerrno);
void			ft_parsing_setenv(char *cmd, t_env **lst);
int				ft_is_builting(char *cmd);
int				ft_manage_builting(char **cmd, t_minishell *minishell);
void			ft_unset(char *name, t_env **lst);
void			ft_builting_exit(char **cmd, t_minishell *mini);
void			ft_exit(t_minishell *minishell);
bool			ft_atoi_bool(const char *str);
void			ft_redir_simple_bulting(t_minishell *minishell);

/// FONCTION AFFICHAGE ///
void			ft_putchar(char c, int fd);
void			ft_putstr(char *s, int fd);
void			ft_put_siganture(void);

// FONCTION LST_ENV ///
char			*ft_get_env(t_env *env, int *str, int len);
char			*ft_getenv(t_env *env, char *str, int len);
void			ft_print_env(t_env *env, int i);
void			ft_push_env(t_env *lst, char *str);
void			ft_delete_env(t_env *lst, char *str);
void			ft_converte_tab_list(char **tab, t_env **lst,
					void (f)(t_env *lst, char *str));
void			ft_lst_setenv(char *name, char *value,
					int init_value, t_env **lst);
void			ft_lst_env_add_back(t_env **alst, t_env *new);
void			ft_lst_env_free(t_env *lst);
char			*ft_init_variable_env(char *tmp);
void			ft_add_variable_env(char *name, char *value, int init_value,
					t_env **lst_env);
t_env			*ft_lst_env_new(char *name, char *value, int init_value);
t_env			*ft_lst_env_last(t_env *lst);
t_env			*ft_lst_getenv(char *str, t_env *lst);
int				ft_lstsize_env(t_env *lst);
t_env			*ft_init_env(char **env);
void			ft_delete_exec_lst_free(t_exec **lst);
char			**ft_recreate_env(t_env *lst);

////// EXECUTION /////
void			ft_execution(t_minishell *minishell);
void			ft_commande_not_found(char	**cmd);
void			ft_childs(t_minishell *minishell,
					t_exec *cmd_tmp, int fd_previous, int *fd);
void			ft_exec(t_minishell *minishell, t_exec *cmd_tmp);
char			*ft_strjoin_path(char *s1, char *s2);
char			*ft_return_path_value(t_env *lst);
char			*ft_path_exec(t_env *lst, char **cmd_arg, int i);
char			*ft_joint_3str(char *str, char *str2, char *str3);
char			**ft_recreate_env(t_env *lst);
void			ft_wait_all_pid(t_exec *lst);
int				ft_exec_lstsize(t_exec *lst);
int				ft_assigne_num_lstexec(t_exec *lst);
void			ft_r_infile(t_exec *cmd_tmp, int fd_previous);
void			ft_r_out(t_minishell *minishell, t_exec *cmd_tmp, int *fd);
int				ft_is_dir(char *fileName);
void			ft_commande_not_found(char	**cmd);
void			ft_commande_error(char	**cmd, char *str_error);

////// DEBUG /////
void			ft_lst_env_bug(t_env *lst);
void			ft_sim_exec_lst_bug(t_exec *lst);

/////	SIGNAUX	////
void			get_signal(int sig);
void			parent_signal(int sig);
void			child_signal(int sig);
void			exit_succes(t_minishell *minishell);

//// MAIN ///
void			ft_start(t_minishell	*minishell, char *input);
void			ft_launcher(t_minishell	*minishell, char *input);
void			ft_delete_exec_lst_free(t_exec **lst);
void			ft_signal(void);

// EXIT AND CLOSE
void			ft_all_close_fd(void);

// SIGNAL
void			parent_signal(int sig);
#endif

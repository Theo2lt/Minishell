/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sredjini <sredjini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 00:55:32 by sredjini          #+#    #+#             */
/*   Updated: 2022/07/21 03:27:38 by sredjini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# define MINISHELL "minishell>"

typedef struct s_env {

	char	*str;
	struct s_env *next;
}		t_env;

typedef struct s_pars
{
	int	process;
	t_env *env;

} t_pars;

int	lexer_redi(char *str, t_pars *pars);
int	lexer_shell(char **str, t_pars *pars);
int	ft_check_expand(char *str, char c, int i, t_pars *pars);
int	ft_negative_quote(char *str, t_pars *pars);
int	ft_positive_char(char *str, t_pars *pars);
int	negative_expand(char *str, int i);
int	ft_isalnum(int c);
int ft_strlen(char *str);
int	ft_isdigit(int c);
int	ft_isalpha(int c);
void	ft_lstadd_back(t_env **alst, t_env *new);
t_env	*ft_lstnew(void);
t_env	*ft_lstlast(t_env *lst);
int	ft_strncmp(char *s1, char *s2, unsigned int n);
char	*ft_strchr(char *str, int c);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(char *s);
char	*ft_init_pars(char *str, t_pars *pars);
char	*ft_substr(char *s, unsigned int start, unsigned int len);
char	*ft_replace(char *str, char *node, int i, int j);
char	*ft_save_pos_expand(char *str, int i, int j, int quote, t_pars *pars);
char	*ft_save_expand(char *str, char c, int i, t_pars *pars);
char	*ft_nb_expand(char *str, int i, t_pars *pars);
 char	*ft_init_pars2(char *str, t_pars *pars);
#endif
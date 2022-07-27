
#include <Minishell.h>

//// STRUCT ENV //////
typedef struct s_env
{
	char *variable_name;
	char *variable_value;
	int  init_value;
	struct s_env *next;
} t_env;

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
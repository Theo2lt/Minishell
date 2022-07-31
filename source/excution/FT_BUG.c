
#include "Minishell.h"

void ft_lst_env_BUG(t_env *lst)
{
	while (lst)
	{
        printf("\n---------------------------------\n");
        printf(" < &NOEUD > addr : %p \n",lst);
        printf("---------------------------------\n");
		printf("addr : %p | %s\n", lst->variable_name, lst->variable_name);
		printf("addr : %p | %d\n", &lst->init_value, lst->init_value);
		printf("addr : %p | %s\n", lst->variable_value, lst->variable_value);
		printf("addr : %p | lst->next\n", lst->next);
		printf("---------------------------------\n");
		lst = lst->next;
	}

}

void ft_sim_cmds_lst_BUG(t_cmd *lst)
{
	while (lst)
	{
		//int i;
		//i = 0;
        printf("\n---------------------------------\n");
        printf("         NUM CMD %d \n",lst->num_cmd);
        printf("---------------------------------\n");
		if(!lst->cmd_arg)
			printf("addr : %p | CMD_ARG (NULL) \n", lst->cmd_arg);
		else
			printf("addr : %p |    CMD_ARG : %s\n", lst->cmd_arg[0], lst->cmd_arg[0]);
		printf("addr : %p |     in_fd : %d\n", &lst->in_fd, lst->in_fd);
		printf("addr : %p |    out_fd : %d\n", &lst->out_fd, lst->out_fd);
		printf("addr : %p | isbuiltin : %d\n", &lst->isbuiltin, lst->isbuiltin);
		printf("addr : %p | lst->next\n", lst->next);
		printf("---------------------------------\n");
		lst = lst->next;
	}

}
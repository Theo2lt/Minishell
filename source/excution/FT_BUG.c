
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


void ft_sim_exec_lst_BUG(t_exec *lst)
{
	while (lst)
	{
		int i;
		int y;

		y = -1;
		i = 1;
        printf("\n---------------------------------\n");
        printf("				CMD					\n");
        printf("---------------------------------\n");
		if(!lst->args)
			printf("addr : %p | CMD_ARG (NULL) \n", lst->args);
		else
		{	
			printf("addr : %p |    CMD_ARG : ", lst->tabs_exeve);
			while (lst->tabs_exeve[++y])
				printf("[%s]",lst->tabs_exeve[y]);
			printf("\n");
			y = 0;
		}
		printf("addr : %p |     in_fd : %d\n", &lst->infile, lst->infile);
		printf("addr : %p |    out_fd : %d\n", &lst->outfile, lst->outfile);
		//printf("addr : %p | isbuiltin : %d\n", &lst->isbuiltin, lst->isbuiltin);
		printf("addr : %p | lst->next\n", lst->next);
		printf("---------------------------------\n");
		lst = lst->next;
		i++;
	}

}


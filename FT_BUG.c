
#include "minishell.h"

void ft_BUG(t_env *lst)
{
	while (lst)
	{
        printf("\n---------------------------------\n");
        printf(" < &NOEUD > addr : %p \n",lst);
        printf("---------------------------------\n");
		printf("addr : %p | %s\n", lst->variable_name, lst->variable_name);
		printf("addr : %p | %s\n", lst->variable_value, lst->variable_value);
		printf("addr : %p | lst->next\n", lst->next);
		printf("---------------------------------\n");
		lst = lst->next;
	}

}
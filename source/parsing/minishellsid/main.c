/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sredjini <sredjini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 00:59:30 by sredjini          #+#    #+#             */
/*   Updated: 2022/07/20 01:49:23 by sredjini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "minishell.h"

t_env *copy_env(char **env)
{
    int i;
    t_env   *first;
    t_env   *copy;
    t_env   *new;

    i = 0;
    copy = ft_lstnew();
    copy->str = ft_strdup(env[i]);
    first = copy;
    while (env[i])
    {
        new = ft_lstnew();
        new->str = ft_strdup(env[i]);
        ft_lstadd_back(&copy, new);
        copy = new;
        i++;
    }
    return (first);
}

int main(int ac, char **av, char **env)
{
    char *str;
    (void)ac;
    (void)av;
    t_pars *pars;
    pars = malloc(sizeof(t_pars));
    pars->env = copy_env(env);
    str= malloc(sizeof(char));
    /*
    while (pars->env)
    {
        printf("%s\n", pars->env->str);
        pars->env = pars->env->next;
    }
    */
    while(1)
    {
        free(str);
        str = readline(MINISHELL);
        add_history(str);
        if(lexer_shell(&str, pars) == 1)
        {
            //free(str);
            //free(pars);
            //return (0);
            //printf("lol\n");
        }        
        if (!ft_strncmp(str, "exit", 4))
        {
            free(str);
            free(pars);
            exit(0);
        }
    }
    return (0);
}
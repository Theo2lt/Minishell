/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remplace_expand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sredjini <sredjini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 01:07:01 by sredjini          #+#    #+#             */
/*   Updated: 2022/07/21 05:36:11 by sredjini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "minishell.h"

char	*ft_init_pars(char *str, t_pars *pars)
{
	int i;
  	int j;
	char	*tmp;
	
	i = - 1;
	while (str[++i])
	{	
        if (str[i] == '$' && str[i + 1]  && (ft_isalpha(str[i + 1])
			|| str[i + 1] == '_'))
	    {
		//	printf("ICI %c ICI + 1 %c\n", str[i], str[i + 1]);
		    j = i + 1;
		    while (str[j] && (ft_isalnum(str[j]) || str[j] == '_'))
			    j++;
			tmp = str;
		    str = ft_save_pos_expand(tmp, 1, i + 1, j, pars);
			//free(tmp);
		//    printf("replace str final %s\n", str);
			i--;
        }
		else if (str[i] == '$' && str[i + 1] && ft_isdigit(str[i + 1]))
		{
			tmp = str;
		//	printf("ICI2 %c ICI2 + 1 %c\n", str[i], str[i + 1]);
		    str = ft_save_pos_expand(tmp, 1, i + 1, i + 2, pars);
		//	free(tmp);
		//    printf("replace str final %s\n", str);
			i--;
		}
		// if(!str[i])
		// 	break ;
	}
//	printf("3 chaine avant de free %s\n",str);
	return (str);
}

char *ft_save_pos_expand(char *str, int quote, int i, int j, t_pars *pars)
{
	char	*tmp;
	t_env 	*temp;
	
	temp = pars->env;
	(void)quote;
	while(temp)
	{
		if (ft_strncmp(str + i,temp->str, j - i) == 0)
		{
			tmp = str;
			str = ft_replace(tmp, ft_strchr(temp->str, '=') + 1, i, j);
			free(tmp);
			return (str);
		}
		temp = temp->next;
	}
	tmp = str;
	str = ft_replace(tmp, NULL, i , j);
	free(tmp);
	return (str); 
}

char	*ft_replace(char *str, char *node, int i, int j)
{
	char	*new;
	char	*tmp;

    new = ft_substr(str, 0, i - 1);
	tmp = new;
//	printf("debug %s str i %c\n", new, str[i]);
	if (node)
	{
		new = ft_strjoin(tmp, node);
		free(tmp);
		tmp = new;
		new = ft_strjoin(tmp, str + j);
		free(tmp);
		return (new);
	}
    new = ft_strjoin(tmp, str + j);
	free(tmp);
	return (new);
}

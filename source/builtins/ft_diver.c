/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_diver.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliot <tliot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 06:55:49 by tliot             #+#    #+#             */
/*   Updated: 2022/08/08 13:01:24 by tliot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

char *ft_joint_free_S1_S2(char *str1, char *str2)
{
    char *str_join;

    str_join = NULL;
    str_join = ft_strjoin(str1, str2);
    if(str1)
        free(str1);
    if(str2)
        free(str2);

    return (str_join);
}
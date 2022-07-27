/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliot <tliot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 00:54:39 by tliot             #+#    #+#             */
/*   Updated: 2022/07/27 00:57:50 by tliot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
#define BUILTINS_H

#include <Minishell.h>

/// FONCTION BUILTINS ///
int ft_exec_pwd(void);
int ft_exec_echo(char **cmd);
int	ft_exec_cd(char **cmd, t_env **lst);
char *ft_get_pwd(void);
int ft_exec_env(t_env *lst);
int ft_exec_export(char **cmd, t_env **lst);
void ft_exec_unset(char **name, t_env **lst);
int	ft_is_built(char **cmd);
int ft_manage_builting(char **cmd, t_env **lst);
void ft_exit(t_env *lst);

#endif
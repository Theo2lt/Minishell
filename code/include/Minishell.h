/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engooh <engooh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 19:57:17 by engooh            #+#    #+#             */
/*   Updated: 2022/07/21 23:08:21 by engooh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHEL_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h> 
# include "libft.h"

void	ft_converte_quotes(char *str);
char	*ft_parser_pipe_utils(char *str, int stop);
char	*ft_parser_chevron_utils(char *str, char c);
int		ft_parser_quote_chevron_pipe(char *str);
int		parser(char *str);
#endif

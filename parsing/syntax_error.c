/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:50:17 by oelharbi          #+#    #+#             */
/*   Updated: 2024/06/07 18:43:01 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	syntax_printer(char *str)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("'\n", 2);
}

int	systax_error(t_parser *lst)
{
	if (lst->class == PIPE)
		return (syntax_printer(lst->string), lst->class = ERROR, 1);
	while (lst)
	{
		if ((lst->class == PIPE && !lst->next) || lst->class == ERROR
			|| (lst->class == PIPE && lst->next->class == PIPE))
			return (syntax_printer(lst->string), lst->class = ERROR, 1);
		else if (lst->class == QUOTE_ERR)
			return (syntax_printer("unclosed quote"), lst->class = ERROR, 1);
		else if (lst->class == HERDOC || lst->class == REDIN
			|| lst->class == REDOUT || lst->class == APPEND)
		{
			if (lst->next == NULL)
				return (syntax_printer("newline"), lst->class = ERROR, 1);
			else if (lst->next->class == REDIN || lst->next->class == REDOUT
				|| lst->next->class == APPEND || lst->next->class == HERDOC
				|| lst->next->class == PIPE)
				return (syntax_printer(lst->next->string),
					lst->next->class = ERROR, 1);
		}
		lst = lst->next;
	}
	return (0);
}

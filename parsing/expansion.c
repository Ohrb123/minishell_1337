/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 14:33:53 by oelharbi          #+#    #+#             */
/*   Updated: 2024/06/07 19:11:21 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	classing(t_parser **expand)
{
	t_parser	*tmp;
	int			count_quotes;

	count_quotes = count_quote((*expand)->string);
	if (count_quotes > 0 && (*expand)->class != LIM)
	{
		(*expand)->string = remove_quotes(&(*expand)->string, count_quotes);
		if (!(*expand)->string)
			return ;
	}
	(count_quotes == -1) && ((*expand)->class = QUOTE_ERR);
	if (!(*expand)->class)
		(*expand)->class = COMMAND;
	tmp = *expand;
	while (tmp)
	{
		if (!tmp->class)
			tmp->class = ARGUMENT;
		tmp = tmp->next;
	}
	expand = &tmp;
}

int	is_space(char *str)
{
	while (str && *str)
	{
		if (ft_iswhitespace(*str))
			return (1);
		str++;
	}
	return (0);
}

int	expansion_error(char c)
{
	if (c == '_' || c == '?')
		return (0);
	else if (!ft_isalpha(c))
		return (1);
	return (0);
}

char	*var_value(char	*var)
{
	if (ft_strchr(var, '='))
		return (ft_strchr(var, '=') + 1);
	return (NULL);
}

void	ex_set(t_minishell *mini, char **str, t_exp_helper *help, t_list *data)
{
	t_list	*tmp;

	help->start = ft_start((*str));
	if (!help->start || expansion_error((*str)[help->start]))
		return ;
	if ((*str)[help->start] == '?')
		return (exit_number(mini, &(*str), help->start));
	help->end = ft_end((*str), help->start);
	help->exp_name = ft_substr((*str), help->start, help->end - help->start);
	if (!help->exp_name)
		ft_exit(mini, NULL, NULL, 12);
	tmp = var_finder(help->exp_name, &data);
	if (!tmp)
	{
		(*str) = NULL;
		return ;
	}
	help->exp_env = tmp->env;
	free(help->exp_name);
	(*str) = remove_str(str, var_value(help->exp_env), help->start, \
	help->end - help->start);
}

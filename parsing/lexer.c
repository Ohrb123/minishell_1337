/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 14:45:19 by oelharbi          #+#    #+#             */
/*   Updated: 2024/06/06 18:48:31 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_shift(char *str, int start, int end, int shifter)
{
	ft_memmove(&(str[end]), &(str[start]), ft_strlen(&(str[start])) + 1);
	if (shifter == -1)
		str[start] = ' ';
	if (shifter == 1)
		str[end] = ' ';
}

char	*put_spaces(char **str, int space_count)
{
	int		i;
	char	*new_str;

	(1 == 1) && (new_str = NULL, i = 0, new_str = allocator(str, space_count));
	if (!new_str)
		return (NULL);
	while (new_str[i])
	{
		if (ft_isoperator(new_str[i]))
		{
			if (i > 0 && !ft_iswhitespace(new_str[i - 1]))
				(ft_shift(new_str, i, i + 1, -1), i++);
			if (new_str[i] != '|')
				while (new_str[i + 1] == '<' || new_str[i + 1] == '>')
					i++;
			if (!ft_iswhitespace(new_str[i + 1]) && new_str[i + 1] != '\0')
				(ft_shift(new_str, i, i + 1, 1), i++);
		}
		if (ft_isqoute(new_str[i]))
			i = get_quote_index(new_str, i + 1);
		i++;
	}
	return (new_str);
}

int	ft_count_spaces(char *str)
{
	int	i;
	int	space_counter;
	int	is_space;

	(1 == 1) && (i = 0, space_counter = 0, is_space = 0);
	while (str[i])
	{
		(ft_isqoute(str[i])) && (i = get_quote_index(str, i + 1));
		if (ft_isoperator(str[i]))
		{
			if (i > 0 && !ft_iswhitespace(str[i - 1]))
				space_counter++;
			if (str[i] != '|')
				while (str[i + 1] == '<' || str[i + 1] == '>')
					i++;
			if (!ft_iswhitespace(str[i + 1]) && str[i + 1] != '\0')
				(1 == 1) && (space_counter++, is_space = 1);
		}
		else
			is_space = 0;
		i++;
	}
	return (space_counter);
}

void	add_2d_spaces(t_minishell **mini, int space_counter)
{
	(*mini)->input = put_spaces(&(*mini)->input, space_counter);
	if (!(*mini)->input)
		ft_exit((*mini), NULL, NULL, 12);
	(*mini)->cmd = ft_split((*mini)->input, SPACES);
	(free((*mini)->input), (*mini)->input = NULL);
	if (!(*mini)->cmd)
		ft_exit((*mini), NULL, NULL, 12);
}

void	lexer(t_minishell *minishell)
{
	int	i;
	int	space_counter;

	i = 0;
	space_counter = ft_count_spaces(minishell->input);
	if (space_counter == 0)
	{
		minishell->cmd = ft_split(minishell->input, SPACES);
		(free(minishell->input), minishell->input = NULL);
		if (!minishell->cmd)
			ft_exit(minishell, NULL, NULL, 12);
	}
	else
		add_2d_spaces(&minishell, space_counter);
}

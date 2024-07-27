/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classification.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 09:36:44 by oelharbi          #+#    #+#             */
/*   Updated: 2024/06/07 19:39:50 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	operator(t_parse_state *state, t_parser *current)
{
	if (!current->class)
	{
		if (*current->string == '|')
			(1) && (current->class = PIPE, *state = START);
		else if (*current->string == '<')
		{
			(1) && (handle_redirection(current, REDIN), *state = IN_FILE);
			if (current->class == HERDOC && current->next && \
			*current->next->string != '<' && *current->next->string != '<' )
				(1) && (current->next->class = LIM, *state = IN_HEREDOC);
		}
		else if (*current->string == '>')
			(1) && (handle_redirection(current, REDOUT), *state = IN_FILE);
	}
}

void	some_thing_else(t_parse_state *state, t_parser *current)
{
	if (!current->class)
	{
		if (current->string == NULL)
			(1) && (current->class = NLL, *state = START);
		else if (*state == START || *state == IN_HEREDOC)
			(1) && (current->class = COMMAND, *state = IN_COMMAND);
		else if (*state == IN_COMMAND)
			(1) && (current->class = ARGUMENT, *state = IN_COMMAND);
		else
			(1) && (current->class = FILE, *state = START);
	}
}

void	classification(t_minishell *mini, t_list *data)
{
	t_parser		*current;
	t_parse_state	state;
	int				count_quotes;

	(1) && (current = mini->lst, state = START, count_quotes = 0);
	while (current)
	{
		(operator(&state, current), parameter_expansion(mini, current, data));
		count_quotes = count_quote(current->string);
		if (count_quotes > 0 && current->class != LIM)
		{
			current->string = remove_quotes(&current->string, count_quotes);
			if (!current->string)
				ft_exit(mini, NULL, NULL, 12);
		}
		(count_quotes == -1) && (current->class = QUOTE_ERR);
		if (!current->class)
			some_thing_else(&state, current);
		current = current->next;
	}
}

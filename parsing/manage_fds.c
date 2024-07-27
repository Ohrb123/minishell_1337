/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_fds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:35:05 by oelharbi          #+#    #+#             */
/*   Updated: 2024/06/06 20:10:13 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	manage_fds(t_minishell *mini)
{
	int	index;

	index = 0;
	while (index < mini->list_size)
	{
		if (!mini->final_cmd[index].redirection_in)
		{
			if (index == 0)
				mini->final_cmd[index].in_fd = 0;
			else
				mini->final_cmd[index].in_fd = TUBE;
		}
		if (!mini->final_cmd[index].redirection_out)
		{
			if (index == mini->list_size - 1)
				mini->final_cmd[index].out_fd = 1;
			else
				mini->final_cmd[index].out_fd = TUBE;
		}
		open_fds(mini, index);
		index++;
	}
}

char	*remove_quotes(char **str, int count_quotes)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	j = 0;
	new_str = zyalloc(((ft_strlen(*str) - count_quotes) + 1) \
	* sizeof(char), 'a', true);
	while ((*str)[j])
	{
		if ((*str)[j] != '\"' && (*str)[j] != '\'')
			new_str[i++] = (*str)[j];
		j++;
	}
	new_str[i] = '\0';
	return (free(*str), *str = NULL, new_str);
}

void	handle_redirection(t_parser *current, int class)
{
	if (class == REDIN)
	{
		if (!current->string[1])
			current->class = REDIN;
		else if (current->string[1] == '<' && !current->string[2])
			current->class = HERDOC;
		else
			current->class = ERROR;
	}
	else
	{
		if (!current->string[1])
			current->class = REDOUT;
		else if (current->string[1] == '>' && !current->string[2])
			current->class = APPEND;
		else
			current->class = ERROR;
	}
}

t_parser	*lstadd_middle(t_parser *lst, t_parser *new, char *str)
{
	t_parser	*prev;
	t_parser	*curr;
	t_parser	*last_of_new;

	if (!lst || !new)
		return (lst);
	if (lst->string == str && !lst->next)
		return (new);
	prev = NULL;
	curr = lst;
	last_of_new = new;
	while (curr && curr->next && curr->string != str)
	{
		prev = curr;
		curr = curr->next;
	}
	last_of_new = lstlast(new);
	last_of_new->next = curr->next;
	if (prev)
		prev->next = new;
	else
		lst = new;
	return (lst);
}

void	lstadd_front(t_parser **lst, t_parser *new, char *str)
{
	t_parser	*last_of_new;

	if (!(*lst) || !new)
		return ;
	last_of_new = new;
	if ((*lst)->string == str && (*lst)->next)
	{
		last_of_new = lstlast(new);
		last_of_new->next = (*lst)->next;
	}
	*lst = new;
}

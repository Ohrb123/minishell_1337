/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 23:54:13 by oelharbi          #+#    #+#             */
/*   Updated: 2024/06/07 18:24:00 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_parser	*lstnew(void *content)
{
	t_parser	*head;

	head = zyalloc(sizeof(t_parser), 'a', true);
	head->string = content;
	head->next = NULL;
	return (head);
}

t_parser	*lstlast(t_parser *lst)
{
	if (!lst)
		return (NULL);
	while (lst && lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	lstadd_back(t_parser **lst, t_parser *new)
{
	t_parser	*last;

	new->class = 0;
	if (!lst || !new)
		return ;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	last = lstlast(*lst);
	last->next = new;
}

void	lstclear(t_parser **lst)
{
	t_parser	*current;
	t_parser	*next;

	if (!lst || !(*lst))
		return ;
	current = *lst;
	while (current)
	{
		next = current->next;
		current = next;
	}
	*lst = NULL;
}

int	count_quote(char *str)
{
	char	current_quote;
	int		count;

	current_quote = '\0';
	count = 0;
	while (str && *str)
	{
		if (*str == '\'' || *str == '\"')
		{
			if (current_quote == '\0')
				(1 == 1) && (current_quote = *str, count++);
			else if (*str == current_quote)
				(1 == 1) && (current_quote = '\0', count++);
		}
		str++;
	}
	if (current_quote != '\0')
		return (-1);
	return (count);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_k.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 17:35:58 by hbettal           #+#    #+#             */
/*   Updated: 2024/06/06 18:56:57 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fds_closer(int end[])
{
	close(end[0]);
	close(end[1]);
}

void	free_handler(char **str)
{
	int	i;

	i = 0;
	while (str[i++])
		free(str[i]);
	free (str);
}

void	ft_lstdel_mid(t_list **data, t_list *rm)
{
	t_list	*first;

	first = *data;
	if (rm == first)
	{
		*data = rm->next;
		ft_lstdelone(rm);
		return ;
	}
	if (rm)
	{
		while (first->next)
		{
			if (first->next == rm)
				break ;
			first = first->next;
		}
		if (rm->next)
			first->next = rm->next;
		else
			first->next = NULL;
	}
	ft_lstdelone(rm);
}

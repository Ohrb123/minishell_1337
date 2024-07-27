/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 13:37:44 by hbettal           #+#    #+#             */
/*   Updated: 2024/06/01 21:42:33 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	unset_build(char **var, t_list **data)
{
	int		i;
	t_list	*tmp;

	i = 0;
	while (var[++i])
	{
		export_parse(var[i]);
		tmp = var_finder(var[i], data);
		ft_lstdel_mid(data, tmp);
	}
}

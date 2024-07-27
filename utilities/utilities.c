/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 18:28:33 by hbettal           #+#    #+#             */
/*   Updated: 2024/06/05 11:39:19 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*where_path(t_list *data)
{
	t_list	*path;

	path = var_finder("PATH", &data);
	if (!path)
		return (NULL);
	if (path->env + 4 && path->env + 5)
		return (path->env + 5);
	return (NULL);
}

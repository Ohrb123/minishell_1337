/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelharbi <oelharbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 10:45:13 by oelharbi          #+#    #+#             */
/*   Updated: 2024/05/22 15:26:10 by oelharbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*tp_dest;
	char	*tp_src;
	size_t	i;

	tp_dest = (char *) dst;
	tp_src = (char *) src;
	i = 0;
	if (tp_dest == NULL && tp_src == NULL)
		return (NULL);
	while (i < n)
	{
		tp_dest[i] = tp_src[i];
		i++;
	}
	return (tp_dest);
}

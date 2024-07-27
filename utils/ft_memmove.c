/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelharbi <oelharbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 19:32:12 by oelharbi          #+#    #+#             */
/*   Updated: 2024/05/22 15:26:14 by oelharbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_memmove(void *dst, void *src, size_t len)
{
	char	*dest;
	char	*source;

	if (!dst && !src)
		return (NULL);
	dest = (char *)dst;
	source = (char *)src;
	if (dst < src)
		ft_memcpy(dst, src, len);
	else if (dst > src)
	{
		while (len > 0)
		{
			len--;
			dest[len] = source[len];
		}
	}
	return (dst);
}

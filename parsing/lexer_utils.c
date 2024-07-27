/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelharbi <oelharbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:05:36 by oelharbi          #+#    #+#             */
/*   Updated: 2024/06/05 00:42:07 by oelharbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isoperator(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

int	ft_isqoute(char c)
{
	if (c == '\"' || c == '\'')
		return (1);
	return (0);
}

int	ft_iswhitespace(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	get_quote_index(char *str, int i)
{
	char	qoute;

	qoute = str[i - 1];
	while (str[i] && str[i] != qoute)
		i++;
	if (!str[i])
		return (i - 1);
	return (i);
}

char	*ft_join(char *s1, char *buff)
{
	char	*str;
	int		i;
	int		x;

	if (!s1)
	{
		s1 = zyalloc(1, 'a', true);
		s1[0] = '\0';
	}
	if (!buff)
		return (free(s1), NULL);
	(1 == 1) && (i = ft_strlen(s1), x = ft_strlen(buff) + ft_strlen(s1) + 1);
	str = zyalloc(x, 'a', true);
	(ft_strlcpy(str, s1, i + 1), ft_strlcat(str, buff, x));
	return (free(s1), s1 = NULL, str);
}

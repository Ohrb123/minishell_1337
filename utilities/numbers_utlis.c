/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numbers_utlis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 19:43:43 by hbettal           #+#    #+#             */
/*   Updated: 2024/06/07 18:08:37 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	no_overflow(int sign, unsigned long long n, int count)
{
	if ((n > LLONG_MAX || count > 19) && sign == -1)
		return (0);
	if ((n > LLONG_MAX || count > 19) && sign == 1)
		return (-1);
	return (n * sign);
}

int	ft_atoi(const char *str)
{
	int					i;
	int					count;
	int					sign;
	unsigned long long	n;

	(1) && (i = 0, count = 0, sign = 1, n = 0);
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] == '0')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = (n * 10) + (str[i++] - '0');
		count++;
	}
	return (no_overflow(sign, n, count));
}

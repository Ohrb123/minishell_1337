/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 11:24:39 by hbettal           #+#    #+#             */
/*   Updated: 2024/06/07 18:20:49 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_helper(t_minishell *mini, char *status)
{
	size_t	i;

	i = -1;
	(void)mini;
	if (!status)
	{
		write(2, "exit\nminishell: exit: ", 22);
		write(2, status, ft_strlen(status));
		(write(2, " numeric argument required\n", 27), exit(255));
	}
	if (status[0] == '-' || status[0] == '+')
		i++ ;
	while (status[++i])
	{
		if (!ft_isdigit(status[i]))
		{
			write(2, "exit\nminishell: exit: ", 22);
			write(2, status, ft_strlen(status));
			(write(2, " numeric argument required\n", 27), exit(255));
		}
	}
}

void	exit_build(t_minishell *mini, char **status)
{
	int		i;
	char	**nums;

	i = -1;
	nums = NULL;
	if (status[1])
	{
		nums = ft_split(status[1], " ");
		exit_helper(mini, nums[0]);
		if (nums[1])
		{
			write(2, "exit\nminishell: exit: ", 22);
			write(2, status[1], ft_strlen(status[1]));
			(write(2, " numeric argument required\n", 27), exit(255));
		}
		if (status[2])
		{
			write(2, "exit\nminishell: exit: too many arguments\n", 41);
			mini->exit_status = 1;
			return ;
		}
		(write(2, "exit\n", 5), exit(ft_atoi(status[1])));
	}
	(write(2, "exit\n", 5), exit(mini->exit_status));
}

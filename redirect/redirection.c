/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 10:41:37 by hbettal           #+#    #+#             */
/*   Updated: 2024/06/06 18:55:35 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_fd(t_minishell *mini, t_pex *pex, int type)
{
	if (mini->final_cmd[pex->i].in_fd == -1 && type)
		exit(1);
	if (mini->final_cmd[pex->i].in_fd == TUBE)
	{
		if (dup2(pex->end[0], 0) == -1)
			fds_closer(pex->end);
	}
	else
	{
		if (dup2(mini->final_cmd[pex->i].in_fd, 0) == -1)
			return (fds_closer(pex->end));
	}
	if (mini->final_cmd[pex->i].out_fd == TUBE && mini->list_size > 1)
	{
		if (dup2(pex->end[1], 1) == -1)
			return (fds_closer(pex->end));
	}
	else
	{
		if (dup2(mini->final_cmd[pex->i].out_fd, 1) == -1)
			return (fds_closer(pex->end));
	}
}

char	*limiter_parse(char *lim)
{
	char	**split;
	char	*tmp;
	int		i;

	i = -1;
	tmp = NULL;
	split = NULL;
	if (ft_strchr(lim, '\"'))
		split = ft_split(lim, "\"");
	else if (!ft_strchr(lim, '\"'))
		split = ft_split(lim, "\'");
	while (split[++i])
	{
		lim = ft_strjoin(tmp, split[i]);
		free(tmp);
		tmp = lim;
	}
	free_handler(split);
	return (lim);
}

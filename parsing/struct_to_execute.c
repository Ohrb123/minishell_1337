/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_to_execute.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 21:30:47 by oelharbi          #+#    #+#             */
/*   Updated: 2024/06/07 19:28:38 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	struct_cmd(t_minishell *mini, t_list *data)
{
	int	i;

	i = 0;
	mini->list_size = lstsize(mini->lst);
	mini->final_cmd = zyalloc(sizeof(t_final_st) * mini->list_size, 'a', true);
	while (i < mini->list_size)
		mini->final_cmd[i++].cmd = NULL;
	i = 0;
	while (i < mini->list_size)
	{
		mini->final_cmd[i].redirection_in = NULL;
		mini->final_cmd[i].redirection_out = NULL;
		if (!set_cmd_line(mini, i))
			return (0);
		if (!open_files(mini, i, data))
			return (1);
		i++;
	}
	manage_fds(mini);
	return (1);
}

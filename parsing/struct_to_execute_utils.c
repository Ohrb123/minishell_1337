/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_to_execute_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 21:34:46 by oelharbi          #+#    #+#             */
/*   Updated: 2024/06/07 19:36:15 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	lstsize(t_parser *lst)
{
	int			pipe_line;
	t_parser	*curr;

	pipe_line = 1;
	curr = lst;
	while (curr)
	{
		if (curr->class == PIPE)
			pipe_line++;
		curr = curr->next;
	}
	return (pipe_line);
}

int	set_cmd_line(t_minishell *mini, int i)
{
	t_parser	*curr;
	int			cmd_size;
	int			index;

	curr = get_pipe(mini->lst, i);
	cmd_size = get_cmd_size(mini, i);
	mini->final_cmd[i].cmd = zyalloc(sizeof(char *) \
	* (cmd_size + 1), 'a', true);
	index = 0;
	while (index < cmd_size)
	{
		if (curr->class == ARGUMENT || curr->class == COMMAND)
			mini->final_cmd[i].cmd[index++] = curr->string;
		curr = curr->next;
	}
	mini->final_cmd[i].cmd[index] = NULL;
	return (1);
}

int	get_cmd_size(t_minishell *mini, int i)
{
	int			cmd_size;
	t_parser	*curr;

	cmd_size = 0;
	curr = get_pipe(mini->lst, i);
	while (curr && curr->class != PIPE)
	{
		mini->final_cmd[i].in_fd = -2;
		mini->final_cmd[i].out_fd = -2;
		if (curr->class == ARGUMENT || curr->class == COMMAND)
			cmd_size++;
		if (curr->class == HERDOC || curr->class == REDIN)
			mini->final_cmd[i].redirection_in = curr;
		if (curr->class == APPEND || curr->class == REDOUT)
			mini->final_cmd[i].redirection_out = curr;
		curr = curr->next;
	}
	return (cmd_size);
}

t_parser	*get_pipe(t_parser *lst, int i)
{
	int			index;
	t_parser	*curr;

	index = 0;
	curr = lst;
	if (i == 0)
		return (curr);
	while (curr && index < i)
	{
		if (curr->class == PIPE)
			index++;
		curr = curr->next;
	}
	return (curr);
}

int	open_files(t_minishell *mini, int i, t_list *data)
{
	t_parser	*curr;
	int			her_fd;

	her_fd = 0;
	curr = get_pipe(mini->lst, i);
	while (curr && curr->class != PIPE)
	{
		if (curr->class == HERDOC && curr->next->class != ERROR)
		{
			her_fd = ft_here_doc(mini, curr->next->string, data);
			if (her_fd == -1)
				return (signal(SIGINT, SIG_DFL), signals(mini), 0);
			if (curr == mini->final_cmd[i].redirection_in)
				mini->final_cmd[i].in_fd = her_fd;
			else
				close (her_fd);
		}
		if (curr->class == ERROR)
		{
			(1) && (mini->exit_status = 258, mini->syntax = 1);
			return (ft_close_fds(mini), 0);
		}
		curr = curr->next;
	}
	return (1);
}

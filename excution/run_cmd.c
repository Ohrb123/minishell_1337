/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 08:07:55 by hbettal           #+#    #+#             */
/*   Updated: 2024/06/07 17:30:59 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	middle_commands(t_pex *pex, t_list **data, t_minishell *mini)
{
	char	*path;
	char	**commands;

	if (fork() == 0)
	{
		check_fd(mini, pex, 1);
		if (build_check(mini, data, pex))
			exit(mini->exit_status);
		else
		{
			commands = mini->final_cmd[pex->i + 1].cmd;
			if (dup2(pex->input, 0) < 0)
				(write (2, "dup2 failed", 11), exit(1));
			close(pex->input);
			path = path_check(commands[0], *data, pex->end);
			if (!commands || !path)
				(fds_closer(pex->end), exit(1));
			fds_closer(pex->end);
		}
		execve(path, commands, mini->new_env);
		exit(1);
	}
}

pid_t	last_cmd(t_pex *pex, t_list **data, t_minishell *mini)
{
	char	*path;
	char	**commands;
	pid_t	id;

	commands = NULL;
	id = fork();
	if (id == 0)
	{
		pex->i++;
		check_fd(mini, pex, 1);
		if (build_check(mini, data, pex))
			exit(mini->exit_status);
		else
		{
			commands = mini->final_cmd[pex->i].cmd;
			path = path_check(commands[0], *data, pex->end);
			if (!commands || !path)
				exit(1);
			fds_closer(pex->end);
		}
		execve(path, commands, mini->new_env);
		exit(mini->exit_status);
	}
	return (id);
}

void	first_cmd(t_list **data, t_pex *pex, t_minishell *mini)
{
	char	*path;
	char	**commands;

	if (fork() == 0)
	{
		check_fd(mini, pex, 1);
		if (build_check(mini, data, pex))
			exit(mini->exit_status);
		else
		{
			commands = mini->final_cmd[0].cmd;
			if (!commands)
				(fds_closer(pex->end), exit(1));
			path = path_check(commands[pex->i], *data, pex->end);
			if (!path)
				(fds_closer(pex->end), exit(1));
			fds_closer(pex->end);
		}
		(execve(path, commands, mini->new_env), exit(1));
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 16:14:13 by hbettal           #+#    #+#             */
/*   Updated: 2024/06/05 11:03:03 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cd_dir(char *dir, t_minishell *mini)
{
	char	*curr_dir;

	if (!access(dir, F_OK) && access(dir, R_OK))
	{
		(printf("cd: permission denied: %s\n", dir), mini->exit_status = 1);
		return (0);
	}
	if (dir[0] == '-' && !dir[1])
	{
		curr_dir = getcwd(NULL, 0);
		if (chdir(mini->last_dir) == -1)
			(printf("cd: No such file or directory\n"), mini->exit_status = 1);
		else
			(free(mini->last_dir), mini->last_dir = curr_dir);
		(free(mini->curr_dir), mini->curr_dir = getcwd(NULL, 0));
		return (printf("%s\n", mini->curr_dir), 0);
	}
	else if (dir[0] == '~' && !dir[1])
	{
		(free(mini->last_dir), mini->last_dir = getcwd(NULL, 0));
		if (chdir(getenv("HOME")) == -1)
			(printf("cd: No such file or directory\n"), mini->exit_status = 1);
		return (0);
	}
	return (1);
}

void	cd_build(char **dir, t_minishell *mini)
{
	if (!dir[1])
	{
		if (mini->last_dir != mini->curr_dir)
			free(mini->last_dir);
		mini->last_dir = getcwd(NULL, 0);
		if (chdir(getenv("HOME")) == -1)
			(printf("cd: No such file or directory\n"), mini->exit_status = 1);
		free(mini->curr_dir);
		mini->curr_dir = getcwd(NULL, 0);
		return ;
	}
	if (!cd_dir(dir[1], mini))
		return ;
	else
	{
		free(mini->last_dir);
		mini->last_dir = getcwd(NULL, 0);
		if (!mini->last_dir)
			printf("cd: error retrieving current directory: getcwd: cannot access \
parent directories: No such file or directory\n");
		if (chdir(dir[1]) == -1)
			(printf("cd: No such file or directory\n"), mini->exit_status = 1);
		(free(mini->curr_dir), mini->curr_dir = getcwd(NULL, 0));
		return ;
	}
}

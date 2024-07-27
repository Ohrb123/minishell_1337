/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 10:47:15 by hbettal           #+#    #+#             */
/*   Updated: 2024/06/07 19:15:07 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*empty_env(t_list *data, t_minishell *mini)
{
	ft_lstadd_back(&data, ft_lstnew(mini->defult_path));
	ft_lstadd_back(&data, ft_lstnew(ft_strdup("OLDPWD")));
	ft_lstadd_back(&data, ft_lstnew(ft_strjoin("PWD=", mini->curr_dir)));
	ft_lstadd_back(&data, ft_lstnew("SHLVL=1"));
	ft_lstadd_back(&data, ft_lstnew(ft_strdup("_=/usr/bin/env")));
	return (data);
}

t_list	*fill_env(char **origin_env, t_list *data, t_minishell *mini)
{
	int		i;
	t_list	*tmp;
	char	*str;
	char	*ctmp;

	i = -1;
	if (!origin_env[0])
		data = empty_env(data, mini);
	else
		while (origin_env[++i])
			ft_lstadd_back(&data, ft_lstnew(origin_env[i]));
	(1) && (tmp = data, str = tmp->env, ctmp = NULL, i = 0);
	while (tmp->next)
	{
		str = ft_strjoin_three(ctmp, " ", tmp->next->env);
		if (i)
			free(ctmp);
		ctmp = str;
		tmp = tmp->next;
		i++;
	}
	mini->new_env = ft_split(str, " ");
	(free(str), indexer(&data));
	return (data);
}

void	env_build(t_list *data, char *cmd)
{
	if (!data)
		return ;
	if (cmd)
	{
		printf("env: %s: No such file or directory\n", cmd);
		return ;
	}
	if (!ft_strncmp(data->env, "PATH=", 5))
		data = data->next;
	while (data)
	{
		if (ft_strchr(data->env, '='))
			printf("%s\n", data->env);
		data = data->next;
	}
}

void	ft_shlvl(t_list *data, t_minishell *m)
{
	t_list	*tmp;
	int		level;
	char	**var;
	char	*ctmp;
	char	*str;

	tmp = var_finder("SHLVL", &data);
	var = ft_split(tmp->env, "=");
	level = ft_atoi(var[1]) + 1;
	tmp->env = ft_strjoin("SHLVL=", ft_itoa(level));
	(1) && (tmp = data, ctmp = tmp->env, level = 0);
	while (tmp->next)
	{
		str = ft_strjoin_three(ctmp, " ", tmp->next->env);
		if (level)
			free(ctmp);
		(1) && (ctmp = str, tmp = tmp->next, level++);
	}
	m->new_env = ft_split(str, " ");
}

void	ft_pwd(t_list	*data, t_minishell *m)
{
	t_list	*tmp;

	if (!data)
		return ;
	tmp = var_finder("PWD", &data);
	if (tmp)
		tmp->env = ft_strjoin("PWD=", m->curr_dir);
	tmp = var_finder("OLDPWD", &data);
	if (tmp)
		tmp->env = ft_strjoin("OLDPWD=", m->last_dir);
	else if (!tmp)
		ft_lstadd_back(&data, ft_lstnew(ft_strjoin("OLDPWD=", m->last_dir)));
}

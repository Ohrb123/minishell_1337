/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:45:00 by hbettal           #+#    #+#             */
/*   Updated: 2024/06/06 20:00:01 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	indexer(t_list **data)
{
	t_list	*tmp;
	t_list	*cur;
	int		index;

	tmp = *data;
	index = 0;
	while (tmp)
	{
		index = 0;
		cur = *data;
		while (cur)
		{
			if (ft_strncmp(tmp->env, cur->env, LONG_MAX) > 0)
				index++;
			cur = cur->next;
		}
		tmp->index = index;
		tmp = tmp->next;
	}
}

t_list	*var_finder(char *var, t_list **data)
{
	t_list	*tmp;

	tmp = *data;
	while (tmp)
	{
		if (!ft_strncmp(tmp->env, ft_strjoin(var, "="), ft_strlen(var) + 1))
			return (tmp);
		else if (!ft_strncmp(tmp->env, var, ft_strlen(tmp->env)))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void	add_variable(char *var, t_list **data, char **sps, char *vr)
{
	t_list	*tmp;
	char	*t;
	int		i;

	(1) && (tmp = *data, i = ft_strlen(sps[0]));
	if (!vr && !var_finder(sps[0], data))
		(ft_lstadd_back(data, ft_lstnew(var)));
	if (sps[0][i - 1] != '+' && vr)
	{
		if (!var_finder(sps[0], data))
			(ft_lstadd_back(data, ft_lstnew(var)));
		else if (ft_strchr(var, '='))
			(1) && (tmp = var_finder(sps[0], data), tmp->env = var);
	}
	else if (sps[0][i - 1] == '+' && vr)
	{
		(1) && (t = ft_substr(sps[0], 0, i - 1), tmp = var_finder(t, data));
		if (!tmp)
			return ;
		t = tmp->env;
		if (ft_strchr(tmp->env, '='))
			tmp->env = ft_strjoin(t, vr);
		else
			tmp->env = ft_strjoin_three(t, "=", vr);
	}
}

void	creat_var(char **var, t_list **data, int i)
{
	char	**sps;
	char	*vr;

	while (var[i] && var[i][0])
	{
		if (var[i][0] == '=' || var[i][0] == '+')
		{
			print_error(var[i], "not a valid identifier");
			i++;
			continue ;
		}
		sps = ft_split(var[i], "=");
		if (!export_parse(sps[0]))
		{
			i++;
			free_handler(sps);
			continue ;
		}
		vr = ft_strchr(var[i], '=') + 1;
		if (sps[0])
			add_variable(var[i], data, sps, vr);
		indexer(data);
		free_handler(sps);
		i++;
	}
}

void	export_build(char **var, t_list **data)
{
	int		i;
	t_list	*tmp;

	tmp = *data;
	i = -1;
	if (!var[1] || !var[1][0])
	{
		while (++i < ft_lstsize(*data))
		{
			tmp = *data;
			while (tmp)
			{
				if (tmp->index == i && ft_strncmp(tmp->env, "PATH=/usr", 9))
					printf("declare -x %s\n", tmp->env);
				tmp = tmp->next;
			}
		}
		return ;
	}
	creat_var(var, data, 1);
}

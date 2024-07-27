/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelharbi <oelharbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 19:37:21 by oelharbi          #+#    #+#             */
/*   Updated: 2024/06/05 01:22:04 by oelharbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	prompt_custom(t_minishell *minishell)
{
	char	*username;
	char	*final;
	char	*n_arrow;
	char	*cur_dir;
	char	*dir;

	if (minishell->trm_prompt != NULL)
		free(minishell->trm_prompt);
	cur_dir = get_dir(minishell);
	username = ft_strjoin(GREEN_ARROW, minishell->username);
	dir = ft_strjoin(SPC, cur_dir);
	n_arrow = ft_strjoin(username, dir);
	final = ft_strjoin(n_arrow, X);
	free(username);
	free(dir);
	free(n_arrow);
	free(cur_dir);
	minishell->trm_prompt = final;
}

char	*get_dir(t_minishell *minishell)
{
	int		i;
	char	*pwd;
	char	**words;
	char	*dir;

	(void)minishell;
	words = NULL;
	i = 0;
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return (NULL);
	if (ft_strncmp(pwd, "/", ft_strlen(pwd)) == 0)
		dir = ft_strdup("/");
	else
	{
		words = ft_split(pwd, "/");
		while (words[i])
			i++;
		dir = ft_strdup(words[--i]);
		free_strings(words);
	}
	free(pwd);
	return (dir);
}

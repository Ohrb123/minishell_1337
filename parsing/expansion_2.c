/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 18:47:25 by hbettal           #+#    #+#             */
/*   Updated: 2024/06/07 19:11:31 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*allocator(char **str, int n)
{
	char	*result;

	n += ft_strlen(*str);
	result = zyalloc(sizeof(char) * (n + 1), 'a', true);
	ft_strlcpy(result, *str, n + 1);
	free(*str);
	return (result);
}

void	check_spaces(t_parser *current, t_minishell *mini)
{
	t_parser		*expand;
	char			**spl;
	int				i;

	expand = NULL;
	i = -1;
	spl = ft_split(current->string, SPACES);
	if (!spl)
		return ;
	while (spl[++i])
		lstadd_back(&expand, lstnew(spl[i]));
	classing(&expand);
	if (mini->lst->string != current->string)
		current = lstadd_middle(mini->lst, expand, current->string);
	else
		lstadd_front(&mini->lst, expand, current->string);
}

void	parameter_expansion(t_minishell *mini, t_parser *current, t_list *data)
{
	t_exp_helper	help;
	int				i;
	int				count;

	i = -1;
	count = 0;
	help.exp_counter = expansion_counter(current->string);
	while (help.exp_counter--)
	{
		if (current->class != LIM)
			ex_set(mini, &current->string, &help, data);
		if (is_space(current->string))
		{
			check_spaces(current, mini);
		}
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 02:08:56 by hbettal           #+#    #+#             */
/*   Updated: 2024/06/07 17:11:38 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_sig = 0;

int	h_start(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (i + 1);
		i++;
	}
	return (0);
}

void	exp_set(t_minishell *mini, char **str, t_list *data)
{
	int		start;
	int		end;
	char	*exp_name;
	char	*exp_env;
	t_list	*tmp;

	start = h_start((*str));
	if (!start || expansion_error((*str)[start]))
		return ;
	if ((*str)[start] == '?')
		return (exit_number(mini, &(*str), start));
	end = ft_end((*str), start);
	exp_name = ft_substr((*str), start, end - start);
	if (!exp_name)
		ft_exit(mini, NULL, NULL, 12);
	tmp = var_finder(exp_name, &data);
	if (!tmp)
		return ((*str) = NULL, (void)0);
	exp_env = tmp->env;
	free(exp_name);
	(*str) = remove_str(str, var_value(exp_env), start, \
	end - start);
	if (!(*str))
		ft_exit(mini, NULL, NULL, 12);
}

char	*file_name(char *file)
{
	int		i;
	char	*unique;
	char	*tmp;

	i = 0;
	tmp = file;
	while (1)
	{
		unique = ft_itoa(i);
		file = ft_strjoin_three(tmp, "_", unique);
		if (access(file, F_OK) == -1)
			return (free(unique), file);
		free(unique);
		if (i)
			free(file);
		i++;
	}
	return (NULL);
}

void	sig_handler(int sig_num)
{
	(void)sig_num;
	write (1, "\n", 1);
	g_sig = 1;
	close(0);
}

int	ft_here_doc(t_minishell *mini, char *lim, t_list *data)
{
	char	*str;
	int		fd;
	char	*file;
	bool	exp;

	(1) && (exp = true, file = file_name("/tmp/secret_file"));
	fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
		return (free(lim), 0);
	if (ft_strchr(lim, '\'') || ft_strchr(lim, '\"'))
		exp = false;
	lim = limiter_parse(lim);
	signal(SIGINT, sig_handler);
	while (1)
	{
		str = readline("heredoc> ");
		if (g_sig == 1)
			return (free(lim), free(str), close(fd), g_sig = 0, -1);
		if (!str || !ft_strncmp(str, lim, INT_MAX))
			return (free(lim), free(str), close(fd), fd = open(file, O_RDONLY));
		if (exp == true)
			exp_set(mini, &str, data);
		(write(fd, str, ft_strlen(str)), write(fd, "\n", 1), free(str));
	}
	return (-1);
}

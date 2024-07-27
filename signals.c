/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:15:24 by oelharbi          #+#    #+#             */
/*   Updated: 2024/06/07 18:21:35 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signals(t_minishell *mini)
{
	remove_c(&mini->term);
	signal(SIGINT, sig_init);
	signal(SIGQUIT, SIG_IGN);
}

void	sig_init(int signum)
{
	if (waitpid(-1, NULL, WNOHANG) == 0)
		return ;
	if (signum == SIGINT)
	{
		write(1, "\n", 2);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	remove_c(struct termios *term)
{
	struct termios	term_removal;

	tcgetattr(1, term);
	tcgetattr(1, &term_removal);
	term_removal.c_lflag &= ~ECHOCTL;
	tcsetattr(1, TCSAFLUSH, &term_removal);
}

void	sig_quit(int signum)
{
	ft_putstr_fd("Quit: ", 2);
	ft_putnbr_fd(signum, 2);
	ft_putchar_fd('\n', 2);
}

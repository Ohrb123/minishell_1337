/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:04:22 by oelharbi          #+#    #+#             */
/*   Updated: 2024/06/07 18:46:11 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// INCLUDES

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include <errno.h>
# include <limits.h>
# include <string.h>
# include <sys/stat.h>
# include <termios.h>
# include <sys/types.h>
# include <dirent.h>
# include <stdarg.h>
# include <stdbool.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

// CLASSES

# define PIPE 1
# define REDIN 2
# define HERDOC 3
# define LIM 4
# define REDOUT 5
# define COMMAND 6
# define ARGUMENT 7
# define FILE 8
# define ERROR 9
# define APPEND 10
# define QUOTE_ERR 11
# define NLL 12

// DEFINES

# define TUBE -1337
# define HR -42
# define GREEN_ARROW "\001\e[1m\e[32m➜  \001\e[1m\e[34m\002"
# define X "\001\e[1m\e[33m\002 ✘ \001\e[0m\002"
# define SPACES " \t\n\v\r\f"
# define SPC "\001\e[1m\e[33m\002 "

// GET_NEXT_LINE

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

// STRUCTS

typedef struct s_pex
{
	int		i;
	int		end[2];
	int		input;
	int		lines;
}	t_pex;

typedef struct s_list
{
	char			*env;
	int				index;
	struct s_list	*next;
}	t_list;

typedef enum e_parse_state
{
	START,
	IN_COMMAND,
	IN_ARG,
	IN_FILE,
	IN_HEREDOC,
	IN_ERROR
}			t_parse_state;

typedef struct s_garbage
{
	void				*adr;
	bool				is_free;
	struct s_garbage	*next;
}		t_garbage;

typedef struct s_exp_helper
{
	int		exp_counter;
	int		start;
	int		end;
	char	*exp_name;
	char	*exp_env;
}		t_exp_helper;

typedef struct s_parser
{
	char			*string;
	int				class;
	struct s_parser	*next;
}		t_parser;

typedef struct s_final_st
{
	char		**cmd;
	int			in_fd;
	int			out_fd;
	t_parser	*redirection_in;
	t_parser	*redirection_out;
}	t_final_st;

typedef struct s_minishell
{
	t_parser		*lst;
	t_final_st		*final_cmd;
	int				list_size;
	char			**cmd;
	char			**new_env;
	char			*cmd_path;
	int				exit_status;
	char			*defult_path;
	char			*input;
	int				signal;
	int				*pids;
	int				env_status;
	int				syntax;
	struct termios	term;
	char			*buffer;
	char			*trm_prompt;
	char			*username;
	char			*last_dir;
	char			*curr_dir;
	t_list			**data;
}		t_minishell;

// SIGNALS

void		signals(t_minishell *mini);
void		remove_c(struct termios *term);
void		sig_init(int signum);
void		sig_quit(int signum);

// READLINE

void		read_line(t_minishell *mini);

// LEXER

char		*allocator(char **str, int n);
int			ft_count_spaces(char *str);
void		lexer(t_minishell *minishell);
char		*put_spaces(char **str, int space_counter);
void		ft_shift(char *str, int start, int end, int shifter);

// LEXER_UTILS

int			ft_iswhitespace(char c);
int			ft_isoperator(char c);
int			ft_isqoute(char c);
int			get_quote_index(char *str, int i);
char		*ft_join(char *s1, char *buff);

// PARSING

char		*var_value(char	*var);
int			expansion_error(char c);
void		classing(t_parser **expand);
int			is_space(char *str);
void		ft_close_fds(t_minishell *mini);
void		lstadd_front(t_parser **lst, t_parser *new, char *str);
t_parser	*lstadd_middle(t_parser *lst, t_parser *new, char *str);
void		handle_redirection(t_parser *current, int class);
char		*remove_quotes(char **str, int count_quotes);
int			parsing(t_minishell *mini, t_list **data);
void		classification(t_minishell *mini, t_list *data);
void		parameter_expansion(t_minishell *mini, \
t_parser *current, t_list *data);
void		ex_set(t_minishell *mini, char **str, \
t_exp_helper *help, t_list *data);
int			export_parse(char *flags);
char		*var_value(char	*var);
void		check_spaces(t_parser *current, t_minishell *mini);
void		parameter_expansion(t_minishell *mini, \
t_parser *current, t_list *data);

// PARSING_UTILS

void		lstadd_back(t_parser **lst, t_parser *new);
t_parser	*lstlast(t_parser *lst);
t_parser	*lstnew(void *content);
int			count_quote(char *str);
void		lstclear(t_parser **lst);
char		*remove_quotes(char **str, int count_quotes);
void		handle_redirection(t_parser *current, int class);
int			expansion_counter(char *str);
int			ft_start(char *str);
int			ft_end(char *str, int start);
int			expansion_error(char c);
void		exit_number(t_minishell *mini, char **str, int start);
char		*remove_str(char **str, char *envvar, int start, int len);
void		syntax_printer(char *str);
int			systax_error(t_parser *lst);
void		ft_exit(t_minishell *mini, char *cmd, char *str, int ext);
void		free_strings(char **strings);
void		print_error(char *var, char *msg);
t_parser	*lstadd_middle(t_parser *lst, t_parser *new, char *str);
void		lstadd_front(t_parser **lst, t_parser *new, char *str);

// STCURT_TO_EXECUTE

int			lstsize(t_parser *lst);
int			struct_cmd(t_minishell *mini, t_list *data);
int			set_cmd_line(t_minishell *mini, int i);
int			get_cmd_size(t_minishell *mini, int i);
t_parser	*get_pipe(t_parser *lst, int i);
void		ft_close_fds(t_minishell *mini);
int			open_files(t_minishell *mini, int i, t_list *data);
void		manage_fds(t_minishell *mini);
void		open_fds(t_minishell *mini, int i);
void		close_fds(t_minishell *mini);
int			open_infd(t_parser *curr, t_parser *redirecyion_in);
int			open_outfd(t_parser *curr, t_parser *redirecyion_out);

// UTILS

void		ft_putchar_fd(char c, int fd);
void		ft_putnbr_fd(int n, int fd);
void		ft_putstr_fd(char *s, int fd);
char		**ft_split(char *s, char *c);
size_t		ft_strlen(const char *s);
size_t		ft_strlcpy(char *dest, const char *src, size_t dstsize);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memmove(void *dst, void *src, size_t len);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strdup(const char *s1);
char		*ft_substr(const char *s, unsigned int start, size_t len);
int			ft_isalnum(int c);
int			ft_isalpha(int c);
char		*ft_itoa(int n);
int			ft_isdigit(int c);
char		*ft_strjoin(char const *s1, char const *s2);

// PROMPT
void		prompt_custom(t_minishell *minishell);
char		*get_dir(t_minishell *minishell);

// GARBAGE_COLLECTOR

void		*zyalloc(size_t size, int flag, bool is_free);
void		cleanup(t_minishell *mini, int exit_status);

/******************** ===> EXCUTION	<=== ********************/

// BUILDTIONS

int			build_check(t_minishell *mini, t_list **data, t_pex *pex);
void		cd_build(char **cmd, t_minishell *mini);
void		pwd_build(t_minishell *mini);
void		echo_build(char	**word, t_minishell *mini);
void		exit_build(t_minishell *mini, char **status);
t_list		*fill_env(char **origin_env, t_list *data, t_minishell *mini);
void		env_build(t_list *data, char *cmd);
void		export_build(char **var, t_list **data);
void		unset_build(char **var, t_list **data);
void		indexer(t_list **data);
t_list		*var_finder(char *var, t_list **data);
void		ft_shlvl(t_list *data, t_minishell *m);
void		ft_pwd(t_list	*data, t_minishell *m);

// EXCUTING

void		single_command(t_minishell *mini, t_list **data);
void		middle_commands(t_pex *pex, t_list **data, t_minishell *mini);
pid_t		last_cmd(t_pex *pex, t_list **data, t_minishell *mini);
void		first_cmd(t_list **data, t_pex *pex, t_minishell *mini);
char		*path_check(char *command, t_list *data, int end[]);
void		fds_closer(int end[]);
int			ft_here_doc(t_minishell *mini, char *lim, t_list *data);
char		*where_path(t_list *data);
void		free_handler(char **str);
void		more_commands(t_pex *pex, t_list **data, t_minishell *mini);

// UTILITIES

char		*ft_strrchr(const char *s, int c);
void		ft_lstdelone(t_list *lst);
void		ft_lstdel_mid(t_list **data, t_list *rm);
void		ft_lstclear(t_list **lst);
t_list		*ft_lstnew(char *content);
void		ft_lstadd_back(t_list **lst, t_list *new);
int			ft_lstsize(t_list *lst);
char		*ft_strtrim(char *s1, char *set);
char		*ft_strjoin_three(char *s1, char *buff, char *s2);
int			ft_atoi(const char *str);
void		free_handler(char **str);
void		fds_closer(int end[]);
void		check_fd(t_minishell *mini, t_pex *pex, int type);
char		*limiter_parse(char *lim);

//GET_NEXT_LINE

char		*ft_strchr(char *s, char c);
char		*ft_join(char *s1, char *buff);

#endif
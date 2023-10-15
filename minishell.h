/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansulist <ansulist@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 10:49:23 by ansulist          #+#    #+#             */
/*   Updated: 2023/10/14 11:48:41 by ansulist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <readline/readline.h>
# include <stdlib.h>
# include <sys/types.h>
# include <dirent.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <errno.h>
# include <fcntl.h>
# include <stddef.h>
# include "./libft/libft.h"
# include <stdbool.h>

# define LLONG_MAX 9223372036854775807

typedef struct s_red
{
	char	*input;
	char	*output;
}t_red;

typedef struct s_data
{
	int		cmd_len;
	int		arg_len;
	char	*cmd;
	char	**args;
	char	**red;
	int		no_pipes;
	int		fd[2];
}t_data;

typedef enum e_operator
{
	NONE,
	PIPE,
	DOUBLE_LEFT_REDIRECTION,
	DOUBLE_RIGHT_REDIRECTION,
	RIGHT_REDIRECTION,
	LEFT_REDIRECTION,
}t_op;

typedef struct s_cmdop
{
	char	*name;
	char	**args;
	int		nb_args;
	t_op	operator;
}t_cmdop;

typedef struct s_env
{
	int		result;
	int		nb_struct;
	bool	fd_in;
	bool	fd_out;
	t_cmdop *origin;
	t_list	*vars;
}t_env;

typedef struct s_fill_vars
{
	int	i;
	int	counter;
}t_fill_vars;

void	initialize_prompt(t_env *env);
t_cmdop	*ft_splitline(char *str);
int		ft_isspace(char c);
int		check_pipes(char c);
int		check_redirection(char c);
int		check_quotes(char c);
int		check_syntaxerror(char *str);
int		check_semicolumn(char *str);
int		check_quotecount(char *str);
int		count_pipes(char *str);
int		count_pipes(char *str);
int		check_endline(char *str);
int		check_consecquotes(char *str);
int		check_quoteasafterred(char *str, int j);
char	*find_first_quote(char *str);
char	*remove_quotes(char *str);
int		skip_quoted_string(const char *s, int i);
char	**ft_newsplit(char const *s, char c);
int		ft_cerror(void);
char	*process_special_chars(char *string, char *special_chars);

int		ft_isspace(char c);
char	*rostring(char *str);
void	trim_spaces(char *input_string);
int		ft_strcmp(char *s1, char *s2);
int		ft_error(void);
void	ft_putchar(char c);
int		ft_echo(t_env *env, char **args);
t_env	*init_env(char **default_env);
int		add_env_variable(t_env *env, char *key, char *value);
void	delete_env_variable(t_env *env, char *key);
int		add_or_update(t_env *env, char *key, char *value);
int		update_env_variable(t_list *var, char *key, char *value);

char	*my_getenv(t_env *env, char *key);
char	*cut_path(char *str);
int		ft_chdir(char *path);
int		ft_move(t_env *env, char *path);
char	*save_env_var(t_env *env, char *key);
int		ft_cd(t_env *env, char *path);

char	*my_getenv(t_env *env, char *key);
int		display_export(t_env *env);
int		display_env_var(t_env *env, char *key);
int		print_env_value(t_env *env, char *key);
int		buildins(t_cmdop *cmd, t_env *env);
bool	is_buildins(t_cmdop *cmd);
int		exec_command_line(t_cmdop *command_line, int len, t_env *env);
int		one_heredoc(t_cmdop *command_line);
int		check_spaces(char *str);
int		pwd(void);
int		ft_free_twod_array(char **str);
char	**ft_order_alpha(t_env *env);
int		ft_export(t_env *env, char *cmd, char **args);

char	*join_free(char *s1, char *s2);
int		check_access(char **path_bin);
int		get_path_bin_one(char *path, char *cmd, char **path_bin);
int		get_path_bin_all(char **paths, char *cmd, char **path_bin);
int		free_and_print(char **path_bin);
int		free_and_print_denied(char **path_bin);
void	binary_command(t_env *env, char *cmd, char **args, int nb_args);

int		ft_unset(t_env *env, char *key, char **args);
int		pipeline_exec(t_cmdop *cmd, t_env *env, int len, bool ghost);
int		exec_command(t_cmdop *cmd, t_env *env);
int		left_redirect_exec(t_cmdop *cmd, t_env *env, int len);
int		right_redirect_exec(t_cmdop *cmd, t_env *env, int len);
int		display_env(t_env *env);

int		delete_env_variable_cmp(void *content, void *key);
void	delete_env_variable(t_env *env, char *key);
int		cmp_var(void *s1, void *s2);
t_env	*init_env(char **default_env);
void	display(void *content);
int		display_env(t_env *env);
int		add_env_variable(t_env *env, char *key, char *value);
void	delete_env_variable_free(void *content);
int		ft_env(t_env *env, t_cmdop *cmd);

t_op	is_operator(char *str);
void	count_struct_none(int *i, int *nb_struct, char **av);
void	count_struct_else(int *i, int *nb_struct);
int		count_struct(char **av);
int		fill_command_args(char **av, t_cmdop *command, int *i);
int		fill_command(char **av, t_cmdop *command, int *i);
int		command_set_op_and_name(t_cmdop *command,
			t_op op, char *name);
int		fill_struct(char **av, t_cmdop *command, int *i);
int		fill_structs(char **av, t_cmdop *command);
int		check_dollarsign(t_cmdop *cmd, int len, t_env *env);
int		ft_free_command_struct(t_cmdop **command, int nb_struct);
int		free_and_return(char **av, t_cmdop **command,
			int ret_val, int nb_struct);
int		init_struct(char *str, t_cmdop **command);

void	child_signal(int signal);
void	signal_controller(int sig_num);
void	redirect_input_char(t_cmdop *cmd);
bool	digits_or_signals(char *str);
bool	is_longlong(char *str);
void	ft_exit(t_cmdop *cmd, t_env *env);
bool	arestringsequal(const char *str1, const char *str2);
int		double_left_redirect_exec(t_cmdop *cmd, t_env *env, int len);
int		print_export(t_env *env);
int		cmp_var(void *s1, void *s2);

bool	is_valid_env_char(char c);
int		count_dollar_var_len(char *line, t_env *env, int *i);
bool	ignore_env_var(char *line, int i);

int		count_one(char *line, t_env *env, t_fill_vars *vars);
int		counter(char *line, t_env *env);
char	*ft_expand(char *line, t_env *env);
int		count_nbr(int nbr);
void	look_for_closure(char *line, int *j, char c);

int		count_nbr(int nbr);
void	config_signal(void);
void	signal_controller(int sig_num);
int		count_struct(char **av);
void	rl_replace_line(const char *text, int clear_undo);
int		ft_free_twod_array(char **str);
int		ft_free_command_struct(t_cmdop **command, int nb_struct);
int		free_command_struct(t_cmdop *cmd, int size_command);
void	trap_signals(void);
int		get_path_bin(t_env *env, char *cmd, char **path_bin);
void	free_env(t_env *env);
void	free_everything(t_env *env);
int		free_and_print_denied(char **path_bin);
int		left_redirect_one(t_cmdop *cmd, t_env *env, int len);
void	bye_minishell(t_env *env);

#endif

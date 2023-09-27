/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansulist <ansulist@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 10:49:23 by ansulist          #+#    #+#             */
/*   Updated: 2023/09/08 15:25:29 by ansulist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

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

#  define LLONG_MAX 9223372036854775807

typedef struct s_red 
{
    char *input;
    char *output;
} t_red;

typedef struct s_data
{
    int cmd_len;
    int arg_len;
    char *cmd;
    char **args;
    char **red;
    int no_pipes;
    int fd[2];
} t_data;

typedef enum e_operator {
    NONE,
    PIPE,
    DOUBLE_LEFT_REDIRECTION,
    DOUBLE_RIGHT_REDIRECTION,
    RIGHT_REDIRECTION,
    LEFT_REDIRECTION,
} t_operator;

typedef struct s_cmdop {
    char *name;
    char **args;
    int nb_args;
    t_operator operator;
} t_cmdop;

typedef struct s_env
{
    t_list *vars;
    int result;
} t_env;

void	initialize_prompt(char **av, t_env *env);
t_cmdop *ft_splitline(char *str);


int    ft_isspace(char c);
int		check_pipes(char c);
int		check_redirection(char c);
int 	check_quotes(char c);
int		check_syntaxerror(char *str);
int 	check_semicolumn(char *str);
int 	check_quotecount(char *str);
int	count_pipes(char *str);
int	count_pipes(char *str);
int		check_endline(char *str);
int	check_consecquotes(char *str);
int	check_quoteasafterred(char *str, int j);
void	remove_quotes(char *str);
char	**ft_newsplit(char const *s, char c);
int	ft_cerror(void);
char *process_special_chars(char *string, char *special_chars);

int		ft_isspace(char c);
char	*rostring(char* str);
void trim_spaces(char *input_string);
int		ft_strcmp(char *s1, char *s2);
int		ft_error(void);
void	ft_putchar(char c);
int ft_echo(t_env *env, char **args);
t_env *init_env(char **default_env);
int add_env_variable(t_env *env, char *key, char *value);
void delete_env_variable(t_env *env, char *key);
int add_or_update(t_env *env, char *key, char *value);
int update_env_variable(t_list *var, char *key, char *value);
int ft_cd(t_env *env, char *path);
char    *my_getenv(t_env *env, char *key);
int display_export(t_env *env);
int    display_env_var(t_env *env, char *key);
int	exec_command_line(t_cmdop *command_line, int len, t_env *env);
int pwd();
int	ft_export(t_env *env, char *cmd, char **args);
void    binary_command(t_env *env, char *cmd, char **args, int nb_args);
int ft_unset(t_env *env, char *key, char **args);
int pipeline_exec(t_cmdop *cmd, t_env *env, int len);
int exec_command(t_cmdop *cmd, t_env *env);
int    left_redirect_exec(t_cmdop *cmd, t_env *env, int len);
int    right_redirect_exec(t_cmdop *cmd, t_env *env, int len);
int display_env(t_env *env);
int	ft_env(t_env *env, t_cmdop *cmd);
int init_struct(char *str, t_cmdop **command);
void	child_signal(int signal);
void redirect_input_char(t_cmdop *cmd);
bool	digits_or_signals(char *str);
bool	is_longlong(char *str);
long long	ft_atoll(const char *str);
void    ft_exit(t_cmdop *cmd);
bool arestringsequal(const char *str1, const char *str2);
int    double_left_redirect_exec(t_cmdop *cmd, t_env *env, int len);
int print_export(t_env *env);
int cmp_var(void *s1, void *s2);
char *ft_expand(char *line, t_env *env);
void	config_signal(void);
int count_struct(char **av);
void rl_replace_line(const char *text, int clear_undo);

#endif

/*
echo "anita" >> toto.txt >> toto.txt >> toto.txt | ls

[
    "echo",
    "anita",
    ">>",
    "toto.txt",
    ">>",
    "toto.txt",
    ">>",
    "toto.txt",
    "|",
    "ls"
]

// < << >> > |

[
    [cmd: "echo", args: ["anita"]]
    [special: "double-redirect", file: "toto.txt"]
    [special: "double-redirect", file: "toto.txt"]
    [special: "double-redirect", file: "toto.txt"]
    [special: "pipe"]
    [cmd: "ls", args: []]
]

*/
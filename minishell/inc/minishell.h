/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkanyilm <42kocaeli.com.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 17:42:44 by kkanyilm          #+#    #+#             */
/*   Updated: 2024/02/22 14:52:44 by kkanyilm         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PROMPT "\033[35mminishell\033[0m$ "
# define SHELL_NAME "minishell"
# define ERR_MALLOC "malloc error"
# define ERR_QUOTE "quote error"
# define FT_FAILURE -1
# define FT_INVALID -2
# define FT_SIGST 0
# define FT_SIGHEREDOC 10
# define FT_SIGEXIT 11

# include <unistd.h>

extern int			g_signal;

enum e_token_type
{
	WORD,
	PIPE,
	BRACKET_OPEN,
	BRACKET_CLOSE,
	REDIR_IN,
	REDIR_OUT,
	SINGLE_QUOTE,
	DOUBLE_QUOTE
};

enum e_exit_vls
{
	EXIT_SET,
	EXIT_GET,
	EXIT_FIRST
};

typedef struct s_env
{
	char	*name;
	char	*value;
}			t_env;

typedef struct s_check
{
	int		i;
	int		j;
	int		k;
	int		is_command;
	int		check_flag;
	pid_t	pid;
	int		status;
	char	**args_arr;
	char	**env_arr;
	char	*path;
	char	*name;
	int		fd_out;
	int		fd_in;
	int		fd[2];
	t_env	**env;
}				t_check;

typedef struct s_file
{
	char	*name;
	int		double_op;
	int		fd;
}	t_file;

typedef struct s_content
{
	char				*content;
	enum e_token_type	type;
	int					is_append;
}			t_content;

typedef struct s_cmd
{
	char		*command;
	char		**flags_array;
	t_content	*content;
	t_file		*input_file;
	t_file		*output_file;
	pid_t		p_id;
}				t_cmd;

typedef struct s_token
{
	char				*content;
	enum e_token_type	type;
	int					is_append;
}						t_token;

// lexer functions
t_token				*lexer(char *input);
enum e_token_type	lexer_get_type(char *input);
int					lexer_token_text(char *input, int *i, t_token **token);
int					get_token_pipe(char *input, int *i, t_token **token);
int					get_token_bracket(char *input, int *i, t_token **token);
int					get_token_redirection(char *input, int *i, t_token **token);
int					get_token_quote(char *input, int *i, t_token **token);
int					get_token_text(char *input, int *i, t_token **token);
t_token				*add_token(t_token **tokens, char *content,
						enum e_token_type type, int is_append);
int					get_cmd_word(t_cmd **cmds, t_token *tokens, t_check *check);
int					get_cmd_redir_in(t_cmd **cmds,
						t_token *tokens, t_check *check);
int					get_cmd_redir_out(t_cmd **cmds,
						t_token *tokens, t_check *check);
int					check_isappend(char *input, int *i);

// parser functions
t_cmd				**parser(t_token *tokens);
int					ft_count_pipe(t_token *tokens);
void				free_files(t_file **files);
t_file				*first_file(char *name, int double_op);
t_file				*add_file(t_file **files, char *name, int double_op);
t_content			*add_content(t_content **contents,
						char *content, enum e_token_type type, int is_append);
t_check				init_check(void);
t_cmd				**init_cmd(t_token *tokens, t_check check);
char				**add_flag(char **flags, char *flag);

// signal functions
void				signal_init(void);

// utils functions
int					ft_strlen_array(char **array);
int					print_error(char *title, char *error_type);
int					print_error_command_not_found(char *command);
void				free_all(t_token **tokens, t_cmd **cmds);
void				free_tokens(t_token **tokens);
void				free_cmds(t_cmd **cmds);
int					command_count(t_cmd **cmds);
int					content_count(t_cmd *cmd);
char				**get_args_cmd(t_cmd *cmd);
char				**get_env_arr(t_env *env);
void				free_double_char(char **arr);
char				*ft_strndup(char *str, int n);
int					env_count(t_env *env);
int					is_white_space(char c);
int					flag_count(t_cmd *cmd);
int					get_total_command_count(t_cmd *cmd);
char				*ft_strjoin_char(char *s1, char c);
int					ft_strlen3(t_env *env);
int					add_old_env_to_new_env(t_env *env, t_env *new_env, int *i);
int					add_old_env_to_new_env_delete(t_env *env,
						t_env *n_enw, t_check *check);

// str join free
char				*ft_strjoin_free(char *s1, char *s2);

// env functions
t_env				*env_init(char	**envp);
char				*get_env(t_env *env, char *name);
t_env				*delete_env(t_env *env, char *name);
t_env				*add_env(t_env *env, char *name, char *value);
t_env				*change_env(t_env *env, char *name, char *value);
char				*read_env(char *name, t_env *env);
void				free_env(t_env *env);
int					is_exist_env(char *name, t_env *env);

// expander functions
t_token				*expand(t_token *tokens, t_env *env);
t_token				*appender(t_token *tokens);

// execute functions
int					execute_commands(t_cmd **cmds, t_env **env);
int					ft_echo(t_cmd *cmd);
int					ft_cd(t_cmd *cmd, t_env *env);
int					ft_pwd(void);
int					ft_export(t_cmd *cmd, t_env **env);
int					ft_unset(t_cmd *cmd, t_env **env);
int					ft_env(t_env *env);
int					ft_exit(t_cmd *cmd, t_env **envp, t_cmd **cmds);

// export utils
void				ft_only_export(t_env *env);
int					check_valid_name(char *name);
int					ft_env_arr_len(t_content *content);

//
int					execute_multi_command(t_cmd **cmds, t_env **env,
						int original_fd, int original_fd_in);
int					execute_builtin(t_cmd *cmd, t_env **env, t_cmd **cmds);
int					execute_command(t_cmd *cmd, t_env *env);
int					heredoc(t_cmd *cmd, int i);

// execute utils
int					is_a_path(char *command);
int					is_paths_define(t_env *env);
void				file_duplicate(t_cmd *cmd);
int					file_define_fd(t_cmd *cmd);
void				set_default_fd(int original_fd, int original_fd_in);

//path functions
char				*get_path(char *command, t_env *env);

//exit_value
int					ft_exit_value(enum e_exit_vls exit_status,
						int value, int *ev);

#endif
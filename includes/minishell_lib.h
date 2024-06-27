/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_lib.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 15:37:08 by cyferrei          #+#    #+#             */
/*   Updated: 2024/06/27 17:58:17 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_LIB_H
# define MINISHELL_LIB_H

/*all includes*/

# include "define.h"
# include "ft_printf.h"
# include "libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <sys/wait.h>
# include <stdbool.h>
# include <signal.h>

/*global var*/

extern int g_sig;

/*all structures*/

typedef struct s_tmp_files
{
	char	*file_name;
	struct s_tmp_files	*next;
}			t_tmp_files;

typedef struct s_exec
{
	pid_t	pid_1;
	pid_t	pid_2;
	pid_t	*pid;
	char	*cmd;
	char	*path;
	char	**path_cmd;
	char	*final_cmd;
	int infile;
	int outfile;
	int here_doc;
	int nb_cmd;
	int nb_node;
	int nb_tube;
	int tube[2];
	int *multi_tube;
	int index;
	char	**my_envp;
}			t_exec;

typedef struct s_prompt
{
	char				*usr_name;
	char				*usr_pwd;
	char				*usr_build_one;
	char				*usr_build_two;
	char				*usr_prompt;
}						t_prompt;
typedef struct s_cd
{
	int i;
	int j;
	char buffer[4096];
	char buffer_old[4096];
	char path_hu[4096];
} t_cd;
typedef struct s_signal
{
	int					signal;
}						t_signal;

typedef struct s_list_arg
{
	struct s_list_arg	*next;
	char				**key_and_val;
	// char				**cmd_and_arg;
	char				*final_cmd;
	char				*input_splited;
	char				result[4096];
	int					count_size;
	// ----variable pour ton exec ----
	char				**file_array;
	char				**tmp_cmd_array;
	char				**cmd_array;
	int					*array_sign;
	// -------------------------------
}						t_list_arg;



typedef struct s_data
{
	t_list_arg			*lst;
	t_list_arg			*tokenizer;
	t_list_arg			*sign_to_exe;
	t_prompt			*prompt;
	t_signal			*signal;
	t_exec				*exec;
	t_tmp_files			*tmp_files;
	int					i;
	int					j;
	int					pansement;
	int					pansement_2;
	int					flag; 
	int					sq_flag;
	int					quote_flag;
	//----new var----
	int					*arrayIntExpand;
	int					exit_status;
	int					sq;
	int					dq;
	size_t				key_len;
	int					spl;
	int					dbl;
	int					size;
}						t_data;

typedef int (*builtin_ptr)(t_data *);

typedef struct s_builtin
{
	builtin_ptr		*builtin_func;
	int				stdin_save;
	int				stdout_save;
}		t_builtin;

/**[PRINT FUNCTIONS]**/

void					print_lst(t_data *data, t_list_arg *lst);
void					print_lst_cmdarg(t_list_arg *lst);
void					print_lst_token(t_list_arg *lst);
void					print_prompt_struct(t_data *data);
void					print_exec_utils(t_data *data);

/**[BUILTINS FUNCTIONS]**/

int	is_a_builtin(t_list_arg *tok);
int					cmd_unset(t_data *data);
void					case_egal(t_data *data);
int					cmd_env(t_data *data);
int					pwd_cmd(t_data *data);
int					cmd_export(t_data *data);
void					case_plus_egal(t_data *data);
void					set_value(t_data *data, char **split_arg);
int						check_plus_egal(t_data *data);
t_data					*build_user_prompt(t_data *data);
void					concat_env_var(t_data *data, char *key, char *new);
int						check_egals(t_data *data);
int						check_export_cmd(t_data *data);
void					print_lst_export(t_list_arg *lst);
int						is_env_var(t_data *data, char **split_key);
void					create_new_var(t_data *data, char *key, char *value);
int					cmd_echo(t_data *data);
int						check_echo_cmd(t_data *data);
void					print_echo(t_data *data);
void	print_echo_flag(t_data *data, int start);
int ft_exit(t_data *data, char *input);
int	check_export_nothing(t_data *data);
void exec_cd_with_opt(t_data *data, t_list_arg *tmp, t_list_arg *save_current, char *buffer);
void exec_cd(t_data *data, t_list_arg *tmp, char *buffer, char *buffer_old, int buffer_size);
int no_arg(t_data *data, t_list_arg *tmp, char *path_hu);
int iterate_in_str(char *str);
void init_tool_box(t_cd *tool_box);
t_list_arg *find_key_user(t_data *data);
t_list_arg *find_key_old_pwd(t_data *data);
t_list_arg *find_key_pwd(t_data *data);
/**[PROMPT FUNCTIONS]**/

int						display_prompt(t_data *data);
t_data					*init_prompt(t_data *data);
void					free_prompt(t_data *data);

/**[UTILS FUNCTIONS]**/

void					free_split(char **split);

/**[PARSER FUNCTION LONGUE COMME MON AUBERGINE]**/

void					parser_list_init(t_data *data, char **envp);
t_list_arg				*ft_lst_arg_new(t_list_arg *new, char *content);
void					ft_lstadd_arg_back(t_list_arg **lst, t_list_arg *new);
t_list_arg				*ft_lst_arg_last(t_list_arg *lst);
void					ft_lst_arg_delone(t_list_arg *lst);
void					ft_lst_arg_clear(t_list_arg **lst);
void					parser_list_init(t_data *data, char **envp);
char					*parser(char *input, t_data *data);
void					msg_error_handler(int *signal, t_data *data);
int						check_quote(char *input, t_data *data);
t_data					*init_signal(t_data *data);
int						checker_err_pipe(char *input, t_data *data);
int						check_pipe(char *input, int i, t_data *data);
int	parse_cmd_arg(t_data *data);
char **split_tokenizer(t_list_arg *cmd, t_data *data);
int					sort_sign(t_list_arg *tmp, t_data *data);
void					ft_clear_tokenizer(t_data *data);
t_list_arg				*init_tokenizer(void);
char					*ft_strdup_cust(const char *source);
int						sign_cmp(char *str);
int						count_sign(char *input);
t_list_arg				*ft_lst_cut_new(char *content);
void					ft_lstadd_cut_back(t_list_arg **lst,
							t_list_arg *new_node);
int						ft_isws(char c);
char					*get_filename(char *str);
void					create_signed(t_list_arg *lst);
int						check_redir(char *input, int i, t_data *data);
int						checker_err(char *input, t_data *data);
char					*search_occurence(char *input, t_data *data);
int ft_current_directory(char *path,t_data *data);
void expander(t_data *data, char *input);
char	*expansion(char *input, t_data *data);
int	get_word_size(char *str);
char *flush_redir(char *str, t_data *data); 
void handle_double_quotes_flush(char *str, char *buffer, int *i, int *j, t_data *data, int flag_for_copy);
void handle_single_quotes_flush(char *str, char *buffer, int *i, int *j, t_data *data, int flag_for_copy);
char **split_pipe_cust(char *input, char c);
int skip_ws_prompt(t_data *data, char *input);
int syntax_checker(char *input, t_data *data);
int	unexpectedToken(char *input, t_data *data);
int	cutting_input(t_data *data, char *input); 
bool isSingleQuote(char c);
bool isDoubleQuote(char c);
bool ifPipe(char c);
int pipeAlone(char *input, int i);
 void handle_double_quotes_flush(char *str, char *buffer, int *i, int *j, t_data *data, int flag_for_copy);
 void handle_single_quotes_flush(char *str, char *buffer, int *i, int *j, t_data *data, int flag_for_copy);
int handle_signs(char *str, int *i);
int	to_next_q(char *str, char c);
void	write_part(const char *str, char *result, int size);
char	**split_tokenizer(t_list_arg *cmd, t_data *data);
/**[EXEC]**/

void	init_exec(t_data *data);
void	init_struct_exec(t_data *data);
void	init_files(t_data *data, t_list_arg *tok, int i);
void	exec_single_cmd(t_data *data);
int	nb_node(t_data *data);
char	*get_path(t_data *data);
void	free_exec(t_data *data);
void	 exec_sub_proc(t_data *data);
int	is_redir(t_list_arg *tok);
char	*build_cmd(t_data *data, t_list_arg *tok);
void	file_not_found(t_data *data, t_list_arg *tok);
void	cmd_not_found(t_data *data);
void	error_excve(t_data *data);
void	exec_one_pipe(t_data *data);
void	exit_error(char *str);
void	first_child_process(t_data *data);
void	second_child_process(t_data *data);
void	exec_multi_pipe(t_data *data);
void	init_tubes(t_data *data);
void	close_tubes(t_data *data);
void	children_process(t_data *data);
void	first_pipe(t_data *data, t_list_arg *tok);
void	last_pipe(t_data *data, t_list_arg *tok);
void	intermediate_pipe(t_data *data, t_list_arg *tok);
void	reset_in_out(t_data *data);
void	error_init(t_data *data, char *str);
void	error_cmd(t_data *data, t_list_arg *tok);
void	error_execve_multi(t_data *data, t_list_arg *tok);
void	file_not_found_multi(t_data *data, t_list_arg *tok);
void	init_files_multi(t_data *data, t_list_arg *tok, int i);
void	init_here_doc(t_data *data, t_list_arg *tok, int idx, char *file);
void	check_here_doc(t_data *data);
void	init_tmp_struct(t_data *data);
void	is_here_doc(t_data *data, t_list_arg *tok);
void rm_tmp_file(t_data *data);
void add_tmp_file(t_data *data, const char *file_name);
void	hd_or_rdr_no_cmd(t_data *data);
void free_tmp_struct(t_data *data);
void	hd_or_rdr_no_cmd_multi(t_data *data);
void error_dir_file_not_found(t_data *data, t_list_arg *tok);
void error_permission_denied(t_data *data, t_list_arg *tok);
void free_resources(t_data *data);
void cleanup_and_exit(t_data *data, int exit_code);
void setup_pipes(t_data *data, t_list_arg *tmp);
int	check_dir(char *file);
void error_is_a_dir_mup(t_data *data, t_list_arg *tok);
void error_cmd_single(t_data *data, t_list_arg *tok);
void cleanup_and_exit_single(t_data *data, int exit_code);
void free_resources_single(t_data *data);
void error_is_a_dir_sgl(t_data *data, t_list_arg *tok);
void error_permission_denied_sgl(t_data *data, t_list_arg *tok);
void error_cmd_op(t_data *data, t_list_arg *tok);
void cleanup_and_exit_op(t_data *data, int exit_code);
void free_resources_op(t_data *data);
void error_is_a_dir_op(t_data *data, t_list_arg *tok);
void error_permission_denied_op(t_data *data, t_list_arg *tok);
void	build_tab_env(t_data *data);
void 	print_env(t_data *data);
void	exec_builtin(t_data *data, int builtin);
void init_files_builtin(t_data *data, t_list_arg *tok, int i);

/**[SIGNALS]**/

void	handle_signal_prompt(void);
void	handle_signal_children(void);
void	ft_ctrl_c(int sig);
void	ft_ctrl_c_children(int sig);
void	ft_back_slash(int sig);

#endif
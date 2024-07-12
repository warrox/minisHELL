/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_lib.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 15:37:08 by cyferrei          #+#    #+#             */
/*   Updated: 2024/07/12 15:22:35 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_LIB_H
# define MINISHELL_LIB_H

/*all includes*/

# include "define.h"
# include "ft_printf.h"
# include "libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <sys/wait.h>

/*global var*/

// extern int				g_sig;

/*all structures*/

typedef struct s_exit_data
{
	int					i;
	char				str[4096];
	char				s_nbr[4096];
	int					nbr;
	char				*nbr_char;
	int					neg;
	int					quote;
	char				**tmp;
	int					count;
	int					j;
}						t_exit_data;

typedef struct s_tmp_files
{
	char				*file_name;
	struct s_tmp_files	*next;
	int					fd;
}						t_tmp_files;

typedef struct s_exec
{
	pid_t				pid_1;
	pid_t				pid_2;
	pid_t				*pid;
	char				*cmd;
	char				*path;
	char				**path_cmd;
	char				*final_cmd;
	int					infile;
	int					outfile;
	int					here_doc;
	int					nb_cmd;
	int					nb_node;
	int					nb_tube;
	int					tube[2];
	int					*multi_tube;
	int					index;
	char				**my_envp;
}						t_exec;

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
	int					i;
	int					j;
	char				buffer[4096];
	char				buffer_old[4096];
	char				path_hu[4096];
}						t_cd;
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

typedef struct s_tool
{
	int					i;
	int					j;
	int					tmp;
	int					ii;
	int					end;
	int					dq;
	int					len;
	char				*token_start;
	char				*temp;
	char				*temp_ptr;
	int					in_single_quote;
	int					in_double_quote;
	int					index;

}						t_tool;
typedef struct s_data
{
	t_list_arg			*lst;
	t_list_arg			*tokenizer;
	t_list_arg			*sign_to_exe;
	t_prompt			*prompt;
	t_signal			*signal;
	t_exec				*exec;
	t_tmp_files			*tmp_files;
	t_cd				tool_box;
	int					i;
	int					j;
	int					pansement;
	int					pansement_2;
	int					buffer_size;
	int					flag;
	int					flag_2;
	int					flag_s;
	int					flag_d;
	int					sq_flag;
	int					quote_flag;
	int					data_count;
	//----new var----
	int					exit_status;
	int					sq;
	int					dq;
	size_t				key_len;
	int					spl;
	int					dbl;
	int					size;
	int					signal_int;
	char				strexpanded[4096];
	char				*input;
	int					int_nbr;
	char				*input_cpy;
}						t_data;

typedef struct s_quote
{
	int					len;
	int					start;
	int					end;
	int					sf;
	int					df;
	int					i;
	int					j;
}						t_quote;

/**[PRINT FUNCTIONS]**/

void					print_lst(t_data *data, t_list_arg *lst);
void					print_lst_cmdarg(t_list_arg *lst);
void					print_lst_token(t_list_arg *lst);
void					print_prompt_struct(t_data *data);
void					print_exec_utils(t_data *data);

/**[BUILTINS FUNCTIONS]**/
int						count_word(char const *str, char c);
t_list_arg				*find_key_pwd(t_data *data);
int						is_a_builtin(t_list_arg *tok);
int						cmd_unset(t_data *data);
void					case_egal(t_data *data);
int						cmd_env(t_data *data);
int						pwd_cmd(t_data *data);
int						cmd_export(t_data *data);
int						is_valid_name(t_data *data);
void					case_plus_egal(t_data *data);
void					exec_case_egual(t_data *data, int i);
void					not_valid_identifier(char **split_cmd);
void					set_value(t_data *data, char **split_arg);
int						check_plus_egal(t_data *data);
t_data					*build_user_prompt(t_data *data);
void					concat_env_var(t_data *data, char *key, char *new);
int						check_egals(t_data *data);
int						check_export_cmd(t_data *data);
void					print_lst_export(t_list_arg *lst);
int						is_env_var(t_data *data, char **split_key);
void					create_new_var(t_data *data, char *key, char *value);
int						cmd_echo(t_data *data, t_list_arg *tok);
int						is_valid_flag_n(char *cmd);
int						check_echo_cmd(t_data *data);
void					print_echo(t_data *data, t_list_arg *tok);
void					print_echo_flag(t_data *data, int start);
int						ft_exit(t_data *data, char *input);
int						check_export_nothing(t_data *data);
void					exec_cd_with_opt(t_data *data, t_list_arg *tmp,
							t_list_arg *save_current, char *buffer);
void					exec_cd(t_data *data, t_list_arg *tmp, char *buffer,
							char *buffer_old);
int						no_arg(t_data *data, t_list_arg *tmp, char *path_hu);
int						iterate_in_str(char *str);
void					init_tool_box(t_data *data);
t_list_arg				*find_key_user(t_data *data);
t_list_arg				*find_key_old_pwd(t_data *data);
t_list_arg				*find_key_pwd(t_data *data);
void					init_check_quote(int *first_enter, int *signal,
							t_data *data);

/**[PROMPT FUNCTIONS]**/

int						display_prompt(t_data *data);
t_data					*init_prompt(t_data *data);
void					free_prompt(t_data *data);

/**[UTILS FUNCTIONS]**/

void					create_var_tab(t_data *data, t_list_arg *tmp, int i);
void					free_split(char **split);
void					free_tokenizer(t_list_arg *current);

/**[PARSER FUNCTION]**/

void					initexpandvariable(t_data *data);
void					passpartstring(int *flag, int *i, char *input);
void					token_ws(char **token_start, char **token_end);
void					s_pipe_init(t_tool *tool);
bool					redirsign(char c);
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
int						parse_cmd_arg(t_data *data);
char					**split_tokenizer(t_list_arg *cmd, t_data *data);
int						sort_sign(t_list_arg *tmp, t_data *data);
void					ft_clear_tokenizer(t_data *data);
t_list_arg				*init_tokenizer(void);
char					*ft_strdup_cust(const char *source);
int						sign_cmp(char *str);
int						count_sign(char *input);
t_list_arg				*ft_lst_cut_new(char *content);
void					ft_lstadd_cut_back(t_list_arg **lst,
							t_list_arg *new_node);
int						ft_isws(char c);
char					*gn(char *str, t_tool *tool);
void					create_signed(t_list_arg *lst);
int						check_redir(char *input, int i, t_data *data);
int						checker_err(char *input, t_data *data);
char					*search_occurence(char *input, t_data *data);
int						ft_current_directory(char *path, t_data *data);
void					expander(t_data *data, char *input);
char					*expansion(char *input, t_data *data);
int						get_word_size(char *str);
char					*flush_redir(char *str, t_data *data);
char					**split_pipe_cust(char *input, char c);
int						skip_ws_prompt(t_data *data, char *input);
int						syntax_checker(char *input, t_data *data);
int						unexpectedtoken(char *input, t_data *data);
int						cutting_input(t_data *data, char *input);
bool					is_single_quote(char c);
bool					is_double_quote(char c);
bool					if_pipe(char c);
int						pipe_alone(char *input, int i);
void					handle_double_quotes_flush(char *str, char *buffer,
							t_data *data);
void					handle_single_quotes_flush(char *str, char *buffer,
							t_data *data);
int						handle_signs(char *str, int *i);
int						to_next_q(char *str, char c);
void					write_part(const char *str, char *result, int size);
char					**split_tokenizer(t_list_arg *cmd, t_data *data);
char					**split_first_equal(const char *s);
void					*free_tab_clean(char *split[]);
bool					isexitcode(char *input, int *i);
bool					isSingleQuote(char c);
bool					isvariable(char *input, int *i);
char					*passtilnextquote(char *input, int *i, char *buffer,
							int *j);
bool					isheredoc(char *input, int *i);
int						triple_sign_checker(char *str, t_data *data);
void					fill_array_sign(t_data *data, char *str,
							t_list_arg *tmp);
int						sort_sign(t_list_arg *tmp, t_data *data);
int						get_word_size(char *str);
void					free_cleaned_array(char **array);
void					free_cleaned_str(char *str);
void					init_quote(t_quote *tool_box, char *str);
void					handle_single_quotes_t(char *str, t_data *data);
void					init_expand(t_data *data);

/**[EXEC]**/

int						init_exec(t_data *data);
void					init_struct_exec(t_data *data);
void					init_files(t_data *data, t_list_arg *tok, int i);
void					exec_single_cmd(t_data *data);
int						nb_node(t_data *data);
char					*get_path(t_data *data);
void					free_exec(t_data *data);
void					exec_sub_proc(t_data *data);
int						is_redir(t_list_arg *tok);
char					*build_cmd(t_data *data, t_list_arg *tok);
void					file_not_found(t_data *data, t_list_arg *tok);
void					cmd_not_found(t_data *data);
void					error_excve(t_data *data);
void					exec_one_pipe(t_data *data);
void					exit_error(char *str);
void					first_child_process(t_data *data);
void					check_and_dup_fisrt(t_data *data);
void					check_and_dup_second(t_data *data);
void					execute_builtin_first_pipe(t_data *data,
							t_list_arg *rpl, int i);
void					execute_builtin_second_pipe(t_data *data,
							t_list_arg *tmp, int i);
void					second_child_process(t_data *data);
void					exec_multi_pipe(t_data *data);
void					init_tubes(t_data *data);
void					check_dir_and_perm_op(t_data *data, t_list_arg *rpl);
void					close_tubes(t_data *data);
void					children_process(t_data *data);
void					first_pipe(t_data *data, t_list_arg *tok);
void					last_pipe(t_data *data, t_list_arg *tok);
void					intermediate_pipe(t_data *data, t_list_arg *tok);
void					reset_in_out(t_data *data);
void					init_outfile_cmd(t_data *data, t_list_arg *tok, int i);
void					init_outfile_builtin(t_data *data, t_list_arg *tok,
							int i);
void					error_init(t_data *data, char *str);
void					error_cmd(t_data *data, t_list_arg *tok);
void					error_execve_multi(t_data *data, t_list_arg *tok);
void					file_not_found_multi(t_data *data, t_list_arg *tok);
void					init_files_multi(t_data *data, t_list_arg *tok, int i);
void					init_here_doc(t_data *data, t_list_arg *tok, int idx,
							char *file);
void					check_here_doc(t_data *data);
void					init_tmp_struct(t_data *data);
void					is_here_doc(t_data *data, t_list_arg *tok);
void					rm_tmp_file(t_data *data);
void					add_tmp_file(t_data *data, const char *file_name);
void					hd_or_rdr_no_cmd(t_data *data);
void					free_tmp_struct(t_data *data);

void					hd_or_rdr_no_cmd_multi(t_data *data);
void					error_dir_file_not_found(t_data *data, t_list_arg *tok);
void					error_permission_denied(t_data *data, t_list_arg *tok);
void					free_resources(t_data *data);
void					cleanup_and_exit(t_data *data, int exit_code);
void					setup_pipes(t_data *data, t_list_arg *tmp);
int						check_dir(char *file);
void					error_is_a_dir_mup(t_data *data, t_list_arg *tok);
void					error_cmd_single(t_data *data, t_list_arg *tok);
void					cleanup_and_exit_single(t_data *data, int exit_code);
void					free_resources_single(t_data *data);
void					init_outfile(t_data *data, t_list_arg *tok, int i);
void					error_is_a_dir_sgl(t_data *data, t_list_arg *tok);
void					error_permission_denied_sgl(t_data *data,
							t_list_arg *tok);
void					error_cmd_op(t_data *data, t_list_arg *tok);
void					cleanup_and_exit_op(t_data *data, int exit_code);
void					free_resources_op(t_data *data);
void					exit_cmd_here_doc(t_data *data, t_list_arg *rpl);
void					execute_builtin_sub_proc(t_data *data, t_list_arg *rpl,
							int i);
void					error_is_a_dir_op(t_data *data, t_list_arg *tok);
void					exit_only_here_doc(t_data *data);
void					error_permission_denied_op(t_data *data,
							t_list_arg *tok);
void					build_tab_env(t_data *data);
void					print_env(t_data *data);
void					exec_builtin(t_data *data, t_list_arg *tok,
							int builtin);
void					execute_builtin(t_data *data, t_list_arg *tmp, int i);
void					check_open_files(t_data *data);
void					check_dir_and_perm(t_data *data, t_list_arg *tmp);
void					init_multi_pipe(t_data *data);
void					error_pid(t_data *data);
void					setup_and_check(t_data *data, t_list_arg *tmp);
void					check_dir_and_perm_sgl(t_data *data, t_list_arg *rpl);
void					init_files_builtin(t_data *data, t_list_arg *tok,
							int i);

/**[SIGNALS]**/

void					handle_signal_prompt(void);
void					handle_signal_children(void);
void					ft_ctrl_c(int sig);
void					ft_ctrl_c_children(int sig);
void					ft_back_slash(int sig);

void					exit_helper(t_data *data);
void					exit_args(t_data *data);
void					exit_num(t_data *data, char *nbr_char);
void					exit_quote(t_data *data, char *nbr_char, int nbr);
void					exit_minus(t_data *data, int nbr, char *nbr_char);
void					exit_plus(t_data *data, char *nbr_char, int nbr);
void					exit_normal(t_data *data, char *nbr_char, int nbr);
void					init_struct(t_exit_data *e, t_data *data);
void					check_plus_minus(char *input, t_exit_data *e);
void					check_helper(t_exit_data *e, t_data *data, char *input);
void					execute_exit(char *input, t_exit_data *e, t_data *data);
long					ft_atoi_long(const char *str);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executer.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/13 10:01:06 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/10/27 11:38:31 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
# define EXECUTER_H

# include <stdbool.h>
# include <unistd.h>
# include "../../hdr/structs.h"

# define MODE_RW_R_R 0644

/*-------------------------buildins-------------------------*/

void	padloper_echo(t_metadata *data, t_exec_list_sim *cmd_list);
void	padloper_cd(t_metadata *data, t_exec_list_sim *cmd_list);
void	padloper_pwd(t_metadata *data, t_exec_list_sim *cmd_list);
void	padloper_export(t_metadata *data, t_exec_list_sim *cmd_list);
void	padloper_unset(t_metadata *data, t_exec_list_sim *cmd_list);
void	padloper_env(t_metadata *data, t_exec_list_sim *cmd_list);
void	padloper_exit(t_metadata *data, t_exec_list_sim *cmd_list);

char	**allocate_env(char **src, t_metadata *data, int add_var);
char	**allocate_export(char **src, int *envp_size, int remove, int add);
void	add_env(char **padloper_env, char *var, int pos);
void	env_pointer_cpy(int envp_size, char **old, char **new);
char	**new_padloper_envp(char **original_envp,
			t_metadata *data, int *envp_size);
int		envcmp(char *s1, char *s2);
bool	env_has_value(char *var);
int		has_var(char **array, char *var);

bool	export_var_not_valid(char *var);
void	populate_export(int size, char **src, char **dst);
char	*export_strcpy(char *dest, char *src);
void	sort_env(t_metadata *data);
void	set_pwd(char **new_padloper_envp, int pos);

void	create_oldpwd(char *oldpwd, t_metadata *data);
bool	set_pwd_and_oldpwd(t_metadata *data, char *oldpwd);

void	open_necessary_infiles_bi(t_metadata *data, t_exec_list_sim *cmd_list);
void	open_necessary_outfiles_bi(t_metadata *data, t_exec_list_sim *cmd_list);
void	redirect_output_bi(t_metadata *data, t_exec_list_sim *cmd_list);
void	close_unused_fd_bi(t_metadata *data, t_exec_list_sim *cmd_list);

/*-------------------------executer-------------------------*/

void	executer(t_metadata *meta_data, t_exec_list_sim *cmd_list);

/*-------------------------file handling-------------------------*/

void	open_necessary_infiles(t_metadata *data, t_exec_list_sim *cmd_list);
void	open_necessary_outfiles(t_metadata *data, t_exec_list_sim *cmd_list);
void	redirect_input(t_metadata *data, t_exec_list_sim *cmd_list);
void	redirect_output(t_metadata *data, t_exec_list_sim *cmd_list);
void	close_unused_fd(t_metadata *data, t_exec_list_sim *cmd_list);

/*-------------------------path builder-------------------------*/

char	*path_builder(t_metadata *data, char *cmd);

/*-------------------------utils-------------------------*/

int		ft_sim_lstsize(t_exec_list_sim *lst);
bool	is_path(char *cmd);
void	close_and_check(int fd);

void	set_buildin_array(t_metadata *data);

void	free_2d_array(char **array);

/*-------------------------error handling-------------------------*/

void	print_error_exit(char *errorobject, int errnocopy, int exitcode);
void	builtin_error(char *program, char *object,
			int errnum, t_metadata *data);
void	error_too_many_arg(t_metadata *data);
char	*get_error_string(char *errno_string, int errnocopy);

/*-------------------------heredoc handling-------------------------*/

void	get_all_heredoc(t_metadata *data, t_exec_list_sim *cmd_list);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executer.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/13 10:01:06 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/10/06 15:06:49 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
# define EXECUTER_H

# include <stdbool.h>
# include <unistd.h>
# include "../../hdr/structs.h"

# define MODE_RW_R_R 0644
# define CNF_BUF_SIZE 18
# define AR_BUF_SIZE 19
# define EXISTING_VAR_HAS_NO_VALUE -61
# define EXPORTED_VAR_HAS_NO_VALUE 61

/*-------------------------buildins-------------------------*/

void	padloper_echo(t_metadata *data, t_exec_list_sim *cmd_list);
void	padloper_cd(t_metadata *data, t_exec_list_sim *cmd_list);
void	padloper_pwd(t_metadata *data, t_exec_list_sim *cmd_list);
void	padloper_export(t_metadata *data, t_exec_list_sim *cmd_list);
void	padloper_unset(t_metadata *data, t_exec_list_sim *cmd_list);
void	padloper_env(t_metadata *data, t_exec_list_sim *cmd_list);
void	padloper_exit(t_metadata *data, t_exec_list_sim *cmd_list);

char	**allocate_env(char **src, int *envp_size, int unset, int export);
char	**new_padloper_envp(char **original_envp, int *envp_size);
int		envcmp(char *s1, char *s2);

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

/*-------------------------heredoc handling-------------------------*/

void	get_all_heredoc(t_metadata *data, t_exec_list_sim *cmd_list);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ms_enums.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/09 20:34:21 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/11/09 20:36:32 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_ENUMS_H
# define MS_ENUMS_H

typedef enum e_pxstates
{
	STATE_CMD,
	STATE_RDIRIN,
	STATE_RDIROUT
}	t_pxstates;

typedef enum e_token_label
{
	LESS,
	LESSLESS,
	GREAT,
	GREATGREAT,
	PIPE,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	EXPAND,
	NO_LABEL
}		t_token_label;

typedef enum e_fin_states
{
	STATE_START,
	STATE_WS,
	STATE_SQUOTE,
	STATE_DQUOTE,
	STATE_EXPAND,
	STATE_COMMON,
	STATE_STXERROR
}	t_fin_state;

typedef enum e_file_flags
{
	RDIR_AMBIGUOUS = -3,
	RDIR_SINGLE = -2,
	RDIR_DOUBLE = -1
}	t_file_flags;

typedef enum e_exit_error_code
{
	CNF = -1,
	AR = -2,
	IS_DIR = -3,
	NOT_VALID = -4,
	NOT_SUPPORTED = -5,
	NOT_SUPPORTED_BOTH = -6,
	NOT_NUMERIC = -7,
	NOT_DIR = -8,
	TOO_MANY = -9,
	NO_PATH = -10,
	EMPTY = 0,
	ERRNO_NO_SUCH_FILE = 2,
	CMD_CANT_EXE = 126,
	CMD_NOT_FOUND = 127,
}				t_exit_error_code;

#endif

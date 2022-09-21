/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 13:03:39 by cchen             #+#    #+#             */
/*   Updated: 2022/09/18 09:31:07 by caruychen        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OP_H
# define OP_H

/*
  ALL SIZES ARE IN BYTES
*/

/*
  IND_SIZE: size of indirect address encoding
  REG_SIZE: size of each register entry (registry)
  DIR_SIZE: size of direct address encoding
*/
# define IND_SIZE			2
# define REG_SIZE			4
# define DIR_SIZE			REG_SIZE

/* Instruction's ACB (Argument coding byte) */
# define REG_CODE			1
# define DIR_CODE			2
# define IND_CODE			3

/* Game environment and champion settings */
# define MAX_ARGS_NUMBER	4
# define MAX_PLAYERS		4
# define MEM_SIZE			4096
# define IDX_MOD			512
# define CHAMP_MAX_SIZE		682

/* Defines assembly language characters */
# define COMMENT_CHAR		'#'
# define ALT_COMMENT_CHAR	';'
# define LABEL_CHAR			':'
# define DIRECT_CHAR		'%'
# define SEPARATOR_CHAR		','
# define LABEL_CHARS		"abcdefghijklmnopqrstuvwxyz_0123456789"

/* Champion name and description */
# define NAME_CMD_STRING	".name"
# define COMMENT_CMD_STRING	".comment"

/* Corewar register will have REG_NUMBER registries */
# define REG_NUMBER			16

/* Nummber of operators */
# define OP_NUMBER			16

/* Cycle and lives tracking macros */
# define CYCLE_TO_DIE		1536
# define CYCLE_DELTA		50
# define NBR_LIVE			21
# define MAX_CHECKS			10

/* Argument types: Register, Direct, Indirect
  * Register (Register mode):
    * Address field refers directly to data in register memory location.
  * Direct (Direct addressing mode):
    Address field refers directly to the memory location in which the
    data is stored.
  * Indirect (Indirect addressing mode):
    Address field contains memory location where the effective address of
    the data is stored
*/

typedef char	t_arg_type;

# define T_REG				1
# define T_DIR				2
# define T_IND				4
# define T_LAB				8

/* Binary file identifier, champion name and champion comment */
# define PROG_NAME_LENGTH	(128)
# define COMMENT_LENGTH		(2048)
# define COREWAR_EXEC_MAGIC	0xea83f3

typedef struct s_header
{
	unsigned int		magic;
	char				prog_name[PROG_NAME_LENGTH + 1];
	unsigned int		prog_size;
	char				comment[COMMENT_LENGTH + 1];
}					t_header;

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 11:01:44 by cchen             #+#    #+#             */
/*   Updated: 2022/10/07 09:33:50 by caruychen        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# include <stdio.h>
# include "definitions.h"
# include "Strings.h"

# define MSG_USAGE "Usage: ./asm <sourcefile.s>"
# define ARG_INVALID_EXT "Unrecognised file type"
# define ERR_MSG_EMPTY_FILE "ERROR: empty file"
# define ERR_MSG_NO_SOURCE "ERROR: Source memory not initialized"

# define RED "\033[0;31m"
# define YELLOW "\033[0;33m"
# define NOCOLOR "\033[0m"

# define LEXER_BAD_INSTR "Illegal character found in instruction"
# define LEXER_BAD_REF "Illegal or empty label reference"
# define LEXER_BAD_QUOTE "Quote string incomplete, please close end \
of quote string"
# define LEXER_UNKNOWN "Encountered an unknown token."
# define LEXER_MISSING_NUM "Missing number from direct reference"
# define REG_WARNING "Register number out of bounds, may lead to\
 Virtual Machine memory errors"

/* Parser */
# define PARSER_EXPECT_CMD "Syntax error: Expected a command, found something\
 else instead"
# define PARSER_UNKNOWN_CMD "Syntax error: Unrecognised command. Allowed\
 commands are: .name, .comment"
# define NAME_EXISTS "Syntax error: Name already given once"
# define COMMENT_EXISTS "Syntax error: Comment already given once"
# define PARSER_NO_QUOTE "Syntax error: Did not find a command string"
# define PARSER_STR_TOO_LONG "Syntax error: Command quote string too long"
# define PARSER_NO_EOL "Syntax error: Command should end with new line"
# define PARSER_EXPECT_START "Syntax error: Expected a label or instruction"
# define PARSER_EXPECT_INSTR "Syntax error: Expected an operation instruction"
# define PARSER_UNKNOWN_INSTR "Syntax error: Encountered an unknown instruction"
# define PARSER_WRONG_ARG "Syntax error: Incorrect argument type"
# define PARSER_INSUF_ARG "Syntax error: Insufficient arguments"
# define PARSER_UNKNOWN_ARG "Syntax error: Unknown argument type"
# define PARSER_EXPECT_EOL "Syntax error: Expected end of line"
# define PARSER_EXPECT_SEP "Syntax error: Expected argument separator"
# define PARSER_EXPECT_MATH_OP "Syntax error: Expected mathematical operator"
# define PARSER_EXPECT_NUM "Syntax error: Expected number"
# define PARSER_TOO_MANY_ARGS "Syntax error: Too many argument separators"
# define PARSER_UNKNOWN_ARGTYPE "Syntax error: Unidentifiable argument type"
# define PARSER_WARN_EMPTY_QUOTE "Champion has empty name or comment"
# define PARSER_EMPTY_CODE "Champion code is empty"

# define ERR_MSG_BAD_OP_IDX "ERROR: Internal error, bad op index"

# define SYMTABLE_DUP "Duplicate label declaration found, may lead to unexpected\
 outcomes"
# define SYMTABLE_OUTSTANDING "Outstanding reference found, missing a label"
# define SYMTABLE_MULT_OUT "Multiple outstanding references to labels"

typedef enum s_errors
{
	ASM_invalidcode,
	ASM_undefinedlabel,
	ASM_invalidaddress,
	ASM_unlabelled,
	ASM_hasaddress,
	ASM_noaddress,
	ASM_ecessfields,
	ASM_mismatched,
	ASM_nonalpha,
	ASM_badlabel,
	ASM_invalidchar,
	ASM_invaliduote,
	ASM_overflow
}			t_errors;

typedef struct s_errorset
{
	t_pos		pos;
	t_string	str;
}		t_errorset;

void		exit_error(void);
void		exit_error_str(char *str);
int			error_ret(char *msg);
int			error_no_str(t_errorset error, char *msg);
int			error(t_errorset error, char *msg);
t_errorset	errorset(t_pos pos, t_string str);
int			warning(t_errorset error, char *msg);
int			warning_ret(char *msg);

#endif

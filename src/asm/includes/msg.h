/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caruychen <cchen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 10:44:51 by caruychen         #+#    #+#             */
/*   Updated: 2022/09/21 20:20:39 by caruychen        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSG_H
# define MSG_H

# define MSG_USAGE "Usage: ./asm <sourcefile.s>"
# define ERR_MSG_INVALID_EXT "ERROR: Unrecognised file type"
# define ERR_MSG_EMPTY_FILE "ERROR: empty file"

/* Parser related messages */
# define ERR_MSG_PARSE_INIT_FAIL "ERROR: Failed to initialize parser"
# define ERR_MSG_BAD_CMD "ERROR: Invalid Name/Comment command"
# define ERR_MSG_STR_TOO_LONG "ERROR: Name/Comment string too long"

/* AST related messages */
# define ERR_MSG_AST_INIT_FAIL "ERROR: AST initialisation failed"

/* opmap related messages */
# define ERR_MSG_NO_OP "ERROR: Could not find operator from hashmap"
# define ERR_MSG_BAD_OP_IDX "ERROR: Internal error, bad op index"

#endif

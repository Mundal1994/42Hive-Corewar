/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caruychen <cchen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 10:44:51 by caruychen         #+#    #+#             */
/*   Updated: 2022/09/18 10:45:14 by caruychen        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSG_H
# define MSG_H

# define MSG_USAGE "Usage: ./asm <sourcefile.s>"
# define ERR_MSG_INVALID_EXT "ERROR: Unrecognised file type"
# define ERR_MSG_EMPTY_FILE "ERROR: empty file"

/* AST related messages */
# define ERR_MSG_NO_NODE "ERROR: Missing node location to initialise to"
# define ERR_MSG_NO_TOKEN "ERROR: Missing token string"
# define ERR_MSG_BAD_TYPE "ERROR: Invalid token type"
# define ERR_MSG_NO_NODE "ERROR: Node not supplied"
# define ERR_MSG_BAD_ORDER "ERROR: Incorrect token order"

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 15:45:57 by cchen             #+#    #+#             */
/*   Updated: 2022/09/15 15:49:39 by cchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define MSG_USAGE "Usage: ./corewar [-d N -v N | -a -i] \
[-n [number] champion.cor ...]\n\
	-a	: prints aff operation to standard output\n\
	-i	: prints basic information about the game to standard output\n\
	-dump N	: dumps memory after <nbr_cycles> on standard output,\
 then quits the game\n\
	-d N	: same command as dump\n\
	-dc N	: variation of -d. displays carriages position on standard output\n\
	-di N	: variation of -dc. also print information about struct info\n\
	-c N	: variation of -dc. also prints carriages on standard output\n\
	-v N	: Verbosity levels, can be added together to enable several\n\
			- 0 : Show only essentials\n\
			- 1 : Show lives\n\
			- 2 : Show cycles\n\
			- 4 : Show operations (Params are NOT litteral ...)\n\
			- 8 : Show deaths\n\
			- 16 : Show PC movements (Except for jumps)\n\
			Verbosity level flags can combined\n\
			ex\n\
				run flag 1 & 2 by using number 3\n\
				run flag 4 & 2 by using number 6 etc...\n\
	-n N	: Manually set the number of the players\
 Have to be in range of the users you are using"

#endif

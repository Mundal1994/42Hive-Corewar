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

# define MSG_USAGE "Usage: ./corewar [-dump nbr_cycles] \
[-n [number] champion.cor ...]\n\
	-d	N: dumps memory after <nbr_cycles> on standard output,\
 then quits the game\n\
 	-n	number: Manually set the number of the next player\n\
	-v	N: Verbosity levels, can be added together to enable several\n\
			- 0 : Show only essentials\n\
			- 1 : Show lives\n\
			- 2 : Show cycles\n\
			- 4 : Show operations (Params are NOT litteral ...)\n\
			- 8 : Show deaths\n\
			- 16 : Show PC movements (Except for jumps)"
# define TOO_MANY_CHAMPS "Too many champions"

#endif

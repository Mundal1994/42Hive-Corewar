/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carriage.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 08:53:57 by cchen             #+#    #+#             */
/*   Updated: 2022/09/20 08:54:02 by cchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CARRIAGE_H
# define CARRIAGE_H

# include <stdint.h>

typedef enum e_carry
{
	FL_POS = 1 << 0,
	FL_ZRO = 1 << 1,
	FL_NEG = 1 << 2
}				t_carry;

typedef struct s_carriage
{
	uint32_t	registry[REG_NUMBER];
	uint32_t	carry;
}				t_carriage;

#endif

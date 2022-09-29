/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavis <jdavis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 09:07:42 by cchen             #+#    #+#             */
/*   Updated: 2022/09/28 17:39:58 by jdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "libft.h"
# include "op.h"
# include "opcodes.h"
# include "error.h"
# include <fcntl.h>

# define TRUE	1
# define FALSE	0
# define ERROR	-1

typedef struct s_profile
{
	int			i;
	char		name[PROG_NAME_LENGTH + 1];
	char		comment[COMMENT_LENGTH + 1];
	int			exec_cd_sz;
	int			pos;
	struct s_profile	*next;
	struct s_profile	*head;
}			t_profile;

typedef struct s_input
{
	u_int8_t	*t_script;
	size_t		capacity;
	size_t		current;
}				t_input;

typedef struct s_carriage
{
	int32_t				id;//unique carriage number
	int32_t				carry;//can be 1 or 0 - has the value of false upon initialization
	int32_t				statement_code;//prior to battle this value is not set
	int32_t				last_live_call;//initialized to 0? cycle in which the statement live performed last
	int32_t				delay;//initialized to 0
	int32_t				pos;//current carriage position
	uint8_t				*home;
	uint8_t				*current;
	int32_t				skip;//nbr of bytes that needs to be skipped to go to next statement
	int32_t				registry[REG_NUMBER];//not acccurate numbers//first r1 will be identification number of player on whose code the carraige stands
	struct s_carriage	*next;
}						t_carriage;

typedef struct s_info
{
	int			winner;//initialized to player with highest identification number
	int			total_cycles;//initialized to 0
	int			live_statement;//initialized to 0
	int			cycles_to_die;// initialized with macro CYCLES_TO_DIE
	int			cycle_count;
	int			checks_count;// initialized to 0
	int			carriage_count;
	t_carriage	*head_carriage;
	int		delay[5][16];
}				t_info;

int		init(int argc, char **argv, int i);
t_input	**read_init(int argc, char **argv, int i, t_profile **champ);
int		game_start(uint8_t core[MEM_SIZE], t_info *info, t_profile *champ);
int		update_carriages(uint8_t core[MEM_SIZE], t_info *info);

//print functions
void	print_core(uint8_t core[MEM_SIZE]);
void	introduce_contestants(t_profile *champ);
void	announce_winner(t_profile *champ, int winner);
void	print_carriages(t_info *info);

#endif

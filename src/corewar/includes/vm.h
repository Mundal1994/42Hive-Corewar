/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavis <jdavis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 09:07:42 by cchen             #+#    #+#             */
/*   Updated: 2022/10/03 16:45:49 by jdavis           ###   ########.fr       */
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
# define STATE	16
# define ARGS	3
# define RESET   "\033[0m"
# define GREEN   "\033[32m"

typedef enum e_flag
{
	A_FLAG,
	D_FLAG,
	S_FLAG,
	V_FLAG,
	I_FLAG,
}	t_flag;

typedef enum e_arg
{
	NON,//0
	R,//1
	D,//2
	I,//3
	RD,//4
	RI,//5
	DI,//6
	RDI,//7
}			t_arg;

typedef enum e_ops
{
	ARG1,
	ARG2,
	ARG3,
	DELAY,
	SIZE = 4,//DON'T CHANGE THIS POS WE NEED IT TO BE FOUR
	PCB,
}			t_ops;

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
	int32_t				tmp_pos;
	uint8_t				*home;
	uint8_t				*current;
	int32_t				skip;//nbr of bytes that needs to be skipped to go to next statement
	int64_t				registry[REG_NUMBER];//not acccurate numbers//first r1 will be identification number of player on whose code the carraige stands
	int32_t				arg_types[ARGS];
	int64_t				args_found[ARGS];
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
	int			flag[5];
	t_carriage	*head_carriage;
	int			operations[6][STATE];
}				t_info;

typedef void	op_table(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info);

int		init(int argc, char **argv, int i, t_info *info);
t_input	**read_init(int argc, char **argv, int i, t_profile **champ);
int		game_start(uint8_t core[MEM_SIZE], t_info *info, t_profile *champ);
int		update_carriages(uint8_t core[MEM_SIZE], t_info *info, op_table *op_table[STATE]);
void	check(uint8_t core[MEM_SIZE], t_info *info);

//print functions
void	print_core(uint8_t core[MEM_SIZE], t_info *info);
void	introduce_contestants(t_profile *champ);
void	announce_winner(t_profile *champ, int winner);
void	print_carriages(t_info *info);
void	print_info(t_info *info);

//statement functions
int		read_bytes(u_int32_t third, int	pos, uint8_t core[MEM_SIZE], int size);
void	put_nbr(uint8_t core[MEM_SIZE], int pos, uint32_t nbr);
void	limit_jump(t_carriage **carriage, int *pos);
//void	check_arg_type(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info, int64_t *arg);
void	check_first_arg_type(uint8_t core[MEM_SIZE], t_carriage **carriage, int64_t *arg);
void	check_second_arg_type(uint8_t core[MEM_SIZE], t_carriage **carriage, int64_t *arg);
void	check_third_arg_type(uint8_t core[MEM_SIZE], t_carriage **carriage, int64_t *arg);
void	update_carry(int nbr, t_carriage **carriage);
void	zjmp(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info);
void	live(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info);
void	ld(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info);
void	st(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info);
void	add(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info);
void	sub(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info);
void	and(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info);
void	or(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info);
void	xor(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info);
void	ldi(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info);
void	sti(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info);
void	fork_op(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info);
void	lld(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info);
void	lldi(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info);
void	lfork(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info);
void	aff(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info);

#endif

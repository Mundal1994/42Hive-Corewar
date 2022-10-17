/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavis <jdavis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 09:07:42 by cchen             #+#    #+#             */
/*   Updated: 2022/10/12 12:34:53 by jdavis           ###   ########.fr       */
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
	NO_FLAG,
	A_FLAG,
	I_FLAG,
	O_FLAG,
	V_FLAG,
	D_FLAG,
	DC_FLAG,
	DI_FLAG,
	C_FLAG,
	FLAG_COUNT,
}	t_flag;

typedef enum e_arg
{
	NON,
	R,
	D,
	I,
	RD,
	RI,
	DI,
	RDI,
}			t_arg;

typedef enum e_ops
{
	ARG1,
	ARG2,
	ARG3,
	DELAY,
	SIZE = 4,
	PCB,
	OPS_COUNT
}			t_ops;

typedef struct s_profile
{
	int					i;
	char				name[PROG_NAME_LENGTH + 1];
	char				comment[COMMENT_LENGTH + 1];
	int					exec_cd_sz;
	int					pos;
	struct s_profile	*next;
	struct s_profile	*head;
}			t_profile;

typedef struct s_input
{
	u_int8_t	*t_script;
	char		*filename;
	int			champ_count;
	size_t		capacity;
	size_t		current;
}				t_input;

typedef struct s_carriage
{
	int32_t				id;
	int32_t				carry;
	int32_t				statement_code;
	int32_t				last_live_call;
	int32_t				delay;
	int32_t				pos;
	int32_t				tmp_pos;
	int32_t				registry[REG_NUMBER];
	int32_t				arg_types[ARGS];
	int64_t				args_found[ARGS];
	struct s_carriage	*next;
}						t_carriage;

typedef struct s_info
{
	int			winner;
	int			total_cycles;
	int			live_statement;
	int			cycles_to_die;
	int			cycle_count;
	int			checks_count;
	int			carriage_count;
	int			flag[FLAG_COUNT];
	t_carriage	*head_carriage;
	char		*champ_names[4];
	int			champ_total;
}				t_info;

int		init_flags(int argc, char **argv, t_info *info);
int		init(int argc, char **argv, int i, t_info *info);
void	set_arg(t_carriage **carriage);
t_input	**read_init(int argc, char **argv, int i, t_profile **champ);
int		game_start(uint8_t core[MEM_SIZE], t_info *info, t_profile *champ);
int		update_carriages(uint8_t core[MEM_SIZE], t_info *info);
void	check(t_info *info);
void	set_statement_code(uint8_t core[MEM_SIZE], t_carriage **carriage);
void	perform_statement_code(uint8_t core[MEM_SIZE], t_carriage **carriage, \
t_info *info);

//move fucntions
void	make_move_tmp(t_carriage **carriage, int move);
void	move_carriage(t_carriage **carriage, int *total);
void	make_move(t_carriage **carriage, int move, int *total);

//print functions
void	print_core(uint8_t core[MEM_SIZE], t_info *info);
void	introduce_contestants(t_profile *champ);
void	announce_winner(t_profile *champ, int winner);
void	print_carriages(t_info *info);
void	print_info(t_info *info);

//statement functions
int		read_bytes(u_int32_t third, int pos, uint8_t core[MEM_SIZE], int size);
void	put_nbr(uint8_t core[MEM_SIZE], int pos, uint32_t nbr);
void	limit_jump(int *pos);
void	update_arg_values(uint8_t core[MEM_SIZE], t_carriage **carriage, \
int64_t *arg, int count);
void	check_second_arg_type(uint8_t core[MEM_SIZE], t_carriage **carriage, \
int64_t *arg);
void	check_third_arg_type(uint8_t core[MEM_SIZE], t_carriage **carriage, \
int64_t *arg);
void	update_carry(int nbr, t_carriage **carriage);
void	op_zjmp(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info);
void	op_live(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info);
void	op_ld(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info);
void	op_st(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info);
void	op_add(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info);
void	op_sub(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info);
void	op_and(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info);
void	op_or(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info);
void	op_xor(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info);
void	op_ldi(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info);
void	op_sti(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info);
void	op_fork(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info);
void	op_lld(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info);
void	op_lldi(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info);
void	op_lfork(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info);
void	op_aff(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info);

//print4 flag
void	v_flag4_one_arg(t_carriage **carriage, char *command);
void	v_flag4_two_arg(t_carriage **carriage, char *command, int reg);
void	v_flag4_three_arg(t_carriage **carriage, char *command, int reg);

//reading bytes/args
int64_t	read_args(u_int32_t first, t_carriage **carriage, u_int8_t core[MEM_SIZE]);
int		read_bytes(u_int32_t third, int pos, uint8_t core[MEM_SIZE], int size);

//error
int		error_clean(t_input **input, t_profile **champ, int c);
int		v_flag5(t_carriage **carriage);
void	print_flag16(uint8_t core[MEM_SIZE], t_carriage **carriage, int total, \
int prev);
int		print_command(t_info *info);
void	print_cycle_count(t_info *info, int die);
int		print_dump_flags(uint8_t core[MEM_SIZE], t_info *info);
int		free_carriage(t_info *info);

typedef void			(*t_op_table)(uint8_t core[MEM_SIZE], \
t_carriage **carriage, t_info *info);

static const t_op_table	g_op_table[STATE] = {
	op_live,
	op_ld,
	op_st,
	op_add,
	op_sub,
	op_and,
	op_or,
	op_xor,
	op_zjmp,
	op_ldi,
	op_sti,
	op_fork,
	op_lld,
	op_lldi,
	op_lfork,
	op_aff,
};

static const int		g_operations[OPS_COUNT][STATE] = {
{2, 6, 1, 1, 1, 7, 7, 7, 2, 7, 1, 2, 6, 7, 2, 1},
{0, 1, 5, 1, 1, 7, 7, 7, 0, 4, 7, 0, 1, 4, 0, 0},
{0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 4, 0, 0, 1, 0, 0},
{10, 5, 5, 10, 10, 6, 6, 6, 20, 25, 25, 800, 10, 50, 1000, 2},
{4, 4, 4, 4, 4, 4, 4, 4, 2, 2, 2, 2, 4, 2, 2, 4},
{0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1},
};

#endif

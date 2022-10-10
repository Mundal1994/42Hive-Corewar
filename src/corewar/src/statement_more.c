
#include "vm.h"

void	limit_jump(int *pos)
{
	if (*pos >= MEM_SIZE)
		*pos %= MEM_SIZE;
	else if (*pos < 0)
		*pos = MEM_SIZE - (*pos * -1);
}

void	v_flag4_three_arg(t_carriage **carriage, char *command, int reg)
{
	int	i;

	i = 0;
	ft_printf("P %4d | %s ", (*carriage)->id, command);
	while (i < ARGS)
	{
		if (i != 0)
			ft_putchar(' ');
		if (i == reg)
			ft_printf("r%d", (*carriage)->args_found[i]);
		else
			ft_printf("%d", (int16_t)(*carriage)->args_found[i]);
		++i;
	}
	ft_putchar('\n');
}

void	ldi(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	int		value;
	int		pos;
	int16_t sum;

	update_arg_values(core, carriage, &(*carriage)->args_found[ARG1], ARG1);
	update_arg_values(core, carriage, &(*carriage)->args_found[ARG2], ARG2);
	if (info->flag[V_FLAG] == 4 && info)
		v_flag4_three_arg(carriage, "ldi", ARG3);
	sum = (int16_t)(*carriage)->args_found[ARG1] + (int16_t)(*carriage)->args_found[ARG2];
	if (sum < 0)
		pos = (*carriage)->pos - (sum * -1) % IDX_MOD;
	else
		pos = (*carriage)->pos + sum % IDX_MOD;
	limit_jump(&pos);
	value = read_bytes(0, pos, core, SIZE);
	(*carriage)->registry[(*carriage)->args_found[ARG3] - 1] = value;
	if (info->flag[V_FLAG] == 4)
		ft_printf("       | -> load from %d + %d = %d (with pc and mod %d)\n", (int16_t)(*carriage)->args_found[ARG1], (int16_t)(*carriage)->args_found[ARG2], sum, pos);
}

void	lldi(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	int		value;
	int		pos;
	int16_t	sum;

	update_arg_values(core, carriage, &(*carriage)->args_found[ARG1], ARG1);
	update_arg_values(core, carriage, &(*carriage)->args_found[ARG2], ARG2);
	if (info->flag[V_FLAG] == 4 && info)
		v_flag4_three_arg(carriage, "lldi", ARG3);
	sum = (int16_t)(*carriage)->args_found[ARG1] + (int16_t)(*carriage)->args_found[ARG2];
	if (sum < 0)
		pos = (*carriage)->pos - (sum * -1);
	else
		pos = (*carriage)->pos + sum;
	value = read_bytes(0, pos, core, SIZE);
	(*carriage)->registry[(*carriage)->args_found[ARG3] - 1] = value;
	if (info->flag[V_FLAG] == 4)
		ft_printf("       | -> load from %d + %d = %d (with pc and mod %d)\n", (int16_t)(*carriage)->args_found[ARG1], (int16_t)(*carriage)->args_found[ARG2], sum, pos);
}


/*


Difference at -d 8198
8198

carriage seems to be off here: ./corewar -di 8012 champs/examples/helltrain.cor champs/examples/jinx.cor




---------

./corewar -d 7215 champs/examples/helltrain.cor champs/championships/2014/rabid-on/jinx.cor champs/examples/turtle.cor

./corewar -di 7214 champs/examples/helltrain.cor champs/examples/jinx.cor champs/examples/turtle.cor
./corewar -di 7215 champs/examples/helltrain.cor champs/examples/jinx.cor champs/examples/turtle.cor

at this point i thought 17 03 70 03 was the issure of having it be printed too much

turns out this is a bigger issue: 0f 03 70 03

./corewar -d 5499 champs/examples/helltrain.cor champs/championships/2014/rabid-on/jinx.cor champs/examples/turtle.cor

./corewar -di 5499 champs/examples/helltrain.cor champs/examples/jinx.cor champs/examples/turtle.cor
./corewar -di 5498 champs/examples/helltrain.cor champs/examples/jinx.cor champs/examples/turtle.cor

0f 03 70 03 was supposed to be deleted and replaced with 00 00 00 04 at pos 1431

CARRIAGE NBR: 14
pos: 1431


BEFORE CODE EXECUTION

CARRIAGE ID 14
carry: 1	statement_code: 1	last_live_call: 5484
delay: 7	pos: 1422	skip: 0
REGISTRY
reg0 : -1	reg1 : 251883523	reg2 : 386101251	reg3 : 0
reg4 : 0	reg5 : 0	reg6 : 0	reg7 : 0
reg8 : 0	reg9 : 0	reg10 : 0	reg11 : 0
reg12 : 0	reg13 : 0	reg14 : 0	reg15 : 0

AFTER CODE EXECUTION

CARRIAGE ID 14
carry: 1	statement_code: 1	last_live_call: 5484
delay: 6	pos: 1422	skip: 0
REGISTRY
reg0 : -1	reg1 : 251883523	reg2 : 386101251	reg3 : 0
reg4 : 0	reg5 : 0	reg6 : 0	reg7 : 0
reg8 : 0	reg9 : 0	reg10 : 0	reg11 : 0
reg12 : 0	reg13 : 0	reg14 : 0	reg15 : 0




this one ?

CARRIAGE ID 16
carry: 1	statement_code: 0	last_live_call: 5499
delay: 0	pos: 1529	skip: 0
REGISTRY
reg0 : -2	reg1 : 0	reg2 : 0	reg3 : 4
reg4 : 48	reg5 : 52	reg6 : 0	reg7 : 0
reg8 : 0	reg9 : 0	reg10 : 0	reg11 : 0
reg12 : 0	reg13 : 0	reg14 : 0	reg15 : 0


CARRIAGE ID 37
carry: 1	statement_code: 0	last_live_call: 5499
delay: 0	pos: 1524	skip: 0
REGISTRY
reg0 : -2	reg1 : 0	reg2 : 0	reg3 : 4
reg4 : 48	reg5 : 52	reg6 : 0	reg7 : 0
reg8 : 0	reg9 : 0	reg10 : 0	reg11 : 0
reg12 : 0	reg13 : 0	reg14 : 0	reg15 : 0


CARRIAGE ID 41
carry: 1	statement_code: 0	last_live_call: 5499
delay: 0	pos: 1544	skip: 0
REGISTRY
reg0 : -2	reg1 : 0	reg2 : 0	reg3 : 4
reg4 : 48	reg5 : 52	reg6 : 0	reg7 : 0
reg8 : 0	reg9 : 0	reg10 : 0	reg11 : 0
reg12 : 0	reg13 : 0	reg14 : 0	reg15 : 0

---------

THIS MIGHT NOT BE THE CORRECT ERROR BUT THE ONE ABOVE
IN THIS CASE IT DOESN"T WORK WITH THE ABOVE CALCULATION

because dif is positive and carriage pos is smaller than position calculated
./corewar -di 8170 champs/examples/helltrain.cor champs/examples/jinx.cor champs/examples/turtle.cor
./corewar -c 8169 champs/examples/helltrain.cor champs/examples/jinx.cor champs/examples/turtle.cor

execution code: 03 70 03 ff ff

ORIG VERSION:
2182 + 65535 % 512 == 2693!!!!! (i think this was the position of the number that needed to be put...)


2182 + 65535 % 4096 == 6277
6277 - 2182 == 4095
4095 % 512 = 511
2182 + 511 = 2693



CURRENT CALC VERSION:
2182 + 65535 % 4096 == 6277
pos - car->pos > 512 but pos > car->pos
	skip
pos - car->pos > -512 but pos > car->pos
	skip
pos - car->pos != -512 and != 512
	skip
pos > MEM_SIZE
	6277 % 4096 == 2181



tried to see if we could add something
2182 + 65535 % 4096 == 6277
6277 % 4096 == 2181
6277 - 2182 == 4095
4095 % 512 == 511
511 + 2181 == 2692.... one off... di



CARRIAGE ID 59
carry: 1	statement_code: 3	last_live_call: 8159
delay: 1	pos: 2182	skip: 0
REGISTRY
reg0 : -1	reg1 : 57672192	reg2 : 318992387	reg3 : 0
reg4 : 0	reg5 : 0	reg6 : 0	reg7 : 0
reg8 : 0	reg9 : 0	reg10 : 0	reg11 : 0
reg12 : 0	reg13 : 0	reg14 : 0	reg15 : 0

--------

where we couldn't get the %IDX_MOD to work
before dif:
./corewar -d 1129 champs/examples/bigzork.cor champs/examples/helltrain.cor
dif:
./corewar -d 1130 champs/examples/bigzork.cor champs/examples/helltrain.cor

the carriage is reading this code: 03 70 02 ff e8
need to find position 2161 - 24 = 2137!!!!!
ffe8 = 65512

ORIG VERSION
65512 % 512 = 488
2161 + 488 % 512 = 2649

2161 + 65512 % 512 = 2649




2161 + 65512 % 4096 == 6233
6233 - 2161 == 4072
4072 % 512 = 488
2182 + 488 = 2670



CURRENT CALC VERSION:
2161 + 65512 % 4096 == 6233
pos - car->pos > 512 but pos > car->pos
	skip
pos - car->pos > -512 but pos > car->pos
	skip
pos - car->pos != -512 and != 512
	skip
pos > MEM_SIZE
	6233 % 4096 == 2137



CARRIAGE ID 2
carry: 1	statement_code: 3	last_live_call: 1124
delay: 1	pos: 2161	skip: 0
REGISTRY
reg0 : -2	reg1 : 0	reg2 : 0	reg3 : 0
reg4 : 0	reg5 : 0	reg6 : 0	reg7 : 0
reg8 : 0	reg9 : 0	reg10 : 0	reg11 : 0
reg12 : 0	reg13 : 0	reg14 : 0	reg15 : 0




*/
void	sti(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	int		pos;
	int16_t	sum;

	update_arg_values(core, carriage, &(*carriage)->args_found[ARG2], ARG2);
	update_arg_values(core, carriage, &(*carriage)->args_found[ARG3], ARG3);
	if (info->flag[V_FLAG] == 4)
		v_flag4_three_arg(carriage, "sti", ARG1);
	sum = (int16_t)(*carriage)->args_found[ARG2] + (int16_t)(*carriage)->args_found[ARG3];
	if (sum < 0)
		pos = (*carriage)->pos - (sum * -1) % IDX_MOD;
	else
		pos = (*carriage)->pos + sum % IDX_MOD;
	limit_jump(&pos);
	if (info->flag[V_FLAG] == 4)
		ft_printf("       | -> store to %d + %d = %d (with pc and mod %d)\n", (int16_t)(*carriage)->args_found[ARG2], (int16_t)(*carriage)->args_found[ARG3], sum, pos);
	put_nbr(core, pos, (uint32_t)(*carriage)->registry[(*carriage)->args_found[ARG1] - 1]);
	if (!info)
		ft_printf("no\n");
}

static int	copy_carriage(t_info **info, t_carriage *carriage, int new_pos)
{
	t_carriage	*new;
	int			i;

	new = (t_carriage *)malloc(sizeof(t_carriage));
	if (!new)
		return (ERROR);
	(*info)->carriage_count++;
	new->id = (*info)->carriage_count;
	new->carry = carriage->carry;
	new->statement_code = OP_NULL;
	new->last_live_call = carriage->last_live_call;
	new->delay = carriage->delay;
	new->pos =new_pos;
	new->home = carriage->home;//this should probably be different
	new->current = carriage->current;//this should probably be different
	new->skip = carriage->skip;//this should probably be different
	i = -1;
	while (++i < REG_NUMBER)
		new->registry[i] = carriage->registry[i];
	i = 0;
	while (i < 3)
	{
		new->arg_types[i] = 0;
		new->args_found[i++] = 0;
	}
	new->next = (*info)->head_carriage;
	(*info)->head_carriage = new;
	return (0);
}

void	fork_op(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	int		pos;
	int16_t	sum;

	if (info->flag[V_FLAG] == 4 && core)
		v_flag4_one_arg(carriage, "fork");
	sum = (int16_t)(*carriage)->args_found[ARG1];
	if (sum < 0)
		pos = (*carriage)->pos - (sum * -1) % IDX_MOD;
	else
		pos = (*carriage)->pos + sum % IDX_MOD;
	limit_jump(&pos);
	copy_carriage(&info, *carriage, pos);
	if (info->flag[V_FLAG] == 4)
		ft_printf("(%d)\n", pos);
}

void	lfork(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	int	pos;

	if (info->flag[V_FLAG] == 4 && core)
		v_flag4_one_arg(carriage, "lfork");
	pos = (*carriage)->pos + (int16_t)(*carriage)->args_found[ARG1];
	limit_jump(&pos);
	copy_carriage(&info, *carriage, pos);
	if (info->flag[V_FLAG] == 4)
		ft_printf("(%d)\n", pos);
}

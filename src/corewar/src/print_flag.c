
#include "vm.h"

int	v_flag5(t_carriage **carriage)
{
	if ((*carriage)->statement_code == OP_LIVE)
		ft_printf("LIVE (%d)\n", (*carriage)->statement_code);
	else if ((*carriage)->statement_code == OP_LD)
		ft_printf("LD (%d)\n", (*carriage)->statement_code);
	else if ((*carriage)->statement_code == OP_ST)
		ft_printf("ST (%d)\n", (*carriage)->statement_code);
	else if ((*carriage)->statement_code == OP_ADD)
		ft_printf("add (%d)\n", (*carriage)->statement_code);
	else if ((*carriage)->statement_code == OP_SUB)
		ft_printf("sub (%d)\n", (*carriage)->statement_code);
	else if ((*carriage)->statement_code == OP_AND)
		ft_printf("AND (%d)\n", (*carriage)->statement_code);
	else if ((*carriage)->statement_code == OP_OR)
		ft_printf("OR (%d)\n", (*carriage)->statement_code);
	else if ((*carriage)->statement_code == OP_XOR)
		ft_printf("XOR (%d)\n", (*carriage)->statement_code);
	else if ((*carriage)->statement_code == OP_ZJMP)
		ft_printf("ZJMP (%d)\n", (*carriage)->statement_code);
	else if ((*carriage)->statement_code == OP_LDI)
		ft_printf("LDI (%d)\n", (*carriage)->statement_code);
	else if ((*carriage)->statement_code == OP_STI)
		ft_printf("STI (%d)\n", (*carriage)->statement_code);
	else if ((*carriage)->statement_code == OP_FORK)
		ft_printf("FORK (%d)\n", (*carriage)->statement_code);
	else if ((*carriage)->statement_code == OP_LLD)
		ft_printf("LLD (%d)\n", (*carriage)->statement_code);
	else if ((*carriage)->statement_code == OP_LLDI)
		ft_printf("LLDI (%d)\n", (*carriage)->statement_code);
	else if ((*carriage)->statement_code == OP_LFORK)
		ft_printf("LFORK (%d)\n", (*carriage)->statement_code);
	else if ((*carriage)->statement_code == OP_AFF)
		ft_printf("AFF (%d)\n", (*carriage)->statement_code);
	return (TRUE);
}

void	v_flag4_one_arg(t_carriage **carriage, char *command)
{
	ft_printf("P %4d | %s ", (*carriage)->id, command);
	if ((*carriage)->statement_code == OP_FORK || (*carriage)->statement_code == OP_LFORK)
		ft_printf("%d ", (int16_t)(*carriage)->args_found[ARG1]);
	else if ((*carriage)->statement_code == OP_ZJMP)
	{
		ft_printf("%d ", (int16_t)(*carriage)->args_found[ARG1]);
		if ((*carriage)->carry)
			ft_printf("OK\n");
		else
			ft_printf("FAILED\n");
	}
	else if ((*carriage)->statement_code == OP_LIVE)
		ft_printf("%d\n", (*carriage)->args_found[ARG1]);
}

void	v_flag4_two_arg(t_carriage **carriage, char *command, int reg)
{
	int	i;

	i = 0;
	ft_printf("P %4d | %s ", (*carriage)->id, command);
	while (i < ARG3)
	{
		if (i != 0)
			ft_putchar(' ');
		// if (reg == -1)
		// {
		// 	if ((*carriage)->arg_types[i] == R)
		// 		ft_printf("r%d", (*carriage)->args_found[i]);
		// 	else if ((*carriage)->arg_types[i] == D || (*carriage)->arg_types[i] == I)
		// 		ft_printf("%d", (int16_t)(*carriage)->args_found[i]);
		// }
		// else
		// {
			if (i == reg)
				ft_printf("r%d", (*carriage)->args_found[i]);
			else if (((*carriage)->arg_types[i] == D || (*carriage)->arg_types[i] == I) && \
				(*carriage)->statement_code == OP_LD)
				ft_printf("%d", (*carriage)->args_found[i]);
			// else if (((*carriage)->arg_types[i] == D || (*carriage)->arg_types[i] == I) && \
			// 	(*carriage)->statement_code == OP_LLD)
			// 	ft_printf("%d", (*carriage)->args_found[i]);NEED TO COME BACK TO THIS
			else if ((*carriage)->arg_types[i] == D || (*carriage)->arg_types[i] == I)
				ft_printf("%d", (int16_t)(*carriage)->args_found[i]);
		//}
		++i;
	}
	ft_putchar('\n');
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
		if (reg == -1)
		{
			ft_printf("r%d", (*carriage)->args_found[i]);
		}
		else
		{
			if (i == reg)
				ft_printf("r%d", (*carriage)->args_found[i]);
			else if ((*carriage)->statement_code == OP_STI || (*carriage)->statement_code == OP_LDI)
				ft_printf("%d", (int16_t)(*carriage)->args_found[i]);
			else
				ft_printf("%d", (*carriage)->args_found[i]);
		}
		++i;
	}
	ft_putchar('\n');
}

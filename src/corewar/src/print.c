/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 11:56:28 by molesen           #+#    #+#             */
/*   Updated: 2022/10/14 11:56:31 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	print_ops_info(int j)
{
	if (j == ARG1)
		ft_printf("ARG1	: ");
	else if (j == ARG2)
		ft_printf("ARG2	: ");
	else if (j == ARG3)
		ft_printf("ARG3	: ");
	else if (j == DELAY)
		ft_printf("DELAY	: ");
	else if (j == SIZE)
		ft_printf("SIZE	: ");
	else if (j == PCB)
		ft_printf("PCB	: ");
}

void	print_info(t_info *info)
{
	int	i;
	int	j;

	ft_printf("\nPRINT INFO\n");
	ft_printf("winner: %d	total_cycles: %d	live_statement: %d\n", info->winner, info->total_cycles, info->live_statement);
	ft_printf("cycles_to_die: %d	cycle_count: %d	checks_count: %d\n", info->cycles_to_die, info->cycle_count, info->checks_count);
	ft_printf("carriage_count: %d\nOPERATIONS\n", info->carriage_count);
	j = 0;
	while (j < 6)
	{
		i = 0;
		print_ops_info(j);
		while (i < STATE)
		{
			ft_printf("%d	", info->operations[j][i]);
			++i;
		}
		ft_printf("\n");
		++j;
	}
	ft_putchar('\n');
}

void	print_carriages(t_info *info)
{
	t_carriage	*carriage;
	int			i;

	carriage = info->head_carriage;
	while (carriage)
	{
		ft_printf("\nCARRIAGE ID %d\ncarry: %d	statement_code: %d	last_live_call: %d\ndelay: %d	pos: %d	skip: %d\n", carriage->id, carriage->carry, carriage->statement_code, carriage->last_live_call, carriage->delay, carriage->pos, carriage->skip);
		i = 0;
		ft_printf("REGISTRY\n");
		while (i < REG_NUMBER)
		{
			ft_printf("reg%d : %d	", i, carriage->registry[i]);
			++i;
			if (i % 4 == 0)
				ft_printf("\n");
		}
		carriage = carriage->next;
	}
}

void	introduce_contestants(t_profile *champ)
{
	ft_printf("Introducing contestants...\n");
	while (champ)
	{
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n", champ->i, champ->exec_cd_sz, champ->name, champ->comment);
		champ = champ->next;
	}
}

void	announce_winner(t_profile *champ, int winner)
{
	while (champ)
	{
		if (winner == champ->i)
		{
			ft_printf("Contestant %d, \"%s\", has won !\n", winner, champ->name);
			break ;
		}
		champ = champ->next;
	}
}

#include "vm.h"

void	print_core(uint32_t core[MEM_SIZE])
{
	int	i;
	int	line;

	i = 0;
	line = 0;
	ft_printf("0x0000 : ");
	while (i < MEM_SIZE)
	{
		if (core[i] < 16)
			ft_printf("0%x", core[i]);
		else
			ft_printf("%x", core[i]);
		++line;
		++i;
		if (line >= 64)
		{
			ft_printf("\n");
			line = 0;
			if (i >= MEM_SIZE)
				break ;
			ft_printf("%#0.4x : ", i);
		}
		else
			ft_printf(" ");
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

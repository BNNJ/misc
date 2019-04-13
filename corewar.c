#include "test.h"
#include <stdint.h>

# define MEM_SIZE				(4*1024)
# define CHAMP_MAX_SIZE			(MEM_SIZE / 6)
# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3

# define OPT_A 0
# define OPT_B 1
# define OPT_C 2
# define OPT_D 4
# define OPT_E 8

typedef struct	s_champ
{
	int				magic;
	char			name[PROG_NAME_LENGTH + 8];
	char			comment[COMMENT_LENGTH + 4];
	char			code[CHAMP_MAX_SIZE];
	struct s_champ	*next;
}				t_champ;

typedef struct	s_vm
{
	int				opt;
	int				nb_player;
	t_champ			*champs;
}				t_vm;


int		ft_swap_int16(int nb)
{
	return ((nb & 0xff00) >> 8 | (nb & 0x00ff) << 8);
}

int		ft_swap_int32(int nb)
{
	return ((nb & 0xff000000) >> 24
		| (nb & 0x00ff0000) >> 8
		| (nb & 0x0000ff00) << 8
		| (nb & 0x000000ff) << 24);
}

static int	get_long_opt(char *arg, t_vm *vm)
{
	int		i;
	char	*opt_table[] = {"axx", "bxxx", "cxxx", "dxxx", "exxx", NULL};

	i = 0;
	while (opt_table[i] && ft_strcmp(opt_table[i], arg))
		++i;
	if (opt_table[i])
		vm->opt |= 1 << i;
	else
	{
		ft_dprintf(2, "corewar: invalid option: %s\n", arg);
		return (0);
	}
	return (1);
}

static int	get_opt(char *arg, t_vm *vm)
{
	int	opt;

	if (*arg == '-')
		return (get_long_opt(arg + 1, vm));
	while (*arg)
	{
		if ((opt = ft_findchar("abcde", *arg)) >= 0)
			vm->opt |= 1 << opt;
		else
		{
			ft_dprintf(2, "corewar: invalid option: %c\n", *arg);
			return (0);
		}
	}
	return (1);
}

static int	get_champ(char *arg, t_vm *vm)
{
	int		fd;
	t_champ	*champ;

	if ((fd = open(arg, O_RDONLY)) <= 0)
	{
		ft_dprintf(2, "corewar: can't open file: %s\n", arg);
		return (0);
	}
	if (!(champ = malloc(sizeof(t_champ))))
		return (0);
	if (read(fd, &champ->magic, sizeof(t_champ) - sizeof(void*)) <= 0)
	{
		ft_dprintf(2, "corewar: error reading file %s\n", arg);
		return (0);
	}
	if ((champ->magic = ft_swap_int32(champ->magic)) != COREWAR_EXEC_MAGIC)
	{
		ft_dprintf(2, "corewar: invalid magic number\n");
		return (0);
	}
	close(fd);
	champ->next = vm->champs;
	vm->champs = champ;
	++vm->nb_player;
	return (1);
}

int			parse_args(int argc, char **argv, t_vm *vm)
{
	int		i;

	i = 0;
	while (++i < argc)
	{
		if (argv[i][0] == '-')
		{
			if (!get_opt(argv[i] + 1, vm))
				return (0);
		}
		else
		{
			if (!get_champ(argv[i], vm))
				return (0);
		}
	}
	return (1);
}

int			main(int argc, char **argv)
{
	t_vm	vm;

	vm = (t_vm){0, 0, NULL};
	if (argc >= 2)
	{
		parse_args(argc, argv, &vm);
	}
//	write(1, vm.champs->name, PROG_NAME_LENGTH + 10);
	ft_printf("%x\n", vm.champs->magic);
	ft_printf("%s\n", vm.champs->name);
	ft_printf("%s\n", vm.champs->comment);
	ft_printf("%s\n", vm.champs->code);
	return (EXIT_SUCCESS);
}

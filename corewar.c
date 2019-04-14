#include "test.h"
#include <stdint.h>

# define MEM_SIZE				(4 * 1024)
# define CHAMP_MAX_SIZE			(MEM_SIZE / 6)
# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3

# define MAX_PLAYERS			4

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
	int				nb;
	struct s_champ	*next;
}				t_champ;

typedef struct	s_vm
{
	int				opt;
	uint8_t			mem[MEM_SIZE];
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

/* ####################### PARSE ARG #####################  */

static int	get_long_opt(char *arg, t_vm *vm)
{
	int		i;
	char	*opt_table[] = {"viewer", "debug", "help", NULL};

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
		if ((opt = ft_findchar("vgh", *arg)) >= 0)
			vm->opt |= 1 << opt;
		else
		{
			ft_dprintf(2, "corewar: invalid option: %c\n", *arg);
			return (0);
		}
	}
	return (1);
}

static t_champ	*new_champ(char *arg, int fd)
{
	t_champ	*champ;

	if (!(champ = ft_memalloc(sizeof(t_champ))))
	{
		ft_dprintf(2, "malloc error\n");
		return (NULL);
	}
	if (read(fd, &champ->magic,
		sizeof(t_champ) - sizeof(void*) - sizeof(int)) <= 0)
	{
		ft_dprintf(2, "corewar: error reading file %s\n", arg);
		return (NULL);
	}
	if ((champ->magic = ft_swap_int32(champ->magic)) != COREWAR_EXEC_MAGIC)
	{
		ft_dprintf(2, "corewar: invalid magic number for %s\n", arg);
		return (NULL);
	}
	return (champ);
}

static int	get_champ(char *arg, t_vm *vm, int player_number)
{
	int		fd;
	t_champ	*champ;

	if ((fd = open(arg, O_RDONLY)) <= 0)
	{
		ft_dprintf(2, "corewar: can't open file: %s\n", arg);
		return (0);
	}
	if ((champ = new_champ(arg, fd)) != NULL)
	{
		champ->nb = player_number;
		champ->next = vm->champs;
		vm->champs = champ;
		++vm->nb_player;
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

int			parse_args(int argc, char **argv, t_vm *vm)
{
	int		i;
	int		player_number;

	i = 0;
	player_number = -1;
	while (++i < argc)
	{
		if (argv[i][0] == '-')
		{
			if (!get_opt(argv[i] + 1, vm))
				return (0);
		}
		else
		{
			if (!get_champ(argv[i], vm, player_number))
				return (0);
			--player_number;
		}
	}
	return (1);
}

/* ########################## INIT #######################  */

int			load_champ(t_vm *vm, t_champ *ch)
{
	int	i;
	int	j;

	i = (MEM_SIZE / vm->nb_player) * (ch->nb + vm->nb_player);
	j = 0;
	while (j < CHAMP_MAX_SIZE)
	{
		vm->mem[i] = ch->code[j];
		++i;
		++j;
	}
	return (1);
}

int			init(t_vm *vm)
{
	t_champ	*tmp;

	if (vm->nb_player > MAX_PLAYERS || vm->nb_player < 2)
	{
		ft_dprintf(2, "corewar: incorrect number of players\n");
		return (0);
	}
	tmp = vm->champs;
	while (tmp)
	{
		load_champ(vm, tmp);
		tmp = tmp->next;
	}
	return (1);
}

/* ########################## MAIN #######################  */

int			main(int argc, char **argv)
{
	t_vm	vm;

	vm = (t_vm){0, {0}, 0, NULL};
	if (argc >= 2)
	{
		if (!(parse_args(argc, argv, &vm)))
			return (EXIT_FAILURE);
		if (!(init(&vm)))
			return (EXIT_FAILURE);
		int	fd;
		fd = open("output_test", O_WRONLY | O_CREAT);
		write(fd, vm.mem, MEM_SIZE);
		close(fd);
		ft_printf("%x\n", vm.champs->magic);
		ft_printf("%s\n", vm.champs->name);
		ft_printf("%s\n", vm.champs->comment);
//		ft_printf("%s\n", vm.champs->code);
	}
	return (EXIT_SUCCESS);
}

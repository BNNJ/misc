#include <stdio.h>
#include <stdlib.h>

void	print_list(int *base, size_t size)
{
	for (size_t i = 0; i < size; ++i)
		printf("%d%c", base[i], " \n"[i == size - 1]);
}

/*
** is a bigger tham b ?
*/

int		is_bigger(const void* a, const void* b)
{
	return (*(int*)a > *(int*)b);
}

int		main(int argc, char **argv)
{
	int	base[argc - 1];

	for (int i = 0; i < argc - 1; ++i)
		base[i] = atoi(argv[i + 1]);

	qsort(base, argc, sizeof(int), is_bigger);

	print_list(base, argc - 1);
	return (0);
}

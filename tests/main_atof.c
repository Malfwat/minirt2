#include <stdio.h>
#include <str.h>

int	main(int ac, char **av)
{
	double	d;

	if (ac != 2)
		return (printf("usage: %s <nombre>\n", av[0]), 1);
	if (!ft_atof(av[1], 2, &d))
		return (printf("ERR\n"), 1);
	printf("%s -> %f\n", av[1], d);
	return (0);
}

//cc tests/main_atof.c srcs/string/{ft_strlen.c,ft_atof.c,ft_strchr.c} -I includes

#define _POSIX_C_SOURCE 200809L

#include "rt_struct.h"
#include "rt_error.h"
#include "rt_parsing.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_case
{
	const char		*input;
	t_err			expected_err;
	int				expected_value;
}	t_case;

/*
** Cases where expected_err != ok must not modify the output value,
** so the sentinel 200 is used to detect a write on the error path.
*/
static int	run_case(t_case c, int index)
{
	char			*copy;
	__UINT8_TYPE__	fov;
	t_err			err;
	int				bad;

	copy = strdup(c.input);
	if (!copy)
		return (1);
	fov = 200;
	err = get_fov(copy, &fov);
	bad = 0;
	if (err != c.expected_err)
		bad = 1;
	if (c.expected_err == ok && (int)fov != c.expected_value)
		bad = 1;
	printf("%-3d %-10s entree=%-10s attendu=(%d, %d) obtenu=(%d, %d)\n",
		index, bad ? "FAIL" : "ok", c.input, (int)c.expected_err,
		c.expected_value, (int)err, (int)fov);
	free(copy);
	return (bad);
}

int	main(void)
{
	static const t_case	cases[] = {
	{"0", ok, 0},
	{"70", ok, 70},
	{"180", ok, 180},
	{"180\n", ok, 180},
	{"70 ", ok, 70},
	{"70\t", ok, 70},
	{"0070", ok, 70},
	{"", bad_fov_format, 0},
	{"-1", bad_fov_format, 0},
	{"181", bad_fov_format, 0},
	{"300", bad_fov_format, 0},
	{"70.5", bad_fov_format, 0},
	{"abc", bad_fov_format, 0},
	{"70abc", bad_fov_format, 0},
	{" 70", bad_fov_format, 0},
	{"+70", bad_fov_format, 0},
	{".", bad_fov_format, 0},
	{"7000000000", bad_fov_format, 0},
	{NULL, ok, 0}
	};
	int	failures;
	int	i;

	failures = 0;
	i = 0;
	while (cases[i].input)
	{
		failures += run_case(cases[i], i);
		i++;
	}
	printf("\n%d case(s) sur %d en echec\n", failures, i);
	return (failures != 0);
}

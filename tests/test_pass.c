/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_pass.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 16:44:47 by me                #+#    #+#             */
/*   Updated: 2026/11/12 19:58:00 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

void	pass_id(char **str_ptr);
void	pass_component(char **str_ptr);
void	pass_color(char **str_ptr);

/*
** Chaque cas donne l'entree et le reste attendu apres l'appel.
** Un pointeur inchange signifie que la fonction a refuse d'avancer :
** c'est le contrat de pass_color sur une entree invalide.
*/
typedef struct s_case
{
	const char	*input;
	const char	*expected;
}	t_case;

static int	run_one(const char *label, void (*fn)(char **),
		t_case c, int index)
{
	char	buf[128];
	char	*p;
	int		bad;

	strcpy(buf, c.input);
	p = buf;
	fn(&p);
	bad = (p == NULL || strcmp(p, c.expected) != 0);
	printf("%-3d %-5s %-9s \"%-18s\" attendu=\"%s\" obtenu=\"%s\"\n",
		index, bad ? "FAIL" : "ok", label, c.input, c.expected,
		p ? p : "(null)");
	return (bad);
}

static int	run_table(const char *label, void (*fn)(char **),
		const t_case *cases)
{
	int	index;
	int	failures;

	index = 0;
	failures = 0;
	while (cases[index].input)
	{
		failures += run_one(label, fn, cases[index], index);
		index++;
	}
	return (failures);
}

int	main(void)
{
	static const t_case	color_cases[] = {
	{"255,255,255", ""},
	{"255, 255, 255", ""},
	{"0,0,0 ", ""},
	{"255,255,255 0.6", "0.6"},
	{"0,0,255\n", ""},
	{"255,255", "255,255"},
	{"255,0", "255,0"},
	{"abc", "abc"},
	{"", ""},
	{NULL, NULL}
	};
	static const t_case	id_cases[] = {
	{"sp 0,0,20", "0,0,20"},
	{"A 0.2 255,255,255", "0.2 255,255,255"},
	{"   sp 0,0,20", "sp 0,0,20"},
	{"A", ""},
	{"", ""},
	{NULL, NULL}
	};
	int	failures;

	failures = 0;
	printf("--- pass_color ---\n");
	failures += run_table("color", pass_color, color_cases);
	printf("--- pass_id ---\n");
	failures += run_table("id", pass_id, id_cases);
	printf("--- pass_component (meme contrat que pass_id) ---\n");
	failures += run_table("component", pass_component, id_cases);
	printf("\n%d cas en echec\n", failures);
	return (failures != 0);
}

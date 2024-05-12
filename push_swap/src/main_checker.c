/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 22:25:02 by rchan--r          #+#    #+#             */
/*   Updated: 2022/12/13 21:29:25 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int		stk_exec_instr(t_stack **hd_a, t_stack **hd_b, char ***instr, int code);
int		instr_code(char *line);
void	free_line(char **line);

int	main(int argc, char **argv)
{
	char	*line;
	t_stack	*ha;
	t_stack	*hb;
	char	**instr;
	int		res;

	if (argc == 1)
		return (0);
	init_push_swap(&ha, &hb, &instr);
	if (read_input(&ha, argv + 1, argc - 1) == 0)
		return (ft_printf("Error\n"), stk_free(&ha), 0);
	line = get_next_line(0);
	res = 1;
	while (line != NULL && res != 0)
	{
		res = stk_exec_instr(&ha, &hb, &instr, instr_code(line));
		free_line(&line);
		if (res != 0)
			line = get_next_line(0);
	}
	if (!line && res == 1 && stk_is_sorted(ha) && !stk_length(hb))
		ft_printf("OK\n");
	else
		ft_printf("KO\n");
	return (free(line), stk_free(&ha), stk_free(&hb), instr_free(&instr), 0);
}

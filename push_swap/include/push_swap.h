/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 21:37:08 by rchan--r          #+#    #+#             */
/*   Updated: 2022/12/13 11:18:21 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"
# include "limits.h"

# define INIT_SIZE 10
# define SA 0
# define SB 1
# define SS 2
# define PA 10
# define PB 11
# define RA 20
# define RB 21
# define RR 22
# define RRA 30
# define RRB 31
# define RRR 32

typedef struct s_stack
{
	int				i;
	struct s_stack	*next;
}	t_stack;

int		read_input(t_stack **head, char **argv, int argc);
void	init_push_swap(t_stack **head_a, t_stack **head_b, char ***instr);

t_stack	*stknew(int i);
void	stkadd_back(t_stack **stk, t_stack *new);
int		stk_no_duplicate(t_stack *stk, int i);
void	stk_free(t_stack **head);
int		stk_is_sorted(t_stack *stk);

t_stack	*stk_tail(t_stack *head);
t_stack	*stk_before_tail(t_stack *head);
int		stk_length(t_stack *head);
t_stack	*stk_smallest(t_stack *head);
int		stk_order(t_stack **head, char ***instr, char c);

int		node_nb_top(t_stack *node, t_stack *head, int *direction);
int		node_to_top(t_stack **head, t_stack *node, char ***instr, char c);
t_stack	*node_find_next(t_stack *head, int *nb, int i);
int		node_insert(t_stack **ha, t_stack **hb, t_stack *node_b, char ***instr);

t_stack	*node_next_to_insert(t_stack *head_a, t_stack *head_b);

char	*instr_str(int s);

void	instr_free(char ***instr);
int		instr_write(char ***instr, char *str);

void	instr_print_ab(char	*str, int count_a, int count_b);
void	instr_print_opti(char **instr);

int		stk_push(t_stack **head_src, t_stack **head_dst, char ***instr, int s);
int		stk_swap(t_stack **stk, char ***instr, int s);
int		stk_swap_both(t_stack **head_a, t_stack **head_b, char ***instr);
int		stk_rotate(t_stack **head, char ***instr, int s);
int		stk_rotate_both(t_stack **head_a, t_stack **head_b, char ***instr);
int		stk_rotate_both(t_stack **head_a, t_stack **head_b, char ***instr);
int		stk_rev_rotate(t_stack **head, char ***instr, int s);
int		stk_rev_rotate_both(t_stack **head_a, t_stack **head_b, char ***instr);
int		stk_exec_r_instr(t_stack **head, int nb, char ***instr, char c);
int		stk_exec_r_r_instr(t_stack **head, int nb, char ***instr, char c);

long	stk_median(t_stack *head);
int		stk_push_median(t_stack **hd_a, t_stack **hd_b, int mdn, char ***instr);

void	get_values3(t_stack	*head_a, int *top, int *middle, int *bottom);
int		solve3_case312(t_stack **head_a, char ***instr);
int		solve3_case213(t_stack **head_a, char ***instr);
int		solve3_case321(t_stack **head_a, char ***instr);
int		solve3_case231(t_stack **head_a, char ***instr);
int		solve3_case132(t_stack **head_a, char ***instr);

int		solve5_insert(t_stack **head_a, t_stack **head_b, char ***instr);

int		solve(t_stack **head_a, t_stack **head_b, char ***instr, int argc);
#endif

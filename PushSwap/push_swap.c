/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaarafi <mmaarafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 20:18:34 by mmaarafi          #+#    #+#             */
/*   Updated: 2025/02/07 15:40:44 by mmaarafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	argument_check(char **str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		if ((str[i][j] == '+' || str[i][j] == '-') && str[i][j + 1] != 0)
			j++;
		while (str[i][j])
		{
			if (!(str[i][j] >= '0' && str[i][j] <= '9'))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	free_strs(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free (strs[i]);
		strs[i] = NULL;
		i++;
	}
	free (strs);
	strs = NULL;
}

void	add_arguments(t_stack **stack_a, char **strs)
{
	long long	var;
	t_stack	*tmp;
	int			i;

	i = 0;
	while (strs[i])
	{
		var = ft_atoi(strs[i]);
		if (var > INT_MAX || var < INT_MIN)
		{
			write(2, "Error\n", 6);
			ft_lstclear(stack_a);
			exit(0);
		}
		tmp = ft_lstnew(var);
		ft_lstadd_back(stack_a, tmp);
		i++;
	}
	free_strs(strs);
}

void	check_duplicate(t_stack **stack_a)
{
	t_stack	*tmp;
	t_stack	*another_tmp;
	int			count;

	tmp = *stack_a;
	while (tmp)
	{
		count = 0;
		another_tmp = *stack_a;
		while (another_tmp)
		{
			if (tmp->data == another_tmp->data)
				count++;
			another_tmp = another_tmp->next;
		}
		if (count > 1)
		{
			write(2, "Error\n", 6);
			ft_lstclear(stack_a);
			exit(0);
		}
		tmp = tmp->next;
	}
}

int	main(int ac, char **av)
{
	char		**strs;
	int			i;
	t_stack		*stack_a;
	t_stack 	*stack_b;

	stack_a = NULL;
	i = 1;
	while (i < ac)
	{
		strs = ft_split(av[i], ' ');
		if (argument_check(strs))
			add_arguments(&stack_a, strs);
		else
		{
			write(2, "Error\n", 6);
			ft_lstclear(&stack_a);
			break ;
		}
		i++;
	}
	check_duplicate(&stack_a);
	// mini_get_next_line();
	while(stack_a)
	{
		printf("this is the content : %d\n", stack_a->data);
		stack_a = stack_a->next;
	}
	return (0);
}

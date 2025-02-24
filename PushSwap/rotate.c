#include "header.h"

void	ra(t_stack **stack)
{
	t_stack	*tmp;
	t_stack *ptr;

	if (!stack || !(*stack) || !((*stack)->next))
		return ;
	tmp = ft_lstnew((*stack)->data);
	ptr = *stack;
	while(ptr)
	{
		ptr->data = (ptr->next)->data;
		ptr = ptr->next;
		if(ptr->next == NULL)
		{
			ptr->data = tmp->data;
			break;
		}
	}
	ft_lstclear(&tmp);
	write(1, "ra\n", 3);
}

void	rb(t_stack **stack)
{
	t_stack	*tmp;
	t_stack *ptr;

	if (!stack || !(*stack) || !((*stack)->next))
		return ;
	tmp = ft_lstnew((*stack)->data);
	ptr = *stack;
	while(ptr)
	{
		ptr->data = (ptr->next)->data;
		ptr = ptr->next;
		if(ptr->next == NULL)
		{
			ptr->data = tmp->data;
			break;
		}
	}
	ft_lstclear(&tmp);
	write(1, "rb\n", 3);
}

void	rr(t_stack **stacka, t_stack **stackb)
{
	ra(stacka);
	rb(stackb);
	write(1, "rr\n", 3);
}

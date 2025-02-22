#include "header.h"

void	rotate(t_stack **stack)
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
}

void	rotate_both(t_stack **stacka, t_stack **stackb)
{
	rotate(stacka);
	rotate(stackb);
}

#include "header.h"

void	ra(t_stack **head)
{
	t_stack	*tail;

	if (*head == NULL || (*head)->next == NULL)
		return ;
	tail = *head;
	while (tail->next != NULL)
		tail = tail->next;
	tail->next = *head;
	*head = (*head)->next;
	tail->next->next = NULL;
	write(1, "ra\n", 3);
}
void	rb(t_stack **head)
{
	t_stack	*tail;

	if (*head == NULL || (*head)->next == NULL)
		return ;
	tail = *head;
	while (tail->next != NULL)
		tail = tail->next;
	tail->next = *head;
	*head = (*head)->next;
	tail->next->next = NULL;
	write(1, "rb\n", 3);
}


void	rr(t_stack **stacka, t_stack **stackb)
{
	ra(stacka);
	rb(stackb);
	write(1, "rr\n", 3);
}

// #include "../minishell.h"


// void			ft_lstadd_front(t_list **alst, t_list *new)
// {
// 	if (*alst)
// 	{
// 		new->next = *alst;
// 		*alst = new;
// 	}
// 	else
// 		*alst = new;
// }

// t_list			*ft_lstnew(char *part)
// {
// 	t_list		*tab;

// 	tab = malloc(sizeof(t_list));
// 	if (!tab)
// 		return (NULL);
// 	tab->part = strdup(part);
// 	tab->next = NULL;
// 	return (tab);
// }

// void			ft_lstclear(t_list **lst)
// {
// 	t_list		*ptr;
// 	t_list		*ptr1;

// 	ptr = *lst;
// 	if (ptr)
// 	{
// 		while (ptr)
// 		{
// 			ptr1 = ptr->next;
// 			free(ptr);
// 			ptr = ptr1;
// 		}
// 		*lst = NULL;
// 	}
// }
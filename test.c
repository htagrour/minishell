#include "minishell.h"
typedef struct  s_test
{
    char *str;
    int num;
}t_test;

void f(void *d)
{
    printf("%s %d\n", ((t_test*)d)->str, ((t_test*)d)->num);
}

void c(void *s)
{
    t_test *temp = s;
    if (temp->str)
        free(temp->str);
    temp->num = 0;
}

int main()
{
    t_list *list;
    int i = 0;

    t_test *test;

    list = (t_list*)malloc(sizeof(t_list));
    ft_bzero(&list, sizeof(t_list*));
    test = (t_test*)malloc(sizeof(t_test));
    test->str = ft_strdup("hello");
    test->num = 17;
    printf("hello wordl\n");
    ft_lstadd_back(&list, ft_lstnew((void*)test));
    ft_lstiter(list, &f);
    ft_lstclear(&list, &c);
    ft_lstiter(list, &f);
    return 0;
}
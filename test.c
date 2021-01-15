#include "minishell.h"
typedef struct  s_test
{
    char *str;
    int num;
}t_test;

void f(void *d)
{
    printf("%s\n", ((t_test*)d)->str);
}

void c(void *s)
{
    t_test *temp = s;

    free(temp->str);
    temp->num = 0;
}

int main()
{
    t_list *list;
    char *str = "str";
    int i = 0;
    t_list *temp;

    t_test *test;
    test = (t_test*)malloc(sizeof(t_test));
    test->str = ft_strdup("hello");
    test->num = 0;
    printf("hi\n");
    ft_lstadd_back(&list, ft_lstnew((void*)test));
    ft_lstiter(list, &f);
    ft_lstclear(&list, &c);
    return 0;
}
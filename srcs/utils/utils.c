
#include "../../minishell.h"

char	**list_to_array(t_list *list)
{
	char	**tab;
	int		i;

	tab = malloc(sizeof(char **) * (ft_lstsize(list) + 1));
	i = 0;
	while (list)
	{
		tab[i++] = ft_strdup((char*)list->content);
		list = list->next;
	}
	tab[i] = NULL;
	return (tab);
}

int	print_error(char *str, int error, t_hash_map *env)
{
	char	*temp;

	temp = ft_itoa(error);
	ft_putendl_fd(str, STDOUT_FILENO, 1);
	set_value("?", temp, env);
	free(temp);
	errno = error;
	return (error);
}

int	free_array(void **array)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
	return (-1);
}

void	swap(char **str1, char **str2)
{
	char	*temp;

	temp = *str1;
	*str1 = *str2;
	*str2 = temp;
}

void	bubblesort(char **tab, int len)
{
	int	i;
	int	j;

	i = 0;
	while (i < len - 1)
	{
		j = i + 1;
		while (j < len)
		{
			if (strcmp(tab[j], tab[i]) < 0)
				swap(&tab[j], &tab[i]);
			j++;
		}
		i++;
	}
}

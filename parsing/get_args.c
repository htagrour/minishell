#include "../minishell.h"

int is_red(char c) // is a redirection char
{
	return (c == '<' || c == '>');
}

int get_file(t_command *command, char *str, int *i)
{
	int double_red = 0;

	*i += 1;
	if (is_red(str[*i]) && str[*i] == str[*i -1])
	{
		if (str[*i] == '<')
			//error
			return 0;
		double_red = 1;
		*i+= 1;
	}
	while(str[*i] && str[*i] == ' ')
		*i+=1;
	if (is_red(str[*i]))
		//error
		return 0;
	int j = 0;
	while(str[*i + j] && !is_red(str[*i + j]) && str[*i + j] != ' ')
		write(1,&str[*i + j++], 1);
	write(1,"|\n", 2);
	return 1;
}

int ft_get_args(t_command *command, char *str)
{
    int value = 1;
    int i = 0;

    while(str[i])
    {
	    while(str[i] == ' ')
		  i++;
	    if (is_red(str[i]))
		    get_file(command, str, &i);
	    i++;
    }
    return value;
}

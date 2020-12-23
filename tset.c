#include <stdio.h>
#include <string.h>
#include "minishell.h"

int main(void)
{
	char **tab;
	int i = 0;
	tab = updated_split("echo 'hello wordl;hello';cmd;", ';');
	while (tab[i])
		printf("%s\n", tab[i++]);
}
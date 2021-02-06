#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "../hash_table/hash_table.h"

int
main(int argc, char *argv[], char *env[])
{
  t_hash_map *dic;

  dic = init_hash_map(2);
  int i = -1;
   set_value("PATH", "/bin", dic);
   set_value("APTH", "hello", dic);
   set_value("ATPH", "hello", dic);
   delet_value("PATH", dic);
  // char *str = get_value("PATH", dic);
  char **tab = hash_to_arr(dic);
  printf("%d\n", dic->elem_total);

  while (tab[++i])
  {
    printf("%s\n", tab[i]);
    free(tab[i]);
  }
  free(tab);
  // free(str);
  free_hash_map(dic);
  return 0;
}
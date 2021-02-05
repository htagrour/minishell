#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "../hash_table/hash_table.h"

int
main(int argc, char *argv[], char *env[])
{
  t_hash_map *dic;

  dic = init_hash_map(100);
  set_value("PATH", "/bin", dic);
  printf("%s\n", get_value("PATH", dic));
  free_hash_map(dic);
  return 0;
}
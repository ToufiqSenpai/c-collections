#include <stdio.h>
#include "../src/list.h"

void foreach_action(const void *element) {
  printf("%s", (char*) element);
}

int main() {
  List *list;

  list_init(list);
  list_add(list, "Muhammad");
  list_add(list, "Taufiqurrahman");
  list_foreach(list, foreach_action);
}

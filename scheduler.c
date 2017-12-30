#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sch_func.c"
#include "menu.c"

int main(int argc, char* argv[]){
  List* procs = get_procs();
  int size = procs->size;
  int quantum, algo = choose_algo(&quantum);
  process* result = NULL;

  switch(algo){
    case FCFS:
      result = fcfs(procs);
      break;
    case SJF:
      result = sjf(procs);
      break;
    case SRTF:
      result = srtf(procs);
      break;
    case RR:
      result = rr(procs, quantum);
      break;
  }
  print_info(result, size);
  return 0;
}

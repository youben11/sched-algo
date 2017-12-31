/*Describe the execution flow
  of a process
  */
typedef struct execution{
  int start;
  int end;
  struct execution* next;
} execution;

typedef struct {
  char name; //process name
  int t_arr; //arrival time
  int t_exe; //execution time
  int t_rem; //remaining time
  int t_end; //end time
  execution* exe;
} process;

/*Describe an element in the List
  contain a process and a pointer to the next element
  */
typedef struct elem {
  process proc;
  struct elem* next;
} elem;

/*Describe a List
  containt the size of the list and a pointer to the first element
  */
typedef struct {
  int size;
  elem* first;
} List;

/*Add a new execution to a process*/
void add_exe(process* p, int start, int end){
  if(p->exe == NULL){
    p->exe = malloc(sizeof(execution));
    p->exe->start = start;
    p->exe->end = end;
    p->exe->next = NULL;
    return;
  }
  execution* e = p->exe;
  while(e->next != NULL)
    e = e->next;

  e->next = malloc(sizeof(execution));
  e->next->start = start;
  e->next->end = end;
  e->next->next = NULL;
}


/*Create a new element at the end of the list
  which contain the process proc
  also increment the size
  */
void add(List* processes, process proc){
  elem *e,*next;
  e = malloc(sizeof(elem));
  e->proc = proc;
  e->next = NULL;


  if (processes->first == NULL) {
    processes->first = e;
    processes->size++;
    return;
  }
  if (processes->first->next == NULL){
    processes->first->next = e;
    processes->size++;
    return;
  }

  next = processes->first;
  while(next->next->next != NULL)
    next = next->next;

  next->next->next = e;
  processes->size++;
  return;
}

/*Returns the process of the first element in the list
  or NULL if it's empty
  also decrement the size if not empty
  */
process* pop(List* processes){
  if(processes->size == 0)
    return NULL;

  process* p = malloc(sizeof(process));
  elem* e = processes->first;
  processes->first = e->next;
  processes->size--;
  memcpy(p, &e->proc, sizeof(process));
  free(e);
  return p;
}

/*Switch two process*/
void switch_proc(process* p1, process* p2){
  process* tmp = malloc(sizeof(process));
  memcpy(tmp, p1, sizeof(process));
  memcpy(p1, p2, sizeof(process));
  memcpy(p2, tmp, sizeof(process));
  free(tmp);
}

/*Sort the list of processes according to
  their arrival time
  */
void sort_arr(List* processes){
  int size = processes->size;
  if(size <= 1)
    return;

  elem* e;
  char sorted = 0;


  while(!sorted){
    sorted = 1;
    e = processes->first;

    for(int i=0; i<--size; i++){
      if(e->proc.t_arr > e->next->proc.t_arr){
        switch_proc(&e->proc, &e->next->proc);
        sorted = 0;
      }
      e = e->next;
    }
  }
}

/*Sort the list of processes according to
  their execution time
  */
void sort_exe(List* processes){
  int size = processes->size;
  if(size <= 1)
    return;

  elem* e;
  char sorted = 0;


  while(!sorted){
    sorted = 1;
    e = processes->first;

    for(int i=0; i<--size; i++){
      if(e->proc.t_exe > e->next->proc.t_exe){
        switch_proc(&e->proc, &e->next->proc);
        sorted = 0;
      }
      e = e->next;
    }
  }
}

/*Sort the list of processes according to
  their remaining time
  */
void sort_rem(List* processes){
  int size = processes->size;
  if(size <= 1)
    return;

  elem* e;
  char sorted = 0;


  while(!sorted){
    sorted = 1;
    e = processes->first;

    for(int i=0; i<--size; i++){
      if(e->proc.t_rem > e->next->proc.t_rem){
        switch_proc(&e->proc, &e->next->proc);
        sorted = 0;
      }
      e = e->next;
    }
  }
}

/*Get only the process that already arrived
  from processes and add them to arrived
  also return the number of process that arrived
  */
int get_arrived(List* processes, List* arrived, int time){
  process* p;
  sort_arr(processes);
  int count = 0;

  while(processes->size){
    if(processes->first->proc.t_arr <= time){
      p = pop(processes);
      add(arrived,*p);
      count++;
    }else break;
  }
  return count;
}

/*Scheduele the process using
  the Fist Come First Served algorithm
  */
process* fcfs(List* processes){
  int time = 0;
  int i = 0;
  process* p = NULL;
  process* result = malloc(sizeof(process) * processes->size);

  sort_arr(processes);
  while(processes->size){
    p = pop(processes);
    while(time < p->t_arr) //no process has arrived
      time++;

    add_exe(p, time, time + p->t_exe);
    time += p->t_exe;
    p->t_end = time;
    p->t_rem = 0;
    memcpy(result + i, p, sizeof(process));
    i++;
  }
  return result;
}

/*Scheduele the process using
  the Shortest Job First algorithm
  */
process* sjf(List* processes){
  int time = 0;
  int i = 0;
  List* arrived = malloc(sizeof(List));
  arrived->size = 0;
  arrived->first = NULL;
  process* p = NULL;
  process* result = malloc(sizeof(process) * processes->size);

  while(processes->size || arrived->size){
    get_arrived(processes, arrived, time);
    sort_exe(arrived);
    p = pop(arrived);

    if(p == NULL){//no process has arrived
      time++;
      continue;
    }

    add_exe(p, time, time + p->t_exe);
    time += p->t_exe;
    p->t_end = time;
    p->t_rem = 0;
    memcpy(result + i, p, sizeof(process));
    i++;
  }
  return result;
}

/*Scheduele the process using
  the Shortest Remaining Time First algorithm
  */
process* srtf(List* processes){

}

/*Scheduele the process using
  the Round Robin algorithm
  */
process* rr(List* processes, int quantum){
  int time = 0;
  int t_used, i = 0;
  List* arrived = malloc(sizeof(List));
  arrived->size = 0;
  arrived->first = NULL;
  process* p = NULL;
  process* result = malloc(sizeof(process) * processes->size);

  while(processes->size || arrived->size){
    get_arrived(processes, arrived, time);
    if (p != NULL)//last process didn't end
      add(arrived, *p);
    p = pop(arrived);

    if(p == NULL){//no process has arrived
      time++;
      continue;
    }

    t_used = (p->t_rem < quantum) ? p->t_rem : quantum;
    add_exe(p, time, time + t_used);
    time += t_used;
    p->t_rem -= t_used;

    if(p->t_rem == 0){//process ended
      p->t_end = time;
      memcpy(result + i, p, sizeof(process));
      p = NULL;
      i++;
    }
  }
  return result;
}

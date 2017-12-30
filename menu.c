#define FCFS 0
#define SJF 1
#define SRTF 2
#define RR 3

void empty_buf(){
  while(getchar() != '\n');
}

/*Make sure that it returns an int*/
int read_int(){
  int buf;
  scanf("%d",&buf);
  empty_buf();
  return buf;
}

/*Returns a list of processes to be scheduled
  from the user
  */
List* get_procs(){
  List* processes = malloc(sizeof(List));
  processes->size = 0;
  processes->first = NULL;
  int n_proc = -1;
  process p;
  p.exe = NULL;

  puts("");
  printf("How many process do you want? (int) ");
  n_proc = read_int();

  for(int i=0;i<n_proc;i++){
    printf("process %d:\n", i+1);
    printf("\tname:(one char) ");
    scanf("%c",&p.name);
    empty_buf();
    printf("\tarrival time:(int) ");
    p.t_arr = read_int();
    printf("\texecution time:(int) ");
    p.t_exe = read_int();
    p.t_rem = p.t_exe;
    add(processes, p);
  }
  puts("");

  return processes;
}

/*Return the number of the scheduling
  algorithm to be used*/
int choose_algo(int* quantum){
  int choice = -1;
  puts("");
  puts("Choose an algorithm between:");
  puts("0-First Come First Served");
  puts("1-Shortest Job First");
  puts("2-Shortest Remaining Time First");
  puts("3-Round Robin");
  do{
    choice = read_int();
  }while(choice < FCFS || choice > RR);

  if(choice == RR){
    printf("Specify the quantum: ");
    *quantum = read_int();
  }
  puts("");
  return choice;
}

/*Print infomation of a process*/
void print_proc(process* p){
  printf("name: %c arr_time: %d exec_time: %d end_time: %d\n",p->name,p->t_arr, p->t_exe,p->t_end);
  execution* e = p->exe;
  while(e != NULL){
    printf("\t from %d to %d\n",e->start, e->end);
    e = e->next;
  }
}

/*Print Gant diagram and other infomation related
  to scheduling
  */
void print_info(process* procs, int size){
  //print all the details of the simulation
}

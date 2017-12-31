#define FCFS 0
#define SJF 1
#define SRTF 2
#define RR 3

void empty_buf(){
  while(getchar() != '\n');
}

/*Make sure that it returns an int*/
int read_int(){
  char buf[6];
  char num;
  do{
    num = 1;
    scanf("%5s",buf);
    for(int i=0;i<strlen(buf);i++){
      if(buf[i] < 48 || buf[i] > 57)
        num = 0;
    }
    empty_buf();
    if(!num)
      printf("Input an int please: ");
  }while(!num);

  return atoi(buf);
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
  printf("name: '%c', arr_time: %d, exec_time: %d, end_time: %d\n",p->name,p->t_arr, p->t_exe,p->t_end);
  execution* e = p->exe;
  while(e != NULL){
    printf("\t from %d to %d\n",e->start, e->end);
    e = e->next;
  }
}

/*Returns the average waiting time*/
float avg_wait(process* procs, int size){
  float sum = 0;
  for(int i=0;i<size;i++){
    sum += procs[i].t_end - procs[i].t_arr - procs[i].t_exe;
  }
  return sum / size;
}

/*Returns the average residence time*/
float avg_res(process* procs, int size){
  float sum = 0;
  for(int i=0;i<size;i++){
    sum += procs[i].t_end - procs[i].t_arr;
  }
  return sum / size;
}

/*Print Gant diagram and other infomation related
  to scheduling
  */
void print_info(process* procs, int size){
  execution* e = NULL;
  int end_time = procs[size - 1].t_end;
  int str_size = end_time + 3;
  int padd = 2;
  char** gant = malloc(sizeof(char*) * size);

  for(int i=0;i<size;i++)
    gant[i] = malloc(sizeof(char) * str_size);
  for(int i=0;i<str_size;i++)//init the first string with spaces
    gant[0][i] = ' ';
  gant[0][str_size-1] = '\0';

  for(int i=1;i<size;i++)//copy the first string into the others
    memcpy(gant[i],gant[0], sizeof(char) * str_size);

  for(int i=0;i<size;i++){//build the Gant diagram
    gant[i][0] = procs[i].name;
    e = procs[i].exe;
    while(e != NULL){
      for(int j=e->start+padd;j<e->end+padd;j++)
        gant[i][j] = '_';
      e = e->next;
    }
  }

  puts("");
  puts("Gant diagram:");
  puts("");
  for(int i=0;i<size;i++)
    printf("%s\n",gant[i]);
  puts("");
  puts("Process execution detail:");
  puts("");
  for(int i=0;i<size;i++)
    print_proc(&procs[i]);
  puts("");
  printf("Average waiting time: %f\n", avg_wait(procs, size));
  printf("Average residence time: %f\n", avg_res(procs, size));
  puts("");
}

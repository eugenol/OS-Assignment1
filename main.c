/*
Operating Systems assignment

*/

/*
1. Read all processes into linked list
2. switch to right algorithm
3. 

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _data {
    int start_time;
    int run_time;
    struct _data *next;  
};

struct _process {
	char ID[11];
    int pid;
	int arrival;
	int burst;
	int priority;
    struct _data *time_data;
    struct _process *next;
    struct _process *prev;
};

void add_proc_node(struct _process **head,struct _process data);
void print_proc_nodes(struct _process *head);
void add_time_node(struct _data **head,struct _data data);
int queue_length(struct _process *head);

void sort_queue(struct _process *head);
void assign_pid(struct _process *head);

//Function prototypes for schedulers
int FCFS(struct _process **process_queue, struct _process **ready_queue, struct _process **done_queue, int quantum);
int SJF(struct _process **process_queue, struct _process **ready_queue, struct _process **done_queue, int quantum);
int RR(struct _process **process_queue, struct _process **ready_queue, struct _process **done_queue, int quantum);
int PP(struct _process **process_queue, struct _process **ready_queue, struct _process **done_queue, int quantum);

int main(int argc, char **argv)
{
	// Parse Arguments
	// Read in input file
	// Store in a list all the inputs
	// Run simulation, depending on choice
	// Display results
	FILE *fptr;
	int scheduler;
	int quantum = 0;
    char input_file[21] = {0};
	char scheduler_type[5] ={0};
    struct _process temp_process = {{0},0,0,0,0,NULL,NULL,NULL};
    struct _process *queue_head = NULL;
    struct _data temp_data = {1,10};
    
    //array of function pointers to scheduling algorithms
    int (*schedulers[4])(struct _process **, struct _process **, struct _process **, int ) = {FCFS, SJF, RR, PP};
    
    // arg c has to be at least 3 - name of program, and 2 arguments    	
	if (argc < 3)
	{
		printf("Usage is: sheduler <input file> <Scheduler> <quantum (optional)>");
		return EXIT_FAILURE;
	}
    
    //Store given arguments in variables
    // 1st arg is scheduler algorithm to use
    // 2rd arg is optional - only needed for round robin - quantum
    // 3nd arg is the name of the input file
 
    strcpy(scheduler_type, argv[1]); 
    printf("%s\n",scheduler_type);
       
    //if round robin, read quantum and input file in argv[3]
    //otherwise inputfile is in argv[2]
    if(strcmp(scheduler_type,"RR")==0)
    {
        quantum = (int)strtol(argv[2],NULL,10);
        quantum = quantum < 1 ? 1 : quantum;
        if (argc < 4)
        {
            printf("Too few arguments for this scheduling algorithm.\n");
            return EXIT_FAILURE;
        } 
        strcpy(input_file, argv[3]);       
    }
    else
    {
        if (argc > 3)
        {
            printf("Too many arguments for this scheduling algorithm.\n");
            return EXIT_FAILURE;
        } 
        strcpy(input_file, argv[2]);    
    }    

    if(strcmp(scheduler_type,"FCFS")==0)
        scheduler = 0;
    else if(strcmp(scheduler_type,"SJF")==0)
        scheduler = 1;
    else if(strcmp(scheduler_type,"RR")==0)
        scheduler = 2;
    else if(strcmp(scheduler_type,"PP")==0)
        scheduler = 3;
    else
    {
        printf("Invalid scheduler chosen.\n");
        return EXIT_FAILURE;
    }


    printf("%s\n",input_file);
    printf("%d\n",quantum);
    printf("%d\n",scheduler);
        
    //Now, read all the data in from the spesified input file
	fptr = fopen(input_file,"r");	
    if(!fptr)
 	{
		printf("Could not open input file\n");
		return EXIT_FAILURE;
	}  
    
    //go through input file and read all values, store in linked list   
    while(fscanf(fptr,"%s %d %d %d\n", temp_process.ID, &temp_process.arrival, &temp_process.burst, &temp_process.priority)==4)
    {
        //printf("%s %d %d %d %d\n", temp_process.ID, temp_process.arrival, temp_process.burst, temp_process.priority, temp_process.pid);
        add_proc_node(&queue_head,temp_process);
    }
    
    fclose(fptr); //close file
   
    // testing   
    add_time_node(&queue_head->time_data,temp_data);
    add_time_node(&queue_head->time_data,temp_data);
    
    printf("Unsorted:\n");
    print_proc_nodes(queue_head);
    
    sort_queue(queue_head);
    
    printf("Sorted:\n");
    print_proc_nodes(queue_head);
    
    assign_pid(queue_head);
    printf("With pid:\n");
    print_proc_nodes(queue_head);
    
    
    printf("Queue length: %d\n",queue_length(queue_head));
    
    schedulers[scheduler];

    //free lists - NB. have to do this still
    
	return 0;	
}

void add_proc_node(struct _process **head,struct _process data)
{
    struct _process *temp; //new node 
    struct _process *iter = *head;    
    
    temp = malloc(sizeof(struct _process));
	
    strcpy(temp->ID, data.ID);
    temp->pid = data.pid;
	temp->arrival = data.arrival;
	temp->burst = data.burst;
	temp->priority = data.priority;
    temp->time_data = NULL;
    temp->next = NULL;
    temp->next = NULL;
    
    if(!iter)
    {
        //temp->pid = 0;
        *head = temp;
    }
    else
    {
        while(iter->next)
            iter = iter->next;
        
        //set correct valuest in temp
        //temp->pid = iter->pid + 1;
        temp->prev = iter;               
        iter->next = temp;
    }
}

void add_time_node(struct _data **head,struct _data data)
{
    struct _data *temp;
    struct _data *iter = *head;    
    
    temp = malloc(sizeof(struct _process));
    
    temp->start_time = data.start_time;
    temp->run_time =data.run_time;
    temp->next = NULL;  
    
    if(!iter)
    {
        *head = temp;
    }
    else
    {
        while(iter->next)
            iter = iter->next;
                       
        iter->next = temp;
        
    }
}

void print_proc_nodes(struct _process *head)
{
    struct _process *iter = head;
    struct _data *iter2;
       
    while(iter)
    {
        printf("%s %d\n",iter->ID, iter->pid);
        iter2 = iter->time_data;
        while(iter2)
        {
            printf("(%d %d)",iter2->start_time, iter2->run_time);\
            iter2 = iter2->next;
            if(!iter2)
                printf("\n");
        }
        iter = iter->next;
    }    
}

int queue_length(struct _process *head)
{
    struct _process *iter = head;
    int count = 0;
    
    while(iter)
    {
        count++;
        iter = iter->next;
    }
    
    return count;    
}

void sort_queue(struct _process *head)
{
    struct _process *iter1 = head;
    struct _process *iter2 = NULL;
    struct _process swap = {{0},0,0,0,0,NULL,NULL,NULL};
    
    int swapped;
    
    if(!head)
        return;
    
    do
    {
        swapped = 0;
        iter1 = head;
        
        while(iter1->next != iter2)
        {
            if(iter1->arrival > iter1->next->arrival)
            {
                //copy iter 1 values to swap
                strcpy(swap.ID,iter1->ID);
                swap.arrival = iter1->arrival;
                swap.burst = iter1->burst;
                swap.priority = iter1->priority;

                //swap iter1 and iter 2
                strcpy(iter1->ID,iter1->next->ID);
                iter1->arrival = iter1->next->arrival;
                iter1->burst = iter1->next->burst;
                iter1->priority = iter1->next->priority;

                //copy swap into iter 2
                strcpy(iter1->next->ID,swap.ID);
                iter1->next->arrival = swap.arrival;
                iter1->next->burst = swap.burst;
                iter1->next->priority = swap.priority;
                
                //swap has occured
                swapped =1;
            }
            iter1=iter1->next;
        }
        iter2 = iter1;
    } while (swapped);  
}

void assign_pid(struct _process *head)
{
    struct _process *iter = head;
        
    if(!iter) //handle empty queue
        return;
    
    iter->pid = 0; //set pid of first entry
    iter = iter->next;
    
    while(iter) //assign in order
    {
        iter->pid = iter->prev->pid+1;
        iter=iter->next;
    }      
}

int FCFS(struct _process **process_queue, struct _process **ready_queue, struct _process **done_queue, int quantum)
{
    return 0;
}

int SJF(struct _process **process_queue, struct _process **ready_queue, struct _process **done_queue, int quantum)
{
    return 0;
}

int RR(struct _process **process_queue, struct _process **ready_queue, struct _process **done_queue, int quantum)
{
    return 0;
}

int PP(struct _process **process_queue, struct _process **ready_queue, struct _process **done_queue, int quantum)
{
    return 0;
}
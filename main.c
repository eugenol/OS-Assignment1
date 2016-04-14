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
	int arrival;
	int burst;
	int priority;
    struct _data *time_data;
    struct _process *next;
};

void add_proc_node(struct _process *head,struct _process data);
void print_proc_nodes(struct _process *head);
void add_time_node(struct _data *head,struct _data data);


int main(int argc, char **argv)
{
	// Parse Arguments
	// Read in input file
	// Store in a list all the inputs
	// Run simulation, depending on choice
	// Display results
	FILE *fptr;
	int scheduler;
	long int quantum = 0;
    char input_file[21] = {0};
	char scheduler_type[3] ={0};
    struct _process temp_process;
    struct _process *queue_head;
    
        	
	if (argc < 3)
	{
		printf("Usage is: sheduler <input file> <Scheduler> <quantum (optional)>");
		return EXIT_FAILURE;
	}
    
    //Store given arguments in variables
    // 1st arg is input file name
    // 2nd is name of scheduling algorithm
    // 3rd arg is optional for round robin - quantum
    
    strcpy(input_file, argv[1]);
    strcpy(scheduler_type, argv[2]);
    
    printf("%s\n",input_file);
    printf("%s\n",scheduler_type);
    
    //if round robin, read quantum
    if(strcmp(scheduler_type,"RR")==0)
    {
        quantum = strtol(argv[3],NULL,10);
        quantum < 1 ? 1 : quantum;       
    }    
       
    printf("%d\n",quantum);
        
    //Now, read all the data in from the spesified input file
	fptr = fopen(input_file,"r");	
    if(!fptr)
 	{
		printf("Could not open input file");
		return EXIT_FAILURE;
	}  
       
    while(fscanf(fptr,"%s %d %d %d\n"),temp_process.ID,&temp_process.arrival,&temp_process.burst,&temp_process.priority)
    {
        add_proc_node(queue_head,temp_process);
    }
    
    print_proc_nodes(queue_head);    
    
	
	return 0;	
}

void add_proc_node(struct _process *head,struct _process data)
{
    struct _process *temp;
    struct _process *iter;    
    
    temp = malloc(sizeof(struct _process));
	
    strcpy(temp->ID, data.ID);
	temp->arrival = data.arrival;
	temp->burst = data.burst;
	temp->priority = data.priority;
    temp->time_data = NULL;
    temp->next = NULL;
    
    if(head==NULL)
    {
        head = temp;
    }
    else
    {
        while(iter->next)
            iter = iter->next;
                       
        iter->next = temp;
        
    }
}

void add_time_node(struct _data *head,struct _data data)
{
    struct _data *temp;
    struct _data *iter;    
    
    temp = malloc(sizeof(struct _process));
    
    temp->start_time = data.start_time;
    temp->run_time =data.run_time;
    temp->next = NULL;  
    
    if(head==NULL)
    {
        head = temp;
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
       
       if(head)
       {
            while(iter->next)
            {
                printf("%s",iter->ID);
            }    
       } 
}
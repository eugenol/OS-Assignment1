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
};

void add_proc_node(struct _process **head,struct _process data);
void print_proc_nodes(struct _process *head);
void add_time_node(struct _data **head,struct _data data);


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
    struct _process temp_process = {{0},0,0,0,0,NULL,NULL};
    struct _process *queue_head = NULL;
    struct _data temp_data = {1,10};
        	
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
        quantum = quantum < 1 ? 1 : quantum;       
    }    
       
    printf("%d\n",quantum);
        
    //Now, read all the data in from the spesified input file
	fptr = fopen(input_file,"r");	
    if(!fptr)
 	{
		printf("Could not open input file");
		return EXIT_FAILURE;
	}  
    
    //go through input file and read all values, store in linked list   
    while(fscanf(fptr,"%s %d %d %d\n", temp_process.ID, &temp_process.arrival, &temp_process.burst, &temp_process.priority)==4)
    {
        //printf("%s %d %d %d %d\n", temp_process.ID, temp_process.arrival, temp_process.burst, temp_process.priority, temp_process.pid);
        add_proc_node(&queue_head,temp_process);
    }
    
    fclose(fptr); //close file
       
    add_time_node(&queue_head->time_data,temp_data);
    add_time_node(&queue_head->time_data,temp_data);
    
    print_proc_nodes(queue_head);
        
/*    
    if(strcmp(scheduler_type,"RR")==0)
    {
   
    }
    else if(strcmp(scheduler_type,"RR")==0)
    {
        
    }
    else if(strcmp(scheduler_type,"RR")==0)
    {
        
    }
    else if(strcmp(scheduler_type,"RR")==0)
    {
        
    }      
*/	
    //free lists
    
	return 0;	
}

void add_proc_node(struct _process **head,struct _process data)
{
    struct _process *temp;
    struct _process *iter = *head;    
    
    temp = malloc(sizeof(struct _process));
	
    strcpy(temp->ID, data.ID);
    temp->pid = data.pid;
	temp->arrival = data.arrival;
	temp->burst = data.burst;
	temp->priority = data.priority;
    temp->time_data = NULL;
    temp->next = NULL;
    
    if(!iter)
    {
        temp->pid = 0;
        *head = temp;
    }
    else
    {
        while(iter->next)
            iter = iter->next;
        
        temp->pid = iter->pid + 1;               
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
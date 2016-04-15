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
#include "queue.h"
#include "FCFS.h"
#include "SJF.h"
#include "RR.h"
#include "PP.h"

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
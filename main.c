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
    struct _process *process_queue = NULL;
    struct _process *ready_queue = NULL;
    struct _process *done_queue = NULL;
    //struct _data temp_data = {1,10};
    int total_run_time = 0;
    float avg_turnaround_time = 0;
    float avg_waiting_time = 0;
    
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
       
    //if round robin or priority with preemption, read quantum and input file in argv[3]
    //otherwise inputfile is in argv[2]
    if(strcmp(scheduler_type,"RR")==0 || strcmp(scheduler_type,"PP")==0)
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
        add_proc_node(&process_queue,temp_process);
    }
    
    fclose(fptr); //close file

    // sort waiting processes accoring to start time
    sort_queue(process_queue, sort_by_arrival);
    // assign process id -- according to start time - similar to real OS
    assign_pid(process_queue);
    //call scheduler here

    total_run_time = schedulers[scheduler](&process_queue, &ready_queue, &done_queue, quantum);
   
    sort_queue(done_queue, sort_by_name);
    print_proc_nodes(done_queue);
    
    printf("Number of processes: %d\n",queue_length(done_queue));
    printf("Total Run Time: %d\n",total_run_time);
    printf("Throughput: %f\n", (float)queue_length(done_queue)/total_run_time);
    
    turnaround_wait_time(done_queue, &avg_turnaround_time, &avg_waiting_time);
    
    printf("Average turnaround time: %f\n", avg_turnaround_time);
    printf("Average waiting time: %f\n", avg_waiting_time);
   
    free_queue(&done_queue);
   
    // testing
    // below is for testing  
    /*
    add_time_node(&process_queue->time_data,temp_data);
    add_time_node(&process_queue->time_data,temp_data);
    
    printf("With pid:\n");
    print_proc_nodes(process_queue);
    printf("Queue length: %d\n",queue_length(process_queue));
    
    //remove_proc_node_from_front(&process_queue);
    
    printf("With pid:\n");
    print_proc_nodes(process_queue);
    printf("Queue length: %d\n",queue_length(process_queue));
    
    printf("Queue length: %d\n",queue_length(done_queue));
    
    printf("Total proc time: %d\n", proc_time_done(process_queue));
    printf("Total proc time: %d\n", proc_time_done(process_queue->next));
    
    printf("Original");
    print_proc_nodes(process_queue);
    remove_proc_node(&process_queue,process_queue);
    printf("Head Removed\n");
    print_proc_nodes(process_queue);
    remove_proc_node(&process_queue,process_queue->next->next);
    printf("Other removed\n");
    print_proc_nodes(process_queue);
    */
    //free lists - NB. have to do this still
    
	return 0;	
}
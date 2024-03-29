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
    char output_file[20] = {0};
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
		printf("Usage is: scheduler <Scheduler> <quantum (optional)> <input file>");
		return EXIT_FAILURE;
	}
    
    //Store given arguments in variables
    // 1st arg is scheduler algorithm to use
    // 2rd arg is optional - only needed for round robin - quantum
    // 3nd arg is the name of the input file
    
    // in case scheduler name does not fit in the string
    if(strlen(argv[1])> 4)
    {
        printf("Unknown Scheduler.\n");
        return EXIT_FAILURE;
    }
    
    strcpy(scheduler_type, argv[1]); 
       
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


    printf("Running simulation on %s with %s scheduler.\n\n",input_file, scheduler_type);

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
    
    turnaround_wait_time(done_queue, &avg_turnaround_time, &avg_waiting_time);
    
    
    printf("\nNumber of processes: %d\n",queue_length(done_queue));
    printf("Total Run Time: %d\n",total_run_time);
    printf("Throughput: %f\n", (float)queue_length(done_queue)/total_run_time);
    printf("Average turnaround time: %f\n", avg_turnaround_time);
    printf("Average waiting time: %f\n\n", avg_waiting_time);
    
    //create output file name
    sprintf(output_file,"output-%s.txt",scheduler_type);
    
    fptr = fopen(output_file,"w");
    fprintf(fptr,"Simulation Results: %s Scheduler.\n\n",scheduler_type);
    print_proc_nodes_to_file(done_queue, fptr);
    fprintf(fptr,"\nNumber of processes: %d\n",queue_length(done_queue));
    fprintf(fptr,"Total Run Time: %d\n",total_run_time);
    fprintf(fptr,"Throughput: %f\n", (float)queue_length(done_queue)/total_run_time);
    fprintf(fptr,"Average turnaround time: %f\n", avg_turnaround_time);
    fprintf(fptr,"Average waiting time: %f\n", avg_waiting_time);
   
    fclose(fptr);
   
    free_queue(&done_queue);
        
	return EXIT_SUCCESS;	
}
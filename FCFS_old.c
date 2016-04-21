#include "FCFS.h"
#include "queue.h"
#include <stdio.h>

int FCFS(struct _process **process_queue, struct _process **ready_queue, struct _process **done_queue, int quantum)
{
    int runtime = 0;
    int burst_time = 0;
    struct _process temp_proc = {{0},0,0,0,0,NULL,NULL,NULL};
    struct _data temp_time_data = {0, 0, NULL};
    
    *ready_queue = *process_queue;
    *process_queue = NULL;
    
    // if there is a process queue, send first process to the ready queue, set runtime
    // to start time, otherwise exit
    // this gets the ball rolling
    if(*ready_queue)
    {
        runtime = (*ready_queue)->arrival;
    }
    else
    {
        return runtime;
    }    
    
    // processws waiting in any of the queues?
    // loop to consume process
    while(*ready_queue)
    {
        //add info to time done
        //move runtime forward by time_left
        burst_time = (*ready_queue)->burst;
        temp_time_data.start_time = runtime;
        temp_time_data.run_time = burst_time;
        add_time_node(&(*ready_queue)->time_data,temp_time_data);
        //move process to done queue
        temp_proc = remove_proc_node_from_front(&*ready_queue);
        add_proc_node(&*done_queue,temp_proc);
        runtime += burst_time;
    }
    return runtime;
}
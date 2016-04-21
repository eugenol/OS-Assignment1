#include "RR.h"
#include "queue.h"
#include <limits.h>
#include <stdio.h>

int FCFS(struct _process **process_queue, struct _process **ready_queue, struct _process **done_queue, int quantum)
{
    int runtime = 0;
    int time_done = 0;
    int isempty = 0;
    struct _process temp_proc = {{0},0,0,0,0,NULL,NULL,NULL};
    struct _process *iter;
    struct _process *temp_ptr;
    struct _data temp_time_data = {0, 0, NULL};
    
    // if there is a process queue, send first process to the ready queue, set runtime
    // to start time, otherwise exit
    // this gets the ball rolling
    if(*process_queue)
    {
        temp_proc = remove_proc_node_from_front(&*process_queue);
        add_proc_node(&*ready_queue,temp_proc);
        runtime = temp_proc.arrival;
    }
    else
    {
        return runtime;
    }    
    
    // processws waiting in any of the queues?
    // loop to consume process
    while( *process_queue || *ready_queue)
    {
        // add waiting processes to the ready queue
        while(*process_queue)
        {
            if(runtime >= (*process_queue)->arrival)
            {
                temp_proc = remove_proc_node_from_front(&*process_queue);
                add_proc_node(&*ready_queue,temp_proc);
            }
            else
            {
                break;
            }
        }
                   
        //fix for long wait between processes                 
        isempty = 0;
        
        //start at head of queue            
        iter = *ready_queue;
        while(iter)
        {
            // check if process is done.
            time_done = iter->burst;

            //add info to time done
            temp_time_data.start_time = runtime;
            temp_time_data.run_time = time_done;
            add_time_node(&iter->time_data,temp_time_data);

            temp_ptr = iter;
            iter = iter->next; // point to next node
            //move process to done queue
            temp_proc = remove_proc_node(&*ready_queue, temp_ptr);
            add_proc_node(&*done_queue,temp_proc);
            //move runtime forward by time_left
            runtime += time_done;
                
            isempty = 1;
                        
        }
        
        if(!isempty)
        {
            //advance time in case there is long delay between processes
            runtime++;
        }       
    }
    return runtime;
}
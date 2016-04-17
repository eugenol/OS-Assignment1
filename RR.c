#include "RR.h"
#include "queue.h"
#include <limits.h>
#include <stdio.h>

int RR(struct _process **process_queue, struct _process **ready_queue, struct _process **done_queue, int quantum)
{
    int runtime = 0;
    int first_proc_time = 0;
    int next_run_time = 0;
    int time_left;
    int isempty = 0;
    struct _process temp_proc;
    struct _process *iter;
    struct _process *temp_ptr;
    struct _process *temp_queue = NULL;
    struct _data temp_time_data;
    
    // if there is a process queue, send first process to the ready queue, set runtime
    // to start time, otherwise exit
    printf("Begin Scheduler\n");
    if(*process_queue)
    {
        temp_proc = remove_proc_node_from_front(&*process_queue);
        add_proc_node(&*ready_queue,temp_proc);
        runtime = first_proc_time = temp_proc.arrival;
        if((*process_queue)->next)
            next_run_time = (*process_queue)->next->arrival;
        else
            next_run_time = INT_MAX;
    }
    else
    {
        return runtime;
    }    
    printf("Run time: %d\n",runtime);
    // processws waiting?
    while( *process_queue || *ready_queue || temp_queue)
    {
        while(*process_queue)
        {

            if(runtime >= (*process_queue)->arrival)
            {
                temp_proc = remove_proc_node_from_front(&*process_queue);
                add_proc_node(&*ready_queue,temp_proc);
                printf("Adding: %d\n", temp_proc.pid);
            }
            else
            {
                next_run_time = (*process_queue)->arrival;
                break;
            }
        }
        
        while(temp_queue)
        {
            temp_proc = remove_proc_node_from_front(&temp_queue);
            add_proc_node(&*ready_queue,temp_proc);
        }
            
        if(!*process_queue)
            next_run_time = INT_MAX;
                     
        printf("Next run time: %d\n",next_run_time);             
                     
        isempty = 0;
                    
        iter = *ready_queue;;
        while(iter)
        {
            time_left = iter->burst - proc_time_done(iter);
            if(time_left > quantum)
            {
                printf("Running process: %d\n",iter->pid);
                //add info to time done
                temp_time_data.start_time = runtime - first_proc_time;
                temp_time_data.run_time = quantum;
                add_time_node(&iter->time_data,temp_time_data);
                //move runtime on by quantum
                runtime += quantum;
                temp_ptr = iter;
                iter = iter->next;
                temp_proc = remove_proc_node(&*ready_queue, temp_ptr);
                add_proc_node(&temp_queue,temp_proc);
            }
            else
            {
                printf("Running process: %d\n",iter->pid);
                //add info to time done
                //move runtime forward by time_left
                temp_time_data.start_time = runtime - first_proc_time;
                temp_time_data.run_time = time_left;
                add_time_node(&iter->time_data,temp_time_data);
                temp_ptr = iter;
                iter = iter->next; // point to next node
                //move process to done queue
                temp_proc = remove_proc_node(&*ready_queue, temp_ptr);
                add_proc_node(&*done_queue,temp_proc);
                runtime += time_left;
            }
            isempty = 1;
            
            if(runtime >= next_run_time)
            {
                printf("runtime >= next_run_time\n");
                break;    
            }
            printf("Run Time: %d\n",runtime);
            
        }
        
        if(!isempty)
        {
            runtime++;
            printf("-------------------------\n");
        }
        
        printf("Queue lengths: %d %d %d\n", queue_length(*process_queue),queue_length(*ready_queue),queue_length(*done_queue));     
    }
    return runtime;// -first_proc_time;
}
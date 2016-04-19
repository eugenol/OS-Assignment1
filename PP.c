#include "SJF.h"
#include "queue.h"
#include <stdio.h>
#include <limits.h>

int PP(struct _process **process_queue, struct _process **ready_queue, struct _process **done_queue, int quantum)
{
    /* Ideas:
    *   Load from process queue into ready queue when the time is right.
    *   sort ready queue according to time left
    *   run ready queue until new process arrives, repeat
    */
    
    int runtime = 0;
    int first_proc_time = 0;
    int next_run_time = 0;
    int time_left = 0;
    int isempty = 0;
    struct _process temp_proc = {{0},0,0,0,0,NULL,NULL,NULL};
    struct _process *iter;
    struct _process *temp_ptr;
    struct _process *temp_queue = NULL;
    struct _data temp_time_data = {0, 0, NULL};
    struct _data *last_time = NULL;
    
    // if there is a process queue, send first process to the ready queue, set runtime
    // to start time, otherwise exit
    // this gets the ball rolling
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
    
    // processws waiting in any of the queues?
    // loop to consume process
    while( *process_queue || *ready_queue || temp_queue)
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
                next_run_time = (*process_queue)->arrival;
                break;
            }
        }
        
        // re add processes
        while(temp_queue)
        {
            temp_proc = remove_proc_node_from_front(&temp_queue);
            add_proc_node(&*ready_queue,temp_proc);
        }
        
        // fix for empty queue    
        if(!*process_queue)
            next_run_time = INT_MAX;
            
        //fix for long wait between processes                 
        isempty = 0;
        
        sort_queue(*ready_queue, sort_by_priority);
        
        //start at head of queue            
        iter = *ready_queue;
        while(iter)
        {
            // check time left for process
            time_left = iter->burst - proc_time_done(iter);
            
            // check if this process can complete before next one arrives
            if(runtime + time_left > next_run_time)
            {
                last_time = get_last_time_node(iter);
                if(last_time && last_time->start_time+last_time->run_time + first_proc_time == runtime)
                {
                    last_time->run_time =  last_time->run_time + next_run_time-runtime;
                }
                else
                {
                    //add info to time done
                    temp_time_data.start_time = runtime - first_proc_time;
                    temp_time_data.run_time = next_run_time-runtime;
                    add_time_node(&iter->time_data,temp_time_data);
                }
                //move runtime on by quantum
                runtime = next_run_time;
                temp_ptr = iter;
                iter = iter->next;
                //move process to temp queue to re add later
                temp_proc = remove_proc_node(&*ready_queue, temp_ptr);
                add_proc_node(&temp_queue,temp_proc);
            }
            else
            {
                //add info to time done
                last_time = get_last_time_node(iter);
                if(last_time && last_time->start_time+last_time->run_time + first_proc_time == runtime)
                {
                    last_time->run_time =  last_time->run_time + time_left;
                }
                else
                {
                    temp_time_data.start_time = runtime - first_proc_time;
                    temp_time_data.run_time = time_left;
                    add_time_node(&iter->time_data,temp_time_data);
                }
                temp_ptr = iter;
                iter = iter->next; // point to next node
                //move process to done queue
                temp_proc = remove_proc_node(&*ready_queue, temp_ptr);
                add_proc_node(&*done_queue,temp_proc);
                //move runtime forward by time_left
                runtime += time_left;
            }
            isempty = 1;
            
            if(runtime >= next_run_time)
            {
                // break to load other processes
                break;    
            }
            
        }
        
        if(!isempty)
        {
            //advance time in case there is long delay between processes
            runtime++;
        }       
    }
    return runtime;// -first_proc_time;
}
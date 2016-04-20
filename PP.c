#include "RR.h"
#include "queue.h"
#include <limits.h>
#include <stdio.h>

int PP(struct _process **process_queue, struct _process **ready_queue, struct _process **done_queue, int quantum)
{
    int runtime = 0;
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
        runtime = temp_proc.arrival;
        
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
                
        sort_queue(*ready_queue,sort_by_priority);
                   
        //fix for long wait between processes                 
        isempty = 0;
        
        //start at head of queue            
        iter = *ready_queue;
        while(iter)
        {
            int frac_run_time = 0;
            int set_break = 0;
            // check if process is done.
            isempty = 1;
            
            time_left = iter->burst - proc_time_done(iter);
            if(time_left > quantum)
            {
                
                if(runtime + quantum > next_run_time)
                {
                    frac_run_time = next_run_time-runtime;
                    set_break = 1;
                }
                else
                {
                    frac_run_time = quantum;
                    set_break = 0;
                }
                
                last_time = get_last_time_node(iter);
                if(last_time && last_time->start_time+last_time->run_time == runtime)
                {
                    last_time->run_time =  last_time->run_time + frac_run_time;
                }
                else
                {
                    //add info to time done
                    temp_time_data.start_time = runtime;
                    temp_time_data.run_time = frac_run_time;
                    add_time_node(&iter->time_data,temp_time_data);
                }
                if(iter->priority>0)
                    iter->priority = iter->priority - 1;
                //move runtime on by quantum
                runtime += frac_run_time;
                
                if(set_break)
                    break;
                    
                sort_queue(*ready_queue,sort_by_priority);
                iter =  *ready_queue;
                  
            }
            else
            {
                int frac_run_time = 0;
                int set_break = 0;
                
                if(runtime + time_left > next_run_time)
                {
                    frac_run_time = next_run_time-runtime;
                    set_break = 1;
                }
                else
                {
                    frac_run_time = time_left;
                    set_break = 0;
                }
                
                //add info to time done
                last_time = get_last_time_node(iter);
                if(last_time && last_time->start_time+last_time->run_time == runtime)
                {
                    last_time->run_time =  last_time->run_time + frac_run_time;
                }
                else
                {
                    //add info to time done
                    temp_time_data.start_time = runtime;
                    temp_time_data.run_time = frac_run_time;
                    add_time_node(&iter->time_data,temp_time_data);
                }
                if(iter->priority>0)
                    iter->priority = iter->priority - 1;
                    
                //move runtime forward by time_left
                runtime += frac_run_time;
                
                if(set_break)
                    break;
                    
                temp_ptr = iter;
                iter = iter->next; // point to next node
                //move process to done queue
                temp_proc = remove_proc_node(&*ready_queue, temp_ptr);
                add_proc_node(&*done_queue,temp_proc);

            }
            
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
    return runtime;
}
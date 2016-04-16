#include "RR.h"
#include "queue.h"

int RR(struct _process **process_queue, struct _process **ready_queue, struct _process **done_queue, int quantum)
{
    /*int runtime = 0;
    int next_proc_time = 0;
    struct _process temp;
    
    // if there is a process queue, send first process to the ready queue, set runtime
    // to start time, otherwise exit
    if(*process_queue)
    {
        temp = remove_proc_node_from_front(&*process_queue)
        add_proc_node(&*ready_queue,temp)
        runtime = temp->arrival;
    }
    else
    {
        return runtime;
    }    
    
    // processws waiting?
    while(*process_queue||*ready_queue)
    {
        if(*process_queue->next)
        {
            next_proc_time = *process_queue->next->arrival_time;
        }
        else
        {
            next_proc_time = INT_MAX;
        }
        
        
    }*/
    return 0;
}
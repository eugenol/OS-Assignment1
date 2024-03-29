#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "queue.h"

void add_proc_node(struct _process **head,struct _process data)
{
    struct _process *temp; //new node 
    struct _process *iter = *head;    
    
    temp = malloc(sizeof(struct _process));
	
    strcpy(temp->ID, data.ID);
    temp->pid = data.pid;
	temp->arrival = data.arrival;
	temp->burst = data.burst;
	temp->priority = data.priority;
    temp->time_data = data.time_data;
    temp->next = NULL;
    temp->next = NULL;
    
    if(!iter)
    {
        //temp->pid = 0;
        *head = temp;
    }
    else
    {
        while(iter->next)
            iter = iter->next;
        
        //set correct valuest in temp
        //temp->pid = iter->pid + 1;
        temp->prev = iter;               
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
        //printf("%s %d ",iter->ID, iter->priority);
        printf("%s ",iter->ID);
        iter2 = iter->time_data;
        while(iter2)
        {
            printf("(%d,%d) ",iter2->start_time, iter2->run_time);\
            iter2 = iter2->next;
            if(!iter2)
                printf("\n");
        }
        iter = iter->next;
    }    
}

void print_proc_nodes_to_file(struct _process *head, FILE *fptr)
{
    struct _process *iter = head;
    struct _data *iter2;
       
    while(iter)
    {
        //printf("%s %d ",iter->ID, iter->arrival);
        fprintf(fptr,"%s ",iter->ID);
        iter2 = iter->time_data;
        while(iter2)
        {
            fprintf(fptr,"(%d,%d) ",iter2->start_time, iter2->run_time);
            iter2 = iter2->next;
            if(!iter2)
                fprintf(fptr,"\n");
        }
        iter = iter->next;
    }    
}

int queue_length(struct _process *head)
{
    struct _process *iter = head;
    int count = 0;
    
    while(iter)
    {
        count++;
        iter = iter->next;
    }
    
    return count;    
}

void sort_queue(struct _process *head, int (*sort_function)(struct _process *item1, struct _process *item2))
{
    struct _process *iter1 = head;
    struct _process *iter2 = NULL;
    struct _process swap = {{0},0,0,0,0,NULL,NULL,NULL};
    
    int swapped;
    
    if(!head)
        return;
    
    do
    {
        swapped = 0;
        iter1 = head;
        
        while(iter1->next != iter2)
        {
            //if(iter1->arrival > iter1->next->arrival)
            if(sort_function(iter1,iter1->next))
            {
                //copy iter 1 values to swap
                strcpy(swap.ID,iter1->ID);
                swap.arrival = iter1->arrival;
                swap.burst = iter1->burst;
                swap.priority = iter1->priority;
                swap.time_data = iter1->time_data;

                //swap iter1 and iter 2
                strcpy(iter1->ID,iter1->next->ID);
                iter1->arrival = iter1->next->arrival;
                iter1->burst = iter1->next->burst;
                iter1->priority = iter1->next->priority;
                iter1->time_data = iter1->next->time_data;

                //copy swap into iter 2
                strcpy(iter1->next->ID,swap.ID);
                iter1->next->arrival = swap.arrival;
                iter1->next->burst = swap.burst;
                iter1->next->priority = swap.priority;
                iter1->next->time_data = swap.time_data;
                
                //swap has occured
                swapped =1;
            }
            iter1=iter1->next;
        }
        iter2 = iter1;
    } while (swapped);  
}

int sort_by_arrival(struct _process *item1, struct _process *item2)
{
    if(item1->arrival > item2->arrival)
        return 1;
    else
        return 0;
}

int sort_by_time_left(struct _process *item1, struct _process *item2)
{
    int time_left_item1 = 0;
    int time_left_item2 = 0;
    
    time_left_item1 = item1->burst - proc_time_done(item1);
    time_left_item2 = item2->burst - proc_time_done(item2);
    
    if(time_left_item1 > time_left_item2)
        return 1;
    else
        return 0;
}
// fix this
int sort_by_priority(struct _process *item1, struct _process *item2)
{
    int last_run_time_item1 = 0;
    int last_run_time_item2 = 0;
    struct _data *iter_item1 = NULL;
    struct _data *iter_item2 = NULL;
    
    if(item1->priority < item2->priority)
        return 1;
    else if (item1->priority == item2->priority)
    {
        iter_item1 = item1->time_data;
        iter_item2 = item2->time_data;
        
        if(iter_item1)
        {
            while(iter_item1->next)
                iter_item1 = iter_item1->next;
            
            last_run_time_item1 = iter_item1->start_time + iter_item1->run_time;
             
        }
        else
        {
            last_run_time_item1 = INT_MIN;
        }
        
        if(iter_item2)
        {
            while(iter_item2->next)
                iter_item2 = iter_item2->next;
            
            last_run_time_item2 = iter_item2->start_time + iter_item2->run_time;
             
        }
        else
        {
            last_run_time_item2 = INT_MIN;
        }
        
        //if equal priorities, run the one that hasnt run the longest
        if(last_run_time_item1 < last_run_time_item2)
            return 0;
        else if (last_run_time_item1==last_run_time_item2)
        {
            if(item1->arrival < item2->arrival)
                return 0;
            else
                return 1;
        }
        else
            return 1;
    }
    else
        return 0;
}

int sort_by_name(struct _process *item1, struct _process *item2)
{  
    long int val1, val2;
    char *str1 = item1->ID;
    char *str2 = item2->ID;
    
    val1 = strtol(str1+7,NULL,10);
    val2 = strtol(str2+7,NULL,10);
    
    return (val1 > val2);
    /*
    if(strcmp(item1->ID,item2->ID) > 0)
        return 1;
    else
        return 0;
   */
}

void assign_pid(struct _process *head)
{
    struct _process *iter = head;
        
    if(!iter) //handle empty queue
        return;
    
    iter->pid = 0; //set pid of first entry
    iter = iter->next;
    
    while(iter) //assign in order
    {
        iter->pid = iter->prev->pid+1;
        iter=iter->next;
    }      
}

struct _process remove_proc_node_from_front(struct _process **head)
{
    struct _process temp = {{0},0,0,0,0,NULL,NULL,NULL};
    struct _process *iter = *head;
    
    if(iter)
    {
        if(iter->next)
        {
            iter->next->prev = NULL;
            *head = iter->next;
        }
        else
        {
            *head = NULL;
        }
        
        strcpy(temp.ID,iter->ID);
        temp.pid = iter->pid;
        temp.arrival = iter->arrival;
        temp.burst = iter->burst;
        temp.priority = iter->priority;
        temp.time_data = iter->time_data;
        
        free(iter);
        iter = NULL;
    }
    return temp;
}

struct _process remove_proc_node(struct _process **head, struct _process *node)
{
    struct _process temp = {{0},0,0,0,0,NULL,NULL,NULL};
    struct _process *iter = node;
    
    if(iter)
    {
        if(iter == *head)
        {
            temp = remove_proc_node_from_front(&*head);
        }
        else
        {
            if(iter->next)
            {
                iter->next->prev = iter->prev;
            }
            
            if(iter->prev)
            {
                iter->prev->next = iter->next;
            }
           
            strcpy(temp.ID,iter->ID);
            temp.pid = iter->pid;
            temp.arrival = iter->arrival;
            temp.burst = iter->burst;
            temp.priority = iter->priority;
            temp.time_data = iter->time_data;
            
            free(iter);
            iter = NULL;
        }
    }
        
    return temp;
}

int proc_time_done(struct _process *proc)
{
    int total_proc_time = 0;
    struct _data *iter = proc->time_data;
    
    if(!iter)
        return total_proc_time;
    
    while(iter)   
    {
        total_proc_time+=iter->run_time;
        iter = iter->next;
    }
    
    return total_proc_time;
}

struct _data *get_last_time_node(struct _process *proc)
{
    struct _data *iter = proc->time_data;
    
    if(!iter)
        return NULL;
    
    while(iter->next)   
    {
        iter = iter->next;
    }
    
    return iter;
}

struct _process *new_node_address(struct _process *head)
{
    struct _process *iter = head;    
    
    if(!iter)
    {
        return NULL;
    }
    else
    {
        while(iter->next)
            iter = iter->next;
        
        return iter;
    }
}

void free_queue(struct _process **head)
{
    struct _process *iter = *head;
    struct _data *iter2 = NULL;
    struct _process *temp_proc = NULL;
    struct _data *temp_data = NULL;
    
    while(iter)
    {
        iter2 = iter->time_data;
        while(iter2)
        {
            temp_data = iter2;
            iter2 = iter2->next;
            
            free(temp_data);
            temp_data = NULL;
        }
        
        temp_proc = iter;
        
        if(iter->next) // if last node, there will be no previous node.
            iter->next->prev = NULL;
       
        *head = iter->next;
        iter = iter->next;
        
        free(temp_proc);
        temp_proc = NULL;
    }
}

void turnaround_wait_time(struct _process *queue, float *avg_turnaround_time, float *avg_waiting_time)
{
    //struct to keep waiting time and turnaround time for each process
    struct _tat{
        int turnaround_time;
        int waiting_time;
    };
    
    struct _tat *arr= NULL;
    struct _data *last_time = NULL;
    struct _process *iter = NULL;
    struct _data *iter2 = NULL;
    
    int num_proc = 0;
    int index = 0;
    int wait_time = 0;
    
    int avg_wait_time = 0;
    int avg_turn_time = 0;
    
    num_proc = queue_length(queue); //find number of processes
        
    arr = malloc(num_proc*sizeof(struct _tat)); // dynamically create array
    
    iter = queue; //start at beginning of queue
    
    while(iter)
    {
        last_time = get_last_time_node(iter);
        arr[index].turnaround_time = last_time->start_time + last_time->run_time - iter->arrival;

        wait_time = 0;

        iter2 = iter->time_data;
        while(iter2->next)
        {
            wait_time -= iter2->run_time;
            iter2=iter2->next;
        }
        wait_time += (iter2->start_time - iter->arrival);
        arr[index].waiting_time = wait_time;
        
        //printf("%s %d %d\n",iter->ID, arr[index].waiting_time, arr[index].turnaround_time);
        iter = iter->next;
        index++;
    }
    
    for(int i = 0; i < num_proc; i++)
    {
        avg_wait_time += arr[i].waiting_time;
        avg_turn_time += arr[i].turnaround_time;
    }
    
    *avg_waiting_time = ((float)avg_wait_time)/num_proc;
    *avg_turnaround_time = ((float)avg_turn_time)/num_proc;
    
    free(arr);
    arr = NULL;
    
}
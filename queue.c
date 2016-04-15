#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    temp->time_data = NULL;
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
        printf("%s %d\n",iter->ID, iter->pid);
        iter2 = iter->time_data;
        while(iter2)
        {
            printf("(%d %d)",iter2->start_time, iter2->run_time);\
            iter2 = iter2->next;
            if(!iter2)
                printf("\n");
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

void sort_queue(struct _process *head)
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
            if(iter1->arrival > iter1->next->arrival)
            {
                //copy iter 1 values to swap
                strcpy(swap.ID,iter1->ID);
                swap.arrival = iter1->arrival;
                swap.burst = iter1->burst;
                swap.priority = iter1->priority;

                //swap iter1 and iter 2
                strcpy(iter1->ID,iter1->next->ID);
                iter1->arrival = iter1->next->arrival;
                iter1->burst = iter1->next->burst;
                iter1->priority = iter1->next->priority;

                //copy swap into iter 2
                strcpy(iter1->next->ID,swap.ID);
                iter1->next->arrival = swap.arrival;
                iter1->next->burst = swap.burst;
                iter1->next->priority = swap.priority;
                
                //swap has occured
                swapped =1;
            }
            iter1=iter1->next;
        }
        iter2 = iter1;
    } while (swapped);  
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
#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>

struct _data {
    int start_time;
    int run_time;
    struct _data *next;  
};

struct _process {
	char ID[11];
    int pid;
	int arrival;
	int burst;
	int priority;
    struct _data *time_data;
    struct _process *next;
    struct _process *prev;
};

void add_proc_node(struct _process **head,struct _process data);
struct _process remove_proc_node_from_front(struct _process **head);
struct _process remove_proc_node(struct _process **head, struct _process *node);
void free_queue(struct _process **head);

//Time node stuff
void add_time_node(struct _data **head, struct _data data);
int proc_time_done(struct _process *proc);
struct _data *get_last_time_node(struct _process *proc);

void print_proc_nodes(struct _process *head);
void print_proc_nodes_to_file(struct _process *head, FILE *fptr);

int queue_length(struct _process *head);
struct _process *new_node_address(struct _process *head);

void assign_pid(struct _process *head);

// sort functions
//void sort_queue(struct _process *head);
void sort_queue(struct _process *head, int (*sort_function)(struct _process *item1, struct _process *item2));
// 
int sort_by_arrival(struct _process *item1, struct _process *item2);
int sort_by_time_left(struct _process *item1, struct _process *item2);
int sort_by_priority(struct _process *item1, struct _process *item2);
int sort_by_name(struct _process *item1, struct _process *item2);

void turnaround_wait_time(struct _process *queue, float *avg_turnaround_time, float *avg_waiting_time);

#endif /*QUEUE_H*/
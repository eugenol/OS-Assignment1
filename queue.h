#ifndef QUEUE_H
#define QUEUE_H

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
void print_proc_nodes(struct _process *head);
void sort_queue(struct _process *head);
int queue_length(struct _process *head);
struct _process remove_proc_node_from_front(struct _process **head);

void add_time_node(struct _data **head,struct _data data);

void assign_pid(struct _process *head);


#endif /*QUEUE_H*/
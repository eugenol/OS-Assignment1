#ifndef FCFS_H
#define FCFS_H

#include "queue.h"

int FCFS(struct _process **process_queue, struct _process **ready_queue, struct _process **done_queue, int quantum);

#endif /*FCFS_H*/
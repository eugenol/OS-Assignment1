#ifndef SJF_H
#define SJF_H

#include "queue.h"

int SJF(struct _process **process_queue, struct _process **ready_queue, struct _process **done_queue, int quantum);

#endif /*SJF_H*/
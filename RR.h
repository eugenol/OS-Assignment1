#ifndef RR_H
#define RR_H

#include "queue.h"

int RR(struct _process **process_queue, struct _process **ready_queue, struct _process **done_queue, int quantum);

#endif /*RR_H*/
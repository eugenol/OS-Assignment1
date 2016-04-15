#ifndef PP_H
#define PP_H

#include "queue.h"

int PP(struct _process **process_queue, struct _process **ready_queue, struct _process **done_queue, int quantum);

#endif /*PP_H*/
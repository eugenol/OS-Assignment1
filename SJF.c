#include "SJF.h"
#include "queue.h"

int SJF(struct _process **process_queue, struct _process **ready_queue, struct _process **done_queue, int quantum)
{
    /* Ideas:
    *   Load from process queue into ready queue when the time is right.
    *   sort ready queue according to time left
    *   run ready queue until new process arrives, repeat
    */
    
    return 0;
}
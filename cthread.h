
#ifndef LIBCTHREAD_CTHREAD_H
#define LIBCTHREAD_CTHREAD_H

#include "arch.h"

#ifdef __cplusplus
extern "C" {
#endif

// Initialize cthreads
// Call before anything below
void cthread_init(void);

typedef int cthread_t;

// Make a new thread, filling `id` with the thread ID
// Also immediately runs the thread
// Returns 0 on success, or -1 on error and sets `errno`
int cthread_create(cthread_t *id, void (*func)(void *), void *arg);

// Yields control
// If called from main thread, this will yield to a libcthread-managed thread
void cthread_yield(void);

// Terminates the calling thread
// Undefined if called from outside of a libcthread-managed thread (e.g. main thread)
void cthread_exit(void);

#ifdef __cplusplus
}
#endif

#endif // LIBCTHREAD_CTHREAD_H

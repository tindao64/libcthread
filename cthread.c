
#include "cthread.h"
#include "arch.h"
#include <setjmp.h>
#include <stdlib.h>
#include <stddef.h>
#include <errno.h>
#include <assert.h>

struct cthread {
    jmp_buf context;
    void *stack_bottom;
    cthread_t id;
};

struct cthread_slot {
    struct cthread thread;
    int in_use;
};

// cthread global state

static int cthread_initialized = 0;
size_t cthread_max_threads;
struct cthread_slot *cthread_slots;

extern size_t CTHREAD_MAX_THREADS;
extern size_t CTHREAD_STACK_SIZE;

__attribute__((weak))
size_t CTHREAD_MAX_THREADS = 32;
__attribute__((weak))
size_t CTHREAD_STACK_SIZE = 32768;

// (size_t)-1 on error
static size_t get_free_slot(void) {
    for (size_t i = 0; i < cthread_max_threads; ++i) {
        if (!cthread_slots[i].in_use) {
            return i;
        }
    }
    return (size_t)-1;
}

void cthread_init(void) {
    if (cthread_initialized) {
        assert(!"cthread_init called multiple times");
        return;
    }

    // save value of max threads, in case it's overridden and changed
    cthread_max_threads = CTHREAD_MAX_THREADS;

    cthread_slots = cthread_malloc(cthread_max_threads * sizeof(struct cthread_slot));
    if (!cthread_slots) {
        // can't do much, but at least crash early
        assert(!"Failed to allocate cthread_slots");
        abort();
    }

    cthread_initialized = 1;
}

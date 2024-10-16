#include <thread.h>
#include <thread-sync.h>

sem_t fill, empty;

struct condvar {
    int nwait;
    sem_t sleep;
    mutex_t lock;
} cv;

void init(struct condvar *cv) {
    cv->nwait = 0;
    mutex_init(&cv->lock);
    SEM_INIT(&cv->sleep, 0);
}

void wait(struct condvar *cv, mutex_t *mutex) {
    // At this point, we hold "mutex".
    mutex_lock(&cv->lock);
    cv->nwait++;
    mutex_unlock(&cv->lock);

    // We have marked this thread as "waiting".
    // Now we release the lock and go to sleep.
    //
    // <-- broadcast() may happen here.
    //     Suppose T1 calls broadcast() and proceeds
    //     with execution. T1 may call wait() and
    //     erroneously being signaled.
    mutex_unlock(mutex);

    // <-- also, here.
    P(&cv->sleep);

    // Re-acquire the mutex.
    mutex_lock(mutex);
}

void broadcast(struct condvar *cv) {
    mutex_lock(&cv->lock);

    // Wake up all waiting threads.
    for (int i = 0; i < cv->nwait; i++) {
        V(&cv->sleep);
    }
    cv->nwait = 0;
    mutex_unlock(&cv->lock);
}

int n = 1, depth = 0;
mutex_t lk = MUTEX_INIT();
struct condvar cv;
 
#define CAN_PRODUCE (depth < n)
#define CAN_CONSUME (depth > 0)

void T_produce() {
    while (1) {
        mutex_lock(&lk);

        while (!CAN_PRODUCE) {
            wait(&cv, &lk);
        }

        printf("(");
        fflush(stdout);
        depth++;

        mutex_unlock(&lk);

        // Yes. We can broadcast without
        // holding the mutex.
        broadcast(&cv);
        usleep(10);
    }
}

void T_consume() {
    init(&cv);

    while (1) {
        mutex_lock(&lk);

        while (!CAN_CONSUME) {
            wait(&cv, &lk);
        }

        printf(")");
        fflush(stdout);
        depth--;

        mutex_unlock(&lk);

        broadcast(&cv);
        usleep(10);
    }
}

int main() {
    for (int i = 0; i < 1; i++) {
        create(T_consume);
        create(T_produce);
    }
}

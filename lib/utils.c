#include "utils.h"
#include "log.h"

/**
 * 断言是相同的线程
 * @param eventLoop
 */
void assertInSameThread(struct event_loop *eventLoop) {
    if (eventLoop->owner_thread_id != pthread_self()) {
        LOG_ERR("not in the same thread");
        exit(-1);
    }
}

/**
 * 判断是否相同的线程
 * @param eventLoop
 * @return 1：same thread, 0：not the same thread
 */
int isInSameThread(struct event_loop *eventLoop){
    return eventLoop->owner_thread_id == pthread_self();
}
#ifndef EVENT_LOOP_H
#define EVENT_LOOP_H

#include <pthread.h>
#include "channel.h"
#include "event_dispatcher.h"
#include "common.h"

extern const struct event_dispatcher poll_dispatcher;
extern const struct event_dispatcher epoll_dispatcher;

/**
 * 存放channel的链表
 */
struct channel_element {
    int type; //1: add  2: delete
    struct channel *channel;
    struct channel_element *next;
};

/**
 * event loop对象
 */
struct event_loop {
    int quit;
    const struct event_dispatcher *eventDispatcher; // 事件分发对象,可以指定poll或epoll

    void *event_dispatcher_data;          // 对应的event_dispatcher的数据
    struct channel_map *channelMap;

    int is_handle_pending;
    struct channel_element *pending_head; // 记录链表头,链表用于存放待处理的channel事件
    struct channel_element *pending_tail; // 记录链表尾

    pthread_t owner_thread_id;            // 记录拥有此event loop对象的线程id
    pthread_mutex_t mutex;                // 互斥锁,用于配合条件变量使用
    pthread_cond_t cond;                  // 条件变量
    int socketPair[2];                    // 本地套接字,父线程用来通知子线程有新的事件需要处理。本项目中sockPair[0]用于写入,sockPair[1]用于读取。
    char *thread_name;                    // 记录线程的名字
};

struct event_loop *event_loop_init();

struct event_loop *event_loop_init_with_name(char *thread_name);

int event_loop_run(struct event_loop *eventLoop);

void event_loop_wakeup(struct event_loop *eventLoop);

int event_loop_add_channel_event(struct event_loop *eventLoop, int fd, struct channel *channel1);

int event_loop_remove_channel_event(struct event_loop *eventLoop, int fd, struct channel *channel1);

int event_loop_update_channel_event(struct event_loop *eventLoop, int fd, struct channel *channel1);

int event_loop_handle_pending_add(struct event_loop *eventLoop, int fd, struct channel *channel);

int event_loop_handle_pending_remove(struct event_loop *eventLoop, int fd, struct channel *channel);

int event_loop_handle_pending_update(struct event_loop *eventLoop, int fd, struct channel *channel);

// dispather派发完事件之后，调用该方法通知event_loop执行对应事件的相关callback方法
// res: EVENT_READ | EVENT_READ等
int channel_event_activate(struct event_loop *eventLoop, int fd, int res);

#endif
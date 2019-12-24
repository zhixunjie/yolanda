#ifndef CHANNEL_H
#define CHANNEL_H

#include "common.h"
#include "event_loop.h"
#include "buffer.h"

#define EVENT_TIMEOUT    0x01
/** Wait for a socket or FD to become readable */
#define EVENT_READ        0x02
/** Wait for a socket or FD to become writeable */
#define EVENT_WRITE    0x04
/** Wait for a POSIX signal to be raised*/
#define EVENT_SIGNAL    0x08


typedef int (*event_read_callback)(void *data);

typedef int (*event_write_callback)(void *data);

struct channel {
    int fd;                                     // 监控的fd
    int events;                                 // 监控的事件类型

    event_read_callback eventReadCallback;      // 发生读事件的回调函数
    event_write_callback eventWriteCallback;    // 发生写事件的回调函数
    void *data;                                 // 调用回调函数的传参, 可能是event_loop，也可能是tcp_server或者tcp_connection
};


struct channel *
channel_new(int fd, int events, event_read_callback eventReadCallback, event_write_callback eventWriteCallback,
            void *data);

int channel_write_event_is_enabled(struct channel *channel);

int channel_write_event_enable(struct channel *channel);

int channel_write_event_disable(struct channel *channel);


#endif
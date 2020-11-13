#ifndef CHANNEL_MAP_H
#define CHANNEL_MAP_H


#include "channel.h"

/**
 * channel映射表
 */
struct channel_map {
    // entries是一个数组。
    // - key等于某个fd
    // - value等于该fd对应的channel对象
    void **entries;

    // entries数组里面的可用数目
    int nentries;
};


int map_make_space(struct channel_map *map, int slot, int msize);

void map_init(struct channel_map *map);

void map_clear(struct channel_map *map);

#endif
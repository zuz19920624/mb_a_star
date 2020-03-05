#pragma once

#define WIDTH_OF_MAP 9
#define HEIGHT_OF_MAP 10
#define WIDTH_OF_BLOCK 3
#define HEIGHT_OF_BLOCK 3
#define NUM_OF_BLOCK_X ( (WIDTH_OF_MAP + WIDTH_OF_BLOCK) / WIDTH_OF_BLOCK)
#define NUM_OF_BLOCK_Y ( (HEIGHT_OF_MAP + HEIGHT_OF_BLOCK) / HEIGHT_OF_BLOCK)
#define MXV     0xffffffff   //maxium
#define NUM_OF_BLOCK_CACHE 4

class nodeClass
{
public:
    unsigned int parent_i;
    unsigned int parent_j;
    int f;
    int g;
    int inCloseList; //1 is in the Closelist, 0 && f != MXV is in the OpenList
    int isReachable; //1 is reachable, 0 is blocked
};

class blockClass
{
public:
    int heap_value;
    nodeClass node[WIDTH_OF_BLOCK * HEIGHT_OF_BLOCK];
    nodeClass edge_node[WIDTH_OF_BLOCK * 2 + HEIGHT_OF_BLOCK * 2];
};

class nodeOpenListNode
{
    int node_i;
    int node_j;
    int f;
};

class nodeOpenList
{
    nodeOpenListNode n[WIDTH_OF_BLOCK * HEIGHT_OF_BLOCK];
}; //on board

class blockOpenListNode
{
    int block_i;
    int block_j;
    int heap_value;
};

class blockOpenList
{
    blockOpenListNode n[NUM_OF_BLOCK_X * NUM_OF_BLOCK_Y];
}; //in memory

class blockOpenListCache
{
    blockOpenListNode n_in[2]; //ping pong buffer
    blockOpenListNode n_out[4];
}; // in cache

class blockMemClass
{
public:
    blockClass block[NUM_OF_BLOCK_X * NUM_OF_BLOCK_Y];
}; // in mem

class blockCacheDataClass
{
public:
    blockClass block;
    int block_i;
    int block_j; //used to record the id of stored blocks id
    int dirty; //indicating that current tag is dirty
    int init; //current tag contains things
};

class blockClassCache
{
public:
    blockCacheDataClass bc[NUM_OF_BLOCK_CACHE];
};
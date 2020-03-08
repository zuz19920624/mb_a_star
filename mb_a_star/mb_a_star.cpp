// mb_a_star.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "data_struct.h"

extern blockMemClass* blockMem;
extern blockOpenList* blockList;
extern blockClassCache* blockCache;
extern blockOpenListCache* BOCache;
nodeClass blockedNode;
extern nodeOpenList* no;

//initialize the block's structure and memory
void initBlockMem(int grid[][HEIGHT_OF_MAP])
{
    for(int i = 0; i < NUM_OF_BLOCK_X; i++)
        for (int j = 0; j < NUM_OF_BLOCK_Y; j++)
        {
            //initialize each block
            blockMem->block[j * NUM_OF_BLOCK_X + i].heap_value = MXV;
            //initialize each node
            for(int node_i = 0; node_i < WIDTH_OF_BLOCK; node_i++)
                for (int node_j = 0; node_j < HEIGHT_OF_BLOCK; node_j++)
                {
                    blockMem->block[j * NUM_OF_BLOCK_X + i].node[node_j * WIDTH_OF_BLOCK + node_i].f = MXV;
                    blockMem->block[j * NUM_OF_BLOCK_X + i].node[node_j * WIDTH_OF_BLOCK + node_i].inCloseList = 0;
                    int grid_x = i * WIDTH_OF_BLOCK + node_i;
                    int grid_y = j * HEIGHT_OF_BLOCK + node_j;
                    blockMem->block[j * NUM_OF_BLOCK_X + i].node[node_j * WIDTH_OF_BLOCK + node_i].isReachable = grid[grid_x][grid_y];
                }
        }
}

//step1 : read the block containing start point
void copyNodeData(nodeClass* p1, nodeClass* p2)
{
    p1->parent_i = p2->parent_i;
    p1->parent_j = p2->parent_j;
    p1->f = p2->f;
    p1->g = p2->g;
    p1->inCloseList = p2->inCloseList;
    p1->isReachable = p2->isReachable;
}

void copyBlockData(int pos, int block_i, int block_j) //read the data from memory to cache
{
    blockCache->bc[pos].block_i = block_i;
    blockCache->bc[pos].block_j = block_j;
    blockCache->bc[pos].init = 1;
    blockCache->bc[pos].dirty = 0;
    blockCache->bc[pos].block.heap_value = blockMem->block[block_j * NUM_OF_BLOCK_X + block_i].heap_value;
    for (int i = 0; i < WIDTH_OF_BLOCK * HEIGHT_OF_BLOCK; i++)
    {
        //blockCache->bc[pos].block.node[i] = blockMem->block[block_j * NUM_OF_BLOCK_X + block_i].node[i];
        copyNodeData(&blockCache->bc[pos].block.node[i], &blockMem->block[block_j * NUM_OF_BLOCK_X + block_i].node[i]);
    }
    //copy node of edge 
    //         Top
    //          |
    // left --- n --- right
    //          |
    //        buttom
    
    if (block_i == 0) //left
    {
        for (int i = 0; i < HEIGHT_OF_BLOCK; i++)
        {
            //current block is blocked
            copyNodeData(&blockCache->bc[pos].block.edge_node[i], &blockedNode);
        }
    }
    else
    {
        for (int i = 0; i < HEIGHT_OF_BLOCK; i++)
        {
            copyNodeData(&blockCache->bc[pos].block.edge_node[i],
                &blockMem->block[block_j * NUM_OF_BLOCK_X + block_i - 1].node[WIDTH_OF_BLOCK * i + WIDTH_OF_BLOCK - 1]);
        }
    }

    if (block_i == NUM_OF_BLOCK_X - 1) //right
    {
        for (int i = 0; i < HEIGHT_OF_BLOCK; i++)
        {
            //current block is blocked
            copyNodeData(&blockCache->bc[pos].block.edge_node[HEIGHT_OF_BLOCK + i], &blockedNode);
        }
    }
    else
    {
        for (int i = 0; i < HEIGHT_OF_BLOCK; i++)
        {
            copyNodeData(&blockCache->bc[pos].block.edge_node[HEIGHT_OF_BLOCK + i],
                &blockMem->block[block_j * NUM_OF_BLOCK_X + block_i - 1].node[WIDTH_OF_BLOCK * i]);
        }
    }

    if (block_j == 0) //top
    {
        for (int i = 0; i < WIDTH_OF_BLOCK; i++)
        {
            //current block is blocked
            copyNodeData(&blockCache->bc[pos].block.edge_node[HEIGHT_OF_BLOCK * 2 + i], &blockedNode);
        }
    }
    else
    {
        for (int i = 0; i < WIDTH_OF_BLOCK; i++)
        {
            copyNodeData(&blockCache->bc[pos].block.edge_node[HEIGHT_OF_BLOCK * 2 + i],
                &blockMem->block[block_j * NUM_OF_BLOCK_X + block_i - 1].node[WIDTH_OF_BLOCK * (HEIGHT_OF_BLOCK - 1) + i]);
        }
    }

    if (block_j == NUM_OF_BLOCK_Y - 1) //buttom
    {
        for (int i = 0; i < WIDTH_OF_BLOCK; i++)
        {
            //current block is blocked
            copyNodeData(&blockCache->bc[pos].block.edge_node[HEIGHT_OF_BLOCK * 2 + WIDTH_OF_BLOCK + i], &blockedNode);
        }
    }
    else
    {
        for (int i = 0; i < WIDTH_OF_BLOCK; i++)
        {
            copyNodeData(&blockCache->bc[pos].block.edge_node[HEIGHT_OF_BLOCK * 2 + WIDTH_OF_BLOCK + i],
                &blockMem->block[block_j * NUM_OF_BLOCK_X + block_i - 1].node[i]);
        }
    }

}

void readBlockInfoIntoCache(int block_i, int block_j)
{
    int done = 0;
    for (int i = 0; i < NUM_OF_BLOCK_CACHE; i++)
    {
        if (blockCache->bc[i].init == 0) //finding the empty position
        {
            copyBlockData(i, block_i, block_j);
            done = 1;
        }
    }
    if (done == 0)// replace latest used
    {
        copyBlockData(blockCache->replacedPointer, block_i, block_j);
        blockCache->replacedPointer++;
    }
}

//insert node into openlist
void insertNode(nodeOpenListNode n)
{

}

//expand block
void expandBlock(int start_i, int start_j, int start_g, int start_f)
{
    //add start point into openlist
    
}

int main()
{
    blockMem = new blockMemClass();
    blockList = new blockOpenList();
    blockCache = new blockClassCache();
    blockedNode.f = MXV;
    blockedNode.g = MXV;
    blockedNode.isReachable = 0;
    blockedNode.inCloseList = 1;
    blockedNode.parent_i = 0;
    blockedNode.parent_j = 0;

    int startPointX = 8;
    int stopPointX = 0;
    int startPointY = 0;
    int stopPointY = 0;
    int startBlockX = (startPointX + WIDTH_OF_BLOCK - 1) / WIDTH_OF_BLOCK;
    int startBlockY = (startPointY + HEIGHT_OF_BLOCK - 1) / HEIGHT_OF_BLOCK;
    int stopBlockX = (stopPointX + WIDTH_OF_BLOCK - 1) / WIDTH_OF_BLOCK;
    int stopBlockY = (stopPointY + HEIGHT_OF_BLOCK - 1) / HEIGHT_OF_BLOCK;
    //step1 : read the block containing start point
    readBlockInfoIntoCache(startBlockX, startBlockY);
    //step2 : expand current block


    int grid[WIDTH_OF_MAP][HEIGHT_OF_MAP] =
    {
        { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
        { 1, 1, 1, 0, 1, 1, 1, 0, 1, 1 },
        { 1, 1, 1, 0, 1, 1, 0, 1, 0, 1 },
        { 0, 0, 1, 0, 1, 0, 0, 0, 0, 1 },
        { 1, 1, 1, 0, 1, 1, 1, 0, 1, 0 },
        { 1, 0, 1, 1, 1, 1, 0, 1, 0, 0 },
        { 1, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
        { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
        { 1, 1, 1, 0, 0, 0, 1, 0, 0, 1 }
    };
    std::cout << "Hello World!\n";
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件

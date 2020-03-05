// mb_a_star.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "data_struct.h"

extern blockMemClass* blockMem;
extern blockOpenList* blockList;
extern blockClassCache* blockCache;
extern blockOpenListCache* BOCache;

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
void readBlockInfoIntoCache(int block_i, int block_j)
{

}

int main()
{
    blockMem = new blockMemClass();
    blockList = new blockOpenList();
    blockCache = new blockClassCache();
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

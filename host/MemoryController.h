#ifndef __MEMORY_CONTROLLER_H__
#define __MEMORY_CONTROLLER_H__

#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <vector>
#include <bits/stdc++.h>

#include "StreamInterface.h"

#define CACHE_SIZE 256
#define NUM_BANKS 16
#define BURST_LENGTH 16

#define ROW_ADDR_WIDTH  10
#define COL_ADDR_WIDTH  4
#define BANK_ADDR_WIDTH 2

#define ACT_CMD 0b00000
#define PRE_CMD 0b01010
#define RD_CMD  0b01101
#define WR_CMD  0b01100
#define NOP_CMD 0b01111

class StreamInterface;

class MemoryController
{
    private:
        static MemoryController* m_pInstance;
        MemoryController();
    
        int currentActiveRow[NUM_BANKS];
        std::deque<std::tuple<uint32_t, uint16_t*, uint16_t>> memCmdQueue;
        std::deque<uint16_t> readQueue;
        std::unordered_map<uint16_t, uint16_t> cache;

        void sendMemoryCommand();
        void recvMemoryResp();

    public:
        StreamInterface* ifc;

        MemoryController(const MemoryController& obj) = delete; 
        static MemoryController* getInstance() {
            if (m_pInstance == NULL) {
                m_pInstance = new MemoryController(); 
                return m_pInstance; 
            }
            else return m_pInstance;
        }

        uint16_t getMemoryResp(uint16_t addr);
        void read(uint16_t addr);
        void write(uint16_t addr, uint16_t* write_data, uint16_t num_element);

};

#endif
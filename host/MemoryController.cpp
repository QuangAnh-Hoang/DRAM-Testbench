#include "MemoryController.h"

MemoryController*
MemoryController::m_pInstance = NULL;

MemoryController::MemoryController() {
    ifc = StreamInterface::getInstance();
    for (int i = 0; i < NUM_BANKS; i++) {
        currentActiveRow[i] = -1;
    }
}

void MemoryController::sendMemoryCommand() {
    while (!memCmdQueue.empty()) {
        uint32_t inst = std::get<0>(memCmdQueue.front());
        uint16_t* data = std::get<1>(memCmdQueue.front());
        uint16_t size = std::get<2>(memCmdQueue.front());

        // printf("Sending command: %x\n", inst);
        ifc->send(&inst, data, size);

        memCmdQueue.pop_front();
    }
}

void MemoryController::recvMemoryResp() {
    // TODO: Check cache size  
    uint16_t readResp[BURST_LENGTH];

    while (!readQueue.empty()) {
        uint16_t addr = readQueue.front();
        while (ifc->recv(&readResp[0], BURST_LENGTH*sizeof(uint16_t)) == -1) {
            printf("Waiting for response from %x\n", addr);
        }

        for (int i = 0; i < BURST_LENGTH; i++) {
            cache[addr + i] = readResp[i];
        }
        readQueue.pop_front();
    }

}

uint16_t MemoryController::getMemoryResp(uint16_t addr) {
    // Check if available in cache
    if (cache.find(addr) != cache.end()) { return cache[addr]; }

    recvMemoryResp();

    return cache[addr];
}

void MemoryController::read(uint16_t addr) {
    // Check if available in cache
    if (cache.find(addr) != cache.end()) { return; }

    uint16_t col_addr = addr & 0x1f;
    uint16_t bank_addr = (addr >> (COL_ADDR_WIDTH)) & 0x3;
    uint16_t row_addr = addr >> (BANK_ADDR_WIDTH + COL_ADDR_WIDTH);
    
    if (currentActiveRow[bank_addr] != row_addr) {
        if (currentActiveRow[bank_addr] != -1) {
            uint32_t pre_cmd = row_addr | (bank_addr << ROW_ADDR_WIDTH) | (PRE_CMD << (ROW_ADDR_WIDTH + BANK_ADDR_WIDTH));
            memCmdQueue.push_back({pre_cmd, nullptr, 0});
            printf("\tPrecharge command: %x\n", pre_cmd);
        }

        currentActiveRow[bank_addr] = row_addr;
        uint32_t act_cmd = row_addr | (bank_addr << ROW_ADDR_WIDTH) | (ACT_CMD << (ROW_ADDR_WIDTH + BANK_ADDR_WIDTH));
        memCmdQueue.push_back({act_cmd, nullptr, 0});
        printf("\tActivate command: %x\n", act_cmd);
    } 
    uint32_t read_cmd = col_addr | (bank_addr << ROW_ADDR_WIDTH) | (RD_CMD << (ROW_ADDR_WIDTH + BANK_ADDR_WIDTH));
    memCmdQueue.push_back({read_cmd, nullptr, 0});

    printf("\tRead command: %x\n", read_cmd);

    readQueue.push_back(addr);
    sendMemoryCommand();
}


void MemoryController::write(uint16_t addr, uint16_t* write_data, uint16_t num_element){
    for (int i = 0; i < num_element; i++) {
        if (cache.find(addr + i) != cache.end()) {
            cache.erase(cache.find(addr + i));
        }
    }

    // printf("\taddr = %x\t", addr);

    uint16_t col_addr = addr & 0x1f;
    uint16_t bank_addr = (addr >> (COL_ADDR_WIDTH)) & 0x3;
    uint16_t row_addr = addr >> (BANK_ADDR_WIDTH + COL_ADDR_WIDTH);

    printf("\tcol_addr = %x, bank_addr = %x, row_addr = %x\n", col_addr, bank_addr, row_addr);

    if (currentActiveRow[bank_addr] != row_addr) {
        if (currentActiveRow[bank_addr] != -1) {
            uint32_t pre_cmd = row_addr | (bank_addr << ROW_ADDR_WIDTH) | (PRE_CMD << (ROW_ADDR_WIDTH + BANK_ADDR_WIDTH));
            memCmdQueue.push_back({pre_cmd, nullptr, 0});
            printf("\tPrecharge command: %x\n", pre_cmd);
        }

        currentActiveRow[bank_addr] = row_addr;
        uint32_t act_cmd = row_addr | (bank_addr << ROW_ADDR_WIDTH) | (ACT_CMD << (ROW_ADDR_WIDTH + BANK_ADDR_WIDTH));
        memCmdQueue.push_back({act_cmd, nullptr, 0});
        printf("\tActivate command: %x\n", act_cmd);
    } 
    uint32_t write_cmd = col_addr | (bank_addr << ROW_ADDR_WIDTH) | (WR_CMD << (ROW_ADDR_WIDTH + BANK_ADDR_WIDTH));
    memCmdQueue.push_back({write_cmd, write_data, num_element*sizeof(uint16_t)});
    printf("\tWrite command: %x\n", write_cmd);

    sendMemoryCommand();
}


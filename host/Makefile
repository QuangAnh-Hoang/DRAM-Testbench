TARGET := hw_emu
BUILD_DIR := ../$(TARGET)
KERNEL_DIR := ../c-kernel/
CXXFLAGS += -g -std=c++17 -Wall -O0 -lrt


.PHONY: hw

hw: $(wildcard *)
	mkdir -p $(BUILD_DIR)
	g++ $(CXXFLAGS) host.cpp StreamInterface.cpp MemoryController.cpp -o $(BUILD_DIR)/app.exe -D HWTARGET -I${XILINX_XRT}/include/ -L$(XILINX_XRT)/lib -lxrt_coreutil -pthread

clean:
	rm -rf $(BUILD_DIR)

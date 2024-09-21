TARGET := hw_emu
PLATFORM ?= xilinx_u50_gen3x16_xdma_5_202210_1
HOSTDIR := ./host
KERNELDIR := ./kernel_rtl
CONFIGDIR := ./configs
BUILD_DIR := $(TARGET)
CXXFLAGS += -g -std=c++17 -Wall -O2

JOBS := 8
VPPFLAGS := --vivado.param general.maxThreads=8 --vivado.impl.jobs 8 --vivado.synth.jobs 8

run: build
ifeq ($(TARGET),hw)
	cp $(CONFIGDIR)/xrt.ini $(BUILD_DIR)
	cd $(BUILD_DIR) && ./app.exe
else
	cp $(CONFIGDIR)/xrt.ini $(BUILD_DIR)
	cd $(BUILD_DIR) && XCL_EMULATION_MODE=$(TARGET) ./app.exe
endif

build: package

host: $(BUILD_DIR)/app.exe 
$(BUILD_DIR)/app.exe: $(HOSTDIR)/$(wildcard *.cpp) $(HOSTDIR)/$(wildcard *.h)
ifeq ($(TARGET),sw_emu)
	$(MAKE) swsim -C $(HOSTDIR)
else
	$(MAKE) hw -C $(HOSTDIR)
endif

## TODO xo files should be created by individual Makefiles in each kernel directory
xo: $(BUILD_DIR)/krnl.xo
$(BUILD_DIR)/krnl.xo:
ifeq ($(TARGET),sw_emu)
	v++ -c -t ${TARGET} --platform $(PLATFORM) --config $(CONFIGDIR)/u50.cfg -k krnl -I./c-kernel ./c-kernel/*.cpp -o $(BUILD_DIR)/krnl.xo $(VPPFLAGS)
else
	#v++ -c --mode hls --platform $(PLATFORM) --config $(KERNELDIR)/hls_config.cfg --work_dir $(BUILD_DIR) $(VPPFLAGS)
	$(MAKE) -C $(KERNELDIR)
endif

xclbin: $(BUILD_DIR)/krnl.xclbin
$(BUILD_DIR)/krnl.xclbin: $(BUILD_DIR)/krnl.xo
	v++ -l -t ${TARGET} --platform $(PLATFORM) --config $(CONFIGDIR)/u50.cfg $(BUILD_DIR)/krnl.xo -o $(BUILD_DIR)/krnl.xclbin $(VPPFLAGS)

emconfig: $(BUILD_DIR)/emconfig.json
$(BUILD_DIR)/emconfig.json:
	emconfigutil --platform $(PLATFORM) --od $(BUILD_DIR) --nd 1

package: host emconfig xclbin
	mkdir -p $(BUILD_DIR)/hw_package
	cd $(BUILD_DIR) && cp app.exe hw_package && cp krnl.xclbin hw_package && cp emconfig.json hw_package
	cp $(CONFIGDIR)/xrt.ini $(BUILD_DIR)/hw_package
	cd $(BUILD_DIR) && tar czvf hw_package.tgz hw_package/

clean:
	rm -rf $(BUILD_DIR) app.exe *json opencl* *log *summary _x xilinx* .run .Xil .ipcache *.jou

cleanall: clean
	$(MAKE) clean -C $(KERNELDIR)
	$(MAKE) clean -C $(HOSTDIR)
	


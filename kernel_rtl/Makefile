ROOTDIR=../

PLATFORM ?= xilinx_u50_gen3x16_xdma_5_202210_1
BSCFLAGS = -show-schedule -aggressive-conditions -show-range-conflict
BSCFLAGS_SYNTH = -bdir ./build -vdir ./build/verilog -simdir ./build -info-dir ./build -fdir ./build 
TARGET := hw_emu
BUILD_DIR := ../$(TARGET)

BSVPATH := $(ROOTDIR)/kernel_rtl/
BSVPATH_ALL := $(BSVPATH)
BSIM_DIR := ./bsim
TB_DIR    :=./tb
TBS       := $(notdir $(basename $(wildcard $(TB_DIR)/*.bsv)))
TB_TARGETS := $(foreach testbench, $(TBS), $(BSIM_DIR)/$(testbench))

BSCFLAGS_BSIM = -bdir $(BSIM_DIR) -vdir $(BSIM_DIR) -simdir $(BSIM_DIR) -info-dir $(BSIM_DIR) -fdir $(BSIM_DIR) -D BSIM -l pthread

.PHONY: all verilog

MODULEPATH=

VIVADO := $(XILINX_VIVADO)/bin/vivado

all: verilog build/krnl.xo

build/krnl.xo: ./scripts/package_kernel.tcl ./scripts/gen_xo.tcl $(wildcard ./build/verilog/*.v) verilog
	mkdir -p build
	$(VIVADO) -mode batch -source scripts/gen_xo.tcl -tclargs $(BUILD_DIR)/krnl.xo krnl hw $(PLATFORM)

verilog: $(wildcard *.bsv)
	mkdir -p build
	mkdir -p build/verilog
	bsc  $(BSCFLAGS) $(BSCFLAGS_SYNTH) -remove-dollar -p +:$(MODULEPATH) -verilog -u -g krnl KernelTop.bsv 
	cd build/verilog/;bash ../../scripts/verilogcopy.sh
	cp *.v ./build/verilog/

.PHONY : mkdir
mkdir:
	mkdir -p ./build
	mkdir -p $(BSIM_DIR)
	@echo TB TARGETS : $(TB_TARGETS)

bsim: $(wildcard ./*bsv) $(wildcard $(BSVPATH)/*.bsv) $(wildcard ./cpp/*.cpp) $(wildcard $(BSVPATH)/cpp/*.cpp) $(wildcard $(BSVPATH)/cpp/*.h)
	mkdir -p $(BSIM_DIR)
	bsc $(BSCFLAGS) $(BSCFLAGS_BSIM) $(DEBUGFLAGS) -p +:$(BSVPATH_ALL) -sim -u -g mkKernelMain_tb ./KernelMain_tb.bsv  
	bsc $(BSCFLAGS) $(BSCFLAGS_BSIM) $(DEBUGFLAGS) -sim -e mkKernelMain_tb -o $(BSIM_DIR)/bsim $(BSIM_DIR)/*.ba $(BSIM_CPPFILES)

$(BSIM_DIR)/%.ba: $(TB_DIR)/%.bsv 
	bsc $(BSCFLAGS) $(BSCFLAGS_BSIM) $(DEBUGFLAGS) -p +:$(BSVPATH) -sim -u -g mkTb $<  

$(BSIM_DIR)/%: $(BSIM_DIR)/%.ba
	bsc $(BSCFLAGS) $(BSCFLAGS_BSIM) $(DEBUGFLAGS) -sim -e mkTb -o $@ $(BSIM_DIR)/*.ba $(BSIM_CPPFILES) 
	@echo testing $@...
	$@ > $(BSIM_DIR)/$(notdir $(basename $@)).log
	cat $(BSIM_DIR)/$(notdir $(basename $@)).log
	rm $@
	rm -f $(BSIM_DIR)/mkTb.o $(BSIM_DIR)/mkTb.ba $(BSIM_DIR)/mkTB.h

.PHONY : tb
tb: mkdir $(TB_TARGETS)
	@echo $(wildcard $(TB_DIR)/*.bsv)

clean:
	rm -rf $(BSIM_DIR)
	rm -rf ./build
	rm -rf *.log *.jou
	rm -rf .Xil

// ==============================================================
// Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2019.2 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
`timescale 1ns/1ps
module s_axi4_lite_controller
#(parameter
    C_S_AXI_ADDR_WIDTH = 8,
    C_S_AXI_DATA_WIDTH = 32
)(
    input  wire                          ACLK,
    input  wire                          ARESET_N,
    // input  wire                          ACLK_EN,
    input  wire [C_S_AXI_ADDR_WIDTH-1:0] AWADDR,
    input  wire                          AWVALID,
    output wire                          AWREADY,
    input  wire [C_S_AXI_DATA_WIDTH-1:0] WDATA,
    input  wire [C_S_AXI_DATA_WIDTH/8-1:0] WSTRB,
    input  wire                          WVALID,
    output wire                          WREADY,
    output wire [1:0]                    BRESP,
    output wire                          BVALID,
    input  wire                          BREADY,
    input  wire [C_S_AXI_ADDR_WIDTH-1:0] ARADDR,
    input  wire                          ARVALID,
    output wire                          ARREADY,
    output wire [C_S_AXI_DATA_WIDTH-1:0] RDATA,
    output wire [1:0]                    RRESP,
    output wire                          RVALID,
    input  wire                          RREADY,
    output wire                          interrupt,
    // user signals
    output wire                          ap_start,
    input  wire                          ap_done,
    input  wire                          ap_ready,
    input  wire                          ap_idle,

    output wire [31:0]                   scalar00,
    output wire [31:0]                   scalar01,
    output wire [31:0]                   scalar02,

    output wire [63:0]                   inst_queue,
    output wire [63:0]                   data_in_queue,
    output wire [63:0]                   data_out_queue

);
//------------------------Address Info-------------------
// 0x00 : Control signals
//        bit 0  - ap_start (Read/Write/COH)
//        bit 1  - ap_done (Read/COR)
//        bit 2  - ap_idle (Read)
//        bit 3  - ap_ready (Read)
//        bit 7  - auto_restart (Read/Write)
//        others - reserved
// 0x04 : Global Interrupt Enable Register
//        bit 0  - Global Interrupt Enable (Read/Write)
//        others - reserved
// 0x08 : IP Interrupt Enable Register (Read/Write)
//        bit 0  - Channel 0 (ap_done)
//        bit 1  - Channel 1 (ap_ready)
//        others - reserved
// 0x0c : IP Interrupt Status Register (Read/TOW)
//        bit 0  - Channel 0 (ap_done)
//        bit 1  - Channel 1 (ap_ready)
//        others - reserved

// 0x10 : Data signal of 'scalar00'
//        bit 31~0 - scalar00[31:0] (Read/Write)
// 0x14 : reserved
// 0x18 : Data signal of 'scalar01'
//        bit 31~0 - scalar01[31:0] (Read/Write)
// 0x1c : reserved
// 0x20 : Data signal of 'scalar02'
//        bit 31~0 - scalar02[31:0] (Read/Write)
// 0x24 : reserved

// 0x28 : Data signal of 'inst_queue'
//        bit 31~0 - A[31:0] (Read/Write)
// 0x2c : Data signal of 'inst_queue'
//        bit 31~0 - A[63:32] (Read/Write)
// 0x30 : reserved

// 0x34 : Data signal of 'data_in_queue'
//        bit 31~0 - B[31:0] (Read/Write)
// 0x38 : Data signal of 'data_in_queue'
//        bit 31~0 - B[63:32] (Read/Write)
// 0x3c : reserved

// 0x40 : Data signal of 'data_out_queue'
//        bit 31~0 - B[31:0] (Read/Write)
// 0x44 : Data signal of 'data_out_queue'
//        bit 31~0 - B[63:32] (Read/Write)
// 0x48 : reserved
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

//------------------------Parameter----------------------
localparam
    ADDR_AP_CTRL         = 8'h00,
    ADDR_GIE             = 8'h04,
    ADDR_IER             = 8'h08,
    ADDR_ISR             = 8'h0c,

    ADDR_SCALAR00_DATA_0          = 8'h10,
    ADDR_SCALAR00_CTRL            = 8'h14,
    ADDR_SCALAR01_DATA_0          = 8'h18,
    ADDR_SCALAR01_CTRL            = 8'h1c,
    ADDR_SCALAR02_DATA_0          = 8'h20,
    ADDR_SCALAR02_CTRL            = 8'h24,

    ADDR_INST_Q_DATA_0            = 8'h28,
    ADDR_INST_Q_DATA_1            = 8'h2c,
    ADDR_INST_Q_CTRL              = 8'h30,
    ADDR_DATA_IN_Q_DATA_0         = 8'h34,
    ADDR_DATA_IN_Q_DATA_1         = 8'h38,
    ADDR_DATA_IN_Q_CTRL           = 8'h3c,
    ADDR_DATA_OUT_Q_DATA_0        = 8'h40,
    ADDR_DATA_OUT_Q_DATA_1        = 8'h44,
    ADDR_DATA_OUT_Q_CTRL          = 8'h48,

    WRIDLE               = 2'd0,
    WRDATA               = 2'd1,
    WRRESP               = 2'd2,
    WRRESET              = 2'd3,
    RDIDLE               = 2'd0,
    RDDATA               = 2'd1,
    RDRESET              = 2'd2,
    ADDR_BITS         = 8;

//------------------------Local signal-------------------
    reg  [1:0]                    wstate = WRRESET;
    reg  [1:0]                    wnext;
    reg  [ADDR_BITS-1:0]          waddr;
    wire [31:0]                   wmask;
    wire                          aw_hs;
    wire                          w_hs;
    reg  [1:0]                    rstate = RDRESET;
    reg  [1:0]                    rnext;
    reg  [31:0]                   rdata;
    wire                          ar_hs;
    wire [ADDR_BITS-1:0]          raddr;
    // internal registers
    reg                           int_ap_idle;
    reg                           int_ap_ready;
    reg                           int_ap_done = 1'b0;
    reg                           int_ap_start = 1'b0;
    reg                           int_auto_restart = 1'b0;
    reg                           int_gie = 1'b0;
    reg  [1:0]                    int_ier = 2'b0;
    reg  [1:0]                    int_isr = 2'b0;
    
    reg  [31:0]                   int_scalar00 = 'b0;
    reg  [31:0]                   int_scalar01 = 'b0;
    reg  [31:0]                   int_scalar02 = 'b0;

    reg  [63:0]                   int_inst_q_addr = 'b0;
    reg  [63:0]                   int_data_in_q_addr = 'b0;
    reg  [63:0]                   int_data_out_q_addr = 'b0;
    wire ACLK_EN;
    wire ARESET;
    assign ACLK_EN = 1;
    assign ARESET = ~ARESET_N;
//------------------------Instantiation------------------

//------------------------AXI write fsm------------------
assign AWREADY = (wstate == WRIDLE);
assign WREADY  = (wstate == WRDATA);
assign BRESP   = 2'b00;  // OKAY
assign BVALID  = (wstate == WRRESP);
assign wmask   = { {8{WSTRB[3]}}, {8{WSTRB[2]}}, {8{WSTRB[1]}}, {8{WSTRB[0]}} };
assign aw_hs   = AWVALID & AWREADY;
assign w_hs    = WVALID & WREADY;

// wstate
always @(posedge ACLK) begin
    if (ARESET)
        wstate <= WRRESET;
    else if (ACLK_EN)
        wstate <= wnext;
end

// wnext
always @(*) begin
    case (wstate)
        WRIDLE:
            if (AWVALID)
                wnext = WRDATA;
            else
                wnext = WRIDLE;
        WRDATA:
            if (WVALID)
                wnext = WRRESP;
            else
                wnext = WRDATA;
        WRRESP:
            if (BREADY)
                wnext = WRIDLE;
            else
                wnext = WRRESP;
        default:
            wnext = WRIDLE;
    endcase
end

// waddr
always @(posedge ACLK) begin
    if (ACLK_EN) begin
        if (aw_hs)
            waddr <= AWADDR[ADDR_BITS-1:0];
    end
end

//------------------------AXI read fsm-------------------
assign ARREADY = (rstate == RDIDLE);
assign RDATA   = rdata;
assign RRESP   = 2'b00;  // OKAY
assign RVALID  = (rstate == RDDATA);
assign ar_hs   = ARVALID & ARREADY;
assign raddr   = ARADDR[ADDR_BITS-1:0];

// rstate
always @(posedge ACLK) begin
    if (ARESET)
        rstate <= RDRESET;
    else if (ACLK_EN)
        rstate <= rnext;
end

// rnext
always @(*) begin
    case (rstate)
        RDIDLE:
            if (ARVALID)
                rnext = RDDATA;
            else
                rnext = RDIDLE;
        RDDATA:
            if (RREADY & RVALID)
                rnext = RDIDLE;
            else
                rnext = RDDATA;
        default:
            rnext = RDIDLE;
    endcase
end

// rdata
always @(posedge ACLK) begin
    if (ACLK_EN) begin
        if (ar_hs) begin
            rdata <= 1'b0;
            case (raddr)
                ADDR_AP_CTRL: begin
                    rdata[0] <= int_ap_start;
                    rdata[1] <= int_ap_done;
                    rdata[2] <= int_ap_idle;
                    rdata[3] <= int_ap_ready;
                    rdata[7] <= int_auto_restart;
                end
                ADDR_GIE: begin
                    rdata <= int_gie;
                end
                ADDR_IER: begin
                    rdata <= int_ier;
                end
                ADDR_ISR: begin
                    rdata <= int_isr;
                end
                ADDR_SCALAR00_DATA_0: begin
                    rdata <= int_scalar00[31:0];
                end
                ADDR_SCALAR01_DATA_0: begin
                    rdata <= int_scalar01[31:0];
                end
                ADDR_SCALAR02_DATA_0: begin
                    rdata <= int_scalar02[31:0];
                end

                ADDR_INST_Q_DATA_0: begin
                    rdata <= int_inst_q_addr[31:0];
                end
                ADDR_INST_Q_DATA_1: begin
                    rdata <= int_inst_q_addr[63:32];
                end

                ADDR_DATA_IN_Q_DATA_0: begin
                    rdata <= int_data_in_q_addr[31:0];
                end
                ADDR_DATA_IN_Q_DATA_1: begin
                    rdata <= int_data_in_q_addr[63:32];
                end
                ADDR_DATA_OUT_Q_DATA_0: begin
                    rdata <= int_data_out_q_addr[31:0];
                end
                ADDR_DATA_OUT_Q_DATA_1: begin
                    rdata <= int_data_out_q_addr[63:32];
                end
            endcase
        end
    end
end


//------------------------Register logic-----------------
assign interrupt    = int_gie & (|int_isr);
assign ap_start     = int_ap_start;
//assign int_ap_idle  = ap_idle;
//assign int_ap_ready = ap_ready;
assign scalar00     = int_scalar00;
assign scalar01     = int_scalar01;
assign scalar02     = int_scalar02;


assign inst_queue      = int_inst_q_addr;
assign data_in_queue   = int_data_in_q_addr;
assign data_out_queue  = int_data_out_q_addr;

// int_ap_start
always @(posedge ACLK) begin
    if (ARESET)
        int_ap_start <= 1'b0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_AP_CTRL && WSTRB[0] && WDATA[0])
            int_ap_start <= 1'b1;
        else if (ap_ready)
            int_ap_start <= int_auto_restart; // clear on handshake/auto restart
    end
end

// int_ap_done
always @(posedge ACLK) begin
    if (ARESET)
        int_ap_done <= 1'b0;
    else if (ACLK_EN) begin
        if (ap_done)
            int_ap_done <= 1'b1;
        else if (ar_hs && raddr == ADDR_AP_CTRL)
            int_ap_done <= 1'b0; // clear on read
    end
end

// int_ap_idle
always @(posedge ACLK) begin
    if (ARESET)
        int_ap_idle <= 1'b0;
    else if (ACLK_EN) begin
            int_ap_idle <= ap_idle;
    end
end

// int_ap_ready
always @(posedge ACLK) begin
    if (ARESET)
        int_ap_ready <= 1'b0;
    else if (ACLK_EN) begin
            int_ap_ready <= ap_ready;
    end
end

// int_auto_restart
always @(posedge ACLK) begin
    if (ARESET)
        int_auto_restart <= 1'b0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_AP_CTRL && WSTRB[0])
            int_auto_restart <=  WDATA[7];
    end
end

// int_gie
always @(posedge ACLK) begin
    if (ARESET)
        int_gie <= 1'b0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_GIE && WSTRB[0])
            int_gie <= WDATA[0];
    end
end

// int_ier
always @(posedge ACLK) begin
    if (ARESET)
        int_ier <= 1'b0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_IER && WSTRB[0])
            int_ier <= WDATA[1:0];
    end
end

// int_isr[0]
always @(posedge ACLK) begin
    if (ARESET)
        int_isr[0] <= 1'b0;
    else if (ACLK_EN) begin
        if (int_ier[0] & ap_done)
            int_isr[0] <= 1'b1;
        else if (w_hs && waddr == ADDR_ISR && WSTRB[0])
            int_isr[0] <= int_isr[0] ^ WDATA[0]; // toggle on write
    end
end

// int_isr[1]
always @(posedge ACLK) begin
    if (ARESET)
        int_isr[1] <= 1'b0;
    else if (ACLK_EN) begin
        if (int_ier[1] & ap_ready)
            int_isr[1] <= 1'b1;
        else if (w_hs && waddr == ADDR_ISR && WSTRB[0])
            int_isr[1] <= int_isr[1] ^ WDATA[1]; // toggle on write
    end
end

// int_scalar00[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_scalar00[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_SCALAR00_DATA_0)
            int_scalar00[31:0] <= (WDATA[31:0] & wmask) | (int_scalar00[31:0] & ~wmask);
    end
end
// int_scalar01[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_scalar01[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_SCALAR01_DATA_0)
            int_scalar01[31:0] <= (WDATA[31:0] & wmask) | (int_scalar01[31:0] & ~wmask);
    end
end
// int_scalar02[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_scalar02[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_SCALAR02_DATA_0)
            int_scalar02[31:0] <= (WDATA[31:0] & wmask) | (int_scalar02[31:0] & ~wmask);
    end
end

// int_inst_q_addr[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_inst_q_addr[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_INST_Q_DATA_0) begin
            int_inst_q_addr[31:0] <= (WDATA[31:0] & wmask) | (int_inst_q_addr[31:0] & ~wmask);
            $display("s_axi_control.v: int_inst_q_addr[31:0] = %x", int_inst_q_addr[31:0]);
        end
    end
end

// int_inst_q_addr[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_inst_q_addr[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_INST_Q_DATA_1) begin
            int_inst_q_addr[63:32] <= (WDATA[31:0] & wmask) | (int_inst_q_addr[63:32] & ~wmask);
            $display("s_axi_control.v: int_inst_q_addr[63:32] = %x", int_inst_q_addr[63:32]);
        end
    end
end

// int_data_in_q_addr[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_data_in_q_addr[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_DATA_IN_Q_DATA_0) begin
            int_data_in_q_addr[31:0] <= (WDATA[31:0] & wmask) | (int_data_in_q_addr[31:0] & ~wmask);
            $display("s_axi_control.v: int_data_in_q_addr[31:0] = %x", int_data_in_q_addr[31:0]);
        end
    end
end

// int_data_in_q_addr[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_data_in_q_addr[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_DATA_IN_Q_DATA_1) begin
            int_data_in_q_addr[63:32] <= (WDATA[31:0] & wmask) | (int_data_in_q_addr[63:32] & ~wmask);
            $display("s_axi_control.v: int_data_in_q_addr[63:32] = %x", int_data_in_q_addr[63:32]);
        end
    end
end

// int_data_out_q_addr[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_data_out_q_addr[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_DATA_OUT_Q_DATA_0) begin
            int_data_out_q_addr[31:0] <= (WDATA[31:0] & wmask) | (int_data_out_q_addr[31:0] & ~wmask);
            $display("s_axi_control.v: int_data_out_q_addr[31:0] = %x", int_data_out_q_addr[31:0]);
        end
    end
end

// int_data_out_q_addr[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_data_out_q_addr[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_DATA_OUT_Q_DATA_1) begin
            int_data_out_q_addr[63:32] <= (WDATA[31:0] & wmask) | (int_data_out_q_addr[63:32] & ~wmask);
            $display("s_axi_control.v: int_data_out_q_addr[63:32] = %x", int_data_out_q_addr[63:32]);
        end
    end
end

//------------------------Memory logic-------------------

endmodule

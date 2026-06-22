/** @file bcu_config.h
*   @brief BCU config Definition File
*   @date 17-Dec-2020
*   @version 01.00.00
*
*
*MCU pin assigment
*   Pin port/function   type    VCU signal
*   1       NC
*   2       NC
*   3   het1[29]    Digital Input   input 5
*   4   het1[27]    Digital Input   input 6
*   5       NC
*   6       Digital Output  output 7
*   7       NC
*   8       NC
*   9   gioA[2] Digital Output  can 3 standby
*   10      VCC
*   11      VSS
*   12  CAN3RX  CAN CAN3RX
*   13  CAN3RX  CAN CAN3TX
*   14  gioA[5] Digital Output  output 8
*   15  het1[22]    Digital Output  output 9
*   16  gioA[6] Digital Output  output 10
*   17      VCC
*   18      OSC
*   19      GND
*   20      OSC
*   21      VSS
*   22  gioA[7] Digital Output  output 11
*   23  het1[1] Digital Output  output 5
*   24  het1[3] Digital Output  output 4
*   25  het1[0] Digital Output  output 12
*   26      VCC
*   27      VSS
*   28      VSS
*   29      VCC
*   30      NC
*   31  het1[5] Digital Input   pgood 1V2
*   32  mibspi5ncs[0]   Digital Output  output 6
*   33  het1[7] Digital Output  output 1
*   34      TEST
*   35      NC
*   36  het1[4] Digital Output  output 3
*   37  MDCLK   ETH MDCLK
*   38  het1[6] Digital Output  Vpu enable
*   39  het1[13]    Digital Output  output 2
*   40  MDIO    ETH MDIO
*   41  het1[15]    Digital Output  Lin En
*   42      VCC
*   43      VSS
*   44      VSS
*   45      VCC
*   46      nPORRST
*   47      VSS
*   48      VCC
*   49      VCC
*   50      VSS
*   51  mibspu3SOMI SPI SPI3SOMI
*   52  mibspi3SIMO SPI SPI3SIMO
*   53  mibspi3CLK  SPI SPI3CLK
*   54  mibspi3ENA  SPI SPI3ENA
*   55  mibspi3NCS  SPI SPI3CS0
*   56      VSS
*   57      VCC
*   58  ad1in[16]   AN input    output monitor 11
*   59  ad1in[17]   AN input    output monitor 12
*   60  ad1in[0]    AN input    output monitor 8
*   61  ad1in[7]    AN input    output monitor  7
*   62  ad1in[18]   AN input    output monitor  5
*   63  ad1in[19]   AN input    output monitor  6
*   64  ad1in[20]   AN input    output monitor  1
*   65  ad1in[21]   AN input    output monitor  3
*   66      ADREF
*   67      ADREF
*   68      VSS
*   69      VCC
*   70  ad1in[9]    AN input    input 5
*   71  ad1in[1]    AN input    output monitor 10
*   72  ad1in[10]   AN input    input 6
*   73  ad1in[2]    AN input    output monitor 9
*   74  ad1in[3]    AN input    input 4
*   75  ad1in[11]   AN input    input 1
*   76  ad1in[4]    AN input    input 2
*   77  ad1in[12]   AN input    input 3
*   78  ad1in[5]    AN input    input 11
*   79  ad1in[13]   AN input    input 10
*   80  ad1in[6]    AN input    input 7
*   81  ad1in[22]   AN input    output monitor 4
*   82  ad1in[14]   AN input    output monitor 2
*   83  ad1in[8]    AN input    input 9
*   84  ad1in[23]   AN input    LV supply
*   85  ad1in[15]   AN input    input 8
*   86  RMII RXER   ETH RMII RXER
*   87      VCC
*   88      VSS
*   89  CAN1TX  CAN CAN1TX
*   90  CAN1RX  CAN CAN1RX
*   91  RMII RXD0   ETH RMII RXD0
*   92  RMII RDD1   ETH RMII RDD1
*   93      NC
*   94      NC  Spare 0
*   95      NC
*   96  het1[23]    Digital Input   input 4
*   97      NC
*   98  RMII TXD0   ETH RMII TXD0
*   99  RMII TXD1   ETH RMII TXD1
*   100 RMII TXEN   ETH RMII TXEN
*   101     VCC
*   102     VSS
*   103     VSS
*   104     VCC
*   105     NC
*   106 het1[8] Digital Input   input 12
*   107 RMII REFCLK ETH RMII REFCLK
*   108     JTAG
*   109 nTRST   SYS
*   110     JTAG
*   111     JTAG
*   112     JTAG
*   113     JTAG
*   114     VCC
*   115     VSS
*   116 nRST    SYS
*   117 nERROR  SYS
*   118 het1[10]    Digital Input   pgood
*   119 ECLK    SYS
*   120     VCC
*   121     VSS
*   122     VSS
*   123     VCC
*   124 RMII CRS DV ETH RMII CRS DV
*   125 het1[14]    Digital Input   input 3
*   126     NC
*   127 het1[30]    Digital Input   input 2
*   128 CAN2TX  CAN CAN2TX
*   129 CAN2RX  CAN CAN2RX
*   130 het1[17]    Digital Input   input 1
*   131 LIN RX  LIN
*   132 LIN TX  LIN
*   133     NC
*   134     VCC
*   135     VSS
*   136     VCC
*   137     VCC
*   138     VSS
*   139 het1[16]    Digital Output  can 2 standby
*   140 het1[18]    Digital Output  can 1 standby
*   141 het1[20]    Digital Input   input 0
*   142     NC
*   143     VCC
*   144     VSS
*
*/

#include "portmacro.h"

#define VERSION_MAJOR 2
#define VERSION_MINOR 2

#define CAN_TX_TASK_FREQ_MS ( 100 / portTICK_PERIOD_MS )
#define BL_START_ADDRESS 0x00000000
#define BCU_FEE_WRITES_MAX 128 /* max number of writes before flash erase */
#define WATCHDOG_RESET_TIME_MS 10

#define OUTPUT_MONITOR_THRESHOLD 1500U
#define SIMULINK_TASK_STACK_SIZE (1024U*2U)



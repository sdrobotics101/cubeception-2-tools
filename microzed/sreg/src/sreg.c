/*
 * Copyright (c) 2012 Xilinx, Inc.  All rights reserved.
 *
 * Xilinx, Inc.
 * XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS" AS A
 * COURTESY TO YOU.  BY PROVIDING THIS DESIGN, CODE, OR INFORMATION AS
 * ONE POSSIBLE   IMPLEMENTATION OF THIS FEATURE, APPLICATION OR
 * STANDARD, XILINX IS MAKING NO REPRESENTATION THAT THIS IMPLEMENTATION
 * IS FREE FROM ANY CLAIMS OF INFRINGEMENT, AND YOU ARE RESPONSIBLE
 * FOR OBTAINING ANY RIGHTS YOU MAY REQUIRE FOR YOUR IMPLEMENTATION.
 * XILINX EXPRESSLY DISCLAIMS ANY WARRANTY WHATSOEVER WITH RESPECT TO
 * THE ADEQUACY OF THE IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO
 * ANY WARRANTIES OR REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE
 * FROM CLAIMS OF INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>

#include "regio.h"
#include "spi.h"

void print_usage (FILE* stream, int exit_code)
{
    fprintf(stream, "\nsreg - spi peripheral register access utility\n");
    fprintf(stream, "\nUsage\n");
    fprintf(stream, "    sreg [--help|-h]\n");
    fprintf(stream, "    sreg [--verbose] --dev device --len length --write data...\n");
    fprintf(stream, "    sreg [--verbose] --dev device --len length --read\n"         );
    fprintf(stream, "    sreg [-v] -d device -l length -w data...\n"                  );
    fprintf(stream, "    sreg [-v] -d device -l length -r\n"                          );
    fprintf(stream,"\nOptions:\n");
    fprintf(stream,"    -v                specifies verbose mode\n");
    fprintf(stream,"    -d dev            specifies device (ps0|ps1|mpu0|mpu1)\n");
    fprintf(stream,"    -l len            specifies length in bytes\n");
    fprintf(stream,"    -w                specifies write to device\n");
    fprintf(stream,"    -r                specifies read from device\n");
    fprintf(stream,"\nArguments:\n");
    fprintf(stream,"    data...           specifies byte stream\n");

    exit (exit_code);
}

int main(int argc, char **argv)
{

    const char* const short_options = "d:hl:rvw";

    const struct option long_options[] = {
        { "dev",     1, NULL, 'd' },
        { "help",    0, NULL, 'h' },
        { "len",     1, NULL, 'l' },
        { "read",    0, NULL, 'r' },
        { "verbose", 0, NULL, 'v' },
        { "write",   0, NULL, 'w' }};

    const char*     device  = NULL;
    unsigned int    length  = 0;
    int             verbose = 1;
    int             op_type = 0;
    int             next_option;
    unsigned int    cnt, bcnt;

    SPI_Device      spi_dev;             
    SpiInit         spi_init = {
            .bitrate         = 1000000,
            .mode            = 0,
            .lsbFirst        = false,
            .intEnable       = false,
            .autoSlaveSelect = false
        };

    uint8_t         buf_rd[16];     /* read  buffer */
    uint8_t         buf_wr[16];     /* write buffer */

    /* parse the command line */
    do {
        next_option = getopt_long (argc, argv, short_options, long_options, NULL);
        switch (next_option) {
            case 'd': device = optarg;                      break;
            case 'h': print_usage(stdout, 0);               break;
            case 'l': length = strtoul(optarg, NULL, 16);   break;
            case 'r': op_type = 1;                          break;
            case 'v': verbose = 2;                          break;
            case 'w': op_type = 0;                          break;
            case '?': print_usage (stderr, 1);              break;
            case  -1:                                       break;
            default:  abort ();                             break;
        }
    } while (next_option != -1);
    
    if ((device==NULL)||(length==0)||(length>16)) print_usage(stdout, 0);

    /* initialize the read and write buffers */
    for (cnt=0; cnt<16; cnt++) {
        buf_rd[cnt] = 0;
        buf_wr[cnt] = 0;
    }

    if      (strcmp(device, "ps0")==0)  { spi_dev  = 0x00020000; }
    else if (strcmp(device, "ps1")==0)  { spi_dev  = 0x00030000; }
    else if (strcmp(device, "mpu0")==0) { spi_dev  = 0x00040000; }
    else if (strcmp(device, "mpu1")==0) { spi_dev  = 0x00050000; }
    else { print_usage(stderr, 1); }

    bcnt = 0;
    int i;
    if (op_type==0) {
        for (i=optind; i<argc; i++) {
            if (bcnt<16) {
                buf_wr[bcnt] = strtoul(argv[i], NULL, 16);
                bcnt++;
            }
        }
    }

    /* initialize the SPI device */
    if (!spiInit(spi_dev, &spi_init, verbose)) {
        return (2);
    }

    spiSelect(spi_dev, 0, verbose);      /* select the spi device */

    /* perform the spi transaction */
    if (!spiTxRx(spi_dev, buf_wr, buf_rd, length, verbose)) {
        spiDeselect(spi_dev, verbose);
        printf("ERROR : TRANSACTION ERROR\n");
        return (3);
    }
    
    spiDeselect(spi_dev, verbose);       /* deselect the spi device */

    return (0);
}


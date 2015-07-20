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

#include "regio.h"

int main(int argc, char **argv)
{
    unsigned int addr;
    unsigned int data;
    unsigned int verbose = 0;
             int argn    = 0;

    if (strcmp(argv[1],"-v")==0) {
        verbose = 1;
        argn    = 1;
    }

    if (strcmp(argv[argn+1],"-r")==0) {
        addr = strtoul(argv[argn+2], NULL, 16);
        regio_rd32(addr, &data, verbose);
        printf("R 0x%08x 0x%08x\n", addr, data);
        
    }
    else if (strcmp(argv[argn+1],"-w")==0) {
        addr = strtoul(argv[argn+2], NULL, 16);
        data = strtoul(argv[argn+3], NULL, 16);
        regio_wr32(addr,  data, verbose);
        printf("W 0x%08x 0x%08x\n", addr, data);
    }

    return (0);
}


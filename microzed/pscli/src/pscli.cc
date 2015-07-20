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
#include "ms5803.h"

void print_usage (FILE* stream, int exit_code)
{
    fprintf(stream, "\npscli - pressure sensor command line interface\n");
    fprintf(stream, "\nUsage\n");
    fprintf(stream, "    pscli [--help|-h]\n");
    fprintf(stream, "    pscli [--verbose] --dev device command args...\n");
    fprintf(stream, "    pscli [-v] -d device [-r] [-t] [-p]\n");
    fprintf(stream,"\nOptions:\n");
    fprintf(stream,"    -v, --verbose     specifies verbose mode\n");
    fprintf(stream,"    -d, --dev device  specifies device (ps0|ps1)\n");
    fprintf(stream,"\nCommands:\n");
    fprintf(stream,"    -r, --reset       resets the pressure sensor\n");
    fprintf(stream,"    -i, --init        initializes the pressure sensor\n");
    fprintf(stream,"    -p, --pres        reads the pressure value\n");
    fprintf(stream,"    -t, --temp        reads the temperatur value\n");

    exit (exit_code);
}

int main(int argc, char **argv)
{
    const char* const short_options = "d:hiprtv";

    const struct option long_options[] = {
        { "dev",     1, NULL, 'd' },
        { "help",    0, NULL, 'h' },
        { "init",    0, NULL, 'i' },
        { "pres",    0, NULL, 'p' },
        { "reset",   0, NULL, 'r' },
        { "temp",    0, NULL, 't' },
        { "verbose", 0, NULL, 'v' }};

    const char*     device  = NULL;

    int             cmd_reset = 0;
    int             cmd_init  = 0;
    int             cmd_pres  = 1;
    int             cmd_temp  = 1;
    int             verbose   = 1;

    int             next_option;

    SPI_Device      spi_dev;

    MS5803          *ms5803;

    /* parse the command line */
    do {
        next_option = getopt_long (argc, argv, short_options, long_options, NULL);
        switch (next_option) {
            case 'd': device = optarg;          break;
            case 'h': print_usage(stdout, 0);   break;
            case 'i': cmd_init  = 1;            break;
            case 'p': cmd_pres  = 1;            break;
            case 'r': cmd_reset = 1;            break;
            case 't': cmd_temp  = 1;            break;
            case 'v': verbose   = 2;            break;
            case '?': print_usage (stderr, 1);  break;
            case  -1:                           break;
            default:  abort ();                 break;
        }
    } while (next_option != -1);
    
    if ((device==NULL)) print_usage(stdout, 0);

    if      (strcmp(device, "ps0")==0)  { spi_dev  = 0x00020000;  }
    else if (strcmp(device, "ps1")==0)  { spi_dev  = 0x00030000;  }
    else                                { print_usage(stderr, 1); }

    ms5803 = new MS5803(spi_dev, verbose-1);

    if (cmd_reset) {
        ms5803->resetSensor();
        printf("PSCLI  : 0x%08x : reset sensor completed\n", spi_dev);
    }

    if (cmd_init) {
        ms5803->initSensor();
        printf("PSCLI  : 0x%08x : init sensor completed\n", spi_dev);
    }

    if (cmd_pres || cmd_temp) {
    	ms5803->initSensor();
        ms5803->readSensor();
        if (cmd_pres)
            printf("PSCLI  : 0x%08x : pressure     : %8.2f\n", spi_dev, ms5803->pressure());
        if (cmd_temp)
            printf("PSCLI  : 0x%08x : temperature  : %8.2f\n", spi_dev, ms5803->temperature());
    }

    return (0);
}


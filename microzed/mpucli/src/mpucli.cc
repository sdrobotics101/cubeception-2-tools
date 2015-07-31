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
#include "mpu9250.h"

void print_usage (FILE* stream, int exit_code)
{
    fprintf(stream, "\nmpucli - mpu command line interface\n");
    fprintf(stream, "\nUsage\n");
    fprintf(stream, "mpucli --help              \n");
    fprintf(stream,"\nOptions:\n");
    fprintf(stream,"    -a, --accl        reads accelerometer\n");
    fprintf(stream,"    -d, --dev device  specifies device (mpu0|mpu1)\n");
    fprintf(stream,"    -g, --gyro        reads gyroscope\n");
    fprintf(stream,"    -m, --magn        reads magnetometer\n");
    fprintf(stream,"    -v, --verbose     specifies verbose mode\n");
    fprintf(stream,"\nCommands:\n");

    exit (exit_code);
}

int main(int argc, char **argv)
{

    const char* const short_options = "ad:ghimv";

    const struct option long_options[] = {
        { "accl",    0, NULL, 'a' },
        { "dev",     1, NULL, 'd' },
        { "gyro",    0, NULL, 'g' },
        { "help",    0, NULL, 'h' },
        { "init",    0, NULL, 'i' },
        { "magn",    0, NULL, 'm' },
        { "verbose", 0, NULL, 'v' }};

    const char*     device      = NULL;

    bool            arg_accl    = true;
    bool            arg_gyro    = true;
    bool            arg_magn    = true;
    bool            arg_init    = false;
    int             verbose     = 1;
    int             next_option;

    SPI_Device      spi_dev;

    MPU9250         *mpu9250;

    /* parse the command line */
    do {
        next_option = getopt_long (argc, argv, short_options, long_options, NULL);
        switch (next_option) {
            case 'a': arg_accl      = true;     break;
            case 'd': device        = optarg;   break;
            case 'g': arg_gyro      = true;     break;
            case 'h': print_usage(stdout, 0);   break;
            case 'i': arg_init      = true;     break;
            case 'm': arg_magn      = true;     break;
            case 'v': verbose       = 2;        break;
            case '?': print_usage (stderr, 1);  break;
            case  -1:                           break;
            default:  abort ();                 break;
        }
    } while (next_option != -1);
    
    if (device==NULL) print_usage(stdout, 0);

    if      (strcmp(device, "mpu0")==0) { spi_dev  = 0x00040000; }
    else if (strcmp(device, "mpu1")==0) { spi_dev  = 0x00050000; }
    else { print_usage(stderr, 1); }

    mpu9250 = new MPU9250(spi_dev, verbose);

    if (arg_init) mpu9250->init(0, 0);

    /* parse command line arguments and start processing */
    int i;
    for (i=optind; i<argc; i++) {

        /* process chipid */
        if (strcmp(argv[i], "chipid")==0) {
            if (verbose > 1)
                printf("MPUCLI : 0x%08x : processing chipid\n", spi_dev);
            
            printf("MPUCLI : 0x%08x : chipid       : 0x%02x\n", spi_dev, mpu9250->chipid_mp9250());
        }

        else {
            break;
        }
    }

    if (arg_accl || arg_gyro || arg_magn) {

        float ax, ay, az, gx, gy, gz, mx, my, mz, temp;

        mpu9250->read(&ax, &ay, &az, &gx, &gy, &gz, &mx, &my, &mz, &temp);

        if (arg_accl) {
            printf("MPUCLI : 0x%08x : accl x       : %9.5f\n", spi_dev, ax);
            printf("MPUCLI : 0x%08x : accl y       : %9.5f\n", spi_dev, ay);
            printf("MPUCLI : 0x%08x : accl z       : %9.5f\n", spi_dev, az);
        }

        if (arg_gyro) {
            printf("MPUCLI : 0x%08x : gyro x       : %9.5f\n", spi_dev, gx);
            printf("MPUCLI : 0x%08x : gyro y       : %9.5f\n", spi_dev, gy);
            printf("MPUCLI : 0x%08x : gyro z       : %9.5f\n", spi_dev, gz);
        }
        
        if (arg_magn) {
            printf("MPUCLI : 0x%08x : magn x       : %9.5f\n", spi_dev, mx);
            printf("MPUCLI : 0x%08x : magn y       : %9.5f\n", spi_dev, my);
            printf("MPUCLI : 0x%08x : magn z       : %9.5f\n", spi_dev, mz);
        }

            printf("MPUCLI : 0x%08x : temp         : %6.2f\n", spi_dev, temp);
    }

    return (0);
}


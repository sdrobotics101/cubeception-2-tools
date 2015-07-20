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

#include "pwm.h"

void print_usage (FILE* stream, int exit_code)
{
    fprintf(stream, "\npwmcli - pwm controller command line interface\n");
    fprintf(stream, "\nUsage\n");
    fprintf(stream, "pwmcli --help              \n");
    fprintf(stream, "pwmcli map chn map         \n");
    fprintf(stream, "pwmcli mapall m0 m1 ... m23\n");
    fprintf(stream, "pwmcli mapall -f map.cfg   \n");
    fprintf(stream, "pwmcli enable              \n");
    fprintf(stream, "pwmcli disable             \n");
    fprintf(stream, "pwmcli set chn val         \n");
    fprintf(stream, "pwmcli setall v0 v1 ... v23\n");
    fprintf(stream, "pwmcli setall -f val       \n");
    fprintf(stream, "pwmcli zeroall             \n");
    fprintf(stream,"\nOptions:\n");
    fprintf(stream,"    -v, --verbose     specifies verbose mode\n");
    fprintf(stream,"    -f, --file file   specifies file to use\n");
    fprintf(stream,"    -p, --percent     specifies format in percent\n");
    fprintf(stream,"    -i, --integer     specifies format in integer\n");
    fprintf(stream,"\nCommands:\n");
    fprintf(stream,"    map chn map       maps the specified channel\n");
    fprintf(stream,"    mapall ...        maps all channels\n");
    fprintf(stream,"    enable            enables all channels\n");
    fprintf(stream,"    disable           disables all channels\n");
    fprintf(stream,"    set chn val       sets the value for the channel\n");
    fprintf(stream,"    setall ...        sets values for all channels\n");
    fprintf(stream,"    zeroall           zeros all pwms\n");

    exit (exit_code);
}

int main(int argc, char **argv)
{
    const char* const short_options = "f:ipv";

    const struct option long_options[] = {
        { "file",    1, NULL, 'f' },
        { "integer", 0, NULL, 'i' },
        { "percent", 0, NULL, 'p' },
        { "verbose", 0, NULL, 'v' }};

    const char*     argfile = NULL;
    int             fmt_int = 0;
    int             verbose = 1;

    int             next_option;

    FILE            *fp;

    PWM             *pwm;

    int             map_tbl[24];    // mapping table
    float           pwm_per[24];    // pwm in percent
    unsigned int    pwm_int[24];    // pwm in integer

    char            fbuf[255];

    int i;
    for (i=0; i<24; i++) {
        map_tbl[i] = i;
        pwm_per[i] = 0.0;
        pwm_int[i] = 0;
    }

    /* parse the command line */
    do {
        next_option = getopt_long (argc, argv, short_options, long_options, NULL);
        switch (next_option) {
            case 'f': argfile   = optarg;       break;
            case 'i': fmt_int   = 1;            break;
            case 'p': fmt_int   = 0;            break;
            case 'v': verbose   = 2;            break;
            case '?': print_usage (stderr, 1);  break;
            case  -1:                           break;
            default:  abort ();                 break;
        }
    } while (next_option != -1);

    pwm     = new PWM(0x00010000, verbose);

    /* parse command line arguments and start processing */
    for (i=optind; i<argc; i++) {

        /* single map processing */
        if      (strcmp(argv[i], "map")==0) {

            if (verbose > 1)
                printf("PWMCLI : processing map\n");

            pwm->setMap(strtol(argv[i+1],NULL,10), strtol(argv[i+2],NULL,10));

            i = i + 2;
        }
        
        /* complete map processing */
        else if (strcmp(argv[i], "mapall")==0) {

            if (verbose > 1)
                printf("PWMCLI : processing mapall\n");

            fp = fopen(argfile, "r");
            if (fp==NULL) {
                fprintf(stderr,"ERROR : CANNOT OPEN FILE : %s\n",argfile);
                exit(1);
            }

            int j=0;
            while ((!feof(fp)) && (j<24)) {
                if (fgets(fbuf, 255, fp)!=NULL) {
                    map_tbl[j] = strtol(fbuf,NULL,10);
                    j++;
                }
            }
            fclose(fp);

            pwm->setMap(map_tbl);
        }
        
        /* enable */
        else if (strcmp(argv[i], "enable")==0) {

            if (verbose > 1)
                printf("PWMCLI : processing enable\n");

            pwm->enable();
        }
        
        /* disable */
        else if (strcmp(argv[i], "disable")==0) {

            if (verbose > 1)
                printf("PWMCLI : processing disable\n");

            pwm->disable();
        }
        
        /* single set pwm processing*/
        else if (strcmp(argv[i], "set")==0) {
            if (verbose > 1)
                printf("PWMCLI : processing set\n");

            (fmt_int) ?
                pwm->setValue(strtol(argv[i+1],NULL,10), strtoul(argv[i+2],NULL,10)) :
                pwm->setDuty (strtol(argv[i+1],NULL,10), strtof (argv[i+2],NULL   ));

            i = i + 2;
        }
        
        /* complete pwm processing */
        else if (strcmp(argv[i], "setall")==0) {
            if (verbose > 1)
                printf("PWMCLI : processing setall\n");

            fp = fopen(argfile, "r");
            if (fp==NULL) {
                fprintf(stderr,"ERROR : CANNOT OPEN FILE : %s\n",argfile);
                exit(1);
            }

            int j=0;
            while ((!feof(fp)) && (j<24)) {
                if (fgets(fbuf, 255, fp)!=NULL) {
                    (fmt_int) ?
                        pwm_int[j] = strtol(fbuf,NULL,10) :
                        pwm_per[j] = strtof(fbuf,NULL   );
                    j++;
                }
            }
            fclose(fp);

            (fmt_int) ? pwm->setValue(pwm_int) : pwm->setDuty(pwm_per);
        }

        /* complete pwm processing */
        else if (strcmp(argv[i], "zeroall")==0) {

            if (verbose > 1)
                printf("PWMCLI : processing zeroall\n");

            for (i=0; i<24; i++) pwm->setDuty(i, 0.0);
        }
        
        /* unrecognized command */
        else { 
            break; 
        }
    }

    return (0);
}


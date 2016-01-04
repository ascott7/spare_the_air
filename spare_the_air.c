/*  \file spare_the_air.c
 *
 *  \author Andrew Scott
 *  \brief Runs a python script to determine whether the current day is a spare
 *         the air day (see http://www.sparetheair.org) and then lights up
 *         a green LED to indicate no spare the air alert or a red LED to
 *         indicate an alert. Updates the status of the LEDs every hour.
 *
 *  \note This file will light up a yellow LED if it unexpectedly is not able
 *        to determine whether the current day is a spare the air day or not.
 */

#include <math.h>
//#include <signal.h>       // for catching ctrl-c
#include <stdio.h>        // for printing to the console
#include "pi_helpers.h"   // for talking to the Pi

#define REDPIN 17
#define GREENPIN 23
#define YELLOWPIN 21

void check_status()
{
    FILE *fp;
    char response[1035];

    /* Open the command for reading. */
    fp = popen("python spare_request.py", "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }

    if (fgets(response, sizeof(response)-1, fp) == NULL) {
        printf("Didn't get response from python script");
        //digital_write(GREENPIN, 0);
        //digital_write(YELLOWPIN, 1);
        //digital_write(REDPIN, 0);
        pclose(fp);
        exit(2);
    }
    
    if (response == "ALL CLEAR") {
        //digital_write(GREENPIN, 1);
        //digital_write(YELLOWPIN, 0);
        //digital_write(REDPIN, 0);
    }

    else if (response == "ALERT") {
        //digital_write(GREENPIN, 0);
        //digital_write(YELLOWPIN, 0);
        //digital_write(REDPIN, 1);
    }

    else {
        //digital_write(GREENPIN, 0);
        //digital_write(YELLOWPIN, 1);
        //digital_write(REDPIN, 0);
    }
    /* close */
    pclose(fp);

}

int main(int argc, char* argv[])
{
    /*pio_init();
    pin_mode(REDPIN, OUTPUT);
    pin_mode(GREENPIN, OUTPUT);
    pin_mode(YELLOWPIN, OUTPUT);
    */
    return 0;
}

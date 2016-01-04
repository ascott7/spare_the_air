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

#define _BSD_SOURCE

#include "pi_helpers.h"   // for talking to the Pi
#include <stdio.h>        // for printing to the console
#include <stdlib.h>
#include <string.h>       // for strcmp

#define REDPIN 17
#define GREENPIN 23
#define YELLOWPIN 21

void update_leds(int red, int green, int yellow)
{
    digital_write(REDPIN, red);
    digital_write(GREENPIN, green);
    digital_write(YELLOWPIN, yellow);
}

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
        update_leds(0, 0, 1);
        pclose(fp);
        exit(2);
    }
    
    if (strcmp(response, "ALL CLEAR\n") == 0) {
        update_leds(0, 1, 0);
    }
    else if (strcmp(response, "ALERT\n") == 0) {
        update_leds(1, 0, 0);
    }
    else {
        update_leds(0, 0, 1);
        printf("weird response from python, got %s\n", response);
    }
    pclose(fp);
}

int main()
{
    pio_init();
    timer_init();
    pin_mode(REDPIN, OUTPUT);
    pin_mode(GREENPIN, OUTPUT);
    pin_mode(YELLOWPIN, OUTPUT);

    while(1) {
        check_status();
        //update_leds(0, 0, 0);
        sleep_millis(21600 * 1000);
    }
    return 0;
}

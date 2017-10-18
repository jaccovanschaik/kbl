/*
 * kbl.c: Set keyboard backlight on an ASUS UX301L notebook.
 *
 * Copyright:	(c) 2015 Jacco van Schaik (jacco@jaccovanschaik.net)
 * Version:	$Id: kbl.c 822 2017-10-18 17:55:05Z jacco $
 *
 * This software is distributed under the terms of the MIT license. See
 * http://www.opensource.org/licenses/mit-license.php for details.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BACKLIGHT_FILE "/sys/class/leds/asus::kbd_backlight/brightness"

#define MIN(x, a) (((x) < (a)) ? (x) : (a))
#define MAX(x, a) (((x) > (a)) ? (x) : (a))

#define CLAMP(x, lower, upper) MAX(MIN((x), (upper)), (lower))

/* Show usage. */
void usage(const char *argv0, int exit_code)
{
    fprintf(stderr, "Set keyboard backlight.\n");
    fprintf(stderr, "Usage: %s <brightness>\n", argv0);
    fprintf(stderr, "<brightness> may be:\n");
    fprintf(stderr, "\t0-3\tdirectly set the keyboard brightness\n");
    fprintf(stderr, "\t--\tdecrease the brightness by one step\n");
    fprintf(stderr, "\t++\tincrease the brightness by one step\n");

    exit(exit_code);
}

int main(int argc, char *argv[])
{
    FILE *fp;
    int brightness;
    char *endptr;

    if (argc == 1) {
        usage(argv[0], 0);
    }
    else if ((fp = fopen(BACKLIGHT_FILE, "r+")) == NULL) {
        perror(BACKLIGHT_FILE);
        return 1;
    }
    else if (fscanf(fp, "%d", &brightness) != 1) {
        fprintf(stderr, "Could not read %s\n", BACKLIGHT_FILE);
        return 1;
    }
    else if (strcmp(argv[1], "--") == 0) {
        brightness = CLAMP(brightness - 1, 0, 3);
    }
    else if (strcmp(argv[1], "++") == 0) {
        brightness = CLAMP(brightness + 1, 0, 3);
    }
    else {
        brightness = strtol(argv[1], &endptr, 10);

        if (endptr != argv[1] + 1 || brightness  < 0 || brightness > 3) {
            fprintf(stderr, "Bad brightness value\n");
            usage(argv[0], 1);
        }
    }

    rewind(fp);

    fprintf(fp, "%d\n", brightness);

    fclose(fp);

    return 0;
}

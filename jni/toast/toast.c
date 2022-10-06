#include <assert.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "json/osd_config.h"
#include "util/time_util.h"

#define DATASIZE 20
#define TOP_ROW 5
#define BOTTOM_ROW 8

#define TOAST_DISABLE_KEY "hide_diagnostics"

#include <stdbool.h>

int toast_enabled = 1;
typedef struct ToastItem
{
    char data[DATASIZE];
    struct timespec shown;
    struct ToastItem *nextNode;
} ToastItem;

ToastItem *bottomStackPointer = NULL;
ToastItem *topStackPointer = NULL;

struct timespec now, lasttoastremoval;

void toast_load_config()
{
    if (get_boolean_config_value(TOAST_DISABLE_KEY))
    {
        toast_enabled = 0;
    }
}

int toast_pop()
{
    if (bottomStackPointer == NULL)
        return 0;

    char data[DATASIZE];
    strcpy(data, bottomStackPointer->data);
    bottomStackPointer->shown = (struct timespec){0, 0};
    ToastItem *TempPointer = bottomStackPointer;
    bottomStackPointer = bottomStackPointer->nextNode;
    free(TempPointer);
    if (bottomStackPointer == NULL)
        topStackPointer = NULL;
    return 1;
}

int toast(char *data, ...)
{
    if (!toast_enabled) {
        return 0;
    }
    ToastItem *TempPointer = malloc(sizeof(ToastItem));
    if (TempPointer == NULL)
        return 0;

    // printf
    va_list va;
    va_start(va, data);
    char copy[DATASIZE];
    vsnprintf(copy, DATASIZE, data, va);

    // our fonts are caps only....
    for (int i = 0; copy[i]; i++)
    {
        copy[i] = toupper(copy[i]);
    }

    strncpy(TempPointer->data, copy, DATASIZE);
    TempPointer->shown = (struct timespec){0, 0};
    TempPointer->nextNode = NULL;
    if (bottomStackPointer == NULL)
        bottomStackPointer = TempPointer;
    else
        topStackPointer->nextNode = TempPointer;
    topStackPointer = TempPointer;
    return 1;
}

void do_toast(void (*display_print_string)(uint8_t init_x, uint8_t y, const char *string, uint8_t len))
{
    if (!toast_enabled) {
        return;
    }

    int numberoffNodes = 0;

    clock_gettime(CLOCK_MONOTONIC, &now);

    // if the last item has been up 3 seconds; chop it
    // but only remove 1 per second
    ToastItem *TempPointer = bottomStackPointer;
    if (
        timespec_subtract_ns(&now, &lasttoastremoval) > NSEC_PER_SEC                      // 1ce per second limit
        && TempPointer != NULL && TempPointer->shown.tv_sec > 0                           // guards
        && timespec_subtract_ns(&now, &TempPointer->shown) > ((uint64_t)NSEC_PER_SEC * 3) // item has been on screen for long enough
    )
    {
        clock_gettime(CLOCK_MONOTONIC, &lasttoastremoval);
        TempPointer = TempPointer->nextNode;
        toast_pop();
    }

    // loop and display
    for (int row = BOTTOM_ROW; row >= TOP_ROW; row--)
    {
        // if we ran out of items blank out the rest of our rows
        if (TempPointer == NULL) {
            char empty[DATASIZE] = {0};
            display_print_string(0, row, empty, DATASIZE);
        } else {

            // set shown time if not set (ie: item not yet shown)
            if (TempPointer->shown.tv_sec == 0)
            {
                clock_gettime(CLOCK_MONOTONIC, &TempPointer->shown);
            }

            // draw the current item in the current row
            display_print_string(0, row, TempPointer->data, DATASIZE);
            TempPointer = TempPointer->nextNode;
        }
    };

    return;
}

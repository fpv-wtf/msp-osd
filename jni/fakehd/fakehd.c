#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "json/osd_config.h"

#define FAKEHD_ENABLE_KEY "fakehd_enable"
#define FAKEHD_LOCK_CENTER_KEY "fakehd_lock_center"
#define FAKEHD_HIDE_THROTTLE_KEY "fakehd_hide_throttle_element" // for compat
#define FAKEHD_MENU_SWITCH_KEY "fakehd_menu_switch"
#define FAKEHD_HIDE_MENU_SWITCH_KEY "fakehd_hide_menu_switch" // for compat
#define FAKEHD_LAYOUT_DEBUG_KEY "fakehd_layout_debug"
#define FAKEHD_COLUMNS_KEY "fakehd_columns"
#define FAKEHD_ROWS_KEY "fakehd_rows"

#define INPUT_ROWS 16
#define INPUT_COLS 30

int fakehd_enabled = 0;
static int fakehd_hide_menu_switch = 0;
static int fakehd_lock_center = 0;
static int fakehd_layout_debug = 0;
static int fakehd_menu_switch_char = 4; // betaflight throttle icon
static int fakehd_trigger_x = 99;
static int fakehd_trigger_y = 99;
static char fakehd_columns = 'S';
static char fakehd_rows[INPUT_COLS] = "WWWWWWCCWWWWWWWD";

#ifdef DEBUG
#define DEBUG_PRINT(fmt, args...) fprintf(stderr, fmt, ##args)
#else
#define DEBUG_PRINT(fmt, args...)
#endif

void load_fakehd_config()
{
    DEBUG_PRINT("checking for fakehd enabled\n");
    if (get_boolean_config_value(FAKEHD_ENABLE_KEY))
    {
        DEBUG_PRINT("fakehd enabled\n");
        fakehd_enabled = 1;
    }
    else
    {
        DEBUG_PRINT("fakehd disabled\n");
    }

    DEBUG_PRINT("checking for fakehd layout debug\n");
    if (get_boolean_config_value(FAKEHD_LAYOUT_DEBUG_KEY))
    {
        DEBUG_PRINT("fakehd layout debug\n");
        fakehd_layout_debug = 1;
    }
    else
    {
        DEBUG_PRINT("fakehd layout debug off\n");
    }

    DEBUG_PRINT("checking for fakehd hide throttle \n");
    if (get_boolean_config_value(FAKEHD_HIDE_MENU_SWITCH_KEY))
    {
        DEBUG_PRINT("fakehd hide throttle\n");
        fakehd_hide_menu_switch = 1;
    }
    else
    {
        DEBUG_PRINT("fakehd no hide throttle\n");
    }
    DEBUG_PRINT("checking for fakehd lock center \n");
    if (get_boolean_config_value(FAKEHD_LOCK_CENTER_KEY))
    {
        DEBUG_PRINT("fakehd lock center\n");
        fakehd_lock_center = 1;
    }
    else
    {
        DEBUG_PRINT("fakehd no lock center\n");
    }

    int trigger = get_integer_config_value(FAKEHD_MENU_SWITCH_KEY);
    if (trigger)
    {
        DEBUG_PRINT("fakehd found custom trigger\n");
        fakehd_menu_switch_char = trigger;
    }
    // trigger
    // rows
    const char * rows = get_string_config_value(FAKEHD_ROWS_KEY);
    if (rows) {
        DEBUG_PRINT("fakehd found custom row conf\n");
        memcpy(fakehd_rows, rows, INPUT_COLS);
    }

    const char * cols = get_string_config_value(FAKEHD_COLUMNS_KEY);
    if (cols)
    {
        DEBUG_PRINT("fakehd found col conf\n");
        fakehd_columns = cols[0];
    }
    DEBUG_PRINT("fakehd finished config init\n");
}

static void fakehd_get_column_config(int cols[INPUT_ROWS])
{
    switch (fakehd_columns)
    {
    case 'T':
        memcpy(cols, (int[]){0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}, sizeof(cols[0]) * INPUT_ROWS);
        break;
    case 'M':
        memcpy(cols, (int[]){3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}, sizeof(cols[0]) * INPUT_ROWS);
        break;
    case 'B':
        memcpy(cols, (int[]){6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21}, sizeof(cols[0]) * INPUT_ROWS);
        break;
    case 'S':
    default:
        memcpy(cols, (int[]){0, 1, 2, 3, 4, 8, 9, 10, 11, 12, 16, 17, 18, 19, 20, 21}, sizeof(cols[0]) * INPUT_ROWS);
        break;
    }

    // If more flexibility needed / when config allows - I suggest the 'default' switch block is separated
    // and used to lookup the mapping from the config file, letting the user define extras?

}

static void fakehd_get_row_config(int rownum, int row[INPUT_COLS])
{
    char rowmode = fakehd_rows[rownum];
    switch (rowmode)
    {
    case 'L':
        memcpy(row, (int[]){0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29}, sizeof(row[0]) * INPUT_COLS);
        break;
    case 'C':
        memcpy(row, (int[]){15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44}, sizeof(row[0]) * INPUT_COLS);
        break;
    case 'R':
        memcpy(row, (int[]){30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59}, sizeof(row[0]) * INPUT_COLS);
        break;
    case 'T':
        memcpy(row, (int[]){0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59}, sizeof(row[0]) * INPUT_COLS);
        break;
    case 'F':
        memcpy(row, (int[]){10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49}, sizeof(row[0]) * INPUT_COLS);
        break;
    case 'D':
        memcpy(row, (int[]){12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41}, sizeof(row[0]) * INPUT_COLS);
        break;
    case 'W':
    default:
        memcpy(row, (int[]){0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59}, sizeof(row[0]) * INPUT_COLS);
        break;
    }

    // If more flexibility needed / when config allows - I suggest the 'default' switch block is separated
    // and used to lookup the mapping from the config file, letting the user define extras?
}


// when possible, this should be called on reconnect. it will do what's needed to put fakehd back
// into fresh booted state
void fakehd_reset() {
    // clear saved centering trigger position
    int fakehd_trigger_x = 99;
    int fakehd_trigger_y = 99;
}

void fakehd_enable()
{
    fakehd_enabled = 1;
}

void fakehd_disable()
{
    fakehd_enabled = 0;
    fakehd_reset();
}

int fakehd_is_enabled() {
    return fakehd_enabled;
}

void fakehd_map_sd_character_map_to_hd(uint16_t sd_character_map[60][22], uint16_t hd_character_map[60][22])
{
    int row[INPUT_COLS];
    int col[INPUT_ROWS];

    fakehd_get_column_config(col);

    int render_x = 0;
    int render_y = 0;
    for (int y = INPUT_ROWS-1; y >= 0; y--)
    {
        fakehd_get_row_config(y, row);
        for (int x = INPUT_COLS-1; x >= 0; x--)
        {
            // to visualise the layout better in dev
            if (fakehd_layout_debug && sd_character_map[x][y] == 0) {
                sd_character_map[x][y] = 48 + (x % 10);
            }

            // skip if it's not a character
            if (sd_character_map[x][y] != 0)
            {
                // if current element is fly min or throttle icon
                // record the current position as the 'trigger' position
                if (fakehd_trigger_x == 99 &&
                    (sd_character_map[x][y] == 0x9c // fly minutes icon (armed time)
                     ||
                     sd_character_map[x][y] == fakehd_menu_switch_char
                     ))
                {
                    DEBUG_PRINT("found fakehd triggger \n");
                    fakehd_trigger_x = x;
                    fakehd_trigger_y = y;
                }

                // if we have seen a trigger (see above) - and it's now gone, switch to centering
                // this is intented to center the menu + postflight stats, which don't contain
                // timer/battery symbols
                if (
                    fakehd_lock_center ||
                    (fakehd_trigger_x != 99 &&
                     sd_character_map[fakehd_trigger_x][fakehd_trigger_y] != 0x9c &&
                     sd_character_map[fakehd_trigger_x][fakehd_trigger_y] != fakehd_menu_switch_char))
                {
                    render_x = x + 15;
                    render_y = y + 3;
                }
                else
                {
                    render_y = col[y];
                    render_x = row[x];
                }
                // 0 out the throttle element if configured to do so
                // and also the three adjacent positions where the thottle percent will be
                if (fakehd_trigger_x != 99 &&
                    fakehd_hide_menu_switch &&
                    sd_character_map[x][y] == fakehd_menu_switch_char)
                {
                    hd_character_map[render_x][render_y] = 0;
                    (render_x <= 57) && (hd_character_map[render_x + 1][render_y] = 0);
                    (render_x <= 56) && (hd_character_map[render_x + 2][render_y] = 0);
                    (render_x <= 55) && (hd_character_map[render_x + 3][render_y] = 0);
                    (render_x <= 54) && (hd_character_map[render_x + 4][render_y] = 0);
                    (render_x <= 53) && (hd_character_map[render_x + 5][render_y] = 0);
                }
                else
                {
                    // otherwise, the normal path
                    hd_character_map[render_x][render_y] = sd_character_map[x][y];
                }
            }
        }
    }
}

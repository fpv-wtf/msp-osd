#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>

#include <SFML/Graphics.h>
#include <SFML/Window.h>

#include "msp.h"
#include "msp_displayport.h"

#define OSD_WIDTH 31
#define OSD_HEIGHT 16

#define X_OFFSET 180

#define SERIAL_PORT "/dev/tty.usbserial-A10K6NWF"

#define SERVER "10.211.55.4"
#define PORT 5762

#define WIDTH 1440
#define HEIGHT 810

#define FONT_WIDTH 36
#define FONT_HEIGHT 54

sfTexture *font;
sfRenderWindow *window;
uint8_t character_map[OSD_WIDTH][OSD_HEIGHT];
displayport_vtable_t *display_driver;

void draw_character(uint32_t x, uint32_t y, uint8_t c)
{
    if (x > OSD_WIDTH - 1 || y > OSD_HEIGHT - 1)
    {
        return;
    }
    character_map[x][y] = c;
}

void draw_screen()
{
    sfRenderWindow_clear(window, sfColor_fromRGB(55, 55, 55));
    for (int y = 0; y < OSD_HEIGHT; y++)
    {
        for (int x = 0; x < OSD_WIDTH; x++)
        {
            uint8_t c = character_map[x][y];
            if (c != 0)
            {
                printf("%c", c > 31 ? c : 20);
                sfIntRect r = {0, FONT_HEIGHT * c, FONT_WIDTH, FONT_HEIGHT};
                sfVector2f dest = {(x * FONT_WIDTH) + X_OFFSET, y * FONT_HEIGHT};
                sfSprite *sprite = sfSprite_create();
                sfSprite_setTexture(sprite, font, 0);
                sfSprite_setTextureRect(sprite, r);
                sfSprite_setPosition(sprite, dest);
                sfRenderWindow_drawSprite(window, sprite, NULL);
                sfSprite_destroy(sprite);
            }
            printf(" ");
        }
        printf("\n");
    }
}

void clear_screen()
{
    printf("clear\n");
    memset(character_map, 0, sizeof(character_map));
}

void draw_complete()
{
    sfRenderWindow_display(window);
    printf("draw complete!\n");
}

void msp_callback(msp_msg_t *msp_message)
{
    displayport_process_message(display_driver, msp_message);
    draw_screen();
}

int connect_to_server(char *address)
{
    int sockfd, connfd;
    struct sockaddr_in servaddr;

    // socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        printf("socket failed!\n");
        exit(0);
    }
    else
        printf("socket created!\n");

    bzero(&servaddr, sizeof(servaddr));

    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(address);
    servaddr.sin_port = htons(PORT);

    if (connect(sockfd, &servaddr, sizeof(servaddr)) != 0)
    {
        printf("connection failed!\n");
        exit(0);
    }
    else
        printf("connected!\n");
    fcntl(sockfd, F_SETFL, O_NONBLOCK);
    return sockfd;
}

int open_serial_port(const char *device)
{
    struct termios tio;
    struct termios stdio;
    int tty_fd;
    fd_set rdset;

    memset(&stdio, 0, sizeof(stdio));
    stdio.c_iflag = 0;
    stdio.c_oflag = 0;
    stdio.c_cflag = 0;
    stdio.c_lflag = 0;
    stdio.c_cc[VMIN] = 1;
    stdio.c_cc[VTIME] = 0;
    tcsetattr(STDOUT_FILENO, TCSANOW, &stdio);
    tcsetattr(STDOUT_FILENO, TCSAFLUSH, &stdio);
    fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);

    memset(&tio, 0, sizeof(tio));
    tio.c_iflag = 0;
    tio.c_oflag = 0;
    tio.c_cflag = CS8 | CREAD | CLOCAL; 
    tio.c_lflag = 0;
    tio.c_cc[VMIN] = 1;
    tio.c_cc[VTIME] = 0;

    tty_fd = open(device, O_RDWR | O_NONBLOCK); 
    cfsetospeed(&tio, B115200);               
    cfsetispeed(&tio, B115200);                
    tcsetattr(tty_fd, TCSANOW, &tio);
    return tty_fd;
}

int main(int argc, char *args[])
{
    memset(character_map, 0, sizeof(character_map));
    sfVideoMode videoMode = {1440, 810, 32};
    window = sfRenderWindow_create(videoMode, "MSP OSD", 0, NULL);
    sfRenderWindow_display(window);
    font = sfTexture_createFromFile("bold.png", NULL);

    display_driver = calloc(1, sizeof(displayport_vtable_t));
    display_driver->draw_character = &draw_character;
    display_driver->clear_screen = &clear_screen;
    display_driver->draw_complete = &draw_complete;

    msp_state_t *msp_state = calloc(1, sizeof(msp_state_t));
    msp_state->cb = &msp_callback;

    // int socket_fd = connect_to_server(SERVER);
    //FILE *socket_fd = fopen("msp_sample.bin", "r");
    int socket_fd = open_serial_port(SERIAL_PORT);
    uint8_t quit = 0;
    while (!quit)
    {
        sfEvent event;
        sfRenderWindow_pollEvent(window, &event);

        // Close window: exit
        if (event.type == sfEvtMouseButtonReleased)
        {
            sfRenderWindow_close(window);
            quit = 1;
        }

        uint8_t byte = 0;
        if (read(socket_fd, &byte, 1) > 0)
            msp_process_data(msp_state, byte);
        usleep(100);
    }
    sfTexture_destroy(font);
    sfRenderWindow_destroy(window);
    free(msp_state);
    free(display_driver);
    return 0;
}
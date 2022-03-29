#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

#include <SFML/Graphics.h>
#include <SFML/Window.h>

#include "msp.h"
#include "msp_displayport.h"

sfTexture *font;
sfRenderWindow *window;

#define SERVER "10.211.55.4"
#define PORT 5762

#define WIDTH 1440
#define HEIGHT 810

void draw_character(uint32_t x, uint32_t y, uint8_t c)
{
    sfIntRect r = {0, FONT_HEIGHT * c, FONT_WIDTH, FONT_HEIGHT};
    sfVector2f dest = {x, y};
    sfSprite *sprite = sfSprite_create();
    sfSprite_setTexture(sprite, font, 0);
    sfSprite_setTextureRect(sprite, r);
    sfSprite_setPosition(sprite, dest);
    sfRenderWindow_drawSprite(window, sprite, NULL);
    sfSprite_destroy(sprite);
}

void clear_screen()
{
    printf("clear\n");
    sfColor black = {0,0,0,0};
    sfRenderWindow_clear(window, black);
}

void draw_complete() {
    printf("draw complete!\n");
    sfRenderWindow_display(window);
}

void msp_callback(msp_msg_t *msp_message)
{
    displayport_process_message(msp_message);
}

int connect_to_server(char *address)
{
    int sockfd, connfd;
    struct sockaddr_in servaddr, cli;

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

int main(int argc, char *args[])
{
    sfVideoMode videoMode = {1440, 810, 32};
    window = sfRenderWindow_create(videoMode, "MSP OSD", 0, NULL);
    font = sfTexture_createFromFile("bold.png", NULL);
    
    displayport_vtable_t *displayport_vtable = calloc(1, sizeof(displayport_vtable_t));
    displayport_vtable->draw_character = &draw_character;
    displayport_vtable->clear_screen = &clear_screen;
    displayport_vtable->draw_complete = &draw_complete;
    set_display_driver(displayport_vtable);
    int socket_fd = connect_to_server(SERVER);

    msp_state_t *msp_state = calloc(1, sizeof(msp_state_t));
    msp_state->cb = &msp_callback;

    uint8_t quit = 0;
    while (sfRenderWindow_isOpen(window))
    {
        sfEvent event;
        sfRenderWindow_pollEvent(window, &event);

        // Close window: exit
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(window);
        
        uint8_t byte = 0;
        if (read(socket_fd, &byte, 1) > 0)
            msp_process_data(msp_state, byte);
    }
    sfTexture_destroy(font);
    sfRenderWindow_destroy(window);
    free(msp_state);
    free(displayport_vtable);
    return 0;
}
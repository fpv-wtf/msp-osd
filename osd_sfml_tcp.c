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

#define OSD_WIDTH 30
#define OSD_HEIGHT 16

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
    if (x > OSD_WIDTH || y > OSD_HEIGHT) {
        return;
    }
    character_map[x][y] = c;
}

void draw_screen() {
    sfRenderWindow_clear(window, sfColor_fromRGB(55,55,55));
    for(int y = 0; y < OSD_HEIGHT; y++) {
        for(int x = 0; x < OSD_WIDTH; x++) {
            uint8_t c = character_map[x][y];
            if (c != 0) {
                printf("%c", c > 31 ? c : 20);
                sfIntRect r = {0, FONT_HEIGHT * c, FONT_WIDTH, FONT_HEIGHT};
                sfVector2f dest = {x * FONT_WIDTH, y * FONT_HEIGHT};
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
    sfRenderWindow_display(window);
}

void clear_screen()
{
    printf("clear\n");
    memset(character_map, 0, sizeof(character_map));
}

void draw_complete() {
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
    
    //int socket_fd = connect_to_server(SERVER);
    FILE *socket_fd = fopen("msp_sample.bin", "r");

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
        if (fread(&byte, 1, 1, socket_fd) > 0)
            msp_process_data(msp_state, byte);
        usleep(100);
    }
    sfTexture_destroy(font);
    sfRenderWindow_destroy(window);
    free(msp_state);
    free(display_driver);
    return 0;
}

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "gui.h"
#include "SDL.h"

#define COMMAND_W 48
#define COMMAND_H 17
#define X_PAD 10
#define Y_PAD 2


#define COMMAND_LINE_SPACING 10

enum MEM_FIELD_ENUM
{
    MEM_F0,  // Current size of Command Buffer
    MEM_F1,  // Command Buffer 
    MEM_FIELD_MAX
};

char message[80];


void wx_command_draw(widget_info *data);
void wx_fx_mouse_button_down_command(widget_info *wx_info);
void wx_fx_command_mouse_wheel(widget_info *wx_info);
void wx_fx_command_key_pressed(widget_info *wx_info);

void wx_command_initialize(widget_info *wx_info);

#define MAX_COMMAND_BUFFER_SIZE 4

int border_color;
char command_buffer[MAX_COMMAND_BUFFER_SIZE + 1];
int  command_buffer_index;
int key_is_pressed;


widget wx_command_create(int x, int y)
{
    widget command;

    command.data.rect.x = x;
    command.data.rect.y = y;
    command.data.rect.w = COMMAND_W;
    command.data.rect.h = COMMAND_H;

    command.data.selected = 0;
    
    command.fx.fx_update = wx_fx_none;
    command.fx.fx_draw = wx_command_draw;
    command.fx.fx_mouse_motion = wx_check_bounds;
    command.fx.fx_mouse_wheel = wx_fx_command_mouse_wheel;
    command.fx.fx_key_pressed = wx_fx_command_key_pressed;
    command.fx.fx_mouse_button_down = wx_fx_mouse_button_down_command;


    wx_command_initialize(&command.data);

    return command; 

}


void wx_command_initialize(widget_info *wx_info)
{
    key_is_pressed = false;
    
    for (int i=0; i<MAX_COMMAND_BUFFER_SIZE; i++)
        command_buffer[i] = '\0';

    command_buffer_index = 0;
    

}

void wx_command_draw(widget_info *wx_info)
{

    SDL_Rect command_bg_rect, command_fg_rect;

    int msg_x, msg_y; 

    command_fg_rect.x = wx_info->rect.x;
    command_fg_rect.y = wx_info->rect.y;
    command_fg_rect.w = COMMAND_W;
    command_fg_rect.h = COMMAND_H;

    command_bg_rect.x = command_fg_rect.x - 1;
    command_bg_rect.y = command_fg_rect.y - 1;
    command_bg_rect.w = command_fg_rect.w + 2;
    command_bg_rect.h = command_fg_rect.h + 2;


    SetRenderDrawColor(COLOR_FOREGROUND);

    SDL_RenderDrawRect(renderer, &command_bg_rect);
    
    SetRenderDrawColor(COLOR_BACKGROUND);

    if (key_is_pressed)
    {
        if (command_buffer_index == MAX_COMMAND_BUFFER_SIZE)
            SetRenderDrawColor(COLOR_TERTIARY);
        else
            SetRenderDrawColor(COLOR_SECONDARY);
    }

    SDL_RenderFillRect(renderer, &command_fg_rect);

    write_text(command_buffer, wx_x(wx_info) + X_PAD, wx_y(wx_info) + Y_PAD, COLOR_FOREGROUND);
    
    msg_x = wx_x(wx_info) + wx_w(wx_info) + 15;
    msg_y = wx_y(wx_info) + Y_PAD;
    
    write_text(message, msg_x, msg_y, COLOR_FOREGROUND);
    

}


void wx_fx_command_mouse_wheel(widget_info *wx_info)
{

}



void wx_fx_mouse_button_down_command(widget_info *wx_info)
{
    // wx_fx_mouse_button_down_select(wx_info);
}

void wx_fx_command_process_buffer(widget_info *wx_info)
{
    char drum = command_buffer[0];

    switch(drum)
    {
        
        case 'H':
            strcpy(message, "Hi-Hatt added (1/4)");
            break;

        case 'S':
            strcpy(message, "Snare added (1/4)");
            break;

        case 'K':
            strcpy(message, "Kick added (1/4)");
            break;

        case 'R':
            strcpy(message, "Ride added (1/4)");
            break;

        case 'T':
            strcpy(message, "Rack Tom added (1/4)");
            break;
        
        case 'F':
            strcpy(message, "Floor Tom added (1/4)");
            break;
        
        case 'P':
            strcpy(message, "Rest added (1/4)");
            break;

    }
    
    for (int i=0; i<MAX_COMMAND_BUFFER_SIZE; i++)
        command_buffer[i] = '\0';

    command_buffer_index = 0;
}

void wx_fx_command_key_pressed(widget_info *wx_info)
{

    if (gui_key_down_pending)
    {
        printf("key down: %c\n", key_char);
        
        key_is_pressed = true;
        
        if ((key_char >= 'a') && (command_buffer_index == 0))
            key_char = toupper(key_char);

        if (command_buffer_index < (MAX_COMMAND_BUFFER_SIZE))
            command_buffer[command_buffer_index++] = key_char;

        if (key_char == SDLK_RETURN)
            wx_fx_command_process_buffer(wx_info);

        else if (key_char == SDLK_ESCAPE)
        {
            command_buffer_index = 0;
            for (int i=0; i<MAX_COMMAND_BUFFER_SIZE; i++)
                command_buffer[i] = '\0';

        }
         
    }




    if (gui_key_up_pending)
    {
        key_is_pressed = false;
        // printf("key up: %c\n", key_char);
    }

}



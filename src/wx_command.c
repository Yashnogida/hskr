
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
int message_color;

void wx_command_draw(widget_info *data);
void wx_fx_mouse_button_down_command(widget_info *wx_info);
void wx_fx_command_mouse_wheel(widget_info *wx_info);
void wx_fx_command_key_pressed(widget_info *wx_info);

void wx_command_initialize(widget_info *wx_info);

int check_valid_drum(char key_char);
void set_message(char *str, int color);
void clear_command_buffer();

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

    const int msg_x = wx_x(wx_info) + wx_w(wx_info) + 15;
    const int msg_y = wx_y(wx_info) + Y_PAD;

    wx_draw_frame(wx_info, COLOR_FOREGROUND, COLOR_WHITE);

    if (key_is_pressed)
            wx_draw_frame(wx_info, COLOR_FOREGROUND, COLOR_SECONDARY);

    write_text(command_buffer, wx_x(wx_info) + X_PAD, wx_y(wx_info) + Y_PAD, COLOR_FOREGROUND);
        
    write_text(message, msg_x, msg_y, message_color);
    

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
    printf("%x\n", drum);

    switch(drum)
    {
        
        case 'H':
            set_message("Hi-Hatt added (1/8)", COLOR_FOREGROUND);
            break;

        case 'S':
            set_message("Snare added (1/8)", COLOR_FOREGROUND);
            break;

        case 'K':
            set_message("Kick added (1/8)", COLOR_FOREGROUND);
            break;

        case 'R':
            set_message("Ride added (1/8)", COLOR_FOREGROUND);
            break;

        case 'T':
            set_message("Rack Tom added (1/8)", COLOR_FOREGROUND);
            break;
        
        case 'F':
            set_message("Floor Tom added (1/8)", COLOR_FOREGROUND);
            break;
        
        case 'P':
            set_message("Rest added (1/8)", COLOR_FOREGROUND);
            break;
        
        default:
            set_message("Invalid Command", COLOR_TERTIARY);
            break;
            
    }
    
    clear_command_buffer();

}

void wx_fx_command_key_pressed(widget_info *wx_info)
{

    if (gui_key_down_pending)
    {
        // printf("key down: %c\n", key_char);
        
        key_is_pressed = true;

        key_char = toupper(key_char);
        
        if ((command_buffer_index == 0))
        {
            set_message("", COLOR_FOREGROUND);


            if (isalpha(key_char) && check_valid_drum(key_char))
                command_buffer[command_buffer_index] = key_char;

            else
                set_message("First entry must be H, S, K, R, T, F, P", COLOR_FOREGROUND);
        }

        else if (command_buffer_index == 1)
        {
        }
    
        if (command_buffer_index < (MAX_COMMAND_BUFFER_SIZE))
            command_buffer[command_buffer_index++] = key_char;
         

        if (key_char == SDLK_ESCAPE)
            clear_command_buffer();
        
        if (key_char == SDLK_BACKSPACE)
        {
            command_buffer[command_buffer_index] = '\0';
            command_buffer_index -= 1;
        }

        if (key_char == SDLK_RETURN)
            wx_fx_command_process_buffer(wx_info);
    }
            


    if (gui_key_up_pending)
    {
        key_is_pressed = false;
        // printf("key up: %c\n", key_char);
    }

}



// Utility Functions

int check_valid_drum(char key_char)
{
    switch(key_char)
    {
         case 'H':
            return 1;

        case 'S':
            return 1;

        case 'K':
            return 1;

        case 'R':
            return 1;

        case 'T':
            return 1;

        case 'F':
            return 1;

        case 'P':
            return 1;
        
        default:
            return 0;

    }
   
}

void clear_command_buffer()
{
    for (int i=0; i<MAX_COMMAND_BUFFER_SIZE; i++)
        command_buffer[i] = '\0';

    command_buffer_index = 0;

}

void set_message(char *str, int color)
{
    message_color = color;
    strcpy(message, str);
}


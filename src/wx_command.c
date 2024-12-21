
#include <stdlib.h>
#include <stdio.h>
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


void wx_command_draw(widget_info *data);
void wx_fx_mouse_button_down_command(widget_info *wx_info);
void wx_fx_command_mouse_wheel(widget_info *wx_info);
void wx_fx_command_key_pressed(widget_info *wx_info);

#define MAX_COMMAND_BUFFER_SIZE 4

#define command_buffer_size(wx_info) *((int*)(wx_info->heap[MEM_F0]))
// #define command_buffer(wx_info, channel) *(((uint32_t*)(wx_info->heap[MEM_F1])) + channel)


widget wx_command_create(int x, int y)
{
    widget command;

    command.data.rect.x = x;
    command.data.rect.y = y;

    command.data.selected = 0;
    
    command.fx.fx_update = wx_fx_none;
    command.fx.fx_draw = wx_command_draw;
    command.fx.fx_mouse_motion = wx_check_bounds;
    command.fx.fx_mouse_wheel = wx_fx_command_mouse_wheel;
    command.fx.fx_key_pressed = wx_fx_command_key_pressed;
    command.fx.fx_mouse_button_down = wx_fx_mouse_button_down_command;

    command.data.heap[MEM_F0] = malloc(sizeof(int));
    command.data.heap[MEM_F1] = malloc(sizeof(char) * MAX_COMMAND_BUFFER_SIZE);

    wx_command_initialize(command.data);
    return command; 

}


void wx_command_initialize(widget_info *wx_info)
{
    // int* a;
    // *a = 5;
    // printf("%d\n", *a);
    // *((int*)(wx_info->heap[MEM_F0])) = 5;
    // *command_buffer_size(wx_info) = 5;
    // printf("%d\n", *((int*)wx_info->heap[MEM_F0]));
}

void wx_command_draw(widget_info *wx_info)
{

    SDL_Rect command_bg_rect, command_fg_rect;
    SDL_Rect command_control_bg_rect, command_control_fg_rect;
    SDL_Rect option_rect;
    
    int command_x1, command_x2;

    widget_info temp_wx_info;

    int opt_x, opt_y, opt_w, opt_h;
    
    int border_color = COLOR_PRIMARY;
    
    command_fg_rect.x = wx_info->rect.x;
    command_fg_rect.y = wx_info->rect.y;
    command_fg_rect.w = COMMAND_W;
    command_fg_rect.h = COMMAND_H;

    command_bg_rect.x = command_fg_rect.x - 1;
    command_bg_rect.y = command_fg_rect.y - 1;
    command_bg_rect.w = command_fg_rect.w + 2;
    command_bg_rect.h = command_fg_rect.h + 2;


    SDL_SetRenderDrawColor(renderer, red_mask(COLOR_FOREGROUND), green_mask(COLOR_FOREGROUND), blue_mask(COLOR_FOREGROUND), SDL_ALPHA_OPAQUE);
    SDL_RenderDrawRect(renderer, &command_bg_rect);

    write_text("H11s", wx_x(wx_info) + X_PAD, wx_y(wx_info) + Y_PAD, COLOR_FOREGROUND);

}


void wx_fx_command_mouse_wheel(widget_info *wx_info)
{

}



void wx_fx_mouse_button_down_command(widget_info *wx_info)
{
    // wx_fx_mouse_button_down_select(wx_info);
}

void wx_fx_command_key_pressed(widget_info *wx_info)
{
    if (gui_key_press_pending)
    {
        printf("%c", key_char);
    }

}



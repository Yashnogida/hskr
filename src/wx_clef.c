
#include <stdlib.h>
#include <stdio.h>
#include "gui.h"
#include "SDL.h"

#define CLEF_W 800
#define CLEF_H 900
#define X_PAD 10
#define Y_PAD 10

#define CLEF_LINE_SPACING 10

enum MEM_FIELD_ENUM
{
    MEM_F0,         // Memory Field 0: Bit Mask for Channels Enabled (Uint8) 
    MEM_F1,         // Memory Field 1: Pointer to array of channel colors (Uint32)
    MEM_FIELD_MAX
};


void wx_clef_draw(widget_info *data);
void wx_fx_mouse_button_down_clef(widget_info *wx_info);
void wx_fx_clef_mouse_wheel(widget_info *wx_info);

#define channel_selected(wx_info, channel) ((widget_info*)wx_info->heap + channel)->selected
#define channel_color(wx_info, channel) *(((uint32_t*)(wx_info->heap[MEM_F1])) + channel)


widget wx_clef_create(int x, int y)
{
    widget clef;

    clef.data.rect.x = x;
    clef.data.rect.y = y;

    clef.data.selected = 0;
    
    clef.fx.fx_update = wx_fx_none;
    clef.fx.fx_draw = wx_clef_draw;
    clef.fx.fx_mouse_motion = wx_check_bounds;
    clef.fx.fx_mouse_wheel = wx_fx_clef_mouse_wheel;
    clef.fx.fx_keypressed = wx_fx_none;
    clef.fx.fx_mouse_button_down = wx_fx_mouse_button_down_clef;
    
    return clef; 

}



void wx_clef_draw(widget_info *wx_info)
{

    SDL_Rect clef_bg_rect, clef_fg_rect;
    SDL_Rect clef_control_bg_rect, clef_control_fg_rect;
    SDL_Rect option_rect;
    
    int clef_x1, clef_x2;

    widget_info temp_wx_info;

    int opt_x, opt_y, opt_w, opt_h;
    
    int border_color = COLOR_PRIMARY;
    
    // clef Rectangle
    clef_fg_rect.x = wx_info->rect.x;
    clef_fg_rect.y = wx_info->rect.y;
    clef_fg_rect.w = CLEF_W;
    clef_fg_rect.h = CLEF_H;

    clef_bg_rect.x = clef_fg_rect.x - 1;
    clef_bg_rect.y = clef_fg_rect.y - 1;
    clef_bg_rect.w = clef_fg_rect.w + 2;
    clef_bg_rect.h = clef_fg_rect.h + 2;

    // Draw Clef

    temp_wx_info.rect = clef_control_fg_rect;
    if ( wx_check_bounds(&temp_wx_info) )
        border_color = COLOR_BACKGROUND;

    clef_x1 = wx_x(wx_info) + X_PAD;
    clef_x2 = CLEF_W - X_PAD;

    SDL_SetRenderDrawColor(renderer, red_mask(COLOR_FOREGROUND), green_mask(COLOR_FOREGROUND), blue_mask(COLOR_FOREGROUND), SDL_ALPHA_OPAQUE);
    SDL_RenderDrawRect(renderer, &clef_bg_rect);
    
    for (int i=0; i<5; i++)
        SDL_RenderDrawLine(renderer, clef_x1, 100 + (CLEF_LINE_SPACING*i), clef_x2, 100 + (CLEF_LINE_SPACING*i));

    write_text("R", clef_x1 + 100, 1050, 0xFF0000);


}


void wx_fx_clef_mouse_wheel(widget_info *wx_info)
{
    if(gui_mouse_wheel_pending)
    {
        printf("%d\n", gui_mouse_wheel_direction);
    }
}




void wx_fx_mouse_button_down_clef(widget_info *wx_info)
{
    // wx_fx_mouse_button_down_select(wx_info);
}


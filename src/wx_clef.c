
#include <stdlib.h>
#include <stdio.h>
#include "gui.h"
#include "SDL.h"
#include "SDL_image.h"

#define CLEF_WINDOW_W 800
#define CLEF_WINDOW_H 900

#define LINES_IN_CLEF 5
#define CLEF_LINE_SPACING 10
#define CLEF_TO_CLEF_SPACING 100
#define CLEF_MARGIN 10

#define CLEF_WIDTH (CLEF_WINDOW_W - 2*CLEF_MARGIN)
#define CLEF_HEIGHT (LINES_IN_CLEF * CLEF_LINE_SPACING)


enum MEM_FIELD_ENUM
{
    MEM_F0,         // Memory Field 0: Bit Mask for Channels Enabled (Uint8) 
    MEM_F1,         // Memory Field 1: Pointer to array of channel colors (Uint32)
    MEM_FIELD_MAX
};


void wx_clef_draw(widget_info *data);
void wx_clef_initialize(widget_info *wx_info);
void wx_fx_mouse_button_down_clef(widget_info *wx_info);
void wx_fx_clef_mouse_wheel(widget_info *wx_info);
void wx_clef_draw_blank_clefs(widget_info *wx_info);

SDL_Texture *clef_blank_texture;


widget wx_clef_create(int x, int y)
{
    widget clef;

    clef.data.rect.x = x;
    clef.data.rect.y = y;
    clef.data.rect.w = CLEF_WINDOW_W;
    clef.data.rect.h = CLEF_WINDOW_H;

    clef.data.selected = 0;
    
    clef.fx.fx_update = wx_fx_none;
    clef.fx.fx_draw = wx_clef_draw;
    clef.fx.fx_mouse_motion = wx_check_bounds;
    clef.fx.fx_mouse_wheel = wx_fx_clef_mouse_wheel;
    clef.fx.fx_key_pressed = wx_fx_none;
    clef.fx.fx_mouse_button_down = wx_fx_mouse_button_down_clef;

    wx_clef_initialize(&clef);
    
    return clef; 

}

void wx_clef_initialize(widget_info *wx_info)
{

    clef_blank_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, CLEF_WIDTH, CLEF_HEIGHT);


    SDL_SetRenderTarget(renderer, clef_blank_texture);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    SDL_SetTextureBlendMode(clef_blank_texture, SDL_BLENDMODE_BLEND);
    SetRenderDrawColor(COLOR_FOREGROUND);
    
    // Clef Horizontal Lines
    for (int i=0; i<LINES_IN_CLEF; i++)
        SDL_RenderDrawLine(renderer, 0, (CLEF_LINE_SPACING*i), CLEF_WIDTH, (CLEF_LINE_SPACING*i));

    // Clef Vertical Lines
    SDL_RenderDrawLine(renderer, 0, 0, 0, (CLEF_HEIGHT - CLEF_LINE_SPACING));
    SDL_RenderDrawLine(renderer, CLEF_WIDTH/2, 0, CLEF_WIDTH/2, (CLEF_HEIGHT - CLEF_LINE_SPACING));
    SDL_RenderDrawLine(renderer, (CLEF_WIDTH - 1), 0, (CLEF_WIDTH - 1), (CLEF_HEIGHT - CLEF_LINE_SPACING));

    SDL_SetRenderTarget(renderer, NULL);

    
}


void wx_clef_draw(widget_info *wx_info)
{

    wx_draw_frame(wx_info, COLOR_FOREGROUND, COLOR_BACKGROUND);
    wx_clef_draw_blank_clefs(wx_info);
    // wx_clef_draw_notes(wx_info);
    // SDL_Surface* lettuce_sur = IMG_Load("lettuce.png");
    // SDL_Texture* lettuce_tex = SDL_CreateTextureFromSurface(renderer, lettuce_sur);



}


void wx_clef_draw_blank_clefs(widget_info *wx_info)
{
    SDL_Rect dest_rect;

    for (int i=0; i<8; i++)
    {
        
        dest_rect.x = wx_x(wx_info) + CLEF_MARGIN;
        dest_rect.y = CLEF_TO_CLEF_SPACING + (i*CLEF_TO_CLEF_SPACING);
        dest_rect.w = CLEF_WIDTH;
        dest_rect.h = CLEF_HEIGHT;
        
        SDL_RenderCopy(renderer, clef_blank_texture, NULL, &dest_rect);
    }
}


void wx_clef_draw_notes(widget_info *wx_info)
{


    // write_text("R", wx_x(wx_info), 100, 1050, 0xFF0000);

}




void wx_fx_clef_mouse_wheel(widget_info *wx_info)
{
    if(gui_mouse_wheel_pending)
    {
        // printf("%d\n", gui_mouse_wheel_direction);
    }
}




void wx_fx_mouse_button_down_clef(widget_info *wx_info)
{
    // wx_fx_mouse_button_down_select(wx_info);
}


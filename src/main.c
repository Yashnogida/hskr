
#include <stdio.h>
#include <stdbool.h>
#include "gui.h"

bool quit;


void setup_state_0();

int main(int argc, char* argv[])
{
  // socket_init("p700-k1.scs.is.keysight.com");
  // socket_close();
  // return 1;

  gui_init();

  setup_state_0();
  
  int ta, tb;

  // socket_init("p700-k1.scs.is.keysight.com");

  while (!quit)
  {
    // ta = SDL_GetTicks();
    gui_update();
    // tb = SDL_GetTicks();
    // printf("%d %d | Update rate: %dms\n", ta, tb, tb - ta);
  }
    

  gui_close();

  return 0;
  
}


void setup_state_0()
{
  
  gui_add_widget_queue( wx_clef_create(10, 10) );
  gui_add_widget_queue( wx_command_create(10, 920) );

}

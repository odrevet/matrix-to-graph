#ifndef SPRITE_H
#define SPRITE_H

#include <tigcclib.h>

#include "io.h"
#include "../display.h"

typedef struct
{
 unsigned char *sz_bitmap;
 int i_size;
 point coord;
} sprite;

void sprite_draw(sprite o_sprite);
void sprite_focus(sprite o_sprite, graph *p_graph, point *v_key);

#endif

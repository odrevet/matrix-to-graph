#include "sprite.h"

void sprite_draw(sprite o_sprite)
{
    Sprite8(o_sprite.coord.x, o_sprite.coord.y, o_sprite.i_size, o_sprite.sz_bitmap, LCD_MEM, SPRT_XOR);
}

void sprite_focus(sprite o_sprite, graph *p_graph, point *v_key)
{
    int i = 0;
    char szHelpMessage[20];
    char bQuitter = 0;
    char bDeplacement = 0;
    int NbSommets = p_graph->i_nb_node;

    SetIntVec(AUTO_INT_1, DUMMY_HANDLER);

    sprite_draw(o_sprite);
    do
    {
        //temporize(800);
        if (_rowread(v_key[LEFT].y) & v_key[LEFT].x)
        {
            sprite_draw(o_sprite);
            o_sprite.coord.x -= 1;
            sprite_draw(o_sprite);
        }
        if (_rowread(v_key[RIGHT].y) & v_key[RIGHT].x)
        {
            sprite_draw(o_sprite);
            o_sprite.coord.x += 1;
            sprite_draw(o_sprite);
        }
        if (_rowread(v_key[DOWN].y) & v_key[DOWN].x)
        {
            sprite_draw(o_sprite);
            o_sprite.coord.y += 1;
            sprite_draw(o_sprite);
        }
        if (_rowread(v_key[UP].y) & v_key[UP].x)
        {
            sprite_draw(o_sprite);
            o_sprite.coord.y -= 1;
            sprite_draw(o_sprite);
        }
        if (_rowread(v_key[LESS].y) & v_key[LESS].x)
        {
            p_graph->i_ray--;
            draw_graph(p_graph);
            sprite_draw(o_sprite);
            ST_helpMsg("Deszoom");
        }
        if (_rowread(v_key[PLUS].y) & v_key[PLUS].x)
        {
            p_graph->i_ray++;
            draw_graph(p_graph);
            sprite_draw(o_sprite);
            ST_helpMsg("Zoom");
        }
        if (_rowread(v_key[ENTER].y) & v_key[ENTER].x)
        {
            //temporize(2500);
            if (bDeplacement == 0)
            {
                do
                {
                    if ((o_sprite.coord.x >= p_graph->v_node[i].coord.x - p_graph->i_ray) &&
                        (o_sprite.coord.y >= p_graph->v_node[i].coord.y - p_graph->i_ray) &&
                        (o_sprite.coord.x < p_graph->v_node[i].coord.x + p_graph->i_ray) &&
                        (o_sprite.coord.y < p_graph->v_node[i].coord.y + p_graph->i_ray))
                    {
                        bDeplacement = 1;
                        strcpy(szHelpMessage, "moving ");
                        strcat(szHelpMessage, p_graph->v_node[i].sz_name);
                        ST_helpMsg(szHelpMessage);
                    }
                    else
                    {
                        if (i == NbSommets)
                        {
                            ST_helpMsg("no node found");
                            i = 0;
                        }
                        else
                        {
                            i++;
                        }
                    }
                } while ((i < NbSommets) && (bDeplacement == 0));
            }
            else
            {
                p_graph->v_node[i].coord = set_coord(o_sprite.coord.x, o_sprite.coord.y);
                draw_graph(p_graph);
                sprite_draw(o_sprite);
                bDeplacement = 0;
                ST_helpMsg("node moved");
            }
        }
        if (_rowread(v_key[ESC].y) & v_key[ESC].x)
        {
            bQuitter = 1;
        }
    } while (bQuitter != 1);
    sprite_draw(o_sprite);
}

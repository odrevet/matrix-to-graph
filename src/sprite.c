#include "sprite.h"

void sprite_draw(sprite o_sprite)
{
    Sprite8(o_sprite.coord.i_x, o_sprite.coord.i_y, o_sprite.i_size, o_sprite.sz_bitmap, LCD_MEM, SPRT_XOR);
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
        if (_rowread(v_key[LEFT].i_y) & v_key[LEFT].i_x)
        {
            sprite_draw(o_sprite);
            o_sprite.coord.i_x -= 1;
            sprite_draw(o_sprite);
        }
        if (_rowread(v_key[RIGHT].i_y) & v_key[RIGHT].i_x)
        {
            sprite_draw(o_sprite);
            o_sprite.coord.i_x += 1;
            sprite_draw(o_sprite);
        }
        if (_rowread(v_key[DOWN].i_y) & v_key[DOWN].i_x)
        {
            sprite_draw(o_sprite);
            o_sprite.coord.i_y += 1;
            sprite_draw(o_sprite);
        }
        if (_rowread(v_key[UP].i_y) & v_key[UP].i_x)
        {
            sprite_draw(o_sprite);
            o_sprite.coord.i_y -= 1;
            sprite_draw(o_sprite);
        }
        if (_rowread(v_key[LESS].i_y) & v_key[LESS].i_x)
        {
            p_graph->i_ray--;
            graph_draw(p_graph);
            sprite_draw(o_sprite);
            ST_helpMsg("Deszoom");
        }
        if (_rowread(v_key[PLUS].i_y) & v_key[PLUS].i_x)
        {
            p_graph->i_ray++;
            graph_draw(p_graph);
            sprite_draw(o_sprite);
            ST_helpMsg("Zoom");
        }
        if (_rowread(v_key[ENTER].i_y) & v_key[ENTER].i_x)
        {
            //temporize(2500);
            if (bDeplacement == 0)
            {
                do
                {
                    if ((o_sprite.coord.i_x >= p_graph->v_node[i].coord.i_x - p_graph->i_ray) &&
                        (o_sprite.coord.i_y >= p_graph->v_node[i].coord.i_y - p_graph->i_ray) &&
                        (o_sprite.coord.i_x < p_graph->v_node[i].coord.i_x + p_graph->i_ray) &&
                        (o_sprite.coord.i_y < p_graph->v_node[i].coord.i_y + p_graph->i_ray))
                    {
                        bDeplacement = 1;
                        strcpy(szHelpMessage, "D�placement de ");
                        strcat(szHelpMessage, p_graph->v_node[i].sz_name);
                        ST_helpMsg(szHelpMessage);
                    }
                    else
                    {
                        if (i == NbSommets)
                        {
                            ST_helpMsg("Aucun sommet trouv� ! ");
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
                p_graph->v_node[i].coord = set_coord(o_sprite.coord.i_x, o_sprite.coord.i_y);
                graph_draw(p_graph);
                sprite_draw(o_sprite);
                bDeplacement = 0;
                ST_helpMsg("D�placement �ffectu�. ");
            }
        }
        if (_rowread(v_key[ESC].i_y) & v_key[ESC].i_x)
        {
            bQuitter = 1;
        }
    } while (bQuitter != 1);
    sprite_draw(o_sprite);
}

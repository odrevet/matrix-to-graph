#include "draw.h"

void draw_arrow(point o_point_from, point o_point_to)
{
    arrow o_arrow = {.width = 6, .theta = 0.8};
    point aptPoly[3];
    float vecLine[2];
    float vecLeft[2];

    // set to point
    aptPoly[0].x = o_point_to.x;
    aptPoly[0].y = o_point_to.y;

    // build the line vector
    vecLine[0] = (float)aptPoly[0].x - o_point_from.x;
    vecLine[1] = (float)aptPoly[0].y - o_point_from.y;

    // build the arrow base vector - normal to the line
    vecLeft[0] = -vecLine[1];
    vecLeft[1] = vecLine[0];

    // setup length parameters
    float fLength = (float)sqrt(vecLine[0] * vecLine[0] + vecLine[1] * vecLine[1]);
    float th = o_arrow.width / (2.0f * fLength);
    float ta = o_arrow.width / (2.0f * (tan(o_arrow.theta) / 2.0f) * fLength);

    // base of the arrow
    point o_point_base = {.x = (int)(aptPoly[0].x + -ta * vecLine[0]),
                          .y = (int)(aptPoly[0].y + -ta * vecLine[1])};

    // build the points on the sides of the arrow
    aptPoly[1].x = (int)(o_point_base.x + th * vecLeft[0]);
    aptPoly[1].y = (int)(o_point_base.y + th * vecLeft[1]);
    aptPoly[2].x = (int)(o_point_base.x + -th * vecLeft[0]);
    aptPoly[2].y = (int)(o_point_base.y + -th * vecLeft[1]);

    FillTriangle(aptPoly[0].x, aptPoly[0].y, aptPoly[1].x, aptPoly[1].y, aptPoly[2].x, aptPoly[2].y, ScrRect, A_NORMAL);
}

void draw_graph(const graph *p_graph)
{
    int index;
    float fAngle;
    point point_src, point_dest;
    unsigned short icon_loop[16] = {
        0x0000, 0x0000, 0x0F80, 0x1040, 0x2020, 0x4010, 0x4010, 0x4010,
        0x40FE, 0x407C, 0x2038, 0x1010, 0x0000, 0x0000, 0x0000, 0x0000};

    clrscr();

    for (index = 0; index < p_graph->i_nb_node; index++)
    {
        DrawStr(p_graph->v_node[index].coord.x - p_graph->i_ray / 2, p_graph->v_node[index].coord.y - p_graph->i_ray / 2, p_graph->v_node[index].sz_name, A_NORMAL);
        DrawClipEllipse(p_graph->v_node[index].coord.x, p_graph->v_node[index].coord.y, p_graph->i_ray, p_graph->i_ray, ScrRect, A_NORMAL);
    }

    for (index = 0; index < p_graph->i_nb_edge; index++)
    {
        if (p_graph->v_edge[index].src == p_graph->v_edge[index].dest)
        {
            Sprite16(p_graph->v_edge[index].src->coord.x, p_graph->v_edge[index].dest->coord.y - p_graph->i_ray * 2, 16, icon_loop, LCD_MEM, SPRT_XOR);
        }
        else
        {
            fAngle = get_angle(p_graph->v_edge[index].src, p_graph->v_edge[index].dest);
            point_src = ortho_projection(p_graph->v_edge[index].src->coord, -p_graph->i_ray, fAngle);
            point_dest = ortho_projection(p_graph->v_edge[index].dest->coord, p_graph->i_ray, fAngle);
            DrawLine(point_src.x, point_src.y, point_dest.x, point_dest.y, A_NORMAL);
            draw_arrow(point_src, point_dest);
        }
    }
}

void draw_edge_weight(edge *v_edge, int i_nb_edge)
{
    int i;
    char szValue[5];
    for (i = 0; i < i_nb_edge; i++)
    {
        sprintf(szValue, "%d", v_edge[i].i_weight);
        if (v_edge[i].src == v_edge[i].dest)
        {
            DrawStr((v_edge[i].src->coord.x + v_edge[i].dest->coord.x) / 2, (v_edge[i].src->coord.y + v_edge[i].dest->coord.y) / 2 - 26, szValue, A_NORMAL);
        }
        else
        {
            DrawStr((v_edge[i].src->coord.x + v_edge[i].dest->coord.x) / 2, (v_edge[i].src->coord.y + v_edge[i].dest->coord.y) / 2 + 4, szValue, A_NORMAL);
        }
    }
}

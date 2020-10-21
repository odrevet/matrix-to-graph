#include "draw.h"

void arrow_draw(point point1, point point2, point point3)
{
    FillTriangle(point1.i_x, point1.i_y, point2.i_x, point2.i_y, point3.i_x, point3.i_y, ScrRect, A_NORMAL);
}

void IntArrowTo(int FromX, int FromY, int ToX, int ToY, arrow *pA)
{

    point ptFrom = {FromX, FromY};
    point ptTo = {ToX, ToY};
    PtArrowTo(ptFrom, ptTo, pA);
}

void PtArrowTo(point pFrom, point pTo, arrow *pA)
{
    point pBase;
    point aptPoly[3];
    float vecLine[2];
    float vecLeft[2];
    float fLength;
    float th;
    float ta;

    // set to point
    aptPoly[0].i_x = pTo.i_x;
    aptPoly[0].i_y = pTo.i_y;

    // build the line vector
    vecLine[0] = (float)aptPoly[0].i_x - pFrom.i_x;
    vecLine[1] = (float)aptPoly[0].i_y - pFrom.i_y;

    // build the arrow base vector - normal to the line
    vecLeft[0] = -vecLine[1];
    vecLeft[1] = vecLine[0];

    // setup length parameters
    fLength = (float)sqrt(vecLine[0] * vecLine[0] + vecLine[1] * vecLine[1]);
    th = pA->nWidth / (2.0f * fLength);
    ta = pA->nWidth / (2.0f * (tan(pA->fTheta) / 2.0f) * fLength);

    // find the base of the arrow
    pBase.i_x = (int)(aptPoly[0].i_x + -ta * vecLine[0]);
    pBase.i_y = (int)(aptPoly[0].i_y + -ta * vecLine[1]);

    // build the points on the sides of the arrow
    aptPoly[1].i_x = (int)(pBase.i_x + th * vecLeft[0]);
    aptPoly[1].i_y = (int)(pBase.i_y + th * vecLeft[1]);
    aptPoly[2].i_x = (int)(pBase.i_x + -th * vecLeft[0]);
    aptPoly[2].i_y = (int)(pBase.i_y + -th * vecLeft[1]);

    line_draw(pFrom, pBase);
    line_draw(pFrom, aptPoly[1]);
    line_draw(pFrom, aptPoly[0]);
    line_draw(pFrom, aptPoly[2]);
}

void line_draw(point pointSource, point pointDest)
{
    short x = pointSource.i_x, y = pointSource.i_y;
    short dx = abs(pointDest.i_x - pointSource.i_x);
    short dy = abs(pointDest.i_y - pointSource.i_y);
    short ystep = (pointSource.i_y < pointDest.i_y) ? 1 : -1, pystep = 30 * ystep;
    short mov = dx ? 0 : -1;
    unsigned char *ptr = (char *)LCD_MEM + 30 * y + (x >> 3);
    short mask = 1 << (~x & 7);
    if (pointSource.i_x < pointDest.i_x)
        while (x != pointDest.i_x || y != pointDest.i_y)
        {
            *ptr |= mask;
            if (mov < 0)
                y += ystep, ptr += pystep, mov += dx;
            else
            {
                mov -= dy;
                if (++x & 7)
                    mask >>= 1;
                else
                    ptr++, mask = 0x80;
            }
        }
    else
        while (x != pointDest.i_x || y != pointDest.i_y)
        {
            *ptr |= mask;
            if (mov < 0)
                y += ystep, ptr += pystep, mov += dx;
            else
            {
                mov -= dy;
                if (x-- & 7)
                    mask <<= 1;
                else
                    ptr--, mask = 1;
            }
        }
}

void draw_graph(const graph *p_graph)
{
    int index;
    float fAngle;
    point point_src, point_dest;
    arrow o_arrow = {.nWidth = 5, .fTheta = 0.25};
    unsigned short icon_loop[16] = {
        0x0000, 0x0000, 0x0F80, 0x1040, 0x2020, 0x4010, 0x4010, 0x4010,
        0x40FE, 0x407C, 0x2038, 0x1010, 0x0000, 0x0000, 0x0000, 0x0000};

    clrscr();

    for (index = 0; index < p_graph->i_nb_node; index++)
    {
        DrawStr(p_graph->v_node[index].coord.i_x - p_graph->i_ray / 2, p_graph->v_node[index].coord.i_y - p_graph->i_ray / 2, p_graph->v_node[index].sz_name, A_NORMAL);
        DrawClipEllipse(p_graph->v_node[index].coord.i_x, p_graph->v_node[index].coord.i_y, p_graph->i_ray, p_graph->i_ray, ScrRect, A_NORMAL);
    }

    for (index = 0; index < p_graph->i_nb_edge; index++)
    {
        if (p_graph->v_edge[index].src == p_graph->v_edge[index].dest)
        {
            Sprite16(p_graph->v_edge[index].src->coord.i_x, p_graph->v_edge[index].dest->coord.i_y - p_graph->i_ray * 2, 16, icon_loop, LCD_MEM, SPRT_XOR);
        }
        else
        {
            fAngle = get_angle(p_graph->v_edge[index].src, p_graph->v_edge[index].dest);
            point_src = ortho_projection(p_graph->v_edge[index].src->coord, -p_graph->i_ray, fAngle);
            point_dest = ortho_projection(p_graph->v_edge[index].dest->coord, p_graph->i_ray, fAngle);
            PtArrowTo(point_src, point_dest, &o_arrow);
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
            DrawStr((v_edge[i].src->coord.i_x + v_edge[i].dest->coord.i_x) / 2, (v_edge[i].src->coord.i_y + v_edge[i].dest->coord.i_y) / 2 - 26, szValue, A_NORMAL);
        }
        else
        {
            DrawStr((v_edge[i].src->coord.i_x + v_edge[i].dest->coord.i_x) / 2, (v_edge[i].src->coord.i_y + v_edge[i].dest->coord.i_y) / 2 + 4, szValue, A_NORMAL);
        }
    }
}

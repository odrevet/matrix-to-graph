#include "display.h"

short menu_display()
{
    HANDLE menu_menu = MenuNew(2, LCD_WIDTH, 18);
    HANDLE menu_exec;
    ICON icon_pencil = {{0x0, 0x0, 0xC0, 0x120, 0x3A0, 0x4C0, 0x880, 0x1100, 0x2200, 0x4400, 0xC800, 0xF000, 0xE000, 0xC000, 0x8000, 0x0}};
    ICON icon_cursor = {{0x40, 0x60, 0x70, 0x78, 0x7C, 0x7E, 0x7F, 0x7C, 0x4C, 0x0E, 0x06, 0x06}};
    MenuAddText(menu_menu, 0, "file", 1, 0);
    MenuAddText(menu_menu, 1, "load matrix", 11, 0);

    MenuAddIcon(menu_menu, 0, &icon_pencil, 2, 0);
    MenuAddText(menu_menu, 2, "draw graph", 21, 0);
    MenuAddText(menu_menu, 2, "transitive closure", 22, 0);
    MenuAddText(menu_menu, 2, "move node", 23, 0);
    MenuAddText(menu_menu, 2, "exchange nodes", 24, 0);
    MenuAddText(menu_menu, 2, "rename node", 25, 0);
    MenuAddText(menu_menu, 2, "display weight", 26, 0);

    MenuAddText(menu_menu, 0, "display", 3, 0);
    MenuAddText(menu_menu, 3, "matrix", 31, 0);
    MenuAddText(menu_menu, 3, "vertices", 32, 0);
    MenuAddText(menu_menu, 3, "nodes", 33, 0);
    MenuAddText(menu_menu, 3, "previous dictionary", 34, 0);
    MenuAddText(menu_menu, 3, "next dictionary", 35, 0);
    MenuAddText(menu_menu, 3, "matrix power", 36, 0);
    MenuAddText(menu_menu, 3, "transitive closure", 37, 0);
    MenuAddText(menu_menu, 3, "search edge", 38, 0);

    //MenuAddIcon(menu_menu, 0, &icon_cursor, 4, 0);
    MenuAddText(menu_menu, -1, "quit", 5, 0);

    menu_exec = MenuBegin(HeapDeref(menu_menu), 0, 0, 0);
    return MenuKey(menu_exec, GKeyIn(NULL, 0));
}

void edge_list(const edge *v_edge, int i_nb_edge)
{
    int index_edge;
    clrscr();
    printf("Node list...\n");
    for (index_edge = 0; index_edge < i_nb_edge; index_edge++)
    {
        printf("%s --%d--> %s\n",
               v_edge[index_edge].src->sz_name,
               v_edge[index_edge].i_weight,
               v_edge[index_edge].dest->sz_name);
        if (i % 12 == 0)
        {
            ngetchx();
        }
    }
    ngetchx();
}

void arrow_draw(point point1, point point2, point point3)
{
    FillTriangle(point1.i_x, point1.i_y, point2.i_x, point2.i_y, point3.i_x, point3.i_y, ScrRect, A_NORMAL);
}

void graph_draw(const graph *p_graph)
{
    int i;
    float fAngle;
    point point_src, point_dest;
    //arrow *Fleche = malloc(sizeof(arrow));
    unsigned short icon_loop[16] = {
        0x0000, 0x0000, 0x0F80, 0x1040, 0x2020, 0x4010, 0x4010, 0x4010,
        0x40FE, 0x407C, 0x2038, 0x1010, 0x0000, 0x0000, 0x0000, 0x0000};

    Fleche->nWidth = 5;
    Fleche->fTheta = 0.25;
    clrscr();

    for (i = 0; i < p_graph->i_nb_node; i++)
    {
        DrawStr(p_graph->v_node[i].coord.i_x - p_graph->i_ray / 2, p_graph->v_node[i].coord.i_y - p_graph->i_ray / 2, p_graph->v_node[i].sz_name, A_NORMAL); //Nom du sommet
        DrawClipEllipse(p_graph->v_node[i].coord.i_x, p_graph->v_node[i].coord.i_y, p_graph->i_ray, p_graph->i_ray, ScrRect, A_NORMAL);                      //Cercle
    }

    for (i = 0; i < p_graph->i_nb_edge; i++)
    {
        if (p_graph->v_edge[i].src == p_graph->v_edge[i].dest)
        {
            Sprite16(p_graph->v_edge[i].src->coord.i_x, p_graph->v_edge[i].dest->coord.i_y - p_graph->i_ray * 2, 16, icon_loop, LCD_MEM, SPRT_XOR);
        }
        else
        {
            fAngle = get_angle(p_graph->v_edge[i].src, p_graph->v_edge[i].dest); //Recupere l'angle (radian)

            point_src = ortho_projection(p_graph->v_edge[i].src->coord, -p_graph->i_ray, fAngle);
            point_dest = ortho_projection(p_graph->v_edge[i].dest->coord, p_graph->i_ray, fAngle);
            PtArrowTo(point_src, point_dest, Fleche);
            /*line_draw(pointSource, pointDest);
   fAngle=get_angle(&pointSource, &pointDest);            //Recupere le nouvel angle
   Fleche.centre = ortho_projection(p_graph->v_edge[i].dest->coord, p_graph->i_ray+Fleche.i_height/2, fAngle);
   Fleche.v_point[0] = set_coord(Fleche.centre.i_x+Fleche.i_height/2, Fleche.centre.i_y+Fleche.i_base/2);
   Fleche.v_point[1] = set_coord(Fleche.v_point[0].i_x, Fleche.v_point[0].i_y-Fleche.i_base);
   Fleche.v_point[2] = set_coord(Fleche.centre.i_x-Fleche.i_height/2, Fleche.centre.i_y);
   arow_draw(rotate(fAngle, Fleche.v_point[0], Fleche.centre), rotate(fAngle, Fleche.v_point[1], Fleche.centre), rotate(fAngle, Fleche.v_point[2], Fleche.centre));
   */
            //free(Fleche);
        }
    }
}

void matrix_draw(matrix *matrice)
{
    int i, j;
    clrscr();
    for (i = 0; i < matrice->i_size; i++)
    {
        for (j = 0; j < matrice->i_size; j++)
        {
            printf(" %d ", matrice->ppi_data[i][j]);
        }
        printf("\n");
    }
    ngetchx();
}

void dict_prev(const graph *p_graph)
{
    int i, j;
    clrscr();
    printf("Si      | P(Xi)\n-----------------\n");
    for (i = 0; i < p_graph->i_nb_node; i++)
    {
        printf("%s      | ", p_graph->v_node[i].sz_name);
        for (j = 0; j < p_graph->i_nb_edge; j++)
        { //Pour tout les chemins
            if (&p_graph->v_node[i] == p_graph->v_edge[j].dest)
            {
                printf(" %s ", p_graph->v_edge[j].src->sz_name);
            }
        }
        printf("\n");
    }
    ngetchx();
}

void dict_next(const graph *p_graph)
{
    int i, j;
    clrscr();
    printf("Si      | S(Xi)\n-----------------\n");
    for (i = 0; i < p_graph->i_nb_node; i++)
    {
        printf("%s      | ", p_graph->v_node[i].sz_name);
        for (j = 0; j < p_graph->i_nb_edge; j++)
        {
            if (&p_graph->v_node[i] == p_graph->v_edge[j].src)
            {
                printf(" %s ", p_graph->v_edge[j].dest->sz_name);
            }
        }
        printf("\n");
    }
    ngetchx();
}

void node_swap_coord(node *v_node, int i_nb_node)
{
    int i, j;
    node_list(v_node, i_nb_node);
    printf("swap node: \n");
    scanf("%d", &i);
    printf("\with: \n");
    scanf("%d", &j);
    i--;
    j--;
    if (i >= 1 && i <= i_nb_node && j >= 1 && j <= i_nb_node)
    {
        node_swap(&v_node[i], &v_node[j]);
    }
}

void menu_enclosure(matrix *p_matrix)
{
    matrix MatriceTemp;

    MatriceTemp.i_size = p_matrix->i_size;
    matrix_malloc(&MatriceTemp);
    matrix_copy(p_matrix, &MatriceTemp);

    matrix_colsure(p_matrix, &MatriceTemp);
    matrix_draw(&MatriceTemp);

    matrix_free(&MatriceTemp);
    ngetchx();
}

void draw_transitive_closure(matrix *p_matrix, graph *p_graph)
{
    matrix matrix_tmp;
    graph graph_tmp;
    int i;

    matrix_tmp.i_size = p_matrix->i_size;
    matrix_malloc(&matrix_tmp);
    matrix_copy(p_matrix, &matrix_tmp);

    matrix_colsure(p_matrix, &matrix_tmp);

    graph_tmp.i_nb_edge = matrix_count_edge(&matrix_tmp);
    graph_tmp.i_nb_node = matrix_tmp.i_size;
    graph_tmp.i_ray = p_graph->i_ray;

    graph_tmp.v_node = calloc(matrix_tmp.i_size, sizeof(node));
    for (i = 0; i < matrix_tmp.i_size; i++)
    {
        strcpy(graph_tmp.v_node[i].sz_name, p_graph->v_node[i].sz_name);
        graph_tmp.v_node[i].coord = set_coord(p_graph->v_node[i].coord.i_x, p_graph->v_node[i].coord.i_y);
    }

    graph_tmp.v_edge = malloc(matrix_count_edge(&matrix_tmp) * sizeof(edge));
    set_edge(&matrix_tmp, &graph_tmp);
    graph_draw(&graph_tmp);
    ST_helpMsg("transitive closure drawing ");
    ngetchx();
    matrix_free(&matrix_tmp);
    free(graph_tmp.v_node);
    free(graph_tmp.v_edge);
}

void menu_pow(matrix *p_matrix)
{
    int iPuissance;
    matrix MatriceTemp;
    MatriceTemp.i_size = p_matrix->i_size;
    matrix_malloc(&MatriceTemp);
    matrix_copy(p_matrix, &MatriceTemp);

    clrscr();
    printf("power: ");
    scanf("%d", &iPuissance);
    matrix_pow(p_matrix, iPuissance, &MatriceTemp);
    matrix_draw(&MatriceTemp);
    matrix_free(&MatriceTemp);
}

void menu_node_rename(node *v_node, int i_nb_node)
{
    short int i_choice;
    int i;
    char *sz_name = NULL;
    clrscr();
    printf("1: prefix all\n2: Rename one\n3: Rename all\n> ");
    scanf("%hd", &i_choice);
    if (i_choice == 1)
    {
        printf("\nNew prefix (< 5 char): \n");
        scanf("%s", sz_name);
        node_prefix(v_node, sz_name, i_nb_node);
    }
    else if (i_choice == 2)
    {
        node_list(v_node, i_nb_node);
        printf("Which node rename ? \n");
        scanf("%d", &i);
        printf("\New name: \n");
        scanf("%s", sz_name);
        node_rename(&v_node[i - 1], sz_name);
    }
    else if (i_choice == 3)
    {
        for (i = 0; i < i_nb_node; i++)
        {
            strcpy(sz_name, "");
            printf("\nN%d name : %s\new name : ", i + 1, v_node[i].sz_name);
            scanf("%s", sz_name);
            if (strcmp(sz_name, NULL))
                node_rename(&v_node[i], sz_name);
            else
                printf("\n%s keep name\n", v_node[i].sz_name);
        }
    }
}

void edge_display_weight(edge *v_edge, int i_nb_edge)
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

void temporize(short int time)
{
    short int randNum;
    while (time-- > 0)
    {
        randNum = rand() % time;
    }
}

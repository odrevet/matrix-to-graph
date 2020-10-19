#define MIN_AMS 101

#include <tigcclib.h>

#include "../matrix.h"
#include "../display.h"
#include "io.h"
#include "trigo.h"
// #include "sprite.h"

short menu_display()
{
    HANDLE menu = MenuNew(2, LCD_WIDTH, 18);
    HANDLE menu_exec;

    //ICON icon_cursor = {{0x40, 0x60, 0x70, 0x78, 0x7C, 0x7E, 0x7F, 0x7C, 0x4C, 0x0E, 0x06, 0x06}};
    MenuAddText(menu, 0, "file", 1, 0);
    MenuAddText(menu, 1, "load matrix", 11, 0);

    MenuAddText(menu, 0, "draw", 2, 0);
    MenuAddText(menu, 2, "draw graph", 21, 0);
    MenuAddText(menu, 2, "transitive closure", 22, 0);
    MenuAddText(menu, 2, "move node", 23, 0);
    MenuAddText(menu, 2, "exchange nodes", 24, 0);
    MenuAddText(menu, 2, "rename node", 25, 0);
    MenuAddText(menu, 2, "display weight", 26, 0);

    MenuAddText(menu, 0, "display", 3, 0);
    MenuAddText(menu, 3, "matrix", 31, 0);
    MenuAddText(menu, 3, "vertices", 32, 0);
    MenuAddText(menu, 3, "nodes", 33, 0);
    MenuAddText(menu, 3, "previous dictionary", 34, 0);
    MenuAddText(menu, 3, "next dictionary", 35, 0);
    MenuAddText(menu, 3, "matrix power", 36, 0);
    MenuAddText(menu, 3, "transitive closure", 37, 0);
    MenuAddText(menu, 3, "find path", 38, 0);

    //MenuAddIcon(menu, 0, &icon_cursor, 4, 0);
    MenuAddText(menu, -1, "quit", 5, 0);

    menu_exec = MenuBegin(HeapDeref(menu), 0, 0, 0);
    return MenuKey(menu_exec, GKeyIn(NULL, 0));
}

void _main(void)
{
    short i_menu_choice;
    graph o_graph;
    matrix o_matrix;

    point v_key[8];

    ESI EsiPtr = top_estack;
    FontSetSys(F_6x8);
    clrscr();

    // check if the argument point to a matrix
    if ((GetArgType(EsiPtr) != LIST_TAG) || (GetArgType(EsiPtr - 1) != LIST_TAG))
    {
        EsiPtr = open_file(); // not a matrix, open a dialog window to select a matrix
    }

    if (!is_square_matrix(EsiPtr))
    {
        printf("Error: The matrix must have the same height and width\n");
        ngetchx();
        exit(0);
    }

    matrix_from_esi(&o_matrix, EsiPtr);
    graph_init(&o_graph, &o_matrix);

    /*sprite cursor;
    unsigned char sprite[12] = {
        0x40, 0x60, 0x70, 0x78, 0x7C, 0x7E, 0x7F, 0x7C,
        0x4C, 0x0E, 0x06, 0x06};

    cursor.i_size = sizeof(sprite);
    cursor.sz_bitmap = malloc(cursor.i_size * sizeof(cursor.sz_bitmap));
    memcpy(cursor.sz_bitmap, sprite, cursor.i_size);
    cursor.coord = set_coord(LCD_WIDTH / 2, LCD_HEIGHT / 2);
    sprite_draw(cursor);

    set_keyboard(v_key);
    INT_HANDLER interrupt1 = GetIntVec(AUTO_INT_1); // save auto-interrupt 1 (bottom text)
    */

    //graph_draw(p_graph);

    do
    {
        i_menu_choice = menu_display();
        switch (i_menu_choice)
        {
        case 11:
            EsiPtr = open_file();
            if (!is_square_matrix(EsiPtr))
            {
                printf("Error: The matrix must be a square matrix\n");
                ngetchx();
            }
            else
            {
                free_all(&o_graph, &o_matrix);
                matrix_from_esi(&o_matrix, EsiPtr);
                graph_init(&o_graph, &o_matrix);
            }
            break;
        case 21:
            graph_draw(&o_graph);
            ngetchx();
            break;
        case 22:
            //draw_transitive_closure(p_matrix, p_graph);
            break;
        case 23:
            //node_move(p_graph);
            break;
        case 25:
            //menu_node_rename(p_graph->v_node, p_matrix->i_size);
            break;
        case 26:
            graph_draw(p_graph);
            draw_edge_weight(p_graph->v_edge, p_graph->i_nb_edge);
            ngetchx();
            break;
        case 31:
            clrscr();
            print_matrix(&o_matrix);
            ngetchx();
            break;
        case 32:
            clrscr();
            print_edge_list(o_graph.v_edge, matrix_count_edge(&o_matrix));
            ngetchx();
            break;
        case 33:
            clrscr();
            print_node_list(o_graph.v_node, o_matrix.i_size);
            ngetchx();
            break;
        case 34:
            clrscr();
            print_dict_prev(&o_graph);
            ngetchx();
            break;
        case 35:
            clrscr();
            print_dict_next(&o_graph);
            ngetchx();
            break;
        case 36:
            //menu_pow(p_matrix);
            break;
        case 37:
            //menu_enclosure(p_matrix);
            break;
        case 38:
            //ford_bellman(p_graph);
            break;
        case 4: // cursor
            //graph_draw(p_graph);
            //sprite_focus(cursor, p_graph, v_key);
            //SetIntVec(AUTO_INT_1, interrupt1);
            break;
        }
    } while (i_menu_choice != 5);

    free_all(&o_graph, &o_matrix);
}

#define MIN_AMS 101

#include <tigcclib.h>

#include "../matrix.h"
#include "../print.h"
#include "trigo.h"
#include "draw.h"
#include "menu.h"
#include "point.h"

ESI open_file()
{
    ESQ types[1] = {MATRIX_TAG};
    HSym file;
    SYM_ENTRY *SymPtr;

    file = VarOpen(types);
    if (file.folder == 0)
        exit(0);
    else
    {
        SymPtr = DerefSym(file);
        return HToESI(SymPtr->handle);
    }
}

void matrix_from_esi(matrix *p_matrix, ESI EsiPtr)
{
    int i, j = 0;
    p_matrix->i_size = remaining_element_count(EsiPtr - 1);
    matrix_malloc(p_matrix);

    i = 0;

    if ((GetArgType(EsiPtr) != LIST_TAG) || (GetArgType(EsiPtr - 1) != LIST_TAG))
        exit(0);

    EsiPtr--;
    while (GetArgType(EsiPtr) != END_TAG)
    {
        EsiPtr--;
        while (GetArgType(EsiPtr) != END_TAG)
        {
            p_matrix->ppi_data[i][j] = (GetArgType(EsiPtr) == INT_TAG) ? GetIntArg(EsiPtr) : (int)estack_number_to_Float(EsiPtr);
            j++;
            SkipArg(EsiPtr);
        }
        i++;
        j = 0;
        EsiPtr--; // END_TAG
    }
    EsiPtr--; // END_TAG
}

void menu_matrix_closure(matrix *p_matrix)
{
    matrix MatriceTemp;

    MatriceTemp.i_size = p_matrix->i_size;
    matrix_malloc(&MatriceTemp);
    matrix_copy(p_matrix, &MatriceTemp);

    matrix_colsure(p_matrix, &MatriceTemp);
    print_matrix(&MatriceTemp);

    matrix_free(&MatriceTemp);
    ngetchx();
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
        print_node_list(v_node, i_nb_node);
        printf("Which node rename ? \n");
        scanf("%d", &i);
        printf("\nNew name: \n");
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

void menu_pow(matrix *p_matrix)
{
    int i_power;
    matrix matrix_tmp;
    matrix_tmp.i_size = p_matrix->i_size;
    matrix_malloc(&matrix_tmp);
    matrix_copy(p_matrix, &matrix_tmp);
    printf("power: ");
    scanf("%d", &i_power);
    matrix_pow(p_matrix, i_power, &matrix_tmp);
    print_matrix(&matrix_tmp);
    matrix_free(&matrix_tmp);
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
        graph_tmp.v_node[i].coord = set_coord(p_graph->v_node[i].coord.x, p_graph->v_node[i].coord.y);
    }

    graph_tmp.v_edge = malloc(matrix_count_edge(&matrix_tmp) * sizeof(edge));
    set_edge(&matrix_tmp, &graph_tmp);
    draw_graph(&graph_tmp);
    ST_helpMsg("transitive closure drawing ");
    ngetchx();
    matrix_free(&matrix_tmp);
    free(graph_tmp.v_node);
    free(graph_tmp.v_edge);
}

void menu_node_move(graph *p_graph)
{
    int index_node = 0;
    char abort = 0;
    char done = 0;

    clrscr();
    draw_graph(p_graph);

    // selection of the node to move
    do
    {
        ST_helpMsg(p_graph->v_node[index_node].sz_name);
        short key = ngetchx();

        if (key == KEY_LEFT)
        {
            if (index_node > 0)
            {
                index_node--;
            }
        }

        if (key == KEY_RIGHT)
        {
            if (index_node < p_graph->i_nb_node - 1)
            {
                index_node++;
            }
        }

        if (_keytest(RR_ESC))
        {
            abort = 1;
            done = 1;
        }

        if (_keytest(RR_ENTER))
        {
            done = 1;
        }

    } while (!done);

    if (!abort)
    {
        // select coord
        done = 0;
        point o_coord = p_graph->v_node[index_node].coord;
        const int crosshair_width = 2;
        const int crosshair_height = 2;
        const int move_px = 6;

        do
        {
            // draw
            clrscr();
            draw_graph(p_graph);
            DrawLine(o_coord.x - crosshair_width, o_coord.y, o_coord.x + crosshair_width, o_coord.y, A_NORMAL);
            DrawLine(o_coord.x, o_coord.y - crosshair_height, o_coord.x, o_coord.y + crosshair_height, A_NORMAL);

            // read key
            short key = ngetchx();

            if (key == KEY_LEFT)
            {
                if (o_coord.x > 0)
                {
                    o_coord.x -= move_px;
                }
            }

            if (key == KEY_RIGHT)
            {
                if (o_coord.x < LCD_WIDTH)
                {
                    o_coord.x += move_px;
                }
            }

            if (key == KEY_UP)
            {
                if (o_coord.y > 0)
                {
                    o_coord.y -= move_px;
                }
            }

            if (key == KEY_DOWN)
            {
                if (o_coord.y < LCD_HEIGHT)
                {
                    o_coord.y += move_px;
                }
            }

            if (_keytest(RR_ESC))
            {
                abort = 1;
                done = 1;
            }

            if (_keytest(RR_ENTER))
            {
                done = 1;
            }
        } while (!done);

        if (!abort)
        {
            p_graph->v_node[index_node].coord = set_coord(o_coord.x, o_coord.y);
        }
    }
}

void _main(void)
{
    short i_menu_choice;
    graph o_graph;
    matrix o_matrix;

    ESI EsiPtr = top_estack;
    FontSetSys(F_6x8);

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

    // initialize drawing coordinates
    int index_node;
    for (index_node = 0; index_node < o_matrix.i_size; index_node++)
    {
        o_graph.v_node[index_node].coord = set_coord(index_node * (LCD_WIDTH / o_matrix.i_size),
                                                     index_node * (LCD_HEIGHT / o_matrix.i_size));
    }

    clrscr();

    do
    {
        i_menu_choice = menu_display();
        switch (i_menu_choice)
        {
        case MENU_FILE_LOAD_MATRIX:
            EsiPtr = open_file();
            if (!is_square_matrix(EsiPtr))
            {
                printf("Error: The matrix must be a square matrix\n");
                ngetchx();
            }
            else
            {
                matrix_free(&o_matrix);
                graph_free(&o_graph);
                matrix_from_esi(&o_matrix, EsiPtr);
                graph_init(&o_graph, &o_matrix);
            }
            break;
        case MENU_DRAW_GRAPH:
            draw_graph(&o_graph);
            ngetchx();
            break;
        case MENU_DRAW_TRANSITIVE_CLOSURE:
            draw_transitive_closure(&o_matrix, &o_graph);
            break;
        case MENU_DRAW_NODE_MOVE:
            menu_node_move(&o_graph);
            draw_graph(&o_graph);
            ngetchx();
            break;
        case MENU_DRAW_RENAME_NODE:
            menu_node_rename(o_graph.v_node, o_matrix.i_size);
            break;
        case MENU_DRAW_DISPLAY_WEIGHT:
            draw_graph(&o_graph);
            draw_edge_weight(o_graph.v_edge, o_graph.i_nb_edge);
            ngetchx();
            break;
        case MENU_DISPLAY_MATRIX:
            clrscr();
            print_matrix(&o_matrix);
            ngetchx();
            break;
        case MENU_DISPLAY_EDGES:
            clrscr();
            print_edge_list(o_graph.v_edge, matrix_count_edge(&o_matrix));
            ngetchx();
            break;
        case MENU_DISPLAY_NODES:
            clrscr();
            print_node_list(o_graph.v_node, o_matrix.i_size);
            ngetchx();
            break;
        case MENU_DISPLAY_PREV_DICT:
            clrscr();
            print_dict_prev(&o_graph);
            ngetchx();
            break;
        case MENU_DISPLAY_NEXT_DICT:
            clrscr();
            print_dict_next(&o_graph);
            ngetchx();
            break;
        case MENU_DISPLAY_MATRIX_POWER:
            clrscr();
            menu_pow(&o_matrix);
            ngetchx();
            break;
        case MENU_DISPLAY_TRANSITIVE_CLOSURE:
            clrscr();
            menu_matrix_closure(&o_matrix);
            ngetchx();
            break;
        case MENU_DISPLAY_FIND_PATH:
            clrscr();
            ford_bellman(&o_graph);
            ngetchx();
            break;
        }
    } while (i_menu_choice != MENU_QUIT);

    matrix_free(&o_matrix);
    graph_free(&o_graph);
}

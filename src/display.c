#include "display.h"

void menu_enclosure(matrix *p_matrix)
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
    print_matrix(&MatriceTemp);
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

void temporize(short int time)
{
    short int randNum;
    while (time-- > 0)
    {
        randNum = rand() % time;
    }
}

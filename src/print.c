#include "print.h"

void print_edge_list(const edge *v_edge, int i_nb_edge)
{
    int index_edge;
    printf("Edge list\n");
    for (index_edge = 0; index_edge < i_nb_edge; index_edge++)
    {
        printf("%s -- %d --> %s\n",
               v_edge[index_edge].src->sz_name,
               v_edge[index_edge].i_weight,
               v_edge[index_edge].dest->sz_name);
    }
}

void print_node_list(node *v_node, int i_nb_node)
{
    int index_node;
    printf("Node list\n");
    for (index_node = 0; index_node < i_nb_node; index_node++)
    {
        printf("#%d: %s. Lvl: %d\n", index_node + 1, v_node[index_node].sz_name, v_node[index_node].i_level);
    }
}

void print_matrix(matrix *p_matrix)
{
    int index_row, index_col;
    for (index_row = 0; index_row < p_matrix->i_size; index_row++)
    {
        for (index_col = 0; index_col < p_matrix->i_size; index_col++)
        {
            printf("%d ", p_matrix->ppi_data[index_row][index_col]);
        }
        printf("\n");
    }
}

void print_dict_prev(const graph *p_graph)
{
    int index_node, index_edge;
    printf("Si      | P(Xi)\n-----------------\n");
    for (index_node = 0; index_node < p_graph->i_nb_node; index_node++)
    {
        printf("%s      | ", p_graph->v_node[index_node].sz_name);
        for (index_edge = 0; index_edge < p_graph->i_nb_edge; index_edge++)
        {
            if (p_graph->v_node + index_node == p_graph->v_edge[index_edge].dest)
            {
                printf(" %s ", p_graph->v_edge[index_edge].src->sz_name);
            }
        }
        printf("\n");
    }
}

void print_dict_next(const graph *p_graph)
{
    int index_node, index_edge;
    printf("Si      | S(Xi)\n-----------------\n");
    for (index_node = 0; index_node < p_graph->i_nb_node; index_node++)
    {
        printf("%s      | ", p_graph->v_node[index_node].sz_name);
        for (index_edge = 0; index_edge < p_graph->i_nb_edge; index_edge++)
        {
            if (p_graph->v_node + index_node == p_graph->v_edge[index_edge].src)
            {
                printf(" %s ", p_graph->v_edge[index_edge].dest->sz_name);
            }
        }
        printf("\n");
    }
}

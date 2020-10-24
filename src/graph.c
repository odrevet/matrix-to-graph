#include "graph.h"

void graph_init(graph *p_graph, matrix *p_matrix)
{
  p_graph->i_nb_edge = matrix_count_edge(p_matrix);
  p_graph->i_nb_node = p_matrix->i_size;
#ifdef __m68k__
  p_graph->i_ray = 10;
#endif
  p_graph->v_node = calloc(p_matrix->i_size, sizeof(node));
  node_prefix(p_graph->v_node, (char *)"S", p_matrix->i_size);

  p_graph->v_edge = malloc(matrix_count_edge(p_matrix) * sizeof(edge));
  set_edge(p_matrix, p_graph);
  set_level(p_matrix, p_graph->v_node);
}

void set_edge(matrix *p_matrix, graph *p_graph)
{
  int i, j, k = 0;

  for (i = 0; i < p_matrix->i_size; i++)
  {
    for (j = 0; j < p_matrix->i_size; j++)
    {
      if (p_matrix->ppi_data[i][j] != 0)
      {
        p_graph->v_edge[k].i_weight = p_matrix->ppi_data[i][j];
        p_graph->v_edge[k].src = p_graph->v_node + i;
        p_graph->v_edge[k].dest = p_graph->v_node + j;
        k++;
      }
    }
  }
}

void graph_free(graph *p_graph)
{
  free(p_graph->v_node);
  free(p_graph->v_edge);
}

void ford_bellman(graph *p_graph)
{
  int i_start, i_end;
  int i, j;
  int i_tmp_valuation;
  char b_short_edge;

  printf("1 : shortest path\n2 : longest path\nchoice : ");
  scanf("%d", &i);
  if (i == 1)
  {
    b_short_edge = 1;
  }
  else
  {
    b_short_edge = 0;
  }

  printf("\nfrom (node number): ");
  scanf("%d", &i_start);
  printf("\nto (node number): ");
  scanf("%d", &i_end);
  printf("\n");

  i_start--;
  i_end--;

  // initialisation
  for (i = 0; i < p_graph->i_nb_node; i++)
  {
    if (b_short_edge)
    {
      p_graph->v_node[i].i_value = INT_MAX;
    }
    else
    {
      p_graph->v_node[i].i_value = -INT_MAX;
    }
  }
  p_graph->v_node[i_start].i_value = 0;

  // valuation
  for (i = 0; i < p_graph->i_nb_node; i++)
  {
    for (j = 0; j < p_graph->i_nb_edge; j++)
    {
      if (p_graph->v_edge[j].src->i_value != abs(INT_MAX)) // source node is valuated
      {
        i_tmp_valuation = p_graph->v_edge[j].src->i_value + p_graph->v_edge[j].i_weight;
        if (b_short_edge)
        {
          if (i_tmp_valuation < p_graph->v_edge[j].dest->i_value)
            p_graph->v_edge[j].dest->i_value = i_tmp_valuation;
        }
        else
        {
          if (i_tmp_valuation > p_graph->v_edge[j].dest->i_value)
            p_graph->v_edge[j].dest->i_value = i_tmp_valuation;
        }
      }
    }
  }

  // display results
  for (i = 0; i < p_graph->i_nb_node; i++)
  {
    if (abs(p_graph->v_node[i].i_value) == INT_MAX)
    {
      printf("No path between \n%s and %s\n", p_graph->v_node[i_start].sz_name, p_graph->v_node[i].sz_name);
      return;
    }
    else
    {
      printf("Distance between \n%s and %s is: %d\n", p_graph->v_node[i_start].sz_name, p_graph->v_node[i].sz_name, p_graph->v_node[i].i_value);
    }
  }

  node *node_current = &p_graph->v_node[i_end];
  printf("\npath is: \n%s", node_current->sz_name);
  do
  {
    for (i = 0; i < p_graph->i_nb_edge; i++)
    {
      if ((p_graph->v_edge[i].dest == node_current) && (p_graph->v_edge[i].src->i_value == node_current->i_value - p_graph->v_edge[i].i_weight))
      {
        node_current = p_graph->v_edge[i].src;
        printf(" %s ", node_current->sz_name);
      }
    }
  } while (node_current != &p_graph->v_node[i_start]);
  printf("\n");
}

#include "node.h"

void node_prefix(node *v_node, char szPrefix[5], int i_nb_node)
{
  int i;
  for (i = 0; i < i_nb_node; i++)
  {
    sprintf(v_node[i].sz_name, "%s%d", szPrefix, i + 1);
  }
}

void node_rename(node *p_node, char sz_name[5])
{
  strcpy(p_node->sz_name, sz_name);
}

void node_swap(node *node_a, node *node_b)
{
  node node_tmp;
  node_tmp.coord = set_coord(node_a->coord.x, node_a->coord.y);
  node_a->coord = set_coord(node_b->coord.x, node_b->coord.y);
  node_b->coord = set_coord(node_tmp.coord.x, node_tmp.coord.y);
}

char set_level(matrix *p_matrix, node *v_node)
{
  int i;
  int i_level = 0;
  matrix matrix_tmp;
  matrix_tmp.i_size = p_matrix->i_size;
  matrix_malloc(&matrix_tmp);

  if (has_loop(p_matrix))
  {
    printf("Error : set_level. A matrix which have loop cannot be used for level calculation");
    return 0;
  }
  else
  {
    matrix_copy(p_matrix, &matrix_tmp);
    for (i = 0; i < matrix_tmp.i_size; i++)
    {
      v_node[i].i_level = -1;
    }

    for (i = 0; i < matrix_tmp.i_size; i++)
    {
      if (has_prev(&matrix_tmp, i))
      {
        v_node[i].i_level = i_level;
      }
    }

    for (i = 0; i < matrix_tmp.i_size; i++)
    {
      if (v_node[i].i_level == i_level)
      {
        matrix_zero_at_line(&matrix_tmp, i);
      }
    }

    while (!all_level_checked(p_matrix, v_node))
    {
      i_level++;
      for (i = 0; i < matrix_tmp.i_size; i++)
      {
        if (has_prev(&matrix_tmp, i) && (v_node[i].i_level == -1))
        {
          v_node[i].i_level = i_level;
        }
      }

      for (i = 0; i < matrix_tmp.i_size; i++)
      {
        if (v_node[i].i_level == i_level)
        {
          matrix_zero_at_line(&matrix_tmp, i);
        }
      }
    }
  }
  matrix_free(&matrix_tmp);
  return 1;
}

char all_level_checked(const matrix *matrice, const node *v_node)
{
  int i;
  for (i = 0; i < matrice->i_size; i++)
  {
    if (v_node[i].i_level < 0)
      return 0;
  }
  return 1;
}

int count_level(node *v_node, int i_level, int i_nb_node)
{
  int i;
  int count_level = 0;

  for (i = 0; i < i_nb_node; i++)
  {
    if (i_level == v_node[i].i_level)
    {
      count_level++;
    }
  }
  return count_level;
}

int node_level_max(node *v_node, int i_nb_node)
{
  int i;
  int i_level_max = 0;

  for (i = 0; i < i_nb_node; i++)
  {
    if (i_level_max < v_node[i].i_level)
      i_level_max = v_node[i].i_level;
  }
  return i_level_max;
}


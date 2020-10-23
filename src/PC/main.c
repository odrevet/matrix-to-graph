#include "../graph.h"
#include "../matrix.h"
#include "../print.h"

void matrix_from_file(matrix *p_matrix, char *path)
{

  FILE *fp = fopen(path, "r");
  fscanf(fp, "%d", &p_matrix->i_size);

  matrix_malloc(p_matrix);

  for (int index_row = 0; index_row < p_matrix->i_size; index_row++)
  {
    for (int index_col = 0; index_col < p_matrix->i_size; index_col++)
    {
      fscanf(fp, "%d", &p_matrix->ppi_data[index_row][index_col]);
    }
  }

  fclose(fp);
}

int main(int argc, char **argv)
{
  matrix o_matrix;
  graph o_graph;

  matrix_from_file(&o_matrix, "test/m.txt"); // TODO from argv
  graph_init(&o_graph, &o_matrix);

  int i_choice;
  do
  {
    printf("0 or less: quit\n");
    printf("1: list edges\n");
    printf("2: print matrix\n");
    printf("3: dict prev\n");
    printf("4: dict next\n");
    printf("Choice: \n");
    scanf("%d", &i_choice);

    switch (i_choice)
    {
    case 1:
      print_edge_list(o_graph.v_edge, o_graph.i_nb_edge);
      break;
    case 2:
      print_matrix(&o_matrix);
      break;
    case 3:
      print_dict_prev(&o_graph);
      break;
    case 4:
      print_dict_next(&o_graph);
      break;
    }

  } while (i_choice > 0);

  graph_free(&o_graph);
  matrix_free(&o_matrix);

  return EXIT_SUCCESS;
}

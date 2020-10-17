#define MIN_AMS 101

#include <tigcclib.h>

#include "io.h"
#include "matrix.h"
#include "display.h"
#include "trigo.h"
#include "sprite.h"

void _main(void)
{
  short i_menu_choice;
  graph *p_graph = NULL;
  matrix *p_matrix = NULL;
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

  p_matrix = malloc(sizeof(matrix));
  p_graph = malloc(sizeof(graph));
  init_all(p_graph, p_matrix, EsiPtr);

  sprite cursor;
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

  //********************** END OF INIT **********************//

  graph_draw(p_graph);
  ST_helpMsg("mtograph V3 - 2020 - Olivier Drevet");
  ngetchx();
  do
  {
    i_menu_choice = menu_display();
    switch (i_menu_choice)
    {
    case 11:
      EsiPtr = open_file();
      if (!is_square_matrix(EsiPtr))
      {
        printf("Error: The matrix must have the same height and width\n");
        ngetchx();
      }
      else
      {
        init_all(p_graph, p_matrix, EsiPtr);
      }
      break;
    case 21:
      graph_draw(p_graph);
      ngetchx();
      break;
    case 22:
      draw_transitive_closure(p_matrix, p_graph);
      break;
    case 23:
      node_move(p_graph);
      break;
    case 24:
      node_swap_coord(p_graph->v_node, p_matrix->i_size);
      break;
    case 25:
      menu_node_rename(p_graph->v_node, p_matrix->i_size);
      break;
    case 26:
      graph_draw(p_graph);
      edge_display_weight(p_graph->v_edge, p_graph->i_nb_edge);
      ngetchx();
      break;
    case 31:
      matrix_draw(p_matrix);
      break;
    case 32:
      edge_list(p_graph->v_edge, matrix_count_edge(p_matrix));
      break;
    case 33:
      node_list(p_graph->v_node, p_matrix->i_size);
      break;
    case 34:
      dict_prev(p_graph);
      break;
    case 35:
      dict_next(p_graph);
      break;
    case 36:
      menu_pow(p_matrix);
      break;
    case 37:
      menu_enclosure(p_matrix);
      break;
    case 38:
      ford_bellman(p_graph);
      break;
    case 4: // cursor
      graph_draw(p_graph);
      sprite_focus(cursor, p_graph, v_key);
      SetIntVec(AUTO_INT_1, interrupt1);
      break;
    }
  } while (i_menu_choice != 5);

  free_all(p_graph, p_matrix);
}

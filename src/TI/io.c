#include "io.h"

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

void set_keyboard(point *v_key)
{
 if (CALCULATOR == 0)
 {
  v_key[UP] = set_coord(0x01, 0x7E);
  v_key[DOWN] = set_coord(0x04, 0x7E);
  v_key[LEFT] = set_coord(0x02, 0x7E);
  v_key[RIGHT] = set_coord(0x08, 0x7E);
  v_key[PLUS] = set_coord(0x02, 0x7D);
  v_key[LESS] = set_coord(0x04, 0x7D);
  v_key[ESC] = set_coord(0x01, 0x3F);
  v_key[ENTER] = set_coord(0x01, 0x7D);
 }
 else
 {
  v_key[UP] = set_coord(0x20, 0x7E);
  v_key[DOWN] = set_coord(0x80, 0x7E);
  v_key[LEFT] = set_coord(0x10, 0x7E);
  v_key[RIGHT] = set_coord(0x40, 0x7E);
  v_key[PLUS] = set_coord(0x10, 0xBF);
  v_key[LESS] = set_coord(0x01, 0xFF);
  v_key[ESC] = set_coord(0x40, 0xBF);
  v_key[ENTER] = set_coord(0x02, 0xFF);
 }
}

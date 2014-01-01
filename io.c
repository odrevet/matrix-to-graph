#include "io.h"

ESI open_file()
{
	ESQ types[1] = {MATRIX_TAG};		//Tag for only load matrix
	HSym file;
	SYM_ENTRY *SymPtr;

	file = VarOpen(types);			//Actually display the window
	if(file.folder == 0)
		exit(0);
	else{
	SymPtr = DerefSym(file);		//file to SYM_ENTRY
	return HToESI(SymPtr->handle); 		//SYM_ENTRY's handle to Expression Stack Index
	}
}

void InitMatrice(matrix *p_matrix, ESI EsiPtr)
{
	int i, j=0;
	p_matrix->i_size = remaining_element_count(EsiPtr-1);
	matrix_malloc(p_matrix);

	i=0;

	if((GetArgType(EsiPtr) != LIST_TAG)||(GetArgType(EsiPtr-1) != LIST_TAG))
		exit(0);

	EsiPtr--;		//pointe sur le premier element de la ligne courante
	while(GetArgType(EsiPtr) != END_TAG){
		EsiPtr--;	//pointer ssur le premier element de la colonne courante
		while(GetArgType(EsiPtr) != END_TAG){			//Remplir la ligne
			p_matrix->ppi_data[i][j] = (GetArgType(EsiPtr) == INT_TAG)?GetIntArg(EsiPtr):(int)estack_number_to_Float(EsiPtr);
			j++;
			SkipArg(EsiPtr);
		}
		i++;
		j=0;
		EsiPtr--;		//Saute le END_TAG
	}
	EsiPtr--;			//saute le END_TAG
}

void SetClavier(point *v_key)
{
	if(CALCULATOR == 0){
		v_key[UP] = set_coord(0x01, 0x7E);
		v_key[DOWN] = set_coord(0x04, 0x7E);
		v_key[LEFT] = set_coord(0x02, 0x7E);
		v_key[RIGHT] = set_coord(0x08, 0x7E);
		v_key[PLUS] = set_coord(0x02, 0x7D);
		v_key[LESS] = set_coord(0x04, 0x7D);
		v_key[ESC] = set_coord(0x01, 0x3F);
		v_key[ENTER] = set_coord(0x01, 0x7D);
	}
	else{
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
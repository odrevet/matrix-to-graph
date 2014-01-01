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

	ESI EsiPtr = top_estack;									//pointer en haut de la pile
	FontSetSys(F_6x8);
	clrscr();

	//Verifie si une matrice est passée en parametre
	if((GetArgType(EsiPtr) != LIST_TAG)||(GetArgType(EsiPtr-1) != LIST_TAG)){		//Ce n'est pas une matrice
		EsiPtr = open_file();		//Si ce n'est pas la cas, ouvrir une fenetre
	}

	//sym = DerefSym(SymFind(GetSymstrArg(EsiPtr)));

	if(! is_square_matrix(EsiPtr)){
		printf("\Error : The matrix must be a squared matrix (same height and width). ");
		ngetchx();
		exit(0);
	}

	p_matrix = malloc(sizeof(matrix));
	p_graph = malloc(sizeof(graph));
	init_all(p_graph, p_matrix, EsiPtr);

	//Initialisation du curseur
	sprite UnCurseur;
	unsigned char sprite[12] = {
	0x40,0x60,0x70,0x78,0x7C,0x7E,0x7F,0x7C,
	0x4C,0x0E,0x06,0x06
	};

	UnCurseur.i_size = sizeof(sprite);
	UnCurseur.sz_bitmap = malloc(UnCurseur.i_size * sizeof(UnCurseur.sz_bitmap));
	memcpy(UnCurseur.sz_bitmap, sprite, UnCurseur.i_size);
	UnCurseur.coord = set_coord(LCD_WIDTH/2, LCD_HEIGHT/2);
	sprite_draw(UnCurseur);

	//initialisation du clavier
	SetClavier(v_key);

  INT_HANDLER interrupt1 = GetIntVec(AUTO_INT_1); 									// save auto-interrupt 1 (bottom text)

	//********************** END OF INIT **********************//
	
	graph_draw(p_graph);
	ST_helpMsg("mtograph V2-2007/2008-Olivier DREVET");
	ngetchx();
	do{
		i_menu_choice = menu_display();		//Afficher le menu
		switch(i_menu_choice){
			case 11:	//Charger une matrice
				EsiPtr = open_file();			//pointer vers la nouvelle matrice
				if(! is_square_matrix(EsiPtr)){
					printf("Ce fichier n'est pas une matrice carrée. \n");
					ngetchx();
				}
				else{
					init_all(p_graph, p_matrix, EsiPtr);
				}
			break;
			case 21:
				graph_draw(p_graph);
				ngetchx();
			break;
			case 22:
				MenuDessinFermetureTransitive(p_matrix, p_graph);
			break;
			case 23:
				summit_move(p_graph);
			break;
			case 24:
				summit_swap_coord(p_graph->v_summit, p_matrix->i_size);
			break;
			case 25:
				menu_summit_rename(p_graph->v_summit, p_matrix->i_size);
			break;
			case 26:
				graph_draw(p_graph);
				path_display_weight(p_graph->v_path, p_graph->i_nb_path);
				ngetchx();
			break;
			case 31:
				matrix_draw(p_matrix);
			break;
			case 32:
				path_list(p_graph->v_path, matrix_count_path(p_matrix));
			break;
			case 33:
				summit_list(p_graph->v_summit, p_matrix->i_size);
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
			case 4:	// Menu Curseur
					graph_draw(p_graph);
					sprite_focus(UnCurseur, p_graph, v_key);
					SetIntVec(AUTO_INT_1,interrupt1);
					break;
		}
	}while(i_menu_choice!=5);
	
	free_all(p_graph, p_matrix);

}

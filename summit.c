#include "summit.h"

void summit_prefix(summit *v_summit, char szPrefi_x[5], int i_nb_summit)
{
	int i;
	clrscr();
	for(i=0;i<i_nb_summit;i++){
		sprintf(v_summit[i].sz_name, "%s%d", szPrefi_x, i+1);
	}
}


void summit_rename(summit *UnSommet, char szNouveauNom[5])
{
	printf("\nRenomme %s en %s\n", UnSommet->sz_name, szNouveauNom);
	ngetchx();
	strcpy(UnSommet->sz_name, szNouveauNom);
}


void summit_swap(summit *UnSommetA, summit *UnSommetB)
{
	summit TmpSommet;
	TmpSommet.coord = set_coord(UnSommetA->coord.i_x, UnSommetA->coord.i_y);
	UnSommetA->coord = set_coord(UnSommetB->coord.i_x, UnSommetB->coord.i_y);
	UnSommetB->coord = set_coord(TmpSommet.coord.i_x, TmpSommet.coord.i_y);

}

char set_level(matrix *p_matrix, summit *v_summit)
{
	int i;
	int i_level = 0;
	matrix MatriceTemp;
	MatriceTemp.i_size = p_matrix->i_size;
	matrix_malloc(&MatriceTemp);

	if(has_loop(p_matrix)){
		printf("Error : set_level. A matrix which have loop cannot be used to calculate levels");
		return 0;
	}
	else{
		//Initialisation
		matrix_copy(p_matrix, &MatriceTemp);
		for(i=0;i<MatriceTemp.i_size;i++){
				v_summit[i].i_level = -1;
		}

		for(i=0;i<MatriceTemp.i_size;i++){			//Les sommets sans precedents sont de NV 0
			if(has_prev(&MatriceTemp, i)){
				v_summit[i].i_level = i_level;
			}
		}

		for(i=0;i<MatriceTemp.i_size;i++){
			if(v_summit[i].i_level == i_level){
				matrix_zero_at_line(&MatriceTemp, i);
			}
		}
		//Fin init

		while(!all_level_checked(p_matrix, v_summit)){
			i_level++;
			for(i=0;i<MatriceTemp.i_size;i++){
				if(has_prev(&MatriceTemp, i)&&(v_summit[i].i_level==-1)){
					v_summit[i].i_level = i_level;
				}
			}

			for(i=0;i<MatriceTemp.i_size;i++){
				if(v_summit[i].i_level == i_level){
					matrix_zero_at_line(&MatriceTemp, i);
				}
			}	//Fin for
		}	//Fin while
	}	//Fin si has_loop
	matrix_free(&MatriceTemp);
	return 1;
}

char all_level_checked(const matrix *matrice, const summit *v_summit)
{
	int i;
	for(i=0;i<matrice->i_size;i++){
		if(v_summit[i].i_level < 0)
			return 0;
	}
	return 1;
}


int count_level(summit *v_summit, int i_level, int i_nb_summit)
{
	int i;
	int iNbSommetsNv=0;

	for(i=0;i<i_nb_summit;i++){
		if(i_level==v_summit[i].i_level){
			iNbSommetsNv++;
		}
	}
	return iNbSommetsNv;
}

int NvMax(summit *v_summit, int i_nb_summit)
{
	int i;
	int iNiveauMax=0;

	for(i=0;i<i_nb_summit;i++){
		if(iNiveauMax<v_summit[i].i_level)
			iNiveauMax = v_summit[i].i_level;
	}
	return iNiveauMax;
}

void sort_by_level(summit *v_summit, int i_nb_summit)
{
	int i;
	int iDecalage;
	int *NvCourant = calloc(NvMax(v_summit, i_nb_summit)+1, sizeof(int));		//Stocke l'index pour chaque niveau
	iDecalage = LCD_WIDTH/(NvMax(v_summit, i_nb_summit)+2);

	//horizontal
	for(i=0;i<i_nb_summit;i++){
			v_summit[i].coord.i_x = iDecalage + iDecalage * v_summit[i].i_level;
	}

	//Vertical
	for(i=0;i<i_nb_summit;i++){
		iDecalage = LCD_HEIGHT/(count_level(v_summit, v_summit[i].i_level, i_nb_summit)+1);
		v_summit[i].coord.i_y = iDecalage + iDecalage * (NvCourant[v_summit[i].i_level]);
		NvCourant[v_summit[i].i_level]++;
	}
	free(NvCourant);
}

void summit_list(summit *v_summit, int i_nb_summit)
{
	int i;
	clrscr();
	printf("Liste des sommets...\n");
	for(i=0;i<i_nb_summit;i++){
		printf("N°%d Nom:%s coord(%d,%d)", i+1, v_summit[i].sz_name, v_summit[i].coord.i_x, v_summit[i].coord.i_y);
		printf("\nNiveau:%d\n", v_summit[i].i_level);
		printf("\n");
			if (i%3==0){		//marque une pause
				ngetchx();
			}
	}
	ngetchx();
}

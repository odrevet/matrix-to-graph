#include "matrix.h"


void matrix_malloc(matrix *p_matrix)
{
	int i;
	p_matrix->ppi_data=(int**)malloc(p_matrix->i_size*sizeof(int*));
	for(i=0;i<p_matrix->i_size;i++)p_matrix->ppi_data[i] = (int*)malloc(p_matrix->i_size*sizeof(int));
}


void matrix_free(matrix *p_matrix)
{
	int i;
	for(i=0;i<p_matrix->i_size;i++){
		free(p_matrix->ppi_data[i]);
	}
	free(p_matrix->ppi_data);
}


char matrix_product(const matrix *A, const matrix *B, matrix *Z)
{
	int i,j,k;
	if(A->i_size!=B->i_size){
		printf("matrix_product error : the two matrix must have the same size");
		return 0;
	}

	matrix_zero(Z);
	for(i=0;i<A->i_size;i++){
		for(j=0;j<B->i_size;j++){
			for(k=0;k<A->i_size;k++){
				Z->ppi_data[i][j] += A->ppi_data[i][k] * B->ppi_data[k][j];
			}
		}
	}
	
	return 1;
}


void matrix_copy(const matrix *MatriceOrig, matrix *MatriceDest)
{
	int i,j;

	for(i=0;i<MatriceDest->i_size;i++){
		for(j=0;j<MatriceOrig->i_size;j++){
			MatriceDest->ppi_data[i][j]=MatriceOrig->ppi_data[i][j];
		}
	}
}


void matrix_zero_at_line(matrix *p_matrix, int iLigne)
{
	int i;
	for(i=0;i<p_matrix->i_size;i++){
			p_matrix->ppi_data[iLigne][i]=0;
	}
}


void matrix_zero(matrix *p_matrix)
{
	int i, j;
	for(i=0;i<p_matrix->i_size;i++){
		for(j=0;j<p_matrix->i_size;j++){
			p_matrix->ppi_data[i][j]=0;
		}
	}
}


char matrix_is_zero(matrix *p_matrix)
{
	int i, j;
	for(i=0;i<p_matrix->i_size;i++){
		for(j=0;j<p_matrix->i_size;j++){
			if(p_matrix->ppi_data[i][j]!=0)
				return 0;
		}
	}
	return 1;
}


void matrix_pow(const matrix *p_matrix, int Puissance, matrix *MatriceRes)
{
	matrix MatriceTemp;
	int i;

	MatriceTemp.i_size = p_matrix->i_size;
	matrix_malloc(&MatriceTemp);
	matrix_copy(p_matrix, &MatriceTemp);

	for(i=0;i<Puissance-1;i++){
		matrix_product(&MatriceTemp, p_matrix, MatriceRes);
		matrix_copy(MatriceRes, &MatriceTemp);
	}
	matrix_free(&MatriceTemp);
}


void matrix_colsure(const matrix *p_matrix, matrix *MatriceRes)
{
	matrix MatriceTemp;
	int i;

	MatriceTemp.i_size = p_matrix->i_size;
	matrix_malloc(&MatriceTemp);
	matrix_copy(p_matrix, &MatriceTemp);
	matrix_copy(p_matrix, MatriceRes);

	for(i=2;i<p_matrix->i_size-1;i++){
		matrix_pow(p_matrix, i, &MatriceTemp);
		matrix_add(MatriceRes, &MatriceTemp, MatriceRes);
	}
	matrix_free(&MatriceTemp);
}


void matrix_bin(matrix *p_matrix)
{
	int i, j;
	for(i=0;i<p_matrix->i_size;i++){
		for(j=0;j<p_matrix->i_size;j++){
			if(p_matrix->ppi_data[i][j]!=0){
				p_matrix->ppi_data[i][j] = 1;
			}
		}
	}
}


void matrix_add(const matrix *MatriceA, const matrix *MatriceB, matrix *MatriceRes)
{
	int i, j;
	for(i=0;i<MatriceA->i_size;i++){
		for(j=0;j<MatriceB->i_size;j++){
			MatriceRes->ppi_data[i][j]= MatriceA->ppi_data[i][j]+MatriceB->ppi_data[i][j];
		}
	}
}


int matrix_count_path(matrix *p_matrix)
{
	int i, j;
	int i_nb_path=0;

	for(i=0;i<p_matrix->i_size;i++){
		for(j=0;j<p_matrix->i_size;j++){
			if(p_matrix->ppi_data[i][j]!=0){
						i_nb_path++;
			}
		}
	}
	return i_nb_path;
}


char has_next(const matrix *p_matrix, int iLigne)
{
	int iColonne;

	for(iColonne=0;iColonne<p_matrix->i_size;iColonne++){		//Pour cette colonne
		if(p_matrix->ppi_data[iColonne][iLigne] != 0){
			return 0;
		}
	}
	return 1;
}


char has_prev(const matrix *p_matrix, int iColonne)
{
	int iLigne;

	for(iLigne=0;iLigne<p_matrix->i_size;iLigne++){		//Pour cette ligne
		if(p_matrix->ppi_data[iLigne][iColonne] != 0){
			return 0;
		}
	}
	return 1;
}


char has_loop(const matrix *matrice)
{
	int i, j;
	for(i=0;i<matrice->i_size;i++){					//Sommets d'origine
		for(j=0;j<matrice->i_size;j++){			  //Sommets d'arrivée
			if((matrice->ppi_data[j][i]!=0) && (matrice->ppi_data[i][j]!=0)){
						return 1;
			}
		}
	}
	return 0;
}

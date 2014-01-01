#include "graph.h"

void init_all(graph *p_graph, matrix *p_matrix, ESI EsiPtr)
{
	int i;

	InitMatrice(p_matrix, EsiPtr);							//Expression stack -> C

	//Initialisation du graphe
	p_graph->i_nb_path = matrix_count_path(p_matrix);
	p_graph->i_nb_summit = p_matrix->i_size;
	p_graph->i_ray = 10;

	//Initialisation des sommets
	p_graph->v_summit = calloc(p_matrix->i_size, sizeof(summit));
	summit_prefix(p_graph->v_summit, (char*)"S", p_matrix->i_size);

	//Initialisation des chemins
	p_graph->v_path = malloc(matrix_count_path(p_matrix) * sizeof(path));
	set_path(p_matrix, p_graph);

	if(set_level(p_matrix, p_graph->v_summit)){
		sort_by_level(p_graph->v_summit, p_matrix->i_size);
	}
	else{
		for(i=0;i<p_matrix->i_size;i++){
			p_graph->v_summit[i].coord = set_coord(i*(LCD_WIDTH/p_matrix->i_size), i*(LCD_HEIGHT/p_matrix->i_size));
		}
	}
}


void free_all(graph *p_graph, matrix *p_matrix)
{
	matrix_free(p_matrix);
	free(p_matrix);
	free(p_graph->v_summit);
	free(p_graph->v_path);
	free(p_graph);
}


void ford_bellman(graph *p_graph)
{
 	int iDepart, iArrive;
 	int i, j;
	int iTempValuation;
	char bCheminMin;

 	clrscr();
	printf("Recherche d'un chemin de valeur extremale\n");
	printf("Algorithme de Ford-Bellman\n\n");
	printf("1 : path le plus court\n2 : path le plus long\nChoix : ");
	scanf("%d", &i);
	if(i==1){
		bCheminMin = 1;
	}
	else{
		bCheminMin = 0;
	}

	printf("\nN° sommet de départ : ");
	scanf("%d", &iDepart);
	printf("\nN° sommet d'arrivée : ");
	scanf("%d", &iArrive);
	printf("\n");

	iDepart--;
	iArrive--;

	//Initialisation
	for(i=0;i<p_graph->i_nb_summit;i++){
		 if(bCheminMin){
				p_graph->v_summit[i].i_value = INT_MAX;
		 }
		 else{
			p_graph->v_summit[i].i_value = -INT_MAX;
		 }
	}
	p_graph->v_summit[iDepart].i_value = 0;

	//valuation
	for (i=0;i<p_graph->i_nb_summit;i++) {																					//Pour tout les sommets
        for (j=0;j<p_graph->i_nb_path;j++){																				//Pour tout les chemins
            if(p_graph->v_path[j].src->i_value != abs(INT_MAX)){									//Si le sommet source du chemin est valué
                iTempValuation = p_graph->v_path[j].src->i_value + p_graph->v_path[j].i_weight;		//Le retenir avec le poids du chemin
                if(bCheminMin){
	                if(iTempValuation < p_graph->v_path[j].dest->i_value) 		//Si le nombre retenu est inf au sommet de dest
	                  p_graph->v_path[j].dest->i_value = iTempValuation;			//Valuer ce sommet avec le nombre retenu
	              }
	              else{
								 	if(iTempValuation > p_graph->v_path[j].dest->i_value) 		//Si le nombre retenu est inf au sommet de dest
	                  p_graph->v_path[j].dest->i_value = iTempValuation;			//Valuer ce sommet avec le nombre retenu
                }	//Fin si
            }	//Fin si
        } //Fin pour chemins
  } //Fin pour sommets

	//Si le sommet n as pas ete value alors quitter, sinon afficher la distance
  for (i=0;i<p_graph->i_nb_summit;i++){
  	if(abs(p_graph->v_summit[i].i_value) == INT_MAX){
			printf("PAS DE CHEMINS entre \n%s et %s ! \n", p_graph->v_summit[iDepart].sz_name, p_graph->v_summit[i].sz_name);
			ngetchx();
			return;
  	}
  	else{
  		printf("La distance entre \n%s et %s est : %d\n", p_graph->v_summit[iDepart].sz_name, p_graph->v_summit[i].sz_name, p_graph->v_summit[i].i_value);
  	}

  	if (i%4==0){		//marque une pause
			ngetchx();
		}
  }

	summit *SommetCourant = &p_graph->v_summit[iArrive];
	printf("\nLe chemin est : \n(%s", SommetCourant->sz_name);
	do{
		for (i=0;i<p_graph->i_nb_path;i++){		//Pour tout les chemins, si meme adresse et valu source == courant - poid
			if((p_graph->v_path[i].dest == SommetCourant)&&(p_graph->v_path[i].src->i_value == SommetCourant->i_value-p_graph->v_path[i].i_weight)){
				SommetCourant = p_graph->v_path[i].src;
				printf(" %s ", SommetCourant->sz_name);
			}
		}
	}while(SommetCourant != &p_graph->v_summit[iDepart]);
	printf(")");
}

void set_path(matrix *p_matrix, graph *p_graph)
{
	int i, j, k=0;

	for(i=0;i<p_matrix->i_size;i++){
		for(j=0;j<p_matrix->i_size;j++){
			if(p_matrix->ppi_data[i][j] != 0){
				p_graph->v_path[k].i_weight = p_matrix->ppi_data[i][j];
				p_graph->v_path[k].src = &p_graph->v_summit[i];
				p_graph->v_path[k].dest = &p_graph->v_summit[j];
				k++;
			}
		}
	}
}

void summit_move(graph *p_graph)
{
	int iNumSommet;
	point Tempcoord;
	clrscr();

	summit_list(p_graph->v_summit, p_graph->i_nb_summit);

	do{
			printf("Déplacer le sommet N°  : ");
			scanf("%d", &iNumSommet);
			iNumSommet--;
			if((iNumSommet>p_graph->i_nb_summit)||(p_graph->i_nb_summit<=0))
			{
				printf("Ce sommet n'existe pas\n");
			}

	}while(iNumSommet>p_graph->i_nb_summit);

	do{
		printf("\nEntrez la nouvelle coord\nhorizontal (inf à %d)\n", LCD_WIDTH-p_graph->i_ray);
		scanf("%d", &Tempcoord.i_x);

		if((Tempcoord.i_x>LCD_WIDTH-p_graph->i_ray)||(Tempcoord.i_x<0))
		{
			printf("\ncoord hors de l' écran ! \n");
		}

	}while(Tempcoord.i_x>LCD_WIDTH);

		do{
		printf("\nEntrez la nouvelle coord\nvertical (inf à %d)\n", LCD_HEIGHT-p_graph->i_ray);
		scanf("%d", &Tempcoord.i_y);

		if((Tempcoord.i_y>LCD_HEIGHT-p_graph->i_ray)||(Tempcoord.i_y<0))
		{
			printf("\ncoord hors de l' écran ! \n");
		}

	}while(Tempcoord.i_y>LCD_HEIGHT);
	p_graph->v_summit[iNumSommet].coord = set_coord(Tempcoord.i_x, Tempcoord.i_y);
}
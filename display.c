#include "display.h"

//Dessiner un menu et renvoyer la valeur choisi
short menu_display()
{
	HANDLE menu_menu= MenuNew(2, LCD_WIDTH, 18);  			// Déclare le menu "non-exécutable".
  HANDLE menu_exec;    																// Déclare le "menu exécutable".
  ICON icoCrayon = {{0x0, 0x0, 0xC0, 0x120, 0x3A0, 0x4C0, 0x880, 0x1100, 0x2200, 0x4400, 0xC800, 0xF000, 0xE000, 0xC000, 0x8000, 0x0}};
	ICON icoCurseur = {{0x40,0x60,0x70,0x78,0x7C,0x7E,0x7F,0x7C,0x4C,0x0E,0x06,0x06}};
  MenuAddText(menu_menu, 0, "Fichier", 1, 0);     //(HANDLE Handle, short ParentID, const char *Text, short ID, short Flags);
  MenuAddText(menu_menu, 1, "Charger une matrice", 11, 0);

  MenuAddIcon(menu_menu, 0, &icoCrayon, 2, 0);
  MenuAddText(menu_menu, 2, "Dessiner le graphe", 21, 0);
  MenuAddText(menu_menu, 2, "Fermeture transitive", 22, 0);
  MenuAddText(menu_menu, 2, "Déplacer un sommet", 23, 0);
  MenuAddText(menu_menu, 2, "Intervertion sommets", 24, 0);
	MenuAddText(menu_menu, 2, "Renommer sommets", 25, 0);
	MenuAddText(menu_menu, 2, "Afficher les valuation", 26, 0);

  MenuAddText(menu_menu, 0, "Afficher", 3, 0);
  MenuAddText(menu_menu, 3, "Afficher la matrice", 31, 0);
  MenuAddText(menu_menu, 3, "Lister les chemins", 32, 0);
  MenuAddText(menu_menu, 3, "Lister les sommets", 33, 0);
	MenuAddText(menu_menu, 3, "Dico des précédents", 34, 0);
	MenuAddText(menu_menu, 3, "Dico des suivants", 35, 0);
  MenuAddText(menu_menu, 3, "matrix puissance", 36, 0);
  MenuAddText(menu_menu, 3, "Fermeture transitive", 37, 0);
  MenuAddText(menu_menu, 3, "Rechercher un chemin", 38, 0);

  MenuAddIcon(menu_menu, 0, &icoCurseur, 4, 0);
  MenuAddText(menu_menu, -1, "Quitter", 5, 0);

  menu_exec = MenuBegin(HeapDeref(menu_menu), 0, 0, 0);   // Permet d'obtenir le "menu-exécutable".
	return MenuKey(menu_exec, GKeyIn(NULL,0));      							// Active le menu, et stocke la valeur choisie dans la variable valeur_menu.
}



void path_list(const path *v_path, int i_nb_path)
{
	int i;
	clrscr();
	printf("Liste des chemins...\n");
	for(i=0;i<i_nb_path;i++){
		printf("%s --%d--> %s\n", v_path[i].src->sz_name, v_path[i].i_weight, v_path[i].dest->sz_name);
		if (i%12==0){		//marque une pause
			ngetchx();
		}
	}
	ngetchx();
}

void arrow_draw(point point1, point point2, point point3)
{
	FillTriangle(point1.i_x, point1.i_y, point2.i_x, point2.i_y, point3.i_x, point3.i_y, ScrRect, A_NORMAL);
}

void graph_draw(const graph *p_graph)
{
	int i;
	float fAngle;
	point pointSource, pointDest;
	arrow *Fleche = malloc(sizeof(arrow));
	unsigned short Boucle[16] = {
	0x0000,0x0000,0x0F80,0x1040,0x2020,0x4010,0x4010,0x4010,
	0x40FE,0x407C,0x2038,0x1010,0x0000,0x0000,0x0000,0x0000
	};

	Fleche->nWidth = 5;
	Fleche->fTheta = 0.25;
	clrscr();

	//Dessiner les sommets
	for(i=0;i<p_graph->i_nb_summit;i++){
		DrawStr(p_graph->v_summit[i].coord.i_x-p_graph->i_ray/2, p_graph->v_summit[i].coord.i_y-p_graph->i_ray/2, p_graph->v_summit[i].sz_name, A_NORMAL); 	//Nom du sommet
		DrawClipEllipse(p_graph->v_summit[i].coord.i_x, p_graph->v_summit[i].coord.i_y, p_graph->i_ray, p_graph->i_ray, ScrRect, A_NORMAL);	//Cercle
	}

	//dessiner les chemins
	for(i=0;i<p_graph->i_nb_path;i++){
		if(p_graph->v_path[i].src == p_graph->v_path[i].dest){
			Sprite16(p_graph->v_path[i].src->coord.i_x,p_graph->v_path[i].dest->coord.i_y-p_graph->i_ray*2,16, Boucle, LCD_MEM,SPRT_XOR);
		}
		else{
			fAngle=get_angle(p_graph->v_path[i].src, p_graph->v_path[i].dest);	//Recupere l'angle (radian)

			pointSource = ortho_projection(p_graph->v_path[i].src->coord, -p_graph->i_ray, fAngle);
			pointDest = ortho_projection(p_graph->v_path[i].dest->coord, p_graph->i_ray, fAngle);
			PtArrowTo(pointSource, pointDest, Fleche);
			/*line_draw(pointSource, pointDest);
			fAngle=get_angle(&pointSource, &pointDest);												//Recupere le nouvel angle
			Fleche.centre = ortho_projection(p_graph->v_path[i].dest->coord, p_graph->i_ray+Fleche.i_height/2, fAngle);
			Fleche.v_point[0] = set_coord(Fleche.centre.i_x+Fleche.i_height/2, Fleche.centre.i_y+Fleche.i_base/2);
			Fleche.v_point[1] = set_coord(Fleche.v_point[0].i_x, Fleche.v_point[0].i_y-Fleche.i_base);
			Fleche.v_point[2] = set_coord(Fleche.centre.i_x-Fleche.i_height/2, Fleche.centre.i_y);
			arow_draw(rotate(fAngle, Fleche.v_point[0], Fleche.centre), rotate(fAngle, Fleche.v_point[1], Fleche.centre), rotate(fAngle, Fleche.v_point[2], Fleche.centre));
			*/
			//free(Fleche);
		}
	}
}

void matrix_draw(matrix *matrice)
{
	int i,j;
	clrscr();
	for(i=0;i<matrice->i_size;i++){
		for(j=0;j<matrice->i_size;j++){
			printf(" %d ", matrice->ppi_data[i][j]);
		}
		printf("\n");
	}
	ngetchx();
}

void dict_prev(const graph *p_graph)
{
	int i, j;
	clrscr();
	printf("Si      | P(Xi)\n-----------------\n");
	for(i=0;i<p_graph->i_nb_summit;i++){			//Pour tout les sommets
		printf("%s      | ", p_graph->v_summit[i].sz_name);
		for(j=0;j<p_graph->i_nb_path;j++){							//Pour tout les chemins
			if(&p_graph->v_summit[i] == p_graph->v_path[j].dest){		//Si & de sommet courant == & de sommet dest d'un chemin
				printf(" %s ", p_graph->v_path[j].src->sz_name);				//Affiche le sommet source
			}
		} //fin pour
		printf("\n");
	}//fin pour
	ngetchx();
}

void dict_next(const graph *p_graph)
{
	int i, j;
	clrscr();
	printf("Si      | S(Xi)\n-----------------\n");
	for(i=0;i<p_graph->i_nb_summit;i++){			//Pour tout les sommets
		printf("%s      | ", p_graph->v_summit[i].sz_name);
		for(j=0;j<p_graph->i_nb_path;j++){							//Pour tout les chemins
			if(&p_graph->v_summit[i] == p_graph->v_path[j].src){		//Si & de sommet courant == & de sommet source d'un chemin
				printf(" %s ", p_graph->v_path[j].dest->sz_name);		//Affiche le sommet dest
			}
		} //fin pour
		printf("\n");
	}//fin pour
	ngetchx();
}

void summit_swap_coord(summit *v_summit, int i_nb_summit)
{
	int i, j;
	summit_list(v_summit, i_nb_summit);
	printf("Echanger le sommet : \n");
	scanf("%d", &i);
	printf("\nAvec le sommet : \n");
	scanf("%d", &j);
	i--;
	j--;
	if(i>=1 && i<=i_nb_summit && j>=1 && j<=i_nb_summit){
		summit_swap(&v_summit[i], &v_summit[j]);
	}
}

void menu_enclosure(matrix *p_matrix)
{
	matrix MatriceTemp;

	MatriceTemp.i_size = p_matrix->i_size;
	matrix_malloc(&MatriceTemp);
	matrix_copy(p_matrix, &MatriceTemp);

	matrix_colsure(p_matrix, &MatriceTemp);
	matrix_draw(&MatriceTemp);

	matrix_free(&MatriceTemp);
	ngetchx();
}

void MenuDessinFermetureTransitive(matrix *p_matrix, graph *p_graph)
{
	matrix MatriceTemp;
	graph GrapheTemp;
	int i;

	MatriceTemp.i_size = p_matrix->i_size;
	matrix_malloc(&MatriceTemp);
	matrix_copy(p_matrix, &MatriceTemp);

	matrix_colsure(p_matrix, &MatriceTemp);

	//Initialisation du graphe
	GrapheTemp.i_nb_path = matrix_count_path(&MatriceTemp);
	GrapheTemp.i_nb_summit = MatriceTemp.i_size;
	GrapheTemp.i_ray = p_graph->i_ray;

	//Initialisation des sommets
	GrapheTemp.v_summit = calloc(MatriceTemp.i_size, sizeof(summit));
	for(i=0;i<MatriceTemp.i_size;i++){
		strcpy(GrapheTemp.v_summit[i].sz_name, p_graph->v_summit[i].sz_name);
		GrapheTemp.v_summit[i].coord = set_coord(p_graph->v_summit[i].coord.i_x, p_graph->v_summit[i].coord.i_y);
	}

	GrapheTemp.v_path = malloc(matrix_count_path(&MatriceTemp) * sizeof(path));
	set_path(&MatriceTemp, &GrapheTemp);
	graph_draw(&GrapheTemp);
	ST_helpMsg("Dessin de la FERMETURE TRANSITIVE. ");
	ngetchx();
	matrix_free(&MatriceTemp);
	free(GrapheTemp.v_summit);
	free(GrapheTemp.v_path);
}

void menu_pow(matrix *p_matrix)
{
	int iPuissance;
	matrix MatriceTemp;
	MatriceTemp.i_size = p_matrix->i_size;
	matrix_malloc(&MatriceTemp);
	matrix_copy(p_matrix, &MatriceTemp);

	clrscr();
	printf("Entrez la puissance : ");
	scanf("%d", &iPuissance);
	matrix_pow(p_matrix, iPuissance, &MatriceTemp);
	matrix_draw(&MatriceTemp);
	matrix_free(&MatriceTemp);
}

void menu_summit_rename(summit *v_summit, int i_nb_summit)
{
		short int iSousMenuChoi_x;
		int i;
		char *sz_name = NULL;
		clrscr();
		printf("1 : Renommer les sommets\navec un prefi_x.\n\n2 : Donner un nouveau nom à un sommet en particulier\n\n3: Renommer tout \nles sommets à la suite\n\nChoi_x : ");
		scanf("%hd", &iSousMenuChoi_x);
		if(iSousMenuChoi_x==1){
		printf("\nEntrez le nouveau préfi_x\n(moins de 5 caratères)\n");
		scanf("%s", sz_name);
		summit_prefix(v_summit, sz_name, i_nb_summit);
		}
		else if(iSousMenuChoi_x==2){
			summit_list(v_summit, i_nb_summit);
			printf("Quel sommet renommer ? \n");
			scanf("%d", &i);
			printf("\nEntrez le nouveau nom\n");
			scanf("%s", sz_name);
			summit_rename(&v_summit[i-1], sz_name);

		}
		else if(iSousMenuChoi_x==3){
			for(i=0;i<i_nb_summit;i++){
				strcpy(sz_name, "");
				printf("\nN° %d Nom actuel : %s\nNouveau Nom : ", i+1, v_summit[i].sz_name);
				scanf("%s", sz_name);
				if(strcmp(sz_name, NULL))
					summit_rename(&v_summit[i], sz_name);
				else
					printf("\n%s Garde son nom\n",v_summit[i].sz_name);
			}
		}
}

void path_display_weight(path *v_path, int i_nb_path)
{
	int i;
	char szValue[5];
	for(i=0;i<i_nb_path;i++){
		sprintf(szValue, "%d", v_path[i].i_weight);
		if(v_path[i].src == v_path[i].dest){
			DrawStr((v_path[i].src->coord.i_x+v_path[i].dest->coord.i_x)/2, (v_path[i].src->coord.i_y+v_path[i].dest->coord.i_y)/2-26, szValue, A_NORMAL);
		}
		else{
			DrawStr((v_path[i].src->coord.i_x+v_path[i].dest->coord.i_x)/2, (v_path[i].src->coord.i_y+v_path[i].dest->coord.i_y)/2+4, szValue, A_NORMAL);
		}
	}
}

void line_draw(point pointSource, point pointDest)
{
  short x = pointSource.i_x, y = pointSource.i_y;
  short dx = abs (pointDest.i_x - pointSource.i_x), dy = abs (pointDest.i_y - pointSource.i_y);
  short ystep = (pointSource.i_y < pointDest.i_y) ? 1 : -1, pystep = 30 * ystep;
  short mov = dx ? 0 : -1;
  unsigned char *ptr = (char*)LCD_MEM + 30 * y + (x >> 3);
  short mask = 1 << (~x & 7);
  if (pointSource.i_x < pointDest.i_x)
    while (x != pointDest.i_x || y != pointDest.i_y)
      {
        *ptr |= mask;
        if (mov < 0) y += ystep, ptr += pystep, mov += dx;
        else
          {
            mov -= dy;
            if (++x & 7) mask >>= 1;
            else ptr++, mask = 0x80;
          }
      }
  else
    while (x != pointDest.i_x || y != pointDest.i_y)
      {
        *ptr |= mask;
        if (mov < 0) y += ystep, ptr += pystep, mov += dx;
        else
          {
            mov -= dy;
            if (x-- & 7) mask <<= 1;
            else ptr--, mask = 1;
          }
      }
}

void temporize(short int time) {
	short int randNum;
	while (time-- > 0) {
		randNum = rand() % time;
	}
}

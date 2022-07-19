/*
	created by: Marivone Kebou Kitio
		    Master I - Datasciences
*/


#include <stdio.h>
#include <stdlib.h>
#include "fonction.h"
#include <string.h>
//#include <conio.h>
#include <math.h>

// PROGRAMME PRINCIPAL  

int main(int argc,char **argv){
    //system("color 63");

    //Ouvrir le fichier de l'image
    if(argc == 3 && strcmp(argv[1],"hist") == 0){

        //Ouvrir le fichier de l'image
        FILE *fichier = NULL;
        fichier = fopen(argv[2],"r");
        int **image = NULL;
        image = creation_image(fichier);

        //Dimension de l'image
        fichier = fopen(argv[2],"r");
        int *dim = NULL;
        dim = get_dim(fichier);

        //Histogramme de l'image
        int* histogramme = NULL;
        histogramme=get_hist(dim,image);
        for(int i=0;i<256;i++){
            printf("pixel %d : %d\n",i,histogramme[i]);
        }
    }
    else if(argc == 4 && strcmp(argv[1],"lumin") == 0){

        FILE *fichier = NULL;
        fichier = fopen(argv[2],"r");
        int **image = NULL;
        image = creation_image(fichier);

        //Dimension de l'image
        fichier = fopen(argv[2],"r");
        int *dim = NULL;
        dim = get_dim(fichier);

        //Luminance
        int **matrix_brillance=NULL;
        matrix_brillance=brillance(dim,image);
        build_file(matrix_brillance,dim[0],dim[1],argc,argv);
    }
    else if(argc == 4 && strcmp(argv[1],"translin")==0){

        FILE *fichier = NULL;
        fichier = fopen(argv[2],"r");
        int **image = NULL;
        image = creation_image(fichier);

        //Dimension de l'image
        fichier = fopen(argv[2],"r");
        int *dim = NULL;
        dim = get_dim(fichier);

        //Transformation lineaire
        int **matrice_transf_lin=NULL;
        matrice_transf_lin= lin_transf(dim,image);
        build_file(matrice_transf_lin,dim[0],dim[1],argc,argv);

    }
    else if(argc == 4 && strcmp(argv[1],"transsat")==0){

        FILE *fichier = NULL;
        fichier = fopen(argv[2],"r");
        int **image = NULL;
        image = creation_image(fichier);

        //Dimension de l'image
        fichier = fopen(argv[2],"r");
        int *dim = NULL;
        dim = get_dim(fichier);

        //Transformation par saturation
        int **matrice_transf_satur=NULL;
        int min=0,max=0;
        printf("Entrer la valeur minimale :");
        scanf("%d",&min);
        printf("Entrer la valeur maximale :");
        scanf("%d",&max);
        matrice_transf_satur=satur_transf(dim,image,min,max);
        build_file(matrice_transf_satur,dim[0],dim[1],argc,argv);
    }
    else if(argc == 4 && strcmp(argv[1],"egal")==0){

        FILE *fichier = NULL;
        fichier = fopen(argv[2],"r");
        int **image = NULL;
        image = creation_image(fichier);

        //Dimension de l'image
        fichier = fopen(argv[2],"r");
        int *dim = NULL;
        dim = get_dim(fichier);

        //Egalisation de l'image
        int **egalisehist=NULL;
        egalisehist=hist_egalis(dim,image);
        build_file(egalisehist,dim[0],dim[1],argc,argv);
    }
    else if (argc == 4 && strcmp(argv[1], "invers")==0){

        FILE *fichier = NULL;
        fichier = fopen(argv[2],"r");
        int **image = NULL;
        image = creation_image(fichier);

        //Dimension de l'image
        fichier = fopen(argv[2],"r");
        int *dim = NULL;
        dim = get_dim(fichier);

        //Inverse de l'image
        int **matrice_inverse=NULL;
        matrice_inverse=inverse_image(dim,image);
        build_file(matrice_inverse,dim[0],dim[1],argc,argv);

    }
    else if(argc == 5 && strcmp(argv[1],"add")==0){

        FILE *fichier = NULL;
        fichier = fopen(argv[2],"r");
        int **image = NULL;
        image = creation_image(fichier);

        //Dimension de l'image
        fichier = fopen(argv[2],"r");
        int *dim = NULL;
        dim = get_dim(fichier);

        FILE *fichier2 = NULL;
        fichier2 = fopen(argv[3],"r");
        int **image2 = NULL;
        image2 = creation_image(fichier2);

        //Dimension de l'image
        fichier2 = fopen(argv[3],"r");
        int *dim2 = NULL;
        dim2 = get_dim(fichier2);

        //addition
         int **addimg = NULL;
        addimg = add_image(dim,dim2,image,image2);
        build_file2(addimg,dim,dim2,argc,argv);

    }
    else if(argc == 5 && strcmp(argv[1],"soust")==0){

        FILE *fichier = NULL;
        fichier = fopen(argv[2],"r");
        int **image = NULL;
        image = creation_image(fichier);

        //Dimension de l'image
        fichier = fopen(argv[2],"r");
        int *dim = NULL;
        dim = get_dim(fichier);
        FILE *fichier2 = NULL;
        fichier2 = fopen(argv[3],"r");
        int **image2 = NULL;
        image2 = creation_image(fichier2);

        //Dimension de l'image
        fichier2 = fopen(argv[3],"r");
        int *dim2 = NULL;
        dim2 = get_dim(fichier2);

        //Soustraction
        int **sousimg=NULL;
        sousimg=soustract_image(dim,dim2,image,image2);
        build_file2(sousimg,dim,dim2,argc,argv);
    }
    else if(argc == 4 && strcmp(argv[1],"mult")==0){

        FILE *fichier = NULL;
        fichier = fopen(argv[2],"r");
        int **image = NULL;
        image = creation_image(fichier);

        //Dimension de l'image
        fichier = fopen(argv[2],"r");
        int *dim = NULL;
        dim = get_dim(fichier);

        //Multiplication
        int **multimg = NULL;
        multimg=multi_image(dim,image);
        build_file(multimg,dim[0],dim[1],argc,argv);

    }
    else if(argc == 5 && strcmp(argv[1],"ou") == 0){
		
        FILE *fichier = NULL;
        fichier = fopen(argv[2],"r");
        int **image = NULL;
        image = creation_image(fichier);

        fichier = fopen(argv[2],"r");
        int *dim = NULL;
        dim = get_dim(fichier);
	
	//Dimensions de l'image binaire
        FILE *fichierb = NULL;
        fichierb = fopen(argv[3],"r");
        int **image_bins = NULL;
        image_bins = creation_image_bin(fichierb);

        //Dimensions de l'image binaire
        fichierb = fopen(argv[3],"r");
        int *dimb = NULL;
        dimb = get_dim(fichierb);

        //Operation OU
        int **image_OU = NULL;
        image_OU = ou_operator(dim,dimb,image,image_bins);
        build_file2(image_OU,dim,dimb,argc,argv); 

    }
    else if(argc == 5 && strcmp(argv[1],"et")==0){
        FILE *fichier = NULL;
        fichier = fopen(argv[2],"r");
        int **image = NULL;
        image = creation_image(fichier);

        fichier = fopen(argv[2],"r");
        int *dim = NULL;
        dim = get_dim(fichier);

	//Dimensions de l'image binaire
        FILE *fichierb = NULL;
        fichierb = fopen(argv[3],"r");
        int **image_bins = NULL;
        image_bins = creation_image_bin(fichierb);

        //Dimensions de l'image binaire
        fichierb = fopen(argv[3],"r");
        int *dimb = NULL;
        dimb = get_dim(fichierb);

        //Operation ET
        int **image_AND = NULL;
        image_AND=et_operator(dim,dimb,image,image_bins);
        build_file2(image_AND,dim,dimb,argc,argv); 
    }
    else if(argc == 4 && strcmp(argv[1],"interp")==0){

        FILE *fichier = NULL;
        fichier = fopen(argv[2],"r");
        int **image = NULL;
        image = creation_image(fichier);

        //Dimension de l'image
        fichier = fopen(argv[2],"r");
        int *dim = NULL;
        dim = get_dim(fichier);

        //Interpolation
        int **interpol = NULL;
        int zoom =0;
        printf("Entrez le niveau de zoom :\n");
        scanf("%d",&zoom);
        interpol= interp_vois(dim,image,zoom);
        build_file(interpol,(dim[0]*zoom),(dim[1]*zoom),argc,argv); 
    }
    else if(argc == 4 && strcmp(argv[1],"convo")==0){

        FILE *fichier = NULL;
        fichier = fopen(argv[2],"r");
        int **image = NULL;
        image = creation_image(fichier);

        //Dimension de l'image
        fichier = fopen(argv[2],"r");
        int *dim = NULL;
        dim = get_dim(fichier);
        printf("******************* Options ****************");
	    printf("\n1.Filtre Moyenneur\n");
        printf("2.Filtre Gaussien\n");
        printf("3.Construire votre filtre\n");
        printf("Entrer le numero qui vous convient: ");
        int num = 0;
        scanf("%d",&num);
        int *dims = NULL;
        dims = malloc(2*sizeof(int));
        int **filtre  = NULL;

	    if(num == 1){
		    printf("\n********** CREATION DU FILTRE MOYENNEUR ***********\n");
        	dims[0] = 0;
        	dims[1] = 0;
        	printf("Entrez le nombre de lignes :");
        	scanf("%d",&dims[0]);
        	printf("Entrez le nombre de colonnes :");
        	scanf("%d",&dims[1]);
		    filtre = construire_filtre(dims,num);

	    }else if(num == 2){
		    dims[0] = 5;
        	dims[1] = 5;
		    filtre = construire_filtre(dims,num);

	    }else if(num == 3) {
		    printf("\n************** CREATION DU FILTRE ***********\n");
        	//int *dims = malloc(2*sizeof(int));
        	dims[0] = 0;
        	dims[1] = 0;
        	printf("Entrez le nombre de lignes :");
        	scanf("%d",&dims[0]);
        	printf("Entrez le nombre de colonnes :");
        	scanf("%d",&dims[1]);
            printf("nblig : %d",dims[0]);
            printf("nbcol : %d",dims[1]);
		    if(dims[0]%2==0 || dims[1]%2==0){
                printf("Entrez les dimensions impaires\n ");
            }
            else{
                filtre = malloc(dims[0] *sizeof(int*));
                for(int i=0;i<dims[0];i++){
                    filtre[i] = malloc(dims[1] *sizeof(int));
                    for(int j=0;j<dims[1];j++){
                        filtre[i][j] = 0;
                    }
                }

                printf("Entrez les valeurs du filtre (%d X %d) :\n",dims[0],dims[1]);
                for(int i=0;i<dims[0];i++){
                    for(int j=0;j<dims[1];j++){
                        printf("Entrez la valeur :");
                        scanf("%d",&filtre[i][j]);
                    }
                }
	        }
        }
        else{
		    filtre = construire_filtre(dims,num);
	    }
	
        //Convolution proprement dite
        int **img_convolue = NULL;
        img_convolue = convolution(image,dim,filtre,dims);
        build_file(img_convolue,dim[0],dim[1],argc,argv);
        free(filtre);
    }
    else if(argc == 4 && strcmp(argv[1],"median")==0){

        FILE *fichier = NULL;
        fichier = fopen(argv[2],"r");
        int **image = NULL;
        image = creation_image(fichier);

        //Dimension de l'image
        fichier = fopen(argv[2],"r");
        int *dim = NULL;
        dim = get_dim(fichier);
        int **img_median = NULL;
        int t = 0;
        printf("Entrer la taille du filtre median :");
        scanf("%d",&t);

        //Filtre Median
        img_median = median(image,dim,t);
        build_file(img_median,dim[0],dim[1],argc,argv);
    }
    else if(argc == 4 && strcmp(argv[1],"sobel")==0){

        FILE *fichier = NULL;
        fichier = fopen(argv[2],"r");
        int **image = NULL;
        image = creation_image(fichier);

        //Dimension de l'image
        fichier = fopen(argv[2],"r");
        int *dim = NULL;
        dim = get_dim(fichier);

        //Filtre Sobel
        int **img_sobel = NULL;
        img_sobel = contour_sobel(image,dim);
        build_file(img_sobel,dim[0],dim[1],argc,argv);

    }
    else if(argc == 4 && strcmp(argv[1], "prewit")==0){

        FILE *fichier = NULL;
        fichier = fopen(argv[2],"r");
        int **image = NULL;
        image = creation_image(fichier);

        //Dimension de l'image
        fichier = fopen(argv[2],"r");
        int *dim = NULL;
        dim = get_dim(fichier);

        //Filtre prewitt
        int **img_prewitt = NULL;
        img_prewitt = contour_prewitt(image,dim);
        build_file(img_prewitt,dim[0],dim[1],argc,argv);

    }
    else if(argc == 4 && strcmp(argv[1],"laplace") ==0){

        FILE *fichier = NULL;
        fichier = fopen(argv[2],"r");
        int **image = NULL;
        image = creation_image(fichier);

        //Dimension de l'image
        fichier = fopen(argv[2],"r");
        int *dim = NULL;
        dim = get_dim(fichier);

        //Filtre Laplacien
        int **img_Laplacien = NULL;
        img_Laplacien = Laplacien(image,dim);
        build_file(img_Laplacien,dim[0],dim[1],argc,argv); 
    }
    else if(argc == 4 && strcmp(argv[1],"robert")==0){

        FILE *fichier = NULL;
        fichier = fopen(argv[2],"r");
        int **image = NULL;
        image = creation_image(fichier);

        //Dimension de l'image
        fichier = fopen(argv[2],"r");
        int *dim = NULL;
        dim = get_dim(fichier);

        //Filtre Roberts
        int **img_roberts = NULL;
        img_roberts = contour_roberts(image,dim);
        build_file(img_roberts,dim[0],dim[1],argc,argv); 
    }
    else if(argc == 3 && strcmp(argv[1],"otsu")==0){

        FILE *fichier = NULL;
        fichier = fopen(argv[2],"r");
        int **image = NULL;
        image = creation_image(fichier);

        //Dimension de l'image
        fichier = fopen(argv[2],"r");
        int *dim = NULL;
        dim = get_dim(fichier);

        //Otsu
        int seuil = ostu(image,dim);
        printf("\nLe bon seuil pour cette image est : %d \n",seuil);
    }
    else if(argc == 4 && strcmp(argv[1],"seuil")==0){

        FILE *fichier = NULL;
        fichier = fopen(argv[2],"r");
        int **image = NULL;
        image = creation_image(fichier);

        //Dimension de l'image
        fichier = fopen(argv[2],"r");
        int *dim = NULL;
        dim = get_dim(fichier);

        //Seuillage
        int **img_app = NULL;
        img_app = seuillage(image,dim);
        build_file(img_app,dim[0],dim[1],argc,argv);

    }
    else if(argc==2 && strcmp(argv[1],"info")==0){
        entree();
    }
    else if(argc==4 && strcmp(argv[1],"hough")==0){

        FILE *fichier = NULL;
        fichier = fopen(argv[2],"r");
        int **image = NULL;
        image = creation_image(fichier);

        //Dimension de l'image
        fichier = fopen(argv[2],"r");
        int *dim = NULL;
        dim = get_dim(fichier);

        int **votes = NULL;
        int **gradients = Laplacien(image,dim);
        votes = votematrix(gradients,dim,image);
        //int **s = NULL;
        //int o = ostu(votes,dim); // 53
        //printf("Seuil = %d \n",o);
        //s = seuillage(votes,dim);
        //int rho = sqrt((dim[0]*dim[0]) + (dim[1]*dim[1]));
        build_file(votes,dim[0],dim[1],argc,argv);
    }
    else if(argc==4 && strcmp(argv[1],"rot")==0){
        FILE *fichier = NULL;
        fichier = fopen(argv[2],"r");
        int **image = NULL;
        image = creation_image(fichier);

        //Dimension de l'image
        fichier = fopen(argv[2],"r");
        int *dim = NULL;
        dim = get_dim(fichier);

        int **rotation = rotate(image,dim);
        build_file(rotation,dim[0],dim[1],argc,argv);
    }
    else{
        printf("\nMauvaise entrees - Verification des entrees\n");
    }







    /* FILE *fichier = NULL;
    fichier = fopen("empreinte.txt","r");
    int **image = NULL;
    image = creation_image(fichier); */

    //Ouvrir le fichier de l'image 2
/*     FILE *fichier2 = NULL;
    fichier2 = fopen("cameraman.txt","r");
    int **image2 = NULL;
    image2 = creation_image(fichier2);

    //Dimension de l'image
    fichier2 = fopen("cameraman.txt","r");
    int *dim2 = NULL;
    dim2 = get_dim(fichier2); */

    //Creation de l'image binaire
/*     FILE *fichierb = NULL;
    fichierb = fopen("carreNoir.txt","r");
    int **image_bins = NULL;
    image_bins = creation_image_bin(fichierb);
    printf("%d\n",image_bins[0][1]);
    
    //Dimensions de l'image binaire
    fichierb = fopen("carreNoir.txt","r");
    int *dimb = NULL;
    dimb = get_dim(fichierb);
    printf("les dimensions image bin :%d  %d\n ",dimb[0],dimb[1]); */

    //L'operation ET 
/*     int **image_AND = NULL;
    image_AND=et_operator(dim,dimb,image,image_bins);
    build_file2(image_AND,dim,dimb); 
 */
    //L'operation OU
/*     int **image_OU=NULL;
    image_OU = ou_operator(dim,dimb,image,image_bins);
    build_file2(image_OU,dim,dimb);   
     */

    //Creation de l'histogramme d'une image
    /*int* histogramme=NULL;
    histogramme=get_hist(dim,image);
    */

    //Luminance d'une image
/*  int **matrix_brillance=NULL;
    matrix_brillance=brillance(dim,image);
    build_file(matrix_brillance,dim[0],dim[1]);  */


    // Amelioration du constraste par transformation lineaire
/*  int **matrice_transf_lin=NULL;
    matrice_transf_lin= lin_transf(dim,image);
    build_file(matrice_transf_lin,dim[0],dim[1]); */


    //Ameliration du constraste par transformation par saturation
/*  int **matrice_transf_satur=NULL;
    matrice_transf_satur=satur_transf(dim,image,10,30);
    build_file(matrice_transf_satur,dim[0],dim[1]);
 */

    //L'inverse d'une image
/*  int **matrice_inverse=NULL;
    matrice_inverse=inverse_image(dim,image);
    build_file(matrice_inverse,dim[0],dim[1]);  */


    //L'egalisation de l'histogramme
/*  int **egalisehist=NULL;
    egalisehist=hist_egalis(dim,image);
    printf("\n%d\n",egalisehist[56][67]);
    build_file(egalisehist,dim[0],dim[1]);  */


    //Addition de deux images
/*     int **addimg = NULL;
    addimg = add_image(dim,dim2,image,image2);
    build_file2(addimg,dim,dim2);
 */

    //Soustraction de deux images
/*      int **sousimg=NULL;
    sousimg=soustract_image(dim,dim2,image,image2);
    build_file2(sousimg,dim,dim2);  */


    //Multiplication de deux images
/*  int **multimg=NULL;
    int k = 3.5
    multimg=multi_image(dim,image,k);
    build_file(multimg,dim[0],dim[1]); */


    //Interpolation lineaire
/*    int **interpol = NULL;
   int zoom = 2;
    interpol= interp_vois(dim,image,zoom);
    build_file(interpol,(dim[0]*zoom),(dim[1]*zoom));  */ 

    //Convolution - Application du filtre
    //creation du filtre
/*     int *dimf = malloc(2*sizeof(int));
    dimf[0] = 0;
    dimf[1] = 1;
    printf("Entrez le nombre de lignes :");
    scanf("%d",&dimf[0]);
    printf("Entrez le nombre de colonnes :");
    scanf("%d",&dimf[1]);
    int **filtre = construire_filtre(dimf,2);
    for(int i=0;i<dimf[0];i++){
        for(int j=0;j<dimf[1];j++){
            printf("%d ",filtre[i][j]);
        }
        printf("\n");
    }
    //Convolution proprement dite
    int **img_convolue = NULL;
    img_convolue = convolution(image,dim,filtre,dimf);
    build_file(img_convolue,dim[0],dim[1]);
 */


    //Filtre Median
/*     int **img_median = NULL;
    img_median = median(image,dim,5);
    build_file(img_median,dim[0],dim[1]);  */


    //Filtre de prewitt
/*       int **img_prewitt = NULL;
    img_prewitt = contour_prewitt(image,dim);
    build_file(img_prewitt,dim[0],dim[1]);  */


    //Filtre Sobel
/*     int **img_sobel = NULL;
    img_sobel = contour_sobel(image,dim);
    //build_file(img_sobel,dim[0],dim[1]);  */

    //Seuillage 
/*     int **img_seuil = NULL;
    img_seuil = seuillage(img_sobel,dim,220);
    build_file(img_seuil,dim[0],dim[1]);   */


    //Filtre Laplacien
/*     int **img_Laplacien = NULL;
    img_Laplacien = Laplacien(image,dim);
    build_file(img_Laplacien,dim[0],dim[1]);   */

    //Filtre Roberts
/*     int **img_roberts = NULL;
    img_roberts = contour_roberts(image,dim);
    build_file(img_roberts,dim[0],dim[1]);  */

     /* int seuil = ostu(image,dim);
    printf("le bon seuil pour cette image est : %d \n",seuil);  */


/*     int **img_app = NULL;
    img_app = seuillage(image,dim);
    build_file(img_app,dim[0],dim[1]);  */

    return 0;
}





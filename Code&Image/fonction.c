#include <stdio.h>
#include <stdlib.h>
#include "fonction.h"
#define TAILLE 120                                                                    
#include <string.h>
#include <math.h>

// DEFINITIONS DES DIFFERENTES FONCTIONS

int  **creation_image(FILE *monfichier){
    
    int **img=NULL;
    if(monfichier != NULL){
        char chaine[TAILLE]="";
        fgets(chaine,TAILLE,monfichier);
        fgets(chaine,TAILLE,monfichier);

        int nbcol=0;
        int nblig=0;
        int val=0;

        fscanf(monfichier,"%d",&nbcol);
        fscanf(monfichier,"%d",&nblig);
        fscanf(monfichier,"%d",&val);
        val = 0;
        //Creation de ma matice qui stoke mon image
        img = malloc(nblig * sizeof(int*));
        
        for(int i=0; i<nblig; i++){
            img[i] = malloc(nbcol * sizeof(int));
            for(int j=0;j<nbcol;j++){
                fscanf(monfichier,"%d",&val);
                img[i][j] = val;
            }
        }
        fclose(monfichier);   
    }
    else{
        printf("Erreur d'ouverture du fichier\n");
    }
    return img;

}

// Creation de l'image Binaire
int  **creation_image_bin(FILE *fichir){
    
    //Ouverture d'un fichier
    char caract = ' ';
    int nblig = 0;
    int nbcol = 0;
    char chain[TAILLE] = " ";
    int **img_bin = NULL;
    if (fichir != NULL){
        // Boucle de lecture des caractères un à un
        fgets(chain,TAILLE,fichir);
        fgets(chain,TAILLE,fichir);
        fscanf(fichir, "%d %d",&nbcol,&nblig);
        
        // creation de la matrice d'image binaire
        
        img_bin = malloc(nblig * sizeof(int*));
        for(int i=0; i<nblig; i++){
            img_bin[i] = malloc(nbcol * sizeof(int));
        }

        //Remplissage de la matrice   
        int i = 0;
        int j = 0;
        while(i<nblig){
            while(j<nbcol){
                fscanf(fichir,"%c",&caract);
                if(caract != '\n'){
                    if(caract == '1'){
                        img_bin[i][j] = 1;
                    }
                    else if(caract =='0'){
                        img_bin[i][j] = 0;
                    }
                    j = j+1;
                }    
            }
            i++;
            j=0;
        }
        fclose(fichir);
    } 
    else{
        printf("Erreur d'ouverture du fichier");
    } 
    return img_bin;
}

//Fonction qui retourne les dimensions de mon image
int *get_dim(FILE *monfichier){
    int *dim = NULL;
    dim = malloc(2*sizeof(int));
    char chaine[TAILLE]="";
    int nbcol,nblig;
    fgets(chaine,TAILLE,monfichier);
    fgets(chaine,TAILLE,monfichier);
    fscanf(monfichier,"%d",&nbcol);
    fscanf(monfichier,"%d",&nblig);
    dim[0] = nblig;
    dim[1] = nbcol;
    return dim;

}

//Construction des fichiers images
void build_file(int **matrix, int nblig,int nbcol,int argc,char **argv){
        FILE* fich = NULL;
        fich = fopen(argv[argc-1],"w");
        if (fich!=NULL){
            fputs("P2\n", fich);
            fputs("#Created By Marivone Kebou alias KKM\n",fich);
            fprintf(fich,"%d %d\n",nbcol,nblig);
            int t = 255;
            fprintf(fich,"%d\n",t);
            for(int i=0;i<nblig;i++){
                for(int j=0;j<nbcol;j++){
                    fprintf(fich,"%d\n",matrix[i][j]);
                }
            }
        }
        else{
            printf("Erreur d'ouverture du fichier");
        }
    }

//Construction des fichiers images
void build_file2(int **matrix, int* dim,int* dimb,int argc,char **argv){
        FILE* fich = NULL;
        fich=fopen(argv[argc-1],"w");
        if (fich!=NULL){
            fputs("P2\n", fich);
            fputs("#Created By Marivone Kebou alias KKM\n",fich);
            int nbcol = min(dim[1],dimb[1]);
            int nblig = min(dim[0],dimb[0]);
            fprintf(fich,"%d %d\n",nbcol,nblig);
            
            int t=255;
            fprintf(fich,"%d\n",t);
            for(int i=0;i<nblig;i++){
                for(int j=0;j<nbcol;j++){
                    fprintf(fich,"%d\n",matrix[i][j]);
                }
            }
        }
        else{
            printf("Erreur d'ouverture du fichier");
        }
    }


//Fonction qui retourne l'histogramme de mon image
int* get_hist(int *dim, int **matrix){

    int *hist=NULL;
    hist=malloc(256*sizeof(int));
    memset(hist, 0, sizeof(int) *256);
    for(int i=0;i<*dim;i++){
        for(int j=0;j<*(dim+1);j++){
            hist[matrix[i][j]]++;
        }
    }

    return hist;
} 


// Recuperer la moyenne de la matrice pour calculer la brillance d'une image
int get_mean(int *dim,int **matrix){
    int val=0; int mean=0;
    for (int i=0;i<*dim;i++){
        for(int j=0;j<*(dim+1);j++){
            val+=matrix[i][j];
        }
    }
    int taille=(*dim) * (*(dim+1)); 
    mean=val/taille;
    return mean;

}

// Minimum entre deux variables
int min(int a,int b){
    if(a>b){
        return b;
    }
    else{
        return a;
    }
}

//Maximum entre deux variables
int max(int a,int b){
    if(a<b){
        return b;
    }
    else{
        return a;
    }
}


//La luminance d'une image
int **brillance(int *dim,int **matrix){
    int moy=get_mean(dim,matrix);
    int **matrixlum=NULL;
    matrixlum=malloc((*dim) * sizeof(int*));
        for(int i=0; i<*dim; i++){
            matrixlum[i] =malloc((*(dim+1)) * sizeof(int));
            for(int j=0;j<*(dim+1);j++){
                matrixlum[i][j]=min((matrix[i][j]+moy),255);
        }
    }
    return matrixlum;
}


//Minimum de toute l'image
int minMatrix(int *dim, int **matrix){
    int min=matrix[0][0];
    for(int i=0;i<*dim;i++){
        for(int j=0;j<*(dim+1);j++){
            if(min<matrix[i][j]){
                min=min;
            }
            else{
                min = matrix[i][j];
            }
        }
    }
    return min;
}


//Maximum de toute l'image
int maxMatrix(int *dim, int **matrix){
    int max=matrix[0][0];
    for(int i=0;i<*dim;i++){
        for(int j=0;j<*(dim+1);j++){
            if(max>matrix[i][j]){
                max=max;
            }
            else{
                max= matrix[i][j];
            }
        }
    }
    return max;
}


// Transformation lineaire
int **lin_transf(int *dim,int **matrix){
    int LUT[256]={0};
    for(int i=0;i<256;i++){
        LUT[i]=(255*(i-minMatrix(dim,matrix)))/(maxMatrix(dim,matrix)-minMatrix(dim,matrix));
    }

    int **matrixlin=NULL;
    matrixlin= malloc((*dim) * sizeof(int*));
    for(int i=0; i<*dim; i++){
        matrixlin[i]= malloc((*(dim+1)) * sizeof(int));
    }    

    for(int i=0;i<*dim;i++){
        for(int j=0;j<*(dim+1);j++){
            matrixlin[i][j]= LUT[matrix[i][j]];
        }

    }
    return matrixlin;
    }
    

//Transformation par saturation
int **satur_transf(int *dim,int **matrix,int smin,int smax){

    int **matrixsatur=NULL;
    matrixsatur= malloc((dim[0]) * sizeof(int*));
    for(int i=0; i<dim[0]; i++){
        matrixsatur[i]= malloc(dim[1] * sizeof(int));
    }    

    for(int i=0;i<dim[0];i++){
        for(int j=0;j<dim[1];j++){
            matrixsatur[i][j] = floor((255*(matrix[i][j]-smin))/(smax-smin));
        }
    }
    return matrixsatur;
}


//Inverse d'une image
int **inverse_image(int *dim,int **matrix){
    int **matrixinvers=NULL;
    matrixinvers= malloc((*dim) * sizeof(int*));
    for(int i=0; i<*dim; i++){
        matrixinvers[i]= malloc((*(dim+1)) * sizeof(int));
    }  
        for(int i=0;i<*dim;i++){
            for(int j=0;j<*(dim+1);j++){
                matrixinvers[i][j]=255-matrix[i][j];
            }
        }
    return matrixinvers;
}


//Egalisation de l'histogrammme
int **hist_egalis(int *dim,int **matrix){
    int *histo=NULL;
    histo=get_hist(dim,matrix);

    float *histocopie=NULL;
    histocopie=malloc(256*sizeof(float));
    for(int i=0;i<256;i++){
        histocopie[i]=(float)histo[i];

    }

//Histogramme normalisée
    float taille=( (*dim) * (*(dim+1)) );
    for(int i=0;i<256;i++){
        histocopie[i]=histocopie[i]/taille;
    }

//Densite de probabilité
    float C[256]={0};
    for (int i=0;i<256;i++){
        float a=0.0f;
        for(int j=0;j<=i;j++){
            a=a+histocopie[j];
        }
        C[i]=a;
    }

//Transformation de niveaux de gris
    int **egal = malloc((*dim) * sizeof(int*));
    for(int i=0;i<*dim;i++){
        egal[i]= malloc(*(dim+1) * sizeof(int));
    }

    for(int i=0;i<*dim;i++){
        for(int j=0;j<*(dim+1);j++){
            egal[i][j]=C[matrix[i][j]] * 255;
        }
    }
return egal;

}

//Addition de deux images
int **add_image(int *dims,int *dims2,int **matrix,int **matrixe){
    int nblig = min(dims[0],dims2[0]);
    int nbcol = min(dims[1],dims2[1]);
    int **tabadd=malloc(nblig * sizeof(int*));
    for(int i=0;i<nblig;i++){
        tabadd[i]=malloc(nbcol * sizeof(int));
    }

    for(int i=0;i<nblig;i++){
        for(int j=0;j<nbcol;j++){
            tabadd[i][j]=min(matrix[i][j]+matrixe[i][j],255);
        }
    }
    return tabadd;
}


//Soustraction de deux images
int **soustract_image(int *dims,int *dims2,int **matrix,int **matrixe){
    int nblig = min(dims[0],dims2[0]);
    int nbcol = min(dims[1],dims2[1]);
    int **tabsous=malloc(nblig * sizeof(int*));
    for(int i=0;i<nblig;i++){
        tabsous[i]=malloc(nbcol * sizeof(int));
    }

    for(int i=0;i<nblig;i++){
        for(int j=0;j<nbcol;j++){
            tabsous[i][j]=max(matrix[i][j]-matrixe[i][j],0);
        }
    }
    return tabsous;
}

//Multiplication de deux images
int **multi_image(int *dim,int **matrix){
    float ratio =0.0;
    int **tabmul=malloc((*dim) * sizeof(int*));
    for(int i=0;i<*dim;i++){
        tabmul[i]=malloc(*(dim+1) * sizeof(int));
    }
    printf("\nEntrer un ratio : ");
    scanf("%f",&ratio);

    for(int i=0;i<*dim;i++){
        for(int j=0;j<*(dim+1);j++){
            int a= (int) ratio*matrix[i][j];
            tabmul[i][j]=min(a,255);
        }
    }

    return tabmul;
}


    
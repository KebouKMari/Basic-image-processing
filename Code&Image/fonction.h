#ifndef FONCTION_H
#define FONCTION_H

// Ici on mettra les prototypes de nos fonctions

void entree();
int  **creation_image(FILE *monfichier);
int  **creation_image_bin(FILE *monfichier);
int *get_dim(FILE *monfichier);
int* get_hist(int *dim, int **matrix);
int get_mean(int *dim,int **matrix);
int **brillance(int *dim,int **matrix);
int min(int a,int b);
int max(int a,int b);
void build_file(int **matrix, int nblig,int nbcol,int argc,char **argv);
void build_file2(int **matrix, int *dim,int* dimb,int argc,char **argv);
int minMatrix(int *dim, int **matrix);
int maxMatrix(int *dim, int **matrix);
int **lin_transf(int *dim, int **matrix);
int **satur_transf(int *dim,int **matrix,int smin, int smax);
void bar_construct(int a);
int **inverse_image(int *dim,int **matrix);
int **hist_egalis(int *dim,int **matrix);
int **add_image(int *dim,int *dim2,int **matrix,int **matrixe);
int **soustract_image(int *dim,int *dim2,int **matrix,int **matrixe);
int **multi_image(int *dim,int **matrix);
int **interp_vois(int *dim,int **matrix,int zoom);
int **et_operator(int *dim,int *dimb,int **matrix,int **matrixe);
int **ou_operator(int *dim,int *dimb,int **matrix,int **matrixe);
int sums(int **matrix,int *dims);
int **creation_filtre(int *dimf);
int **construire_filtre(int *dimf,int num);
int **convolution(int **matrix,int *dim,int **filtre,int *dimf);
int *trier(int *tab,int dim);
int **median(int **matrix,int *dim,int dimf);
void affichage(int **matrix,int *dim);
int **rotate(int **p,int *dim);
int **contour_prewitt(int **matrix,int *dim);
int **contour_sobel(int **matrix,int *dim);
int **Laplacien(int **matrix,int *dim);
int **contour_roberts(int **matrix,int *dim);
int **seuillage(int **matrix,int *dim);
int ostu(int **matrix,int *dim);
int **votematrix(int **matrix,int *dim,int **p);

#endif
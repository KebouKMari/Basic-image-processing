#include <stdio.h>
#include <stdlib.h>
#include "fonction.h"
#define TAILLE 120                                                                    
#include <string.h>
#include <math.h>

//Operation ET LOGIQUE
int **et_operator(int *dim,int *dimb,int **matrix,int **matrixe){
    int nblig = min(dim[0],dimb[0]);
    int nbcol = min(dim[1],dimb[1]);
    int **tabEt = NULL;
    tabEt = malloc(nblig * sizeof(int*));
    for(int i = 0;i<nblig; i++){
        tabEt[i] = malloc(nbcol * sizeof(int));
    }

    for(int i = 0;i<nblig;i++){
        for(int j = 0;j<nbcol;j++){
            if(matrixe[i][j] == 1){
                tabEt[i][j] = 0;
            }
            else if (matrixe[i][j] == 0){
                tabEt[i][j] = matrix[i][j];
            }
        }
    }
    return tabEt;
}

//Operation OU LOGIQUE

int **ou_operator(int *dim,int *dimb,int **matrix,int **matrixe){
    //Creation de la matrice
    int **tabOU = NULL;
    int nblig = min(dim[0],dimb[0]);
    int nbcol = min(dim[1],dimb[1]);
    tabOU = malloc(nblig * sizeof(int*));
    for(int i=0;i<nblig;i++){
        tabOU[i]=malloc(nbcol * sizeof(int));
    }
    //Remplissage de la matrice
    for(int i=0;i<nblig;i++){
        for(int j=0;j<nbcol;j++){
            if(matrixe[i][j] == 1){
                tabOU[i][j] = matrix[i][j];
            }
            else if (matrixe[i][j] == 0){
                tabOU[i][j] = 255;
            }
        }
    }
    return tabOU;

} 

int **interp_vois(int *dim,int **matrix,int zoom){
    int n = 0;
    int c = 0;
    //Construction de la matrice
    int **M = malloc((zoom*dim[0])*sizeof(int*));
    for(int i =0; i<(zoom*dim[0]);i++){
        M[i] = malloc((dim[1]*zoom)*sizeof(int));
         for(int j = 0; j<(dim[1]*zoom);j++){
            M[i][j] = -1;

        }
    } 
  
    //Interpolation proprement dite
    for (int i=0;i<dim[0];i++){
        n = n + zoom;
        for(int j=0;j<dim[1];j++){
            c = c + zoom;
            for(int k=0;k<n;k++){
                for(int l=0;l<c;l++){
                    if(M[k][l] == -1){
                        M[k][l] = matrix[i][j];
                    }
                }
            }
        }
        c = 0;
    }
    return M;
}

//Creation du filtre
int **creation_filtre(int *dimf){

    if(dimf[0]%2==0 || dimf[1]%2==0){
        printf("Entrez les dimensions impaires\n ");
    }
    else{
        int **matrix = NULL;
        matrix = malloc(dimf[0] *sizeof(int*));
        for(int i=0;i<dimf[0];i++){
            matrix[i] = malloc(dimf[1] *sizeof(int));
        }
        printf("Entrez les valeurs du filtre (%d X %d) :\n",dimf[0],dimf[1]);
        for(int i=0;i<dimf[0];i++){
            for(int j=0;j<dimf[1];j++){
                printf("Entrez la valeur :");
                scanf("%d",&matrix[i][j]);
            }
        }
        return matrix;
    }
}


int **construire_filtre(int *dimf,int num){
    int **matrix = NULL; 
    switch (num)
    {
    case 1:
    //Moyenneur
        if(dimf[0]%2==0 || dimf[1]%2==0){
            printf("Les dimensions doivent etre impaires");
            break;
        }
        else{
            matrix = malloc(dimf[0]*sizeof(int*));
            for(int i=0;i<dimf[0];i++){
                matrix[i] = malloc(dimf[1]*sizeof(int));
                for(int j=0;j<dimf[1];j++){
                    matrix[i][j] = 1;
                }
            }
            return matrix;
        }
        break;

    case 2:
        //Gaussien
            matrix = malloc(dimf[0]*sizeof(int*));
                for(int i=0;i<dimf[0];i++){
                    matrix[i] = malloc(dimf[1] *sizeof(int));
                }
            matrix[0][0]=1; matrix[0][1]=2; matrix[0][2]=3; matrix[0][3]=2; matrix[0][4]=1;
            matrix[1][0]=2; matrix[1][1]=6; matrix[1][2]=8; matrix[1][3]=6; matrix[1][4]=2;
            matrix[2][0]=3; matrix[2][1]=8; matrix[2][2]=10; matrix[2][3]=8; matrix[2][4]=3;
            matrix[3][0]=2; matrix[3][1]=6; matrix[3][2]=8; matrix[3][3]=6; matrix[3][4]=2;
            matrix[4][0]=1; matrix[4][1]=2; matrix[4][2]=3; matrix[4][3]=2; matrix[4][4]=1;
        return matrix;
    break;
    default:
        printf("Bad number");
        break;
    }
}

//Somme des elements d'une matrice
int sums (int **matrix,int *dims)
{
    int sum = 0;
    for (int i = 0;i<dims[0];i++){
        for (int j =0; j<dims[1];j++){
            sum =sum + matrix[i][j];
        }
    }
    return sum;
}

//Convolution
int **convolution(int **matrix,int *dim,int **filtre,int *dimf){

    //Creation de la matrice resultante
    int s = 0;
    s = sums(filtre,dimf);
    int **image_filtre = malloc(dim[0]*sizeof(int*));
    for (int i =0; i<dim[0]; i++){
        image_filtre[i] = malloc(dim[1]*sizeof(int));
        for(int j=0;j<dim[1];j++){
            image_filtre[i][j] = 0;
        }
    }

    // Code proprement dit
    int m = dimf[0]/2;
    int ic = 0, jc = 0;
    for (int i = m; i<(dim[0]-m); i++){
       for (int j = m;j<(dim[1]-m); j++){
            ic = i - m;
            jc = j - m;
            for (int k=0; k<dimf[0]; k++){
                for (int h=0; h<dimf[1]; h++){
                    image_filtre[i][j] = image_filtre[i][j] + (matrix[ic][jc]*filtre[k][h]);
                    jc++;
                }    
                ic++;
                jc = j-m;
            }
            if(s>0){
                image_filtre[i][j] = (image_filtre[i][j] / s);
            }
            else{
                image_filtre[i][j] = image_filtre[i][j];
            }
        }
    }
    return image_filtre;
}
  
//Trie par ordre croissant
int *trier(int *tab,int dim){

    int permu = 0;
    for (int i=0;i<dim-1;i++){
        for(int j=i+1;j<dim;j++){
            if(tab[i]>tab[j]){
                permu = tab[j];
                tab[j] = tab[i];
                tab[i]= permu;
            }
        }
    }
    return tab;
}

//Afficche une matrice
void affichage(int **matrix,int *dim){
    for(int i=0;i<dim[0];i++){
        for(int j=0;j<dim[1];j++){
            printf("%d ",matrix[i][j]);
        }
        printf("\n");
    }
}

//Filtre median
int **median(int **matrix,int *dim,int dimf){

    int m=0,ic=0,jc=0,h=0,mid=0;
    m = dimf/2;
    //Creation du tableau t pour le tri
    int *t = malloc((dimf*dimf)*sizeof(int));

    //Creation de la matrice finale
    int **M = malloc(dim[0]*sizeof(int*));
    for(int i=0;i<dim[0];i++){
        M[i] = malloc(dim[1]*sizeof(int));
        for(int j=0;j<dim[1];j++){
            M[i][j] = 0;
        }
    }

    for(int i=m;i<(dim[0]-m);i++){
        for(int j=m;j<(dim[1]-m);j++){
            ic = i - m;
            jc = j - m;
            for(int k=0;k<dimf;k++){
                for(int l=0;l<dimf;l++){
                    t[h] = matrix[ic][jc];
                    h++;
                    jc++;
                }
                ic = ic + 1;
                jc = j - m;
            }

            t = trier(t,dimf*dimf);
            mid = (dimf*dimf)/2;
            if(((dimf*dimf)%2) != 0){
                M[i][j] = t[mid];
            }
            else{
                M[i][j] = (t[mid] + t[mid+1]) /2;
            }
            h = 0;
        }
    }
    return M;
}

//Rotation d'une matrice
int **rotate(int **p,int *dim){
    int **M = malloc(dim[0]*sizeof(int*));
    for(int i=0;i<dim[0];i++){
        M[i] = malloc(dim[1]*sizeof(int));
    }
    
    int k=0,h=0;
    for(int i=0;i<dim[0];i++){
        for(int j=dim[1]-1;j>=0;j--){
            M[k][h] = p[i][j];
            k++;
        }
        h++;
        k=0;
    }
    return M;
}

//Contour avec prewitt
int **contour_sobel(int **matrix,int *dim){

    int **sobelD = malloc(3*sizeof(int*));
    for(int i=0;i<3;i++){
        sobelD[i] = malloc(3*sizeof(int));
    }

    int **sobelG = malloc(3*sizeof(int*));
    for(int i=0;i<3;i++){
        sobelG[i] = malloc(3*sizeof(int));
    }

    int **sobelB = malloc(3*sizeof(int*));
    for(int i=0;i<3;i++){
        sobelB[i] = malloc(3*sizeof(int));
    }

    int **sobelH = malloc(3*sizeof(int*));
    for(int i=0;i<3;i++){
        sobelH[i] = malloc(3*sizeof(int));
    }

    sobelD[0][0] = -1; sobelD[0][1] = 0; sobelD[0][2] = 1;
    sobelD[1][0] = -2; sobelD[1][1] = 0; sobelD[1][2] = 2;
    sobelD[2][0] = -1; sobelD[2][1] = 0; sobelD[2][2] = 1;

    sobelG[0][0] = 1; sobelG[0][1] = 0; sobelG[0][2] = -1;
    sobelG[1][0] = 2; sobelG[1][1] = 0; sobelG[1][2] = -2;
    sobelG[2][0] = 1; sobelG[2][1] = 0; sobelG[2][2] = -1;

    sobelB[0][0] = -1; sobelB[0][1] = -2; sobelB[0][2] = -1;
    sobelB[1][0] = 0; sobelB[1][1] = 0; sobelB[1][2] = 0;
    sobelB[2][0] = 1; sobelB[2][1] = 2; sobelB[2][2] = 1;

    sobelH[0][0] = 1; sobelH[0][1] = 2; sobelH[0][2] = 1;
    sobelH[1][0] = 0; sobelH[1][1] = 0; sobelH[1][2] = 0;
    sobelH[2][0] = -1; sobelH[2][1] = -2; sobelH[2][2] = -1;


    int df[3] = {3,3};

    int **R = malloc(dim[0]*sizeof(int*));
    for(int i=0; i<dim[0];i++){
        R[i] = malloc(dim[1]*sizeof(int));
    } 
    
    int **Gd = NULL;
    int **Gg = NULL;
    int **Gb = NULL;
    int **Gh = NULL;
    Gd = convolution(matrix,dim,sobelD,df); 
    Gg = convolution(matrix,dim,sobelG,df);
    Gb = convolution(matrix,dim,sobelB,df);
    Gh = convolution(matrix,dim,sobelH,df);
    int val1 = 0,val2 =0,val=0;

    for(int i=0;i<dim[0];i++){
        for(int j=0;j<dim[1];j++){
            val1 = max(Gd[i][j],Gg[i][j]);
            val2 = max(Gb[i][j],Gh[i][j]);
            val = max(val1,val2);
            if(val >255){
                val = 255;
            }
            R[i][j] = val;
        }
    }

    return R; 
}

int **contour_prewitt(int **matrix,int *dim){

    int **prewitD = malloc(3*sizeof(int*));
    for(int i=0;i<3;i++){
        prewitD[i] = malloc(3*sizeof(int));
    }

    int **prewitG = malloc(3*sizeof(int*));
    for(int i=0;i<3;i++){
        prewitG[i] = malloc(3*sizeof(int));
    }

    int **prewitB = malloc(3*sizeof(int*));
    for(int i=0;i<3;i++){
        prewitB[i] = malloc(3*sizeof(int));
    }

    int **prewitH = malloc(3*sizeof(int*));
    for(int i=0;i<3;i++){
        prewitH[i] = malloc(3*sizeof(int));
    }

    prewitD[0][0] = -1; prewitD[0][1] = 0; prewitD[0][2] = 1;
    prewitD[1][0] = -1; prewitD[1][1] = 0; prewitD[1][2] = 1;
    prewitD[2][0] = -1; prewitD[2][1] = 0; prewitD[2][2] = 1;

    prewitG[0][0] = 1; prewitG[0][1] = 0; prewitG[0][2] = -1;
    prewitG[1][0] = 1; prewitG[1][1] = 0; prewitG[1][2] = -1;
    prewitG[2][0] = 1; prewitG[2][1] = 0; prewitG[2][2] = -1;

    prewitB[0][0] = -1; prewitB[0][1] = -1; prewitB[0][2] = -1;
    prewitB[1][0] = 0; prewitB[1][1] = 0; prewitB[1][2] = 0;
    prewitB[2][0] = 1; prewitB[2][1] = 1; prewitB[2][2] = 1;

    prewitH[0][0] = 1; prewitH[0][1] = 1; prewitH[0][2] = 1;
    prewitH[1][0] = 0; prewitH[1][1] = 0; prewitH[1][2] = 0;
    prewitH[2][0] = -1; prewitH[2][1] = -1; prewitH[2][2] = -1;


    int df[3] = {3,3};

    int **R = malloc(dim[0]*sizeof(int*));
    for(int i=0; i<dim[0];i++){
        R[i] = malloc(dim[1]*sizeof(int));
    } 
    
    int **Gd = NULL;
    int **Gg = NULL;
    int **Gb = NULL;
    int **Gh = NULL;
    Gd = convolution(matrix,dim,prewitD,df); 
    Gg = convolution(matrix,dim,prewitG,df);
    Gb = convolution(matrix,dim,prewitB,df);
    Gh = convolution(matrix,dim,prewitH,df);
    int val1 =0,val2 =0,val=0;

    for(int i=0;i<dim[0];i++){
        for(int j=0;j<dim[1];j++){
            val1 = max(Gd[i][j],Gg[i][j]);
            val2 = max(Gb[i][j],Gh[i][j]);
            val = max(val1,val2);
            if(val >255){
                val = 255;
            }
            R[i][j] = val;
        }
    }

    return R; 
}

int ** Laplacien(int **matrix,int *dim){
    
    int **laplacien = malloc(3*sizeof(int*));
    for(int i=0;i<3;i++){
        laplacien[i] = malloc(3*sizeof(int));
    }

    laplacien[0][0] = 0; laplacien[0][1] = 1; laplacien[0][2] = 0;
    laplacien[1][0] = 1; laplacien[1][1] = -4; laplacien[1][2] = 1;
    laplacien[2][0] = 0; laplacien[2][1] = 1; laplacien[2][2] = 0;
    int df[3] = {3,3};
    
    int **Gx = NULL;
    Gx = convolution(matrix,dim,laplacien,df); 

    for(int i=0;i<dim[0];i++){
        for(int j=0;j<dim[1];j++){
            if(Gx[i][j]<0){
                Gx[i][j] = 0;
            }
        }
    } 
    
    return Gx; 
}

int **contour_roberts(int **matrix,int *dim){

    int **robertD = malloc(3*sizeof(int*));
    for(int i=0;i<3;i++){
       robertD[i] = malloc(3*sizeof(int));
    }

    int **robertG = malloc(3*sizeof(int*));
    for(int i=0;i<3;i++){
        robertG[i] = malloc(3*sizeof(int));
    }

   
    robertD[0][0] = 0; robertD[0][1] = 0; robertD[0][2] = 1;
    robertD[1][0] = 0; robertD[1][1] = 0; robertD[1][2] = 0;
    robertD[2][0] = -1; robertD[2][1] = 0; robertD[2][2] = 0;

    robertG[0][0] = 1; robertG[0][1] = 0;robertG[0][2] = 0;
    robertG[1][0] = 0; robertG[1][1] = 0; robertG[1][2] = 0;
    robertG[2][0] = 0; robertG[2][1] = 0; robertG[2][2] = -1;

    int df[3] = {3,3};

    int **R = malloc(dim[0]*sizeof(int*));
    for(int i=0; i<dim[0];i++){
        R[i] = malloc(dim[1]*sizeof(int));
    } 
    
    int **Gd = NULL;
    int **Gg = NULL;

    Gd = convolution(matrix,dim,robertD,df); 
    Gg = convolution(matrix,dim,robertG,df);

    int val1 = 0, a =0, b =0;

    for(int i=0;i<dim[0];i++){
        for(int j=0;j<dim[1];j++){
            /* val1 = max(Gd[i][j],Gg[i][j]);
            if(val1 >255){
                val1 = 255;
            }
            R[i][j] = val1; */
            a = Gd[i][j] * Gd[i][j];
            b = Gg[i][j] * Gg[i][j];
            val1 = sqrt(a+b);
            if(val1>255){
                val1 =255;
            }
            R[i][j] = val1;
        }
    }
    return R; 

}

int **seuillage(int **matrix,int *dim){

    int **R = malloc(dim[0]*sizeof(int*));
    for(int i=0; i<dim[0];i++){
        R[i] = malloc(dim[1]*sizeof(int));
    } 


    printf("\nEntrer le seuil : ");
    int seuil = 0;
    scanf("%d",&seuil);
    for(int i=0; i<dim[0]; i++){
        for(int j=0;j<dim[1];j++){
            if(matrix[i][j]<=seuil){
                R[i][j] = 0;
            }
            else{
                R[i][j] = 255;
            }
        }
    }
    return R;
}

int ostu(int **matrix,int *dim){

    float moy1 =0,moy2 =0,var1 =0,var2 =0,Ib=0,Is=0;int s=0; 
    int *hist = NULL;
    hist = get_hist(dim,matrix);

    for(int t=1;t<256;t++){
        //La variance v1
        for(int i=0;i<t;i++){
            var1 = var1 + hist[i];
        }
        var1 = var1 /(dim[0]*dim[1]);
        
        //La variance v2
        for(int i=t;i<256;i++){
            var2 = var2 + hist[i];
        }
        var2 = var2 /(dim[0]*dim[1]);
        
        //Moyenne 1
        for(int k=0;k<t;k++){
            moy1 = moy1 + (k*hist[k]);
        }

        if(var1 == 0 || moy1 ==0){
            moy1 = 0;
        }
        else{
            moy1 = (moy1 / (dim[0]*dim[1]*var1));
        } 

        //Moyenne 2
        for(int k=t;k<256;k++){
            moy2 = moy2 + (k*hist[k]);
        }
        
        if(var2 == 0 || moy2 ==0){
            moy2 = 0;
        }
        else{
            moy2 = moy2 / (dim[0]*dim[1]*var2);
        }

        Ib = var1 * var2 *((moy1 - moy2)*(moy1 - moy2));
        
        if(Ib>Is){
            s = t;
            Is = Ib;
        }
    }

    return s;  
}

void entree(){
    printf(" _______________________________________________________________________________________\n");
    printf("\n                              TP VISION PAR ORDINATEUR              \n");
     printf(" _____________________________________________________________________________________\n");
    printf("                                            created by : | Marivone Kebou Kitio |\n\n\n");
    printf("--------------------- Possibilites --------------------\n\n\n");
    printf("1.L'histogramme d'une image : hist nomfichier fich\n\n");
    printf("2.Ameliorer la luminance d'une image : lumin nomfichier fich\n\n");
    printf("3.Contraste par transformation lineaire d'une image : translin nomfichier fich\n\n");
    printf("4.Contraste par transformation par saturation d'une image : transsat nomfichier fich\n\n");
    printf("5.Contraste par egalisation de l'histogramme: egal nomfichier fich\n\n");
    printf("6.L'inverse d'une image : invers nomfichier fich\n\n");
    printf("7.Addition d'images :add nomfichier1 nomfichier2 fich\n\n");
    printf("8.Soustraction d'image : soust nomfichier1 nomfichier2 fich\n\n");
    printf("9.Multiplication d'image : mult nomfichier fich\n\n");
    printf("10.Operation OU : ou nomfichier1 nomfichier2 fich\n\n");
    printf("11.Operation ET : et nomfichier1 nomfichier2 fich\n\n");
    printf("12.Zoom par interpolation par plus proche voisin : interp nomfichier fich\n\n");
    printf("13.Convolution d'une image : convo nomfichier fich\n\n");
    printf("14.Filtrage median d'une image : median nomfichier fich\n\n");
    printf("15.Contours_Roberts d'une image : robert nomfichier fich\n\n");
    printf("16.Contours_Sobel d'une image : sobel nomfichier fich\n\n");
    printf("17.Contours_Prewitt d'une image : prewit nomfichier fich\n\n");
    printf("18.Contours Laplacien d'une image : laplace nomfichier fich\n\n");
    printf("19.Detection automatique de seuil : otsu nomfichier\n\n");
    printf("20.Seuillage d'une image : seuil nomfichier fich\n\n");
    printf("21.Transformee de hough : hough nomfichier fich\n\n");
    printf("22.Rotation d'une image : rot nomfichier fich\n\n\n");
    printf("Executer  avec : ./execute\n\n");

}

int **votematrix(int **matrix,int *dim,int **p){


    int rho = sqrt((dim[0]*dim[0]) + (dim[1]*dim[1]));
    int theta = 181;

    int **vote = NULL;
    vote = malloc(rho*sizeof(int*));
    for(int i = 0;i<rho;i++){
        vote[i] = malloc(theta*sizeof(int));
        for(int j=0;j<theta;j++){
            vote[i][j] = 0;
        }
    }

    int ro = 0;
    float ks =0.0;
    for(int i=0;i<dim[0];i++){
        for(int j=0;j<dim[1];j++){
            if(matrix[i][j] > 120){
                for(int k=0;k<theta;k++){
                    ks = (k * 3.14) / 180;
                    ro = i*cos(ks) + j*sin(ks);
                    if(ro>=0 && ro<rho){
                        vote[ro][k] = vote[ro][k]+1;
                    }
                }
            }
        }
    }
    //return vote;

    //Creation de la matrice finale
    int **final = malloc(dim[0]*sizeof(int*));
    for(int i=0;i<dim[0];i++){
        final[i] = malloc(dim[1]*sizeof(int));
        for(int j=0;j<dim[1];j++){
            final[i][j] = 0;
        }
    }

    int x = 0; 
    float kj=0.0;
    for (int i=0;i<rho;i++){
        for(int j=0;j<theta;j++){
            if(vote[i][j]>47){
                for(int y=0;y<dim[1];y++){
                    kj = (j * 3.14) / 180;
                    x = ((i/cos(kj)) - (y*tan(kj)));
                    if(x>=0 && x<dim[0]){
                        final[x][y] = 255;
                    }
                }
            } 
        }
    }

    int **res = NULL;
    res = malloc(dim[0]*sizeof(int*));
    for(int i=0;i<dim[0];i++){
        res[i] = malloc(dim[1]*sizeof(int));
        for(int j=0;j<dim[1];j++){
            res[i][j] =0;
        }
    }

    for(int i=0;i<dim[0];i++){
        for(int j=0;j<dim[1];j++){
            res[i][j] = final[i][j] + p[i][j];
            if(res[i][j]>255){
                res[i][j] = 255;
            }
        }
    }
 
    return res;

}
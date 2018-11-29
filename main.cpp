#include <iostream>
#include <math.h>
#include <string.h>

int main() {

    FILE *fptr;
    float popPredator, popPrey, popPreyMax, Y[2][3], h=1, alpha, alphaZero, gama, beta, delta;
    int tempo;

    //Abre o arquivo onde salva a variaçao ne populaçao geral
    fptr = fopen("/home/joaopaulo/CLionProjects/ReiLeao/population.txt", "w");
    if (fptr == NULL) {
        printf("Arquivo nao existe! \n");
        return 0;
    }



    //Inicializaçao RK2
    Y[0][1] = (Y[0][0] + h*(Y[0][0] + (h/2)*((alpha*Y[0][0]) - (beta*Y[0][0]*Y[1][0]))));
    Y[1][1] = (Y[1][0] + h*(Y[1][0] + (h/2)*(((-1)*Y[1][0]) + (delta*Y[0][1]*Y[1][0]))));



    //20 anos -> 240 meses
    for(tempo = 0; tempo <= 240; tempo++){

    // diferentes criterios para definição de alpha
    //alpha = ((1.5+sin(tempo))*alphaZero);
    //alpha = (alpha*(popPreyMax - Y[0][0]));  ???? não seria zero?

    beta = popPrey/alpha;
    gama = popPredator*gama;


    Y[0][2] = Y[0][0] + h*( 3*((alpha*Y[0][1]) - (beta*Y[0][1]*Y[1][1])) - (alpha*Y[0][0]) - (beta*Y[0][0]*Y[1][0])  );
    Y[1][2] = Y[1][0] + h*( 3*((-1)*gama*Y[1][1] + (delta*Y[0][1]*Y[1][1]))   -  ((-1)*gama*Y[1][0] + (delta*Y[0][0]*Y[1][0]))  );

    //imprimindo no arquivo
    fprintf(fptr, "%d;%f;%f\n", tempo,Y[0][0],Y[1][0]);

    //Avançando: k-1 <- k e k <- k+1
    Y[0][0] = Y[0][1];
    Y[1][0] = Y[1][1];
    Y[0][1] = Y[0][2];
    Y[1][2] = Y[1][2];
     }

}
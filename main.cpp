#include <iostream>
#include <math.h>
#include <string.h>
#include <cmath>
#include "AdamsBashford.h"
#include "AdamsBashfordUnlimited.h"
#include "AdamsBashfordSinusoidal.h"

using namespace std;

int main(int argc, char** argv) {


    int type = 9;

    while (type != 0 && type != 1) {
        cout << "Que metodo de ambiente aos herbivoros você deseja utilizar?\n"
         << "Digite 0 para ilimitado\n"
         << "Digite 1 para senoidal\n";
        cin >> type;
    }

    AdamsBashford* adamsBashford;

    if (type == 0) {
        adamsBashford = new AdamsBashfordUnlimited();
    } else {
        adamsBashford = new AdamsBashfordSinusoidal();
    }

    //Forçando a variação de tempo em 1 para os valores não ficarem muito distorcidos
    adamsBashford->timeVariation = 1;


    cout << "Quantos meses devem ser simulados? Ex.: 2400\n";
    cin >> adamsBashford->totalOfMonths;
    cout << "Qual o intervalo entre cada iteração (milissegundos) Ex.: 100\n";
    cin >> adamsBashford->cycleInterval;

    cout << "Qual a população inicial de presas? Ex.: 5000\n";
    cin >> adamsBashford->preyInitialPopulation;
    cout << "Qual a população inicial de predadores? Ex.: 100\n";
    cin >> adamsBashford->predatorInitialPopulation;


    cout << "Qual o quoeficiente de crescimento das presas (α) (Ex.: 0.01)\n";
    cin >> adamsBashford->alpha;
    cout << "Qual o quoeficiente de crescimento dos predadores (∆). (Ex.: 0.00001)\n";
    cin >> adamsBashford->delta;

    adamsBashford->calc();

    cout << "Todos as informações foram plotadas!";

}
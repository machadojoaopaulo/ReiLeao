//
// Created by João Paulo Machado on 2018-11-30.
//
#include <map>
#include <vector>
#include <cmath>
#include <unistd.h>

#include "gnuplot-iostream.h"

#ifndef REILEAO_ADAMSBASHFORD_H
#define REILEAO_ADAMSBASHFORD_H

class AdamsBashford {

private:

    Gnuplot gp;
    std::vector<std::pair<double, double>> chartPoints, chartInitialPoints;

    void setupChart() {
        gp << "set title 'Sistema Presa-Predador'\n"
           << "set grid\n";
    }

    void printChart() {
        gp << "plot" << gp.file1d(this->chartInitialPoints) << " title 'População Inicial' with points lt 1 pt 7 lc rgb 'red',"
           << gp.file1d(this->chartPoints) << "title 'Evolução' with points lt 3 pt 4" << std::endl;
    }

protected:

    double alphaInitial, beta, gama, preyPopulationT1, preyPopulationT2, preyPopulationT3, predatorPopulationT1, predatorPopulationT2, predatorPopulationT3, preyEulerFunction, predatorEulerFunction;

    void beforeCalculation() {
        //Definição de constantes
        this->beta = this->alpha / this->predatorInitialPopulation;
        this->gama = this->delta * this->preyInitialPopulation;
        this->alphaInitial = this->alpha;

        //Pertubação da lineridade populacional
        this->preyPopulationT1 = (this->preyInitialPopulation * 0.96);
        this->predatorPopulationT1 = this->predatorInitialPopulation;


        //Y de euler
        preyEulerFunction = this->preyPopulationT1 + (this->timeVariation) * (
                (this->alpha * this->preyPopulationT1) -
                (this->beta * this->preyPopulationT1 * this->predatorPopulationT1)
        );

        predatorEulerFunction = this->predatorPopulationT1 + (this->timeVariation) * (
                ((-1) * this->gama * this->predatorPopulationT1) +
                (this->delta * this->predatorPopulationT1 * this->preyPopulationT1)
        );

        //Inicializaçao Rouge Koutte 2
        this->preyPopulationT2 = (
                this->preyPopulationT1 + (this->timeVariation / 2) *
                                         (
                                                 this->preyPopulationT1 + (
                                                         (this->timeVariation) *
                                                         (
                                                                 (this->alpha * this->preyEulerFunction) -
                                                                 (this->beta * this->preyEulerFunction *
                                                                  this->predatorEulerFunction)
                                                         )
                                                 )
                                         )
        );

        this->predatorPopulationT2 = (
                this->predatorPopulationT1 + (this->timeVariation / 2) *
                                             (
                                                     this->predatorPopulationT1 + (
                                                             (this->timeVariation) *
                                                             (
                                                                     ((-1) * this->gama * this->predatorEulerFunction) +
                                                                     (this->delta * this->preyEulerFunction *
                                                                      this->predatorEulerFunction)
                                                             )
                                                     )
                                             )
        );
    }

    virtual void alphaVariation(int time) = 0;

public :
    double preyInitialPopulation, predatorInitialPopulation, alpha, delta, timeVariation;
    unsigned int cycleInterval = 500, totalOfMonths;

    void calc() {

        this->chartInitialPoints.push_back(
                std::make_pair(
                        round(this->preyInitialPopulation),
                        round(this->predatorInitialPopulation)
                )
        );

        this->beforeCalculation();
        this->setupChart();

        for (int time = 1; time <= this->totalOfMonths; time++) {

            // Diferentes criterios para definição de alpha
            this->alphaVariation(time);

            this->preyPopulationT3 = this->preyPopulationT2 + (this->timeVariation / 2) * (
                    (
                            3 * (
                                    (this->alpha * this->preyPopulationT2) -
                                    (this->beta * this->preyPopulationT2 * this->predatorPopulationT2)
                            )
                    ) -
                    (
                            (this->alpha * this->preyPopulationT1) -
                            (this->beta * this->preyPopulationT1 * this->predatorPopulationT1)
                    )
            );

            this->predatorPopulationT3 = this->predatorPopulationT2 + (this->timeVariation / 2) * (
                    (
                            3 * (
                                    (-1 * this->gama * this->predatorPopulationT2) +
                                    (this->delta * this->preyPopulationT2 * this->predatorPopulationT2)
                            )
                    ) -
                    (
                            (-1 * this->gama * this->predatorPopulationT1) +
                            (this->delta * this->preyPopulationT1 * this->predatorPopulationT1)
                    )
            );


            this->chartPoints.push_back(
                    std::make_pair(
                            round(this->preyPopulationT1),
                            round(this->predatorPopulationT1)
                    )
            );

            //Avançando: k-1 <- k e k <- k+1
            this->preyPopulationT1 = this->preyPopulationT2;
            this->preyPopulationT2 = this->preyPopulationT3;

            this->predatorPopulationT1 = this->predatorPopulationT2;
            this->predatorPopulationT2 = this->predatorPopulationT3;

            //Atualiza o grafico
            this->printChart();

            //Espera para ver a evolucao do grafico
            usleep(this->cycleInterval);
        }

    }
};

#endif //REILEAO_ADAMSBASHFORD_H

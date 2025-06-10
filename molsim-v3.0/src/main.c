/*****************************************************************
 *  Filename     : main.c
 *  Description  : run
 *  Author       : Ogawa <ocmikanmgmg@gmail.com>
 *  Created      : Jun 7, 2025
 *  Compiler     : arm-none-eabi-gcc
 *  SBC          : Raspberry Pi Zero 2 W (32bit)
 *  License      : MIT License
 *  Note         : 
 *  History      : 2025/06/07 - ファイル作成
 *  最終編集 2025/6/8
 *****************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "parameter.h"
#include "atom.h"
#include "force.h"
#include "integrator.h"

int main(void) {
    Parameter *parameter = {
        parameter->atomNum           = 3,
        parameter->simulationStep    = 100,
        parameter->timeStep          = 0.01,
        parameter->epsilonVal        = 1.0,
        parameter->sigmaVal          = 1.0,
        parameter->atomMass          = 1.0,
        parameter->cutoffCoefficient = 2.5,
        parameter->cellSize[0]       = 10;
        parameter->cellSize[1]       = 10;
        parameter->cellSize[2]       = 10;
    };





















    u4 simstep = 0;
    printf("刻み幅入力　　:");
    usleep(300000);
    printf("0.01(自動設定)\n");
    usleep(100000);
    printf("質量入力　　　:");
    usleep(300000);
    printf("1(自動設定)\n");
    usleep(100000);
    printf("カットオフ入力:");
    usleep(300000);
    printf("2.5(自動設定)\n");
    usleep(100000);
    printf("ステップ数入力:");
    scanf("%ld", &simstep);
    usleep(1);
    printf("RUN SIMULATIOM\n");

    Atom *atom = (Atom *)malloc(sizeof(Atom) * parameter.atomNum);
    initialize_atom(atom, parameter);
    atom[0].atomPosition[0] = 0.0;
    atom[1].atomPosition[0] = 9.0;
    atom[2].atomPosition[0] = 5.0;


    calculation_force(atom, &parameter);
/*
    for (u4 step = 0; step < simstep; step++) {
        velocity_verlet(atoms, &parameter);
        printf("Step %lu: Atom0 Pos = %f, Atom1 Pos = %f\n",
               step, atoms[0].atomPosition[0], atoms[1].atomPosition[0]);
        usleep(10000);
    }
*/
    for(u4 step = 0; step < simstep; step++) {
        velocity_verlet(atom, &parameter);
        //for(u4 atomId = 0; atomId < atom->atomId; atomId++) {
        //↑これはoutputで書くべきかも
    }
  

    free(atom);
    return 0;

}




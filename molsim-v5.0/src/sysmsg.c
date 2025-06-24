/*****************************************************************
 *  Filename     : sysmsg.c
 *  Description  : to calcration time step
 *  Author       : Ogawa <ocmikanmgmg@gmail.com>
 *  Created      : Jun 7, 2025
 *  Compiler     : arm-none-eabi-gcc
 *  SBC          : Raspberry Pi Zero 2 W
 *  License      : MIT License
 *  Note         : 
 *  History      : 2025/06/07 - ファイル作成
 *****************************************************************/
#include "sysmsg.h"

void system_message(Parameter *parameter){
    printf("MD-simulation ver4.1 温度制御を追加．\n");
    usleep(300000);
    printf("検証効率化のため自動入力します...\n");
    usleep(300000);
    printf("\n");
    for(int i=0;i<10000;i++) {
        printf("\r初期パラメータ構築中：     %d",i * (int)rand());
        usleep(100);
    }
    printf("\n");

    printf("目標温度　　　　　:");
    usleep(100000);
    scanf("%lf", &(parameter->initialTemperature));
    //printf("10\n");
    //parameter->atomNum = 40;
    usleep(100000);

    printf("原子の初期配置をします，\n");
    printf("原子間隔:");
    usleep(100000);
    printf("3");
    usleep(100000);
/*
    printf("原子数　　　　　:");
    usleep(100000);
    //scanf("%lu", &(parameter->atomNum));
    printf("10\n");
    parameter->atomNum = 40;
    usleep(100000);
*/

    printf("ステップ　　　　:");
    usleep(100000);
    //scanf("%lu", &(parameter->simulationStep));
    printf("100\n");
    parameter->simulationStep = 100;
    usleep(100000);    

    printf("刻み幅　　　　　:");
    usleep(100000);
    //scanf("%lf", &(parameter->timeStep));
    printf("0.1\n");
    parameter->timeStep = 0.1;
    usleep(100000);

    printf("sigma　　　　　:");
    usleep(100000);
    printf("1.0\n");
    usleep(100000);
/*
    printf("ε　　  　　　　:");
    usleep(100000);
    printf("1.0\n");
    usleep(100000);
*/

    printf("カットオフ　　　:");
    usleep(100000);
    printf("2.5\n");
    usleep(100000);

    printf("セルX長さ　　　　:");
    usleep(100000);
    //scanf("%lf", &(parameter->cellSize[0]));
    printf("40\n");
    parameter->cellSize[0] = 40;
    usleep(100000);

    printf("セルY長さ　　　 :");
    usleep(100000);
    //scanf("%lf", &(parameter->cellSize[1]));
    printf("40\n");
    parameter->cellSize[1] = 40;
    usleep(100000);

    printf("セルZ長さ　　　 :");
    usleep(100000);
    //scanf("%lf", &(parameter->cellSize[2]));
    printf("40\n");
    parameter->cellSize[2] = 40;
    usleep(100000);

    printf("初期配置間隔　　:");
    usleep(100000);
    //scanf("%lf", &(parameter->atomInterval));
    printf("1\n");
    parameter->atomInterval = 1;
    usleep(1);

    usleep(1);
    printf("RUN SIMULATIOM\n");
}
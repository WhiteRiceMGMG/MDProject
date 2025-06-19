/*****************************************************************
 *  Filename     : main.c
 *  Description  : ファイル分割を統合
 *  Author       : Ogawa <ocmikanmgmg@gmail.com>
 *  Created      : Jun 11, 2025
 *  Compiler     : arm-none-eabi-gcc
 *  SBC          : Raspberry Pi Zero 2 W
 *  License      : Ogawa license
 *  Note         : ファイルをすべて統合した
 *  History      : 2025/06/15 - 統合版作成
 *****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <math.h>



 #define THREE_DIMENSION 3

typedef char               s1;   /* signed 1 byte (8 bit) */
typedef short              s2;   /* signed 2 bytes (16 bit) */
typedef long               s4;   /* signed 4 bytes (32 bit) */
typedef long long          s8;   /* signed 8 bytes (64 bit) */

typedef unsigned char      u1;   /* unsigned 1 byte (8 bit) */
typedef unsigned short     u2;   /* unsigned 2 bytes (16 bit) */
typedef unsigned long      u4;   /* unsigned 4 bytes (32 bit) */
typedef unsigned long long u8;   /* unsigned 8 bytes (64 bit) */

typedef float              f4;   /* 4 bytes float (single precision) */
typedef double             f8;   /* 8 bytes float (double precision) */

typedef struct {
    u4 atomId;
    f8 atomPosition[3];
    f8 atomVelocity[3];
    f8 atomForce[3];
} Atom;


typedef struct {
    u4 atomNum;
    u4 simulationStep;
    f8 timeStep;
    f8 epsilonVal;
    f8 sigmaVal;
    f8 atomMass;
    f8 cutoffCoefficient;
    f8 cellSize[3];
    f8 atomInterval;
    f8 initialTemperature;
    f8 currentTemperature;
    f8 boltzmannVal;
} Parameter;

void initialize_atom(Atom *atom, Parameter *parameter);
f8 apply_period(f8 position, Parameter *parameter, f8 cellMax);
void calculation_force(Atom *atom, Parameter *parameter);
void velocity_verlet(Atom *atom, Parameter *parameter);
void write_file(Atom *atom, Parameter *parameter, u4 step);
void calculate_temperature(Atom *atom, Parameter *parameter);
void control_temperature(Atom *atom, Parameter *parameter);
f8 rand_normal(f8 mean, f8 stddev);
f8 calculation_minimam(f8 rij, f8 cellMax);
void system_message(Parameter *parameter);

int main(void) {
    Parameter *parameter = (Parameter *)malloc(sizeof(Parameter));
    
    parameter->atomNum            = 100;    /*原子の数*/
    parameter->simulationStep     = 100;    /*シミュレーションステップ*/
    parameter->timeStep           = 0.1;    /*1ステップあたりの時間*/
    parameter->epsilonVal         = 1.0;  /*原子間の引力*/
    parameter->sigmaVal           = 1.0;  /*ポテンシャルエネルギー最小位置*/
    parameter->atomMass           = 1.0;  /*原子質量*/
    parameter->cutoffCoefficient  = 2.5;  /*カットオフ距離*/
    parameter->cellSize[0]        = 20;    /*X方向のセルの長さ*/
    parameter->cellSize[1]        = 20;    /*Y方向のセルの長さ*/
    parameter->cellSize[2]        = 20;    /*Z方向のセルの長さ*/
    parameter->atomInterval       = 1;    /*初期原子間距離*/
    parameter->initialTemperature = 300;    /*初期温度*/
    parameter->currentTemperature = 0;    /*現在の温度*/
    parameter->boltzmannVal       = 1;    /*ボルツマン定数*/

    system_message(parameter);
    

    Atom *atom = (Atom *)malloc(sizeof(Atom) * parameter->atomNum);
    initialize_atom(atom, parameter);
//-----------------------------------------------------------
    double kT_over_m = parameter->boltzmannVal * parameter->initialTemperature / parameter->atomMass;
    double stddev = sqrt(kT_over_m); 

    for (u4 i = 0; i < parameter->atomNum; i++) {
        for (u4 d = 0; d < 3; d++) {
            atom[i].atomVelocity[d] = rand_normal(0.0, stddev); 
        }
    }

    double vcm[3] = {0.0, 0.0, 0.0};
    for (u4 i = 0; i < parameter->atomNum; i++) {
        for (u4 d = 0; d < 3; d++) {
            vcm[d] += atom[i].atomVelocity[d];
        }
    }
    for (u4 d = 0; d < 3; d++) {
        vcm[d] /= parameter->atomNum;
    }
    for (u4 i = 0; i < parameter->atomNum; i++) {
        for (u4 d = 0; d < 3; d++) {
            atom[i].atomVelocity[d] -= vcm[d]; 
        }
    }    
//-----------------------------------------------------------
    // ランダム配置（最小距離を考慮）
    double minDistance = 1.0; // 原子間の最小距離
    srand(time(NULL)); // ランダムシードを設定

    for (u4 i = 0; i < parameter->atomNum; i++) {
        int valid = 0;
        while (!valid) {
            valid = 1; // 配置が有効か仮定
            for (u4 dimension = 0; dimension < 3; dimension++) {
                atom[i].atomPosition[dimension] =
                    ((double)rand() / RAND_MAX) * parameter->cellSize[dimension];
            }
            for (u4 j = 0; j < i; j++) {
                double distanceSquared = 0.0;
                for (u4 dimension = 0; dimension < 3; dimension++) {
                    double diff = atom[i].atomPosition[dimension] - atom[j].atomPosition[dimension];
                    distanceSquared += diff * diff;
                }
                if (sqrt(distanceSquared) < minDistance) {
                    valid = 0; // 配置をやり直す
                    break;
                }
            }
        }
    }

/*
    atom[0].atomPosition[0] = 0.0;
    atom[1].atomPosition[0] = 9.0;
    atom[2].atomPosition[0] = 5.0;
*/

    calculation_force(atom, parameter);

    for(u4 step = 0; step < parameter->simulationStep; step++) {
        if (step == 0) {
            calculate_temperature(atom, parameter);
            control_temperature(atom, parameter);
        }
        velocity_verlet(atom, parameter);
        //printf("Step %lu: Atom0 Pos = %f, Atom1 Pos = %f \n",
        //       step, atom[0].atomPosition[0], atom[1].atomPosition[0]);
        printf("Step:%lu  ", step);
        //if (step % 5 == 0) {
            calculate_temperature(atom, parameter);
            printf("Temperature:%f\n",parameter->currentTemperature);
 //           control_temperature(atom, parameter);
        //}
        
           write_file(atom,parameter,step);


        //for(u4 atomId = 0; atomId < atom->atomId; atomId++) {
        //↑これはoutputで書くべきかも
    }
  

    free(atom);
    return 0;
}

void initialize_atom(Atom *atom, Parameter *parameter) {
    u4 i = 0;
    u1 dimension = 0;
    for (i = 0; i < parameter->atomNum; i++) {
        (atom + i) -> atomId = i;
        for(dimension = 0; dimension < THREE_DIMENSION; dimension++) {
            *((atom + i)->atomPosition + dimension) = 0;
            *((atom + i)->atomVelocity + dimension) = 0;
            *((atom + i)->atomForce + dimension) = 0;
        }
    }
}

f8 apply_period(f8 position, Parameter *parameter, f8 cellMax) {
    
    while (position >= cellMax) {
        position -= cellMax;
    }
    while (position < 0) {
        position += cellMax;
    }
    return position;
}

f8 calculation_minimam(f8 rij, f8 cellMax) {
    if(rij > 0.5 * cellMax) {
        rij -= cellMax;
    } else if(rij < -0.5 * cellMax) {
        rij += cellMax;
    } else {
        ;
    }
    return rij;
}


void calculation_force(Atom *atom, Parameter *parameter) {
    u4 i                    = 0; 
    u4 j                    = 0;
    u1 dimension            = 0;
    f8 rij[THREE_DIMENSION] = {0};
    f8 r2                   = 0;
    f8 r6                   = 0;
    f8 r12                  = 0;
    f8 fij                  = 0;
    f8 fMeg                 = 0;
    f8 cellSize             = 0;
    f8 epsilon              = parameter -> epsilonVal;
    f8 sigma                = parameter -> sigmaVal;
    f8 cutoff               = parameter -> cutoffCoefficient * sigma;
    f8 cutoff2              = cutoff * cutoff;

    for(i = 0; i < parameter -> atomNum; i++) {
        (atom + i) -> atomId = i;
        for(dimension = 0; dimension < THREE_DIMENSION; dimension++) {
            *((atom + i) -> atomForce + dimension) = 0;
        }
    }

    for(i = 0; i < parameter -> atomNum - 1; i++) {
        for(j = i + 1; j < parameter -> atomNum; j++) {
            r2 = 0;
            for(dimension = 0; dimension < THREE_DIMENSION; dimension++) {
                rij[dimension] = atom[j].atomPosition[dimension] 
                                   - atom[i].atomPosition[dimension];
                cellSize = parameter -> cellSize[dimension];
                rij[dimension] = calculation_minimam(rij[dimension],cellSize) ;               
                r2 += rij[dimension] * rij[dimension];
            }
            if (r2 < 1e-12) {
                printf("[警告] r^2 = %.10f between atom %lu and atom %lu\n", r2, i, j);
                continue;
            }
            if(r2 < cutoff2) {
                r6 = (sigma * sigma) / r2;
                r6 = r6 * r6 * r6;
                r12 = r6 * r6;
                fMeg = 24 * epsilon * (2 * r12 - r6) / r2;
                for(dimension = 0; dimension < 3; dimension++) {
                    fij = fMeg * rij[dimension];
                    atom[i].atomForce[dimension] += fij;
                    atom[j].atomForce[dimension] -= fij;
                }
            }
        }
    }
}

void velocity_verlet(Atom *atom, Parameter *parameter) {
    u4 i            = 0;
    u4 dimension    = 0;
    f8 acceleration = 0;
    f8 cellSize[3]  = {0};
    u4 atomNum      = parameter -> atomNum;
    f8 mass         = parameter -> atomMass;
    f8 timeStep     = parameter -> timeStep;
    f8 halfTimeStep = timeStep * 0.5; 

    for(dimension = 0; dimension < THREE_DIMENSION; dimension++) {
        cellSize[dimension] = parameter->cellSize[dimension];
    }

    for(i = 0; i < atomNum; i++) {
        for(dimension = 0; dimension < THREE_DIMENSION; dimension++) {
            acceleration = atom[i].atomForce[dimension] / mass;
            atom[i].atomVelocity[dimension] += halfTimeStep * acceleration;
        }
    }
    
    for(i = 0; i < atomNum; i++) {
        for(dimension = 0; dimension < THREE_DIMENSION; dimension++) {
            atom[i].atomPosition[dimension] += timeStep * atom[i].atomVelocity[dimension];
            //↓ポインタ渡ししたかったけど，iとdimensionも渡すのがめんどいのと，多分渡す値自体もf8で軽いからこうした．
            //引数にparameter構造体を指定しているが，多分ここは削れると思う．
            atom[i].atomPosition[dimension] = apply_period(atom[i].atomPosition[dimension], parameter,cellSize[dimension]); 
        }
    }



    calculation_force(atom, parameter);

    for(i = 0; i < atomNum; i++) {
        for(dimension = 0; dimension < THREE_DIMENSION; dimension++) {
            acceleration = atom[i].atomForce[dimension] / mass;
            atom[i].atomVelocity[dimension] += halfTimeStep * acceleration;
        }
    }

    /*ここら辺から速度スケーリング法適応したい． */
    
}


void write_file(Atom *atom, Parameter *parameter, u4 step) {
    


    u4 i = 100;
    FILE *file;
    file = fopen("test.txt", "a");
    if (file == NULL) {
        perror("ファイルオープンに失敗");
        return;
    }

    fprintf(file,"%lu\n",parameter->atomNum);
    fprintf(file, "timestep %lu  \n", step);
    for(i = 0; i < parameter->atomNum;i++) {
        //fprintf(file, "atom:%lu  ", atom[i].atomId);
        fprintf(file,"A ");
        for(u4 dimension = 0; dimension < 3; dimension++) {
            fprintf(file, "%f ", atom[i].atomPosition[dimension]);
        }
        fprintf(file, "\n");
    }
    //fprintf(file, "--------------------------------------------------------------------------\n");
    fclose(file);
    return;



}

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


    printf("原子数　　　　　:");
    usleep(100000);
    //scanf("%lu", &(parameter->atomNum));
    printf("10\n");
    parameter->atomNum = 40;
    usleep(100000);

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

void calculate_temperature(Atom *atom, Parameter *parameter){
    f8 *atomVelocity          = atom->atomVelocity;    
    u4 atomNum                = parameter->atomNum;
    f8 atomMass               = parameter->atomMass;
    f8 boltzmannVal           = parameter->boltzmannVal;
    f8 currentTemperature     = parameter->currentTemperature;
    f8 initialTemperature     = parameter->initialTemperature;
    u4 dimension              = 0;
    f8 temporaryTemperature   = 0;
    u4 i                      = 0;
    f8 temperatureCoefficient = 0;

    for (i = 0; i < atomNum; i++) {
        for(dimension = 0; dimension < THREE_DIMENSION; dimension++) {
            temporaryTemperature += atomVelocity[i * THREE_DIMENSION + dimension] 
                                    * atomVelocity[i * THREE_DIMENSION + dimension];
        }
    }
    parameter->currentTemperature 
                = temporaryTemperature * atomMass  / (3 * atomNum * boltzmannVal);
}

void control_temperature(Atom *atom, Parameter *parameter){
    u4 i         = 0;
    u4 dimension = 0;
    f8 targetTemperature = parameter->initialTemperature;
    f8 currentTemperature = parameter->currentTemperature;
    f8 modifyTemperature  = sqrt(targetTemperature / currentTemperature);
    for(i = 0; i < parameter->atomNum; i++) {
        for(dimension = 0; dimension < THREE_DIMENSION; dimension++) {
            atom->atomVelocity[i * THREE_DIMENSION + dimension] = 
                atom->atomVelocity[i * THREE_DIMENSION + dimension] * modifyTemperature;
        }
    }
}
/*
    temperatureCoefficient = initialTemperature / currentTemperature;
    temperatureCoefficient *= temperatureCoefficient;
*/

f8 rand_normal(f8 mean, f8 stddev) {
    double u1 = ((double)rand() + 1.0) / ((double)RAND_MAX + 2.0);
    double u2 = ((double)rand() + 1.0) / ((double)RAND_MAX + 2.0);
    return mean + stddev * sqrt(-2.0 * log(u1)) * cos(2.0 * M_PI * u2);
}


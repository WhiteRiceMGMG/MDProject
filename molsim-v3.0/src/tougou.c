/*****************************************************************
 *  Filename     : main.c
 *  Description  : ファイル分割を統合
 *  Author       : Ogawa <ocmikanmgmg@gmail.com>
 *  Created      : Jun 11, 2025
 *  Compiler     : arm-none-eabi-gcc
 *  SBC          : Raspberry Pi Zero 2 W
 *  License      : Ogawa license
 *  Note         : ファイル全部統合した
 *  History      : 2025/06/010 - プログラム作成開始
 *****************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <math.h>

#define THREE_DIMENSION 3

typedef char               s1;
typedef short              s2;
typedef long               s4;
typedef long long          s8;
typedef unsigned char      u1;
typedef unsigned short     u2;
typedef unsigned long      u4;
typedef unsigned long long u8;
typedef float              f4;
typedef double             f8;

//1原子あたり80byteってことは，100万原子で80MBくらい？
//あとアライメントf8，4byteのパディングを活用したい
typedef struct {
    u4 atomId;
  //u4 atomType; とか？←アリアリ
    f8 atomPosition[3];
    f8 atomVelocity[3];
    f8 atomForce[3];
} Atom;

//これはいいや パディングなし
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

} Parameter;

void initialize_atom(Atom *atom, Parameter *parameter);
f8 apply_period(f8 position, Parameter *parameter, f8 cellMax);
f8 calculation_minimam(f8 rij, f8 cellMax);
void calculation_force(Atom *atom, Parameter *parameter);
void velocity_verlet(Atom *atom, Parameter *parameter);
void write_file(Atom *atom, Parameter *parameter, u4 step);

//main関数の入力の部分は関数作るでぐちゃぐちゃや→sys_msg関数とか作るで
int main(void) {
    Parameter *parameter = (Parameter *)malloc(sizeof(Parameter));
    parameter->atomNum           = 0;
    parameter->simulationStep    = 0;
    parameter->timeStep          = 0;
    parameter->epsilonVal        = 1.0;
    parameter->sigmaVal          = 1.0;
    parameter->atomMass          = 1.0;
    parameter->cutoffCoefficient = 2.5;
    parameter->cellSize[0]       = 0;
    parameter->cellSize[1]       = 0;
    parameter->cellSize[2]       = 0;
    parameter->atomInterval      = 0;
    printf("原子数 10推奨    ：");
    usleep(100000);
    scanf("%lu", &(parameter->atomNum));
    usleep(100000);

    printf("ステップ数 100推奨：");
    usleep(100000);
    scanf("%lu", &(parameter->simulationStep));
    usleep(100000);    

    printf("刻み幅 0.1推奨    ：");
    usleep(100000);
    scanf("%lf", &(parameter->timeStep));
    usleep(100000);

    printf("σ                  ：");
    usleep(100000);
    printf("1.0(自動設定)\n");
    usleep(100000);

    printf("ε                  ：");
    usleep(100000);
    printf("1.0(自動設定)\n");
    usleep(100000);

    printf("カットオフ入力     :");
    usleep(100000);
    printf("2.5(自動設定)\n");
    usleep(100000);
    
    printf("セルX長さ 5推奨   :");
    usleep(100000);
    scanf("%lf", &(parameter->cellSize[0]));
    usleep(100000);

    printf("セルY長さ 5推奨  ：");
    usleep(100000);
    scanf("%lf", &(parameter->cellSize[1]));
    usleep(100000);

    printf("セルZ長さ 5推奨  ：");
    usleep(100000);
    scanf("%lf", &(parameter->cellSize[2]));
    usleep(100000);

    printf("初期配置間隔 1推奨 ：");
    usleep(100000);
    scanf("%lf", &(parameter->atomInterval));
    usleep(1);

    usleep(1);
    printf("RUN SIMULATIOM\n");

    Atom *atom = (Atom *)malloc(sizeof(Atom) * parameter->atomNum);
    initialize_atom(atom, parameter);

    // ここら辺ぐちゃぐちゃ治したい，変数宣言ここでしたくない
    double minDistance = 1.0; 
    srand(time(NULL)); 

    for (u4 i = 0; i < parameter->atomNum; i++) {
        int valid = 0;
        while (!valid) {
            valid = 1; 
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
                    valid = 0; 
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
        velocity_verlet(atom, parameter);
        printf("Step %lu: Atom0 Pos = %f, Atom1 Pos = %f\n",
               step, atom[0].atomPosition[0], atom[1].atomPosition[0]);
        if(step == (parameter->simulationStep / 100)) {
            printf("◻️");
        }
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

}

void write_file(Atom *atom, Parameter *parameter, u4 step) {
    


    u4 i = 100;
    FILE *file;
    file = fopen("test.xyz", "a");
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


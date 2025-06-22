/*****************************************************************
 *  Filename     : boundary.c
 *  Description  : to calcration time step
 *  Author       : Ogawa <ocmikanmgmg@gmail.com>
 *  Created      : Jun 7, 2025
 *  Compiler     : arm-none-eabi-gcc
 *  SBC          : Raspberry Pi Zero 2 W
 *  License      : MIT License
 *  Note         : 
 *  History      : 2025/06/08 - ファイル作成
 *****************************************************************/
#include "initialAtom.h"

void initial_atom_position_lattice(Atom *atom, Parameter *parameter) {
    u4 i             = 0;
    u4 j             = 0;
    u4 k             = 0;
    f8 latticeLength = 10;
    f8 atomBetween   = 0;

    for(i = 0; i < latticeLength; i++) {
        for(j = 0; j < latticeLength; j++) {
            for(k = 0; k < latticeLength; k++) {
                //ここで分子の初期配置をする，なんかアイデアないかな．ちょっと難しいンゴね
                *(atom->atomPosition + 0) = i * latticeLength;
                *(atom->atomPosition + 1) = j * latticeLength;
                *(atom->atomPosition + 2) = k * latticeLength;
                 
            }
        }
    }
}
/*****************************************************************
 *  Filename     : atom.h
 *  Description  : define atom
 *  Author       : Ogawa <ocmikanmgmg@gmail.com>
 *  Created      : Aug 24, 2025
 *  Compiler     : gcc
 *  SBC          : Raspberry Pi Zero 2 W (32bit)
 *  License      : OGW License
 *  Note         : no windows
 *  History      : 2025/08/24 - ファイル作成
 *  最終編集 2025/08/24
 *****************************************************************/
 #include <includes.h>

 #ifndef ATOM_H
 #define ATOM_H

 typedef struct
 {
    u4 atmId;
    f8 atmPos[3];
    f8 atmVel[3];
    f8 atmFoc[3];
 } Atom;

 void initialize_atom(Atom  *atom, Parameter *parameter);

 #endif

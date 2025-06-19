/*****************************************************************
 *  Filename     : sysdef.h
 *  Description  : to define fixed length integer type
 *  Author       : Ogawa <ocmikanmgmg@gmail.com>
 *  Created      : Jun 7, 2025
 *  Compiler     : arm-none-eabi-gcc
 *  SBC          : Raspberry Pi Zero 2 W (32bit)
 *  License      : MIT License
 *  Note         : 
 *  History      : 2025/06/07 - ファイル作成
 *****************************************************************/
#ifndef SYSDEF_H
#define SYSDEF_H

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

#endif 
/*******************************************************************************
Firenzina is a UCI chess playing engine by
Kranium (Norman Schmidt), Yuri Censor (Dmitri Gusev) and ZirconiumX (Matthew Brades).
Rededication: To the memories of Giovanna Tornabuoni and Domenico Ghirlandaio.
Special thanks to: Norman Schmidt, Jose Maria Velasco, Jim Ablett, Jon Dart, Andrey Chilantiev, Quoc Vuong.
Firenzina is a clone of Fire 2.2 xTreme by Kranium (Norman Schmidt).
Firenzina is a derivative (via Fire) of FireBird by Kranium (Norman Schmidt)
and Sentinel (Milos Stanisavljevic). Firenzina is based (via Fire and FireBird)
on Ippolit source code: http://ippolit.wikispaces.com/
Ippolit authors: Yakov Petrovich Golyadkin, Igor Igorovich Igoronov,
and Roberto Pescatore
Ippolit copyright: (C) 2009 Yakov Petrovich Golyadkin
Ippolit date: 92th and 93rd year from Revolution
Ippolit owners: PUBLICDOMAIN (workers)
Ippolit dedication: To Vladimir Ilyich
"This Russian chess ship is a truly glorious achievement of the
 October Revolution and Decembrists movement!"

Firenzina is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Firenzina is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see http://www.gnu.org/licenses/.
*******************************************************************************/
#pragma once

#include "fire.h" // Added by YC on 1/9/2014

static int SlabNumber = -1;
static bool LargeSlab = false;

static uint8_t *SlabRootLoc = NULL;
static uint8_t *CurrentSlabLoc;
static int64_t CurrentSlabSize = 0;

typedef struct
    {
    int16_t Value;
    uint8_t token, flags;
    } typeMaterial;
SlabDeclare2(typeMaterial, Material, 419904);

SlabDeclare1(typeMM, RookMM, 64);
SlabDeclare1(typeMM, BishopMM, 64);
SlabDeclare2(uint64_t, MMOrtho, 102400);
SlabDeclare2(uint64_t, MMDiag, 5248);

typePos RootPosition[MaxCPUs][RPperCPU];
typePos RootPosition0[1], NullParent[1];

int16_t MaxPositionalGain[0x10][010000];
#define MaxPosGain(piece, mos) MaxPositionalGain[piece][mos]
#define HistoryValue(P, M) HistoryPITo (P, P->sq[From (M)],To (M))
uint16_t History[0x10 * 0100];
#define HistoryPITo(P, PI, To) History[(PI) * 0100 + (To)]
int32_t PieceSquareValue[0x10][0100];
#define PST(pi, sq) PieceSquareValue[pi][sq]

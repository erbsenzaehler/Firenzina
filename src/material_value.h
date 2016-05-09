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

#include "fire.h"

#define I(a,b,c) ((a & 0xff) | (b << 8) | (0 << 27))
#define QueenEnding 1
#define RookEnding 2
#define OppositeBishopEnding 3
#define BishopEnding 4
#define KnightEnding 5
#define BishopKnightEnding 6
#define PawnEnding 7
#define WhiteMinorOnly 8
#define BlackMinorOnly 16
#define BishopKnightMate 32

#define Value4(w, x, y, z) \
	((((uint64_t) (z)) << 48) + (((uint64_t) (y)) << 32) + \
	(((uint64_t) (x)) << 16) + (((uint64_t) (w)) << 0)) ///todo

#define ValueP  Value4 ( 80,  90,  110,  120)
#define ValueN  Value4 (240, 270,  330,  360)
#define ValueB  Value4 (248, 279,  341,  372)
#define ValueR  Value4 (400, 450,  550,  600)
#define ValueQ  Value4 (760, 855, 1045, 1140)
#define ValueBP Value4 ( 36,  40,   49,   54)


#define KnightPawnBonus Value4 (0, 2, 4, 5)
#define BishopPawnPenalty Value4(0, 1, 2, 3)
#define RookPawnPenalty Value4 (5, 4, 2, 0)
#define TwoRookPenalty Value4(16, 20, 28, 32)
#define QandRPenalty Value4(8, 10, 14, 16)
#define MoreMinorsBonus Value4(20, 15, 10, 5)
#define BPNoMinorsBonus Value4(5, 5, 5, 5)

#define Phase_Minor (1)
#define PhaseRook (3)
#define PhaseQueen (6)
const static uint32_t MaterialValue[16] =
    {
    0, I(0, 0x1440, 1), I(1, 0x240, 1), 0, I(1, 0x24, 1), I(1, 0x48, 1), I(3, 0x04, 1), I(6, 0x1, 1),
	0, I(0, 0xb640, 1), I(1, 0x6c0, 1), 0, I(1, 0x90, 1), I(1, 0x120, 1), I(3, 0xc, 1), I(6, 0x2, 1)
    };

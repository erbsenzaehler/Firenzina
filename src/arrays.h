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

#define HashWTM (0x1220ab8c00000004)
#define InterPose(x, y) Interpose[x][y]
#define Evade(x, y) Evade[x][y]
#define Line(x, y) Line[x][y]
#define Hash(pi, sq) Zobrist[pi][sq]
uint64_t Interpose[64][64], Evade[64][64];
int8_t Line[64][64];
uint64_t Zobrist[16][64];

#define Rank1 0x00000000000000ff
#define Rank2 0x000000000000ff00
#define Rank3 0x0000000000ff0000
#define Rank4 0x00000000ff000000
#define Rank5 0x000000ff00000000
#define Rank6 0x0000ff0000000000
#define Rank7 0x00ff000000000000
#define Rank8 0xff00000000000000

#define FileA 0x0101010101010101
#define FileB 0x0202020202020202
#define FileC 0x0404040404040404
#define FileD 0x0808080808080808
#define FileE 0x1010101010101010
#define FileF 0x2020202020202020
#define FileG 0x4040404040404040
#define FileH 0x8080808080808080

static const uint64_t RankArray[8] =
    {
	0x00000000000000ff, 0x000000000000ff00,
	0x0000000000ff0000, 0x00000000ff000000,
	0x000000ff00000000, 0x0000ff0000000000,
	0x00ff000000000000, 0xff00000000000000
    };
static const uint64_t FileArray[8] =
    {
	0x0101010101010101, 0x0202020202020202,
	0x0404040404040404, 0x0808080808080808,
	0x1010101010101010, 0x2020202020202020,
	0x4040404040404040, 0x8080808080808080
    };

SlabDeclare1(uint64_t, SqSet, 64);
SlabDeclare1(uint64_t, SqClear, 64);
SlabDeclare1(uint64_t, NonDiag, 64);
SlabDeclare1(uint64_t, NonOrtho, 64);
SlabDeclare1(uint64_t, Ortho, 64);
SlabDeclare1(uint64_t, Diag, 64);
SlabDeclare1(uint64_t, OrthoDiag, 64);
SlabDeclare1(uint64_t, OpenFileW, 64);
SlabDeclare1(uint64_t, OpenFileB, 64);
SlabDeclare1(uint64_t, PassedPawnW, 64);
SlabDeclare1(uint64_t, PassedPawnB, 64);
SlabDeclare1(uint64_t, ProtectedPawnW, 64);
SlabDeclare1(uint64_t, ProtectedPawnB, 64);
SlabDeclare1(uint64_t, IsolatedPawnW, 64);
SlabDeclare1(uint64_t, IsolatedPawnB, 64);
SlabDeclare1(uint64_t, ConnectedPawns, 64);
SlabDeclare1(uint64_t, InFrontW, 8);
SlabDeclare1(uint64_t, NotInFrontW, 8);
SlabDeclare1(uint64_t, InFrontB, 8);
SlabDeclare1(uint64_t, NotInFrontB, 8);
SlabDeclare1(uint64_t, IsolatedFiles, 8);
SlabDeclare1(uint64_t, FilesLeft, 8);
SlabDeclare1(uint64_t, FilesRight, 8);
SlabDeclare1(uint64_t, Doubled, 64);
SlabDeclare1(uint64_t, Left2, 64);
SlabDeclare1(uint64_t, Right2, 64);
SlabDeclare1(uint64_t, Left1, 64);
SlabDeclare1(uint64_t, Right1, 64);
SlabDeclare1(uint64_t, Adjacent, 64);
SlabDeclare1(uint64_t, LongDiag, 64);
SlabDeclare1(uint64_t, Northwest, 64);
SlabDeclare1(uint64_t, Southwest, 64);
SlabDeclare1(uint64_t, Northeast, 64);
SlabDeclare1(uint64_t, Souteast, 64);
SlabDeclare1(uint64_t, QuadrantWKwtm, 64);
SlabDeclare1(uint64_t, QuadrantBKwtm, 64);
SlabDeclare1(uint64_t, QuadrantWKbtm, 64);
SlabDeclare1(uint64_t, QuadrantBKbtm, 64);
SlabDeclare1(uint64_t, ShepherdWK, 64);
SlabDeclare1(uint64_t, ShepherdBK, 64);
SlabDeclare1(uint64_t, HashCastling, 16);
SlabDeclare1(uint64_t, HashEP, 8);
SlabDeclare1(uint64_t, HashRev, 16);
SlabDeclare1(uint64_t, AttN, 64);
SlabDeclare1(uint64_t, AttK, 64);
SlabDeclare1(uint64_t, AttPw, 64);
SlabDeclare1(uint64_t, AttPb, 64);

static const uint64_t Ranks2to6NotA = 0x0000fefefefefe00;
static const uint64_t Ranks2to6NotAB = 0x0000fcfcfcfcfc00;
static const uint64_t Ranks2to6 = 0x0000ffffffffff00;
static const uint64_t Ranks2to6NotH = 0x00007f7f7f7f7f00;
static const uint64_t Ranks2to6NotGH = 0x00003f3f3f3f3f00;
static const uint64_t Ranks3to7NotA = 0x00fefefefefe0000;
static const uint64_t Ranks3to7NotAB = 0x00fcfcfcfcfc0000;
static const uint64_t Ranks3to7 = 0x00ffffffffffff0000;
static const uint64_t Ranks3to7NotGH = 0x003f3f3f3f3f0000;
static const uint64_t Ranks3to7NotH = 0x007f7f7f7f7f0000;
static const uint64_t White = 0x55aa55aa55aa55aa;
static const uint64_t Black = 0xaa55aa55aa55aa55;
static const uint64_t Rank2NotA = 0x000000000000fe00;
static const uint64_t Rank2NotH = 0x0000000000007f00;
static const uint64_t Rank7NotA = 0x00fe000000000000;
static const uint64_t Rank7NotH = 0x007f000000000000;
static const uint64_t NotA = 0xfefefefefefefefe;
static const uint64_t NotH = 0x7f7f7f7f7f7f7f7f;
static const uint64_t F1G1 = 0x0000000000000060;
static const uint64_t C1D1 = 0x000000000000000c;
static const uint64_t B1C1D1 = 0x000000000000000e;
static const uint64_t F8G8 = 0x6000000000000000;
static const uint64_t C8D8 = 0x0c00000000000000;
static const uint64_t B8C8D8 = 0x0e00000000000000;

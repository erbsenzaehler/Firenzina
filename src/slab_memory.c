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

#include "fire.h"


void *FromSlab(uint64_t sz)
    {
    void *A;
    uint64_t pageset = ((uint64_t)(CurrentSlabLoc)) & 0xfff;
    if (sz >= 0x1000 && pageset & 0xfff)
        CurrentSlabLoc += (0x1000 - pageset);
    A = CurrentSlabLoc;
    if (sz & 0x3f)
        sz = sz + (0x40 - (sz & 0x3f));
    CurrentSlabLoc += sz;
    if (CurrentSlabLoc - SlabRootLoc > CurrentSlabSize)
        {
        CurrentSlabLoc -= sz;
        Send("FromSlab %d failed\n", (int)(sz));
        return NULL;
        }
    return A;
    }
void DeleteSlab()
    {
    FreeMem(SlabRootLoc, &SlabNumber, &LargeSlab);
    }

void InitSlab(int mb)
    {
    FillSlab();
    }

static void FillSlab()
    {
    SlabAlloc1(uint64_t, AttN, 64);
    SlabAlloc1(uint64_t, AttK, 64);
    SlabAlloc1(uint64_t, AttPw, 64);
    SlabAlloc1(uint64_t, AttPb, 64);
    SlabAlloc1(typeMM, RookMM, 64);
    SlabAlloc1(typeMM, BishopMM, 64);
    SlabAlloc2(uint64_t, MMOrtho, 102400);
    SlabAlloc2(uint64_t, MMDiag, 5248);
    SlabAlloc1(uint64_t, SqSet, 64);
    SlabAlloc1(uint64_t, SqClear, 64);
    SlabAlloc1(uint64_t, NonDiag, 64);
    SlabAlloc1(uint64_t, NonOrtho, 64);
    SlabAlloc1(uint64_t, Ortho, 64);
    SlabAlloc1(uint64_t, Diag, 64);
    SlabAlloc1(uint64_t, OrthoDiag, 64);
    SlabAlloc1(uint64_t, OpenFileW, 64);
    SlabAlloc1(uint64_t, OpenFileB, 64);
    SlabAlloc1(uint64_t, PassedPawnW, 64);
    SlabAlloc1(uint64_t, PassedPawnB, 64);
    SlabAlloc1(uint64_t, ProtectedPawnW, 64);
    SlabAlloc1(uint64_t, ProtectedPawnB, 64);
    SlabAlloc1(uint64_t, IsolatedPawnW, 64);
    SlabAlloc1(uint64_t, IsolatedPawnB, 64);
    SlabAlloc1(uint64_t, ConnectedPawns, 64);
    SlabAlloc1(uint64_t, InFrontW, 8);
    SlabAlloc1(uint64_t, NotInFrontW, 8);
    SlabAlloc1(uint64_t, InFrontB, 8);
    SlabAlloc1(uint64_t, NotInFrontB, 8);
    SlabAlloc1(uint64_t, IsolatedFiles, 8);
    SlabAlloc1(uint64_t, FilesLeft, 8);
    SlabAlloc1(uint64_t, FilesRight, 8);
    SlabAlloc1(uint64_t, Doubled, 64);
    SlabAlloc1(uint64_t, Left2, 64);
    SlabAlloc1(uint64_t, Right2, 64);
    SlabAlloc1(uint64_t, Left1, 64);
    SlabAlloc1(uint64_t, Right1, 64);
    SlabAlloc1(uint64_t, Adjacent, 64);
    SlabAlloc1(uint64_t, LongDiag, 64);
    SlabAlloc1(uint64_t, Northwest, 64);
    SlabAlloc1(uint64_t, Southwest, 64);
    SlabAlloc1(uint64_t, Northeast, 64);
    SlabAlloc1(uint64_t, Souteast, 64);
    SlabAlloc1(uint64_t, QuadrantWKwtm, 64);
    SlabAlloc1(uint64_t, QuadrantBKwtm, 64);
    SlabAlloc1(uint64_t, QuadrantWKbtm, 64);
    SlabAlloc1(uint64_t, QuadrantBKbtm, 64);
    SlabAlloc1(uint64_t, ShepherdWK, 64);
    SlabAlloc1(uint64_t, ShepherdBK, 64);
    SlabAlloc3(uint64_t, Interpose, 0100 * 0100);
    SlabAlloc3(uint64_t, Evade, 0100 * 0100);
    SlabAlloc3(uint64_t, Zobrist, 0x10 * 0100);
    SlabAlloc3(int8_t, Line, 0100 * 0100);
    SlabAlloc1(uint64_t, HashCastling, 16);
    SlabAlloc1(uint64_t, HashEP, 8);
    SlabAlloc1(uint64_t, HashRev, 16);
    SlabAlloc2(int16_t, MaxPositionalGain, 0x10 * 010000);
    SlabAlloc2(uint16_t, History, 0x10 * 0100);
    SlabAlloc2(int32_t, PieceSquareValue, 0x10 * 0100);
    SlabAlloc2(typeMaterial, Material, 419904);
    ResetHistory();
    ResetPositionalGain();
    InitArrays();
    InitMaterialValue();
    InitStatic();
    }

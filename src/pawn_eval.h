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

#define WhiteKingPawnDistance(pawn, king)                             \
  MAX (((king > pawn) ? 3 : 6) * ABS (Rank (pawn) - Rank (king)), \
		6 * ABS (File (pawn) - File (king)))
#define BlackKingPawnDistance(pawn, king)                             \
  MAX (((king < pawn) ? 3 : 6) * ABS (Rank (pawn) - Rank (king)), \
		6 * ABS (File (pawn) - File (king)))

#define Islands Score(0, 3)
#define Hole Score(1, 2)
#define DoubledClosed Score(2, 4)
#define DoubledOpen Score(4, 8)
#define DoubledClosedIsolated Score(2, 4)
#define DoubledOpenIsolated Score(6, 10)
#define IsolatedClosed Score(5, 8)
#define IsolatedOpen Score(15, 20)
#define BackwardClosed Score(5, 5)
#define BackwardOpen Score(10, 15)
#define Chain Score(1, 2)
#define KingAttPawn Score(0, 5)
#define KingOO Score(5, 0)
#define KingOOO Score(5, 0)

typedef struct
	{
	uint64_t Edge, Middle, Center;
	uint8_t ShelterEdge[8], ShelterMiddle[8], ShelterCenter[8];
	uint8_t StormEdge[8], StormMiddle[8], StormCenter[8], ShelterDiag[8], Zero, ValueZero;
	} typePawnPtr;
typePawnPtr PawnPtr[8];

static const uint8_t ShelterAA[8] =
	{
	30, 0, 5, 15, 20, 25, 25, 25
	};
static const uint8_t ShelterAB[8] =
	{
	55, 0, 15, 40, 50, 55, 55, 55
	};
static const uint8_t ShelterAC[8] =
	{
	30, 0, 10, 20, 25, 30, 30, 30
    };
static const uint8_t StormAA[8] =
    {
    5, 0, 35, 15, 5, 0, 0, 0
    };
static const uint8_t StormAB[8] =
    {
    10, 0, 50, 20, 10, 0, 0, 0
    };
static const uint8_t StormAC[8] =
    {
    10, 0, 50, 20, 10, 0, 0, 0
    };
static const uint8_t ShelterBA[8] =
    {
    30, 0, 5, 15, 20, 25, 25, 25
    };
static const uint8_t ShelterBB[8] =
    {
    55, 0, 15, 40, 50, 55, 55, 55
    };
static const uint8_t ShelterBC[8] =
    {
    30, 0, 10, 20, 25, 30, 30, 30
    };
static const uint8_t StormBA[8] =
    {
    5, 0, 35, 15, 5, 0, 0, 0
    };
static const uint8_t StormBB[8] =
    {
    10, 0, 50, 20, 10, 0, 0, 0
    };
static const uint8_t StormBC[8] =
    {
    10, 0, 50, 20, 10, 0, 0, 0
    };
static const uint8_t ShelterCB[8] =
    {
    30, 0, 5, 15, 20, 25, 25, 25
    };
static const uint8_t ShelterCC[8] =
    {
    55, 0, 15, 40, 50, 55, 55, 55
    };
static const uint8_t ShelterCD[8] =
    {
    30, 0, 10, 20, 25, 30, 30, 30
    };
static const uint8_t StormCB[8] =
    {
    5, 0, 35, 15, 5, 0, 0, 0
    };
static const uint8_t StormCC[8] =
    {
    10, 0, 50, 20, 10, 0, 0, 0
    };
static const uint8_t StormCD[8] =
    {
    10, 0, 50, 20, 10, 0, 0, 0
    };
static const uint8_t ShelterDC[8] =
    {
    30, 0, 5, 15, 20, 25, 25, 25
    };
static const uint8_t ShelterDD[8] =
    {
    55, 0, 15, 40, 50, 55, 55, 55
    };
static const uint8_t ShelterDE[8] =
    {
    30, 0, 10, 20, 25, 30, 30, 30
    };
static const uint8_t StormDC[8] =
    {
    5, 0, 35, 15, 5, 0, 0, 0
    };
static const uint8_t StormDD[8] =
    {
    10, 0, 50, 20, 10, 0, 0, 0
    };
static const uint8_t StormDE[8] =
    {
    10, 0, 50, 20, 10, 0, 0, 0
    };
static const uint8_t ShelterLongDiagA[8] =
    {
    10, 0, 2, 4, 6, 8, 10, 10
    };
static const uint8_t ShelterLongDiagB[8] =
    {
    8, 0, 2, 4, 6, 7, 8, 8
    };
static const uint8_t ShelterLongDiagC[8] =
    {
    6, 0, 2, 3, 4, 5, 6, 6
    };
static const uint8_t ShelterLongDiagD[8] =
    {
    4, 0, 1, 2, 3, 4, 4, 4
    };
static const uint8_t OpposingPawnsMult[9] =
	{
	6, 5, 4, 3, 2, 1, 0, 0, 0
	};
static const uint8_t PawnCountMult[9] =
	{
	6, 5, 4, 3, 2, 1, 0, 0, 0
	};
static const uint8_t BlockedPawnValue[64] =
    {
	0, 0, 0, 0, 0, 0, 0, 0,
	1, 1, 2, 2, 2, 2, 1, 1,
	1, 2, 3, 3, 3, 3, 2, 1,
	1, 2, 3, 5, 5, 3, 2, 1,
	1, 2, 3, 5, 5, 3, 2, 1,
	1, 2, 3, 3, 3, 3, 2, 1,
	1, 1, 2, 2, 2, 2, 1, 1,
	0, 0, 0, 0, 0, 0, 0, 0

    };
static const int32_t MyKingPawnDistance[8] =
    {
    0, 0, 0, 1, 2, 3, 5, 0
    };
static const int32_t OppKingPawnDistance[8] =
    {
    0, 0, 0, 2, 4, 6, 10, 0
    };
static const int32_t PassedPawnValue[8] =
    {
    Score(0, 0), Score(0, 0), Score(0, 0), Score(10, 10),
	Score(20, 25), Score(40, 50), Score(60, 75), Score(0, 0)
    };
static const int32_t OutsidePassedPawnValue[8] =
    {
    Score(0, 0), Score(0, 0), Score(0, 0), Score(0, 0),
	Score(2, 5), Score(5, 10), Score(10, 20), Score(0, 0)
    };
static const int32_t ProtectedPassedPawnValue[8] =
    {
    Score(0, 0), Score(0, 0), Score(0, 0), Score(0, 0),
	Score(5, 10), Score(10, 15), Score(15, 25), Score(0, 0)
    };
static const int32_t ConnectedPassedPawnValue[8] =
    {
    Score(0, 0), Score(0, 0), Score(0, 0), Score(0, 0),
	Score(5, 10), Score(10, 15), Score(20, 30), Score(0, 0)
    };
static const int32_t CandidatePawnValue[8] =
    {
    Score(0, 0), Score(0, 0), Score(0, 0), Score(5, 5),
	Score(10, 12), Score(20, 25), Score(0, 0), Score(0, 0)
    };


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

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

static const char *Engine = "Firenzina";
static const char *Vers = "2.4.4 dev xTreme";
static const char *Author = "N. Schmidt, D. Gusev and M. Brades";

#define STDIN_FileNO 0

#define SlabDeclare1(Type, v, c) Type v[c]
#define SlabAlloc1(Type, v, c)
#define SlabDeclare2(Type, v, c) Type v[c]
#define SlabAlloc2(Type, v, c)
#define SlabDeclare3 SlabDeclare1
#define SlabAlloc3 SlabAlloc1

//*******************************************************************************//
// Define default settings here (comment by Yuri Censor for Firenzina, 3/25/2013)//
//*******************************************************************************//
// System
#define MaxCPUs 16
#define RPperCPU 8
#define MaxSP 16 // It looks like this number must match MaxCPUs. Yuri Censor, 12/15/2013
#define DEFAULT_HASH_SIZE 128
#define MAX_HASH_SIZE 65536
#define DEFAULT_PAWN_HASH_SIZE 32
#define MAX_PAWN_HASH_SIZE 1024
#define DEFAULT_MULTIPV 1
#define MAX_MULTIPV 250
#define DEFAULT_MIN_PV_DEPTH 15

// Split Depths
#define MIN_AN_SPLIT_DEPTH 8             // Original: 12
#define DEFAULT_AN_SPLIT_DEPTH 12        // Original: 12; Conservative: 12; Aggressive: 14
#define MAX_AN_SPLIT_DEPTH 24
#define MIN_CN_SPLIT_DEPTH 8             // Original: 12
#define DEFAULT_CN_SPLIT_DEPTH 14        // Original: 14; Conservative: 14; Aggressive: 16
#define MAX_CN_SPLIT_DEPTH 24
#define MIN_PV_SPLIT_DEPTH 8             // Original: 12
#define DEFAULT_PV_SPLIT_DEPTH 12        // Original: 12
#define MAX_PV_SPLIT_DEPTH 24

// Time Management
#define DEFAULT_ABSOLUTE_FACTOR 25       // Original: 25; Conservative: 25; Aggressive: 30
#define MAX_ABSOLUTE_FACTOR 100
#define DEFAULT_BATTLE_FACTOR   100      // Original: 100; Conservative: 95; Aggressive: 75
#define MAX_BATTLE_FACTOR 200
#define DEFAULT_DESIRED_MILLIS 40
#define MAX_DESIRED_MILLIS 80
#define DEFAULT_EASY_FACTOR 15           // Original: 15; Conservative: 15; Aggressive: 20
#define MAX_EASY_FACTOR 100
#define DEFAULT_EASY_FACTOR_PONDER 33    // Original: 33
#define MAX_EASY_FACTOR_PONDER 100
#define DEFAULT_NORMAL_FACTOR 75         // Original: 75; Conservative: 80; Aggressive: 50
#define MAX_NORMAL_FACTOR 200

#include "linux.h"
#include "hash.h"

int NumCPUs;
uint64_t NodeCheck;
#define ZobRev(Pos) (0ULL)
#define CheckHalt() { if (Position->stop) { return(0); } }
#define Height(x)((x)->height)
#define Is_Exact(x) (x)
#define prefetch(x) __builtin_prefetch((char*)(x))
#include "move.h"
bool BoardIsOk, isNewGame;

#define CheckRepetition(in_check)                                             \
	CheckHalt ();                                                              \
	if (in_check && Position->Dyn->reversible == 100) return Move50 (Position); \
	if (Position->Dyn->reversible >= 100) return(0);                           \
	for (i = 4; i <= Position->Dyn->reversible &&                               \
		i <= Position->StackHeight; i += 2)                                  \
	if (Position->Stack[Position->StackHeight - i] ==                         \
		(Position->Dyn->Hash ^ ZobRev (Position))) return(0);

typedef struct
    {
    uint64_t Hash, PawnHash;
    uint32_t material;
    int32_t Static;
    uint8_t age, _9, wKdanger, bKdanger;
    uint8_t oo, reversible, ep, cp;
    uint64_t wAtt, bAtt, wXray, bXray;
    int32_t Value, PositionalValue;
    uint16_t _5, _6, killer1, killer2, move;
    uint8_t _0, _3, exact, lazy, SavedFlags, flags;
    uint64_t wKcheck, bKcheck, _1, _2, _8;
    } typeDynamic;

#include "SMP.h"
#include "board.h"
#include "slab_memory.h"

#define MAX(x, y) (((x) >= (y)) ? (x) : (y))
#define MIN(x, y) (((x) <= (y)) ? (x) : (y))
#define ABS(x) (((x) >= 0) ? (x) : -(x))
#define FileDistance(x, y) (ABS(File(x) - File(y)))
#define RankDistance(x, y) (ABS(Rank(x) - Rank(y)))

#define Score(x,y) (((x) << 16) + (y))
#define ValueMate 30000
#define ValueInfinity 32750
#define MultiCentiPawnPV 65535
#define RandomCount 0
#define RandomBits 1

#define MaxDepth 256

#define ScoreReduction(x)(((uint32_t) (MIN ((x), 96))) >> 5)
#define KingDangerAdjust(wK, bK) (0)

#define BitClear(b, B) B &= (B - 1)
#define BitSet(b, B) B |=((uint64_t) 1) << (b)

// System
volatile bool DoPonder;
volatile bool Ponder_Hit;
volatile bool DoInfinite;
volatile bool SuppressInput;
volatile bool Stop;
volatile bool UCINewGame;

bool BenchMarking;
bool Ponder;
bool DoOutput;
bool StallInput;
bool NoSupport;

int MultiPV;
int RandRange;

// Eval Weights
int DrawWeight;
int KingSafetyWeight;
int MaterialWeight;
int MobilityWeight;
int PawnWeight;
int PositionalWeight;
int PSTWeight;

// Lazy Eval
int LazyEvalMin;
int LazyEvalMax;

//Piece Values
int PValue;
int NValue;
int BValue;
int RValue;
int QValue;
int BPValue;

// Pruning Thresholds
int PrunePawn;
int PruneMinor;
int PruneRook;
int PruneCheck;

//Search Vars
int AspirationWindow;
int CountLimit;
bool ExtendInCheck;
int ValueCut;
int NullReduction;
int VerifyReduction;
bool  VerifyNull;
int DeltaCutoff;
int DepthRedMin;
int HeightMultiplier;
int HistoryThreshold;
int LowDepthMargin;
int MinDepthMultiplier;
int MinTransMoveDepth;
int QSAlphaThreshold;
int SearchDepthMin;
int SearchDepthReduction;
int SEECutOff;
int SEELimit;

int TopMinDepth;
int UndoCountThreshold;

//Split Depths
bool  SplitAtCN;
int ANSplitDepth;
int CNSplitDepth;
int PVSplitDepth;
bool  SlitDepth;

//Time Management
int AbsoluteFactor;
int BattleFactor;
int DesiredMillis;
int EasyFactor;
int EasyFactorPonder;
int NormalFactor;

//UCI Info Strings
bool CurrMoveInfo;
bool DepthInfo;
bool LowDepthPVs;
bool NPSInfo;
bool VerboseUCI;
int MinPVDepth;

#define CheckForMate(v) \
	{ \
	if (v < -ValueMate + 64) return (-ValueMate + 64); \
	if (v > ValueMate - 64) return (ValueMate - 64); \
	} \

#include "arrays.h"
#include "functions.h"

///Content of former common.h
#define TempoValue (4 + ((Position->Dyn->material & 0xff) >> 2))
#define TempoValue2 (4 + ((Position->Dyn->material & 0xff) >> 2))
#define EVAL(m, dp) Eval (Position, -0x7fff0000, 0x7fff0000, m, dp)
#define EvalLazy(B, A, p, m) Eval (Position, (B) - (p), (A) + (p), m, depth)
#define EvalQsearch(v, m) EvalLazy ((v), (v), LazyEvalMin, (m))
#define EvalLowDepth(v, m) EvalLazy ((v), (v), LazyEvalMin, (m))
#define EvalCutAll(v, m) EvalLazy ((v), (v), LazyEvalMax, (m))
#define MaxPositional(m) MaxPosGain (Position->sq[From (m)], (m) & 07777)
#define IsRepetition(x)                                  \
  (value > x && Pos0->reversible >= 2 &&                 \
   ((To(move) << 6) | From(move)) == (Pos0 - 1)->move && \
  Position->sq[To(move)] == 0)
#define IsInterpose(x) (x & (1 << 15))
#define EasySEE(x) (x & 0x300000)
#define PassedPawnPush(to, x) \
  (Position->sq[to] == EnumMyP && x && (BitboardOppP & IsPassedPawn[to]) == 0)
#define PieceIsWhite(pi) (pi <= 7)
#define PieceIsBlack(pi) (pi >= 8)
#define QSearchCondition (new_depth <= 1)
#define LowDepthCondition (new_depth <= 9)
#define LowDepthConditionPV (new_depth <= 9)
///End of common.h

char String1[MaxCPUs][64], String2[MaxCPUs][64];
char String3[MaxCPUs][64], String4[MaxCPUs][64];
char *InputBuffer, *input_ptr;

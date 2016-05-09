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

void ResetPositionalGain()
    {
    int p, m;

	for (p = 0; p < 0x10; p++)
		for (m = 0; m < 010000; m++)
			MaxPosGain(p, m) = 0;
    }

void ResetHistory()
    {
    int pi, sq;

	for (pi = 0; pi < 0x10; pi++)
		for (sq = A1; sq <= H8; sq++)
			HistoryPITo(Position, pi, sq) = 0x800;
    }

void InitHashTables()
    {
    PVHashTable = NULL;
    EvalHash = NULL;
    PawnHash = NULL;
    CurrentPHashSize = (1 << 16);
    EvalHashSize = (1 << 15);
	CurrentHashSize = DEFAULT_HASH_SIZE;
	CurrentPHashSize = DEFAULT_PAWN_HASH_SIZE;
    }

void InitRootPosition()
    {
    memset((void *)RootPosition0, 0, sizeof(typePos));
    RootPosition0->DynRoot = malloc(MaxPly * sizeof(typeDynamic));
    RootPosition0->Dyn = RootPosition0->DynRoot + 1;
    RootPosition0->stop = false;
    }

void InitGlobals()
    {
// Eval Weights
    DrawWeight = 128;
    KingSafetyWeight = 128;
    MaterialWeight = 128;
    MobilityWeight = 128;
    PawnWeight = 128;
	PositionalWeight = 128;
    PSTWeight = 128;

// Lazy Eval
	LazyEvalMin = 150;
	LazyEvalMax = 300;

// Piece Values
	PValue  = 100;
	NValue  = 300;
	BValue  = 310;
	RValue  = 500;
	QValue  = 950;
	BPValue =  45;

// Prune Thresholds
	PruneCheck =  10;
	PrunePawn  = 160;
	PruneMinor = 500;
	PruneRook  = 800;

// Search Vars
	AspirationWindow     =     6;
	CountLimit           =     5;
	DeltaCutoff          = 25000;
	DepthRedMin          =    12;
	ExtendInCheck        = false;
	HeightMultiplier     =    64;
	HistoryThreshold     =    50;
	LowDepthMargin       =  1125;
	MinDepthMultiplier   =    48;
	MinTransMoveDepth    =    16;
	NullReduction        =     8;
	QSAlphaThreshold     =   200;
	SearchDepthMin       =    20;
	SearchDepthReduction =     6;
	SEECutOff            =   120;
	SEELimit             =  6174;
	TopMinDepth          =    14;
	UndoCountThreshold   =    15;
	ValueCut             = 15000;
	VerifyNull           = true;
	VerifyReduction      =     2;

// Split Depths
	SplitAtCN = true;
	ANSplitDepth = DEFAULT_AN_SPLIT_DEPTH;
	CNSplitDepth = DEFAULT_CN_SPLIT_DEPTH;
	PVSplitDepth = DEFAULT_PV_SPLIT_DEPTH;

// Time Management
	AbsoluteFactor = DEFAULT_ABSOLUTE_FACTOR;
	BattleFactor = DEFAULT_BATTLE_FACTOR;
	EasyFactor = DEFAULT_EASY_FACTOR;
	EasyFactorPonder = DEFAULT_EASY_FACTOR_PONDER;
	NormalFactor = DEFAULT_NORMAL_FACTOR;
	DesiredMillis = DEFAULT_DESIRED_MILLIS;

//UCI Info Strings
	CurrMoveInfo = false;
	DepthInfo = false;
	LowDepthPVs = false;
	NPSInfo = false;
	VerboseUCI = false;
	MinPVDepth = DEFAULT_MIN_PV_DEPTH;

//Miscellaneous


	BenchMarking = false;
    InfiniteLoop = false;
    MultiPV = DEFAULT_MULTIPV;
    Threads = 1;
    Ponder = false;
	RandRange = 0;
    SearchIsDone = true;
    SMPisActive = false;
    StallMode = false;
    StallInput = false;
    SuppressInput = false;
	UCINewGame = false;
    }

int main()
    {
	InitHashTables();
	InitRootPosition();
	InitGlobals();
    RPInit();
    InitHash(CurrentHashSize);
    InitCaptureValues();
    InitPawns();
    NewGame(RootPosition0, true);
    InputBuffer = malloc(65536);
    input_ptr = InputBuffer;
	InitSMP();
    while (1)
        Input(RootPosition0);
    return 0;
    }

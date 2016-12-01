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
void NanoSleep(int);
int InitPawnHash(int);
int InitPawnHashWrapper(int);
void InitArrays();
void InitCaptureValues();
void InitSlab(int);
void CreateMem(void **, int, uint64_t, int *, bool *, char *);
void FreeMem(void *, int *, bool *);
uint64_t GetRand();
void HaltSearch(int, int);
void CheckDone(typePos*, int);
void InitSearch(typePos*, char*);
void Info(int64_t);
void Eval(typePos*, int, int, int, int);
void Mobility(typePos*);
void EvalHashClear();
int InitEvalHash(int);
int EvalEnding(typePos * Position, int Value, uint64_t wPatt, uint64_t bPatt);
void SetValueArray();
void InitRandom32(uint64_t);

typeMoveList* CaptureMoves(typePos*, typeMoveList*, uint64_t);
typeMoveList* OrdinaryMoves(typePos*, typeMoveList*);
typeMoveList* EvasionMoves(typePos*, typeMoveList*, uint64_t);
void InitCaptureValues();
typeMoveList* WhiteCaptures(typePos*, typeMoveList*, uint64_t);
typeMoveList* BlackCaptures(typePos*, typeMoveList*, uint64_t);
typeMoveList* WhiteOrdinary(typePos*, typeMoveList*);
typeMoveList* BlackOrdinary(typePos*, typeMoveList*);
void SortOrdinary(typeMoveList*, typeMoveList*, uint32_t, uint32_t, uint32_t);
typeMoveList* QuietChecksWhite(typePos*, typeMoveList*, uint64_t);
typeMoveList* QuietChecksBlack(typePos*, typeMoveList*, uint64_t);
typeMoveList* PositionalMovesWhite(typePos*, typeMoveList*, int);
typeMoveList* PositionalMovesBlack(typePos*, typeMoveList*, int);
typeMoveList* BlackEvasions(typePos*, typeMoveList*, uint64_t);
typeMoveList* WhiteEvasions(typePos*, typeMoveList*, uint64_t);
void IncrementAge();
void HashClear();
int HashClearAll();
int InitHash(int);
void HashLowerAllNew(uint64_t, int, int, int, int, int);
void HashUpperCutNew(uint64_t, int, int, int, int);
void HashLowerNew(uint64_t, int, int, int, int, int, int);
void HashUpperNew(uint64_t, int, int, int, int, int);
void HashExactNew(uint64_t, int, int, int, int, int, int);
int InitPVHash(int);
int PVHashClear();
void Input(typePos*);
void ResetHistory();
void ResetPositionalGain();

void Make(typePos*, uint32_t);
void Undo(typePos*, uint32_t);
void MakeWhite(typePos*, uint32_t);
void UndoWhite(typePos*, uint32_t);
void MakeBlack(typePos*, uint32_t);
void UndoBlack(typePos*, uint32_t);

int InitMaterialValue();
uint32_t NextWhite(typePos*, typeNext*);
uint32_t NextBlack(typePos*, typeNext*);
bool WhiteOK(typePos*, uint32_t);
bool BlackOK(typePos*, uint32_t);
void InitPawns();
void PawnEval(typePos*, typePawnEval*);
int Move50(typePos*);

int PVQsearchWhite(typePos*, int, int, int);
int PVQsearchWhiteCheck(typePos*, int, int, int);
int PVQsearchBlack(typePos*, int, int, int);
int PVQsearchBlackCheck(typePos*, int, int, int);
void TopWhite(typePos*);
void TopBlack(typePos*);
int RootWhite(typePos*, int, int, int);
int RootBlack(typePos*, int, int, int);
int PVNodeWhite(typePos*, int, int, int, int);
int PVNodeBlack(typePos*, int, int, int, int);
int ExcludeWhite(typePos*, int, int, uint32_t);
int ExcludeWhiteCheck(typePos*, int, int, uint32_t);
int ExcludeBlack(typePos*, int, int, uint32_t);
int ExcludeBlackCheck(typePos*, int, int, uint32_t);
int CutNodeWhite(typePos*, int, int);
int CutNodeBlack(typePos*, int, int);
int CutNodeWhiteCheck(typePos*, int, int);
int CutNodeBlackCheck(typePos*, int, int);
int AllNodeWhite(typePos*, int, int);
int AllNodeBlack(typePos*, int, int);
int AllNodeWhiteCheck(typePos*, int, int);
int AllNodeBlackCheck(typePos*, int, int);
int LowDepthWhite(typePos*, int, int);
int LowDepthBlack(typePos*, int, int);
int LowDepthWhiteCheck(typePos*, int, int);
int LowDepthBlackCheck(typePos*, int, int);
int QsearchWhite(typePos*, int, int);
int QsearchBlack(typePos*, int, int);
int QsearchWhiteCheck(typePos*, int, int);
int QsearchBlackCheck(typePos*, int, int);
static void OutputBestMove();
void Search(typePos *);
void Information(typePos *, int64_t, int, int, int);
int WhiteAnalysis(typePos*, int, int, int);
int BlackAnalysis(typePos*, int, int, int);
bool WhiteSEE(typePos *, uint32_t);
bool BlackSEE(typePos *, uint32_t);
void InitPosition(typePos *, char *);
void InitStatic();
uint32_t FullMove(typePos *, uint32_t);
uint32_t NumericMove(typePos * , char *);
void ErrorEnd(char *, ...);
void ErrorFen(char *, ...);
void Send(char *, ...);
char *Notate(uint32_t, char *);
uint64_t GetClock();
uint64_t ProcessClock();
void InitBitboards(typePos *);
void NewGame(typePos *, bool);
bool TryInput();
bool SMPSplit(typePos*, typeNext *, int, int, int, int, int *);
void FailHigh(SplitPoint*, typePos *, uint32_t);
//void FailHigh(SplitPoint* sp, typePos* Position, uint32_t m);

void SMPStub();
void ThreadHalt(typePos*);
void ThreadStall(typePos*, int);
void WhitePVNodeSMP(typePos*);
void BlackPVNodeSMP(typePos*);
void WhiteAllSMP(typePos*);
void BlackAllSMP(typePos*);
void WhiteCutSMP(typePos*);
void BlackCutSMP(typePos*);
int InitSMP();
void EndSMP();
void RPInit();
int PawnHashReset();
void PonderHit();
void WhiteTopAnalysis(typePos*);
void BlackTopAnalysis(typePos*);
int WhiteMultiPV(typePos *, int);
int BlackMultiPV(typePos *, int);
char *EmitFen(typePos *, char *);
int Stat(char *);
void QuitLargePawns();
void QuitPV();
void DetachAllMemory();
void QuitEvalHash();
void MagicMultInit();
static void FillSlab();
void BenchMark(typePos*, char*);

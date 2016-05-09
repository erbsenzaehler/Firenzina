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
#include "control.h"

#define Infinity 0x7ffffffffffffff
#define StrTok(p) p = strtok (NULL, " ")

static int64_t LastMessage;
static int64_t AbsoluteTime, DesiredTime, Increment;
static int Depth;
static bool NewPonderhit;
jmp_buf J;
static int64_t BattleTime, EasyTime, NormalTime;

void PonderHit()
    {
    if (!DoPonder)
        return;
    Ponder_Hit = true;
    DoPonder = false;
    NewPonderhit = true;
    AbsoluteTime += GetClock() - StartClock;
    }
void HaltSearch(int d, int rank)
    {
    Stop = true;
    DoPonder = false;
    DoInfinite = false;
    SuppressInput = true;
        SMPAllHalt = true;
        if (d == 0)
            EndSMP();
    }
void Info(int64_t x)
    {
    uint64_t t, nps, Nodes = 0;
	int cpu, rp;
    clock_t u;

    if (x < 0)
        return;
	DoOutput = true;

    for (cpu = 0; cpu < Threads; cpu++)
        for (rp = 0; rp < RPperCPU; rp++)
            Nodes += RootPosition[cpu][rp].nodes;

    u = clock();
    t = x / 1000;

    if (t == 0)
        nps = 0;
    else
        nps = Nodes / t;
    u = ProcessClock() - CPUtime;

	if (NPSInfo)
		Send("info time %lld nodes %lld nps %lld\n", t, Nodes, nps * 1000);

    LastMessage = x;
    CPUtime += u;
    }

void CheckDone(typePos * Position, int d)
    {
    int64_t x;
    if (!RootBestMove)
        return;
    if (SMPAllHalt)
        {
        HaltSearch(d, 1);
        return;
        }
    if (SuppressInput)
        return;
    if (!JumpIsSet)
        return;
    x = GetClock() - StartClock;
    if (d && d == Depth)
        {
        HaltSearch(d, 1);
        return;
        }
    if (!BenchMarking  && x - LastMessage > 1000000)
        Info(x);
    if (DoPonder)
        goto End;
    if (DoInfinite)
        goto End;
    if (d >= 1 && d < 8)
        goto End;
    if (x > AbsoluteTime)
        {
        HaltSearch(d, 1);
        return;
        }
    if (d == 0 && !NewPonderhit)
        goto End;
    NewPonderhit = false;

    if (!BadMove && x >= BattleTime)
        {
        HaltSearch(d, 2);
        return;
        }
    if (EasyMove && x >= EasyTime)
        {
        HaltSearch(d, 3);
        return;
        }
    if (!BattleMove && x >= NormalTime && !BadMove)
        {
        HaltSearch(d, 4);
        return;
        }
    End:
    if (d)
        return;


	if (!BenchMarking)
		{
		while (TryInput())
			{
			Input(Position);
			if (d == 0 && !SMPisActive)
				return;
			}
		}
	}
void TimeManager(int64_t Time, int64_t OppTime, int64_t Increment, int mtg)
    {
	if (mtg)
        {
        if (mtg > 25)
            mtg = 25;
        DesiredTime = Time / mtg + Increment;
        AbsoluteTime = (Time * mtg) / ((mtg << 2) - 3) - MIN(1000000, Time / 10);
        if (mtg == 1)
            AbsoluteTime -= MIN(1000000, AbsoluteTime / 10);
        if (AbsoluteTime < 1000)
            AbsoluteTime = 1000;
        }
    else
        {
        AbsoluteTime = (Time * AbsoluteFactor) / 100 - 10000;
        if (AbsoluteTime < 1000)
            AbsoluteTime = 1000;
        DesiredTime = (Time * DesiredMillis) / 1000 + Increment;
        }
    if (DesiredTime > AbsoluteTime)
        DesiredTime = AbsoluteTime;
    if (DesiredTime < 1000)
        DesiredTime = 1000;
    EasyTime = (DesiredTime * EasyFactor) / 100;
    if (Ponder)
        EasyTime = (DesiredTime * EasyFactorPonder) / 100;
    BattleTime = (DesiredTime * BattleFactor) / 100;
    NormalTime = (DesiredTime * NormalFactor) / 100;
    }

void InitSearch(typePos * Position, char *str)
    {
    char *p;
    int64_t wtime = Infinity, btime = Infinity, winc = 0, binc = 0, Time, OppTime, mtg = 0;
    int sm = 0;
    Depth = 255;
    AbsoluteTime = DesiredTime = Infinity;
    Stop = false;
    DoInfinite = false;
    DoPonder = false;
    NewPonderhit = false;
    DoSearchMoves = false;
    LastMessage = 0;
    p = strtok(str, " ");
    for (StrTok(p); p != NULL; StrTok(p))
        {
        if (!strcmp(p, "depth"))
            {
            StrTok(p);
            Depth = MAX(1, atoi(p));
            }
        else if (!strcmp(p, "movetime"))
            {
            StrTok(p);
            AbsoluteTime = MAX(1, atoll(p)) * 1000;
            }
        else if (!strcmp(p, "wtime"))
            {
            StrTok(p);
            wtime = atoll(p) * 1000;
            }
        else if (!strcmp(p, "winc"))
            {
            StrTok(p);
            winc = atoll(p) * 1000;
            }
        else if (!strcmp(p, "btime"))
            {
            StrTok(p);
            btime = atoll(p) * 1000;
            }
        else if (!strcmp(p, "binc"))
            {
            StrTok(p);
            binc = atoll(p) * 1000;
            }
        else if (!strcmp(p, "movestogo"))
            {
            StrTok(p);
            mtg = atoi(p);
            }
        else if (!strcmp(p, "infinite"))
            DoInfinite = true;
        else if (!strcmp(p, "ponder"))
            DoPonder = true;
        else if (!strcmp(p, "searchmoves"))
            DoSearchMoves = true;
        else if (DoSearchMoves)
            SearchMoves[sm++] = NumericMove(Position, p);
        else
            ErrorEnd("go string: %s", p);
        }
    BattleTime = Infinity;
    NormalTime = Infinity;
    EasyTime = Infinity;

    Time = Position->wtm ? wtime : btime;
    OppTime = Position->wtm ? btime : wtime;
    if (Time < 0)
        Time = 0;
    if (Time == Infinity)
        goto End;
    Increment = Position->wtm ? winc : binc;
        TimeManager(Time, OppTime, Increment, mtg);
    End:
    if (Time == Infinity)
        Analysing = true;
    else
        Analysing = false;
    if (DoSearchMoves)
        SearchMoves[sm] = MoveNone;
    }

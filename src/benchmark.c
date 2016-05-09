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
#include <time.h>


#define numPos 37
#define numCycles 1

static uint64_t TotalTime = 0;
static uint64_t TotalNodes = 0;

static int BestANSD = 0;
static int BestANNPS = 0;
static int BestCNSD = 0;
static int BestCNNPS = 0;
static int BestPVSD = 0;
static int BestPVNPS = 0;

char BenchmarkPos[numPos][128] =
	{
    // Positions from Stockfish
    "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1",
    "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 10",
    "8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - 0 11",
    "4rrk1/pp1n3p/3q2pQ/2p1pb2/2PP4/2P3N1/P2B2PP/4RRK1 b - - 7 19",
    "rq3rk1/ppp2ppp/1bnpb3/3N2B1/3NP3/7P/PPPQ1PP1/2KR3R w - - 7 14",
    "r1bq1r1k/1pp1n1pp/1p1p4/4p2Q/4Pp2/1BNP4/PPP2PPP/3R1RK1 w - - 2 14",
    "r3r1k1/2p2ppp/p1p1bn2/8/1q2P3/2NPQN2/PPP3PP/R4RK1 b - - 2 15",
    "r1bbk1nr/pp3p1p/2n5/1N4p1/2Np1B2/8/PPP2PPP/2KR1B1R w kq - 0 13",
    "r1bq1rk1/ppp1nppp/4n3/3p3Q/3P4/1BP1B3/PP1N2PP/R4RK1 w - - 1 16",
    "4r1k1/r1q2ppp/ppp2n2/4P3/5Rb1/1N1BQ3/PPP3PP/R5K1 w - - 1 17",
    "2rqkb1r/ppp2p2/2npb1p1/1N1Nn2p/2P1PP2/8/PP2B1PP/R1BQK2R b KQ - 0 11",
    "r1bq1r1k/b1p1npp1/p2p3p/1p6/3PP3/1B2NN2/PP3PPP/R2Q1RK1 w - - 1 16",
    "3r1rk1/p5pp/bpp1pp2/8/q1PP1P2/b3P3/P2NQRPP/1R2B1K1 b - - 6 22",
    "r1q2rk1/2p1bppp/2Pp4/p6b/Q1PNp3/4B3/PP1R1PPP/2K4R w - - 2 18",
    "4k2r/1pb2ppp/1p2p3/1R1p4/3P4/2r1PN2/P4PPP/1R4K1 b - - 3 22",
    "3q2k1/pb3p1p/4pbp1/2r5/PpN2N2/1P2P2P/5PP1/Q2R2K1 b - - 4 26",
    "6k1/6p1/6Pp/ppp5/3pn2P/1P3K2/1PP2P2/3N4 b - - 0 1",
    "3b4/5kp1/1p1p1p1p/pP1PpP1P/P1P1P3/3KN3/8/8 w - - 0 1",
    "2K5/p7/7P/5pR1/8/5k2/r7/8 w - - 0 1",
    "8/6pk/1p6/8/PP3p1p/5P2/4KP1q/3Q4 w - - 0 1",
    "7k/3p2pp/4q3/8/4Q3/5Kp1/P6b/8 w - - 0 1",
    "8/2p5/8/2kPKp1p/2p4P/2P5/3P4/8 w - - 0 1",
    "8/1p3pp1/7p/5P1P/2k3P1/8/2K2P2/8 w - - 0 1",
    "8/pp2r1k1/2p1p3/3pP2p/1P1P1P1P/P5KR/8/8 w - - 0 1",
    "8/3p4/p1bk3p/Pp6/1Kp1PpPp/2P2P1P/2P5/5B2 b - - 0 1",
    "5k2/7R/4P2p/5K2/p1r2P1p/8/8/8 b - - 0 1",
    "6k1/6p1/P6p/r1N5/5p2/7P/1b3PP1/4R1K1 w - - 0 1",
    "1r3k2/4q3/2Pp3b/3Bp3/2Q2p2/1p1P2P1/1P2KP2/3N4 w - - 0 1",
    "6k1/4pp1p/3p2p1/P1pPb3/R7/1r2P1PP/3B1P2/6K1 w - - 0 1",
    "8/3p3B/5p2/5P2/p7/PP5b/k7/6K1 w - - 0 1",

    // 5-man positions
    "8/8/8/8/5kp1/P7/8/1K1N4 w - - 0 1",     // Kc2 - mate
    "8/8/8/5N2/8/p7/8/2NK3k w - - 0 1",      // Na2 - mate
    "8/3k4/8/8/8/4B3/4KB2/2B5 w - - 0 1",    // draw

    // 6-man positions
    "8/8/1P6/5pr1/8/4R3/7k/2K5 w - - 0 1",   // Re5 - mate
    "8/2p4P/8/kr6/6R1/8/8/1K6 w - - 0 1",    // Ka2 - mate
    "8/8/3P3k/8/1p6/8/1P6/1K3n2 b - - 0 1",  // Nd2 - draw

    // 7-man positions
    "8/R7/2q5/8/6k1/8/1P5p/K6R w - - 0 124", // Draw
	};
void BenchMark(typePos* Position, char* GoString)
	{
	int i, j;
	char String[1024], GO_String[1024];
	int cpu, rp;
	uint64_t Nodes, C, Time;
	HashClearAll();
	BenchMarking = true;
	Send("%s\n\n", "benchmarking, please wait...");
	for (j = 0; j < numCycles; j++)
		{
	    for (i = 0; i < numPos; i++)
			{
	        Send("position %d\n", i + 1);
			sprintf(String, "%s %s\n", "fen", BenchmarkPos[i]);
			InitPosition(Position, String);
			strcpy(GO_String, GoString);
			InitSearch(Position, GO_String);
			C = GetClock();
			Search(Position);
			Time = GetClock() - C;
			Nodes = 0;
			for (cpu = 0; cpu < Threads; cpu++)
				for (rp = 0; rp < RPperCPU; rp++)
				Nodes += RootPosition[cpu][rp].nodes;
			Send("nodes: %lld\n", Nodes);
	        Send("time : %lld ms\n", Time / 1000);
			Send("NPS  : %lld kNPS\n\n", ((Nodes * 1000) / Time));
	        TotalNodes += Nodes;
			TotalTime += Time;
	        }
		HashClearAll();
		}
    Send("total nodes: %lld\n", TotalNodes);
    Send("total time : %lld ms\n", TotalTime / 1000);
    Send("total NPS  : %lld kNPS\n\n", ((TotalNodes * 1000) / TotalTime));
	BenchMarking = false;
	HashClearAll();
	InitPosition(Position, "startpos");
    }

void SDBenchMark(typePos* Position, char *GoString)
    {
    int i, j;
    char String[1024], GO_String[1024];
    int cpu, rp;
    uint64_t Nodes = 0, C, Time = 0;
    uint64_t TotalTime = 0, TotalNodes = 0, ThisNPS = 0;
	HashClearAll();
	BenchMarking = true;
	Send("benchmarking AN Split depths, please wait...\n");
    for (i = MIN_AN_SPLIT_DEPTH; i <= MAX_AN_SPLIT_DEPTH; i += 2)
        {
		ANSplitDepth = i;
		for (j = 0; j < numPos; j++)
			{
			sprintf(String, "%s %s\n", "fen", BenchmarkPos[j]);
			InitPosition(Position, String);
			strcpy(GO_String, GoString);
			InitSearch(Position, GO_String);
			C = GetClock();
			Search(Position);
			Time = GetClock() - C;
			Nodes = 0;
			for (cpu = 0; cpu < Threads; cpu++)
				for (rp = 0; rp < RPperCPU; rp++)
					Nodes += RootPosition[cpu][rp].nodes;
			TotalNodes += Nodes;
			TotalTime += Time;
			}
		Send("AN Split depth : %d\n", i);
		Send("average kNPS: %lld\n\n", ((TotalNodes * 1000) / TotalTime));
		ThisNPS = ((TotalNodes * 1000) / TotalTime);
		if (ThisNPS > BestANNPS)
			{
			BestANNPS = ThisNPS;
			BestANSD = i;
			}
		}
	ANSplitDepth = BestANSD;
    Send("fastest AN Split depth: %d\n\n", BestANSD);
	Send("benchmarking CN Split depths, please wait...\n\n");
    for (i = MIN_CN_SPLIT_DEPTH; i <= MAX_CN_SPLIT_DEPTH; i += 2)
        {
		CNSplitDepth = i;
		for (j = 0; j < numPos; j++)
			{
			sprintf(String, "%s %s\n", "fen", BenchmarkPos[j]);
			InitPosition(Position, String);
			strcpy(GO_String, GoString);
			InitSearch(Position, GO_String);
			C = GetClock();
			Search(Position);
			Time = GetClock() - C;
			Nodes = 0;
			for (cpu = 0; cpu < Threads; cpu++)
				for (rp = 0; rp < RPperCPU; rp++)
					Nodes += RootPosition[cpu][rp].nodes;
			TotalNodes += Nodes;
			TotalTime += Time;
			}
		Send("CN Split depth : %d\n", i);
		Send("average kNPS: %lld\n\n", ((TotalNodes * 1000) / TotalTime));
		ThisNPS = ((TotalNodes * 1000) / TotalTime);
		if (ThisNPS > BestCNNPS)
			{
			BestCNNPS = ThisNPS;
			BestCNSD = i;
			}
		}
	CNSplitDepth = BestCNSD;
    Send("fastest CN Split depth: %d\n\n", BestCNSD);
	Send("benchmarking PV Split depths, please wait...\n\n");
    for (i = MIN_PV_SPLIT_DEPTH; i <= MAX_PV_SPLIT_DEPTH; i += 2)
        {
		PVSplitDepth = i;
		for (j = 0; j < numPos; j++)
			{
			sprintf(String, "%s %s\n", "fen", BenchmarkPos[j]);
			InitPosition(Position, String);
			strcpy(GO_String, GoString);
			InitSearch(Position, GO_String);
			C = GetClock();
			Search(Position);
			Time = GetClock() - C;
			Nodes = 0;
			for (cpu = 0; cpu < Threads; cpu++)
				for (rp = 0; rp < RPperCPU; rp++)
					Nodes += RootPosition[cpu][rp].nodes;
			TotalNodes += Nodes;
			TotalTime += Time;
			}
		Send("PV Split depth : %d\n", i);
		Send("average kNPS: %lld\n\n", ((TotalNodes * 1000) / TotalTime));
		ThisNPS = ((TotalNodes * 1000) / TotalTime);
		if (ThisNPS > BestPVNPS)
			{
			BestPVNPS = ThisNPS;
			BestPVSD = i;
			}
		}
	PVSplitDepth = BestPVSD;
    Send("fastest PV Split depth: %d\n\n", BestPVSD);
	BenchMarking = false;
	HashClearAll();
	InitPosition(Position, "startpos");
    }

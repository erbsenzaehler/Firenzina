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

#define NodeTypePV 1
#define NodeTypeAll 2
#define NodeTypeCut 3

pthread_mutex_t PThreadCondMutex[MaxCPUs];
pthread_mutex_t Wakeup_Lock_IO[1];
pthread_mutex_t SMP[1];
pthread_cond_t PThreadCondWait[MaxCPUs];
pthread_cond_t Wakeup_IO[1];

bool volatile Die[MaxCPUs];
bool volatile SMPisActive;
bool volatile SMPAllHalt;
bool volatile IOAwake;
bool volatile InfiniteLoop;
bool volatile SearchIsDone;
bool volatile StallMode;
int volatile Threads;

typedef struct
    {
    int alpha;
    int beta;
    int depth;
    int node_type;
    int value;
    uint32_t move;
    uint32_t good_move;
    uint32_t childs;
    typeNext *MovePick;
    bool tot;
    bool active;
    pthread_mutex_t splock[1];
    } SplitPoint;
SplitPoint RootSP[MaxSP];
volatile uint64_t SMPFree;
#include <setjmp.h>


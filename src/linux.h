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

#include "bits.h"
#include <pthread.h>

#define Lock(x) pthread_mutex_lock (x)
#define UnLock(x) pthread_mutex_unlock (x)
#define Wait(x, y) pthread_cond_wait (x, y)
#define Signal(x) pthread_cond_signal (x)
#define WaitForLock(x, y) { Lock (&(y)); Wait (&(x), &(y)); UnLock (&(y)); }
#define SignalForLock(x, y) { Lock (&(y)); Signal (&(x)); UnLock (&(y)); }
#define LockInit(x) pthread_mutex_init ((x), NULL)
#define CondInit(x, y) \
 { pthread_cond_init (&(x), NULL); pthread_mutex_init (&(y), NULL); }
#define PThreadCreate(N, b, thr, d) pthread_create (N, NULL, thr, (void*) (d))
pthread_t PThread[MaxCPUs], PThreadIO;
#define SMPThread(A) void* SMPThread (void* A)
#define IOThread(A) void* io_thread (void* A)

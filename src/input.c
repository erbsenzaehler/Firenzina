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
#define MaxVar 8
#define NumSubClasses 8

static bool HasDeletion = false;
static pthread_mutex_t InputDelete[1];
static bool Init = false;
static bool QuitDemand = false;

static int UCIFen ()
	{
    Send("info string %s\n", EmitFen (RootPosition0, String1[0]));
	return true;
	}
typedef enum
    {
    UCISpin,
    UCICheck,
    UCIButton,
    UCIString,
    UCICombo,
    UCIIgnore
    } enumUCI;
typedef struct
    {
    char name[0x100];
    char sub_class[0x40];
    int type;
    int32_t min, max, def;
    void *var;
    int(*action)(int);
    } UCItype;

char Combo[1][MaxVar][16] =
    {
    { "Tic", "Tac", "Toe" }
    };
char TicTacToe[16];

char SubClassList[NumSubClasses][16] =
    {
	"System", "Info", "Other", "Search", "SMP", "Time"
    };
UCItype UCIOptions[256] =
    {
// System
    { "Hash", "System", UCISpin, 1, MAX_HASH_SIZE, DEFAULT_HASH_SIZE, &CurrentHashSize, &InitHash },
    { "Pawn_Hash", "System", UCISpin, 1, MAX_PAWN_HASH_SIZE, DEFAULT_PAWN_HASH_SIZE, &CurrentPHashSize, &InitPawnHashWrapper },
    { "Threads", "SMP", UCISpin, 1, MaxCPUs, 1, &Threads, &InitSMP },
    { "MultiPV", "System", UCISpin, 1, MAX_MULTIPV, DEFAULT_MULTIPV, &MultiPV, NULL },
// Split Depths
    { "AN_Split_Depth", "SMP", UCISpin, MIN_AN_SPLIT_DEPTH, MAX_AN_SPLIT_DEPTH, DEFAULT_AN_SPLIT_DEPTH, &ANSplitDepth, NULL },
    { "CN_Split_Depth", "SMP", UCISpin, MIN_CN_SPLIT_DEPTH, MAX_CN_SPLIT_DEPTH, DEFAULT_CN_SPLIT_DEPTH, &CNSplitDepth, NULL },
    { "PV_Split_Depth", "SMP", UCISpin, MIN_PV_SPLIT_DEPTH, MAX_PV_SPLIT_DEPTH, DEFAULT_PV_SPLIT_DEPTH, &PVSplitDepth, NULL },
// Time Management
    { "Absolute_Factor", "Time", UCISpin, 1, MAX_ABSOLUTE_FACTOR, DEFAULT_ABSOLUTE_FACTOR, &AbsoluteFactor, NULL },
    { "Battle_Factor", "Time", UCISpin, 1, MAX_BATTLE_FACTOR, DEFAULT_BATTLE_FACTOR, &BattleFactor, NULL },
    { "Desired_Millis ", "Time", UCISpin, 1, MAX_DESIRED_MILLIS, DEFAULT_DESIRED_MILLIS, &DesiredMillis, NULL },
    { "Easy_Factor", "Time", UCISpin, 1, MAX_EASY_FACTOR, DEFAULT_EASY_FACTOR, &EasyFactor, NULL },
    { "Easy_Factor_Ponder", "Time", UCISpin, 1, MAX_EASY_FACTOR_PONDER, DEFAULT_EASY_FACTOR_PONDER, &EasyFactorPonder, NULL },
    { "Normal_Factor", "Time", UCISpin, 1, MAX_NORMAL_FACTOR, DEFAULT_NORMAL_FACTOR, &NormalFactor, NULL},
//UCI Info Strings
    { "Current_Move_Info", "Info", UCICheck, 0, 0, false, &CurrMoveInfo, NULL },
    { "Depth_Info", "Info", UCICheck, 0, 0, false, &DepthInfo, NULL },
    { "Low_Depth_PVs", "Info", UCICheck, 0, 0, false, &LowDepthPVs, NULL },
    { "NPS_Info", "Info", UCICheck, 0, 0, false, &NPSInfo, NULL },
    { "Extend_In_Check", "Search", UCICheck, 0, 0, false, &ExtendInCheck, NULL },
    { "Ponder", "System", UCICheck, 0, 0, false, &Ponder, NULL },
    { "Split_at_CN", "SMP", UCICheck, 0, 0, true, &SplitAtCN, NULL },
    { "Verbose_UCI", "Info", UCICheck, 0, 0, false, &VerboseUCI, NULL },
    { "Verify_Null", "Search", UCICheck, 0, 0, true, &VerifyNull, NULL },
    { "Clear_Hash", "Other", UCIButton,  0, 0, 0, NULL, &HashClearAll },
    { "Get_FEN_String", "Other", UCIButton,  0, 0, 0, NULL, &UCIFen },
    { "", "", -1, 0, 0, false, NULL, NULL }
    };

static void uci()
    {
    UCItype *uci;
    char string[256];
    char *str;
    char TYPE[5][16] =
        {
		"spin", "check", "button", "string", "combo"
        };
	Send("id name %s %s\n", Engine, Vers);
    Send("id author %s\n", Author);

		for (uci = UCIOptions; uci->type != -1; uci++)
			{
			str = string;
			sprintf(str, "option name %s type %s", uci->name, TYPE[uci->type]);
			str += strlen(str);
			if (uci->type == UCICheck)
				sprintf(str, " default %s", uci->def ? "true" : "false");
			else if (uci->type == UCIString)
				sprintf(str, " default NULL");
			else if (uci->type == UCISpin)
				sprintf(str, " min %d max %d default %d", uci->min, uci->max, uci->def);
			else if (uci->type == UCICombo)
				{
				int i;
				for (i = 0; i < uci->max; i++)
					{
					sprintf(str, " var %s", Combo[uci->min][i]);
					str += strlen(str);
					}
				sprintf(str, " default %s", Combo[uci->min][uci->def]);
				}
			str += strlen(str);
			sprintf(str, "\n");
			Send("%s", string);
			}

    Send("uciok\n");
    }
static void SetOption(char *string)
    {
    UCItype *uci;
    char *v;
    char *u;
    int Value, r;
    while (string[0] == ' ' || string[0] == '\t')
        string++;
    r = strlen(string) - 1;
    while (string[r] == ' ' || string[r] == '\t')
        string[r--] = 0;
    u = strstr(string, "value");
    if (u)
        {
        while ((*u) == ' ' || (*u) == '\t')
            u--;
        }
    else
        u = string + strlen(string);
    for (uci = UCIOptions; uci->type != -1; uci++)
        {
        if (!memcmp(uci->name, string, u - string - 1))
            {
            if (uci->type == UCIButton)
                {
                Value = uci->action(true);
				if (VerboseUCI)
					Send ("info string Button %s pushed %s\n", uci->name, Value ? "true" : "false");
                return;
                }
            v = strstr(string, "value");
            if (!v)
                return;
            if (uci->type == UCIString)
                {
                strcpy((char *)(uci->var), v + 6);
				if (VerboseUCI)
					Send("info string Option %s %s\n", uci->name, (char*) (uci->var));
                if (uci->action)
                    (uci->action)(true);
                }
            else if (uci->type == UCICheck)
                {
                if (!strcmp(v + 6, "false"))
                    {
                    if (* ((bool *)(uci->var)) == false)
                        {
						if (VerboseUCI)
							Send ("info string Option %s %s\n", uci->name, "false");
                        return;
                        }
                    * ((bool *)(uci->var)) = false;
                    if (uci->action)
                        uci->action(false);
                    }
                if (!strcmp(v + 6, "true"))
                    {
                    if (* ((bool *)(uci->var)) == true)
                        {
						if (VerboseUCI)
							Send ("info string Option %s %s\n", uci->name, "true");
                        return;
                        }
                    * ((bool *)(uci->var)) = true;
                    if (uci->action)
                        uci->action(true);
                    }
				if (VerboseUCI)
					Send ("info string Option %s %s\n", uci->name, (* ((bool*) (uci->var))) ? "true" : "false");
                }
            else if (uci->type == UCISpin)
                {
                Value = atoi(v + 6);
                if (Value < uci->min)
                    Value = uci->min;
                if (Value > uci->max)
                    Value = uci->max;
                if (uci->var)
                    {
                    if (* ((int32_t *)(uci->var)) == Value)
                        {
						if (VerboseUCI)
							Send ("info string Option %s %d\n", uci->name, Value);
                        return;
                        }
                    * ((int32_t *)(uci->var)) = Value;
                    }
                if (uci->action)
                    {
                    r = uci->action(Value);
                    if (r)
                        Value = r;
                    }
				if (VerboseUCI)
					Send ("info string Option %s %d\n", uci->name, Value);
                }
            else if (uci->type == UCICombo)
                {
                strcpy((char *)(uci->var), v + 6);
				if (VerboseUCI)
					Send ("info string Option %s %s\n", uci->name, (char*) (uci->var));
                if (uci->action)
                    (uci->action)(true);
                }
            return;
            }
        }
	if (VerboseUCI)
		Send ("info string Option unknown: %s\n", string);
    }

void SharedDelete()
    {
    Lock(InputDelete);
    if (HasDeletion)
        {
        UnLock(InputDelete);
        return;
        }
    QuitPV();
    QuitLargePawns();
    DetachAllMemory();
    QuitEvalHash();
    UnLock(InputDelete);
    }
static void Quit()
    {
    SharedDelete();
    exit(0);
    }

static void ParseInput(typePos *Position, char *I)
    {
    if (!Init)
        {
        Init = true;
        LockInit(InputDelete);
        }
    UCINewGame = false;
    if (!strcmp(I, "quit"))
        {
        QuitDemand = true;
        ParseInput(Position, "stop");
        Quit();
        }
    else if (!strcmp(I, "stop"))
        {
        if (SearchIsDone)
            return;
        HaltSearch(0, 0);
        if (InfiniteLoop)
            return;
        StallMode = true;
        while (!SearchIsDone)
            NanoSleep(1000000);
        StallMode = false;
        SuppressInput = false;
        return;
        }
    else if (!strcmp(I, "isready"))
        {
		Send ("readyok\n");
        return;
        }
    if (!strcmp(I, "stall"))
        {
        StallInput = true;
        return;
        }
    else if (!strcmp(I, "ponderhit"))
        {
        PonderHit();
        return;
        }
    else if (!strcmp(I, "ucinewgame"))
        {
        if (SearchIsDone)
            {
            NewGame(Position, true);
            return;
            }
        UCINewGame = true;
        HaltSearch(0, 0);
        if (InfiniteLoop)
            return;
        StallMode = true;
        while (!SearchIsDone)
            NanoSleep(1000000);
        StallMode = false;
        SuppressInput = false;
        return;
        }
    if (JumpIsSet)
        return;
    if (!strcmp(I, "bench"))
        BenchMark(Position, "go depth 13");
    else if (!memcmp(I, "benchmark", 9))
        BenchMark(Position, I + 10);
	if (!strcmp(I, "sd-bench"))
        SDBenchMark(Position, "go depth 13");
    else if (!memcmp(I, "benchmark", 9))
        SDBenchMark(Position, I + 10);
    if (!memcmp(I, "go", 2))
        {
        InitSearch(Position, I);
        if (BoardIsOk)
            Search(Position);
        }
    else if (!memcmp(I, "position", 8))
        InitPosition(Position, I + 9);
    else if (!memcmp(I, "setoption name", 14))
        SetOption(I + 15);
    else if (!strcmp(I, "uci"))
        uci();

    SuppressInput = false;
    }

#include <unistd.h>
void Input(typePos *Position)
    {
    int i, r = 0;
    if (SuppressInput)
        return;
    if (QuitDemand)
        ParseInput(Position, "quit");
    read(STDIN_FileNO, InputBuffer, 1);
    ReadMe:
    while (InputBuffer[r++] != '\n')
        read(STDIN_FileNO, InputBuffer + r, 1);
    if (InputBuffer[r - 2] == '\\')
        {
        r -= 3;
        goto ReadMe;
        }
    InputBuffer[r - 1] = 0;
    InputBuffer[r] = 0;
    ParseInput(Position, InputBuffer);
    if (QuitDemand)
        ParseInput(Position, "quit");
    }

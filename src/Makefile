# Stockfish, a UCI chess playing engine derived from Glaurung 2.1
# Copyright (C) 2004-2008 Tord Romstad (Glaurung author)
# Copyright (C) 2008-2015 Marco Costalba, Joona Kiiski, Tord Romstad
# Copyright (C) 2015-2016 Marco Costalba, Joona Kiiski, Gary Linscott, Tord Romstad
#
# Stockfish is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# Stockfish is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.


### ==========================================================================
### Section 1. General Configuration
### ==========================================================================

### Establish the operating system name
UNAME = $(shell uname)

### Executable name
EXE = firenzina-dev

### Installation dir definitions
PREFIX = /usr/local
BINDIR = $(PREFIX)/bin

### Built-in benchmark for pgo-builds
PGOBENCH = ./$(EXE)
### Object files
OBJS = main.o \
       50move.o \
       all_node.o \
       arrays.o \
       benchmark.o \
       control.o \
       cut_node.o \
       endgame.o \
       evaluation.o \
       exclude_node.o \
       hash_init.o \
       hash_use.o \
       input.o \
       low_depth.o \
       magic_mult.o \
       make_move.o \
       material_value.o \
       mem_handler.o \
       mobility.o \
       move_gen.o \
       next_move.o \
       ok_move.o \
       pawn_eval.o \
       pv_node.o \
       qsearch.o \
       qsearch_pv.o \
       root_analysis.o \
       root_multipv.o \
       root_node.o \
       search.o \
       SEE.o \
       set_position.o \
       signals.o \
       slab_memory.o \
       SMP.o \
       SMP_init.o \
       SMP_search.o \
       static.o \
       top_analysis.o \
       top_node.o \
       unmake_move.o \
       utility.o \


### ==========================================================================
### Section 2. High-level Configuration
### ==========================================================================
#
# flag                --- Comp switch --- Description
# ----------------------------------------------------------------------------
#
# debug = yes/no      --- -g               --- Enable/Disable debug mode
# optimize = yes/no   --- -O3              --- Enable/Disable optimizations
# arch = (name)       --- (-arch)          --- Target architecture
# bits = 64           --- -m64             --- 64-bit operating system
# popcnt = yes/no     --- -DUSE_POPCNT     --- Use popcnt x86_64 asm-instruction
#
# Note that Makefile is space sensitive, so when adding new architectures
# or modifying existing flags, you have to make sure there are no extra spaces
# at the end of the line for flag values.

### 2.1. General and architecture defaults
optimize = yes
debug = no
bits = 32
popcnt = no

### 2.2 Architecture specific

ifeq ($(ARCH),x86-64-modern)
	arch = x86_64
	bits = 64
	popcnt = yes
endif

### ==========================================================================
### Section 3. Low-level configuration
### ==========================================================================

### 3.1 Selecting compiler (default = gcc)

CFLAGS += -Wall -std=c11 -Wall -Wextra -Wpedantic -Wshadow -Wfatal-errors -Wstrict-overflow -fno-strict-aliasing \
		 -Wno-missing-field-initializers -Wmissing-declarations -Wdeprecated -Wunused $(EXTRACFLAGS)
DEPENDFLAGS += -std=c11
LDFLAGS += -lpthread $(EXTRALDFLAGS)

ifeq ($(COMP),)
	COMP=gcc
endif

ifeq ($(COMP),gcc)
	comp=gcc
	CC=gcc
endif

ifeq ($(COMP),clang)
	comp=clang
	CC=clang
endif

profile_prepare = $(comp)-profile-prepare
profile_make = $(comp)-profile-make
profile_use = $(comp)-profile-use
profile_clean = $(comp)-profile-clean

### 3.2 Debugging
ifeq ($(debug),yes)
	CFLAGS += -g
endif

### 3.3 Optimization
ifeq ($(optimize),yes)
	CFLAGS += -O3
endif

### 3.4. Bits
ifeq ($(bits),64)
	CFLAGS += -m64
endif

### 3.5 popcnt
ifeq ($(popcnt),yes)
	CFLAGS += -msse3 -mpopcnt -DHasPopCNT
endif

### 3.6 Link Time Optimization, it works since gcc 4.5.
### This is a mix of compile and link time options because the lto link phase
### needs access to the optimization flags.
ifeq ($(optimize),yes)
	ifeq ($(debug),no)
		CFLAGS += -flto
		LDFLAGS += $(CFLAGS)
	endif
	ifeq ($(COMP),clang)
		LDFLAGS += -fuse-ld=gold
	endif
endif


### ==========================================================================
### Section 4. Public targets
### ==========================================================================

help:
	@echo ""
	@echo "To compile firenzina, type: "
	@echo ""
	@echo "make target ARCH=arch [COMP=compiler] [COMPCC=CC]"
	@echo ""
	@echo "Supported targets:"
	@echo ""
	@echo "build                   > Standard build"
	@echo "profile-build           > PGO build"
	@echo "strip                   > Strip executable"
	@echo "install                 > Install executable"
	@echo "clean                   > Clean up"
	@echo ""
	@echo "Supported arch:"
	@echo ""
	@echo "x86-64-modern           > x86 64-bit with popcnt support"
	@echo ""
	@echo "Supported compilers:"
	@echo ""
	@echo "gcc                     > Gnu compiler (default)"
	@echo "clang                   > LLVM Clang compiler"
	@echo ""
	@echo "Simple examples. If you don't know what to do, you likely want to run: "
	@echo ""
	@echo "make build ARCH=x86-64-modern    (This is for 64-bit systems)"
	@echo ""
	@echo "Advanced examples, for experienced users: "
	@echo ""
	@echo "make build ARCH=x86-64-modern COMP=clang"
	@echo "make profile-build ARCH=x86-64-modern COMP=gcc COMPCC=g++-4.8"
	@echo ""


.PHONY: build profile-build
build:
	$(MAKE) ARCH=$(ARCH) COMP=$(COMP) config-sanity
	$(MAKE) ARCH=$(ARCH) COMP=$(COMP) all

profile-build:
	$(MAKE) ARCH=$(ARCH) COMP=$(COMP) config-sanity
	@echo ""
	@echo "Step 0/4. Preparing for profile build."
	$(MAKE) ARCH=$(ARCH) COMP=$(COMP) $(profile_prepare)
	@echo ""
	@echo "Step 1/4. Building executable for benchmark ..."
	@touch *.c *.h
	$(MAKE) ARCH=$(ARCH) COMP=$(COMP) $(profile_make)
	@echo ""
	@echo "Step 2/4. Running benchmark for pgo-build ..."
	$(PGOBENCH)
	@echo ""
	@echo "Step 3/4. Building final executable ..."
	@touch *.c *.h
	$(MAKE) ARCH=$(ARCH) COMP=$(COMP) $(profile_use)
	@echo ""
	@echo "Step 4/4. Deleting profile data ..."
	$(MAKE) ARCH=$(ARCH) COMP=$(COMP) $(profile_clean)

strip:
	strip $(EXE)

install:
	-mkdir -p -m 755 $(BINDIR)
	-cp $(EXE) $(BINDIR)
	-strip $(BINDIR)/$(EXE)

clean:
	$(RM) $(EXE) $(EXE).exe *.o .depend *~ core *.gcda default.profdata default.profraw

default:
	help

### ==========================================================================
### Section 5. Private targets
### ==========================================================================

all: $(EXE) .depend

config-sanity:
	@echo ""
	@echo "Config:"
	@echo "debug: '$(debug)'"
	@echo "optimize: '$(optimize)'"
	@echo "arch: '$(arch)'"
	@echo "bits: '$(bits)'"
	@echo "popcnt: '$(popcnt)'"
	@echo ""
	@echo "Flags:"
	@echo "CC: $(CC)"
	@echo "CFLAGS: $(CFLAGS)"
	@echo "LDFLAGS: $(LDFLAGS)"
	@echo ""
	@echo "Testing config sanity. If this fails, try 'make help' ..."
	@echo ""
	@test "$(debug)" = "yes" || test "$(debug)" = "no"
	@test "$(optimize)" = "yes" || test "$(optimize)" = "no"
	@test "$(arch)" = "x86_64"
	@test "$(bits)" = "64"
	@test "$(popcnt)" = "yes" || test "$(popcnt)" = "no"
	@test "$(comp)" = "gcc" || test "$(comp)" = "clang"

$(EXE): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)

gcc-profile-prepare:
	$(MAKE) ARCH=$(ARCH) COMP=$(COMP) gcc-profile-clean

gcc-profile-make:
	$(MAKE) ARCH=$(ARCH) COMP=$(COMP) \
	EXTRACFLAGS='-fprofile-generate' \
	EXTRALDFLAGS='-lgcov' \
	all

gcc-profile-use:
	$(MAKE) ARCH=$(ARCH) COMP=$(COMP) \
	EXTRACFLAGS='-fprofile-use' \
	EXTRALDFLAGS='-lgcov' \
	all

gcc-profile-clean:
	@rm -rf *.gcda *.gcno

clang-profile-prepare:
	$(MAKE) ARCH=$(ARCH) COMP=$(COMP) clang-profile-clean

clang-profile-make:
	$(MAKE) ARCH=$(ARCH) COMP=$(COMP) \
	EXTRACFLAGS='-fprofile-instr-generate' \
	EXTRALDFLAGS='-fprofile-instr-generate' \
	all

clang-profile-use:
	@llvm-profdata merge -output=default.profdata default.profraw
	$(MAKE) ARCH=$(ARCH) COMP=$(COMP) \
	EXTRACFLAGS='-fprofile-instr-use=default.profdata' \
	all

clang-profile-clean:
	@rm -f default.profdata default.profraw

.depend:
	-@$(CC) $(DEPENDFLAGS) -MM $(OBJS:.o=.c) > $@ 2> /dev/null

-include .depend


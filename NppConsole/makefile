# 
# This file is part of Notepad++ console plugin.
# Copyright ©2011 Mykhajlo Pobojnyj <mpoboyny@web.de>

# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
# 

BINNAME=NppConsole.dll
OUTDIR=bin
OBJDIR=obj
INCDIR=include
SRCDIR=source
RCDIR=resources
TARGETDIR="D:/Programms/npp.5.9.bin.minimalist/plugins"

CC=${GXX}
CFLAGS=-Wall -Wno-missing-braces -Wno-conversion-null
LINK=${GXX}
LDFLAGS=-s -lcomctl32 -lgdi32 -static -shared -Wl,--subsystem,windows
RC=${RCC}

DEFINES=-DUNICODE -D_UNICODE
INCLUDES=-I./$(INCDIR) -I./NppCommon -I../Common

ifeq ($(debug),yes)
  CFLAGS+= -g -O
  DEFINES+= -D_DEBUG -DDEBUG
endif

ifeq ($(log),yes)
  DEFINES+= -D_SYSLOG
endif

HEADERS:=$(wildcard $(INCDIR)/*)
SOURCES:=$(wildcard $(SRCDIR)/*)
OBJECTS:=$(patsubst $(SRCDIR)/%.cxx, $(OBJDIR)/%.o,$(SOURCES))

RCFILES:=$(wildcard $(RCDIR)/*)
RCSOURCE:=$(RCDIR)/resources.rc
RCOBJECT:=$(OBJDIR)/resources.o


all : $(OUTDIR) $(BINNAME)

$(OUTDIR):
	-${MKDIR} $(OUTDIR)
	-${MKDIR} $(OBJDIR)

$(BINNAME): $(OBJECTS) $(RCOBJECT) 
	$(LINK) -o $(OUTDIR)/$(BINNAME) $(OBJECTS) $(RCOBJECT) $(LDFLAGS)
	-${CP} $(OUTDIR)/$(BINNAME) $(TARGETDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.cxx $(HEADERS)
	$(CC) $(CFLAGS) $(DEFINES) $(INCLUDES) -c $< -o $@

$(RCOBJECT): $(RCFILES)
	$(RC) $(INCLUDES) -i $(RCSOURCE) -o $(RCOBJECT)

clean:
	-${RMDIR} $(OBJDIR)
	-${RMDIR} $(OUTDIR)

.PHONY: clean

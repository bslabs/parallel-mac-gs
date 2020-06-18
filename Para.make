#   File:       Para.make
#   Target:     Para
#   Sources:    :Paralell:Source:Common.c

SourceDir = {MPW}Paralell:Source:
IncludeDir = {MPW}Paralell:Includes:
ObjDir = {MPW}Paralell:Obj:
RezDir =  {MPW}Paralell:Resources:

OBJECTS = ¶
		{ObjDir}Common.c.o ¶
		{ObjDir}Globals.c.o ¶
		{ObjDir}ParaMain.c.o ¶
		{ObjDir}Menus.c.o ¶
		{ObjDir}Dialogs.c.o ¶
		{ObjDir}Sound.c.o ¶
		{ObjDir}print.c.o
Para ÄÄ Para.make {RezDir}ParaMac.r
	 Rez -a {RezDir}ParaMac.r -i {RIncludes} -o Para
 
Para ÄÄ Para.make {OBJECTS}
	Link -w -t APPL -c MOOf ¶
		{OBJECTS} ¶
		"{CLibraries}"CSANELib.o ¶
		"{CLibraries}"Math.o ¶
		"{CLibraries}"StdClib.o ¶
		"{CLibraries}"CInterface.o ¶
		"{CLibraries}"CRuntime.o ¶
		"{Libraries}"Interface.o ¶
		-o Para

{ObjDir}Common.c.o Ä Para.make {SourceDir}Common.c
	 C -d MAC -i {IncludeDir} {SourceDir}Common.c -o {ObjDir}Common.c.o
{ObjDir}Globals.c.o Ä Para.make {SourceDir}Globals.c
	 C  -d MAC -i {IncludeDir} {SourceDir}Globals.c -o {ObjDir}Globals.c.o
{ObjDir}ParaMain.c.o Ä Para.make {SourceDir}ParaMain.c
	 C  -d MAC -i {IncludeDir} {SourceDir}ParaMain.c -o  {ObjDir}ParaMain.c.o
{ObjDir}Menus.c.o Ä Para.make {SourceDir}Menus.c
	 C -d MAC -i {IncludeDir} {SourceDir}Menus.c -o  {ObjDir}Menus.c.o
{ObjDir}Dialogs.c.o Ä Para.make {SourceDir}Dialogs.c
	 C -d MAC -i {IncludeDir} {SourceDir}Dialogs.c -o  {ObjDir}Dialogs.c.o
{ObjDir}Sound.c.o Ä Para.make {SourceDir}Sound.c
	 C -d MAC -i {IncludeDir} {SourceDir}Sound.c -o  {ObjDir}Sound.c.o
{ObjDir}print.c.o Ä Para.make {SourceDir}print.c
	 C -d MAC -i {IncludeDir} {SourceDir}print.c -o  {ObjDir}print.c.o


#   File:       ParaGS.make
#   Target:     ParaGS

SourceDir = {MPW}Paralell:Source:
IncludeDir = {MPW}Paralell:Includes:
ObjDir = {MPW}Paralell:Obj:
RezDir = {MPW}Paralell:Resources:


ParaGS ÄÄ ParaGS.make ¶
		"{CIIGSLibraries}"Start.obj ¶
		{ObjDir}Common.c.obj ¶
		{ObjDir}Dialogs.c.obj ¶
		{ObjDir}Globals.c.obj ¶
		{ObjDir}Menus.c.obj ¶
		{ObjDir}ParaMain.c.obj¶
		{ObjDir}Sound.c.obj ¶
		{ObjDir}Print.c.obj
	LinkIIGS ¶
		"{CIIGSLibraries}"Start.obj ¶
		{ObjDir}Common.c.obj ¶
		{ObjDir}Dialogs.c.obj ¶
		{ObjDir}Globals.c.obj ¶
		{ObjDir}Menus.c.obj ¶
		{ObjDir}ParaMain.c.obj ¶
		{ObjDir}Sound.c.obj ¶
		{ObjDir}print.c.obj ¶
		-lib "{CIIGSLibraries}"CLib ¶
		-o ParaGS
  reziigs -o ParaGS {RezDir}ParaGS.r -i {riigsincludes}
	DuplicateIIGS -y -mac ParaGS :
#ParaGS ÄÄ  :Paralell:Resources:ParaGS.r
{ObjDir}Common.c.obj Ä ParaGS.make {SourceDir}Common.c
	CIIGS -d GS -i {IncludeDir} {SourceDir}Common.c -o {ObjDir}Common.c.obj
{ObjDir}Dialogs.c.obj Ä ParaGS.make {SourceDir}Dialogs.c 
	CIIGS -d GS -i {IncludeDir} {SourceDir}Dialogs.c -o {ObjDir}Dialogs.c.obj
{ObjDir}Globals.c.obj Ä ParaGS.make {SourceDir}Globals.c 
	CIIGS -d GS -i {IncludeDir} {SourceDir}Globals.c -o {ObjDir}Globals.c.obj
{ObjDir}Menus.c.obj Ä ParaGS.make {SourceDir}Menus.c  
	CIIGS -d GS -i {IncludeDir} {SourceDir}Menus.c -o {ObjDir}Menus.c.obj
{ObjDir}ParaMain.c.obj Ä ParaGS.make {SourceDir}ParaMain.c  
	CIIGS -d GS -i {IncludeDir} {SourceDir}ParaMain.c -o {ObjDir}ParaMain.c.obj
{ObjDir}Sound.c.obj Ä ParaGS.make {SourceDir}Sound.c 
	CIIGS -d GS -i {IncludeDir} {SourceDir}Sound.c  -o {ObjDir}Sound.c.obj
{ObjDir}print.c.obj Ä ParaGS.make {SourceDir}print.c 
	CIIGS -d GS -i {IncludeDir} {SourceDir}print.c -o {ObjDir}print.c.obj

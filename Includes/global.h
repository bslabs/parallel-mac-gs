#ifndef __MYGLOBALS__
#define __MYGLOBALS__
#include <types.h>
#include "defines.h"
extern int itemID;
extern int menuID;		/* global for HiliteMenu() use */
extern WindowPtr activewindow; /* our window */
extern EventRecord ERecord;	
#ifdef MAC
extern ControlHandle myctlhandle;  /* spelled differently on the GS */
extern MenuHandle applemenuhandle,filemenuhandle,editmenuhandle;
extern ControlHandle TheControlID;
extern SysEnvRec myConfig;
extern Boolean YeahColor;	/* my color flag */
extern Handle MyMenuHandle;
extern long Notes[];
extern Boolean gHasWaitNextEvent;
#endif

#ifdef GS
extern Boolean editSet;	/* for toggling the edit menu items for NDAs */
extern MenuBarRecHndl MyMenuHandle;
extern PatternPtr Pats[5];
extern Pattern mypatterns[5];
extern Ref mystartstopreccord;  
extern CtlRecHndl myctlhandle;
extern short Notes[];
#endif
#endif
/* game variables */
extern int CurrentScore;
extern Rect RA[6];	/* array of rects */
extern Point WordPoint;
extern Boolean Playing;
extern Boolean PlayedOnce;
extern unsigned char Sequence[500];
extern int SeqPos;
extern int CurrentLength;
extern Boolean tryagain;


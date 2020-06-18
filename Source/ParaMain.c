/* ************************************************************************* */
/*																			 */
/* Parallel application shell and example									 */
/* By: C.K. Haun															 */
/* Para is designed to show that Mac and GS programming are a lot closer 	 */
/* than you might have thought.  By using the techniques shown here and 	 */
/* careful planning, you can develop applications for both platforms 		 */
/* in parallel, speeding up development, testing, and debugging time.		 */
/* ************************************************************************* */
/*    NOTE: Requires MPW C and MPW CIIGS !									 */
/* ************************************************************************* */
/*																			 */
/*		v1.0B1	Haun	Version for '90 WWDC CD	     						 */
/*	Components:																 */
/*				Paramain.c													 */
/*				Common.c													 */
/*				Dialogs.c													 */
/*				Globals.c													 */
/*				Menus.c														 */
/*				Print.c														 */
/*				Sound.c														 */
/*				Defines.h													 */
/*				Global.h													 */
/*				GSAlias.h													 */
/*				ParaGS.h													 */ 
/*				ParaMac.h													 */
/*				ParaGS.r													 */
/*				ParaMac.r													 */
/*				Para.make													 */
/*				ParaGS.make													 */
/*				ParaMenu													 */
/* ************************************************************************* */

/*********************************************************************
*                                                                    *
*                                                                    *
*             Copyright (c) Apple Computer, Inc. 1990                *
*                       All Rights Reserved                          *
*                                                                    *
*                                                                    *
*  ----------------------------------------------------------------  *
*                                                                    *
*     This program and its derivatives are licensed only for         *
*     use on Apple computers.                                        *
*                                                                    *
*     Works based on this program must contain and                   *
*     conspicuously display this notice.                             *
*                                                                    *
*     This software is provided for your evaluation and to           *
*     assist you in developing software for the Apple IIGS           *
*     and Macintosh computers.                                       *
*                                                                    *
*     DISCLAIMER OF WARRANTY                                         *
*                                                                    *
*     THE SOFTWARE IS PROVIDED "AS IS" WITHOUT                       *
*     WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED,               *
*     WITH RESPECT TO ITS MERCHANTABILITY OR ITS FITNESS             *
*     FOR ANY PARTICULAR PURPOSE.  THE ENTIRE RISK AS TO             *
*     THE QUALITY AND PERFORMANCE OF THE SOFTWARE IS WITH            *
*     YOU.  SHOULD THE SOFTWARE PROVE DEFECTIVE, YOU (AND            *
*     NOT APPLE OR AN APPLE AUTHORIZED REPRESENTATIVE)               *
*     ASSUME THE ENTIRE COST OF ALL NECESSARY SERVICING,             *
*     REPAIR OR CORRECTION.                                          *
*                                                                    *
*     Apple does not warrant that the functions                      *
*     contained in the Software will meet your requirements          *
*     or that the operation of the Software will be                  *
*     uninterrupted or error free or that defects in the             *
*     Software will be corrected.                                    *
*                                                                    *
*     SOME STATES DO NOT ALLOW THE EXCLUSION                         *
*     OF IMPLIED WARRANTIES, SO THE ABOVE EXCLUSION MAY              *
*     NOT APPLY TO YOU.  THIS WARRANTY GIVES YOU SPECIFIC            *
*     LEGAL RIGHTS AND YOU MAY ALSO HAVE OTHER RIGHTS                *
*     WHICH VARY FROM STATE TO STATE.                                *
*                                                                    *
*                                                                    *
*********************************************************************/




/* The Main segement for Paralell */




#ifdef MAC 
#include "paramac.h"
extern Boolean TrapAvailable(tNumber,tType);
#endif

#ifdef GS
#include "parags.h"
extern PicHandle GetPicture();
#include "GSAlias.h"

#endif

 
#include "defines.h"
 

/* Some externs.  If you want to use the ANSI type checking for MPW C, then you'll
 want to move these to ParaMac.h and fully define them */
extern GetIndRect();
extern SwitchTitle();
extern int	DisplayScore();
extern note();
extern InitBell();
extern SayTryAgain(); 
extern Pen();
extern WriteNum();
extern PrintScore();

main()
	{
	/* local main variables */
	Boolean quitFlag;
	int x;
	#ifdef MAC
	RgnHandle mousergn;  /* for WaitNextEvent */ 
	mousergn=NewRgn(); 
	
	#endif

	
	
	StartProgram();
	StartMenus();
	
	/* some game flags */
	Playing=false; 
	quitFlag=false;
	
	/* Hacking the Event Loop */
	/*  The most comprehensive and hardest to get around changes happen here,
	in the programs event loop.  The Mac generates 16 events.  The gs's 
	TaskMaster generates [30].  That's a major difference, and some of the 
	things work the same even though they have different event numbers.
	But, careful planning and creative use of defines will fix */
	

	
		while(!quitFlag){
		#ifdef MAC
		SystemTask();

	if(gHasWaitNextEvent) x = WaitNextEvent(everyEvent, &ERecord, MAXLONG, mousergn);
		else x=GetNextEvent(everyEvent,&ERecord); 
		
		
		#endif
		#ifdef GS
		ERecord.wmTaskMask=0x1fffff;
		ERecord.what=TaskMaster(everyEvent,&ERecord);
		/* putting the extended code into the what field for */
		 /* call compatability with the Mac */	
		#endif			 
		x=FixEvent(&ERecord);
		
		/* lots of event codes are different on the two machines, and TaskMaster
		adds quite a few.  Also, a lot of the events needed on the Mac are not
		needed when TaskMaster is being used.
		So, the choice is to either make your main event loop even more 
		complicated than it already is, or work around it.
		The function call FixEvent() is the work-around.  FixEvent generates 
		pseudo event codes that will match all the mac or gs events, without 
		having to have contradictory or misleading event types.
		It encapsulates things like MenuSelect ,FindWindow, and TrackControl*/
		
			switch(x){
				case pNullEvent :
				break;
				case pMouseDown :
				break;
				case  pMouseUp :
				break;
				case  pKeyDown :
				break;
				
				case  pKeyUp	:   /* not available directly on the gs */
				break;
				
				case  pAutoKey	:
				break;
				case  pUpdate		:

				break;
				
				case  pDisk	:   /* not available on the gs */
#ifdef MAC
				 DoDiskEvents(ERecord.message);
#endif
				break;
				
				case  pActivate	:
				break;
				
				case  pSwitch	:  /* not available on the Mac */
				break;
				
				case  pNetwork	:  /* not available on the gs */
				break;
				
				case  pDriver	:
				break;
				
				case  pApp1	:
				break;
				
				case  pApp2	:
				break;
				
				case  pApp3	:
				break;
				
				case  pApp4	:
				break;
				
				
				case  pDeskTop	:
				break;
				
				case  pMenuBar	 :
				
					
					
					switch(itemID){
						case aboutitem :
							AboutPara();  /* go show an alert */
						break;
						case quititem:
							quitFlag=true;
						break;
						case newgameitem : /* start the game now.  All these functions */					
							Playing=true;  /* are identical on the Mac and GS */
							EraseRect(&activewindow->portRect);
							InvalRect(&activewindow->portRect);
							ShowControl(myctlhandle);
							StartGame();
							
						break;
						
						
						
						
						
						}
					/* One method of dealing with differences is to conditionally */
					/* compile them at each occurance, like this HiliteMenu() call */
					/* Since I only call this once in this program I'm comfortable */
					/* with doing it this way.  It's also very plain what's */
					/* happening. */
					#ifdef MAC   
					HiliteMenu(false);   
					#endif			  
					#ifdef GS
					HiliteMenu(false,menuID);
					#endif
				break;
				
				case  pSysClick	: 
				break;					
				
				case  pInContent :
				/* Window content click, only important during game */

					GlobalToLocal(&ERecord.where);
					if(Playing)TestHit(ERecord.where);
				
				break;
				
				
				case  pDrag	:
				break;
				
				case  pGrow	:
				break;
				
				case  pGoAway :
					quitFlag=true;
				break;
				
				case  pZoom	:
				break;
				
				case  pInInfo	:  /* not directly avaiable on the Mac */
				break;
				
				case  pInSpecial :	  /* not directly avaiable on the Mac */
				break;
				
				case  pInDA	:  			/* not directly avaiable on the Mac */
				break;
				
				case  pInFrame	:  /* not directly avaiable on the Mac */
				break;
				
				case  pInactiveMenu	:  /* not directly avaiable on the Mac */
				break;
				
				case  pCloseNDA	:  /* not directly avaiable on the Mac */
				break;
				
				case  pTrackZoom	:
				break;
				
				case  pInControl :  /* not directly avaiable on the Mac, faked with */
									/* FixEvent */
					if(!PlayedOnce){
						PlaySeq();
						PlayedOnce=true;
				
						/* This call is aliased in the GS headers file.  I have */
						/* re-defined it so the call works the same way on both */
						/* machines.  */
						HiliteControl(myctlhandle,255);

						}
				
				
				
				
				
				
				break;
				
				case  pInControlMenu	:  /* not directly avaiable on the Mac */
				break;
				
				
				
				
				
				}
		

		} 
	#ifdef GS
	/* the gs needs to shut down the tools it started */
	/* during your exit of the program */
	ShutDownTools(refIsHandle,mystartstopreccord);
	#endif
}  /* main */
	
	
/* DrawMain is the content draw routine for the currently open window
*  On the Mac, you have to explicitly call DrawMain() in response to an
*  update or activate event.  On the GS, the pointer to the DrawMain
*  routine is set ( see below in StartProgram() ) when the program is started, and TaskMaster
*  will call it as appropriate.  The beauty of it is, however you call it, it's
*  still the same routine....
*/
/* Inputs : none */
/* Ouputs : none */
DrawMain()
{
int qq;
PicHandle fredhandle;
Rect temprect;
#ifdef MAC
BeginUpdate(activewindow);  /* The Window Manager calls BeginUpdate on the GS */
#endif
/* have to preserve old data bank and make sure this routine's DB is set.  */
#ifdef GS
int dbr;
dbr = SaveDB();
#endif
if(!Playing){  /* Show the title graphic if not playing */
	fredhandle=GetPicture(0x18L);
	temprect=(*(fredhandle))->picFrame;
	#ifdef GS
	InsetRect(&temprect,0,8);  /* TEMP fix */
	#endif	
	DrawPicture(fredhandle,&temprect);}
else{  /* We're playing, so paint the rects,the score, and the control */ 
	/* now paint the rects */
	for(qq=0;qq<4;qq++){
		SetColor(qq+1);
		/* Since the Rects came out of resources, we just don't care what machine */
		/* we're painting them on */
		PaintRect(&RA[qq]);
		SetColor(0);
		Pen(3,3);		/* in common.c, sets pen size */
		temprect=RA[qq];
		InsetRect(&temprect,-3,-3);
		FrameRect(&temprect);
		
		MoveTo(WordPoint.h,WordPoint.v);
		DrawString("\pSteps completed: ");
		
		
		EraseRect(&RA[5]);
		
		#ifdef MAC
		TextFace(bold);
		#endif
		#ifdef GS
		SetTextFace(boldMask);
		#endif
		WriteNum(CurrentScore);
		
		#ifdef MAC
		TextFace(normal);
		#endif
		#ifdef GS
		SetTextFace(plainMask);
		#endif




		}}

DrawControls(activewindow); 

#ifdef MAC
EndUpdate(activewindow);  /* The Window Manager calls EndUpdate on the GS */
#endif
#ifdef GS
 RestoreDB(dbr);  /* restore old GS data bank */
#endif

}

 





/* Starting tools is one of the major differences between the Mac and
* the GS.  The GS requires the application to allocate workspace for the
* toolsets it plans to use.
* Also, there are more toolsets that need to be started.
* But by using the GS StartUpTools() call, the actually coding is smaller
* than the Mac. 
*/
/* Inputs : none */
/* Ouputs : none */
StartProgram()
{
int qq;  /* index counter I'll be using */

#ifdef MAC
UnloadSeg((Ptr) _DataInit);	/* get rid of the %A5init segment */
MaxApplZone();	 			/* fill whole heap */

InitGraf((Ptr) &qd.thePort); /* Quickdraw On */
InitFonts();
InitWindows();
InitMenus();
TEInit();
InitDialogs(nil);
InitCursor();
DILoad();
/* get my window for the wind resource */
activewindow=GetNewWindow(8888,0,(WindowPtr)-1);
SetPort(activewindow);
myctlhandle=GetNewControl (1111,activewindow);

/* Find out if Color QuickDraw is available on the machine we're running on */
SysEnvirons(1,&myConfig);
YeahColor=myConfig.hasColorQD;

/* See if we are multiFinding or not */
gHasWaitNextEvent = TrapAvailable(_WaitNextEvent, ToolTrap);
  
#endif
#ifdef GS
 int ii;
 char temp;

mystartstopreccord=StartUpTools(_ownerid, 2, 0x0001L); 

InitCursor();    /* StartUpTools() sets waitcursor if QDAUX is started */
/* NewWindow2 loads the window from our resource fork */
activewindow=(WindowPtr)NewWindow2(0L,0L,(ProcPtr)DrawMain,0L,2,0x003BE79EL,0x800e);

/* the control list for this window is attached to the window resource, so I */
/* don't need to create the controls for this window, they get created by the */
/* NewWindow2() call.   But I will need the resulting handle */
/* for the control we have */

myctlhandle=GetCtlHandleFromID(activewindow, 0x701AF1E6L);

/* initialize my patterns */
for(ii=0;ii<0x20;ii++)mypatterns[0][ii]=0;
Pats[0]=mypatterns[0];
for(qq=1;qq<5;qq++){
	Pats[qq]=mypatterns[qq];
	for(ii=0;ii<0x20;ii++){
		temp=(qq+4)*0x10;
		temp=temp|(qq+4);
		mypatterns[qq][ii]=temp;
		}
}



#endif





SetPort(activewindow);
HideControl(myctlhandle);

/* now load the points and the rects from our point and rect resource */
/* This makes us very flexible, we can vary screen coordinates from machine */
/* to machine without 1) Recompiling the source or 2) Affecting the other machine's */
/* code AT ALL */
for(qq=0;qq<6;qq++)GetIndRect(&RA[qq],1,qq+1);
/* move the second to last rect into a point */
/* since I store point info in my rect list.  Less confusing than creating a new */
/* resource type for this simple application.  If you use a lot of points, then */
/* it would benifit you to create a rPointList resource */
#ifdef MAC
WordPoint.h=RA[4].left;
WordPoint.v=RA[4].bottom;
#endif
#ifdef GS
WordPoint.h=RA[4].h1;
WordPoint.v=RA[4].v2;
#endif
InitBell();  /* sets our bell tone */
}

/* Disk events don't happen on the GS (yet) so this routine is only compiled */
/* on the Mac.  You can create your own disk events on the GS, but is it worth it */
/* to your application? */
	
#ifdef MAC
/* Inputs : long event message */
/* Ouputs : none */
void DoDiskEvents(long message)
{ int hival,loval,temp;
	Point fredpoint = {40,40};
	hival=HiWord(message);
	loval=LoWord(message);
	if(hival!=noErr)/* something happened */
		{ temp=DIBadMount(fredpoint,message);}
}


#endif








/* All the rest of the stuff is the heart of the game.  And of course, it's just
in plain old ordinary C, C that'll run on a Mac, on a gs, on an Amiga, or on a 
Cray.  And that's the point, most of the brain work that you'll be doing
on your project lies here, and here is the point where it's all the same. */

/* Tests the current mouse position, sees if the player clicked in the right box 
	for the current sequence position */
/* Inputs : Point */
/* Ouputs : none */
TestHit(x)
Point x;
	{long startticks;
	long nowticks;
	int qq;
	for(qq=0;qq<4;qq++){
		/* Mac PtInRect takes a Point.  GS takes a Point pointer.  Sometimes these */
		/* things can become annoying */
		#ifdef MAC
		if(PtInRect(x,&RA[qq])){
		#endif
		#ifdef GS
		if(PtInRect(&x,&RA[qq])){
		#endif
			InvertRect(&RA[qq]);	/* flash the box and play a note */
			note(Notes[qq]);
			InvertRect(&RA[qq]);
			
			/* check for current lenght */
			
			if(Sequence[SeqPos]==qq){  /* This was the correct box for the current */
				SeqPos++;			   /* position, so advance to the next */
					if(SeqPos==CurrentLength){
						CurrentLength++;
						if(CurrentScore)CurrentScore++;  /* increase score if not 0 */
						else CurrentScore=3;
						InvalRect(&RA[5]); /* invalidate the score area */
		
		
						SeqPos=0;
						/* now wait a bit before restarting */
						/* so the player has time to think */
						startticks=TickCount();
						
						nowticks=TickCount();
						while((nowticks-startticks)<45){
						nowticks=TickCount();}
						PlaySeq();}
			
			}
		else{ /* wrong box, tell them so */
			Failure(); }
		
		
		}
		
		}
		
	
	
	}

/* Initializes the 500 step sequence */
/* Inputs : none */
/* Ouputs : none */
SetSeq()
	{
	int qq;
	for(qq=0;qq<500;qq++){
		Sequence[qq]=Random()&0x3;
	
	
	}
	CurrentLength=3;  /* always starts at 3 */
	
	
}

/* Play the sequence that the user must track */
/* Inputs : none */
/* Ouputs : none */
PlaySeq()
{
int qq;
for(qq=0;qq<CurrentLength;qq++){
	InvertRect(&RA[Sequence[qq]]);
	note(Notes[Sequence[qq]]);
	InvertRect(&RA[Sequence[qq]]);
	
	
	
}


}

/* This is the fail point.  Everyone will reach here someday.  */
/* Remeber, in VideoGames, there is no success... */
/* Inputs : none */
/* Ouputs : none */
Failure()
{int val; 
if(!tryagain){  /* give 'em another chance */
	SayTryAgain();    /* an alert */
	SeqPos=0;
	DrawMain();  /* redraw after the alert box trashed the screen */
	
	PlaySeq();
	tryagain=true;
	
}
else{
	HideControl(myctlhandle);
	
	
	val=DisplayScore(CurrentScore);  /* in dialogs */
	DrawMain();
	Playing=false;

	if(val==3)PrintScore();
	EraseRect(&activewindow->portRect);
	InvalRect(&activewindow->portRect);
			
	
}

}

/* Sets up all the starting variables for the game, and re-draws the screen in it's */
/* new colors. */
/* Inputs : none */
/* Ouputs : none */
StartGame()
	{
	SetSeq();
	CurrentScore=0;
	DrawMain();
	PlaySeq();
	tryagain=false;
	PlayedOnce=false;
	SeqPos=0;

	/* this call is aliased on the GS */
	HiliteControl(myctlhandle,false);
	
}


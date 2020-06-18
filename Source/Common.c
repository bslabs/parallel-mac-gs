/* Some very common routines which can be problems when trying to write for both 
   machines, but have simple solutions */
#ifdef GS
#include "parags.h"
#endif
#ifdef MAC
#include "paramac.h"
extern ControlHandle myctlhandle;
#endif


#include "defines.h"

/* SetColor is an alternative to using ForeColor,SetSolidPenPat, etc. 
   For specific special color uses, this will not work, but it will be functional
   in almost all situations.  Those times when it won't work are usually
   when you are addressing specific hardware, and that's not paralell
   material anyway. */
/* Input : integer color word */
/* output : none */
SetColor(color)
int color;
{
	/* Of course, this is completely different on the GS and the Mac.  But */
	/* by using a function like SetColor() to do all your color setting, you */
	/* only have to remember one function, instead of doing conditional compiles */
	/* every time you change colors.  Cleans up your source code */
	#ifdef MAC
	long MyColors[5]={
		blackColor,
		redColor ,
		greenColor, 
		blueColor,
		cyanColor
		};
	
	Pattern wpat1;
	/* For the Mac, I'm just going with two levels of checking.  If the machine
	has color quickdraw, I use old style quickdraw coloring.  If it doesn't have
	CQD I use patterns.*/
	
	if(YeahColor){
		ForeColor(MyColors[color]);}
		
	else{  /* instead use a pattern */	
		if(color!=0){GetIndPattern((Pattern)wpat1, sysPatListID,color+10);
		PenPat(wpat1);}
		else{ PenPat(qd.black);}
		}
	
	
	#endif
	#ifdef GS
	SetPenPat(Pats[color]);
	#endif
	
	
	
}

/*	FixEvent is the heart of a mini-TaskMaster for the Mac side.  It encapsulates
	all the window manipulation and control calls, returning a 'new' event code
	or null.  Most of these can be set to return null, but there may be specific
	instances when you'd like to know about the result, like a pMenuEvent */

#ifdef MAC
/* Input : Event record pointer */
/* Output : pseudo event code specific to Parallel, defined in defines.h */
short FixEvent(EventRecord *x)
{
extern DrawMain();
WindowPtr twindow;
Rect limitRect={0,0,320,512};  /* or whatever you'd like */
long endGrowSize;
int currentcontrol;
int pcode;
int fred;
Point locpoint;
ControlHandle returnedcontrol;
switch(x->what){
	case pKeyDown: 
	case pAutoKey :
		if(x->modifiers & cmdKey){  /* this call further encapsulates menu key */
		 							/* selections in FixEvent */
			if(ReturnID(MenuKey(x->message & charCodeMask)))return(pMenuBar);}
			/* if menukey is successful, ReturnID fills the correct variables */
			/*  matching the GS numbering system, and */
			/* returns true */
		else{ return(x->what);}
	break;
	
	
	case pMouseDown :
		switch(FindWindow(x->where,&twindow)){
			case inDesk:
				return(pDeskTop);
			break;
			case inMenuBar:
				if(ReturnID(MenuSelect(x->where)))return(pMenuBar);
			/* if MenuSelect is successful, ReturnID fills the correct variables */
			/*  matching the GS numbering system, and */
			/* returns true */
				return(pNullEvent); /* else no event */
			break;
			case inSysWindow:			
				SystemClick(x, twindow);  
				return(pSysClick);  /* in case you care about sys clicks */
			break;
			
			case inDrag:
				DragWindow(twindow,x->where,&qd.screenBits.bounds);
				return(pNullEvent);
			break;
			case inGrow:
				endGrowSize=GrowWindow(twindow,x->where,&limitRect);
				/* endGrowSize is here in case you care about it ever, not used here */
				return(pNullEvent);
			break;
			case inGoAway:
				if(TrackGoAway(twindow,x->where))return(pGoAway);
				return(pNullEvent);  
			break;
			case inContent:
				if(twindow!=FrontWindow()){
					SelectWindow(twindow);return(pNullEvent);}
					/* falls through if this was already the front window */				
			default :
			/* none of the above, so indicating a raw content click. 
			Since the gs's TaskMaster tracks controls automatically, so will we... */
			
				currentcontrol=0;
				pcode=0;
				locpoint=x->where;  /* I may want the global coords saved for later */
				GlobalToLocal(&locpoint);
				fred=FindControl(locpoint,twindow,&returnedcontrol);
				if(fred){ /* it's in a control */
					/* now see what the part code was */

					fred=TrackControl(returnedcontrol,locpoint,NULL); 
					if(fred){ /* stayed in until MouseUp */
						TheControlID=returnedcontrol;
						return(pInControl);}}
				/* but if it really wasn't a control, we'll do this... */
				return(pInContent);
			break;
			
			
			}
	break;
	case pUpdate :
	case pActivate :
	DrawMain();
	break;
	default :
		/* anything else, just tell 'em about it */
		return(x->what);
	break;
	
}




}
#endif
#ifdef GS
/* Input : Event record pointer */
/* Output : pseudo event code specific to Parallel */
/* The GS FixEvent loop is of course much smaller than the Mac version, since */
/* TaskMaster takes care of most of the stuff */
int FixEvent(x)
EventRecord * x;
{
int qq;
/* first check the front window to see if edit items need to be enabled for */
/* NDAs */
if((GetWKind(FrontWindow())) & 0x8000)
	{
	if(!editSet){
	
	for(qq=undoitem;qq<closeitem+1;qq++)EnableMItem(qq);
	editSet=true;
	}
	}
else{
	if(editSet){
		for(qq=undoitem;qq<closeitem+1;qq++)DisableMItem(qq);
		editSet=false;
	}
}



switch(x->what){
	
	case wInMenuBar :  /* main difference here is to xfer the menu item and menu ID */
	ReturnID();	 	   /*	to a symmetrical place as the Mac's */
	break;
	
	case activateEvt :   /* redrawing already handled by the ContentDraw proc, you */
	case updateEvt :	 /*	may want additional enabling and disabling */
		return(pNullEvent);
	break;
	case wInControl :
		return(pInControl);
	break;	
	
}


	return(x->what);
}

#endif





/* GetIndRect gets a Rect structure from a resource */
/* 	This greatly facilitates using the same graphic routines for both machines.
	Since basically everything in QuickDraw can be expressed as a Rect ( or half a 
	Rect, a Point) putting the different screen coords in resources allows you
	to never use frustrating conversion factors or graphics juggling, you put
	the real coordinates you want in each fork. */
/* 	Inputs : 	Pointer to rectangle structure to fill 
				Resource ID of rect list to use
				Index of rectangle to load */
/*	Outputs :	None */

GetIndRect(myrectpointer,rectlist,whichrect)
Rect *myrectpointer;
int rectlist;
int whichrect;
{
	Handle theresource;
	#ifdef GS
	theresource=(Handle)LoadResource(98,(long)rectlist);
	#endif
	#ifdef MAC
	theresource=(Handle)GetResource('RECT',rectlist);
	
	#endif
	whichrect--;
	/* the sizeof()s in this call are just insurance and super-protection, */
	/* letting the compiler do math instead of us.  That's why we bought the */
	/* computers. */
	whichrect=(whichrect*(sizeof(Rect)))+sizeof(long);
	
	BlockMove((Ptr)((*theresource)+whichrect),(Ptr)myrectpointer,(long)sizeof(Rect));
}



/* Does the same thing for points as GetIndRect does for Rects */
/* This isn't used in this program, included for your entertainment */
GetIndPoint(mypointpointer,pointlist,whichpoint)
Point *mypointpointer;
int pointlist;
int whichpoint;
{
Handle theresource;
#ifdef GS
theresource=(Handle)LoadResource(99,(long)pointlist);
#endif
#ifdef MAC
theresource=(Handle)GetResource('pont',pointlist);

#endif
whichpoint--;

whichpoint=(whichpoint*(sizeof(Point)))+sizeof(long);

BlockMove((Ptr)((*theresource)+whichpoint),(Ptr)mypointpointer,(long)sizeof(Point));
}

/* This changes the pen size */
/* 	This is one of the places where it is easier to put your #ifdefs in one place,
	instead of many.  It forces you to remember a new function ( Pen() ) but 
	that's a small price to pay to untangle your code. */
/*	Inputs : 	Horizontal and Vertical size of pen */
/*	Outputs :	None 	*/
Pen(x,y)
int x;
int y;
{
	#ifdef MAC
	PenSize(x,y);
	#endif
	#ifdef GS
	SetPenSize(x,y);
	#endif
}

#ifdef GS
/* 	Here is an instance where the functionality of a Mac call has been duplicated 
	with a 'created' gs call.  Since the call or it's analog does not exsist on the 
	gs, we're free to create our own and make it do what we want, and we decrease
	confusion. */
/* GetPicture functions like the Mac getpicture */
/*	Inputs	: 	Resource ID of picture 	*/
/*	Output	: Handle	*/
PicHandle GetPicture(picnumber)
long picnumber;
{
	return((PicHandle)LoadResource(rPicture,picnumber));
}                                  
#endif




/* just a handy utility routine */
/* Inputs	: number to convert to text */
/*	Outputs	: none */
WriteNum(numtowrite)
int numtowrite;
{char fred[11];

#ifdef MAC
NumToString((long)numtowrite,&fred);
#endif
#ifdef GS
/* Of course this doesn't work for negative or fractional numbers */
/* but that would be only a little extra work. I leave it as an exercise for */
/* the student.... */
int counter;
counter=1;
while(((numtowrite)/(10*counter))>0){
counter++;
}

Int2Dec(numtowrite,fred+1,counter,0);


fred[0]=counter;
#endif
DrawString(fred);
	
	
	
}


#ifdef MAC
/* Check here to see if WaitNextEvent is available so we can be MultiFinder */
/* happy. */
Boolean TrapAvailable(tNumber,tType)
	short		tNumber;
	TrapType	tType;
{
	if ( ( tType == ToolTrap ) &&
		( myConfig.machineType > envMachUnknown ) &&
		( myConfig.machineType < envMacII ) ) {		/* it's a 512KE, Plus, or SE */
		tNumber = tNumber & 0x03FF;
		if ( tNumber > 0x01FF )					/* which means the tool traps */
			tNumber = _Unimplemented;			/* only go to 0x01FF */
	}
	return NGetTrapAddress(tNumber, tType) != GetTrapAddress(_Unimplemented);
} /*TrapAvailable*/



#endif
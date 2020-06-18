/* 	Menu handling routines */
/* 	Menu handling can be drastically different on the Mac and the GS
*  	The primary driver for the difference is in the TaskMaster mechanism on
*  	the GS.  TaskMaster eliminates the need for the application to call
*	either MenuSelect() or MenuKey(), TaskMaster returns the menu ID
*	and the Menu Item ID in the extended task record instead.
*	
*	There are two ways to deal with this.  The first is to ignore TaskMaster
*	completely, and use GetNextEvent() on the GS also.  If you follow this
*	method, then the code will be functionally idential to to Mac, with the
*	same call names and responses.
*	
*	However, that defeats the purpose of having TaskMaster() along.  So
*	here I'll describe how the code can still be made close to similar with
*	the Mac using GetNextEvent and the GS using TaskMaster.
	*/
#ifdef MAC
#include "paramac.h"
#endif
#ifdef GS
#include "parags.h"
#endif
#include "defines.h"
#include "global.h"
extern Handle MyMenuBar;
#ifdef Mac
extern MenuHandle applemenuhandle;
#endif
	
/* 	The Mac and the gs have a signifigant difference in the way they handle
	menu items.  The Mac menu items are relative, if it's the second item in the
	menu then it's menu item 2.  The gs menu item IDs are absolute.  If a menu
	item is defined in the resource as menu item 500, it will always be menu item
	500.
	So you have to make a decision, are you going to treat the gs menus like
	mac menus, or vice versa.  In this code I'll treat Mac menus like gs menus,
	so ReturnID will convert the Mac menu id into the cooresponding GS
	menu ID.   */
#ifdef MAC
/* The mMessage is passed to ReturnID() by FixEvent() */
/* Input : long message returned from MenuSelect or MenuKey */
/* Ouput : Boolean */
Boolean ReturnID(long mMessage)
{
	int loval,hival;
	Str255 DAname;
short ItemArray[3][10]={  	/* array of item ids for each menu.  Each ID corresponds to */
		{aboutitem,0,0,0,0,0,0,0,0,0},  /* the ID of the gs menu item */
		{newgameitem,0,0,quititem,0,0,0,0,0,0},  /* this structure grows and changes as  */
		{0,0,0,0,0,0,0,0,0,0},		/* you grow and change your menu bar. */
		
		
		
		};	

	
	loval=LoWord(mMessage);
	hival=HiWord(mMessage);
	/* The Apple Menu needs to be handled a little differently.  TaskMaster
	on the gs takes care of opening DA's, we'll of course do it manually on the
	Mac  */
	if((hival==applemenu)&&(loval!=1)){
		GetItem(applemenuhandle,loval,&DAname);
		OpenDeskAcc(DAname);    	
		HiliteMenu(false);
		return(false);}
	else{  /* if it was not a DA, then we change the Mac style menu and item ID */
		menuID=hival;   /* and put it in a convienient place */
		hival=hival-128;
		itemID=ItemArray[hival][loval-1];
		return(true);
		
		}
}
#endif

/* menu initialization is basically the same on both machines, both use
*   resources for the menus and the menu bar is created with one call. */
/* Inputs : none */
/* Ouputs : none */
StartMenus()
{
	#ifdef MAC
	MyMenuHandle=GetNewMBar (148);
	SetMenuBar(MyMenuHandle);
	applemenuhandle = GetMHandle(applemenu);
	AddResMenu (applemenuhandle,'DRVR');  /* and add the DA's */
	
	#endif
	#ifdef GS 
	MyMenuHandle=NewMenuBar2(2,1L,0L);
	SetSysBar(MyMenuHandle);
	SetMenuBar(0L);
	FixAppleMenu(1);  /* adds all the DA's to menu 1 */
	FixMenuBar();
	#endif
	DrawMenuBar();
}


#ifdef GS
/* Inputs : none */
/* Ouputs : Boolean */
Boolean ReturnID()   /* no input for the GS analogue, since MenuSelect has already been */
					 /*				called for this click by TaskMaster */
					/* All I'm doing here is moving the information returned by TaskMaster */
					/* from the TaskRecord to my own variables, so there will be more Mac/GS */
					/* symmetry */
{
	menuID=HiWord(ERecord.wmTaskData);
	itemID=LoWord(ERecord.wmTaskData);
	return(true);  /* If it got to here, it has to be true */
	
}
#endif
									
									
				
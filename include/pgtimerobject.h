/*
    ParaGUI - crossplatform widgetset
    Copyright (C) 2000 - 2009 Alexander Pipelka
 
    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.
 
    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.
 
    You should have received a copy of the GNU Library General Public
    License along with this library; if not, write to the Free
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 
    Alexander Pipelka
    pipelka@teleweb.at
 
    Last Update:      $Author: braindead $
    Update Date:      $Date: 2009/06/04 10:25:08 $
    Source File:      $Source: /sources/paragui/paragui/include/pgtimerobject.h,v $
    CVS/RCS Revision: $Revision: 1.1.2.6.2.10 $
    Status:           $State: Exp $
*/

/** \file pgtimerobject.h
	Header file for the PG_TimerObject class.
*/

#ifndef PG_TIMEROBJECT_H
#define PG_TIMEROBJECT_H

#include "paragui.h"
#include "pgsignals.h"
#include <map>


/**
	@author Alexander Pipelka
 
	@short A class to handle periodical timers
 
	This class encapsulates the SDL_AddTimer, SDL_RemoveTimer functions.
*/

class DECLSPEC PG_TimerObject {

public:

	typedef unsigned long ID;

	/**
	Signal type declaration
	**/
	template<class datatype = PG_Pointer>
class SignalTimer : public PG_Signal2<PG_TimerObject*, PG_TimerObject::ID, datatype> {}
	;

	/**
	Constructor of the PG_TimerObject class.
	The constructor also calls SDL_InitSubSystem(SDL_Timer) to enable
	the SDL timer subsystem.
	*/
	PG_TimerObject();

	virtual ~PG_TimerObject();

	/**
	Add a timer to the object.

	@param interval timer intervall in ms
	@return id of the timer

	You can add any number of timers to an object.
	After the timer-interval the virtual function eventTimer(PG_TimerObject::ID id, Uint32 interval)
	will be called
	*/
	PG_TimerObject::ID AddTimer(Uint32 interval);

	/**
	Remove a timer

	@param id id of the timer to remove
	*/
	bool RemoveTimer(PG_TimerObject::ID id);

	int SetTimer(Uint32 interval);

	void StopTimer();

	/**
	timer event handler

	@param id id of the elapsed timer
	@param interval timer interval
	@return should return the interval of the next timer event
	*/
	virtual Uint32 eventTimer(PG_TimerObject::ID id, Uint32 interval);

	virtual Uint32 eventTimer(Uint32 interval);

	SignalTimer<> sigTimer;

private:

	DLLLOCAL static Uint32 callbackTimer(Uint32 interval, void* data);

	DLLLOCAL static Uint32 callbackSingleTimer(Uint32 interval);

	static PG_TimerObject::ID globalTimerID;

	static std::map<PG_TimerObject::ID, PG_TimerObject*> timermap;

	static Uint32 objectcount;

	static PG_TimerObject* objSingleTimer;

	std::map<PG_TimerObject::ID, SDL_TimerID> my_timermap;

	SDL_mutex* my_lock;
};

#endif // PG_TIMEROBJECT_H

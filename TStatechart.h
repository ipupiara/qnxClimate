//
// Module Name:	TStatechart.hpp
//
// Description:	Template class for statechart engine.
//
// Copyright (c) 1994-2005 Grant D. Schultz.	All rights reserved.
//
//		
//
//		PN, 5. Nov 2005:
//
//      a description of this Framework you can find under
//
//		www.codeproject.com/samples/Statechart.asp
//
//		you need not understand this code, actually implementing a fsm is much simple
//
#if !defined(__TSTATECHART_HPP__)
#define __TSTATECHART_HPP__

#include <stdlib.h>
#include <string.h>
#include <assert.h>
//#pragma warning(push, 3)
//#pragma warning(disable : 4100)
//#pragma warning(disable : 4663)
//#pragma warning(disable : 4018)
//#pragma warning(disable : 4245)
//#pragma warning(disable : 4663)
#include <vector>
#include <algorithm>
//#pragma warning(pop)
#include "stdtype.h"


///////////////////////////////////////////////////////////////////////
// These are to be returned from event check methods.

				// Indicates no matching event found in event check method.
const uint32	u32NoMatch = 0x80000000,

				// To be returned at end of an event handler path, after
				// normal event handling.
				u32HandlingDone = 0x40000000;


///////////////////////////////////////////////////////////////////////
// These are to be passed into BEGIN_EVENT_HANDLER, OR'd onto the state
// name (if going to a different state).  Only one of these can be used
// at a time.

				// Indicates that a match to the event was found, but that
				// no transitions are to occur.  I.e., it's an internal
				// transition.
const uint32	u32NoStateChange = 0x20000000,

				// Indicates we should return to a state with history.
				u32WithHistory = 0x10000000;
				
///////////////////////////////////////////////////////////////////////

// This constant is used for removing all modifiers.
const uint32	u32AllMasks = (u32NoStateChange | u32WithHistory);


// Internal struct.
// An array of these is created by the template constructor, one
// for each state "declared" by the programmer.
typedef struct
{
	// Vector (starting with tree root) of all states leading down
	// the tree, ending with "me".
	std::vector<int32>	m_vi32Ancestry;

	bool				m_bIsSimpleState;

	// Holds the index of the substate most recently left.  If
	// we are to return to a child of this state with history, this is
	// the state to return to.  If this value is -1, then the state
	// hasn't been left, and thus, the default substate is the
	// one to return to.  If this node represents a simple state, this
	// member is meaningless.
	int32				m_i32HistoryReturnState;
} xInternalState;



// Instantiate this template with the class that makes use of the statechart
// engine.
template <class T> class TStatechart
{
	public:
		// Anyone using this template must declare an array of these,
		// filling in all relevant information.
		typedef struct
		{
			// These names must be enumerated values, and must have the
			// value of their location in the state array.
			int32	m_i32StateName;

			// state name of parent state; -1 if the state has no parent.
			int32	m_i32ParentStateName;

			// If this state encompasses others and one of them is to be the
			// default when this one is entered, put its name here.
			// -1 for none.
			int32	m_i32DefaultChildToEnter;

			// Pointers to the various methods that the engine can call.  Make
			// them 0 to indicate no such method exists.  (m_pfu32EventChecker
			// cannot be omitted.)
			uint32	(T::*m_pfu32EventChecker)(void);
			void	(T::*m_pfDefaultStateEntry)(void);
			void	(T::*m_pfEnteringState)(void);
			void	(T::*m_pfLeavingState)(void);
		} xStateType;

		// Special member functions.
		TStatechart(T& t, xStateType* const xaStates,
			const uint32 u32NumStates,
			const uint32 u32InitialState);

		virtual ~TStatechart();

		// When called, this method will call any event checking
		// methods it deems necessary to find a match.  If an event
		// match is found, it will call any exit and entry methods
		// to complete the state change.
		bool			processEvent(T& t);

		// Checks to see if the engine is in the specified state.  You
		// may specify a compound state.
		bool			inState(const uint32 u32State);

		// This method is to be called once a match is found, and
		// must come before any "actions" on the event arrow.
		void			beginEventAction(T& t, uint32 u32NextState,
							uint32& u32LastStateExited);

		// This method is to be called after an event handler
		// method's "action" section.
		void			endEventAction(T& t, uint32 u32NextState,
							uint32 u32LastStateExited);

	private:
		const uint32		m_u32NumStates;

		const xStateType	*m_pxaUserStateDefns;

		uint32				m_u32CurrentState;
		xInternalState		*m_xaStateData;

		// Holds the list of states we are exiting as we check
		// for events.
		std::vector<uint32> m_vu32exitingStates;

		// If -1, the array m_i32ExitingStates is not in use.
		// Otherwise, it's the index of the last used slot.
		int32				m_i32ExitingStatesIndex;

		uint32	enterDestinationState(T& t, const uint32 u32NewState,
					const bool bWithHistory,
					const uint32 u32IndexOfFirstStateToEnter);
		void	generateAncestries(void);
		void	initHistoryReturns(void);
		void	setInitialState(T& t, uint32 u32InitialState);
		void	verifyStateNames(void);

	private:
		// Prevent access to this one.
		TStatechart();
		bool	stateIsAncestorOf(int32 i32Ancestor, uint32 u32Child);

		// Don't allow access to this.
		TStatechart& operator=(const TStatechart& t);
};



#define CREATE_ENGINE(class, engine_name, state_array, num_states, start_state)	\
	engine_name = NULL;															\
	engine_name = new TStatechart<class>										\
			(*this, state_array, num_states, start_state);						\
	assert(NULL != engine_name);



#define DESTROY_ENGINE(class, engine_name)						\
	assert(NULL != engine_name);								\
	delete static_cast<TStatechart<class> *>(engine_name);



#define PROCESS_EVENT(class_name, engine_name)					\
	static_cast<TStatechart<class_name> *>						\
		(engine_name)->processEvent(*this)



#define IN_STATE(class_name, engine_name, state_to_test_for)	\
	static_cast<TStatechart<class_name> *>						\
		(engine_name)->inState(state_to_test_for)



#define BEGIN_EVENT_HANDLER(class_name, engine_name, state_and_flags)	\
{																		\
	uint32	u32LastStateExited_##engine_name;							\
	uint32	u32State_and_flags_##engine_name = state_and_flags;			\
	static_cast<TStatechart<class_name> *>(engine_name)->				\
		beginEventAction(*this,											\
		(state_and_flags), u32LastStateExited_##engine_name)



#define END_EVENT_HANDLER(class_name, engine_name)						\
	static_cast<TStatechart<class_name> *>(engine_name)->				\
		endEventAction(*this, u32State_and_flags_##engine_name,			\
			u32LastStateExited_##engine_name);							\
}



template<class T>
TStatechart<T>::~TStatechart()
{
	delete [] m_xaStateData;
}



//
// Name:	TStatechart
//
// Desc.:	Creates the internal structures for representing the
//			statechart.
//
// In:		t, the object to drive via the engine.
//			xaStates, the user's array of state defn's.
//			u32NumStates, the number the caller is working with.
//			u32InitialState, the name (index) of the initial state,
//			(need not be a simple state).
//
template<class T>
TStatechart<T>::TStatechart(T& t, xStateType* const xaStates,
	const uint32 u32NumStates, const uint32 u32InitialState) :
	m_u32NumStates(u32NumStates), m_pxaUserStateDefns(xaStates)
{
	// The constructor for this class will do the following error
	// checking on the array of states passed in:
	//	 1.	Ensure that if a state is specified as having a parent,
	//		 that the parent does indeed exist.
	//	 2.	If there is a circular reference of states and their
	//		 parents, the constructor to fail.
	//	 3.	Check to see that a state is not its own parent.
	//	 4.	Ensure that the names of states match their indices.
	//	 5.	Ensure that a state is not its own default substate.
	//	 6.	Ensure that the starting state is either 1) a simple state,
	//		 or 2) that the starting state has default substates,
	//		 eventually leading to a simple state.
	//	 7.	Ensure that there is at least one state passed in.

	// Failure indicates no states passed in.
	assert(0 != m_u32NumStates);

	m_xaStateData = new xInternalState[m_u32NumStates];
	verifyStateNames();
	generateAncestries();
	initHistoryReturns();
	setInitialState(t, u32InitialState);

	m_i32ExitingStatesIndex = -1;

#if defined (TESTING)
	cout << endl << flush;
	for (int32 i=0; i<m_u32NumStates; i++)
	{
		for (int32 j=0; j<m_xaStateData[i].vu32ancestry.size(); j++)
		{
			cout << m_xaStateData[i].vu32ancestry[j] << flush;
			cout << "	" << flush;
		}
		cout << "\t; is_simple? "
			<< (m_xaStateData[i].m_bIsSimpleState ? "Yes" : "No")
			<< endl << flush;
	}
	cout << endl << flush;
	cout << "current (initial) state is :" << m_u32CurrentState << endl
		<< flush;
#endif
}


//
// Name:	verifyStateNames
//
// Desc.:	Verifies that the creator of the states followed the
//			rules for indexing, etc.
//
template<class T>
void TStatechart<T>::verifyStateNames(void)
{
	for (uint32 u=0; u!=m_u32NumStates; u++)
	{
		// Failure indicates that a state does not have a name
		// which represents its index in the state array.
		assert(m_pxaUserStateDefns[u].m_i32StateName == static_cast<int32>(u));

		// Failure indicates that a state is its own parent.
		assert(m_pxaUserStateDefns[u].m_i32StateName !=
			m_pxaUserStateDefns[u].m_i32ParentStateName);

		// Failure indicates that a specified
		// parent has an invalid index.
		assert(m_pxaUserStateDefns[u].m_i32ParentStateName <
			(int32)m_u32NumStates);

		// Failure indicates that a specified
		// default child has an invalid index.
		assert(m_pxaUserStateDefns[u].m_i32DefaultChildToEnter <
			(int32)m_u32NumStates);

		// Failure indicates that a state has specified
		// itself as the default substate.
		assert(m_pxaUserStateDefns[u].m_i32StateName !=
			m_pxaUserStateDefns[u].m_i32DefaultChildToEnter);
	}
}


//
// Name:	generateAncestries
//
// Desc.:	For each state, generates a local (to that state) copy
//			of that state's complete ancestry.
//
template<class T>
void TStatechart<T>::generateAncestries(void)
{
	uint32		u32StateBeingProcessed,
				u32CurrentAncestor;

	// Set all simple flags to true, and reset them in a subsequent
	// loop, as we prove that a state is not simple.
	for (u32StateBeingProcessed=0;
		u32StateBeingProcessed<m_u32NumStates;
			u32StateBeingProcessed++)
	{
		m_xaStateData[u32StateBeingProcessed].m_bIsSimpleState = true;
	}

	for (u32StateBeingProcessed=0;
		u32StateBeingProcessed<m_u32NumStates;
			u32StateBeingProcessed++)
	{
		// Generate the tree for m_pxaUserStateDefns[u32StateBeingProcessed].
		m_xaStateData[u32StateBeingProcessed].m_vi32Ancestry.
			insert(m_xaStateData[u32StateBeingProcessed].m_vi32Ancestry.begin(),
				u32StateBeingProcessed);

		u32CurrentAncestor = u32StateBeingProcessed;
		// Generate the list of parents.
		while (-1 != m_pxaUserStateDefns[u32CurrentAncestor].
			m_i32ParentStateName)
		{
			m_xaStateData[u32StateBeingProcessed].
				m_vi32Ancestry.insert(
					m_xaStateData[u32StateBeingProcessed].m_vi32Ancestry.begin(), 
					m_pxaUserStateDefns[u32CurrentAncestor].m_i32ParentStateName
				);

			u32CurrentAncestor = m_pxaUserStateDefns[u32CurrentAncestor].
				m_i32ParentStateName;

			// Because state [u32CurrentAncestor] is the parent of
			// someone, it can't be a simple state.  By "checking them
			// off" here, we set to false all those that aren't leaves.
			m_xaStateData[u32CurrentAncestor].m_bIsSimpleState = false;
			assert(u32CurrentAncestor < m_u32NumStates);
		}
	}
}


//
// Name:	initHistoryReturns
//
// Desc.:	Sets each state's history return value to -1, since upon
//			constructing the class, no state switching has taken place.
//
template<class T>
void TStatechart<T>::initHistoryReturns(void)
{
	uint32		u32StateBeingProcessed;

	for (u32StateBeingProcessed=0;
		u32StateBeingProcessed<m_u32NumStates;
			u32StateBeingProcessed++)
	{
		m_xaStateData[u32StateBeingProcessed].m_i32HistoryReturnState = -1;
	}
}


//
// Name:	setInitialState
//
// Desc.:	Sets the initial state of the statechart (which may not
//			be a simple state).  Executes any entry methods or default
//			entry methods needed.
//
// In:		t, the object to drive via the engine.
//			u32InitialState, the first state.
//
template<class T>
void TStatechart<T>::setInitialState(T& t, uint32 u32InitialState)
{
	// Enter the state we were given.
	if (NULL != m_pxaUserStateDefns[u32InitialState].m_pfEnteringState)
	{
		(t.*m_pxaUserStateDefns[u32InitialState].m_pfEnteringState)();
	}

	// Set this here in case there are no sub-states.
	m_u32CurrentState = u32InitialState;

	// If we were given a state with default children,
	// enter them until there aren't any more.
	int32	i32ChildToEnter = m_pxaUserStateDefns[u32InitialState].
		m_i32DefaultChildToEnter;

	while (-1 != i32ChildToEnter)
	{
		if (NULL != m_pxaUserStateDefns[i32ChildToEnter].
			m_pfDefaultStateEntry)
		{
			(t.*m_pxaUserStateDefns[i32ChildToEnter].
				m_pfDefaultStateEntry)();
		}
		if (NULL != m_pxaUserStateDefns[i32ChildToEnter].m_pfEnteringState)
		{
			(t.*m_pxaUserStateDefns[i32ChildToEnter].m_pfEnteringState)();
		}

		// At this point, we have just "entered" a valid state.  If we
		// fall out of the loop, we want the "current" state to be
		// recorded here.
		m_u32CurrentState = i32ChildToEnter;

		i32ChildToEnter = m_pxaUserStateDefns[i32ChildToEnter].
			m_i32DefaultChildToEnter;
	}

	// Failure implies that the initial state was not a simple
	// state, or that it didn't have default substates
	// leading to a simple state.
	assert(m_xaStateData[m_u32CurrentState].m_bIsSimpleState);

#if defined (TESTING)
	cout << "Initial state set to "
		<< m_u32CurrentState
		<< ".\n";
#endif
}


//
// Name:	processEvent
//
// Desc.:	The method that drives the statechart, calling event
//			checking methods looking for a match, and if one is
//			found, calls all of the exit and entry methods
//			involved in changing states.
//
// In:		t, the object to drive via the engine.
//
// Returns:	true if a match was found, false otherwise.
//
template<class T>
bool TStatechart<T>::processEvent(T& t)
{
	uint32	u32result;			 // Result of calling event check method.

	int32	i32StateBeingTried;
	bool	bMatchFound;

	m_i32ExitingStatesIndex = -1;
	m_vu32exitingStates.clear();

	bMatchFound = false;
	i32StateBeingTried = m_u32CurrentState;
	while ((-1 != i32StateBeingTried) && (!bMatchFound))
	{

#if defined (TESTING)
		cout << "About to look for a match from inside state "
			<< i32StateBeingTried
			<< ".\n";
#endif

		// Capture a state we may exit from.
		m_vu32exitingStates.insert(m_vu32exitingStates.end(), static_cast<uint32>(i32StateBeingTried));

		m_i32ExitingStatesIndex++;
		
		// Failure indicates that an event checking method was NULL.
		assert(NULL != m_pxaUserStateDefns[i32StateBeingTried].m_pfu32EventChecker);

		u32result = (t.*m_pxaUserStateDefns[i32StateBeingTried].m_pfu32EventChecker)();
		bMatchFound = (0 == (u32result & u32NoMatch));

#if defined (TESTING)
		if (bMatchFound)
		{
			cout << "Match found from within state "
				<< i32StateBeingTried
				<< ".\n";
		}
#endif

		// A failure implies that more than one
		// mask was OR'red onto the return state.
		assert(0 == ((u32result & u32AllMasks) & ((u32result & u32AllMasks) - 1)));

		i32StateBeingTried = m_pxaUserStateDefns[i32StateBeingTried].
			m_i32ParentStateName;
	}
	// When we exit this loop, we have either found an event
	// handler that recognized the event, and have completely
	// transitioned to the destination state, or we have
	// exhausted the set of states from which an event handler
	// could have been found.

	return (bMatchFound);
}


//
// Name:	beginEventAction
//
// Desc.:	Called from user's code when their event handler method
//			recognizes an event match.  This method should be the first
//			thing called from within the body of that action handler.
//			This method causes all state exits to be performed, in
//			preparation for the user to perform their actions defined on
//			the event arrow itself.
//
// In:		t, the object to drive via the engine.
//			u32DestStateAndFlags, the destination state and any
//			modifying flags like "history".
//
//	Out:	u32LastStateExited, tracks the last state we exited;
//			needed for performing correct state re-entries later.
//
template<class T>
void TStatechart<T>::beginEventAction(T& t, uint32 u32DestStateAndFlags,
	uint32& u32LastStateExited)
{
	// A failure implies that the next state
	// we're to switch to is invalid.
	assert((u32DestStateAndFlags & (~u32AllMasks)) < m_u32NumStates);

	int32	u32DestState = static_cast<uint32>
		(u32DestStateAndFlags & (~u32AllMasks));

	if (u32NoStateChange == u32DestStateAndFlags)
	{
		// Reset the index, since we won't be exiting any states.
		m_i32ExitingStatesIndex = -1;

		return;
	}

	// Exit from the states that we have to leave to get to the
	// level at which the event was recognized.
	int32	u32StateBeingLeft = 0xffffffff;
	for (int i=0; i<=m_i32ExitingStatesIndex; i++)
	{
		// Exit from state i.
		u32StateBeingLeft = m_vu32exitingStates[i];

		// Failure implies that we captured a bad state index.
		assert((u32StateBeingLeft >= 0) && (u32StateBeingLeft < m_u32NumStates));

		if (NULL != m_pxaUserStateDefns[u32StateBeingLeft].m_pfLeavingState)
		{
			(t.*m_pxaUserStateDefns[u32StateBeingLeft].m_pfLeavingState)();
		}
		u32LastStateExited = u32StateBeingLeft;

		// Save history return info.
		m_xaStateData[m_pxaUserStateDefns[u32StateBeingLeft].
			m_i32ParentStateName].m_i32HistoryReturnState =
			u32StateBeingLeft;
	}

	// Now, we must exit from any further states required to get to
	// the level at which we can begin entering states.
	//
	// u32StateBeingLeft was the last one we left (above).
	assert(-1 != u32StateBeingLeft);

	// Go up the tree one more level.
	u32StateBeingLeft = m_pxaUserStateDefns[u32StateBeingLeft].m_i32ParentStateName;

	// Exit states until we're about to leave the ancestor state of
	// our original state that is also an ancestor of the dest state.
	while ((-1 != u32StateBeingLeft) &&
		(!stateIsAncestorOf(u32StateBeingLeft, u32DestState)))
	{
		if (NULL != m_pxaUserStateDefns[u32StateBeingLeft].m_pfLeavingState)
		{
			(t.*m_pxaUserStateDefns[u32StateBeingLeft].m_pfLeavingState)();
		}
		u32LastStateExited = u32StateBeingLeft;

		u32StateBeingLeft =
			m_pxaUserStateDefns[u32StateBeingLeft].m_i32ParentStateName;

		// Save history return info.
		m_xaStateData[m_pxaUserStateDefns[u32StateBeingLeft].
			m_i32ParentStateName].m_i32HistoryReturnState =
			u32StateBeingLeft;
	}

	// Now, cover one last case:  the case where the dest state _is_
	// the one we were about to exit.  If so, exit it also.
	if (u32StateBeingLeft == u32DestState)
	{
		if (NULL != m_pxaUserStateDefns[u32StateBeingLeft].m_pfLeavingState)
		{
			(t.*m_pxaUserStateDefns[u32StateBeingLeft].m_pfLeavingState)();
		}
		u32LastStateExited = u32StateBeingLeft;
		
		m_xaStateData[m_pxaUserStateDefns[u32StateBeingLeft].
			m_i32ParentStateName].m_i32HistoryReturnState =
			u32StateBeingLeft;
	}
	// At this point, we have exited all states that we will
	// have to exit.  Return so the calling event check method
	// can perform its action handling.

	return;
}


//
// Name:	endEventAction
//
// Desc.:	To be called as the last thing inside the caller's method
//			that handles this event.  Calls methods to effect re-entry
//			into the appropriate states.
//
// In:		t, the object to drive via the engine.
//			u32DestStateAndFlags, the destination state and any
//			modifying flags like "history".	MUST MATCH the value
//			passed into BeginEventAction for the same event handler.
//			u32LastStateExited, must be the value passed back in the
//			corresponding BeginEventAction call.
//
template<class T>
void TStatechart<T>::endEventAction(T& t, uint32 u32DestStateAndFlags,
	uint32 u32LastStateExited)
{
	if (u32NoStateChange == u32DestStateAndFlags)
	{
		return;
	}

	// Perform all state entries to get to the destination state.
	uint32	u32DestState = static_cast<uint32>
		(u32DestStateAndFlags & (~u32AllMasks));

	int32	i32IndexOfFirstStateToEnter = -1;

	if (stateIsAncestorOf(u32LastStateExited, u32DestState))
	{
		// ...then start re-entry at u32LastStateExited
		// (in the ancestry of u32DestState).

		// I.e., loop through the ancestry of the destination state,
		// and pick out the index into the ancestry of where the 
		// state u32LastStateExited is found.
		for (uint32 u=0; u<m_xaStateData[u32DestState].m_vi32Ancestry.size(); u++)
		{
			if (m_xaStateData[u32DestState].m_vi32Ancestry[u] ==
				static_cast<int32>(u32LastStateExited))
			{
				i32IndexOfFirstStateToEnter = u;
				break;
			}
		}
	}
	else
	{
		// Otherwise, start re-entry at spot one state below
		// where the two ancestries meet.  So, find where they
		// first diverge.

		// First we must compute the value for the loop test.
		int32	i32MaxIndex;
		if (m_xaStateData[u32DestState].m_vi32Ancestry.size() >
			m_xaStateData[u32LastStateExited].m_vi32Ancestry.size())
		{
			i32MaxIndex = m_xaStateData[u32LastStateExited].m_vi32Ancestry.size() - 1;
		}
		else
		{
			i32MaxIndex = m_xaStateData[u32DestState].m_vi32Ancestry.size() - 1;
		}

		for (int32 i=0; i<=i32MaxIndex; i++)
		{
			// Do this assigment each time, so no matter how the
			// loop terminates (for loop exceeding index or finding
			// a difference in ancestry), we get our index
			// initialized.
			i32IndexOfFirstStateToEnter = i;

			if (m_xaStateData[u32LastStateExited].m_vi32Ancestry[i] !=
				m_xaStateData[u32DestState].m_vi32Ancestry[i])
			{
				// Indicates a logic failure; the first element
				// of every ancestry should be the global state.
				assert(0 != i);
				
				break;
			}
		}
	}

	// Failure indicates a logic problem.  We should always
	// find the state, since u32LastStateExited is an
	// ancestor of the destination state.
	assert(-1 != i32IndexOfFirstStateToEnter);
	
	m_u32CurrentState = enterDestinationState(t,
		u32DestState,
		0 != (u32DestStateAndFlags & u32WithHistory),
		i32IndexOfFirstStateToEnter);

	return;
}


//
// Name:	enterDestinationState
//
// Desc.:	Enters states, using history information if requested,
//			and default child information if necessary to reach
//			a simple state.
//
// In:		t, the object to drive via the engine.
//			u32NewState, the state we're destined for (can be a
//			composite state).
//			bWithHistory, true if we're supposed to enter a state
//			with history.
//			u32IndexOfFirstStateToEnter, the index (in the
//			ancestry of the destination state) of the first state
//			we are supposed to enter.
//
// Returns:	the new simple state's name.
//
template<class T>
uint32 TStatechart<T>::enterDestinationState(T& t,
	const uint32 u32NewState, const bool bWithHistory,
	const uint32 u32IndexOfFirstStateToEnter)
{
	uint32	u;

	// Enter states until we're at our given destination.
	u = u32IndexOfFirstStateToEnter;
	do
	{
		if (NULL != m_pxaUserStateDefns[m_xaStateData[u32NewState].
			m_vi32Ancestry[u]].m_pfEnteringState)
		{
			(t.*m_pxaUserStateDefns[m_xaStateData[u32NewState].
				m_vi32Ancestry[u]].m_pfEnteringState)();
		}
		u++;
	}
	while (u <= m_xaStateData[u32NewState].m_vi32Ancestry.size() - 1);

	// At this point, we've entered the state requested.  Now,
	// we must enter lower states with history, if requested.
	uint32		u32StateTransitionallyIn = u32NewState;
	if (bWithHistory)
	{
		while (-1 != m_xaStateData[u32StateTransitionallyIn].
			m_i32HistoryReturnState)
		{
			u32StateTransitionallyIn =
				m_xaStateData[u32StateTransitionallyIn].
					m_i32HistoryReturnState;
			if (NULL != m_pxaUserStateDefns[u32StateTransitionallyIn].
				m_pfEnteringState)
			{
				(t.*m_pxaUserStateDefns[u32StateTransitionallyIn].
					m_pfEnteringState)();
			}
		}
	}
	// At this point, we're in the state "u32StateTransitionallyIn".

	// Now, if we're not in a simple state yet,
	// follow default children until we are.
	while (!m_xaStateData[u32StateTransitionallyIn].m_bIsSimpleState)
	{
		if (-1 != m_pxaUserStateDefns[u32StateTransitionallyIn].
			m_i32DefaultChildToEnter)
		{
			u32StateTransitionallyIn =
				m_pxaUserStateDefns[u32StateTransitionallyIn].
				m_i32DefaultChildToEnter;
			if (NULL != m_pxaUserStateDefns[u32StateTransitionallyIn].
				m_pfDefaultStateEntry)
			{
				(t.*m_pxaUserStateDefns[u32StateTransitionallyIn].
					m_pfDefaultStateEntry)();
			}
			if (NULL != m_pxaUserStateDefns[u32StateTransitionallyIn].
				m_pfEnteringState)
			{
				(t.*m_pxaUserStateDefns[u32StateTransitionallyIn].
					m_pfEnteringState)();
			}
		}
		else
		{
			// Failure indicates that the caller specified a
			// destination state that didn't have default
			// children leading to a simple state.
			assert(false);
		}
	}
	return (u32StateTransitionallyIn);
}


//
// Name:	stateIsAncestorOf
//
// Desc.:	Decides if a state is an ancestor of another state.
//
// In:		u32ancestor, the ancestor to test against.
//			u32Child, the potential descendant state.
//
// Returns:	True if the child is a descendant of the ancestor.
//
template<class T>
bool TStatechart<T>::stateIsAncestorOf(int32 i32Ancestor, uint32 u32Child)
{
	bool	bInAncestry = false;

	for (int32 i=m_xaStateData[u32Child].m_vi32Ancestry.size() - 1; i>=0; i--)
	{
		if (i32Ancestor == m_xaStateData[u32Child].m_vi32Ancestry[i])
		{
			bInAncestry = true;
		}
	}

	return (bInAncestry);
}


//
// Name:	inState
//
// Desc.:	Tells if the statechart is in the given state (can be a
//			simple or composite state).
//
// In:		u32State, the state being queried.
//
// Returns:	true if we're in it, false otherwise.
//
template<class T>
bool TStatechart<T>::inState(const uint32 u32State)
{
	int32	i;

	if (u32State == m_u32CurrentState)
	{
		return (true);
	}
	for (i=m_xaStateData[m_u32CurrentState].m_vi32Ancestry.size() - 1; i>=0; i--)
	{
		if (u32State == static_cast<uint32>(m_xaStateData[m_u32CurrentState].m_vi32Ancestry[i]))
		{
			return (true);
		}
	}
	return (false);
}

#endif	// TStatechart file include guard.

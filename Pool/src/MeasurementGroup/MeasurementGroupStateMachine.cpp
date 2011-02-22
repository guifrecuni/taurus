//+=============================================================================
//
// file :         MeasurementGroupStateMachine.cpp
//
// description :  C++ source for the MeasurementGroup and its alowed. 
//                method for commands and attributes
//
// project :      TANGO Device Server
//
// $Author$
//
// $Revision$
//
// $Log$
// Revision 1.9  2007/08/30 12:40:39  tcoutinho
// - changes to support Pseudo counters.
//
// Revision 1.8  2007/08/24 15:55:26  tcoutinho
// safety weekend commit
//
// Revision 1.7  2007/04/30 15:47:05  tcoutinho
// - new attribute "Channels"
// - new device property "Channel_List"
// - when add/remove channel, pool sends a change event on the MeasurementGroupList
//
// Revision 1.6  2007/04/23 15:17:59  tcoutinho
// - changes according to Sardana metting 26-03-2007: identical measurement groups can be created, Add/Remove  Exp. channel from a MG, etc
//
// Revision 1.5  2007/04/03 07:17:05  tcoutinho
// - following decision made on Sardana metting 26-03-2007, the save config feature will not be implemented on a measurement group basis.
//
// Revision 1.4  2007/02/28 16:21:52  tcoutinho
// - support for 0D channels
// - basic fixes after running first battery of tests on measurement group
//
// Revision 1.3  2007/02/16 10:00:49  tcoutinho
// - start is not allowed if moving
//
// Revision 1.2  2007/02/08 10:50:19  etaurel
// - Some small changes after the merge
//
// Revision 1.1  2007/02/03 15:20:39  tcoutinho
// - new Measurement Group Tango device
//
//
// copyleft :     European Synchrotron Radiation Facility
//                BP 220, Grenoble 38043
//                FRANCE
//
//-=============================================================================
//
//  		This file is generated by POGO
//	(Program Obviously used to Generate tango Object)
//
//         (c) - Software Engineering Group - ESRF
//=============================================================================

#include "MeasurementGroup.h"
#include "MeasurementGroupClass.h"
#include <tango.h>

/*====================================================================
 *	This file contains the methods to allow commands and attributes
 * read or write execution.
 *
 * If you wand to add your own code, add it between 
 * the "End/Re-Start of Generated Code" comments.
 *
 * If you want, you can also add your own methods.
 *====================================================================
 */

namespace MeasurementGroup_ns
{

//=================================================
//		Attributes Allowed Methods
//=================================================

//+----------------------------------------------------------------------------
//
// method : 		MeasurementGroup::is_Integration_time_allowed
// 
// description : 	Read/Write allowed for Integration_time attribute.
//
//-----------------------------------------------------------------------------
bool MeasurementGroup::is_Integration_time_allowed(Tango::AttReqType type)
{
	if (get_state() == Tango::UNKNOWN)
	{
		//	End of Generated Code

		//	Re-Start of Generated Code
		return false;
	}
	return true;
}
//+----------------------------------------------------------------------------
//
// method : 		MeasurementGroup::is_Integration_count_allowed
// 
// description : 	Read/Write allowed for Integration_count attribute.
//
//-----------------------------------------------------------------------------
bool MeasurementGroup::is_Integration_count_allowed(Tango::AttReqType type)
{
	if (get_state() == Tango::UNKNOWN)
	{
		//	End of Generated Code

		//	Re-Start of Generated Code
		return false;
	}
	return true;
}
//+----------------------------------------------------------------------------
//
// method : 		MeasurementGroup::is_Timer_allowed
// 
// description : 	Read/Write allowed for Timer attribute.
//
//-----------------------------------------------------------------------------
bool MeasurementGroup::is_Timer_allowed(Tango::AttReqType type)
{
	if (get_state() == Tango::UNKNOWN)
	{
		//	End of Generated Code

		//	Re-Start of Generated Code
		return false;
	}
	return true;
}
//+----------------------------------------------------------------------------
//
// method : 		MeasurementGroup::is_Monitor_allowed
// 
// description : 	Read/Write allowed for Monitor attribute.
//
//-----------------------------------------------------------------------------
bool MeasurementGroup::is_Monitor_allowed(Tango::AttReqType type)
{
	if (get_state() == Tango::UNKNOWN)
	{
		//	End of Generated Code

		//	Re-Start of Generated Code
		return false;
	}
	return true;
}
//+----------------------------------------------------------------------------
//
// method : 		MeasurementGroup::is_ZeroDExpChannels_allowed
// 
// description : 	Read/Write allowed for ZeroDExpChannels attribute.
//
//-----------------------------------------------------------------------------
bool MeasurementGroup::is_ZeroDExpChannels_allowed(Tango::AttReqType type)
{
	if (get_state() == Tango::UNKNOWN)
	{
		//	End of Generated Code

		//	Re-Start of Generated Code
		return false;
	}
	return true;
}
//+----------------------------------------------------------------------------
//
// method : 		MeasurementGroup::is_OneDExpChannels_allowed
// 
// description : 	Read/Write allowed for OneDExpChannels attribute.
//
//-----------------------------------------------------------------------------
bool MeasurementGroup::is_OneDExpChannels_allowed(Tango::AttReqType type)
{
	if (get_state() == Tango::UNKNOWN)
	{
		//	End of Generated Code

		//	Re-Start of Generated Code
		return false;
	}
	return true;
}
//+----------------------------------------------------------------------------
//
// method : 		MeasurementGroup::is_TwoDExpChannels_allowed
// 
// description : 	Read/Write allowed for TwoDExpChannels attribute.
//
//-----------------------------------------------------------------------------
bool MeasurementGroup::is_TwoDExpChannels_allowed(Tango::AttReqType type)
{
	if (get_state() == Tango::UNKNOWN)
	{
		//	End of Generated Code

		//	Re-Start of Generated Code
		return false;
	}
	return true;
}
//+----------------------------------------------------------------------------
//
// method : 		MeasurementGroup::is_Counters_allowed
// 
// description : 	Read/Write allowed for Counters attribute.
//
//-----------------------------------------------------------------------------
bool MeasurementGroup::is_Counters_allowed(Tango::AttReqType type)
{
	if (get_state() == Tango::UNKNOWN)
	{
		//	End of Generated Code

		//	Re-Start of Generated Code
		return false;
	}
	return true;
}

//+----------------------------------------------------------------------------
//
// method : 		MeasurementGroup::is_PseudoCounters_allowed
// 
// description : 	Read/Write allowed for Counters attribute.
//
//-----------------------------------------------------------------------------
bool MeasurementGroup::is_PseudoCounters_allowed(Tango::AttReqType type)
{
	if (get_state() == Tango::UNKNOWN)
	{
		//	End of Generated Code

		//	Re-Start of Generated Code
		return false;
	}
	return true;
}

//+----------------------------------------------------------------------------
//
// method : 		MeasurementGroup::is_Channels_allowed
// 
// description : 	Read/Write allowed for Counters attribute.
//
//-----------------------------------------------------------------------------
bool MeasurementGroup::is_Channels_allowed(Tango::AttReqType type)
{
	if (get_state() == Tango::UNKNOWN)
	{
		//	End of Generated Code

		//	Re-Start of Generated Code
		return false;
	}
	return true;
}

//+----------------------------------------------------------------------------
//
// method : 		MeasurementGroup::is_Motors_allowed
// 
// description : 	Read/Write allowed for Counters attribute.
//
//-----------------------------------------------------------------------------
bool MeasurementGroup::is_Motors_allowed(Tango::AttReqType type)
{
	if (get_state() == Tango::UNKNOWN)
	{
		//	End of Generated Code

		//	Re-Start of Generated Code
		return false;
	}
	return true;
}

//=================================================
//		Commands Allowed Methods
//=================================================

//+----------------------------------------------------------------------------
//
// method : 		MeasurementGroup::is_Start_allowed
// 
// description : 	Execution allowed for Start command.
//
//-----------------------------------------------------------------------------
bool MeasurementGroup::is_Start_allowed(const CORBA::Any &any)
{
	if (get_state() == Tango::MOVING	||
		get_state() == Tango::FAULT	||
		get_state() == Tango::ALARM	||
		get_state() == Tango::UNKNOWN)
	{
		//	End of Generated Code

		//	Re-Start of Generated Code
		return false;
	}
	return true;
}
//+----------------------------------------------------------------------------
//
// method : 		MeasurementGroup::is_Abort_allowed
// 
// description : 	Execution allowed for Abort command.
//
//-----------------------------------------------------------------------------
bool MeasurementGroup::is_Abort_allowed(const CORBA::Any &any)
{
		//	End of Generated Code

		//	Re-Start of Generated Code
	return true;
}
//+----------------------------------------------------------------------------
//
// method : 		MeasurementGroup::is_AddExpChannel_allowed
// 
// description : 	Execution allowed for AddExpChannel command.
//
//-----------------------------------------------------------------------------
bool MeasurementGroup::is_AddExpChannel_allowed(const CORBA::Any &any)
{
	if (get_state() == Tango::MOVING	||
		get_state() == Tango::FAULT	||
		get_state() == Tango::UNKNOWN)
	{
		//	End of Generated Code

		//	Re-Start of Generated Code
		return false;
	}
	return true;
}
//+----------------------------------------------------------------------------
//
// method : 		MeasurementGroup::is_RemoveExpChannel_allowed
// 
// description : 	Execution allowed for RemoveExpChannel command.
//
//-----------------------------------------------------------------------------
bool MeasurementGroup::is_RemoveExpChannel_allowed(const CORBA::Any &any)
{
	if (get_state() == Tango::MOVING	||
		get_state() == Tango::FAULT	||
		get_state() == Tango::UNKNOWN)
	{
		//	End of Generated Code

		//	Re-Start of Generated Code
		return false;
	}
	return true;
}

}	// namespace MeasurementGroup_ns

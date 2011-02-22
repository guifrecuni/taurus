//=============================================================================
//
// file :        CTExpChannel.h
//
// description : Include for the CTExpChannel class.
//
// project :	CounterTimerExperimentChannel
//
// $Author$
//
// $Revision$
//
// $Log$
// Revision 1.10  2007/08/30 12:40:39  tcoutinho
// - changes to support Pseudo counters.
//
// Revision 1.9  2007/08/17 13:07:29  tcoutinho
// - pseudo motor restructure
// - pool base dev class restructure
// - initial commit for pseudo counters
//
// Revision 1.8  2007/07/26 07:05:42  tcoutinho
// fix bug 10 : Change all tango commands from Stop to Abort
//
// Revision 1.7  2007/05/25 12:48:10  tcoutinho
// fix the same dead locks found on motor system to the acquisition system since release labeled for Josep Ribas
//
// Revision 1.6  2007/05/22 13:43:09  tcoutinho
// - added new method
//
// Revision 1.5  2007/02/16 10:02:42  tcoutinho
// - new method to set the state coming from a measurement group (maybe in the future move it to the super class)
//
// Revision 1.4  2007/01/30 15:56:28  etaurel
// - Fix some memory leaks
// - Value is now a Double attribute
//
// Revision 1.3  2007/01/16 16:50:04  etaurel
// - It's now possible to write the Value attribute
//
// Revision 1.2  2007/01/16 14:23:19  etaurel
// - First release with Counter Timer
//
// Revision 1.1  2007/01/05 15:03:15  etaurel
// - First implementation of the Counter Timer class
//
//
// copyleft :   CELLS/ALBA
//		Edifici Ciences Nord
//		Campus Universitari de Bellaterra
//		Universitat Autonoma de Barcelona
//		08193 Bellaterra, Barcelona, SPAIN
//
//=============================================================================
//
//  		This file is generated by POGO
//	(Program Obviously used to Generate tango Object)
//
//=============================================================================
#ifndef _CTEXPCHANNEL_H
#define _CTEXPCHANNEL_H

#include "PoolIndBaseDev.h"

namespace Pool_ns
{
    struct CTExpChannelPool;
}

/**
 * @author	$Author$
 * @version	$Revision$
 */

 //	Add your own constants definitions here.
 //-----------------------------------------------

/**
 * @namespace CTExpChannel_ns
 *
 * @brief The namespace for the Counter/Timer Experiment channel (CTExpChannel) tango class.
 * 
 * @author	tcoutinho 
 */
namespace CTExpChannel_ns
{

/**
 * @class CTExpChannel
 * 
 * @brief Counter/Timer Experiment Device used by the Sardana project device pool
 * 
 * Device States Description:
 * Tango::ON :       The C/T is ON and waiting
 * Tango::FAULT :    A fault has been reported by the device controller
 * Tango::UNKNOWN :  IMpossible to communicate with the device controller
 * Tango::MOVING :   The C/T is counting
 */

//class CTExpChannel: public Tango::Device_4Impl
class CTExpChannel: public Pool_ns::PoolIndBaseDev
{
public :
    //	Add your own data members here
    //-----------------------------------------


    //	Here is the Start of the automatic code generation part
    //-------------------------------------------------------------	
/**
 *	@name attributes
 *	Attributs member data.
 */
//@{
        Tango::DevDouble	*attr_Value_read;
        Tango::DevDouble	attr_Value_write;
//@}

/**
 *	@name Device properties
 *	Device properties member data.
 */
//@{

//@}

/**@name Constructors
 * Miscellaneous constructors */
//@{
/**
 * Constructs a newly allocated Command object.
 *
 *	@param cl	Class.
 *	@param s 	Device Name
 */
    CTExpChannel(Tango::DeviceClass *cl,string &s);
/**
 * Constructs a newly allocated Command object.
 *
 *	@param cl	Class.
 *	@param s 	Device Name
 */
    CTExpChannel(Tango::DeviceClass *cl,const char *s);
/**
 * Constructs a newly allocated Command object.
 *
 *	@param cl	Class.
 *	@param s 	Device name
 *	@param d	Device description.
 */
    CTExpChannel(Tango::DeviceClass *cl,const char *s,const char *d);
//@}

/**@name Destructor
 * Only one desctructor is defined for this class */
//@{
/**
 * The object desctructor.
 */	
    ~CTExpChannel() {delete_device();};
/**
 *	will be called at device destruction or at init command.
 */
    void delete_device();
//@}

    
/**@name Miscellaneous methods */
//@{
/**
 *	Initialize the device
 */
    virtual void init_device();
/**
 *	Always executed method befor execution command method.
 */
    virtual void always_executed_hook();

//@}

/**
 * @name CTExpChannel methods prototypes
 */

//@{
/**
 *	Hardware acquisition for attributes.
 */
    virtual void read_attr_hardware(vector<long> &attr_list);
/**
 *	Extract real attribute values for Value acquisition result.
 */
    virtual void read_Value(Tango::Attribute &attr);
/**
 *	Write Value attribute values to hardware.
 */
    virtual void write_Value(Tango::WAttribute &attr);
/**
 *	Read/Write allowed for Value attribute.
 */
    virtual bool is_Value_allowed(Tango::AttReqType type);
/**
 *	Execution allowed for Start command.
 */
    virtual bool is_Start_allowed(const CORBA::Any &any);
/**
 *	Execution allowed for Abort command.
 */
    virtual bool is_Abort_allowed(const CORBA::Any &any);
/**
 * This command gets the device status (stored in its <i>device_status</i> data member) and returns it to the caller.
 *	@return	Status description
 *	@exception DevFailed
 */
    virtual Tango::ConstDevString	dev_status();
/**
 * Start counting
 *	@exception DevFailed
 */
    void	start();
/**
 * Stop counting
 *	@exception DevFailed
 */
    void	abort();

/**
 *	Read the device properties from database
 */
     void get_device_property();
//@}

    //	Here is the end of the automatic code generation part
    //-------------------------------------------------------------	
    
    Pool_ns::CTExpChannelPool &get_countertimer_element();
    
protected :	
    //	Add your own data members here
    //-----------------------------------------
    
    double				read_value;

    void inform_ghost(Tango::DevState,Tango::DevState);
    
public:

    virtual void base_abort(bool);
    
    void set_state_from_group(Controller::CtrlState &);
    
    bool				th_failed;
    Tango::DevErrorList	th_except;

    virtual void pool_elem_changed(Pool_ns::PoolElemEventList &, Pool_ns::PoolElementEvent &) {}    
};

}	// namespace_ns

#endif	// _CTEXPCHANNEL_H

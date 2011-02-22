//+=============================================================================
//
// file :         CommunicationChannel.cpp
//
// description :  C++ source for the CommunicationChannel and its commands. 
//                The class is derived from Device. It represents the
//                CORBA servant object which will be accessed from the
//                network. All commands which can be executed on the
//                CommunicationChannel are implemented in this file.
//
// project :      TANGO Device Server
//
// $Author$
//
// $Revision$
//
// $Log$
// Revision 1.4  2007/08/17 13:07:29  tcoutinho
// - pseudo motor restructure
// - pool base dev class restructure
// - initial commit for pseudo counters
//
// Revision 1.3  2007/08/07 10:19:37  tcoutinho
// -fix bug on communication channel state: state calculation had to be adapted
//
// Revision 1.2  2007/07/16 12:19:39  tcoutinho
// Changed Comunication to Communication
//
// Revision 1.1  2007/07/16 12:12:23  tcoutinho
// Unfortunately I made a syntax error and named 'Comunication' instead of 'Communication'. The old directory was ComunicationChannel
//
// Revision 1.6  2007/07/12 13:09:25  tcoutinho
// - added Open, Close, ReadLine methods
//
// Revision 1.5  2007/07/09 14:03:25  tcoutinho
// added open and close methods
//
// Revision 1.4  2007/07/02 14:45:29  tcoutinho
// first stable comunication channel commit
//
// Revision 1.3  2007/06/28 16:22:37  tcoutinho
// safety commit during comunication channels development
//
// Revision 1.2  2007/06/28 07:15:34  tcoutinho
// safety commit during comunication channels development
//
// Revision 1.1  2007/06/27 08:54:55  tcoutinho
// first commit for comuncation channels
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



//===================================================================
//
//	The following table gives the correspondance
//	between commands and method's name.
//
//  Command's name|  Method's name
//	----------------------------------------
//  State      |  dev_state()
//  Status     |  dev_status()
//  Read       |  read()
//  Write      |  write()
//  WriteRead  |  write_read()
//  Open       |  open()
//  Close      |  close()
//  ReadLine   |  read_line()
//
//===================================================================

#include "Pool.h"
#include "Utils.h"
#include "PoolUtil.h"
#include "CommunicationChannel.h"
#include "CommunicationChannelClass.h"
#include "CommunicationChannelUtil.h"

#include <tango.h>
#include <pool/ComCtrl.h>

namespace CommunicationChannel_ns
{

//+----------------------------------------------------------------------------
//
// @fn 		CommunicationChannel::CommunicationChannel(string &s)
// 
// description : 	constructor for simulated CommunicationChannel
//
// in : - cl : Pointer to the DeviceClass object
//      - s : Device name 
//
//-----------------------------------------------------------------------------
CommunicationChannel::CommunicationChannel(Tango::DeviceClass *cl,string &s)
//:Tango::Device_4Impl(cl,s.c_str())
:Pool_ns::PoolIndBaseDev(cl,s.c_str())
{
    init_cmd = false;
    init_device();
}

CommunicationChannel::CommunicationChannel(Tango::DeviceClass *cl,const char *s)
//:Tango::Device_4Impl(cl,s)
:Pool_ns::PoolIndBaseDev(cl,s)
{
    init_cmd = false;
    init_device();
}

CommunicationChannel::CommunicationChannel(Tango::DeviceClass *cl,const char *s,const char *d)
//:Tango::Device_4Impl(cl,s,d)
:Pool_ns::PoolIndBaseDev(cl,s,d)
{
    init_cmd = false;
    init_device();
}
//+----------------------------------------------------------------------------
//
// @fn 		CommunicationChannel::delete_device()
// 
// description : 	will be called at device destruction or at init command.
//
//-----------------------------------------------------------------------------
void CommunicationChannel::delete_device()
{
    //	Delete device's allocated object
    
//
// To know that we are executing this code due to a pool shutdown and not due to a
// "Init" command, we are using the polling thread ptr which is cleared in the DS
// shutdown sequence before the device destruction
//
    bool sd = false;

    Tango::Util *tg = Tango::Util::instance();
    if (tg->get_polling_thread_object() != NULL)
    {
        if (get_state() == Tango::MOVING)
        {
            TangoSys_OMemStream o;
            o << "Init command on Communication channel device is not allowed while a Communication channel is reading/writing" << ends;

            Tango::Except::throw_exception((const char *)"ComCh_InitNotAllowed",o.str(),
                    (const char *)"CommunicationChannel::delete_device");
        }
    }
    else
    {
        sd = true;
    }

//
// If we are not in a shutdown sequence:
// Lock the ghost group in order the polling thread not to
// start requesting for motor state while we are deleting it and
// inform ghost group that there is one channel less
//
// If we are called due to a Init command on the DServer admin,
// the measurement_group class is already deleted and the ghost group
// as well
//

    if (sd == false)
    {
        // TODO: ghost group
    }
    
//
// Delete the device from its controller and from the pool
//

    // If in shutdown mode, protect against exceptions
    if (sd)
    {
        try
        {
            delete_from_pool();
        }
        catch(Tango::DevFailed &df)
        {
            std::cout << "Error deleting '"<< get_name()
                      << "' from controller:" << std::endl;
            Tango::Except::print_exception(df);
        }
        catch(...)
        {
            std::cout << "Unknown error deleting '"<< get_name()
                      << "' from controller." << std::endl;
        }        
    }
    else
    {
        delete_from_pool();
    }
    delete_utils();
    
    PoolIndBaseDev::delete_device();
}

//+----------------------------------------------------------------------------
//
// @fn 		CommunicationChannel::init_device()
// 
// description : 	will be called at device initialization.
//
//-----------------------------------------------------------------------------
void CommunicationChannel::init_device()
{
    INFO_STREAM << "CommunicationChannel::CommunicationChannel() create device " << device_name << endl;

    // Initialise variables to default values
    //--------------------------------------------
    PoolIndBaseDev::init_device();
    
//
// We will push change event on State and Value attributes
//

    Tango::Attribute &state_att = dev_attr->get_attr_by_name("state");
    state_att.set_change_event(true,false);

//
// Build the PoolBaseUtils class depending on the
// controller type
//

    set_utils(new CommunicationChannelUtil(pool_dev));
    
//
// Inform Pool of our birth
//

    Pool_ns::CommunicationChannelPool *cc_pool_ptr = new Pool_ns::CommunicationChannelPool;
    init_pool_element(cc_pool_ptr);
    
    {
        Tango::AutoTangoMonitor atm(pool_dev);	
        pool_dev->add_element(cc_pool_ptr);
    }

//
// Inform controller of our birth
//

    a_new_child(cc_pool_ptr->get_ctrl_id());
    
//
// If we are called due to a init command, update our info in the
// ghost group
//
        
    if (init_cmd == true)
    {
        //TODO: ghost group
        init_cmd = false;
    }
}

Pool_ns::CommunicationChannelPool &CommunicationChannel::get_comch_element()
{
    return static_cast<Pool_ns::CommunicationChannelPool &>(get_pool_element());
}

//+----------------------------------------------------------------------------
//
// @fn 		CommunicationChannel::get_device_property()
// 
// description : 	Read the device properties from database.
//
//-----------------------------------------------------------------------------
void CommunicationChannel::get_device_property()
{
    //	Initialize your default values here (if not done with  POGO).
    //------------------------------------------------------------------
    PoolIndBaseDev::get_device_property();
    
    //	Read device properties from database.(Automatic code generation)
    //------------------------------------------------------------------

    //	End of Automatic code generation
    //------------------------------------------------------------------

}
//+----------------------------------------------------------------------------
//
// @fn 		CommunicationChannel::always_executed_hook()
// 
// description : 	method always executed before any command is executed
//
//-----------------------------------------------------------------------------
void CommunicationChannel::always_executed_hook()
{
    DEBUG_STREAM << "CommunicationChannel::always_executed_hook entering... "<< endl;
    bool propagate = true;
    
    Pool_ns::CommunicationChannelPool &comch_element = get_comch_element();
    
    if (comch_element.get_simulation_mode())
    {
        Tango::DevState old_state = get_state();
        
        if (is_fica_built())
        {
            unknown_state = false;
            Pool_ns::PoolLock &pl = fica_ptr->get_mon();
            Pool_ns::AutoPoolLock lo(pl);
            if (!this->ctrl_code_online)
            {
                set_state(Tango::FAULT);
            }
            else
            {
                if (comch_element.is_add_device_done())
                {
                    Controller::CtrlState mi;
                    try
                    {
                        read_state_from_ctrl(mi,false);
                        set_state((Tango::DevState)mi.state);
                        ctrl_str = mi.status;
                    }
                    catch(Tango::DevFailed &e)
                    {
                        set_state(Tango::UNKNOWN);
                        ctrl_str = "\nError reported from controller when requesting for object state";
                        ctrl_str += "\n\t";
                        ctrl_str += e.errors[0].desc.in();
                    }
                }
                else
                    set_state(Tango::FAULT);
            }
        }
        else
        {
            set_state(Tango::FAULT);
        }
        
//
// If necessary notify the ghost group of changes in this element.
// The ghost group will itself notify any internal listeners. 
//
        if(propagate == true)
        {
            inform_ghost(old_state,get_state());
        }
    }
}

//+----------------------------------------------------------------------------
//
// @fn 		CommunicationChannel::read_attr_hardware
// 
// description : 	Hardware acquisition for attributes.
//
//-----------------------------------------------------------------------------
void CommunicationChannel::read_attr_hardware(vector<long> &attr_list)
{
    DEBUG_STREAM << "CommunicationChannel::read_attr_hardware(vector<long> &attr_list) entering... "<< endl;
    //	Add your own code here
}

//+------------------------------------------------------------------
/**
 *	@fn	CommunicationChannel::read
 *
 *	Method to execute "Read"
 *	Atempts to read up to n bytes from the Communication channel.
 *	If n is 0(zero), Read() returns an empty array.
 *	If n is -1, Read() will return all data available in the channel.
 *
 * @param	argin	Number of bytes to read from the Communication channel. 0 will return an empty array. -1 will read all available data
 * @return	The data stream read from the channel
 *
 */
//+------------------------------------------------------------------
Tango::DevVarCharArray *CommunicationChannel::read(Tango::DevLong argin)
{
    DEBUG_STREAM << "CommunicationChannel::read(): entering... !" << endl;

    //	Add your own code to control device here
    
    Tango::DevVarCharArray	*argout;
    
    read_from_ctrl(argin);

    unsigned long len = buf.size(); 
    if(len > 0)
    {
        argout = create_DevVarCharArray((unsigned char *)buf.data(),len);
    }
    else
    {
        argout = new Tango::DevVarCharArray();
        argout->length(0);
    }
    
    return argout;
}

//+------------------------------------------------------------------
/**
 *	@fn	CommunicationChannel::read_line
 *
 *	description:	method to execute "ReadLine"
 *	Atempts to read characters up to a new line character from the communication channel
 *
 * @return	The character read from the communication channel
 *
 */
//+------------------------------------------------------------------
Tango::DevVarCharArray *CommunicationChannel::read_line()
{
    //	POGO has generated a method core with argout allocation.
    //	If you would like to use a static reference without copying,
    //	See "TANGO Device Server Programmer's Manual"
    //		(chapter : Writing a TANGO DS / Exchanging data)
    //------------------------------------------------------------
    DEBUG_STREAM << "CommunicationChannel::read_line(): entering... !" << endl;

    //	Add your own code to control device here

    Tango::DevVarCharArray	*argout;
    
    read_line_from_ctrl();

    unsigned long len = buf.size(); 
    if(len > 0)
    {
        argout = create_DevVarCharArray((unsigned char *)buf.data(),len);
    }
    else
    {
        argout = new Tango::DevVarCharArray();
        argout->length(0);
    }
    
    return argout;
}


//+------------------------------------------------------------------
/**
 *	@fn	CommunicationChannel::write
 *
 *	description:	method to execute "Write"
 *	Sends the given data as parameter to the Communication channel.
 *	The result is the number of bytes actually sent to the channel.
 *
 * @param	argin	The data stream to be sent to the Communication channel
 * @return	The number of bytes actually sent to the channel
 *
 */
//+------------------------------------------------------------------
Tango::DevLong CommunicationChannel::write(const Tango::DevVarCharArray *argin)
{
    DEBUG_STREAM << "CommunicationChannel::write(): entering... !" << endl;

    //	Add your own code to control device here
    
    return write_to_ctrl(argin->get_buffer(),argin->length());
}

//+------------------------------------------------------------------
/**
 *	@fn	CommunicationChannel::write_read
 *
 *	description:	method to execute "WriteRead"
 *	Sends the given data as parameter to the Communication channel.
 *	After this operation completes it performs a read to get all data available in the Communication channel.
 *
 * @param	argin	The data stream to be sent to the Communication channel
 * @return	The data stream read from the channel
 *
 */
//+------------------------------------------------------------------
Tango::DevVarCharArray *CommunicationChannel::write_read(const Tango::DevVarCharArray *argin)
{
    //	POGO has generated a method core with argout allocation.
    //	If you would like to use a static reference without copying,
    //	See "TANGO Device Server Programmer's Manual"
    //		(chapter : Writing a TANGO DS / Exchanging data)
    //------------------------------------------------------------
    DEBUG_STREAM << "CommunicationChannel::write_read(): entering... !" << endl;

    //	Add your own code to control device here
    Tango::DevVarCharArray	*argout;
    
    Pool_ns::AutoPoolLock lo(fica_ptr->get_mon());
    
    write_read_ctrl(argin->get_buffer(),argin->length(),-1);

    unsigned long len = buf.size(); 
    if(len > 0)
    {
        argout = create_DevVarCharArray((unsigned char *)buf.data(),len);
    }
    else
    {
        argout = new Tango::DevVarCharArray();
        argout->length(0);
    }	

    return argout;
}

//+------------------------------------------------------------------
/**
 *	@fn	CommunicationChannel::dev_status
 *
 *	description:	method to execute "Status"
 *	This command gets the device status (stored in its <i>device_status</i> data member) and returns it to the caller.
 *
 * @return	Status description
 *
 */
//+------------------------------------------------------------------
Tango::ConstDevString CommunicationChannel::dev_status()
{
    Tango::ConstDevString	argout = DeviceImpl::dev_status();
    DEBUG_STREAM << "CommunicationChannel::dev_status(): entering... !" << endl;

    //	Add your own code to control device here

    base_dev_status(argout);
    
    argout = tmp_status.c_str();
    return argout;
}

//+------------------------------------------------------------------
/**
 *	@fn	CommunicationChannel::write_read_ctrl
 *
 *	description:	method to execute "Write" on the controller
 *	Atempts to write up to n bytes from the controller.
 *	If length is 0(zero), it will empty the internal buffer.
 *	If length is -1, will fill the internal buffer with all available data
 *
 * @param	data			data to write 
 * @param	write_len		write_len number of bytes to write 	
 * @param	max_read_len	maximum number of bytes to read. 0(zero), it will 
 * 							empty the internal buffer. -1, will fill the 
 * 							internal buffer with all available data
 */
//+------------------------------------------------------------------
void CommunicationChannel::write_read_ctrl(const unsigned char *data, long write_len, long max_read_len)
{
    Pool_ns::AutoPoolLock lo(fica_ptr->get_mon());
    
    if(write_len == 0)
        buf.clear();
    else
        buf.assign((const char*)data,write_len);
        
    try
    {
        ComController *typed_ctrl = static_cast<ComController *>(get_controller());
        string &res = typed_ctrl->WriteReadOne(get_axis(),buf,write_len,max_read_len);
        buf.assign(res);
    }
    SAFE_CATCH(fica_ptr->get_name(),"read_from_ctrl");
}


//+------------------------------------------------------------------
/**
 *	Execute "Read" on the controller
 *	Atempts to read up to length bytes from the controller.
 *	If length is 0(zero), it will empty the internal buffer.
 *	If length is -1, will fill the internal buffer with all available data
 *
 * @param	len	Number of bytes to read from the controller. 0(zero), it will 
 * 				empty the internal buffer. -1, will fill the internal buffer 
 * 				with all available data
 */
//+------------------------------------------------------------------
void CommunicationChannel::read_from_ctrl(long len)
{
    Pool_ns::AutoPoolLock lo(fica_ptr->get_mon());
    
    try
    {
        ComController *typed_ctrl = static_cast<ComController *>(get_controller());
        string &res = typed_ctrl->ReadOne(get_axis(),len);
        buf.assign(res);
    }
    SAFE_CATCH(fica_ptr->get_name(),"read_from_ctrl");
}

//+------------------------------------------------------------------
/**
 *	Execute "ReadLine" on the controller
 *	Atempts to read up to a new line character from the controller.
 */
//+------------------------------------------------------------------
void CommunicationChannel::read_line_from_ctrl()
{
    Pool_ns::AutoPoolLock lo(fica_ptr->get_mon());
    
    try
    {
        ComController *typed_ctrl = static_cast<ComController *>(get_controller());
        string &res = typed_ctrl->ReadLineOne(get_axis());
        buf.assign(res);
    }
    SAFE_CATCH(fica_ptr->get_name(),"read_line_from_ctrl");
}
//+------------------------------------------------------------------
/**
 *	Execute "Write" on the controller
 *	Atempts to write up to n bytes from the controller.
 *	If length is 0(zero), it will empty the internal buffer.
 *	If length is -1, will fill the internal buffer with all available data
 *
 * @param	data			data to write 
 * @param	length	Number of bytes to read from the controller.
 *					0(zero), it will empty the internal buffer.
 *					-1, will fill the internal buffer with all available data
 */
//+------------------------------------------------------------------
Tango::DevLong CommunicationChannel::write_to_ctrl(const unsigned char *data, long length)
{
    DEBUG_STREAM << "CommunicationChannel::write_to_ctrl(): entering... !" << endl;
    Pool_ns::AutoPoolLock lo(fica_ptr->get_mon());
    
    if(length == 0)
        buf.clear();
    else
        buf.assign((const char*)data,length);
        
    try
    {
        ComController *typed_ctrl = static_cast<ComController *>(get_controller());
        return typed_ctrl->WriteOne(get_axis(),buf,length);
    }
    SAFE_CATCH(fica_ptr->get_name(),"read_from_ctrl");
    
    // Make the compiler quiet
    return 0;
}

//+----------------------------------------------------------------------------
/**
 * Inform ghost group of a change in the state
 * 
 * @param old_state the old state
 * @param new_state the new state
 */
//+----------------------------------------------------------------------------
void CommunicationChannel::inform_ghost(Tango::DevState old_state,Tango::DevState new_state)
{
    //TODO	
}

//+------------------------------------------------------------------
/**
 *	@fn	CommunicationChannel::open
 *
 *	description:	method to execute "Open"
 *	opens the communication channel
 *
 */
//+------------------------------------------------------------------
void CommunicationChannel::open()
{
    DEBUG_STREAM << "CommunicationChannel::open(): entering... !" << endl;

    //	Add your own code to control device here
    Pool_ns::AutoPoolLock lo(fica_ptr->get_mon());
    
    try
    {
        ComController *typed_ctrl = static_cast<ComController *>(get_controller());
        return typed_ctrl->OpenOne(get_axis());
    }
    SAFE_CATCH(fica_ptr->get_name(),"open");
    
}

//+------------------------------------------------------------------
/**
 *	@fn	CommunicationChannel::close
 *
 *	description:	method to execute "Close"
 *	closes the communication channel
 *
 *
 */
//+------------------------------------------------------------------
void CommunicationChannel::close()
{
    DEBUG_STREAM << "CommunicationChannel::close(): entering... !" << endl;

    //	Add your own code to control device here
    Pool_ns::AutoPoolLock lo(fica_ptr->get_mon());
    
    try
    {
        ComController *typed_ctrl = static_cast<ComController *>(get_controller());
        return typed_ctrl->CloseOne(get_axis());
    }
    SAFE_CATCH(fica_ptr->get_name(),"open");
}


}	//	namespace

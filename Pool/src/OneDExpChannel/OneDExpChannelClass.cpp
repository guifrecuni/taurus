static const char *RcsId     = "$Header:  $";
static const char *TagName   = "$Name:  $";
static const char *HttpServer= "http://www.esrf.fr/computing/cs/tango/tango_doc/ds_doc/";
//+=============================================================================
//
// file :        OneDExpChannelClass.cpp
//
// description : C++ source for the OneDExpChannelClass. A singleton
//               class derived from DeviceClass. It implements the
//               command list and all properties and methods required
//               by the OneDExpChannel once per process.
//
// project :     TANGO Device Server
//
// $Author:  $
//
// $Revision:  $
//
// $Log:  $
//
// copyleft :   European Synchrotron Radiation Facility
//              BP 220, Grenoble 38043
//              FRANCE
//
//-=============================================================================
//
//  		This file is generated by POGO
//	(Program Obviously used to Generate tango Object)
//
//         (c) - Software Engineering Group - ESRF
//=============================================================================


#include "OneDExpChannel.h"
#include "OneDExpChannelClass.h"
#include <tango.h>


//+----------------------------------------------------------------------------
/**
 *	Create OneDExpChannelClass singleton and return it in a C function for Python usage
 */
//+----------------------------------------------------------------------------
extern "C" {
#ifdef WIN32

__declspec(dllexport)

#endif

    Tango::DeviceClass *_create_OneDExpChannel_class(const char *name) {
        return OneDExpChannel_ns::OneDExpChannelClass::init(name);
    }
}


namespace OneDExpChannel_ns
{

//+----------------------------------------------------------------------------
//
// method : 		StartClass::execute()
// 
// description : 	method to trigger the execution of the command.
//                PLEASE DO NOT MODIFY this method core without pogo   
//
// in : - device : The device on which the command must be excuted
//		- in_any : The command input data
//
// returns : The command output data (packed in the Any object)
//
//-----------------------------------------------------------------------------
CORBA::Any *StartClass::execute(Tango::DeviceImpl *device,const CORBA::Any &in_any)
{

    cout2 << "StartClass::execute(): arrived" << endl;

    ((static_cast<OneDExpChannel *>(device))->start());
    return new CORBA::Any();
}

//+----------------------------------------------------------------------------
//
// method : 		AbortClass::execute()
// 
// description : 	method to trigger the execution of the command.
//                PLEASE DO NOT MODIFY this method core without pogo   
//
// in : - device : The device on which the command must be excuted
//		- in_any : The command input data
//
// returns : The command output data (packed in the Any object)
//
//-----------------------------------------------------------------------------
CORBA::Any *AbortClass::execute(Tango::DeviceImpl *device,const CORBA::Any &in_any)
{

    cout2 << "AbortClass::execute(): arrived" << endl;

    ((static_cast<OneDExpChannel *>(device))->abort());
    return new CORBA::Any();
}


//
//----------------------------------------------------------------
//	Initialize pointer for singleton pattern
//----------------------------------------------------------------
//
OneDExpChannelClass *OneDExpChannelClass::_instance = NULL;

//+----------------------------------------------------------------------------
//
// method : 		OneDExpChannelClass::OneDExpChannelClass(string &s)
// 
// description : 	constructor for the OneDExpChannelClass
//
// in : - s : The class name
//
//-----------------------------------------------------------------------------
OneDExpChannelClass::OneDExpChannelClass(string &s):DeviceClass(s)
{

    cout2 << "Entering OneDExpChannelClass constructor" << endl;
    set_default_property();
    get_class_property();
    write_class_property();
       
    nb_static_attr = 0;
    first_call_to_device_factory = true;

    cout2 << "Leaving OneDExpChannelClass constructor" << endl;

}
//+----------------------------------------------------------------------------
//
// method : 		OneDExpChannelClass::~OneDExpChannelClass()
// 
// description : 	destructor for the OneDExpChannelClass
//
//-----------------------------------------------------------------------------
OneDExpChannelClass::~OneDExpChannelClass()
{
    _instance = NULL;
}

//+----------------------------------------------------------------------------
//
// method : 		OneDExpChannelClass::instance
// 
// description : 	Create the object if not already done. Otherwise, just
//			return a pointer to the object
//
// in : - name : The class name
//
//-----------------------------------------------------------------------------
OneDExpChannelClass *OneDExpChannelClass::init(const char *name)
{
    if (_instance == NULL)
    {
        try
        {
            string s(name);
            _instance = new OneDExpChannelClass(s);
        }
        catch (bad_alloc)
        {
            throw;
        }		
    }		
    return _instance;
}

OneDExpChannelClass *OneDExpChannelClass::instance()
{
    if (_instance == NULL)
    {
        cerr << "Class is not initialised !!" << endl;
        exit(-1);
    }
    return _instance;
}

//+----------------------------------------------------------------------------
//
// method : 		OneDExpChannelClass::command_factory
// 
// description : 	Create the command object(s) and store them in the 
//			command list
//
//-----------------------------------------------------------------------------
void OneDExpChannelClass::command_factory()
{
    command_list.push_back(new StartClass("Start",
        Tango::DEV_VOID, Tango::DEV_VOID,
        "",
        "",
        Tango::OPERATOR));
    command_list.push_back(new AbortClass("Abort",
        Tango::DEV_VOID, Tango::DEV_VOID,
        "",
        "",
        Tango::OPERATOR));

    //	add polling if any
    for (unsigned int i=0 ; i<command_list.size(); i++)
    {
    }
}

//+----------------------------------------------------------------------------
//
// method : 		OneDExpChannelClass::get_class_property
// 
// description : 	Get the class property for specified name.
//
// in :		string	name : The property name
//
//+----------------------------------------------------------------------------
Tango::DbDatum OneDExpChannelClass::get_class_property(string &prop_name)
{
    for (unsigned int i=0 ; i<cl_prop.size() ; i++)
        if (cl_prop[i].name == prop_name)
            return cl_prop[i];
    //	if not found, return  an empty DbDatum
    return Tango::DbDatum(prop_name);
}
//+----------------------------------------------------------------------------
//
// method : 		OneDExpChannelClass::get_default_device_property()
// 
// description : 	Return the default value for device property.
//
//-----------------------------------------------------------------------------
Tango::DbDatum OneDExpChannelClass::get_default_device_property(string &prop_name)
{
    for (unsigned int i=0 ; i<dev_def_prop.size() ; i++)
        if (dev_def_prop[i].name == prop_name)
            return dev_def_prop[i];
    //	if not found, return  an empty DbDatum
    return Tango::DbDatum(prop_name);
}

//+----------------------------------------------------------------------------
//
// method : 		OneDExpChannelClass::get_default_class_property()
// 
// description : 	Return the default value for class property.
//
//-----------------------------------------------------------------------------
Tango::DbDatum OneDExpChannelClass::get_default_class_property(string &prop_name)
{
    for (unsigned int i=0 ; i<cl_def_prop.size() ; i++)
        if (cl_def_prop[i].name == prop_name)
            return cl_def_prop[i];
    //	if not found, return  an empty DbDatum
    return Tango::DbDatum(prop_name);
}
//+----------------------------------------------------------------------------
//
// method : 		OneDExpChannelClass::device_factory
// 
// description : 	Create the device object(s) and store them in the 
//			device list
//
// in :		Tango::DevVarStringArray *devlist_ptr : The device name list
//
//-----------------------------------------------------------------------------
void OneDExpChannelClass::device_factory(const Tango::DevVarStringArray *devlist_ptr)
{

    //	Create all devices.(Automatic code generation)
    //-------------------------------------------------------------
    for (unsigned long i=0 ; i < devlist_ptr->length() ; i++)
    {
        cout4 << "Device name : " << (*devlist_ptr)[i].in() << endl;
                        
        // Create devices and add it into the device list
        //----------------------------------------------------
        device_list.push_back(new OneDExpChannel(this, (*devlist_ptr)[i]));							 

        // Export device to the outside world
        // Check before if database used.
        //---------------------------------------------
        if ((Tango::Util::_UseDb == true) && (Tango::Util::_FileDb == false))
            export_device(device_list.back());
        else
            export_device(device_list.back(), (*devlist_ptr)[i]);
    }
    //	End of Automatic code generation
    //-------------------------------------------------------------

    long nb_dev = device_list.size();

//
// Get the number of static attribute before any dynamic one is added
//
    
    if ((nb_dev != 0) && (first_call_to_device_factory == true))
    {
        nb_static_attr = device_list.back()->get_device_attr()->get_attr_nb();
        first_call_to_device_factory = false;
    }

//
// Create dynamic attribute but remove the unwanted ones
//
    
    long nb_new_device = devlist_ptr->length();
    long start_index;
    
    if (nb_dev != 0)
        start_index = nb_dev - nb_new_device;
    else
        start_index = 0;
        
    for (long i=0 ; i < nb_new_device ; i++)
    {
        if (static_cast<OneDExpChannel *>(device_list[start_index + i])->is_add_device_done() == true)
        {
            static_cast<OneDExpChannel *>(device_list[start_index + i])->create_dyn_attr();
            static_cast<OneDExpChannel *>(device_list[start_index + i])->remove_unwanted_dyn_attr_from_device();
        }	
    }	

}
//+----------------------------------------------------------------------------
//	Method: OneDExpChannelClass::attribute_factory(vector<Tango::Attr *> &att_list)
//-----------------------------------------------------------------------------
void OneDExpChannelClass::attribute_factory(vector<Tango::Attr *> &att_list)
{
    //	Attribute : SimulationMode
    SimulationModeAttrib	*simulation_mode = new SimulationModeAttrib();
    att_list.push_back(simulation_mode);

	//	Attribute : Instrument
	InstrumentAttrib	*instrument = new InstrumentAttrib();
	instrument->set_disp_level(Tango::EXPERT);
	att_list.push_back(instrument);
    
    //	Attribute : DataLength
    DataLengthAttrib	*data_length = new DataLengthAttrib();
    att_list.push_back(data_length);

    //	Attribute : Data
    DataAttrib	*data = new DataAttrib();
    att_list.push_back(data);

    //	Attribute : Value
    ValueAttrib	*value = new ValueAttrib();
    att_list.push_back(value);

    //	End of Automatic code generation
    //-------------------------------------------------------------
}

//+----------------------------------------------------------------------------
//
// method : 		OneDExpChannelClass::get_class_property()
// 
// description : 	Read the class properties from database.
//
//-----------------------------------------------------------------------------
void OneDExpChannelClass::get_class_property()
{
    //	Initialize your default values here (if not done with  POGO).
    //------------------------------------------------------------------

    //	Read class properties from database.(Automatic code generation)
    //------------------------------------------------------------------

    //	Call database and extract values
    //--------------------------------------------
    if (Tango::Util::instance()->_UseDb==true)
        get_db_class()->get_property(cl_prop);
    Tango::DbDatum	def_prop;

    //	End of Automatic code generation
    //------------------------------------------------------------------

}

//+----------------------------------------------------------------------------
//
// method : 	OneDExpChannelClass::set_default_property
// 
// description: Set default property (class and device) for wizard.
//              For each property, add to wizard property name and description
//              If default value has been set, add it to wizard property and
//              store it in a DbDatum.
//
//-----------------------------------------------------------------------------
void OneDExpChannelClass::set_default_property()
{
    string	prop_name;
    string	prop_desc;
    string	prop_def;

    vector<string>	vect_data;
    //	Set Default Class Properties
    //	Set Default Device Properties
    prop_name = "id";
    prop_desc = "The experiment channel identifier";
    prop_def  = "";
    if (prop_def.length()>0)
    {
        Tango::DbDatum	data(prop_name);
        data << vect_data ;
        dev_def_prop.push_back(data);
        add_wiz_dev_prop(prop_name, prop_desc,  prop_def);
    }
    else
        add_wiz_dev_prop(prop_name, prop_desc);

    prop_name = "MaxDataLength";
    prop_desc = "Maximum Length of the spectrum data";
    prop_def  = "8192";
    vect_data.clear();
    vect_data.push_back("8192");
    if (prop_def.length()>0)
    {
        Tango::DbDatum	data(prop_name);
        data << vect_data ;
        dev_def_prop.push_back(data);
        add_wiz_dev_prop(prop_name, prop_desc,  prop_def);
    }
    else
        add_wiz_dev_prop(prop_name, prop_desc);

}
//+----------------------------------------------------------------------------
//
// method : 		OneDExpChannelClass::write_class_property
// 
// description : 	Set class description as property in database
//
//-----------------------------------------------------------------------------
void OneDExpChannelClass::write_class_property()
{
    //	First time, check if database used
    //--------------------------------------------
    if (Tango::Util::_UseDb == false)
        return;

    Tango::DbData	data;
    string	classname = get_name();
    string	header;
    string::size_type	start, end;

    //	Put title
    Tango::DbDatum	title("ProjectTitle");
    string	str_title("OneDimensionExperimentalChannel");
    title << str_title;
    data.push_back(title);

    //	Put Description
    Tango::DbDatum	description("Description");
    vector<string>	str_desc;
    str_desc.push_back("One Dimension Experiment device used by the Sardana project device pool");
    description << str_desc;
    data.push_back(description);
        
    //	put cvs location
    string	rcsId(RcsId);
    string	filename(classname);
    start = rcsId.find("/");
    if (start!=string::npos)
    {
        filename += "Class.cpp";
        end   = rcsId.find(filename);
        if (end>start)
        {
            string	strloc = rcsId.substr(start, end-start);
            //	Check if specific repository
            start = strloc.find("/cvsroot/");
            if (start!=string::npos && start>0)
            {
                string	repository = strloc.substr(0, start);
                if (repository.find("/segfs/")!=string::npos)
                    strloc = "ESRF:" + strloc.substr(start, strloc.length()-start);
            }
            Tango::DbDatum	cvs_loc("cvs_location");
            cvs_loc << strloc;
            data.push_back(cvs_loc);
        }
    }

    //	Get CVS tag revision
    string	tagname(TagName);
    header = "$Name: ";
    start = header.length();
    string	endstr(" $");
    end   = tagname.find(endstr);
    if (end!=string::npos && end>start)
    {
        string	strtag = tagname.substr(start, end-start);
        Tango::DbDatum	cvs_tag("cvs_tag");
        cvs_tag << strtag;
        data.push_back(cvs_tag);
    }

    //	Get URL location
    string	httpServ(HttpServer);
    if (httpServ.length()>0)
    {
        Tango::DbDatum	db_doc_url("doc_url");
        db_doc_url << httpServ;
        data.push_back(db_doc_url);
    }

    //  Put inheritance
    Tango::DbDatum	inher_datum("InheritedFrom");
    vector<string> inheritance;
    inheritance.push_back("Device_4Impl");
    inher_datum << inheritance;
    data.push_back(inher_datum);

    //	Call database and and values
    //--------------------------------------------
    get_db_class()->put_property(data);
}

}	// namespace

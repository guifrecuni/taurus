static const char *RcsId     = "$Header:  $";
static const char *TagName   = "$Name:  $";
static const char *HttpServer= "http://www.esrf.fr/computing/cs/tango/tango_doc/ds_doc/";
//+=============================================================================
//
// file :        ControllerClass.cpp
//
// description : C++ source for the ControllerClass. A singleton
//               class derived from DeviceClass. It implements the
//               command list and all properties and methods required
//               by the Controller once per process.
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


#include <tango.h>

#include <Controller.h>
#include <ControllerClass.h>


//+----------------------------------------------------------------------------
/**
 *	Create ControllerClass singleton and return it in a C function for Python usage
 */
//+----------------------------------------------------------------------------
extern "C" {
#ifdef WIN32

__declspec(dllexport)

#endif

    Tango::DeviceClass *_create_Controller_class(const char *name) {
        return Controller_ns::ControllerClass::init(name);
    }
}


namespace Controller_ns
{
//+----------------------------------------------------------------------------
//
// method : 		SendClass::execute()
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
CORBA::Any *SendClass::execute(Tango::DeviceImpl *device,const CORBA::Any &in_any)
{

    cout2 << "SendClass::execute(): arrived" << endl;

    const Tango::DevVarCharArray	*argin;
    extract(in_any, argin);

    return insert((static_cast<Controller *>(device))->send(argin));
}


//+----------------------------------------------------------------------------
//
// method : 		AddElementClass::execute()
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
CORBA::Any *AddElementClass::execute(Tango::DeviceImpl *device,const CORBA::Any &in_any)
{

    cout2 << "AddElementClass::execute(): arrived" << endl;

    const Tango::DevVarStringArray	*argin;
    extract(in_any, argin);

    ((static_cast<Controller *>(device))->add_element(argin));
    return new CORBA::Any();
}

//+----------------------------------------------------------------------------
//
// method : 		DeleteElementClass::execute()
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
CORBA::Any *DeleteElementClass::execute(Tango::DeviceImpl *device,const CORBA::Any &in_any)
{

    cout2 << "DeleteElementClass::execute(): arrived" << endl;

    Tango::DevString	argin;
    extract(in_any, argin);

    ((static_cast<Controller *>(device))->delete_element(argin));
    return new CORBA::Any();
}


//
//----------------------------------------------------------------
//	Initialize pointer for singleton pattern
//----------------------------------------------------------------
//
ControllerClass *ControllerClass::_instance = NULL;

//+----------------------------------------------------------------------------
//
// method : 		ControllerClass::ControllerClass(string &s)
// 
// description : 	constructor for the ControllerClass
//
// in : - s : The class name
//
//-----------------------------------------------------------------------------
ControllerClass::ControllerClass(string &s):DeviceClass(s)
{

    cout2 << "Entering ControllerClass constructor" << endl;
    set_default_property();
    get_class_property();
    write_class_property();
    
    cout2 << "Leaving ControllerClass constructor" << endl;

}
//+----------------------------------------------------------------------------
//
// method : 		ControllerClass::~ControllerClass()
// 
// description : 	destructor for the ControllerClass
//
//-----------------------------------------------------------------------------
ControllerClass::~ControllerClass()
{
    _instance = NULL;
}

//+----------------------------------------------------------------------------
//
// method : 		ControllerClass::instance
// 
// description : 	Create the object if not already done. Otherwise, just
//			return a pointer to the object
//
// in : - name : The class name
//
//-----------------------------------------------------------------------------
ControllerClass *ControllerClass::init(const char *name)
{
    if (_instance == NULL)
    {
        try
        {
            string s(name);
            _instance = new ControllerClass(s);
        }
        catch (bad_alloc)
        {
            throw;
        }		
    }		
    return _instance;
}

ControllerClass *ControllerClass::instance()
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
// method : 		ControllerClass::command_factory
// 
// description : 	Create the command object(s) and store them in the 
//			command list
//
//-----------------------------------------------------------------------------
void ControllerClass::command_factory()
{
    command_list.push_back(new AddElementClass("AddElement",
        Tango::DEVVAR_STRINGARRAY, Tango::DEV_VOID,
        "arg[0] - axis number (starting at 1)\narg[1] - element name\narg[2] - (optional) device name",
        "",
        Tango::OPERATOR));
    command_list.push_back(new DeleteElementClass("DeleteElement",
        Tango::DEV_STRING, Tango::DEV_VOID,
        "the axis number or element name or device name",
        "",
        Tango::OPERATOR));
    command_list.push_back(new SendClass("Send",
        Tango::DEVVAR_CHARARRAY, Tango::DEVVAR_CHARARRAY,
        "The string to send to the controller",
        "The response from the controller",
        Tango::OPERATOR));

    //	add polling if any
    for (unsigned int i=0 ; i<command_list.size(); i++)
    {
    }
}

//+----------------------------------------------------------------------------
//
// method : 		ControllerClass::get_class_property
// 
// description : 	Get the class property for specified name.
//
// in :		string	name : The property name
//
//+----------------------------------------------------------------------------
Tango::DbDatum ControllerClass::get_class_property(string &prop_name)
{
    for (unsigned int i=0 ; i<cl_prop.size() ; i++)
        if (cl_prop[i].name == prop_name)
            return cl_prop[i];
    //	if not found, return  an empty DbDatum
    return Tango::DbDatum(prop_name);
}
//+----------------------------------------------------------------------------
//
// method : 		ControllerClass::get_default_device_property()
// 
// description : 	Return the default value for device property.
//
//-----------------------------------------------------------------------------
Tango::DbDatum ControllerClass::get_default_device_property(string &prop_name)
{
    for (unsigned int i=0 ; i<dev_def_prop.size() ; i++)
        if (dev_def_prop[i].name == prop_name)
            return dev_def_prop[i];
    //	if not found, return  an empty DbDatum
    return Tango::DbDatum(prop_name);
}

//+----------------------------------------------------------------------------
//
// method : 		ControllerClass::get_default_class_property()
// 
// description : 	Return the default value for class property.
//
//-----------------------------------------------------------------------------
Tango::DbDatum ControllerClass::get_default_class_property(string &prop_name)
{
    for (unsigned int i=0 ; i<cl_def_prop.size() ; i++)
        if (cl_def_prop[i].name == prop_name)
            return cl_def_prop[i];
    //	if not found, return  an empty DbDatum
    return Tango::DbDatum(prop_name);
}
//+----------------------------------------------------------------------------
//
// method : 		ControllerClass::device_factory
// 
// description : 	Create the device object(s) and store them in the 
//			device list
//
// in :		Tango::DevVarStringArray *devlist_ptr : The device name list
//
//-----------------------------------------------------------------------------
void ControllerClass::device_factory(const Tango::DevVarStringArray *devlist_ptr)
{

    //	Create all devices.(Automatic code generation)
    //-------------------------------------------------------------
    for (unsigned long i=0 ; i < devlist_ptr->length() ; i++)
    {
        cout4 << "Device name : " << (*devlist_ptr)[i].in() << endl;
                        
        // Create devices and add it into the device list
        //----------------------------------------------------
        device_list.push_back(new Controller(this, (*devlist_ptr)[i]));							 

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

}
//+----------------------------------------------------------------------------
//	Method: ControllerClass::attribute_factory(vector<Tango::Attr *> &att_list)
//-----------------------------------------------------------------------------
void ControllerClass::attribute_factory(vector<Tango::Attr *> &att_list)
{
    //	Attribute : Elements
    ElementsAttrib	*elements = new ElementsAttrib();
    Tango::UserDefaultAttrProp	elements_prop;
    elements_prop.set_label("Elements");
    elements_prop.set_description("The list of elements controlled by this controller");
    elements->set_default_properties(elements_prop);
    elements->set_change_event(true, false);
    att_list.push_back(elements);

    //	End of Automatic code generation
    //-------------------------------------------------------------
}

//+----------------------------------------------------------------------------
//
// method : 		ControllerClass::get_class_property()
// 
// description : 	Read the class properties from database.
//
//-----------------------------------------------------------------------------
void ControllerClass::get_class_property()
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
    int	i = -1;


    //	End of Automatic code generation
    //------------------------------------------------------------------

}

//+----------------------------------------------------------------------------
//
// method : 	ControllerClass::set_default_property
// 
// description: Set default property (class and device) for wizard.
//              For each property, add to wizard property name and description
//              If default value has been set, add it to wizard property and
//              store it in a DbDatum.
//
//-----------------------------------------------------------------------------
void ControllerClass::set_default_property()
{
    string	prop_name;
    string	prop_desc;
    string	prop_def;

    vector<string>	vect_data;
    //	Set Default Class Properties
    //	Set Default Device Properties
}
//+----------------------------------------------------------------------------
//
// method : 		ControllerClass::write_class_property
// 
// description : 	Set class description as property in database
//
//-----------------------------------------------------------------------------
void ControllerClass::write_class_property()
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
    string	str_title("Device Pool Generic Controller");
    title << str_title;
    data.push_back(title);

    //	Put Description
    Tango::DbDatum	description("Description");
    vector<string>	str_desc;
    str_desc.push_back("A Controller Tango device which is the Tango API for the Device Pool generic controller");
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

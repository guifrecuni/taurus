static const char *RcsId     = "$Header$";
static const char *TagName   = "$Name$";
static const char *HttpServer= "http://www.esrf.fr/computing/cs/tango/tango_doc/ds_doc/";
//+=============================================================================
//
// file :        PseudoMotorClass.cpp
//
// description : C++ source for the PseudoMotorClass. A singleton
//               class derived from DeviceClass. It implements the
//               command list and all properties and methods required
//               by the PseudoMotor once per process.
//
// project :     TANGO Device Server
//
// $Author$
//
// $Revision$
//
// $Log$
// Revision 1.4  2007/08/23 10:33:42  tcoutinho
// - basic pseudo counter check
// - some fixes regarding pseudo motors
//
// Revision 1.3  2007/08/20 06:37:32  tcoutinho
// development commit
//
// Revision 1.2  2007/08/17 13:11:25  tcoutinho
// - pseudo motor restructure
// - pool base dev class restructure
// - initial commit for pseudo counters
//
// Revision 1.1  2007/08/14 07:58:47  tcoutinho
// New initial version of pseudo motor revised
//
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


#include "PseudoMotor.h"
#include "PseudoMotorClass.h"
#include <tango.h>

//+----------------------------------------------------------------------------
/**
 *	Create PseudoMotorClass singleton and return it in a C function for Python usage
 */
//+----------------------------------------------------------------------------
extern "C" {
#ifdef WIN32

__declspec(dllexport)

#endif

	Tango::DeviceClass *_create_PseudoMotor_class(const char *name) {
		return PseudoMotor_ns::PseudoMotorClass::init(name);
	}
}


namespace PseudoMotor_ns
{
//+----------------------------------------------------------------------------
//
// method : 		MoveRelativeClass::execute()
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
CORBA::Any *MoveRelativeClass::execute(Tango::DeviceImpl *device,const CORBA::Any &in_any)
{

	cout2 << "MoveRelativeClass::execute(): arrived" << endl;

	Tango::DevDouble	argin;
	extract(in_any, argin);

	((static_cast<PseudoMotor *>(device))->move_relative(argin));
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

	((static_cast<PseudoMotor *>(device))->abort());
	return new CORBA::Any();
}


//
//----------------------------------------------------------------
//	Initialize pointer for singleton pattern
//----------------------------------------------------------------
//
PseudoMotorClass *PseudoMotorClass::_instance = NULL;

//+----------------------------------------------------------------------------
//
// method : 		PseudoMotorClass::PseudoMotorClass(string &s)
// 
// description : 	constructor for the PseudoMotorClass
//
// in : - s : The class name
//
//-----------------------------------------------------------------------------
PseudoMotorClass::PseudoMotorClass(string &s):DeviceClass(s)
{

	cout2 << "Entering PseudoMotorClass constructor" << endl;
	set_default_property();
	get_class_property();
	write_class_property();
	
	nb_static_attr = 0;
	first_call_to_device_factory = true;
	
	cout2 << "Leaving PseudoMotorClass constructor" << endl;

}
//+----------------------------------------------------------------------------
//
// method : 		PseudoMotorClass::~PseudoMotorClass()
// 
// description : 	destructor for the PseudoMotorClass
//
//-----------------------------------------------------------------------------
PseudoMotorClass::~PseudoMotorClass()
{
	_instance = NULL;
}

//+----------------------------------------------------------------------------
//
// method : 		PseudoMotorClass::instance
// 
// description : 	Create the object if not already done. Otherwise, just
//			return a pointer to the object
//
// in : - name : The class name
//
//-----------------------------------------------------------------------------
PseudoMotorClass *PseudoMotorClass::init(const char *name)
{
	if (_instance == NULL)
	{
		try
		{
			string s(name);
			_instance = new PseudoMotorClass(s);
		}
		catch (bad_alloc)
		{
			throw;
		}		
	}		
	return _instance;
}

PseudoMotorClass *PseudoMotorClass::instance()
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
// method : 		PseudoMotorClass::command_factory
// 
// description : 	Create the command object(s) and store them in the 
//			command list
//
//-----------------------------------------------------------------------------
void PseudoMotorClass::command_factory()
{
	command_list.push_back(new AbortClass("Abort",
		Tango::DEV_VOID, Tango::DEV_VOID,
		"",
		"",
		Tango::OPERATOR));
	command_list.push_back(new MoveRelativeClass("MoveRelative",
		Tango::DEV_DOUBLE, Tango::DEV_VOID,
		"amount to move",
		"",
		Tango::OPERATOR));

	//	add polling if any
	for (unsigned int i=0 ; i<command_list.size(); i++)
	{
	}
}

//+----------------------------------------------------------------------------
//
// method : 		PseudoMotorClass::get_class_property
// 
// description : 	Get the class property for specified name.
//
// in :		string	name : The property name
//
//+----------------------------------------------------------------------------
Tango::DbDatum PseudoMotorClass::get_class_property(string &prop_name)
{
	for (unsigned int i=0 ; i<cl_prop.size() ; i++)
		if (cl_prop[i].name == prop_name)
			return cl_prop[i];
	//	if not found, return  an empty DbDatum
	return Tango::DbDatum(prop_name);
}
//+----------------------------------------------------------------------------
//
// method : 		PseudoMotorClass::get_default_device_property()
// 
// description : 	Return the default value for device property.
//
//-----------------------------------------------------------------------------
Tango::DbDatum PseudoMotorClass::get_default_device_property(string &prop_name)
{
	for (unsigned int i=0 ; i<dev_def_prop.size() ; i++)
		if (dev_def_prop[i].name == prop_name)
			return dev_def_prop[i];
	//	if not found, return  an empty DbDatum
	return Tango::DbDatum(prop_name);
}

//+----------------------------------------------------------------------------
//
// method : 		PseudoMotorClass::get_default_class_property()
// 
// description : 	Return the default value for class property.
//
//-----------------------------------------------------------------------------
Tango::DbDatum PseudoMotorClass::get_default_class_property(string &prop_name)
{
	for (unsigned int i=0 ; i<cl_def_prop.size() ; i++)
		if (cl_def_prop[i].name == prop_name)
			return cl_def_prop[i];
	//	if not found, return  an empty DbDatum
	return Tango::DbDatum(prop_name);
}
//+----------------------------------------------------------------------------
//
// method : 		PseudoMotorClass::device_factory
// 
// description : 	Create the device object(s) and store them in the 
//			device list
//
// in :		Tango::DevVarStringArray *devlist_ptr : The device name list
//
//-----------------------------------------------------------------------------
void PseudoMotorClass::device_factory(const Tango::DevVarStringArray *devlist_ptr)
{

	//	Create all devices.(Automatic code generation)
	//-------------------------------------------------------------
	for (unsigned long i=0 ; i < devlist_ptr->length() ; i++)
	{
		cout4 << "Device name : " << (*devlist_ptr)[i].in() << endl;
						
		// Create devices and add it into the device list
		//----------------------------------------------------
		device_list.push_back(new PseudoMotor(this, (*devlist_ptr)[i]));							 

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
		PseudoMotor *pm_dev = static_cast<PseudoMotor *>(device_list[start_index + i]);
		if (pm_dev->is_add_device_done() == true)
		{
			pm_dev->create_dyn_attr();
			pm_dev->remove_unwanted_dyn_attr_from_device();
		}	
	}	
}
//+----------------------------------------------------------------------------
//	Method: PseudoMotorClass::attribute_factory(vector<Tango::Attr *> &att_list)
//-----------------------------------------------------------------------------
void PseudoMotorClass::attribute_factory(vector<Tango::Attr *> &att_list)
{
	//	Attribute : Position
	PositionAttrib	*position = new PositionAttrib();
	att_list.push_back(position);

	//	Attribute : Instrument
	InstrumentAttrib	*instrument = new InstrumentAttrib();
	instrument->set_disp_level(Tango::EXPERT);
	att_list.push_back(instrument);

	//	End of Automatic code generation
	//-------------------------------------------------------------
}

//+----------------------------------------------------------------------------
//
// method : 		PseudoMotorClass::get_class_property()
// 
// description : 	Read the class properties from database.
//
//-----------------------------------------------------------------------------
void PseudoMotorClass::get_class_property()
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
// method : 	PseudoMotorClass::set_default_property
// 
// description: Set default property (class and device) for wizard.
//              For each property, add to wizard property name and description
//              If default value has been set, add it to wizard property and
//              store it in a DbDatum.
//
//-----------------------------------------------------------------------------
void PseudoMotorClass::set_default_property()
{
	string	prop_name;
	string	prop_desc;
	string	prop_def;

	vector<string>	vect_data;
	//	Set Default Class Properties
	//	Set Default Device Properties
	prop_name = "id";
	prop_desc = "The pseudo motor identifier";
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

	prop_name = "Motor_list";
	prop_desc = "List of motors used by the pseudo motor";
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

	prop_name = "Motor_group";
	prop_desc = "The motor group being used by this pseudo motor";
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

	prop_name = "Role";
	prop_desc = "The role of this pseudo motor in the pseudo motor controller";
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

}
//+----------------------------------------------------------------------------
//
// method : 		PseudoMotorClass::write_class_property
// 
// description : 	Set class description as property in database
//
//-----------------------------------------------------------------------------
void PseudoMotorClass::write_class_property()
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
	string	str_title("Pseudo Motor");
	title << str_title;
	data.push_back(title);

	//	Put Description
	Tango::DbDatum	description("Description");
	vector<string>	str_desc;
	str_desc.push_back("An abstract level that translates a user meaninfull motor operation into");
	str_desc.push_back("a real operation on motor(s).");
	str_desc.push_back("This is done through a mathematical translation function.");
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

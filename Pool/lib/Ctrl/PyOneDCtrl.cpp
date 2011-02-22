#include "PyOneDCtrl.h"
#include "PyUtils.h"

using namespace std;

//+-------------------------------------------------------------------------
//
// method : 		PyOneDController::PyOneDController
//
// description : 	This Python CounterTimer Controller class ctor
//
// argin : - inst : The controller instance name
//	   	   - cl_name : The controller class name
//	  	   - module : The python module object
//		   - prop_dict : The python properties dictionnary
//
//--------------------------------------------------------------------------

PyOneDController::PyOneDController(const char *inst,const char *cl_name,PyObject *module,PyObject *prop_dict)
:PyController(cl_name, module), OneDController(inst)
{
    //cout << "[PyOneDController] class ctor with instance = " << inst << endl;

    clear_method_flag();

//
// Build the string to create the Python controller object
//

    string py_cmd(cl_name);
    py_cmd = py_cmd + "('" + inst_name + "')";

//
// Create the controller object
//

    PyObject *ctrl_class = PyObject_GetAttrString(mod,(char *)cl_name);
    PyObject *arg_tuple = PyTuple_New(2);
    PyObject *arg_str = PyString_FromString(inst);

    if ((ctrl_class == NULL) || (arg_tuple == NULL) || (arg_str == NULL))
    {
        TangoSys_OMemStream o;
        o << "Can't build argument to create Python controller " << cl_name << ends;

        Tango::Except::throw_exception((const char *)"Pool_CantCreatePyController",o.str(),
                        (const char *)"PyOneDController::PyOneDController");
    }

    int insert_res = PyTuple_SetItem(arg_tuple,0,arg_str);
    if (insert_res != 0)
    {
        TangoSys_OMemStream o;
        o << "Can't build argument to create Python controller " << cl_name << ends;

        Tango::Except::throw_exception((const char *)"Pool_CantCreatePyController",o.str(),
                        (const char *)"PyOneDController::PyOneDController");
    }

    insert_res = PyTuple_SetItem(arg_tuple,1,prop_dict);
    if (insert_res != 0)
    {
        TangoSys_OMemStream o;
        o << "Can't build argument to create Python controller " << cl_name << ends;

        Tango::Except::throw_exception((const char *)"Pool_CantCreatePyController",o.str(),
                        (const char *)"PyOneDController::PyOneDController");
    }

    py_obj = PyObject_Call(ctrl_class,arg_tuple,NULL);
    if (py_obj == NULL)
    {
        PyObject *ex_exec,*ex_value,*ex_tb;
        Tango::DevErrorList err_list;
        err_list.length(2);

        PyErr_Fetch(&ex_exec,&ex_value,&ex_tb);
        this->Py_init_dev_error(ex_exec,ex_value,ex_tb,err_list);

        string tmp_str("Can't create Python controller ");
        tmp_str += cl_name;

        err_list[1].origin = CORBA::string_dup("PyOneDController::PyOneDController");
        err_list[1].desc = CORBA::string_dup(tmp_str.c_str());
        err_list[1].reason = CORBA::string_dup("PyCtrl_CantCreatePyController");
        err_list[1].severity = Tango::ERR;

        Py_DECREF(ctrl_class);
        Py_DECREF(arg_tuple);

        throw Tango::DevFailed(err_list);
    }

    Py_DECREF(ctrl_class);
    Py_DECREF(arg_tuple);

//
// Check which methods are defined within this class
//

    check_existing_methods(py_obj);

}

//+-------------------------------------------------------------------------
//
// method : 		PyOneDController::~PyOneDController
//
// description : 	This Python OneD Experiment Channel Controller class dtor
//
//--------------------------------------------------------------------------

PyOneDController::~PyOneDController()
{
    //cout << "[PyOneDController] class dtor" << endl;
    Py_DECREF(py_obj);
}

//+-------------------------------------------------------------------------
//
// method : 		PyOneDController::AddDevice
//
// description : 	Creates a new OneD Experiment Channel for the controller
//
// argin : - ind : The OneDExpChannel index within the controller
//
//--------------------------------------------------------------------------

void PyOneDController::AddDevice(int32_t ind)
{
    //cout << "[PyOneDController] Creating a new OneDExpChannel with index " << ind << " on controller PyOneDController/" << inst_name  << endl;

    AutoPythonGIL lo;

    PyObject *res = NULL;
    res = PyObject_CallMethod(py_obj, (char*)"AddDevice", (char*)"i", ind);
    check_void_return(res,"Error reported from the controller AddDevice method","AddDevice");
}

//+-------------------------------------------------------------------------
//
// method : 		PyOneDController::DeleteDevice
//
// description : 	Delete a OneD Experiment Channel from the controller
//
// argin : - ind : The OneDExpChannel index within the controller
//
//--------------------------------------------------------------------------

void PyOneDController::DeleteDevice(int32_t ind)
{
    //cout << "[PyOneDController] Deleting  OneDExpChannel with index " << ind << " on controller PyOneDController/" << inst_name  << endl;

    AutoPythonGIL lo;

    PyObject *res = NULL;
    res = PyObject_CallMethod(py_obj, (char*)"DeleteDevice", (char*)"i", ind);
    check_void_return(res,"Error reported from the controller DeleteDevice method","DeleteDevice");
}

//+-------------------------------------------------------------------------
//
// method : 		PyOneDController::PreReadAll
//
// description : 	Call the Python controller "PreReadAll" method
//
//--------------------------------------------------------------------------

void PyOneDController::PreReadAll()
{
    if (pre_read_all == true)
    {
        AutoPythonGIL lo;

        PyObject *res = NULL;
        res = PyObject_CallMethod(py_obj, (char*)"PreReadAll", NULL);
        check_void_return(res,"Error reported from the controller PreReadAll method","PreReadAll");
    }
}

//+-------------------------------------------------------------------------
//
// method : 		PyOneDController::PreReadOne
//
// description : 	Call the Python controller "PreReadOne" method
//
// argin : - ind: The OneDExpChannel index within the controller
//
//--------------------------------------------------------------------------

void PyOneDController::PreReadOne(int32_t ind)
{
    if (pre_read_one == true)
    {
        AutoPythonGIL lo;

        PyObject *res = NULL;
        res = PyObject_CallMethod(py_obj, (char*)"PreReadOne", (char*)"i", ind);
        check_void_return(res,"Error reported from the controller PreReadOne method","PreReadOne");
    }
}

//+-------------------------------------------------------------------------
//
// method : 		PyOneDController::ReadAll
//
// description : 	Call the Python controller "ReadAll" method
//
//--------------------------------------------------------------------------

void PyOneDController::ReadAll()
{
    if (read_all == true)
    {
        AutoPythonGIL lo;

        PyObject *res = NULL;
        res = PyObject_CallMethod(py_obj, (char*)"ReadAll", NULL);
        check_void_return(res,"Error reported from the controller ReadAll method","ReadAll");
    }
}

//+-------------------------------------------------------------------------
//
// method : 		PyOneDController::ReadOne
//
// description : 	Read a OneDExpChannel value from the Python controller
//
// argin : - ind : The OneDExpChannel index within the controller
//
//--------------------------------------------------------------------------

double *PyOneDController::ReadOne(int32_t ind)
{

    double *dres = NULL;

    AutoPythonGIL lo;

    PyObject *res = PyObject_CallMethod(py_obj, (char*)"ReadOne", (char*)"i", ind);
// Teresa: ver como hacer esto para ReadOne dando un puntero

    /*  if (res != NULL)
    {
        if (PyNumber_Check(res) == 1)
        {
            if (PyFloat_Check(res) == true)
                dres = PyFloat_AsDouble(res);
            else
                dres = (double)PyInt_AsLong(res);
        }
        else
        {
            Py_DECREF(res);
            Tango::Except::throw_exception(
                    (const char *)"PyCtrl_BadType",
                    (const char *)"The value returned by the controller code is not a Python number as expected",
                     (const char *)"PyOneDController::ReadOne()");
        }
    }
    else
    {
        PyObject *ex_exec,*ex_value,*ex_tb;
        Tango::DevErrorList err_list;
        err_list.length(2);

        PyErr_Fetch(&ex_exec,&ex_value,&ex_tb);
        this->Py_init_dev_error(ex_exec,ex_value,ex_tb,err_list);

        string tmp_str("Can't read the OneDExpChannel value");

        err_list[1].origin = CORBA::string_dup("PyOneDController::ReadOne");
        err_list[1].desc = CORBA::string_dup(tmp_str.c_str());
        err_list[1].reason = CORBA::string_dup("PyCtrl_CantReadValue");
        err_list[1].severity = Tango::ERR;

        throw Tango::DevFailed(err_list);
    }
    */
    Py_DECREF(res);
    return dres;
}


//+-------------------------------------------------------------------------
//
// method : 		PyOneDController::StartOne
//
// description : 	Call the Python controller "StartOne" method
//
// argin : - ind: The OneDExpChannel index within the controller
//
//--------------------------------------------------------------------------

void PyOneDController::StartOne(int32_t ind)
{
    if (start_one == true)
    {
        AutoPythonGIL lo;

        PyObject *res = NULL;
        res = PyObject_CallMethod(py_obj, (char*)"StartOne", (char*)"i", ind);
        check_void_return(res,"Error reported from the controller StartOne method","StartOne");
    }
}


//+-------------------------------------------------------------------------
//
// method : 		PyOneDController::PreStateAll
//
// description : 	Call the Python controller "PreReadAll" method
//
//--------------------------------------------------------------------------

void PyOneDController::PreStateAll()
{
    if (pre_state_all == true)
    {
        AutoPythonGIL lo;

        PyObject *res = NULL;
        res = PyObject_CallMethod(py_obj, (char*)"PreStateAll", NULL);
        check_void_return(res,"Error reported from the controller PreStateAll method","PreStateAll");
    }
}

//+-------------------------------------------------------------------------
//
// method : 		PyOneDController::PreStateOne
//
// description : 	Call the Python controller "PreStateOne" method
//
// argin : - axis: The motor index within the controller
//
//--------------------------------------------------------------------------

void PyOneDController::PreStateOne(int32_t axis)
{
    if (pre_state_one == true)
    {
        AutoPythonGIL lo;

        PyObject *res = NULL;
        res = PyObject_CallMethod(py_obj, (char*)"PreStateOne", (char*)"i", axis);
        check_void_return(res,"Error reported from the controller PreStateOne method","PreStateOne");
    }
}

//+-------------------------------------------------------------------------
//
// method : 		PyOneDController::StateAll
//
// description : 	Call the Python controller "StateAll" method
//
//--------------------------------------------------------------------------

void PyOneDController::StateAll()
{
    if (state_all == true)
    {
        AutoPythonGIL lo;

        PyObject *res = NULL;
        res = PyObject_CallMethod(py_obj, (char*)"StateAll", NULL);
        check_void_return(res,"Error reported from the controller StateAll method","StateAll");
    }
}

//+-------------------------------------------------------------------------
//
// method : 		PyOneDController::StateOne
//
// description : 	Call the Python controller "StateOne" method
//
// argin : - ind: The OneDExpChannel index within the controller
//		   - ptr: Pointer to the structure used to returned a OneD Experiment Channel state
//
//--------------------------------------------------------------------------

void PyOneDController::StateOne(int32_t axis, Controller::CtrlState *ptr)
{
    _StateOne(axis, ptr);
}

//+-------------------------------------------------------------------------
//
// method : 		PyOneDController::SetExtraAttributePar
//
// description : 	Call the Python controller "SetExtraAttribute" method
//
// argin : - axis: The motor index within the controller
//		   - par_name: The parameter name
//		   - par_value: The parameter value
//
//--------------------------------------------------------------------------

void PyOneDController::SetExtraAttributePar(int32_t axis,string &par_name,Controller::CtrlData &par_value)
{
    if (set_extra_attribute == true)
    {
        AutoPythonGIL lo;

        PyObject *res = NULL;
        switch (par_value.data_type)
        {
            case Controller::BOOLEAN:
            res = PySetExtraAttributeBool(py_obj,axis,par_name,par_value.bo_data);
            break;

            case Controller::INT32:
            res = PyObject_CallMethod(py_obj, (char*)"SetExtraAttributePar",
                    (char*)"isi", axis, par_name.c_str(), par_value.int32_data);
            break;

            case Controller::DOUBLE:
            res = PyObject_CallMethod(py_obj, (char*)"SetExtraAttributePar",
                    (char*)"isd", axis, par_name.c_str() ,par_value.db_data);
            break;

            default:
            res = PyObject_CallMethod(py_obj, (char*)"SetExtraAttributePar",
                    (char*)"iss", axis, par_name.c_str(),
                    par_value.str_data.c_str());
            break;
        }
        check_void_return(res,"Error reported from the controller SetExtraAttributePar method","SetExtraAttributePar");
    }
    else
        throw_simple_exception("Method SetExtraAttributePar is not implemented in controller","SetExtraAttributePar");
}

//+-------------------------------------------------------------------------
//
// method : 		PyOneDController::GetExtraAttributePar
//
// description : 	Call the Python controller "GetExtraAttributePar" method
//
// argin : - axis: The motor index within the controller
//		   - par_name: The parameter name
//
//--------------------------------------------------------------------------

Controller::CtrlData PyOneDController::GetExtraAttributePar(int32_t axis,string &extra_par_name)
{
    Controller::CtrlData dres;

    if (get_extra_attribute == true)
    {
        AutoPythonGIL lo;

        PyObject *res = NULL;

        res = PyObject_CallMethod(py_obj, (char*)"GetExtraAttributePar",
                (char*)"is", axis, extra_par_name.c_str());
        if (res != NULL)
        {
            if (PyString_Check(res) == 1)
            {
                dres.str_data = PyString_AsString(res);
                dres.data_type = Controller::STRING;
            }
            else if (PyFloat_Check(res) == 1)
            {
                dres.db_data = PyFloat_AsDouble(res);
                dres.data_type = Controller::DOUBLE;
            }
            else if (PyInt_Check(res) == 1)
            {
                if (PyBool_Check(res) == 1)
                {
                    if (res == Py_False)
                        dres.bo_data = false;
                    else
                        dres.bo_data = true;
                    dres.data_type = Controller::BOOLEAN;
                }
                else
                {
                    dres.int32_data = (int32_t) PyInt_AsLong(res);
                    dres.data_type = Controller::INT32;
                }
            }
            else
            {
                Py_DECREF(res);
                Tango::Except::throw_exception(
                    (const char *)"PyCtrl_BadType",
                    (const char *)"The value returned by the controller code is neither a Python string, a Python float or a Python int as expected",
                    (const char *)"PyController::GetExtraAttributePar()");
            }
        }
        else
        {
            PyObject *ex_exec,*ex_value,*ex_tb;
            Tango::DevErrorList err_list;
            err_list.length(2);

            PyErr_Fetch(&ex_exec,&ex_value,&ex_tb);
            this->Py_init_dev_error(ex_exec,ex_value,ex_tb,err_list);

            string tmp_str("Can't get extra attribute parameter");

            err_list[1].origin = CORBA::string_dup("PyController::GetExtraAttributePar");
            err_list[1].desc = CORBA::string_dup(tmp_str.c_str());
            err_list[1].reason = CORBA::string_dup("PyCtrl_CantGetExtraAttrParameter");
            err_list[1].severity = Tango::ERR;

            throw Tango::DevFailed(err_list);
        }
        Py_DECREF(res);
    }
    else
        throw_simple_exception("Method GetExtraAttributePar is not implemented in controller","GetExtraAttributePar");

    return dres;
}

//+-------------------------------------------------------------------------
//
// method : 		PyOneDController::SendToCtrl
//
// description : 	Call the Python controller "SendToCtrl" method
//
// argin : - in_str: The input string to pass to the controller
//
//--------------------------------------------------------------------------

string PyOneDController::SendToCtrl(string &in_str)
{
    string returned_str("Default string: The controller returns nothing or an invalid data type");

    if (send_to_ctrl == true)
    {
        AutoPythonGIL lo;

        PyObject *res = NULL;
        res = PyObject_CallMethod(py_obj,
                (char*)"SendToCtrl", (char*)"s",
                in_str.c_str());

        if (res != NULL)
        {
            if (PyString_Check(res) == 1)
            {
                returned_str = PyString_AsString(res);
            }
            Py_DECREF(res);
        }
    }
    else
        throw_simple_exception("Method SendToCtrl is not implemented in controller","SendToCtrl");

    return returned_str;
}

//+-------------------------------------------------------------------------
//
// method : 		PyOneDController::clear_method_flag
//
// description : 	Clear all the boolean flags used to memorize which
//					pre-defined method are implemented in this controller
//
//--------------------------------------------------------------------------

void PyOneDController::clear_method_flag()
{
    base_clear_method_flag();

    pre_read_all = false;
    pre_read_one = false;
    read_all = false;
    abort_one = false;
    start_one = false;
    set_par = false;
    get_par = false;
}

//+-------------------------------------------------------------------------
//
// method : 		PyOneDController::check_existing_method
//
// description : 	Check which pre-defined methods are implemented in this
//					controller and set the method flag according to the
//					check result
//					It is not necesseray to check for
//						GetState()
//						ReadOne()
//					because the pool refuses to load controller code if these
//					methods are not defined
//
// argin : - obj : The python controller object
//
//--------------------------------------------------------------------------

void PyOneDController::check_existing_methods(PyObject *obj)
{
    base_check_existing_methods(obj);

    PyObject *met;

    if ((met = PyObject_GetAttrString(obj,"PreReadAll")) != NULL)
    {
        pre_read_all = true;
        Py_DECREF(met);
    }
    else
        PyErr_Clear();

    if ((met = PyObject_GetAttrString(obj,"PreReadOne")) != NULL)
    {
        pre_read_one = true;
        Py_DECREF(met);
    }
    else
        PyErr_Clear();

    if ((met = PyObject_GetAttrString(obj,"ReadAll")) != NULL)
    {
        read_all = true;
        Py_DECREF(met);
    }
    else
        PyErr_Clear();

    if ((met = PyObject_GetAttrString(obj,"StartOne")) != NULL)
    {
        start_one = true;
        Py_DECREF(met);
    }
    else
        PyErr_Clear();

    if ((met = PyObject_GetAttrString(obj,"AbortOne")) != NULL)
    {
        abort_one = true;
        Py_DECREF(met);
    }
    else
        PyErr_Clear();

   if ((met = PyObject_GetAttrString(obj,"GetPar")) != NULL)
    {
        get_par = true;
        Py_DECREF(met);
    }
    else
        PyErr_Clear();

    if ((met = PyObject_GetAttrString(obj,"SetPar")) != NULL)
    {
        set_par = true;
        Py_DECREF(met);
    }
    else
        PyErr_Clear();
}


//+-------------------------------------------------------------------------
//
// method : 		PyOneDController::GetPar
//
// description : 	Call the Python controller "GetPar" method
//
// argin : - axis: The oned index within the controller
//		   - par_name: The parameter name
//
//--------------------------------------------------------------------------

Controller::CtrlData PyOneDController::GetPar(int32_t axis,string &par_name)
{
    Controller::CtrlData dres;

    if (get_par == true)
    {
        AutoPythonGIL lo;

        PyObject *res = NULL;

        res = PyObject_CallMethod(py_obj,
                (char*)"GetPar",
                (char*)"is", axis, par_name.c_str());

        if (res == NULL)
        {
            PyObject *ex_exec,*ex_value,*ex_tb;
            Tango::DevErrorList err_list;
            err_list.length(2);

            PyErr_Fetch(&ex_exec,&ex_value,&ex_tb);
            this->Py_init_dev_error(ex_exec,ex_value,ex_tb,err_list);

            string tmp_str("Can't get oned parameter");

            err_list[1].origin = CORBA::string_dup("PyOneDController::GetPar");
            err_list[1].desc = CORBA::string_dup(tmp_str.c_str());
            err_list[1].reason =
                CORBA::string_dup("PyCtrl_CantGetOneDParameter");
            err_list[1].severity = Tango::ERR;

            throw Tango::DevFailed(err_list);
        }

        if (PyNumber_Check(res) == 1)
        {
            if (par_name == "DataLength")
            {
                if (PyInt_Check(res) == true)
                {
                    dres.int32_data = (int32_t) PyInt_AsLong(res);
                    dres.data_type = Controller::INT32;
                }
                else
                {
                    Py_DECREF(res);
                    Tango::Except::throw_exception(
                        (const char *)"PyCtrl_BadType",
                        (const char *)"The value returned by the controller"
                        " code is not a Python integer as expected",
                        (const char *)"PyOneDController::GetPar()");
                }
            }
            else
            {
                if (PyFloat_Check(res) == true)
                    dres.db_data = PyFloat_AsDouble(res);
                else
                    dres.db_data = (double)PyInt_AsLong(res);
                dres.data_type = Controller::DOUBLE;
            }
        }
        else
        {
            Py_DECREF(res);
            Tango::Except::throw_exception(
                (const char *)"PyCtrl_BadType",
                (const char *)"The value returned by the controller code is"
                " not a Python number as expected",
                (const char *)"PyOneDController::GetPar()");
        }

        Py_DECREF(res);
    }
    else
    {
        cout << "Default GetPar method returning NaN" << endl;
        dres.db_data = strtod("NaN",NULL);
    }

    return dres;
}

//+-------------------------------------------------------------------------
//
// method : 		PyMotorController::SetPar
//
// description : 	Call the Python controller "SetPar" method
//
// argin : - axis: The oned index within the controller
//		   - par_name: The parameter name
//		   - par_value: The parameter value
//
//--------------------------------------------------------------------------

void PyOneDController::SetPar(int32_t axis,string &par_name,
                               Controller::CtrlData &par_value)
{
    if (set_par == true)
    {
        AutoPythonGIL lo;

        PyObject *res = NULL;
        if (par_name == "DataLength")
        {
            if (par_value.data_type == Controller::INT32)
                res = PyObject_CallMethod(py_obj,
                        (char*)"SetPar", (char*)"isi", axis,
                        par_name.c_str(),par_value.int32_data);
            else
                throw_simple_exception("Bad data type used to set DataLength "
                                       "parameter: Long wanted","SetPar");
        }
        else
        {
            if (par_value.data_type == Controller::DOUBLE)
                res = PyObject_CallMethod(py_obj,
                        (char*)"SetPar",
                        (char*)"isd", axis,
                        par_name.c_str(),par_value.db_data);
            else
                throw_simple_exception("Bad data type used to set oned "
                                       "parameters: Double wanted","SetPar");
        }
        check_void_return(res,"Error reported from the controller SetPar method",
                          "SetPar");
    }
    else
        throw_simple_exception("Method SetPar is not implemented in controller",
                               "SetPar");
}


extern "C"
{
Controller *_create_PyOneDExpChannelController(const char *inst,const char *cl_name,PyObject *mo,PyObject *prop)
{
    return new PyOneDController(inst,cl_name,mo,prop);
}
}

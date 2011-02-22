static const char *RcsId = "$Header$";
//+=============================================================================
//
// file :        ClassFactory.cpp
//
// description : C++ source for the class_factory method of the DServer
//               device class. This method is responsible to create
//               all class singletin for a device server. It is called
//               at device server startup
//
// project :     TANGO Device Server
//
// $Author$
//
// $Revision$
//
// $Log$
// Revision 1.1  2007/08/14 07:58:47  tcoutinho
// New initial version of pseudo motor revised
//
//
// copyleft :    European Synchrotron Radiation Facility
//               BP 220, Grenoble 38043
//               FRANCE
//
//-=============================================================================
//
//  		This file is generated by POGO
//	(Program Obviously used to Generate tango Object)
//
//         (c) - Software Engineering Group - ESRF
//=============================================================================


#include <tango.h>
#include <PseudoMotorClass.h>

/**
 *	Create PseudoMotorClass singleton and store it in DServer object.
 */

void Tango::DServer::class_factory()
{

	add_class(PseudoMotor_ns::PseudoMotorClass::init("PseudoMotor"));

}

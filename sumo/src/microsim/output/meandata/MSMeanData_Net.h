#ifndef MSMeanData_Net_h
#define MSMeanData_Net_h
//---------------------------------------------------------------------------//
//                        MSMeanData_Net.cpp -
//  Redirector for mean data output (net->edgecontrol)
//                           -------------------
//  project              : SUMO - Simulation of Urban MObility
//  begin                : Mon, 10.05.2004
//  copyright            : (C) 2004 by Daniel Krajzewicz
//  organisation         : IVF/DLR http://ivf.dlr.de
//  email                : Daniel.Krajzewicz@dlr.de
//---------------------------------------------------------------------------//

//---------------------------------------------------------------------------//
//
//   This program is free software; you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation; either version 2 of the License, or
//   (at your option) any later version.
//
//---------------------------------------------------------------------------//
// $Log$
// Revision 1.2  2004/11/23 10:14:27  dkrajzew
// all detectors moved to microscim/output; new detectors usage applied
//
// Revision 1.1  2004/08/02 12:05:34  dkrajzew
// moved meandata to an own folder
//
// Revision 1.1  2004/07/02 09:01:44  dkrajzew
// microsim output refactoring (moved to a subfolder)
//
/* =========================================================================
 * imported modules
 * ======================================================================= */
#include <microsim/output/MSDetectorFileOutput.h>


/* =========================================================================
 * class declarations
 * ======================================================================= */
class OutputDevice;
class MSEdgeControl;
class MSEdge;
class MSLane;


/* =========================================================================
 * class definitions
 * ======================================================================= */
/**
 * @class MSMeanData_Net
 */
class MSMeanData_Net : public MSDetectorFileOutput
{
public:
    /// constructor
    MSMeanData_Net( unsigned int t, unsigned int index,
        MSEdgeControl &edges,bool addHeaderTail = true );

    /// destructor
    virtual ~MSMeanData_Net();

    virtual void write(XMLDevice &dev,
        MSNet::Time startTime, MSNet::Time stopTime);

    virtual void writeEdge(XMLDevice &dev,
        const MSEdge &edge,
        MSNet::Time startTime, MSNet::Time stopTime);

    virtual void writeLane(XMLDevice &dev,
        const MSLane &lane,
        MSNet::Time startTime, MSNet::Time stopTime);

    friend class MSMeanData_Net_Utils;

    std::string  getNamePrefix( void ) const;
    void writeXMLHeader( XMLDevice &dev ) const;
    virtual void writeXMLOutput( XMLDevice &dev,
        MSNet::Time startTime, MSNet::Time stopTime );
    void writeXMLDetectorInfoStart( XMLDevice &dev ) const;
    void writeXMLDetectorInfoEnd( XMLDevice &dev ) const;
    MSUnit::IntSteps getDataCleanUpSteps( void ) const;

protected:
    /// the time interval the data shall be aggregated over (in s)
    unsigned int myInterval;

    /// Information whether the header information shall be printed
    bool myUseHeader;

    /// The mean data index of this output
    unsigned int myIndex;

    /// The edgecontrol to use
    MSEdgeControl &myEdges;

};


//----------- DO NOT DECLARE OR DEFINE ANYTHING AFTER THIS POINT ------------//

#endif

// Local Variables:
// mode:C++
// End:



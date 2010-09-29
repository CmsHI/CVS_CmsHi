
/** \class HHistID  Ganzhur/HafHistogram/src/HHistID.cc
 *
 * Description:
 * Analysis code of the CMS experiment;
 * Original version is a part of HAF package developed for CMS: UserCode/HAF  
 *
 * This class allows ID numbers, ID strings or both to be used		
 * to uniquely identify histograms.  The actual use of this		
 * class depends on the concrete package that implements HepTuple	
 *
 * \author Marcel Kunze,        Ruhr-University Bochum, Germany 
 *
 * \version $Id: HHistID.cc,v 1.3 2009/11/19 09:40:31 ganzhur Exp $
 *
 */

#include "UserCode/HafHistogram/interface/HHistID.h"

HHistID::HHistID(int theNumber) : 
_numSet(1), 
_stringSet(0),
_idNumber(theNumber),
_idString() {}

HHistID::HHistID(const char * theString) :
_numSet(0), 
_stringSet(1),
_idNumber(0),
_idString(theString) {}

HHistID::HHistID(int theNumber,const char * theString) :
_numSet(1), 
_stringSet(1),
_idNumber(theNumber),
_idString(theString) {}

HHistID::HHistID(const HHistID & other) :
_numSet(other._numSet), 
_stringSet(other._stringSet),
_idNumber(other._idNumber),
_idString(other._idString) {}

// prefix increment number ID
HHistID & HHistID::operator++() { 
    if ( _numSet ) {
	++_idNumber;
    };
    // return this
    return *this; 
}

// postfix increment number ID
const HHistID HHistID::operator++(int) { 
    // initialize result
    HHistID result(*this);
    // increment this 
    ++(*this);
    // return result
    return result; 
}

// prefix decrement number ID
HHistID & HHistID::operator--() { 
    if ( _numSet ) {
	--_idNumber;
    };
    // return this
    return *this; 
}

// postfix decrement number ID
const HHistID HHistID::operator--(int) { 
    // initialize result
    HHistID result(*this);
    // increment this 
    --(*this);
    // return result
    return result; 
}

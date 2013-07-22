#ifndef __IPHC_TREE_DisplayTool_H__
#define __IPHC_TREE_DisplayTool_H__

// STL headers
#include <iostream>

// ROOT headers
#include <TVector2.h>
#include <TVector3.h>
#include <TLorentzVector.h>

std::ostream& operator<< (std::ostream& os, const TLorentzVector& q);
std::ostream& operator<< (std::ostream& os, const TVector2& q);
std::ostream& operator<< (std::ostream& os, const TVector3& q);
 
#endif

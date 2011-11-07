#ifndef __IPHC_TREE_NTTRIGGERPATHTYPE_H__
#define __IPHC_TREE_NTTRIGGERPATHTYPE_H__

// STL headers
#include <iostream>
#include <string>

// ROOT headers
#include <TROOT.h> 

namespace IPHCTree
{

  /// \class TriggerPathType
  struct NTTriggerPathType
  {
    // -------------------------------------------------------------
    //                        data members
    // -------------------------------------------------------------
    std::string name;
    UInt_t prescale;
    bool fired;

    // -------------------------------------------------------------
    //                       method members
    // -------------------------------------------------------------

    /// Constructor without arguments 
    NTTriggerPathType() : prescale(0), fired(false) {}
 
    /// Constructor with arguments
    NTTriggerPathType(const std::string& _name,
                      const UInt_t& _prescale,
                      const Bool_t& _fired) :
      name(_name), prescale(_prescale), fired(_fired) {}

    /// Destructor
    ~NTTriggerPathType() {}

  };

}
 
#endif

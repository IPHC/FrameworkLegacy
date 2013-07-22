#include "../interface/MTPileUp.h"

using namespace IPHCTree;

// ---------------------------------------------------------------------------
// Reset
// ----------------------------------------------------------------------------
void MTPileUp::Reset(bool constructor_call)
{
   if (!constructor_call)
   {
     interactions.clear();
   }
}

  
// ---------------------------------------------------------------------------
// Dump
// ----------------------------------------------------------------------------
void MTPileUp::Dump(std::ostream & os) const
{
  NTPileUp::Dump(os);
  os << " size of bunches = " << interactions.size() << std::endl;

  // List of bunches
  for (std::map<Char_t, std::vector<MTInteraction> >::const_iterator
         it = interactions.begin(); it!=interactions.end(); it++)
  {
    os << " - bunch[" << it->first << "] with nb interactions = ";
    os << it->second.size() << std::endl;    
  }
}


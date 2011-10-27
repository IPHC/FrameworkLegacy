#include "../interface/NTTrigger.h"

using namespace IPHCTree;


// -------------------------------------------------------------------------
// FillTableName
// -------------------------------------------------------------------------
void NTTrigger::FillTableName(const std::string& L1name, const std::string& HLTname)
{
  tablenames_.resize(2);
  tablenames_[0]=L1name;
  tablenames_[1]=HLTname;
}


// -------------------------------------------------------------------------
// FillTriggerResults
// -------------------------------------------------------------------------
void NTTrigger::FillTrigger(const std::map<std::string, 
                            std::pair<UInt_t, Bool_t> >& data)
{
  // Clear all containers : names, prescales, trigger bits
  names_.clear();
  prescales_.resize(data.size(),0);
  results_.resize(data.size(),false);

  // Loop over trigger bit
  unsigned int index=0;
  for (std::map<std::string, std::pair<UInt_t, Bool_t> >::const_iterator
         it = data.begin(); it != data.end(); it++)
  {
    // Add trigger bit name
    names_.insert(it->first);

    // Add trigger prescale
    prescales_[index]=it->second.first;

    // Add results
    results_[index]=it->second.second;

    // Increment index
    index++;
  }
}


// -------------------------------------------------------------------------
// Dump
// -------------------------------------------------------------------------
void NTTrigger::Dump(std::ostream & os) const
{
  //Trigger table
  os << "Trigger information : "  << std::endl;
  os << " L1 table name  = "      << L1name()  << std::endl;
  os << " HLT table name = "      << HLTname() << std::endl; 
  os << " Number of trigger bits = " << results_.size() << std::endl;
  os << " Number of path names = "   << names_.size() << std::endl;
  os << " Number of prescales = "    << prescales_.size() << std::endl;
}



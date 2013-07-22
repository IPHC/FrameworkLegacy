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
// GetSubTable
// -------------------------------------------------------------------------
bool NTTrigger::GetSubTable(const std::string& name, 
                            std::vector<IPHCTree::NTTriggerPathType>& subtable) const
{
  // Clear subtable
  subtable.clear();

  // Safety
  if (name=="") return false;

  // Loop over paths
  for (std::set<std::string>::const_iterator it = names_.begin();
       it != names_.end(); it++)
  {
    if (NameCompatible(name, *it))
    {
      unsigned int index = std::distance(names_.begin(),it);
      subtable.push_back(IPHCTree::NTTriggerPathType(*it,
                                           prescales_[index],
                                           results_[index])    );
    }
  } 

  return (!subtable.empty());
}


// -------------------------------------------------------------------------
// IsFiredWithWildcads
// -------------------------------------------------------------------------
bool NTTrigger::IsFiredWithWildcards(const std::string& name) const
{
  // Safety
  if (name=="") return false;

  // Loop over paths
  for (std::set<std::string>::const_iterator it = names_.begin();
       it != names_.end(); it++)
  {
    if (NameCompatible(*it,name))
    {
      if (results_[std::distance(names_.begin(),it)]) return true;
    }
  } 
  return false;
}


// -------------------------------------------------------------------------
// NameCompatible
// -------------------------------------------------------------------------
bool NTTrigger::NameCompatible(const std::string& pattern,
                               const std::string& name) const
{
  // Easy case : 
  if (name.size() < pattern.size()) return false;
  else if (pattern=="*") return true;

  // Counting number of * in pattern 
  unsigned int sharp_counter=0;
  int sharp_pos=-1;
  for (unsigned i=0; i<pattern.length(); i++)
  { if (pattern[i]=='*') 
    { 
      sharp_counter++;
      if (sharp_pos==-1) sharp_pos=i;
    }
  }

  // no * case
  if (sharp_counter==0) return (pattern==name);

  // 2 or more * case
  else if (sharp_counter>1) return false;

  // only one *
  else
  {
    // '*' at the begin of the name
    if (sharp_pos==0)
    {
      return (pattern.compare(1, // the second character
                              pattern.size()-1, // pattern size without '*'
                              name, 
                              name.size()-pattern.size()+1, 
                              pattern.size()-1 ) == 0); // pattern size without '*'
    }
    else if (static_cast<unsigned int>(sharp_pos)==(pattern.size()-1))
    {
      return (pattern.compare(0, // the beginning
                              pattern.size()-1, // pattern size without '*' 
                              name,
                              0, // the beginning
                              pattern.size()-1) == 0); // pattern size without '*'
    }
    else
    {
      if (!(pattern.compare(0,
                            sharp_pos,
                            name,
                            0,
                            sharp_pos)==0)) return false;

      return (pattern.compare(sharp_pos+1, // the second character
                              pattern.size()-sharp_pos-1, // pattern size without '*'
                              name, 
                              name.size()-pattern.size()+sharp_pos+1, 
                              pattern.size()-sharp_pos-1) == 0); // pattern size without '*'

    }
  }
}


// -------------------------------------------------------------------------
// Print
// -------------------------------------------------------------------------
void NTTrigger::Dump(std::ostream& os) const
{
  // Header
	os << "Object: Trigger Table" << std::endl;
	os << " - L1 table  = " << L1name() << std::endl;
	os << " - HLT table = " << HLTname() << std::endl;
  os << " - Nb paths  = " << results_.size() << std::endl;
  os << "--------------------------------------------------" << std::endl;
  os.width(30);  os << "";
  os << " | fired? | prescale" << std::endl;

  // Loop over paths
  unsigned int index=0;
  for (std::set<std::string>::const_iterator name = names_.begin();
       name != names_.end(); name++)
  {
    //  unsigned int index = std::distance(name,names_.begin());
    os.width(30); os << *name;
    os << " |   " << static_cast<unsigned int>(results_[index]);
    os << "    | " << prescales_[index] << std::endl;
    index++;
  }

  // Foot
  os << "--------------------------------------------------" << std::endl;
}

#ifndef __IPHC_TREE_NTTRIGGER_H__
#define __IPHC_TREE_NTTRIGGER_H__

// STL headers
#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <string>

// ROOT headers
#include <TROOT.h> 

// IPHC headers
#include "NTTriggerPathType.h"


namespace IPHCTree
{

  /// \class NTTrigger
  /// Class related to trigger info for NTuple 
	class NTTrigger
	{
    // -------------------------------------------------------------
    //                        data members
    // -------------------------------------------------------------
	protected:

    /// pointer to the table of prescales
    std::vector<UInt_t>       prescales_;

    /// pointer to the table of trigger bit names
    std::set<std::string>     names_;

    /// trigger bit table
    std::vector<Bool_t>       results_;

    /// trigger table name
    std::vector<std::string>  tablenames_;

    // -------------------------------------------------------------
    //                       method members
    // -------------------------------------------------------------
	public:

    /// Constructor without arguments
		NTTrigger()
    { }

    /// Destructor
		~NTTrigger()
    { }

    /// Clear content of the Trigger
		void Reset()
		{
      names_.clear();
      results_.clear();
      prescales_.clear();
      tablenames_.clear();
		}

		/// \brief Accessor to HLT table name
		const std::string HLTname() const
    { if (tablenames_.size()>=2) return tablenames_[1];
      else return ""; }

		/// \brief Accessor to L1 table name
		const std::string L1name() const
    { if (tablenames_.size()>=1) return tablenames_[0];
      else return ""; }

		/// Is the given trigger path fired
    bool IsFired(const std::string& name) const
    {
      if (name.find("*")!=std::string::npos)
      {
        return results_[GetIndex(name)];
      }
      else
      {
        return IsFiredWithWildcards(name);
      }
    }

		/// Is the given trigger path fired
    UInt_t GetPrescale(const std::string& name) const
    {
      return prescales_[GetIndex(name)];
    }

		/// Is the given trigger path fired
    bool GetSubTable(const std::string& name,
                     std::vector<IPHCTree::NTTriggerPathType>& subtable) const;


    // ---------------- Displaying ---------------------------

		/// Display information related to the MultiCollection
    /// \param[in,out] os   a log stream
    void Dump(std::ostream & os = std::cout) const;

    /// Alias to Dump method
    void PrintInfo(std::ostream & os = std::cout) const
    { Dump(os); }

    void FillTableName(const std::string& L1name, const std::string& HLTname);

    void FillTrigger(const std::map<std::string, 
                                    std::pair<UInt_t, Bool_t> >& data);

  private:

    /// Getting index
    unsigned int GetIndex(const std::string& name) const
    {
      std::set<std::string>::const_iterator found = names_.find(name);
      if (found==names_.end()) 
      {
        std::cout << "ERROR - GetIndex - Trigger" << std::endl;
        return 0;
      }
      return std::distance(names_.begin(),found); 
    }

		/// Is a trigger path consistent with with name fired 
    /// (wildcard '*' is allowed)
    bool IsFiredWithWildcards(const std::string& name) const;


    /// Is the two names are consistent (including wildcard)
    bool NameCompatible(const std::string& pattern,
                        const std::string& name) const;

	};
}
 
#endif

#ifndef __IPHC_TREE_KeyedCollection_H__
#define __IPHC_TREE_KeyedCollection_H__

// STL headers
#include <vector>
#include <iostream>
#include <string>
#include <set>
#include <map>
#include <iterator>
#include <typeinfo>

// IPHC headers
#include "DisplayTool.h"


namespace IPHCTree
{

  class NTTransient;
  class MTTransient;

	template <class T> class KeyedCollection
	{

    friend class IPHCTree::NTTransient;
    friend class IPHCTree::MTTransient;

    // -------------------------------------------------------------
    //                        data members
    // -------------------------------------------------------------
	protected:

    /// transient variable : collection of variable names
    mutable std::set<std::string> names_; //! TRANSIENT

    /// persistent variable : collection of variable values
    std::vector<T> values_;

    // -------------------------------------------------------------
    //                       method members
    // -------------------------------------------------------------
	public:

    /// Constructor without arguments
		KeyedCollection()
    { }

    /// Destructor
		virtual ~KeyedCollection()
    { }

    /// Clear content of the KeyedCollection
		void Reset()
		{
      values_.clear();
      names_.clear();
		}

    /// Typdef
    typedef typename std::vector<T>::iterator       values_iterator;
    typedef typename std::vector<T>::const_iterator const_values_iterator;

    /// Gives number of stored variables
    unsigned int size() const
    { return values_.size(); }

		/// Display information related to the collection
    /// \param[in,out] os   a log stream
    virtual void Dump(std::ostream & os = std::cout) const;

    /// Alias to Dump method
    virtual void PrintInfo(std::ostream & os = std::cout) const
    { Dump(os); }

    //Add a new element
    virtual void Add(const std::string& name,const T& value);

    /// Fill the Collection with a std::map
    void Fill(const std::map<std::string, T>& data);

		/// Get an item 
    const T& Get(const std::string& name) const
    {
      return values_[GetIndex(name)];
    }

		/// Get an item 
    const T& operator[](const std::string& name) const
    {
      return Get(name);
    }

  private:

    /// Getting index
    unsigned int GetIndex(const std::string& name) const
    {
      std::set<std::string>::const_iterator found = names_.find(name);
      if (found==names_.end()) 
      {
        std::cout << "ERROR : KeyedCollection - Cannot find '"
                  << name << "'" << std::endl;
        std::cout << "Available content is : " << std::endl;
        Dump();
        return 0;
      }
      return std::distance(names_.begin(),found); 
    }


	};


  // -------------------------------------------------------------------------
  // Dump
  // --------------------------------------------------------------------------
  template <class T>
  void KeyedCollection<T>::Dump(std::ostream & os) const
  {

    // check event initialization
    if (names_.empty() && !values_.empty())
    {
      os << "ERROR : you have not initialized the event" << std::endl;
    }

    // display number of items
    os << "Number of items : " << names_.size() << std::endl;

    // determining the length of the longest name
    unsigned int maxlength = 0;
    for (std::set<std::string>::const_iterator 
         it = names_.begin(); it != names_.end(); it++)
    {
      if (it == names_.begin() || maxlength < it->size() )
        maxlength=it->size();
    }

    // displaying names
    for (std::set<std::string>::const_iterator
         it = names_.begin(); it != names_.end(); it++)
    {
      os << "  ";
      os.width(maxlength); os << (*it);
      os << " : " << Get(*it) << std::endl;
    }
  }

  // -------------------------------------------------------------------------
  // Fill
  // -------------------------------------------------------------------------
  template <class T>
  void KeyedCollection<T>::Add(const std::string& name,const T& value)
  {
    names_.insert(name);
    values_.push_back(value);
  } 


  // -------------------------------------------------------------------------
  // Fill
  // -------------------------------------------------------------------------
  template <class T>
  void KeyedCollection<T>::Fill(const std::map<std::string,T>& data) 
  {
    // Clear all containers : names, prescales, trigger bits
    names_.clear();
    values_.resize(data.size(),T());

    // Loop over trigger bit
    unsigned int index=0;
    typedef typename std::map<std::string,T>::const_iterator data_iterator;
    for(data_iterator it = data.begin(); it != data.end(); it++)
    {
      // Add trigger bit name
      names_.insert(it->first);

      // Add trigger prescale
      values_[index]=it->second;

      // Increment index
      index++;
    }
  }



}
 
#endif

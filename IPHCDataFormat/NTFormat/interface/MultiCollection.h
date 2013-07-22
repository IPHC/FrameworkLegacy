#ifndef __IPHC_TREE_MULTICOLLECTION_H__
#define __IPHC_TREE_MULTICOLLECTION_H__

// STL headers
#include <vector>
#include <iostream>
#include <string>
#include <set>
#include <stdlib.h>

// ROOT headers
#include <TROOT.h>

namespace IPHCTree
{

  class NTTransient;
  class MTTransient;

	template <class T> class MultiCollection
	{

    friend class IPHCTree::NTTransient;
    friend class IPHCTree::MTTransient;

    // -------------------------------------------------------------
    //                        data members
    // -------------------------------------------------------------
	protected:

    // ------------------- persistent data -------------------------

    /// collection of variable names
    std::vector< std::vector<T> > collections_;

    /// collection of variable names
		std::vector< std::string > names_;

    /// current index
    mutable UInt_t current_index_; //! TRANSIENT

    // -------------------------------------------------------------
    //                       method members
    // -------------------------------------------------------------
	public:

    /// Constructor without arguments
		MultiCollection()
    { current_index_=0; }

    /// Destructor
		~MultiCollection()
    { }

    /// Clear content of the MultiCollection
		void Reset()
		{
      current_index_=0;
      names_.clear();
      collections_.clear();
		}

    /// Creating a new Collection
    void Reserve(const std::set<std::string>& labels)
    {
      // Clear names table
      names_.resize(labels.size(),"");
      collections_.resize(labels.size(),std::vector<T>());

      // Add names
      unsigned int index=0;
      for (std::set<std::string>::const_iterator
             it=labels.begin(); it!=labels.end(); it++)
      {
        names_[index]=(*it);
        index++;
      }

      // Reset index
      current_index_=0;
    }

    /// Changing collection
    void SelectLabel(const std::string& label) const
    {
      for (unsigned int i=0;i<names_.size();i++)
      {
        if (names_[i]==label) {current_index_=i; return; }
      }
      std::cout << "ERROR : MultiCollection - Cannot found label = '" 
                << label << "'" << std::endl;
      std::cout << "Available content is :"<<std::endl;
      Dump();
      current_index_=0;
    }

    // ------- Accessor and Mutator @ Collection level ----------

    /// Getting a collection by its name
    const std::vector<T>* GetCollection(const std::string& name) const
    {
      for (unsigned int i=0;i<names_.size();i++)
      {
        if (names_[i]==name) return &collections_[i];
      }
      return 0;
    }

    /// Getting list of collections
    void GetCollectionList(std::set<std::string>& names) const
    { 
      names.clear();
      for (unsigned int i=0;i<names_.size();i++)
        names.insert(names_[i]);
    }

    /// Check if a collection exist
    bool DoYouKnowCollection(const std::string& name) const
    {
      for (unsigned int i=0;i<names_.size();i++)
        if (names_[i]==name) return true;
      return false;
    }

    // ------- Accessor and Mutator @ Element level ----------

    /// operator [] overloading 
    T& operator[] (unsigned int i)
    { return collections_[current_index_][i]; }

    /// operator [] overloading in readmode
    const T& operator[] (unsigned int i) const
    { return collections_[current_index_][i]; }

    /// return size of the collection
    unsigned int size() const
    { return collections_[current_index_].size(); }

    typedef typename std::vector<T>::iterator iterator;
    typedef typename std::vector<T>::const_iterator const_iterator;
    typedef typename std::vector<T>::reverse_iterator reverse_iterator;
    typedef typename std::vector<T>::const_reverse_iterator 
                                                const_reverse_iterator;

    /// iterator to the begin of the collection
    iterator begin()
    { return collections_[current_index_].begin(); }

    /// iterator to the end of the collection
    iterator end()
    { return collections_[current_index_].end(); }

    /// iterator to the begin of the readmode collection
    const_iterator begin() const
    { return collections_[current_index_].begin(); }

    /// iterator to the end of the readmode collection
    const_iterator end() const
    { return collections_[current_index_].end(); }

    /// iterator to the end of the readmode collection
    reverse_iterator rbegin()
    { return collections_[current_index_].rbegin(); }

    /// iterator to the begin of the collection
    reverse_iterator rend()
    { return collections_[current_index_].rend(); }

    /// iterator to the end of the collection
    const_reverse_iterator rbegin() const
    { return collections_[current_index_].rbegin(); }

    /// iterator to the begin of the readmode collection
    const_reverse_iterator rend() const
    { return collections_[current_index_].rend(); }

    /// Adding an item to the current collection
    /// and getting a pointer to this item
    T* New()
    {
      collections_[current_index_].push_back(T());
      return &(collections_[current_index_].back());
    }

    /// Adding an item to the current collection
    void push_back(const T& item)
    {
      collections_[current_index_].push_back(item);
    }

    // ---------------- Displaying ---------------------------

		/// Display information related to the MultiCollection
    /// \param[in,out] os   a log stream
    void Dump(std::ostream & os = std::cout) const
    {
	
	  if (names_.size()!=collections_.size())
      {
        os << "-- internal problems with KeyedCollection --" << std::endl;
      }
      else
      {
        for (unsigned int i=0;i<names_.size();i++)
        {
          os << names_[i] << " : size = " 
             << collections_[i].size()
             << std::endl;
        }
      }
    }

    /// Alias to Dump method
    void PrintInfo(std::ostream & os = std::cout) const
    { Dump(os); }


	};



}
 
#endif

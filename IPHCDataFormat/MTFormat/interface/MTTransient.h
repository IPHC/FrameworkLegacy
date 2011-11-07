#ifndef __IPHC_TREE_MTTRANSIENT_H__
#define __IPHC_TREE_MTTRANSIENT_H__

// STL headers
#include <vector>
#include <string>
#include <set>
#include <list>


namespace IPHCTree
{

  class MTEvent;

  class MTTransient
  {
  public:

    static void InitializeAfterReading(const IPHCTree::MTEvent* event)
    {
      readmode_SetLeptonCharge(event);
      readmode_SetGenParticleFamily(event);
      readmode_SetKeyedCollectionName(event);
    }

    static void InitializeBeforeWriting(IPHCTree::MTEvent* event)
    {
      writemode_SetLeptonCharge(event);
      writemode_SetKeyedCollectionName(event);
    }

  protected:

    static void readmode_SetLeptonCharge(const IPHCTree::MTEvent* event);
    static void readmode_SetGenParticleFamily(const IPHCTree::MTEvent* event);
    static void readmode_SetKeyedCollectionName(const IPHCTree::MTEvent* event);
    static void writemode_SetLeptonCharge(IPHCTree::MTEvent* event);
    static void writemode_SetKeyedCollectionName(IPHCTree::MTEvent* event);

  };
}


#endif

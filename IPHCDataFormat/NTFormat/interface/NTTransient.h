#ifndef __IPHC_TREE_NTTRANSIENT_H__
#define __IPHC_TREE_NTTRANSIENT_H__

// STL headers
#include <vector>
#include <string>
#include <set>
#include <list>


namespace IPHCTree
{

  class NTEvent;

  class NTTransient
  {
  public:

    static void InitializeAfterReading(const IPHCTree::NTEvent* event)
    {
      readmode_SetLeptonCharge(event);
      readmode_SetGenParticleFamily(event);
      readmode_SetKeyedCollectionName(event);
    }

    static void InitializeBeforeWriting(IPHCTree::NTEvent* event)
    {
      writemode_SetLeptonCharge(event);
      writemode_SetKeyedCollectionName(event);
    }

  protected:

    static void readmode_SetLeptonCharge(const IPHCTree::NTEvent* event);
    static void writemode_SetLeptonCharge(IPHCTree::NTEvent* event);
    static void readmode_SetGenParticleFamily(const IPHCTree::NTEvent* event);
    static void readmode_SetKeyedCollectionName(const IPHCTree::NTEvent* event);
    static void writemode_SetKeyedCollectionName(IPHCTree::NTEvent* event);

  };
}


#endif

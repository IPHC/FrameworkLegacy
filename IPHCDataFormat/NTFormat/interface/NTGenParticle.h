#ifndef __TOP_TREE_NTGENPARTICLE_H__
#define __TOP_TREE_NTGENPARTICLE_H__

#include <TLorentzVector.h>

namespace TopTree
{

  class NTGenParticle
  {
  public :

    TLorentzVector p4;
    Int_t id;
    const NTGenParticle* mother;
    std::vector<NTGenParticle*> daughters;

  public :
 

    NTGenParticle ();
    ~NTGenParticle ();
    void Reset();
    void Dump(std::ostream & os = std::cout);



  };
}

#endif

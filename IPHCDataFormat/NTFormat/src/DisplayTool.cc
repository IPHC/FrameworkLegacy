#include "../interface/DisplayTool.h"


std::ostream& operator<< (std::ostream& os, const TLorentzVector& q)
{
  os << "( " 
     << q.Px() << " , "
     << q.Py() << " , "
     << q.Pz() << " , "
     << q.E()  << " )";
  return os;
}


std::ostream& operator<< (std::ostream& os, const TVector3& q)
{
  os << "( " 
     << q.Px() << " , "
     << q.Py() << " , "
     << q.Pz() << " )";
  return os;
}


std::ostream& operator<< (std::ostream& os, const TVector2& q)
{
  os << "( " 
     << q.Px() << " , "
     << q.Py() << " )";
  return os;
}

#include <string>
using namespace std;


class TimeStamp
{
public:
    TimeStamp():microSecondsSinceEpoch_(0){}

    explicit TimeStamp(int microSecondsSinceEpochArg)
    : microSecondsSinceEpoch_(microSecondsSinceEpochArg)
    {
     }
 

      int microSecondsSinceEpoch() const { return microSecondsSinceEpoch_; }

    

     string toFormattedString() const;

private:
     int microSecondsSinceEpoch_;


};

   inline bool operator<(TimeStamp lhs, TimeStamp rhs)
    {
      return lhs.microSecondsSinceEpoch() < rhs.microSecondsSinceEpoch();
     }

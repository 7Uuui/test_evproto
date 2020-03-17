#include "Timestamp.h"
#include <sys/time.h>
#include <iostream>
#include <stdio.h>
using namespace std;

namespace evproto
{
Timestamp Timestamp::now()
{
struct timeval tv;
gettimeofday(&tv,NULL);
double span = tv.tv_sec + tv.tv_usec / 1000000.0;
//cout<<"Timestamp::now"<<span<<endl;
return Timestamp(span);
}
}

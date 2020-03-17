#include "TimeStamp.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
using namespace std;

string TimeStamp::toFormattedString() const
{
   time_t t = time(NULL);
    printf("UTC:   %s", asctime(gmtime(&t)));
    printf("local: %s", asctime(localtime(&t)));
 

    struct tm buf;
    char str[26];
//    asctime(str,sizeof str,gmtime(&t, &buf));
    printf("UTC:   %s", str);
  //  asctime(str,sizeof str,localtime(&t, &buf)));
    printf("local: %s", str);
    return str;

}

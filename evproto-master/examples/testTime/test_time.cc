#include <iostream>
#include "TimeStamp.h"
using namespace std;

int main(void)
{
  TimeStamp time;
  string str_time = time.toFormattedString();
  cout << str_time << endl;
}

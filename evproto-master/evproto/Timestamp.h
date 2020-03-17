#ifndef TIMESTAMP_H
#define TIMESTAMP_H
namespace evproto
{
class Timestamp
{
public:
Timestamp(){}
explicit Timestamp(double time){}
~Timestamp(){}
static Timestamp now();

};
}
#endif

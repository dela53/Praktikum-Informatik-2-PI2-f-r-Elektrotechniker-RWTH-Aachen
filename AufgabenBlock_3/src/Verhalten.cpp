#include "Verhalten.h"

Verhalten::Verhalten() : p_pWeg()
{
}

Verhalten::Verhalten(Weg& weg) : p_pWeg(&weg)
{
}

Verhalten::~Verhalten()
{
}

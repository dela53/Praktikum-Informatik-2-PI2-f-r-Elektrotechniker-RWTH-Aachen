#include "Fahrausnahme.h"
#include "Fahrzeug.h"
#include "Weg.h"

Fahrausnahme::Fahrausnahme(Fahrzeug& fzg, Weg& weg) : p_pFahrzeug(fzg), p_pWeg(weg)
{

}


Fahrausnahme::~Fahrausnahme()
{

}

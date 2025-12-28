#include "Parken.h"
#include "Fahrzeug.h"
#include "Verhalten.h"
#include "Losfahren.h"
#include <math.h>

extern double dGlobaleZeit;

Parken::Parken()
{
}

Parken::Parken(Weg& weg) : Verhalten(weg)
{
}

Parken::Parken(Weg& weg, double dStartzeitpunkt) : Verhalten(weg), p_dStartzeitpunkt(dStartzeitpunkt)
{
}

Parken::~Parken()
{
}


double Parken::dStrecke(Fahrzeug& fzg, double dZeitIntervall)
{
	if(!p_pWeg ) return 0.0;

	const double epsilon = 0.000001; // Fehlertoleranz

	// Startzeit überschritten Meldung
	if (!p_bErreicht && dGlobaleZeit + epsilon >= p_dStartzeitpunkt)
	{
		p_bErreicht = true;
		// Wirft ein Objekt dass das Zeitstartpunkt erreicht wurde (Ausnahme)
		throw Losfahren(fzg, *p_pWeg);
	}
	return 0.0;
}

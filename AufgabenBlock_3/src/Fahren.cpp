#include "Fahren.h"
#include "Fahrzeug.h"
#include "Verhalten.h"
#include "Streckenende.h"
#include "Weg.h"

#include <algorithm>
#include <iostream>
#include <cmath>

Fahren::Fahren()
{
}

Fahren::Fahren(Weg& weg) : Verhalten(weg)
{
}

Fahren::~Fahren()
{
}

// Funktion die die Strecke berechnet die das Fahrzeug fahren kann
double Fahren::dStrecke(Fahrzeug& fzg, double dZeitIntervall)
{
	// überprüft ob die Funktion überhaubt ausgeführt werden kann
	if (!p_pWeg || dZeitIntervall <= 0.0) return 0.0;

	const double epsilon = 0.000001; // Fehlertoleranz
	double dMoeglicheStrecke = fzg.dGeschwindigkeit() * dZeitIntervall;
	double dPlatz = p_pWeg->getLaenge() - fzg.getAbschnittStrecke();
	// Bei Überholverbot ist der Platz beschränkt auf das vordere Fahrzeug. Sonst gibt es keine Schranke
	double dPlatzSchranke = p_pWeg->getVirtuelleSchranke() - fzg.getAbschnittStrecke();
	// Kleinere Strecke wird übergeben
	double dPlatzEffektiv = std::min(dPlatz, dPlatzSchranke);


	// Gibt eine einmalige Meldung, wenn der Weg erreicht wurde.
	if (dPlatzEffektiv <= epsilon)
	{
		if (dPlatz <= epsilon)
		{
			if (!p_bErreicht && dPlatz <= epsilon)
			{
				p_bErreicht = true;

				// Wirft ein Objekt dass das Streckenende erreicht wurde (Ausnahme)
				throw Streckenende(fzg, *p_pWeg);
			}
	    }
		//Schranke schon erreicht
		return 0.0;
	}
	return std::min(dMoeglicheStrecke, dPlatzEffektiv);
  }



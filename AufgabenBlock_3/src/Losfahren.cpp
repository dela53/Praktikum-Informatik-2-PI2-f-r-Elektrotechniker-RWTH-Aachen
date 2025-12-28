#include "Losfahren.h"

extern double dGlobaleZeit;

Losfahren::Losfahren(Fahrzeug& fzg, Weg& weg) : Fahrausnahme(fzg, weg)
{
}


Losfahren::~Losfahren()
{
}

void Losfahren::vBearbeiten()
{
		std::cout << p_pFahrzeug.getName()
				  << " ist in Minute " << dGlobaleZeit << " auf dem Weg \""
				  << p_pWeg.getName() << "\" abgefahren \n";

		// Löschen aus dem Weg als parkendes Fahrzeug
		std::unique_ptr<Fahrzeug> losfahren = p_pWeg.pAbgabe(p_pFahrzeug);

		// Auto auf dem Weg als fahrend wieder hinzufügen. Ein Parameter --> fahrend
		p_pWeg.vAnnahme(std::move(losfahren));
}

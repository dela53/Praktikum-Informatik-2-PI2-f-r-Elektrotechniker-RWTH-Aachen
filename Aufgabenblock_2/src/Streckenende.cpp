#include "Streckenende.h"

Streckenende::Streckenende(Fahrzeug& fzg, Weg& weg) : Fahrausnahme(fzg, weg)
{
	// TODO Auto-generated constructor stub

}

Streckenende::~Streckenende()
{
	// TODO Auto-generated destructor stub
}

void Streckenende::vBearbeiten()
{
	 std::cout << p_pFahrzeug.getName()
			   << " ist am Ende des Weges \""
			   << p_pWeg.getName() << "\" angekommen.\n";

	 std::unique_ptr<Fahrzeug> abgabe = p_pWeg.pAbgabe(p_pFahrzeug);

}

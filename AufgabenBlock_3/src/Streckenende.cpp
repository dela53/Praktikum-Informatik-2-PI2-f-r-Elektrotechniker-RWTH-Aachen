#include "Streckenende.h"

Streckenende::Streckenende(Fahrzeug& fzg, Weg& weg) : Fahrausnahme(fzg, weg)
{
}

Streckenende::~Streckenende()
{
}

void Streckenende::vBearbeiten()
{
	 std::cout << p_pFahrzeug.getName()
			   << " ist am Ende des Weges \""
			   << p_pWeg.getName() << "\" angekommen.\n";

	 auto abgabe = p_pWeg.pAbgabe(p_pFahrzeug);
	 if (!abgabe)
	 {
	         std::cerr << "Streckenende: pAbgabe hat kein Fahrzeug zurückgegeben!\n" << std::endl;
	         return;
	 }

	 // Nötig für die vorherigen Aufgaben bis 6, da es noch keine Zielkreuzungen gibt. Hat immer Probleme gemacht
	 auto zielKreuzung = p_pWeg.getZielkreuzung();
	 if (!zielKreuzung)
	 {
	         std::cerr << "Streckenende: Zielkreuzung ist nullptr! Fahrzeug wird gelöscht.\n" << std::endl;
	         return;
	 }

	 auto neuerWeg = zielKreuzung->pZufaelligerWeg(p_pWeg);
	 if (!neuerWeg)
	 {
	         std::cerr << "Streckenende: pZufaelligerWeg lieferte nullptr!\n" << std::endl;
	         return;
	 }

	 zielKreuzung->vTanken(*abgabe);

	 std::cout << "ZEIT : " << dGlobaleZeit << "\n";
	 std::cout << "KREUZUNG : " << zielKreuzung->getName() << " (Tank: " << zielKreuzung->getTankstelle() << ")\n";
	 std::cout << "WECHSEL : " << p_pWeg.getName() << " -> " << neuerWeg->getName() << "\n";
	 std::cout << "FAHRZEUG : " << std::endl;
	 Fahrzeug::vKopf();
	 std::cout << "  " << *abgabe;

	 // Neuer Weg nimmt fahrendes Fahrzeug an
	 neuerWeg->vAnnahme(std::move(abgabe));
}

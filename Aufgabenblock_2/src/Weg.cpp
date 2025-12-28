#include "Weg.h"
#include "Simulationsobjekt.h"
#include "Tempolimit.h"
#include "Fahrzeug.h"
#include "Fahrausnahme.h"
#include "vertagt_liste.h"

#include <limits>
#include <iostream>
#include <iomanip>
#include <string>
#include <list>

Weg::Weg() : Simulationsobjekt(), p_dLaenge(20), p_eTempolimit(Tempolimit::AUTOBAHN) // default
{
}

Weg::Weg(std::string sName, double dLaenge, Tempolimit eTempolimit) : Simulationsobjekt(sName), p_dLaenge(dLaenge), p_eTempolimit(eTempolimit)
{
}

Weg::~Weg()
{
}

// Simuliert alle auf dem Weg befindlichen Fahrzeuge durch eine range-based Schleife und fängt Fahrausnahmen ab
void Weg::vSimulieren()
{
	// Aktualisierung der Fahrzeuge, falls nicht aktualisiert
	p_pFahrzeuge.vAktualisieren();

	// Schleife über alle Fahrzeuge welche versucht sie zu simulieren und ggf. Ausnahmen abfängt und demenstprechent handelt
	for (auto it = p_pFahrzeuge.begin(); it != p_pFahrzeuge.end(); it++)
	{
		try
		{
		(*it)->vSimulieren();
		}
		catch (Fahrausnahme& fahrausnahme)
		{
			fahrausnahme.vBearbeiten();
		}
	}
	// Aktualisierung der Fahrzeuge
	p_pFahrzeuge.vAktualisieren();
}

void Weg::vAusgeben()
{
	std::cout << std::resetiosflags(std::ios::adjustfield) << std::setiosflags(std::ios::left)
	   << std::setw(5)  << p_iID
	   << std::setw(15) << p_sName
	   << std::setw(15) << p_dLaenge
	   << std::setw(15) << std::setw(30) << "( ";

	  for (auto it = p_pFahrzeuge.begin(); it != p_pFahrzeuge.end(); it++)
	  {
		  std::cout << (*it)->getName() << " ";
	  }

	std::cout << ")" << std::endl;
	// ab hier rechtsbündig
	std::cout << std::resetiosflags(std::ios::adjustfield) << std::setiosflags(std::ios::right)
	   << std::fixed << std::setprecision(1)
	   << '\n'
	   << std::setfill('-') << std::setw(85) << "-" << '\n' << std::setfill(' ');
}

std::ostream& Weg::vAusgeben(std::ostream& o) const
{
	o << std::resetiosflags(std::ios::adjustfield) << std::setiosflags(std::ios::left)
	   << std::setw(5)  << p_iID
	   << std::setw(15) << p_sName
	   << std::setw(15) << p_dLaenge
	   << "( ";

	  for (auto it = p_pFahrzeuge.begin(); it != p_pFahrzeuge.end(); it++)
	  {
		  o << (*it)->getName() << "  ";
	  }

	o << ")" << std::endl;
	// ab hier rechtsbündig
	o  << std::resetiosflags(std::ios::adjustfield) << std::setiosflags(std::ios::right)
	   << std::fixed << std::setprecision(1)
	   << '\n'
	   << std::setfill('-') << std::setw(85) << "-" << '\n' << std::setfill(' ');
	return o;
}

void Weg::vKopf()
{
	std::cout << std::resetiosflags(std::ios::adjustfield)   // alles zurücksetzen
	   << std::setiosflags(std::ios::left)            // Überschriften links
	   << std::setw(5)  << "| ID"
	   << std::setw(15) << "| Name"
	   << std::setw(15) << "| Länge"
	   << std::setw(30) << "| Fahrzeuge"
	   << std::endl
	   << std::setfill('-')
	   << std::setw(85) << "-" << std::endl << std::setfill(' ');
}


///////////////// getter-Funktionen ///////////////////////////
double Weg::getTempolimit()
{
	switch (p_eTempolimit)
	{
	case INNERORTS:
		return 50.0;
	case LANDSTRASSE:
		return 100.0;
	case AUTOBAHN:
		return std::numeric_limits<double>::max();
	default:
		return std::numeric_limits<double>::max();
	}
}

const double Weg::getLaenge() const
{
	return p_dLaenge;
}

const vertagt::VListe<std::unique_ptr<Fahrzeug>>& Weg::getFahrzeuge() const
{
		return p_pFahrzeuge;
}
//////////////////////////////////////////////////////////////

void Weg::vAnnahme(std::unique_ptr<Fahrzeug> fzg)
{
	if(!fzg) return; // damit kein nullptr als Fahrzeug ensteht

	// Setzen des Fahrzeugs auf den neuen Weg
    fzg->vNeueStrecke(*this);   // (fzg->fahren() Ruf die Methode fahren() auf dem Objekt auf, auf das autoPtr zeigt.)

    // Setzen des Fahrzeugs auf die Fahrzeugliste des Weges
    p_pFahrzeuge.push_back(std::move(fzg)); // move da unique-ptr nicht kopiert werden kann // auto.fahren() Ruf die Methode fahren() auf dem Objekt auto auf

    // Aktualisierung der Fahrzeuge
    p_pFahrzeuge.vAktualisieren();

}


void Weg::vAnnahme(std::unique_ptr<Fahrzeug> fzg, double dStartzeitpunkt)
{
	if(!fzg) return; // damit kein nullptr als Fahrzeug ensteht

	// Setzen des Fahrzeugs auf den neuen Weg
    fzg->vNeueStrecke(*this, dStartzeitpunkt);   //(fzg->fahren() Ruf die Methode fahren() auf dem Objekt auf, auf das autoPtr zeigt.)

    // Setzen des Fahrzeugs auf die Fahrzeugliste des Weges
    p_pFahrzeuge.push_front(std::move(fzg));

    // Aktualisierung der Fahrzeuge
    p_pFahrzeuge.vAktualisieren();

}

/* Läuft die Liste durch un sucht das Fahrzeug welches abgegeben werden muss.
 * Das Fahrzeug wird aus der Liste gelöscht und zurückgegeben
 */
std::unique_ptr<Fahrzeug> Weg::pAbgabe(const Fahrzeug& fzg)
{
	for (auto it = p_pFahrzeuge.begin(); it != p_pFahrzeuge.end(); it++)
	{
		if (!(*it)) continue; // Sonderfall nullptr
// it zeiger auf std::unique_ptr<Fahrzeug>, *it Zeiger auf unique_ptr<Fahrzeug>, **it Zeiger auf Fahrzeug& (Referenz) bzw. Objekt selbst. Fahrzeug (Kopie)
		if (*(*it) == fzg)
		{
			std::unique_ptr<Fahrzeug> fzgGefunden = std::move(*it);
			p_pFahrzeuge.erase(it); // Löschen aus der Liste sonst bleibt ein nullptr in der Liste
			return fzgGefunden;
		}
	}
	// Aktualisierung der Fahrzeuge
	p_pFahrzeuge.vAktualisieren();

	return nullptr; // Fahrzeug nicht gefunden
}


// Überladung des << Operators
std::ostream& operator<<(std::ostream& o, Weg& weg)
{
	weg.vAusgeben(o);
	return o;
}

#include "Fahrzeug.h"
#include "Verhalten.h"
#include "Parken.h"
#include "Fahren.h"

#include <iostream>
#include <string>
#include <iomanip>
#include <ostream>

int Fahrzeug::p_iMaxID = 0; // statische Variable
extern double dGlobaleZeit;

Fahrzeug::Fahrzeug() : p_iID(++p_iMaxID) // Initialisierungsliste. Initialisieren bevor erzeugen. Danach darf nicht mehr geändert werden.
{
	//std::cout << "\nFahrzeug erzeugt: " << "  | Name: " << p_sName << " | ID: " << p_iID << std::endl;
}

Fahrzeug::Fahrzeug(const std::string& p_sNameInput) : p_sName(p_sNameInput), p_iID(++p_iMaxID) // p_sNameInput ist der Parameter des Konstruktors
{
	//std::cout << "\nFahrzeug erzeugt: " << "  | Name: " << p_sName << " | ID: " << p_iID << std::endl;
}

Fahrzeug::Fahrzeug(const std::string& p_sNameInput, double maxSpeed) : p_sName(p_sNameInput), p_iID(++p_iMaxID), p_dMaxGeschwindigkeit(maxSpeed > 0 ? maxSpeed : 0.0)
{
	//std::cout << "\nFahrzeug erzeugt: " << "  | Name: " << p_sName << " | ID: " << p_iID << " | Max Speed: " << p_dMaxGeschwindigkeit << "km/h" << std::endl;
}

Fahrzeug::~Fahrzeug()
{
	//std::cout << "\nFahrzeug gelöscht: " << " | Name: " << p_sName << " | ID: " << p_iID << std::endl;
}

void Fahrzeug::vAusgeben()
{
 std::cout << std::resetiosflags(std::ios::adjustfield) << std::setiosflags(std::ios::left)
	   << std::setw(5)  << p_iID
	   << std::setw(15) << p_sName
	   // ab hier rechtsbündig
	   << std::resetiosflags(std::ios::adjustfield) << std::setiosflags(std::ios::right)
	   << std::fixed << std::setprecision(1)
	   << std::setw(25) << p_dMaxGeschwindigkeit
	   << std::setw(25) << dGeschwindigkeit()
	   << std::setw(25) << p_dGesamtStrecke
	   << std::setw(30) << p_dAbschnittStrecke
	   // Platzhalter
	   << std::setw(25) << "-"                    // Gesamtverbrauch
	   << std::setw(25) << "-"                    // Tankinhalt
	   << '\n'
	   << std::setfill('-') << std::setw(140) << "-" << '\n' << std::setfill(' ');
}


void Fahrzeug::vAusgeben(std::ostream& o) const
{
	o << std::resetiosflags(std::ios::adjustfield) << std::setiosflags(std::ios::left)
	   << std::setw(5)  << p_iID
	   << std::setw(15) << p_sName
	   // ab hier rechtsbündig
	   << std::resetiosflags(std::ios::adjustfield) << std::setiosflags(std::ios::right)
	   << std::fixed << std::setprecision(1)
	   << std::setw(25) << p_dMaxGeschwindigkeit
	   << std::setw(25) << dGeschwindigkeit()
	   << std::setw(25) << p_dGesamtStrecke
	   << std::setw(30) << p_dAbschnittStrecke
	   // Platzhalter
	   << std::setw(25) << "-"                    // Gesamtverbrauch
	   << std::setw(25) << "-"                    // Tankinhalt
	   << '\n'
	   << std::setfill('-') << std::setw(150) << "-" << '\n' << std::setfill(' ');
}

void Fahrzeug::vKopf()
{
	std::cout << std::resetiosflags(std::ios::adjustfield)   // alles zurücksetzen
	   << std::setiosflags(std::ios::left)            // Überschriften links
	   << std::setw(5)  << "| ID"
	   << std::setw(15) << "| Name"
	   << std::setw(35) << "| Maximal-Geschwindigkeit(km/h)"
	   << std::setw(25) << "| Geschwindigkeit(km/h)"
	   << std::setw(25) << "| Gesamtstrecke(km)"
	   << std::setw(25) << "| Abschnitt(km)"
	   << std::setw(25) << "| Gesamtverbrauch(Liter)"
	   << std::setw(25) << "| Tankinhalt(Liter)"
	   << std::endl
	   << std::setfill('-')
	   << std::setw(150) << "-" << std::endl << std::setfill(' ');
}

void Fahrzeug::vSimulieren()
{
	// Überprüfen, ob schon in dieser Zeit schon simuliert wurde
	if (p_dZeit >= dGlobaleZeit) return;

	const double p_dVergangeneZeit = dGlobaleZeit - p_dZeit;

	double dTeilstrecke = 0;
	// Bei jedem Takt wird berechnet wie Weit das Fahrzeug fahren darf. Falls Parkend --> 0km
	if (p_pVerhalten)
	{
	   dTeilstrecke = p_pVerhalten->dStrecke(*this, p_dVergangeneZeit); //*this = aktueller Fahrzeug
    }

    // Strecke bzw. Weg aktualisieren
	p_dGesamtStrecke    += dTeilstrecke; // für Ausgabe
	p_dAbschnittStrecke += dTeilstrecke; // für verbleibende Strecke

	// Zeit aktualisieren
	p_dGesamtZeit += p_dVergangeneZeit;
	p_dZeit = dGlobaleZeit;
}

// Standard-Wert Null
double Fahrzeug::dTanken(double dMenge)
{
	return dMenge = 0.0;
}

double Fahrzeug::dGeschwindigkeit() const
{
	return p_dMaxGeschwindigkeit;
}

void Fahrzeug::vNeueStrecke(Weg& weg)
{
	p_pVerhalten = std::make_unique<Fahren>(weg);
}

void Fahrzeug::vNeueStrecke(Weg& weg, double dStartzeitpunkt)
{
	p_pVerhalten = std::make_unique<Parken>(weg, dStartzeitpunkt);
}

// Überladung des << Operators
// Warum außerhalb der Klasse? Weil cout nicht zur Fahrzeug-Klasse gehört sondern zu ostream.
// Wenn man es in der Klasse überladen würde dann wäre es verkehrt herum
// Was istf friend? Erlaubt es ein private Member auszugeben. --> unschön
std::ostream& operator<<(std::ostream& o, const Fahrzeug& fahrzeug) // Bedeutung cout << fahrzeug
{
	fahrzeug.vAusgeben(o);
	return o;
}

bool Fahrzeug::operator<(const Fahrzeug& fahrzeug) const
{
	return (p_dGesamtStrecke < fahrzeug.p_dGesamtStrecke);
}

// Überladener (=) Operator welcher das kopieren erlaubt im erlaubten Rahmen.
// Dabei wird die ID nicht kopiert da es Konstant ist und außerdem nicht erlaubt ist.
Fahrzeug& Fahrzeug::operator=(const Fahrzeug& fahrzeug)
{
	p_sName = fahrzeug.p_sName;
	p_dMaxGeschwindigkeit = fahrzeug.p_dMaxGeschwindigkeit;
	p_dGesamtStrecke = fahrzeug.p_dGesamtStrecke;
	p_dGesamtZeit = fahrzeug.p_dGesamtZeit;
	p_dZeit = fahrzeug.p_dZeit;
	return *this; // Gibt Referenz auf sich selber (Fahrzeug) zurück
}

#include "PKW.h"
#include "SimuClient.h"

#include <iostream>
#include <string>
#include <iomanip>
#include <ostream>

extern double dGlobaleZeit;

PKW::PKW()
{
	std::cout << "\nPKW erzeugt " << " | ID: " << p_iID << "\n" << std::endl;
}

PKW::PKW(std::string sName) : Fahrzeug(sName)
{
	std::cout << "\nPKW erzeugt: " << " | Name: " << p_sName << " | ID: " << p_iID << "\n" << std::endl;
}

PKW::PKW(std::string sName, double dMaxGeschwindigkeit) : Fahrzeug(sName, dMaxGeschwindigkeit)
{
	std::cout << "\nPKW erzeugt: " << "  | Name: "
			  << p_sName << " | ID: " << p_iID
			  << " | Max Speed: " << p_dMaxGeschwindigkeit << "km/h"
			  << "\n" << std::endl;
}

PKW::PKW(std::string sName, double dMaxGeschwindigkeit, double dVerbrauch = 8.0, double dTankvolumen)
: Fahrzeug(sName, dMaxGeschwindigkeit), p_dVerbrauch(dVerbrauch), p_dTankvolumen(dTankvolumen), p_dTankinhalt(dTankvolumen/2)
{
	std::cout << "\nPKW erzeugt: "
			  << " | Name: " << sName << " | ID: " << p_iID
			  << " | Max Speed: " << p_dMaxGeschwindigkeit << "km/h"
			  << " | Verbrauch:" << p_dVerbrauch << "Liter | Tankvolumen: "
			  << p_dTankvolumen << " Liter | Tankinhalt: " << p_dTankinhalt
			  << " Liter" << "\n" << std::endl;
}

// Destruktor
PKW::~PKW()
{
	std::cout << "\nPKW gelöscht: " << " | Name: " << p_sName << " | ID: " << p_iID << std::endl;
}

// Überschriebener Funktion für das Tanken eines PKWs
double PKW::dTanken(double dMenge)
{
	// wenn die Menge größer ist dann volltanken
	if (dMenge >= p_dTankvolumen - p_dTankinhalt)
	{
		p_dTankinhalt = p_dTankvolumen;
		dMenge = p_dTankvolumen - p_dTankinhalt;
		return dMenge;
	}
	p_dTankinhalt += dMenge;
	return dMenge;
}

void PKW::vSimulieren()
{
	// Wenn Tank leer, soll nicht mehr simuliert werden.
	if (p_dTankinhalt == 0.0)
	{
		p_dZeit = dGlobaleZeit; // Bedeutung: wurde schon simuliert
		return;
	}
	// zurückgelegte Strecke speichern
	double dGesamtStreckeVor = p_dGesamtStrecke;
	// Zeitsimulation um die zurückgelegte Strecke zu aktualisieren
	Fahrzeug::vSimulieren();
	// Definition von Verbrauch ------> Liter/100km deshalb durch 100km
	p_dTankinhalt -= p_dVerbrauch * (p_dGesamtStrecke - dGesamtStreckeVor)/100;
	// Tankinhalt negativ ausschließen
	if(p_dTankinhalt < 0.0) p_dTankinhalt = 0.0;
}

void PKW::vAusgeben()
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
	   << std::setw(25) << p_dAbschnittStrecke
	   << std::setw(25) << (p_dVerbrauch*p_dGesamtStrecke/100.0)   // Gesamtverbrauch
	   << std::setw(25) << p_dTankinhalt              // Tankinhalt
	   << '\n'
	   << std::setfill('-') << std::setw(150) << "-" << '\n' << std::setfill(' ');
}

// Überladung des << Operators
void PKW::vAusgeben(std::ostream& o) const
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
	   << std::setw(25) << p_dAbschnittStrecke
	   << std::setw(25) << (p_dVerbrauch*p_dGesamtStrecke/100.0)   // Gesamtverbrauch
	   << std::setw(25) << p_dTankinhalt              // Tankinhalt
	   << '\n'
	   << std::setfill('-') << std::setw(185) << "-" << '\n' << std::setfill(' ');
}

// Gibt die kleinste Geschwindigkeit zurück, um das Tempolimit nicht zu überschreiten
double PKW::dGeschwindigkeit() const
{
	// kein Verhalten, keine Straße, keine Begrenzung
	 if (!p_pVerhalten) return p_dMaxGeschwindigkeit;

	 // p_pVerhalten aus Fahrzeug von Datentyp Weg
	 double dLimit = p_pVerhalten->getWeg()->getTempolimit();

	return std::min(dLimit, p_dMaxGeschwindigkeit);
}

// Berechnet die echte Position des PKWs und zeichnet sie auf dem Weg
void PKW::vZeichnen(const Weg& weg) const
{
	 double relPosition = p_dAbschnittStrecke / weg.getLaenge();
	 bZeichnePKW(p_sName,weg.getName(), relPosition, dGeschwindigkeit(), p_dTankinhalt);
}

void PKW::vEinlesen(std::istream& c)
{
	// Überprüft ob Name leer ist
	std::string sName;
	double dMaxGeschwindigkeit;
	double dVerbrauch;
	double dTankvolumen;

	c >> sName;
	p_sName = sName;

	c >> dMaxGeschwindigkeit;
	p_dMaxGeschwindigkeit = dMaxGeschwindigkeit;

	c >> dVerbrauch;
	p_dVerbrauch = dVerbrauch;

	c >> dTankvolumen;
	p_dTankvolumen = dTankvolumen;

	// wirft einen Fehler wenn Name schon gesetzt ist
	if (!c) throw std::runtime_error("PKW::vEinlesen: Name wurde schon gesetzt.");
}

PKW& PKW::operator=(const PKW& pkw)
{
	p_sName = pkw.p_sName;
	p_dMaxGeschwindigkeit = pkw.p_dMaxGeschwindigkeit;
	p_dGesamtStrecke = pkw.p_dGesamtStrecke;
	p_dGesamtZeit = pkw.p_dGesamtZeit;
	p_dZeit = pkw.p_dZeit;
	p_dVerbrauch = pkw.p_dVerbrauch;
	p_dTankinhalt = pkw.p_dTankinhalt;
	p_dTankvolumen = pkw.p_dTankvolumen;
	return *this; // Gibt Referenz auf sich selber (Fahrzeug) zurück
}

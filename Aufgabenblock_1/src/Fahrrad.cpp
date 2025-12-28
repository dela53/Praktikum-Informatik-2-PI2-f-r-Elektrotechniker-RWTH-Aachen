#include "Fahrrad.h"
#include <math.h>
#include <iomanip>
#include <ostream>

Fahrrad::Fahrrad() : Fahrzeug()
{
	std::cout << "Fahrrad erzeugt " << " | ID: " << p_iID << std::endl;
}

// Konstruktor
Fahrrad::Fahrrad(std::string sName, double dMaxGeschwindigkeit) : Fahrzeug(sName, dMaxGeschwindigkeit)
{
	std::cout << "Fahrrad erzeugt: "  << "  | Name: "
			  << p_sName << " | ID: " << p_iID
			  << " | Max Speed: " << p_dMaxGeschwindigkeit << "km/h"
			  << std::endl;
}

Fahrrad::~Fahrrad()
{
	std::cout << "Fahrrad gelöscht " << " | ID: " << p_iID << std::endl;
}
// override
void Fahrrad::vSimulieren()
{
	Fahrzeug::vSimulieren();
}

// override
void Fahrrad::vAusgeben()
{
	// Kein Tank und Verbrauch
	std::cout << std::resetiosflags(std::ios::adjustfield) << std::setiosflags(std::ios::left)
	   << std::setw(5)  << p_iID
	   << std::setw(15) << p_sName
	   // ab hier rechtsbündig
	   << std::resetiosflags(std::ios::adjustfield) << std::setiosflags(std::ios::right)
	   << std::fixed << std::setprecision(1)
	   << std::setw(25) << p_dMaxGeschwindigkeit
	   << std::setw(25) << dGeschwindigkeit()
	   << std::setw(25) << p_dGesamtStrecke
	   // Platzhalter
	   << std::setw(25) << "-"                    // Gesamtverbrauch
	   << std::setw(25) << "-"                    // Tankinhalt
	   << '\n'
	   << std::setfill('-') << std::setw(140) << "-" << '\n' << std::setfill(' ');
}

void Fahrrad::vAusgeben(std::ostream& o) const
{
	Fahrzeug::vAusgeben(o);
}

// Überschreibende Funktion für die Geschwindigkeit mit einer Geschwindigkeitsabnahme
double Fahrrad::dGeschwindigkeit() const
{
	if(p_dMaxGeschwindigkeit <= 12.0)
	{
	double dGeschwindigkeit = p_dMaxGeschwindigkeit;
	return dGeschwindigkeit;
	}
	const int stufen = (int)(p_dGesamtStrecke / 20.0);
	double dGeschwindigkeit = p_dMaxGeschwindigkeit * pow(0.9, stufen); // 10 Prozent Geschwindigkeitsabnahme pro 20 kmh
	// Grenze von 12 kmh setzen
	if (dGeschwindigkeit < 12.0) dGeschwindigkeit = 12.0;
	return dGeschwindigkeit;
}

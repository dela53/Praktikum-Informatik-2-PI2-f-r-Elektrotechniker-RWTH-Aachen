#include "Simulationsobjekt.h"

#include <string>
#include <iomanip>
#include <iostream>

int Simulationsobjekt::p_iMaxID = 0; // statische Variable

Simulationsobjekt::Simulationsobjekt() : p_iID(++p_iMaxID) // Initialisierungsliste. Initialisieren bevor erzeugen. Danach darf nicht mehr geändert werden.
{
	//std::cout << "\nSimulationsobjekt erzeugt: " << "  | Name: " << p_sName << " | ID: " << p_iID << "\n" << std::endl;
}

Simulationsobjekt::Simulationsobjekt(const std::string p_sNameInput) : p_sName(p_sNameInput), p_iID(++p_iMaxID) // p_sNameInput ist der Parameter des Konstruktors
{
	//std::cout << "\nSimulationsobjekt erzeugt: " << "  | Name: " << p_sName << " | ID: " << p_iID << "\n" << std::endl;
}

Simulationsobjekt::~Simulationsobjekt()
{
	//std::cout << "\nSimulationsobjekt gelöscht: " << " | Name: " << p_sName << " | ID: " << p_iID << std::endl;
}

void Simulationsobjekt::vAusgeben()
{
	std::cout << std::resetiosflags(std::ios::adjustfield) << std::setiosflags(std::ios::left)
		   << std::setw(5)  << p_iID
		   << std::setw(15) << p_sName
		   // ab hier rechtsbündig
		   << std::resetiosflags(std::ios::adjustfield) << std::setiosflags(std::ios::right)
		   << std::fixed << std::setprecision(1)
		   << '\n'
		   << std::setfill('-') << std::setw(25) << "-" << '\n' << std::setfill(' ');
}


std::ostream& Simulationsobjekt::vAusgeben(std::ostream& o) const
{
	o << std::resetiosflags(std::ios::adjustfield) << std::setiosflags(std::ios::left)
	   << std::setw(5)  << p_iID
	   << std::setw(15) << p_sName
	   // ab hier rechtsbündig
	   << std::resetiosflags(std::ios::adjustfield) << std::setiosflags(std::ios::right)
	   << std::fixed << std::setprecision(1)
	   << '\n'
	   << std::setfill('-') << std::setw(25) << "-" << '\n' << std::setfill(' ');
	return o;
}

void Simulationsobjekt::vKopf()
{
	std::cout << std::resetiosflags(std::ios::adjustfield)   // alles zurücksetzen
	   << std::setiosflags(std::ios::left)            // Überschriften links
	   << std::setw(5)  << "| ID"
	   << std::setw(15) << "| Name"
	   << std::endl
	   << std::setfill('-')
	   << std::setw(25) << "-" << std::endl << std::setfill(' ');
}

// Überladung des == Operators z.B. if(s1 == s2)
bool Simulationsobjekt::operator==(const Simulationsobjekt& simulationsObjekt) const
	{
	return p_iID == simulationsObjekt.p_iID;
	}

void Simulationsobjekt::vEinlesen(std::istream& c)
{
	// Überprüft ob Name leer ist
	if (c)
	{
		std::string sName;
		c >> sName;
		p_sName = sName;
	}
	// wirft einen Fehler wenn Name schon gesetzt ist
	else throw std::runtime_error("Simulationsobjekt::vEinlesen: Name wurde schon gesetzt.");
}

std::ostream& operator<<(std::ostream &o, const Simulationsobjekt &s)
{
	s.vAusgeben(o);
	return o;
}

// Überladener Eingabeoperator
std::istream& operator>>(std::istream& c, Simulationsobjekt& simulationsObjekt)
{
	simulationsObjekt.vEinlesen(c);
	return c;
}

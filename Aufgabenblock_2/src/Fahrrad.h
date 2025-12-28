#ifndef FAHRRAD_H_
#define FAHRRAD_H_
#include "Fahrzeug.h"

class Fahrrad : public Fahrzeug
{
public:
	Fahrrad();

	// Konstruktor mit dem Namen und der maximalen Geschwindigkeit
	Fahrrad(std::string sName, double dMaxGeschwindigkeit);

	virtual ~Fahrrad();

	// Überschriebene Funktionen spezifisch für Fahrräder //
	// Geschwindigkeit sinkt mit der Zeit, da Fahrer ermüdet
	double dGeschwindigkeit() const override;

	// Überschriebene Simulations-Funktion für PKW
	void vSimulieren() override;

	void vZeichnen(const Weg&) const override;

	// Überschriebene Ausgabe-Funktion für PKW's
	void vAusgeben() override;

	// Überladene Ausgabe-Funktion für PKW's
	void vAusgeben(std::ostream& o) const override;
};

#endif /* FAHRRAD_H_ */

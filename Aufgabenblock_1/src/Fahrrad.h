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
	// Funktion für die aktuelle Geschwindigkeit
	double dGeschwindigkeit() const override;
	// ÜberschrieSimulations-Funktion für PKW
	void vSimulieren() override;
	// Überschriebene Ausgabe-Funktion für PKW's
	void vAusgeben() override;
	// Überladene Ausgabe-Funktion für PKW's
	void vAusgeben(std::ostream& o) const override;
};

#endif /* FAHRRAD_H_ */

#ifndef FAHRRAD_H_
#define FAHRRAD_H_

#include "Fahrzeug.h"
#include "Weg.h"

class Fahrrad : public Fahrzeug
{
public:
	Fahrrad();

	// Konstruktor mit dem Namen und der maximalen Geschwindigkeit
	Fahrrad(std::string, double);

	virtual ~Fahrrad();

	// Überschriebene Funktionen spezifisch für Fahrräder //
	// Funktion für die aktuelle Geschwindigkeit
	virtual double dGeschwindigkeit() const override;

	// ÜberschrieSimulations-Funktion für PKW
	virtual void vSimulieren() override;

	virtual void vZeichnen(const Weg&) const override;

	// Überschriebene Ausgabe-Funktion für PKW's
	virtual void vAusgeben() override;

	// Überladene Ausgabe-Funktion für PKW's
	virtual void vAusgeben(std::ostream&) const override;

	virtual void vEinlesen(std::istream&) override;
};

#endif /* FAHRRAD_H_ */

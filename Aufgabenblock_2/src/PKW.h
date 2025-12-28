#ifndef PKW_H_
#define PKW_H_

#include "Fahrzeug.h"
#include "Weg.h"
#include "Verhalten.h"

#include <ostream>
#include <string>
#include <limits>

class PKW : public Fahrzeug
{
public:
	// Default-Konstruktor
	PKW();

	// An Klasse Fahrzeug anpassen //
	// Konstruktor mit Namen
	PKW(std::string sName);

	// Konstruktor mit Namen und der maximalen Geschwindigkeit
	PKW(std::string sName, double dMaxGeschwindigkeit);

	// Konstruktor mit Namen, Max-Geschwindigkeit, Verbrauch und Tankvolumen (Standard 53 liter)
	PKW(std::string sName, double dMaxGeschwindigkeit, double dVerbrauch, double dTankvolumen = 53.0);

	// Destruktor
	virtual ~PKW();

	// Überladene Operatoren
	PKW& operator=(const PKW& pkw);

	// Überschriebene Funktionen spezifisch für PKW's //
	// Funktion um vollzutanken wenn kein Wert übergeben wurde. dMenge = inf
	double dTanken(double dMenge = std::numeric_limits<double>::infinity()) override;

	// ÜberschrieSimulations-Funktion für PKW
	void vSimulieren() override;

	// Überschriebene Ausgabe-Funktion für PKW's
	void vAusgeben() override;

	// Überladene Ausgabe-Funktion für PKW's
	void vAusgeben(std::ostream& o) const override;

	// Funktion für die aktuelle Geschwindigkeit
	double dGeschwindigkeit() const override;

	// Überschriebene Funktion die ein PKW einzeichnet
	virtual void vZeichnen(const Weg&) const override;

protected:

private:
	// Spezifische Eigenschaften eines PKW's
	double p_dVerbrauch = 8.0;
	double p_dTankvolumen = 53.0;
	double p_dTankinhalt = p_dTankvolumen/2;

};

#endif /* PKW_H_ */

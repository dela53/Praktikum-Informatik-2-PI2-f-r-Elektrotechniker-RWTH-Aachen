#ifndef KREUZUNG_H_
#define KREUZUNG_H_

#include <memory>
#include <list>
#include <random>
#include <iostream>

#include "Simulationsobjekt.h"
#include "Tempolimit.h"
#include "Weg.h"
#include "Fahrzeug.h"

class Kreuzung : public Simulationsobjekt
{
public:
	Kreuzung();
	Kreuzung(std::string, double dTankstelle = 0);
	virtual ~Kreuzung();

	// getter-Funktion für Tankstellenkapazität
	const double getTankstelle() const {return p_dTankstelle;}

	// setter-Funktion für Tankstellenkapazität
	void setTankstelle(double);

	// Tanken eines Fahrzeugs an einer Kreuzung
	void vTanken(Fahrzeug&);

	// Simulation des Simulationsobjekts Kreuzung
	virtual void vSimulieren() override;

	virtual void vAusgeben() override;
	std::ostream& vAusgeben(std::ostream&) const;

	// Verbindet zwei Straßen miteinander bzw. erstellt eine Kreuzung. Parameter der Wege werden einander bekannt gemacht
	static void vVerbinde(const std::string, const std::string, const double, const std::shared_ptr<Kreuzung>,
	                      const std::shared_ptr<Kreuzung>, const Tempolimit, const bool bUeberholverbot = true);

	void vAnnahme(std::unique_ptr<Fahrzeug>, double); // ---> parkend

	std::shared_ptr<Weg> pZufaelligerWeg(Weg&);

	virtual void vEinlesen(std::istream&) override;

private:
	// Liste für die Wege der Kreuzung
	std::list<std::shared_ptr<Weg>> p_pWege;
	// Tankstellenkapazität
	double p_dTankstelle = 0.0;
};

std::ostream& operator<<(std::ostream&, Kreuzung&);

#endif /* KREUZUNG_H_ */

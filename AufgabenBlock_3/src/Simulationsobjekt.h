#ifndef SIMULATIONSOBJEKT_H_
#define SIMULATIONSOBJEKT_H_

#include <string>
#include <iostream>
#include <iomanip>

/*
 * Die (abstrakte) Oberklasse aller Objekte die simuliert werden.
 * Sie fasst alle wichtigen Methoden für alle Simulationsobjekte zusammen.
 * Unterklassen: Fahrzeuge, Weg
 */
class Simulationsobjekt
{
public:
	Simulationsobjekt();

	Simulationsobjekt(const std::string);

	virtual ~Simulationsobjekt();

	// Simulationsmethode, rein virtuelle Methode --> kann nicht aufgerufen werden
	virtual void vSimulieren() = 0;

	// Ausgaben //
	virtual void vAusgeben();
	std::ostream& vAusgeben(std::ostream&) const;

	static void vKopf();

	virtual void vEinlesen(std::istream&);

	// Getter-Funktionen //
	std::string getName() const {return p_sName;}
	int getID() const {return p_iID;}

	// Verbieten des Copy-Konstruktors
	// Verhindert das kopieren eines Fahrzeugs,
	// da hier in der Aufgabe jedes Auto eine einzelne ID besitzt.
	// Außerdem ist p_ID konstant. Würde ein fehler ausspucken wenn man kopiert
	Simulationsobjekt(const Simulationsobjekt&) = delete;

	// Überladener Operator
	bool operator==(const Simulationsobjekt&) const;

protected:
	// Name des Fahrzeugs
	std::string p_sName = ""; // zeigt, das es leer ist
	// ID des Fahrzeugs
	const int p_iID;
	// Zeit bis zur letzten Simulation
	double p_dZeit = 0.0;
private:
	// Inkrementierer für ID
	static int p_iMaxID;
};

// Überladene Operatoren
std::ostream& operator<<(std::ostream&, const Simulationsobjekt&);
std::istream& operator>>(std::istream&, Simulationsobjekt&);

#endif /* SIMULATIONSOBJEKT_H_ */

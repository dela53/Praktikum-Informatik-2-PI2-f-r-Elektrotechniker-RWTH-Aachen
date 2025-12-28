#ifndef FAHRZEUG_H_
#define FAHRZEUG_H_

#include "Simulationsobjekt.h"
#include "Weg.h"
#include "Verhalten.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <ostream>
#include <limits>
#include <memory>

extern double dGlobaleZeit; // externe Variable um globale Variable anderen Dateien bekannt zu machen

class Verhalten;

/*
 * Unterklasse von Simulationsobjekt.
 * Diese Klasse kann Fahrzeuge erzeugen, simulieren und und ihre spezifischen Werte ausgeben.
 * Unterklassen: PKW, Fahrrad
 */
class Fahrzeug : public Simulationsobjekt
{
public:
///////////////////////////////////////////// Konstruktoren //////////////////////////////////////////////////////////
	// Standardkonstruktor
	Fahrzeug();
	// Konstruktor mit Namen
	Fahrzeug(const std::string& p_sNameInput);
	// Konstruktor mit Namen und maximalen Geschwindigkeit
	Fahrzeug(const std::string& p_sNameInput, double maxSpeed);
	// Destruktor
	virtual ~Fahrzeug();
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Memberfunktion für Simulationen
	virtual void vSimulieren();

////////////////////////////////// Ausgaben //////////////////////////////////////////////////////////
	// Alles ausgeben
	virtual void vAusgeben();
	// Überladene Ausgabefunktion
	virtual void vAusgeben(std::ostream&) const;
	// Kopf der Tabelle für vAusgeben() // statisch da es immer für jeden gleich ist
	static void vKopf();
///////////////////////////////////////////////////////////////////////////////////////////////////////

	// Funktion um vollzutanken wenn kein Wert übergeben wurde. dMenge = inf
	virtual double dTanken(double dMenge = std::numeric_limits<double>::infinity());

	// Basis-Funktion für aktuelle Geschwindigkeit
	virtual double dGeschwindigkeit() const;

	// Fahrendes Fahrzeug wird auf dem Weg gesetzt
	void vNeueStrecke(Weg&);

	// Parkendes Fahrzeug bis zu Startzeit wird auf dem Weg gesetzt
	void vNeueStrecke(Weg&, double);

	// Rein virtuelle
	virtual void vZeichnen(const Weg&) const {};

	// Überladung des (<) und (=) Operator
    bool operator<(const Fahrzeug& fahrzeug) const;
    Fahrzeug& operator=(const Fahrzeug& fahrzeug);

////////////////////////////////////// Getter-Funktionen ////////////////////////////////////////////
	std::string getName() const {return p_sName;}
	int getID() const {return p_iID;}
	double getAbschnittStrecke(){return p_dAbschnittStrecke;}
	double getGesamtStrecke() {return p_dGesamtStrecke;}
/////////////////////////////////////////////////////////////////////////////////////////////////////

	// Verbieten des Copy-Konstruktors
	// Verhindert das kopieren eines Fahrzeugs,
	// da hier in der Aufgabe jedes Auto eine einzelne ID besitzt.
	// Außerdem ist p_ID konstant. Würde ein Fehler ausspucken, wenn man kopiert
	Fahrzeug(const Fahrzeug&) = delete;

protected:
	// Name des Fahrzeugs
	std::string p_sName = ""; // zeigt, das es leer ist
	// ID des Fahrzeugs
	const int p_iID;
	// Maximale Geschwindigkeit
	double p_dMaxGeschwindigkeit = 0.0; // Es wird sichergestellt dass Anfangswert 0 ist
	// Insgesamt zurückgelegte Strecke
	double p_dGesamtStrecke = 0.0;
	// Gesamte Fahrzeit
	double p_dGesamtZeit = 0.0;
	// Zeit bis zur letzten Simulation
	double p_dZeit = 0.0;
	// Verhalten unique-Zeiger in den der Weg gespeichert wird und auf dem Verhalten des Fahrzeug (fahrend oder parkend) zeigt.
	std::unique_ptr<Verhalten> p_pVerhalten; // Speicher wird automatisch gelöscht.
	// Bisher zurückgelegte Strecke auf dem Abschnitt
	double p_dAbschnittStrecke = 0.0;

private:
	// Inkrementierer für ID
	static int p_iMaxID; // sorgt dafür dass jedem Fahrzeug eine andere ID zugewiesen wird // static damit Objekte keine Kopien bekommen, sonst kommt es zu Dopplungen. Mit static: Alle Objekte greifen auf den selben Speicher
};

// Überladung außerhalb der Klasse
std::ostream& operator<<(std::ostream&, const Fahrzeug&);

#endif /* FAHRZEUG_H_ */

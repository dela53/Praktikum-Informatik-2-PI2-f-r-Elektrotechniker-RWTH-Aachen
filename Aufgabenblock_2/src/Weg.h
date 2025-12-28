#ifndef WEG_H_
#define WEG_H_

#include "Simulationsobjekt.h"
#include "Tempolimit.h"
#include "Fahrzeug.h"
#include "vertagt_aktion.h"
#include "vertagt_liste.h"

#include <limits>
#include <iostream>
#include <list>

class Fahrzeug;

/*
 * Unterklasse von Simulationsobjekt:
 * Erstellt einen Weg indem alle erzeugten Fahrzeuge auf dem Weg simuliert werden kann.
 * Speichert alle auf dem Weg simulierten Fahrzeuge  in einer Liste speziell für dieses Objekt
 * Unterklassen: keine
 */
class Weg : public Simulationsobjekt
{
public:
	// Standard Konstruktor
	Weg();

	// Konstruktor mit Namen, Weglänge und Tempolimit (default = inf)
	Weg(std::string sName, double dLaenge, Tempolimit eTempolimit = AUTOBAHN);

	// Destruktor
	virtual ~Weg();
	// Ausgabefunktion
	virtual void vAusgeben() override;

	// Überladene Ausgabefunktion
	std::ostream& vAusgeben(std::ostream& o) const;

	// Kopf der Tabelle für vAusgeben() // statisch da es immer für jeden gleich ist
	static void vKopf();

	// Simulationsmethode
	virtual void vSimulieren() override;

	// getter-Funktionen //
	double getTempolimit();
	const double getLaenge() const;
	const vertagt::VListe<std::unique_ptr<Fahrzeug>>& getFahrzeuge() const;

	// nimmt parkende oder fahrende Fahrzeuge auf dem Weg an
	void vAnnahme(std::unique_ptr<Fahrzeug> fzg); // ---> fahrend
	// überladen
	void vAnnahme(std::unique_ptr<Fahrzeug>, double); // ---> parkend

	 // Funktion für Abgabe eines Fahrzeugs wegen Verhaltensänderung
	std::unique_ptr<Fahrzeug> pAbgabe(const Fahrzeug&);

protected:
	// Liste für Fahrzeuge die auf dem Weg gesetzt werden
    vertagt::VListe<std::unique_ptr<Fahrzeug>> p_pFahrzeuge;

private:
	double p_dLaenge = 0.0;
	Tempolimit p_eTempolimit;
};

// Überladung des (<<) Operators außerhalb der Klasse
std::ostream& operator<<(std::ostream&, Weg&);

#endif /* WEG_H_ */

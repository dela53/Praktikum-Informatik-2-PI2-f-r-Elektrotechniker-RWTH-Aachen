#ifndef WEG_H_
#define WEG_H_

#include "Simulationsobjekt.h"
#include "Tempolimit.h"
#include "vertagt_aktion.h"
#include "vertagt_liste.h"

#include <iostream>
#include <iomanip>

class Fahrzeug;
class Kreuzung;
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
	Weg(std::string, double, Tempolimit eTempolimit = AUTOBAHN, bool bUeberholverbot = true, std::shared_ptr<Kreuzung> pZielkreuzung = nullptr);

	// Destruktor
	virtual ~Weg();
	// Ausgabefunktion
	virtual void vAusgeben() override;

	// Überladene Ausgabefunktion
	std::ostream& vAusgeben(std::ostream&) const;

	// Kopf der Tabelle für vAusgeben() // statisch da es immer für jeden gleich ist
	static void vKopf();

	// Simulationsmethode
	virtual void vSimulieren() override;

	// getter/setter-Funktionen //
	double getTempolimit();
	const double getLaenge() const;
	const double getVirtuelleSchranke() const;
	void setVirtuelleSchranke(double);
	const vertagt::VListe<std::unique_ptr<Fahrzeug>>& getFahrzeuge() const;
	const std::shared_ptr<Kreuzung> getZielkreuzung() const;
	const std::shared_ptr<Weg> getRueckweg() const;
	void setRueckweg(std::shared_ptr<Weg>);

	// nimmt parkende oder fahrende Fahrzeuge auf dem Weg an
	void vAnnahme(std::unique_ptr<Fahrzeug>); // ---> fahrend
	// überladen
	void vAnnahme(std::unique_ptr<Fahrzeug>, double); // ---> parkend

	// Funktion für Abgabe eines Fahrzeugs wegen Verhaltensänderung
	std::unique_ptr<Fahrzeug> pAbgabe(const Fahrzeug&);

	virtual void vEinlesen(std::istream&) override;

protected:
	// Liste für Fahrzeuge die auf dem Weg gesetzt werden
    vertagt::VListe<std::unique_ptr<Fahrzeug>> p_pFahrzeuge;
    //
	const std::weak_ptr<Kreuzung> p_pZielkreuzung;
	// Zeigt auf dem Rückweg. Kein const, da gesettet
	std::weak_ptr<Weg> p_pRueckweg;
private:
    // Länge der Straße
	double p_dLaenge = 0.0;
	// Variable die ein Überholverbot angibt. Standard Überholverbot
	bool p_bUeberholverbot = true;
	// Falls ein Fahrzeug stehen bleibt, darf das hintere Auto nicht über die Schranke hinaus
	double p_dVirtuelleSchranke = 0.0;
	// Tempolimit des Weges
	Tempolimit p_eTempolimit;
};

// Überladung des (<<) Operators außerhalb der Klasse
std::ostream& operator<<(std::ostream&, Weg&);

#endif /* WEG_H_ */

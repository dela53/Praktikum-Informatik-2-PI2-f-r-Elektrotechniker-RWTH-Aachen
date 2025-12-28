#ifndef VERHALTEN_H_
#define VERHALTEN_H_

class Weg;
class Fahrzeug;
/*
 * Eine (abstrakte) Klasse welche das Verhalten eines Fahrzeugs auf dem Weg beschreibt.
 * Dabei gibt es zwei Zustände: Fahrend und parkend
 * Unterklassen: Fahren, Parken
 */
class Verhalten
{
public:
	// Standard Konstruktor
	Verhalten();

	// Konsruktor Verhalten mit Instanz auf Weg
	Verhalten(Weg& weg);

	// Destruktor
	virtual ~Verhalten();

	// Ermittelt, wie weit ein Fahrzeug in der ermittelten Zeit fahren kann,
	// ohne das Wegende zu überschreiten (rein Virtuell). Wird ein mal pro Takt aufgerufen
	virtual double dStrecke(Fahrzeug& aFzg, double dZeitIntervall) = 0;

	// getter-Funktionen //
	// gibt den Weg zurück.
	Weg* getWeg(){return p_pWeg;}

protected:
	Weg* p_pWeg;
};

#endif /* VERHALTEN_H_ */

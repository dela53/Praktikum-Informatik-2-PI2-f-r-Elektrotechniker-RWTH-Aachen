#ifndef FAHRAUSNAHME_H_
#define FAHRAUSNAHME_H_

#include "Fahrzeug.h"
#include "Weg.h"
#include "Parken.h"
#include "Fahren.h"

#include <exception>

/*
 * Eine (abstrakte) Unterklasse von der Klasse exception um Ausnahmen zu werfen.
 * Sie beschreibt die Ausnahmen der Fahrzeug in einem Weg wie,
 *  wenn das Fahrzeug am Ende des Wegs angekommen ist oder wenn die Startzeit des parkenden Autos erreicht wurde.
 *  Unterklassen: Losfahren, Streckenende
 */
class Fahrausnahme : public std::exception
{
public:
	// Speichert Fahrzeug und Weg bei der die Ausnahme eingetreten ist
	Fahrausnahme(Fahrzeug&, Weg&);

	// Das Verhalten des Autos ändert sich oder das Auto wird ggf. aus dem Weg gelöscht
	virtual void vBearbeiten() = 0;

	virtual ~Fahrausnahme();

protected:
	Fahrzeug& p_pFahrzeug;
	Weg& p_pWeg;
};

#endif /* FAHRAUSNAHME_H_ */

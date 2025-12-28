#ifndef LOSFAHREN_H_
#define LOSFAHREN_H_

#include "Fahrausnahme.h"
#include "Fahrzeug.h"
#include "Weg.h"
#include "Parken.h"
#include "Fahren.h"

class Losfahren : public Fahrausnahme
{
public:
	//Losfahren();

	// Speichert Fahrzeug und Weg bei der die Ausnahme eingetreten ist
	Losfahren(Fahrzeug&, Weg&);

	virtual ~Losfahren();

	virtual void vBearbeiten() override;

};

#endif /* LOSFAHREN_H_ */

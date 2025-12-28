#ifndef STRECKENENDE_H_
#define STRECKENENDE_H_

#include "Fahrausnahme.h"
#include "Fahrzeug.h"
#include "Weg.h"
#include "Kreuzung.h"

class Streckenende : public Fahrausnahme
{
public:
	Streckenende(Fahrzeug&, Weg&);
	virtual ~Streckenende();

	virtual void vBearbeiten() override;
};

#endif /* STRECKENENDE_H_ */

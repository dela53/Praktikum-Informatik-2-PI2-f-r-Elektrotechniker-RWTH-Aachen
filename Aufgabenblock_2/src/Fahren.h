#ifndef FAHREN_H_
#define FAHREN_H_

#include "Fahrzeug.h"
#include "Verhalten.h"

class Weg;
class Fahrzeug;

class Fahren : public Verhalten
{
public:
	Fahren();

	// Konstruktor mit Instanz auf Weg
	Fahren(Weg& weg);

	virtual ~Fahren();

	// Ermittelt, wie weit ein Fahrzeug in der Ermittelten Zeit fahren kann,
	// ohne das Wegende zu überschreiten (überschrieben)
	virtual double dStrecke(Fahrzeug& aFzg, double dZeitIntervall) override;
protected:
	bool p_bErreicht = false;

};

#endif /* FAHREN_H_ */

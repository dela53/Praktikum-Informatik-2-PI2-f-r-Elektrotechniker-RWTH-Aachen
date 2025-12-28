#ifndef PARKEN_H_
#define PARKEN_H_

#include "Fahrzeug.h"
#include "Verhalten.h"

class Weg;
class Fahrzeug;

class Parken : public Verhalten
{
public:
	Parken();
	Parken(Weg& weg);
	Parken(Weg& weg, double dStartzeitpunkt);
    virtual ~Parken();

	// Ermittelt, wie weit ein Fahrzeug in der Ermittelten Zeit fahren kann,
	// ohne das Wegende zu überschreiten (überschrieben)
	virtual double dStrecke(Fahrzeug& aFzg, double dZeitIntervall) override;



protected:
	double p_dStartzeitpunkt = 0.0;
	// speichert ob Meldung ausgegeben wurde, dass Startzeitpunkt schon erreicht wurde
	bool p_bErreicht = false;
};

#endif /* PARKEN_H_ */

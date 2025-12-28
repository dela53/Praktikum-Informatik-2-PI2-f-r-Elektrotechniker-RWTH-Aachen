#ifndef SIMULATION_H_
#define SIMULATION_H_

#include <iostream>
#include <memory>
#include <list>
#include <fstream>
#include <map>
#include <string>

class Kreuzung;

class Simulation
{
public:
	Simulation();
	virtual ~Simulation();

	void vEinlesen(std::istream&, bool bMitGrafik = false);
	void vSimulieren(double, double);

private:
	int p_iZeilenNummer = 0;
	std::map<std::string, std::shared_ptr<Kreuzung>> p_pMapKreuzungen;
};

// Überladener Eingabeoperator
std::istream& operator>>(std::istream&, Simulation&);

#endif /* SIMULATION_H_ */

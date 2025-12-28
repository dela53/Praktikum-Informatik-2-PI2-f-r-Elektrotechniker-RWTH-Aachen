#include "Kreuzung.h"

Kreuzung::Kreuzung()
{
	std::cout << "\nKreuzung erzeugt " << " | ID: " << p_iID << "\n" << std::endl;
}

Kreuzung::Kreuzung(std::string sName, double dTankstelle) : Simulationsobjekt(sName), p_dTankstelle(dTankstelle)
{
	std::cout << "\nKreuzung erzeugt: " << " | Name: " << p_sName << " | ID: " << p_iID << "\n" << std::endl;
}
Kreuzung::~Kreuzung()
{
	std::cout << "\nKreuzung gelöscht: " << " | Name: " << p_sName << " | ID: " << p_iID << std::endl;
}

void Kreuzung::setTankstelle(double dTanke)
{
	p_dTankstelle -= dTanke;
	if (p_dTankstelle < 0) p_dTankstelle = 0.0;
}

// Tankt solange Gas verfügbar ist
void Kreuzung::vTanken(Fahrzeug& fzg)
{
	if(p_dTankstelle > 0) setTankstelle(fzg.dTanken());
}

void Kreuzung::vVerbinde(const std::string sNameHinweg, const std::string sNameRueckweg, const double dWegLaenge,
		const std::shared_ptr<Kreuzung> wegKreuzung1, const std::shared_ptr<Kreuzung> wegKreuzung2, const Tempolimit eTempolimit, const bool bUeberholverbot)
{
	// Erstellen der Wege als shared_ptr
	auto weg1 =  std::make_shared<Weg>(sNameHinweg, dWegLaenge, eTempolimit, bUeberholverbot, wegKreuzung2);
	auto weg2 =  std::make_shared<Weg>(sNameRueckweg, dWegLaenge, eTempolimit, bUeberholverbot, wegKreuzung1);

	// Bekanntmachen der Wege
	weg1->setRueckweg(weg2);
	weg2->setRueckweg(weg1);

	// Die neu erzeugten Wege werden den jeweiligen Kreuzungen zugeordnet
	// weg1 wird in die Wegliste von wegKreuzung1 eingetragen. Weg2 analog
	wegKreuzung1->p_pWege.push_back(weg1);
	wegKreuzung2->p_pWege.push_back(weg2);
}

void Kreuzung::vAnnahme(std::unique_ptr<Fahrzeug> fzg, double dStartzeitpunkt)
{
	if(fzg == nullptr || p_pWege.empty())
	{
		std::cerr << "Fehler: Fahrzeug oder Weg existiert nicht!" << std::endl;
		return;
	}
	// Tankt das Fahrzeug voll
	vTanken(*fzg);
	// Fahrzeug wird im Ersten Weg der Liste parkend angenommen
	p_pWege.front()->vAnnahme(std::move(fzg), dStartzeitpunkt);
}

void Kreuzung::vSimulieren()
{
	for (auto it = p_pWege.begin(); it != p_pWege.end(); it++)
	{
		(*it)->vSimulieren();
	}
}

void Kreuzung::vAusgeben()
{
	std::cout << std::resetiosflags(std::ios::adjustfield) << std::setiosflags(std::ios::left)
			  << std::setw(5)  << p_iID
			  << std::setw(15) << p_sName << " | Tankstellenfüllung: " <<  p_dTankstelle
			  // ab hier rechtsbündig
			  << std::resetiosflags(std::ios::adjustfield) << std::setiosflags(std::ios::right)
			  << std::fixed << std::setprecision(1)
			  << '\n'
			  << std::setfill('-') << std::setw(25) << "-" << '\n' << std::setfill(' ');
	}

std::ostream& Kreuzung::vAusgeben(std::ostream& o) const
{
	o << std::resetiosflags(std::ios::adjustfield) << std::setiosflags(std::ios::left)
	   << std::setw(5)  << p_iID
	   << std::setw(15) << p_sName << " | Tankstellenfüllung: " <<  p_dTankstelle
	   // ab hier rechtsbündig
	   << std::resetiosflags(std::ios::adjustfield) << std::setiosflags(std::ios::right)
	   << std::fixed << std::setprecision(1)
	   << '\n'
	   << std::setfill('-') << std::setw(25) << "-" << '\n' << std::setfill(' ');
	return o;
}

std::shared_ptr<Weg> Kreuzung::pZufaelligerWeg(Weg& weg)
{
	// Es gibt nur ein Weg in der Liste bzw. Sackgasse
	if (p_pWege.size() == 1) return p_pWege.front();

	auto rueckweg = weg.getRueckweg();
	if (rueckweg == nullptr)
	{
		std::cerr << "pZufaelligerWeg: Rückweg lieferte ein nullptr!\n" << std::endl;
		return p_pWege.front();
	}

	// Damit man mit Indiez zugreifen kann
	std::vector<std::shared_ptr<Weg>> vectorWeg;

	for (auto it = p_pWege.begin(); it != p_pWege.end(); it++)
	{
		// Überprüfen ob der Rückweg ausgeschlossen werden muss mit Vergleich der Identität
		if (rueckweg && (*it)->getName() == rueckweg->getName()) continue;
		vectorWeg.push_back(*it);
	}
	// Falls keine Kandidaten zurückgeben
	if (vectorWeg.empty()) return rueckweg;

	static std::mt19937 device(1234);
	std::uniform_int_distribution<int> dist(0, vectorWeg.size()-1);
	int zuf = dist(device);

	std::cout << "pZufaelligerWeg: Zufälliger Weg wurde gewählt" << std::endl;
	return vectorWeg[zuf];
}

void Kreuzung::vEinlesen(std::istream& c)
{
	std::string sName;
	double dTankstelle;

	c >> sName;
	p_sName = sName;

	c >> dTankstelle;
	p_dTankstelle = dTankstelle;

	// wirft einen Fehler wenn Name schon gesetzt ist
	if (!c) throw std::runtime_error("Kreuzung::vEinlesen: Name wurde schon gesetzt.");
}

// Überladung des << Operators
std::ostream& operator<<(std::ostream& o, Kreuzung& kr)
{
	kr.vAusgeben(o);
	return o;
}

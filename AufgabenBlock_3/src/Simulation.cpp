#include "Simulation.h"
#include "PKW.h"
#include "Fahrrad.h"
#include "Kreuzung.h"
#include "SimuClient.h"

#include <memory>
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <iomanip>

extern double dGlobaleZeit;

Simulation::Simulation()
{
}

Simulation::~Simulation()
{
}

// Liest Dateien ein, um sie zu simulieren.
void Simulation::vEinlesen(std::istream& c, bool bMitGrafik)
{
	std::string schluesselwort;

	while (c >> schluesselwort)
	{
		// Zählt Zeilennummer für Ortung der Fehler
		++p_iZeilenNummer;

		try
		{
			if (schluesselwort == "KREUZUNG")
			{
				// Kreuzung erzeugen
				auto kreuzung = std::make_shared<Kreuzung>();

				try
				{
					kreuzung->vEinlesen(c);

					std::string sName = kreuzung->getName();
					// Überprüfen ob Kreuzung schon existiert
					if (p_pMapKreuzungen.find(sName) != p_pMapKreuzungen.end())
					{
						throw std::runtime_error("KREUZUNG | Zeile " + std::to_string(p_iZeilenNummer) + ": Fehler: Kreuzung " + sName + " wurde schon gesetzt. ");
					}

					// Kreuzung in der Map speichern
					p_pMapKreuzungen[sName] = kreuzung;

					if (bMitGrafik)
					{
						double dKoordinatenX, dKoordinatenY;
						c >> dKoordinatenX >> dKoordinatenY;
						if (!c) throw std::runtime_error("KREUZUNG: Fehler beim Einlesen der Koordinaten");
						// bZeichneKreuzung(X-Koordinaten, Y-Koordinaten)
						bZeichneKreuzung(dKoordinatenX, dKoordinatenY);
					}
				}
				// Falls vEinlesen was wirft, hier abfangen
				catch (const std::exception& ausnahme)
				{
				throw std::runtime_error("KREUZUNG | Zeile " + std::to_string(p_iZeilenNummer) + ": Fehler beim Einlesen der Kreuzung: " + std::string(ausnahme.what()));
				}
			}
			else if (schluesselwort == "STRASSE")
			{
				std::string sNameQ, sNameZ, sNameW1, sNameW2;
				double dLaenge = 0;
				int iTempolimit;
				bool bUeberholverbot;

				// Einlesen der Parameter
				c >> sNameQ >> sNameZ >> sNameW1 >> sNameW2 >> dLaenge >> iTempolimit >> bUeberholverbot;

				// Verschiedene Fehler überprüfen und werfen
				if (!c) // !c = c.fail() || c.bad() bzw. wenn das Einlesen fehlerhaft war
				{
					throw std::runtime_error("STRASSE | Zeile " + std::to_string(p_iZeilenNummer) + ": Fehler beim Einlesen der Strasse.");
				}
			    if (p_pMapKreuzungen.find(sNameQ) == p_pMapKreuzungen.end())
				{
					throw std::runtime_error("STRASSE | Zeile " + std::to_string(p_iZeilenNummer) + ": Fehler: " + sNameQ + " existiert nicht.");
				}
				if (p_pMapKreuzungen.find(sNameZ) == p_pMapKreuzungen.end())
				{
					throw std::runtime_error("STRASSE | Zeile " + std::to_string(p_iZeilenNummer) + ": Fehler: " + sNameZ + " existiert nicht.");
				}
				// Erzeugt die Kreuzungen und wirft eine Ausnahme falls sie nicht mit dem Namen gefunden wurde (.at())-wirft vom Typ out_of_range
				try
				{
				auto quellKreuzung = p_pMapKreuzungen.at(sNameQ);
				auto zielKreuzung = p_pMapKreuzungen.at(sNameZ);

				// Verbinden der Quellkreuzung (nameQ) mit der Zielkreuzung (nameZ) über weg1
				Kreuzung::vVerbinde(sNameW1, sNameW2, dLaenge, quellKreuzung, zielKreuzung, static_cast<Tempolimit>(iTempolimit), bUeberholverbot);

				if (bMitGrafik)
				{
					int iAnzahlKoordinaten;
					// Einlesen
					c >> iAnzahlKoordinaten; // Liest die Koordinatenpaare ein.
					if (!c) throw std::runtime_error("STRASSE: Fehler beim Einlesen der Koordinaten");

					std::vector<int> iKoordinaten(2*iAnzahlKoordinaten);

					for (int i = 0; i < 2*iAnzahlKoordinaten; i++)
					{
						c >> iKoordinaten[i];
						if (!c) throw std::runtime_error("STRASSE: Fehler beim Einlesen der Koordinaten");
					}
					// bZeichneStrasse(Name Startweg, Name Zielweg, Länge der Straße, Koordinatenpaare bzw Punkte, Koordinaten der verschiedenen Straßen)
					bZeichneStrasse(sNameW1, sNameW2, dLaenge, iAnzahlKoordinaten, iKoordinaten.data()); // iKoordinaten.data() gibt die Werte ohne Schleife zurück)
				}
				}
				catch (const std::out_of_range& ausnahme)
				{
				    throw std::runtime_error("STRASSE | Zeile " + std::to_string(p_iZeilenNummer) + ": Kreuzung existiert nicht: " + ausnahme.what());
				}
			}
			else if (schluesselwort == "PKW")
			{
				std::string sNameS;
				double dStartZeit;
				auto pkw = std::make_unique<PKW>();

				try
				{
					// Daten einlesen
					pkw->vEinlesen(c);
					c >> sNameS >> dStartZeit;

					// Falls das Einlesen fehlerhaft war
					if (!c) throw std::runtime_error("PKW | Zeile " + std::to_string(p_iZeilenNummer) + ": Fehler beim Einlesen der Startkreuzung oder Startzeit.");

					// Wirft automatisch eine Ausnahme
					auto startKreuzung = p_pMapKreuzungen.at(sNameS);
					// Fahrzeug auf der Kreuzung annehmen
					startKreuzung->vAnnahme(std::move(pkw), dStartZeit);

				}
				// Fängt die Fehlermeldung ab wenn startKreuzung nicht existiert
				catch (const std::out_of_range& ausnahme) // fängt .at()
				{
					throw std::runtime_error("PKW | Zeile " + std::to_string(p_iZeilenNummer) + ": Fehler: " + sNameS + " existiert nicht. " + ausnahme.what());
				}
				// Falls vEinlesen was wirft, hier abfangen
				catch (const std::exception& ausnahme)
				{
					throw std::runtime_error("PKW | Zeile " + std::to_string(p_iZeilenNummer) + ": Fehler beim Einlesen der PKW: " + ausnahme.what());
				}
			}
			else if (schluesselwort == "FAHRRAD")
			{
				// Parameter zum einlesen
				std::string sNameS;
				double dStartZeit;
				auto fahrrad = std::make_unique<Fahrrad>();

				try
				{
					// Einlesen
					fahrrad->vEinlesen(c);
					c >> sNameS >> dStartZeit;

					// Falls das Einlesen fehlerhaft war
					if (!c) throw std::runtime_error("FAHRRAD | Zeile " + std::to_string(p_iZeilenNummer) + ": Fehler beim Einlesen der Startkreuzung oder Startzeit.");
					// Wirft automatisch eine Ausnahme wegen at()
					auto startKreuzung = p_pMapKreuzungen.at(sNameS);
					// Fahrzeug auf der Kreuzung annehmen
					startKreuzung->vAnnahme(std::move(fahrrad), dStartZeit);
				}
				// Fängt die Fehlermeldung ab wenn startKreuzung nicht existiert
				catch (const std::out_of_range& ausnahme) // fängt .at()
				{
					throw std::runtime_error("PKW | Zeile " + std::to_string(p_iZeilenNummer) + ": Fehler: " + sNameS + " existiert nicht. " + ausnahme.what());
				}
				// Falls vEinlesen was wirft, hier abfangen
				catch (const std::exception& ausnahme)
				{
					throw std::runtime_error("FAHRRAD | Zeile " + std::to_string(p_iZeilenNummer) + ": Fehler beim Einlesen des Fahrrads: " + ausnahme.what());
				}
			}
		}
		catch (const std::exception& ausnahme)
		{
			std::cerr << "SIMULATION | Zeile " << p_iZeilenNummer << " Fehler(" << ausnahme.what() << ")" << std::endl;
		}
	}
}

// Simuliert alle Kreuzungen auf der Map
void Simulation::vSimulieren(double dDauer, double dZeitschritt)
{
	for (dGlobaleZeit = 0; dGlobaleZeit <= (dDauer * dZeitschritt); dGlobaleZeit += dZeitschritt)
	{
		for (auto it = p_pMapKreuzungen.begin(); it != p_pMapKreuzungen.end(); it++)
		{
			// wie vUhr() in main
			vSetzeZeit(dGlobaleZeit);
			std::cout << std::endl << std::endl << std::setw(22) << std::setfill('-') << "-" << std::setfill(' ') << std::endl;
			std::cout << "Globale-Zeit: " << dGlobaleZeit*60 << " min" << std::endl;
			std::cout << std::setw(22) << std::setfill('-') << "-" << std::setfill(' ') << std::endl << std::endl;

			// second gibt den Wert der Map aus
			it->second->vSimulieren();
		}
		vSleep(1);
	}
	vSleep(10000);
	vBeendeGrafik();
}

// Überladener Eingabeoperator
std::istream& operator>>(std::istream& c, Simulation& simulation)
{
	simulation.vEinlesen(c);
	return c;
}

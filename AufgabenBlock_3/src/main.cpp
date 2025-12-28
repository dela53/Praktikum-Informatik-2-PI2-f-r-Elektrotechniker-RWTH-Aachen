#include "Fahrzeug.h"
#include "Fahrrad.h"
#include "PKW.h"
#include "Simulationsobjekt.h"
#include "Weg.h"
#include "SimuClient.h"
#include "vertagt_aktion.h"
#include "vertagt_liste.h"
#include "Kreuzung.h"
#include "Simulation.h"

#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <iomanip>
#include <cmath>
#include <list>
#include <random>
#include <limits>
#include <istream>
#include <fstream>

using namespace std;

// Globale Variablen
double dGlobaleZeit = 0.0;

// einlesende Variablen
string sName;
double dMaxGeschwindigkeit, dVerbrauch, dTankvolumen;

// Zeit
double dZeittakt = 0.1;
int iStunden = 4;

// Funktionen initialisieren, da unter main implementiert
void vAufgabe_1();
void vAufgabe_1a();
void vAufgabe_2();
void vAufgabe_3();
void vAufgabe_4();
void vAufgabe_5();
void vAufgabe_6();
void vAufgabe_6a();
void vAufgabe_7();
void vAufgabe_8();
void vAufgabe_9();
void vAufgabe_9a();
void vUhr();
void vTanke(Weg& weg, double dTankZeit);
void vFahrzeugAusgabe(const Weg& weg);
//void vAufgabe_AB1();

/////////////////////
////Hauptfunktion////
/////////////////////
int main()
{
	int i = 0;

	cout << "Welche Aufgabe moechten Sie starten?" << endl;
	cout << "1 - Aufgabe 1" << endl;
	cout << "2 - Aufgabe 2" << endl;
	cout << "3 - Aufgabe 3" << endl;
	cout << "4 - Aufgabe 4" << endl;
	cout << "5 - Aufgabe 5" << endl;
	cout << "6 - Aufgabe 6" << endl;
	cout << "61 - Aufgabe 6a" << endl;
	cout << "7 - Aufgabe 7" << endl;
	cout << "8 - Aufgabe 8" << endl;
	cout << "9 - Aufgabe 9" << endl;
	cout << "91 - Aufgabe 9a" << endl;
	cout << "Ihre Wahl: ";
	cin >> i;

	switch(i)
	{
		case 1:
			vAufgabe_1();
			break;
		case 2:
			vAufgabe_2();
			break;
		case 3:
			vAufgabe_3();
			break;
		case 4:
			vAufgabe_4();
			break;
		case 5:
			vAufgabe_5();
			break;
		case 6:
			vAufgabe_6();
			break;
		case 61:
			vAufgabe_6a();
			break;
		case 7:
			vAufgabe_7();
			break;
		case 8:
			vAufgabe_8();
			break;
		case 9:
			vAufgabe_9();
			break;
		case 91:
			vAufgabe_9a();
			break;
		default:
			cerr << "Ungültige Auswahl!" << endl;
			break;
	}
return 0;
}


//////////////////
////Aufgabe 1/////
//////////////////
void vAufgabe_1()
{
//statische Objekte. Werden automatisch gelöscht
Fahrzeug auto1("VW Sharan");
Fahrzeug auto2("Mini Cooper");

cout << "\n";

// Dynamisch erzeugte Fahrzeuge
auto auto3 = new Fahrzeug("Mercedes Benz ML 300");
auto auto4 = new Fahrzeug("Mercedes Benz C 500");

cout << "\n";

// Manuelle Destruktoren
delete auto3;
delete auto4;

cout << "\n";

// Dynamisch mit smart-Pointer. Werden automatisch gelöscht. -----> keine Speicherlecks
auto auto5 = make_unique<Fahrzeug>("Mercedes Benz GLC 500", 220); // kann nicht kopiert werden
auto auto6 = make_unique<Fahrzeug>("Mercedes Benz GLC 300", 225);
auto auto7 = make_shared<Fahrzeug>("Mercedes Benz S 550 Coupe", 315); // mehrere Pointer können auf diesem Objekt zeigen // use_count() = 1 <----------------
auto auto8 = make_shared<Fahrzeug>("Porsche 9/11");
auto auto7Neu = std::move(auto6); // Besitzwechel // @suppress("Invalid arguments")

cout << "Counter Auto7 = " << auto7.use_count() << "\n\n"; // auto7.use_count() = 1 <----------------
auto auto6neu = auto7; // Inhalt des Pointers wird in einem neuen sharedpointer kopiert. ---> Jetzt teilen sich mehrere pointer das Objekt.
cout << "Counter Auto7 = " << auto7.use_count() << "\n\n"; //auto7.use_count() = 2 <-----------------

vector<unique_ptr<Fahrzeug>> schlüssel1; // Speicher für Pointer der Objekte. Analogie: Autoschlüssel, da Autos nicht direkt gespeichert werden

schlüssel1.push_back(std::move(auto5)); // Move nötig, da sonst eine Kopie übergeben wird. move -----> Besitzwechsel // @suppress("Invalid arguments")


schlüssel1.clear(); // Vector wird gelöscht. Alle Counter Null

vector<shared_ptr<Fahrzeug>> schlüssel2;

schlüssel2.push_back(auto7); // auto7.use_count() = 1 <----------------------
cout << "Counter Auto7 (vor Besitzerwechsel) = " << auto7.use_count() << "\n\n";
schlüssel2.push_back(std::move(auto7)); // auto7.use_count() = 0; <----------------
cout << "Counter Auto7 (nach Besitzerwechsel) = " << auto7.use_count() << "\n\n" << endl;

schlüssel2.clear(); // Vector wird gelöscht. Alle Counter Null
}

void vAufgabe_1a()
{

	// Dynamischer Speicher für die Fahrzeuge --> Garage
	vector<std::unique_ptr<Fahrzeug>> garage;

	// Einlesen von drei Fahrzeugen
	for (int i = 1; i <= 3; ++i)
	{
	    // Name mit Leerzeichen
	    cout << "Geben Sie den Namen des " << i << "ten Fahrzeugs an: ";
	    getline(std::cin >> std::ws, sName);  // std::ws ignoriert Leerzeichen und Zeilenumbrüche

	    // Maximale Geschwindigkeit (robuste Zahleneingabe)
	    while (true)
	    {
	        cout << "\nGeben Sie die maximale Geschwindigkeit des " << i << "ten Fahrzeugs an: ";
	        cin >> dMaxGeschwindigkeit;
	        // logische Bedingung
	        if (dMaxGeschwindigkeit > 0)
	        {
	            break;
	        }
	        // Eingabefehler beheben
	        cout << "Bitte eine gültige Zahl eingeben.\n";
	    }

	    auto fahrzeug = make_unique<Fahrzeug>(sName, dMaxGeschwindigkeit);
	    garage.push_back(std::move(fahrzeug));
	}
	for (double i=0; i<iStunden; i+=dZeittakt)
	{
		dGlobaleZeit += dZeittakt;
		cout << endl << endl << setw(20) << setfill('-') << "-" << setfill(' ') << endl;
		cout << "Globale-Zeit: " << dGlobaleZeit*60 << " min" << endl;
		cout << setw(20) << setfill('-') << "-" << setfill(' ') << endl << endl;

		Fahrzeug::vKopf();

		// Iterator um auf jeden Vektor zuzugreifen ohne Fehler (Pi1)
		for (auto it = garage.begin(); it != garage.end(); it++)
		{
			(*it)->vSimulieren();
			(*it)->vAusgeben();
		}

	}
}
//////////////////
////Aufgabe 2/////
//////////////////
void vAufgabe_2()
{
		// Dynamischer Speicher für die Fahrzeuge --> Garage
		vector<std::unique_ptr<Fahrzeug>> garage;
		int iAnzahlPKW, iAnzahlFahrrad;

		cout << "Wie viele PKW's sollen erzeugt werden? Geben Sie eine Zahl ein: ";
		cin >> iAnzahlPKW;

		// Einlesen von drei Fahrzeugen
		for (int i = 1; i <= iAnzahlPKW; ++i)
		{
		    // Name mit Leerzeichen
		    cout << "Geben Sie den Namen des " << i << "ten PKW an: ";
		    getline(std::cin >> std::ws, sName);  // std::ws ignoriert Leerzeichen und Zeilenumbrüche

		    // Maximale Geschwindigkeit (robuste Zahleneingabe)
		    while (true)
		    {
		        cout << "\nGeben Sie die maximale Geschwindigkeit des " << i << "ten PKW an: ";
		        cin >> dMaxGeschwindigkeit;
		        // logische Bedingung
		        if (dMaxGeschwindigkeit > 0)
		        {
		            break;
		        }
		        // Eingabefehler beheben
		        cerr << "Bitte eine gültige Zahl eingeben.\n";
		    }

		    while (true)
		    {
		    	cout << "Geben Sie den Verbrauch ein: " << endl;
		    	cin >> dVerbrauch;
				// logische Bedingung
				if (dVerbrauch > 0)
				{
					break;
				}
				// Eingabefehler beheben
				cerr << "Bitte eine gültige Zahl eingeben.\n";
			}

		    while (true)
			 {
				cout << "Geben Sie den Tankvolumen ein: " << endl;
			    cin >> dTankvolumen;
				// logische Bedingung
				if (dTankvolumen > 0)
				{
					break;
				}
				// Eingabefehler beheben
				cerr << "Bitte eine gültige Zahl eingeben.\n";
			 }

		     // Erstellen eines einzigartigen Fahrzeugs und speichern in einem Vektor
		    auto pkw = make_unique<PKW>(sName, dMaxGeschwindigkeit);
		    garage.push_back(std::move(pkw));
		}

		cout << "Wie viele Fahrräder sollen erzeugt werden? ";
		cin >> iAnzahlFahrrad;

		for (int i = 1; i <= iAnzahlFahrrad; ++i)
		{
			// Name mit Leerzeichen
			cout << "\nGeben Sie den Namen des " << i << "ten Fahrrad an: ";
			getline(std::cin >> std::ws, sName);  // std::ws ignoriert Leerzeichen und Zeilenumbrüche

			// Maximale Geschwindigkeit (robuste Zahleneingabe)
			while (true)
			{
				cout << "\nGeben Sie die maximale Geschwindigkeit des " << i << "ten Fahrrad an: ";
				cin >> dMaxGeschwindigkeit;
				// logische Bedingung
				if (dMaxGeschwindigkeit > 0)
				{
					break;
				}
				// Eingabefehler beheben
				cerr << "Bitte eine gültige Zahl eingeben.\n";
			}

			auto fahrrad = make_unique<Fahrrad>(sName, dMaxGeschwindigkeit);
			// PKWs und Fahrräder können zusammen gespeichert werden, weil beide von der selben Klasse erben bzw. beide vom Typ Fahhrzeug sind
			garage.push_back(std::move(fahrrad));
		}

		double dTankZeit = 3.0;
		double epsilon = 0.0001;

		for (double i=0; i<iStunden; i+=dZeittakt)
		{
			dGlobaleZeit += dZeittakt;
			cout << endl << endl << setw(20) << setfill('-') << "-" << setfill(' ') << endl;
			cout << "Globale-Zeit: " << dGlobaleZeit*60 << " min" << endl;
			cout << setw(20) << setfill('-') << "-" << setfill(' ') << endl << endl;

			Fahrzeug::vKopf();

			// Iterator um auf jeden Vektor zuzugreifen ohne Fehler (Pi1)
			for (auto it = garage.begin(); it != garage.end(); it++)
			{
				(*it)->vSimulieren();
				(*it)->vAusgeben();

				// beide Werte sind double Werte also gibt es eine kleine Abweichung. Ist diese Abweichung sehr klein, kann man sie einfach als 3 km runden
				if (std::fmod(dGlobaleZeit, dTankZeit) < epsilon) // dGlobaleZeit modulo dTamkZeit = 0
				{
				(*it)->dTanken();
				}

			}

		}
}

//////////////////
////Aufgabe 3/////
//////////////////
void vAufgabe_3()
{
	    // Dynamischer Speicher für die Fahrzeuge --> Garage
	    vector<std::unique_ptr<Fahrzeug>> garage;

	    Fahrzeug* pkw = new PKW("Porsche 911", 320, 10.9, 204.0);
		Fahrzeug* fahrrad = new Fahrrad("BMX", 35);

		garage.push_back(std::unique_ptr<Fahrzeug>(pkw));
		garage.push_back(std::unique_ptr<Fahrzeug>(fahrrad));

		// Nutzung des überladenen Operators <<
		Fahrzeug::vKopf();
		cout << *pkw << endl;
		cout << *fahrrad << endl;

		const double dTankZeit = 3.0;
		const double epsilon = 0.000001;

		for (double i=0; i<iStunden; i+=dZeittakt)
		{
			dGlobaleZeit += dZeittakt;
			cout << endl << endl << setw(20) << setfill('-') << "-" << setfill(' ') << endl;
			cout << "Globale-Zeit: " << dGlobaleZeit*60 << " min" << endl;
			cout << setw(20) << setfill('-') << "-" << setfill(' ') << endl << endl;

			Fahrzeug::vKopf();

			// Iterator um auf jeden Vektor zuzugreifen ohne Fehler (Pi1)
			for (auto it = garage.begin(); it != garage.end(); it++)
			{
				(*it)->vSimulieren();
				cout << *it->get();

				// Beide Werte sind double Werte also gibt es eine kleine Abweichung. Ist diese Abweichung sehr klein, kann man sie einfach als 3 km runden
				if (std::fmod(dGlobaleZeit, dTankZeit) < epsilon) (*it)->dTanken(); // dGlobaleZeit modulo dTamkZeit = 0
			}

			if(*pkw < *fahrrad)
			{
				cout << "\nDer Fahrradfahrer hat insgesamt mehr zurückgelegt als den Autofahrer\n" << endl;
			}
			else
			{
				cout << "\nDer Autofahrer hat insgesamt mehr zurückgelegt als den Fahrradfahrer\n" << endl;
			}
         }
		// Nutzung des überladenen Operators (=) und (<<)
		Fahrzeug fahrrad2("E-Bike", 35);
		Fahrzeug fahrrad3;
		fahrrad3 = fahrrad2;

		Fahrzeug::vKopf();
		cout << fahrrad2 << endl;
		cout << fahrrad3 << endl;
}

//////////////////
////Aufgabe 4/////
//////////////////
void vAufgabe_4()
{
	// Erstellen eines Weges
	Weg weg("Uhlgasse", 100.0, AUTOBAHN);
	weg.vKopf();
	cout << weg << endl;
}

//////////////////
////Aufgabe 5/////
//////////////////
void vAufgabe_5()
{
	const double dStartzeit = 2.0;

	// Weg erstellen
	Weg weg("Uhlgasse", 1.0, AUTOBAHN);

	// Drei Fahrzeuge Erstellen
	auto fzg_fahrend = make_unique<PKW>("Mercedes Benz GLC 500", 220);
	auto fzg_parkend = make_unique<Fahrzeug>("Mercedes Benz GLC 300", 225);
	auto fzg2_fahrend = make_unique<Fahrrad>("BMX", 35);

	// Fahrzeuge auf Weg setzen
	weg.vAnnahme(std::move(fzg_fahrend));
	weg.vAnnahme(std::move(fzg_parkend), dStartzeit);
	weg.vAnnahme(std::move(fzg2_fahrend));

	//Ausgabe des Weges
	weg.vKopf();
	cout << weg << endl;

	// Simulation //
	const double dZeittakt = 0.5;
	const int iAnzahlSchritte = 10;

	for (int i = 0; i < iAnzahlSchritte; ++i)
	{
		// bei jeder Simulationsschleife Zeit aktualisieren
		dGlobaleZeit += dZeittakt;
		cout << endl << endl << setw(20) << setfill('-') << "-" << setfill(' ') << endl;
		cout << "Globale-Zeit: " << dGlobaleZeit*60 << " min" << endl;
		cout << setw(20) << setfill('-') << "-" << setfill(' ') << endl << endl;
		weg.vSimulieren();
	}
}
///////////////////////////////////////////////////// Optionale Funktionen ///////////////////////////////////////////////////////////////////
// Tankt automatisch alle Fahrzeuge
void vTanke(Weg& weg, double dTankZeit)
{
	const double epsilon = 0.000001; // Fehlertoleranz

	for (auto& fahrzeug_ptr : weg.getFahrzeuge())
		{
			// Beide Werte sind double Werte also gibt es eine kleine Abweichung. Ist diese Abweichung sehr klein, kann man sie einfach als 3 km runden
			if (fmod(dGlobaleZeit, dTankZeit) < epsilon) fahrzeug_ptr->dTanken(); // dGlobaleZeit modulo dTankZeit = 0
		}
}

// Gibt die Zeit in der Grafik und in der Konsole aus
void vUhr()
{
	vSetzeZeit(dGlobaleZeit);
	cout << endl << endl << setw(22) << setfill('-') << "-" << setfill(' ') << endl;
	cout << "Globale-Zeit: " << dGlobaleZeit*60 << " min" << endl;
	cout << setw(22) << setfill('-') << "-" << setfill(' ') << endl << endl;
}

void vFahrzeugAusgabe(const Weg& weg)
{
	Fahrzeug::vKopf();
	for(auto const& fahrzeug_ptr : weg.getFahrzeuge())
	{
		fahrzeug_ptr->vAusgeben();
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////
////Aufgabe 6/////
//////////////////
void vAufgabe_6()
{
	// Definieren der Zeit
	const double dZeittakt = 0.4;
	const int iAnzahlSchritte = 100;
	// Definieren der Tankzeit
	const double dTankZeit = 3.0;
	// Definieren der Startzeit des parkendem Auto
	const double dStartzeit = 2.0;

	auto fzg_fahrend = make_unique<PKW>("Mercedes", 220, 15.0);
	auto fzg_parkend = make_unique<PKW>("Mclaren", 225);
	auto fzg2_fahrend = make_unique<Fahrrad>("BMX", 35);
	auto fzg3_parkend = make_unique<PKW>("Corvette", 220);

	Weg stadt("Innenstadt", 500.0, INNERORTS); // Tempolimit: 50 kmh
	Weg a555("Autobahn", 500.0, AUTOBAHN, false); // Tempolimit: unbegrenzt // kein Überholverbot

	// Intialisierung der Grafik auf dem SimuServer
	bInitialisiereGrafik(800, 500);

	// Setzen der Koordinaten für die Straße, gerade Linie
	int koordinaten[4] = {700, 250, 10, 250};

	// Zeichnen der Straße
	bZeichneStrasse(stadt.getName(), a555.getName(), stadt.getLaenge(), 2, koordinaten); // Array muss genau (2 x AnzahlKoord) int-Elemente enthalten

	a555.vAnnahme(std::move(fzg_fahrend));
	stadt.vAnnahme(std::move(fzg_parkend), dStartzeit);
	stadt.vAnnahme(std::move(fzg2_fahrend));
	// Fahrzeug startet nach der ersten hälfte der Simulation
	a555.vAnnahme(std::move(fzg3_parkend), dZeittakt*iAnzahlSchritte/2);

	//Ausgabe des Weges
	stadt.vKopf();
	cout << stadt << endl;
	a555.vKopf();
	cout << a555 << endl;

	for (dGlobaleZeit = 0; dGlobaleZeit <= (dZeittakt * iAnzahlSchritte); dGlobaleZeit += dZeittakt)
		{
			vUhr(); // Gibt die Zeit in der Grafik und in der Konsole aus
			stadt.vSimulieren();
			a555.vSimulieren();

			vTanke(stadt, dTankZeit);
			vTanke(a555, dTankZeit);

			//Ausgabe des Weges
			stadt.vKopf();
			cout << stadt << endl;
			a555.vKopf();
			cout << a555 << endl;

			vSleep(100);
		}

	vBeendeGrafik();
}

///////////////////
////Aufgabe 6a/////
///////////////////
// Testprogramm für Vertagt_Liste
void vAufgabe_6a()
{
	// Vertagt Liste erzeugen
	vertagt::VListe<int> vListe;

	static std::mt19937 device(0);
	std::uniform_int_distribution<int> dist(1, 10);
	//int zuf = dist(device);

	// 10 Zufallszahlen generieren
	for(int i = 1; i <= 10; i++)
	{
		vListe.push_back(dist(device));
	}
	cout << endl << endl;
	vListe.vAktualisieren();

	// Ausgeben mit Aktualisierung der Liste
	for(auto it = vListe.begin(); it != vListe.end(); it++)
	{
		std::cout << (*it) << " ";
	}
	cout << endl << endl;

	// Ausgeben ohne Aktualisierung der Liste
	for(auto it = vListe.begin(); it != vListe.end(); it++)
	{
			if ((*it) < 5) vListe.erase(it);
	}
	cout << endl << endl;

	vListe.vAktualisieren();

	// Ausgeben mit Aktualisierung der Liste
	for(auto it = vListe.begin(); it != vListe.end(); it++)
		{
				if ((*it) < 5) vListe.erase(it);
		}
	cout << endl << endl;

	vListe.push_front(dist(device));
	vListe.push_back(dist(device));

	// Ausgeben ohne Aktualisierung der Liste
	for(auto it = vListe.begin(); it != vListe.end(); it++)
			{
					if ((*it) < 5) vListe.erase(it);
			}
	cout << endl << endl;

	// Liste aktualisieren
	vListe.vAktualisieren();

	// Ausgeben mit Aktualisierung der Liste
	for(auto it = vListe.begin(); it != vListe.end(); it++)
			{
					if ((*it) < 5) vListe.erase(it);
			}
}

//////////////////
////Aufgabe 7/////
//////////////////
void vAufgabe_7()
{
	// Definieren der Zeit
	const double dZeittakt = 0.05;
	const int iAnzahlSchritte = 600;

	// Liste um alle Kreuzungen in einer Schleife zu simulieren
	std::list<std::shared_ptr<Kreuzung>> kreuzungenListe;

	bInitialisiereGrafik(1000, 800); // bInitialisiereGrafik(Breite, Höhe)

	std::shared_ptr<Kreuzung> Kr1 = std::make_shared<Kreuzung>("Kr1");
	std::shared_ptr<Kreuzung> Kr2 = std::make_shared<Kreuzung>("Kr2", 1000);
	std::shared_ptr<Kreuzung> Kr3 = std::make_shared<Kreuzung>("Kr3");
	std::shared_ptr<Kreuzung> Kr4 = std::make_shared<Kreuzung>("Kr4");

	Kreuzung::vVerbinde("W12", "W21", 40, Kr1, Kr2, INNERORTS);           // Straße 1
	Kreuzung::vVerbinde("W23a", "W32a", 115, Kr2, Kr3, AUTOBAHN, false);  // Straße 2
	Kreuzung::vVerbinde("W23b", "W32b", 40, Kr2, Kr3, INNERORTS);         // Straße 3
	Kreuzung::vVerbinde("W24", "W42", 55, Kr2, Kr4, INNERORTS);           // Straße 4
	Kreuzung::vVerbinde("W34", "W43", 85, Kr3, Kr4, AUTOBAHN, false);     // Straße 5
	Kreuzung::vVerbinde("W44a", "W44b", 130, Kr4, Kr4, INNERORTS, false); // Straße 6

	// bZeichneKreuzung(X-Koordinaten, Y-Koordinaten)
	bZeichneKreuzung(680, 40);  // Kr1
	bZeichneKreuzung(680, 300); // Kr2
	bZeichneKreuzung(680, 570); // Kr3
	bZeichneKreuzung(320, 300); // Kr4

	// bZeichneStrasse(Name Startweg, Name Zielweg, Länge der Straße, Koordinatenpaare bzw Punkte, Koordinaten der verschiedenen Straßen)
	int iKoordinaten1[4] = {680, 40, 680, 300};
	bZeichneStrasse("W12", "W21", 40, 2, iKoordinaten1); // 1

	int iKoordinaten2[12] = {680, 300, 850, 300, 970, 390, 970, 500, 850, 570, 680, 570};
	bZeichneStrasse("W23a", "W32a", 115, 6, iKoordinaten2); // 2

	int iKoordinaten3[4] = {680, 300, 680, 570};
	bZeichneStrasse("W23b", "W32b", 40, 2, iKoordinaten3); // 3

	int iKoordinaten4[4] = {680, 300, 320, 300};
	bZeichneStrasse("W24", "W42", 55, 2, iKoordinaten4); // 4

	int iKoordinaten5[10] = {680, 570, 500, 570, 350, 510, 320, 420, 320, 300};
	bZeichneStrasse("W34", "W43", 85, 5, iKoordinaten5); // 5

	int iKoordinaten6[14] = {320, 300, 320, 150, 200, 60, 80, 90, 70, 250, 170, 300, 320, 300};
	bZeichneStrasse("W44a", "W44b", 130, 7, iKoordinaten6); // 6

	auto fzg1 = make_unique<PKW>("Mercedes", 120, 7);
	auto fzg2 = make_unique<PKW>("Mclaren", 200, 12);
	auto fzg3 = make_unique<Fahrrad>("BMX", 35);
	auto fzg4 = make_unique<PKW>("Corvette", 140, 8);

	Kr1->vAnnahme(std::move(fzg1), 0.5);
	Kr1->vAnnahme(std::move(fzg2), 0.4);
	Kr1->vAnnahme(std::move(fzg3), 0.3);
	Kr1->vAnnahme(std::move(fzg4), 0.2);

	kreuzungenListe.push_back(std::move(Kr1));
	kreuzungenListe.push_back(std::move(Kr2));
	kreuzungenListe.push_back(std::move(Kr3));
	kreuzungenListe.push_back(std::move(Kr4));

	for (dGlobaleZeit = 0; dGlobaleZeit <= (dZeittakt * iAnzahlSchritte); dGlobaleZeit += dZeittakt)
		{
			vUhr();

			for (auto it = kreuzungenListe.begin(); it != kreuzungenListe.end(); it++)
			{
				(*it)->vSimulieren();
			}
			vSleep(1);
		}
	vSleep(1000);
	vBeendeGrafik();
}
//////////////////
////Aufgabe 8/////
//////////////////
void vAufgabe_8()
{
	// Einlesen der VO.dat Datei
	std::ifstream fin("VO.dat");

	// wirft eine Fehlermeldung, wenn die Datei nicht geöffnet werden kann
	if (!fin)
	{
		throw std::runtime_error("Fehler beim Öffnen der Datei VO.dat");
		return;
	}

	// PKW und Fahrrad erstellen
	auto pkw1 = std::make_unique<PKW>();
	auto fahrrad1 = std::make_unique<Fahrrad>();
	// Kreuzung erstellen
	auto kr1 = std::make_unique<Kreuzung>();

	try
	{
		// Einlesen der Daten
		fin >> *pkw1;
		fin >> *fahrrad1;
		fin >> *kr1;

		Fahrzeug::vKopf();
		cout << *pkw1;
		cout << *fahrrad1;
		cout << *kr1;
    }
	catch(const std::exception& ausnahme)
	{
		// what() gibt den Fehler aus, der in runtime-Error geschrieben wurde
		cout << "Ausnahme: " << ausnahme.what() << endl;
		return;
	}
}
//////////////////
////Aufgabe 9/////
//////////////////
void vAufgabe_9()
{
	// Einlesen der VO.dat Datei
	auto simulation = std::make_unique<Simulation>();
	std::ifstream fin("Simu.dat");

	if (!fin)
	{
		throw std::runtime_error("Fehler beim Einlesen der Datei");
		return;
	}

	// Einlesen und simulieren
	fin >> *simulation;
	simulation->vSimulieren(15, 0.1);
}
//////////////////
////Aufgabe 9a////
//////////////////
void vAufgabe_9a()
{
	bInitialisiereGrafik(1500, 1500); // bInitialisiereGrafik(Breite, Höhe)
	// Einlesen der VO.dat Datei
	auto simulation = std::make_unique<Simulation>();
	std::ifstream fin("SimuDisplay.dat");

	if (!fin)
	{
		throw std::runtime_error("Fehler beim Einlesen der Datei");
		return;
	}

	// Einlesen und simulieren
	simulation->vEinlesen(fin, true);
	simulation->vSimulieren(600, 0.05);
	//vBeendeGrafik(); ist schon in vSimulieren in Simulation drin
}

#include "Fahrzeug.h"
#include "Fahrrad.h"
#include "PKW.h"
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <iomanip>
#include <cmath>

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
void vAufgabe_AB1();

/////////////////////
////Hauptfunktion////
/////////////////////
int main()
{
//vAufgabe_1();
//vAufgabe_1a();
//vAufgabe_2();
//vAufgabe_3();
vAufgabe_AB1();
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

		double dTankZeit = 3.0;
		double epsilon = 0.000001;

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
				cout << *(*it);

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

extern double dGlobaleZeit;
double dEpsilon = 0.001;

void vAufgabe_AB1() {

    int l = 0; // Laufindex für gezielte AUsgabe
    vector<int> ausgabe{13};
    double dTakt = 0.4;

    std::vector<unique_ptr<Fahrzeug>> vecFahrzeuge;
    vecFahrzeuge.push_back(make_unique <PKW>("Audi", 229, 9.6));
    vecFahrzeuge.push_back(make_unique <Fahrrad>("BMX", 24.7));
    for (dGlobaleZeit = 0; dGlobaleZeit < 10; dGlobaleZeit += dTakt)
    {
        auto itL = find(ausgabe.begin(), ausgabe.end(), l);
        if (itL != ausgabe.end()) {
            std::cout << std::endl << l <<  " Globalezeit = " << dGlobaleZeit << std::endl;
            Fahrzeug::vKopf();
        }

        for (int i = 0; i < vecFahrzeuge.size(); i++)
        {
            vecFahrzeuge[i]->vSimulieren();
            if (fabs(dGlobaleZeit - 3.0) < dTakt/2)
            {
                vecFahrzeuge[i]->dTanken();
            }
            if (itL != ausgabe.end()) {
                std::cout << *vecFahrzeuge[i] << endl;
            }
        }
        l++;
    }
    char c;
    std::cin >> c;
}

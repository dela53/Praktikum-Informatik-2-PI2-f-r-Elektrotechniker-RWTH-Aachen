#pragma once

#include "vertagt_aktion.h"
#include <list>
#include <memory>
/*
 * Eine Liste die die sich die Veränderungen in der Liste merkt und am ende der Schleife ausführt,
 * damit der Iterator nicht während der Schleife zerstört wird und damit das Programm weiter simuliert
 */
namespace vertagt
{
/* Eine Liste die die sich die Veränderungen in der Liste merkt und am Ende einer Schleife mit fzg.aktualisieren() ausführt,
 * damit der Iterator nicht während der Schleife zerstört wird und damit das Programm weiter simuliert
 */
	template <class T>
	class VListe
	{
	private:
		std::list<T> p_objekte; // die echten Daten
		std::list<std::unique_ptr<VAktion<T>>> p_aktionen; // die gemerkten Änderungen

	public:
		// Typdefinitionen
		using iterator = typename std::list<T>::iterator;
		using const_iterator = typename std::list<T>::const_iterator;

		// Konstruktoren
		VListe() = default; // default damkt der Standardkonstruktor nicht automatisch vom Compiler gelöscht wird
		// Destruktor
		~VListe()
		{
			vAktualisieren();
			p_objekte.clear();
		}

		void clear()
		{
			p_aktionen.clear();
		}

		// Lesefunktionen
		const_iterator begin() const
		{
			return p_objekte.begin();
		}
		const_iterator end() const
		{
			return p_objekte.end();
		}
		iterator begin()
		{
			return p_objekte.begin();
		}
		iterator end()
		{
			return p_objekte.end();
		}
		bool empty() const
		{
			return p_objekte.empty();
		}

        // std::make_unique<VPushBack<T>>(p_objekte, std::move(obj)) ---> Objekt wird in der echten Liste eingefügt bzw verschoben und es wird ein ptr darauf erstellt
		// Schreibfunktionen. p_aktionen.push_back speichert die Aktionen die gemacht werden müssen
		void push_back(T obj)
		{
			// Aktionselement für PushBack auf Liste erzeugen // PushBack hat zwei Parameter
			p_aktionen.push_back(std::make_unique<VPushBack<T>>(p_objekte, std::move(obj))); // obj geht nicht da es vom Typ T ist und nicht VPushBack<T>
		}

		void push_front(T obj)
		{
			// Aktionselement für PushBack auf Liste erzeugen
			p_aktionen.push_back(std::make_unique<VPushFront<T>>(p_objekte, std::move(obj)));
		}

		void erase(iterator it)
		{
			// Aktionselement für PushBack auf Liste erzeugen (hier Iterator statt Objekt !)
			p_aktionen.push_back(std::make_unique<VErase<T>>(p_objekte, it));
		}

		// Änderungen auf Objektliste übertragen
		void vAktualisieren()
		{
			// Änderungen auf Objektliste übertragen
			for (auto& pAktion : p_aktionen)
			{
				// Aktion ausführen
				pAktion->vAusfuehren();
			}
			// Aktionsliste löschen
			p_aktionen.clear();
		}
	};
} // namespace vertagt

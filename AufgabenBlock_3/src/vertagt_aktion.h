#pragma once

#include <list>

namespace vertagt
{
	// Oberklasse VAktion
	template <class T>
	class VAktion
	{
	protected:
		std::list<T>& p_pListe;  // Zeiger auf Liste der Objekte

	public:
	    // Benötigt man einen Standardkonstruktor? Nein
		VAktion(std::list<T>& ptListe) : p_pListe(ptListe){}
		virtual ~VAktion() = default;
		virtual void vAusfuehren() = 0;
	};

	// Klasse die sich merkt, dass sich das gefundene Objekt hinten in der Liste eingefügt werden muss
	template <class T>
	class VPushBack : public VAktion<T>
	{
	public:
		using iterator = typename std::list<T>::iterator;

	private:
		T p_objekt;

	public:
		VPushBack(std::list<T>& liste, T obj) : VAktion<T>(liste), p_objekt(std::move(obj))	{}
		virtual ~VPushBack() = default;
		void vAusfuehren() override
		{
			VAktion<T>::p_pListe.push_back(std::move(p_objekt));
		}
	};

	// Klasse die sich merkt, dass sich das gefundene Objekt ganz vorne in der Liste eingefügt werden muss
	template <class T>
		class VPushFront : public VAktion<T>
	    {
	    public:
	    	using iterator = typename std::list<T>::iterator;

		private:
	    	T p_objekt;

		public:
			VPushFront(std::list<T>& liste, T obj): VAktion<T>(liste), p_objekt(std::move(obj)) {}
			virtual ~VPushFront() = default;
			void vAusfuehren() override
			{
				VAktion<T>::p_pListe.push_front(std::move(p_objekt));
			}
    };

	// Klasse die sich merkt, dass sich das gefundene Objekt aus der Liste entfernt werden muss
	template <class T>
	class VErase : public VAktion<T>
	{
	public:
		using iterator = typename std::list<T>::iterator;

	private:
		iterator p_it;  // bei erase Iterator speichern

	public:
		VErase(std::list<T>& liste, iterator it) : VAktion<T>(liste), p_it(it) {}
		virtual ~VErase() = default;
		void vAusfuehren() override
		{
			VAktion<T>::p_pListe.erase(p_it);
		}
	};
}  // namespace vertagt

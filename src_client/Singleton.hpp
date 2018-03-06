#ifndef _SINGLETON_H_
# define _SINGLETON_H_

template<typename T> class Singleton
{
public:
	static T& Instance()
	{
		static T theSingleInstance; // suppose que T a un constructeur par défaut
		return theSingleInstance;
	}
};
 
# endif
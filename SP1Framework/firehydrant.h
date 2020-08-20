#pragma once
#include "Entities.h"
#include <Windows.h>

class firehydrant : public Entity
{
protected:
	static int total_no_of_hydrant;

	COORD position;
public:

	firehydrant();
	~firehydrant();

	static void SetTotalHydrant(int SetTotalHr);
	static int GetTotalHydrant();



	
};


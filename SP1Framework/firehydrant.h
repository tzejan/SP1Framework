#pragma once
#include "Entities.h"
#include <wincontypes.h>
class firehydrant : public Entity
{
protected:
	static int total_no_of_hydrant;
	COORD position;
public:
	static void SetTotalHydrant(int SetTotalHr);
	static int GetTotalHydrant();


	void RandomHydrantSpawn();
};


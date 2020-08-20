#pragma once
#include "Entities.h"
class firehydrant : public Entity
{
protected:
	static int total_no_of_hydrant;
public:
	static void SetTotalHydrant(int SetTotalHr);
	static int GetTotalHydrant();
};


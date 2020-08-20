#include "firehydrant.h"

firehydrant::firehydrant()
{
	position.X = 10;
	position.Y = 10;

}

firehydrant::~firehydrant()
{
}

void firehydrant::SetTotalHydrant(int SetTotalHr)
{
	total_no_of_hydrant = SetTotalHr;
}

int firehydrant::GetTotalHydrant()
{
	return total_no_of_hydrant;
}



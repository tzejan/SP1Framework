#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <windows.h>


using namespace std;

int main()

{

	int s = 180;
	
		cout << "You have 3 minutes " << endl;


		for (s; s >= 0; s--)
	    {
		
		Sleep(1000);
		system("cls");
		cout << "time remaining" << endl;
		cout << "seconds:" << s << endl;
		

		if (s == 0)
		{
			Sleep(1000);
			cout << "THE END" << endl;
		}
		
	}


	return 0;
}
#include <iostream>
#include <string>

using namespace std;

int** matriceDistances(string s1, string s2)
{
	int n1 = s1.size();
	int n2 = s2.size();

	n1++;
	n2++;

	int** T = new int*[n1];    //alluer la matrice
	for (int i = 0; i < n1; ++i)
		T[i] = new int[n2];

	for (int i = 0; i < n1; ++i)
		T[i][0] = i;
	for (int j = 0; j < n2; ++j)
			T[0][j] = j;

	for (int i = 1; i < n1; ++i){
		for (int j = 1; j < n2; ++j){
			int x = 0;
			if (s1[i-1] != s2[j-1])
			 	x = 1;
			 
			 T[i][j] = min(T[i-1][j]+1, min(T[i][j-1]+1, T[i-1][j-1]+x));
		}
	}


  return T; // À modifier
}

int alignement(string& s1, string& s2)
{
	int n1 = s1.size();
	int n2 = s2.size();

	int i = n1;
	int j = n2;

	n1++;
	n2++;

	int** T = new int*[n1];    //alluer la matrice
	for (int i = 0; i < n1; ++i)
		T[i] = new int[n2];

	T = matriceDistances(s1, s2);
	int distance = T[n1-1][n2-1];

	while (i > 0 && j > 0){
		if (T[i][j] == T[i-1][j-1] && s1[i-1] == s2[j-1])
		{
			i--;
			j--;
		}
		else if (T[i][j] == T[i-1][j-1]+1)
		{
			i--;
			j--;
		}
		else if (T[i][j] == T[i-1][j]+1)
		{
			s2.insert(j,"_");
			i--;
		}
		else if (T[i][j] == T[i][j-1]+1)
		{
			s1.insert(i,"_");
			j--;
		}
	}

	for (int i=0; i<n1; i++) delete[] T[i];
        delete[] T;

  return distance; // À modifier
}

int distanceEdition(string s1, string s2)
{
	int m = s1.size();
	int n = s2.size();

	int* P = new int[n+1];
	int* C = new int[n+1];

	for (int j = 0; j <= n; ++j)
		P[j] = j;

	for (int i = 1; i <= m; ++i)
	{
		C[0] = i;
		for (int j = 1; j <= n; ++j)
		{
			int x;
			if (s1[i-1] == s2[j-1])
				x = 0;
			else
				x = 1;
			C[j] = min(P[j]+1, min(C[j-1]+1, P[j-1]+x));
		}
		for (int j = 0; j <= n; ++j)
			P[j] = C[j];
	}

	delete[] P;

  return C[n]; // À modifier
}

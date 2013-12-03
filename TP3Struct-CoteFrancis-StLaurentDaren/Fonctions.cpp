#include "Fonctions.h"

#include <algorithm>

using namespace std;

string Int64ToString(__int64 const& ri64, int iRadix)
{
	bool bNeg = (ri64 < 0);
	__int64 i64 = ri64;
	string ostrRes;
	bool bSpecial = false;
	if(true == bNeg)
	{
		i64 = -i64;
		if(i64 < 0)
			//Special case number -9223372036854775808 or 0x8000000000000000
			bSpecial = true;
		ostrRes.append(1, '-');
	}
	int iR;
	do
	{
		iR = i64 % iRadix;
		if(true == bSpecial)
			iR = -iR;
		if(iR < 10)
			ostrRes.append(1, '0' + iR);
		else
			ostrRes.append(1, 'A' + iR - 10);
		i64 /= iRadix;
	}
	while(i64 != 0);
	//Reverse the string
	string::iterator it = ostrRes.begin();
	if(bNeg)
		it++;
	reverse(it, ostrRes.end());
	return ostrRes;
}

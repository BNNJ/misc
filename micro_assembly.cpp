#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

int main()
{
	int R[4],n,immediate;
	cin>>R[0]>>R[1]>>R[2]>>R[3]>>n; cin.ignore(1);
	istringstream reader;
	auto operand = [&]() -> int&
	{
		if(reader>>immediate)
			return immediate;
		reader.clear();
		return R[reader.get()-'a'];
	};
	vector<string> code;
	while(n--)
	{
		string inst;  getline(cin,inst);
		code.push_back(inst);
	}
	for(int ip=0;ip<code.size();++ip)
	{
		reader = istringstream(code[ip]);
		string inst;  reader>>inst;
		switch(inst[0])
		{
			case 'M': { int &dst=operand(); dst=operand(); } break;
			case 'A': { int &dst=operand(); dst=operand()+operand(); } break;
			case 'S': { int &dst=operand(); dst=operand()-operand(); } break;
			case 'J': { int addr=operand(); if(operand()!=operand())ip=addr-1; } break;
		}
	}
	cout << R[0] << " " << R[1] << " " << R[2] << " " << R[3] << endl;
}

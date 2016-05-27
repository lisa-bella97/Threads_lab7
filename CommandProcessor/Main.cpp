#include "CommandProcessor.h"
#include <vector>
#include <sstream>

vector<string> split(const string &s, char delim);

int main()
{
	CommandProcessor cp;
	string command;
	cout << '>';
	while (getline(cin, command))
	{
		if (command.substr(0, 4) == "echo")
		{
			thread t(&CommandProcessor::echo, &cp, command.substr(5));
			t.join();
		}
		else if (command.substr(0, 5) == "alarm")
		{
			thread t(&CommandProcessor::alarm, &cp, stoi(command.substr(6)));
			t.detach();
		}
		else if (command.substr(0, 6) == "calarm")
		{
			thread t(&CommandProcessor::calarm, &cp, stoi(command.substr(7)));
			t.join();
		}
		else if (command.substr(0, 5) == "start")
		{
			thread t(&CommandProcessor::start, &cp, stoi(command.substr(6)));
			t.detach();
		}
		else if (command.substr(0, 6) == "cancel")
		{
			thread t(&CommandProcessor::cancel, &cp, stoi(command.substr(7)));
			t.join();
		}
		else if (command.substr(0, 4) == "find")
		{
			vector<string> expressions = split(command, ' ');
			if (expressions.size() != 3)
				cout << "Incorrect command\n";
			thread t(&CommandProcessor::find, &cp, expressions[1], expressions[2]);
			t.detach();
		}
		else
			cout << "Incorrect command\n";
		cout << '>';
	}
	system("pause");
	return 0;
}

vector<string> split(const string &s, char delim)
{
	vector<string> elems;
	stringstream ss(s);
	string item;

	while (getline(ss, item, delim))
		elems.push_back(item);

	return elems;
}

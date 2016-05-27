#include "CommandProcessor.h"

int CommandProcessor::alarm_id = 0;

void CommandProcessor::echo(string& text)
{
	unique_lock<mutex> lk(mut);
	cout << text << endl;
}

void CommandProcessor::alarm(size_t sec)
{
	unique_lock<mutex> lk(mut);
	lk.unlock();
	this_thread::sleep_for(chrono::seconds(sec));
	cout << "\nAlarm!!!\n>";
}

void CommandProcessor::calarm(size_t sec)
{
	unique_lock<mutex> lk(mut);
	cout << "calarm " << ++alarm_id << " created" << endl;
	alarms.insert(pair<size_t, pair<size_t, bool>>(alarm_id, pair<size_t, bool>(sec, false)));
}

void CommandProcessor::start(size_t id)
{
	unique_lock<mutex> lk(mut);
	auto alarm = alarms.find(id);
	if (alarm == alarms.end())
		return;
	lk.unlock();
	this_thread::sleep_for(chrono::seconds(alarm->second.first));
	if (!alarm->second.second)
		cout << "\nAlarm!!!\n>";
	alarm->second.second = false;
}

void CommandProcessor::cancel(size_t id)
{
	unique_lock<mutex> lk(mut);
	auto alarm = alarms.find(id);
	if (alarm == alarms.end())
		return;
	alarm->second.second = true;
}

void CommandProcessor::find(string& filename, string& expression)
{
	unique_lock<mutex> lk(mut);
	ifstream fin(filename);
	if (!fin)
		return;
	cout << endl << filename << " is being processed\n>";
	lk.unlock();
	string str;
	int pos = 0;
	int counter = 0;
	while (getline(fin, str))
	{
		while (true)
		{
			pos = str.find(expression);
			if (pos == string::npos)
				break;
			str = str.substr(pos + expression.size());
			counter++;
		} 
	}
	fin.close();
	cout << endl << expression << " was found " << counter << " times\n>";
}

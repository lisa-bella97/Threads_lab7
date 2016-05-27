#pragma once
#include <iostream>
#include <thread>
#include <mutex>
#include <string>
#include <map>
#include <fstream>

using namespace std;

class CommandProcessor
{
	mutex mut;
	map<size_t, pair<size_t, bool>> alarms;
public:
	static int alarm_id;
	CommandProcessor() {}
	void echo(string& text);
	void alarm(size_t sec);
	void calarm(size_t sec);
	void start(size_t id);
	void cancel(size_t id);
	void find(string& filename, string& expression);
	~CommandProcessor() { alarms.clear(); }
};

#pragma once

class CSVScanner : public ThreadWithProgressWindow
{
public:
	CSVScanner(String filename);

	Result scan();

	virtual void run();

protected:
	File csvFile;
	File logFile;
	Result result;

	void parseLine(String const &line, StringArray &tokens);
	void handleASIOHostNotify(StringArray & tokens);
	void handleASIOOutputReady(StringArray & tokens);

	double hostNotifySeconds;
	double maxElapsedHostNotifySeconds;
	double maxCallbackSeconds;
};


#pragma once
#include "StreamManager.h"

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
	FileInputStream csvInputStream;
	StreamManager streamManager;

	void parseLine(String const &line, StringArray &tokens);
	void handleASIOHostNotify(StringArray & tokens);
	void handleASIOOutputReady(StringArray & tokens);

	double hostNotifySeconds;
	double maxElapsedHostNotifySeconds;
	double maxCallbackSeconds;

	enum 
	{
		MEGA_BYTE = 1024 * 1024
	};

	static const String comma;
	static const String ASIOHostNotify;
	static const String ASIOOutputReady;
	static const String AVTPTransmit;
	static const String AVTPReceive;

	JUCE_LEAK_DETECTOR(CSVScanner);
};


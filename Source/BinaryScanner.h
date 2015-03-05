#pragma once

#include "EventLog.h"
#include "EventList.h"

class BinaryScanner : public ThreadWithProgressWindow
{
public:
	BinaryScanner(String filename);

	Result scan();

	virtual void run();

protected:
	File binaryFile;
	File outputFile;
	Result result;
	FileInputStream binaryInputStream;

	double hostNotifySeconds;
	double maxElapsedHostNotifySeconds;
	double maxCallbackSeconds;

	const String comma;

	enum 
	{
		MEGA_BYTE = 1024 * 1024
	};

	JUCE_LEAK_DETECTOR(BinaryScanner);
	void parseEntry(EventLogEntry const &entry, String &line, FileOutputStream &outputStream);
	void getEventText(EventLogEntry const &entry, String &text);
};


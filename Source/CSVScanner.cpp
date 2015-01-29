#include "JuceHeader.h"
#include "CSVScanner.h"

CSVScanner::CSVScanner(String filename) :
result(Result::ok()),
hostNotifySeconds(0.0),
maxElapsedHostNotifySeconds(0.0),
maxCallbackSeconds(0.0),
ThreadWithProgressWindow("CSV Scanner",true,true)
{
	csvFile = File::getCurrentWorkingDirectory().getChildFile(filename);
	logFile = File::getCurrentWorkingDirectory().getFullPathName() + "\\log.txt";

	if (logFile.existsAsFile())
	{
		logFile.deleteFile();
	}
}

Result CSVScanner::scan()
{
	if (false == csvFile.exists())
		return Result::fail(csvFile.getFullPathName() + " does not exist");

	if (runThread())
	{
		return result;
	}

	return Result::fail("User canceled");
}

void CSVScanner::run()
{
	int64 bytes = csvFile.getSize();
	int64 remaining = bytes;
	FileInputStream inputStream(csvFile);

	String line;
	StringArray tokens;

	do
	{
		if (threadShouldExit())
		{
			result = Result::fail("User canceled");
			return;
		}

		line = inputStream.readNextLine();

		parseLine(line, tokens);

		remaining -= line.getNumBytesAsUTF8();
		int64 progress = bytes - remaining;
		setProgress(double(progress) / bytes);
	} while (line.isNotEmpty());
}

String const comma(",");
String ASIOHostNotify("ASIO host notify");
String ASIOOutputReady("ASIO output ready");

void CSVScanner::parseLine(String const &line, StringArray &tokens)
{
	if (false == logFile.existsAsFile())
	{
		logFile.create();
	}

	tokens.clearQuick();
	tokens.addTokens(line, comma, String::empty);

	if (ASIOHostNotify == tokens[3])
	{
		handleASIOHostNotify(tokens);
		return;
	}

	if (ASIOOutputReady == tokens[3])
	{
		handleASIOOutputReady(tokens);
		return;
	}
}

void CSVScanner::handleASIOHostNotify(StringArray & tokens)
{
	double seconds = tokens[1].getDoubleValue();
	double elapsedSeconds = 0.0;
	if (hostNotifySeconds != 0.0)
	{
		elapsedSeconds = seconds - hostNotifySeconds;
	}
	hostNotifySeconds = seconds;

	if (elapsedSeconds > maxElapsedHostNotifySeconds)
	{
		String logString("an ASIO Host Notify event has set a new maxElapsedHostNotifySeconds entry: " + String(elapsedSeconds) + " seconds. \n");
		logString += "The previous maxElapsedHostNotifySeconds was: " + String(maxElapsedHostNotifySeconds) + " seconds. \n";
		logString += "This happened on eventIndex: " + tokens[0] + ". \n\n";
		logFile.appendText(logString);

		maxElapsedHostNotifySeconds = elapsedSeconds;
	}
}

void CSVScanner::handleASIOOutputReady(StringArray & tokens)
{
	double seconds = tokens[1].getDoubleValue();
	double callbackSeconds = 0.0;
	if (hostNotifySeconds != 0.0)
	{
		callbackSeconds = seconds - hostNotifySeconds;
	}

	if (callbackSeconds > maxCallbackSeconds)
	{
		String logString("an ASIO Output Ready event has set a new maxCallbackSeconds entry: " + String(callbackSeconds) + " seconds. \n");
		logString += "The previous maxCallbackSeconds was: " + String(maxCallbackSeconds) + " seconds. \n";
		logString += "This happened on eventIndex: " + tokens[0] + ". \n\n";
		logFile.appendText(logString);
	}

	maxCallbackSeconds = jmax(maxCallbackSeconds, callbackSeconds);
}

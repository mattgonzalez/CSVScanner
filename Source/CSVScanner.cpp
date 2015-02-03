#include "JuceHeader.h"
#include "CSVScanner.h"

const String CSVScanner::comma(",");
const String CSVScanner::ASIOHostNotify("ASIO host notify");
const String CSVScanner::ASIOOutputReady("ASIO output ready");
const String CSVScanner::AVTPTransmit("AVTP transmit");
const String CSVScanner::AVTPReceive("AVTP receive");


CSVScanner::CSVScanner(String filename) :
result(Result::ok()),
hostNotifySeconds(0.0),
maxElapsedHostNotifySeconds(0.0),
maxCallbackSeconds(0.0),
csvFile(File::getCurrentWorkingDirectory().getChildFile(filename)),
csvInputStream(File::getCurrentWorkingDirectory().getChildFile(filename)),
ThreadWithProgressWindow("CSV Scanner",true,true)
{
	
}

Result CSVScanner::scan()
{
	File outputFolder(File::getCurrentWorkingDirectory());
	logFile = File(outputFolder.getChildFile(csvFile.getFileNameWithoutExtension() + ".out.txt"));

	if (false == csvInputStream.openedOk())
	{
		return Result::fail("Could not open the specified CSV file, quitting!");
	}

	if (logFile.existsAsFile())
	{
		logFile.deleteFile();
		logFile.create();
	}

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
#ifdef _WIN64
	BufferedInputStream bufferedCSVInputStream(csvInputStream, 1024 * MEGA_BYTE);
#else
	BufferedInputStream bufferedCSVInputStream(csvInputStream, 512 * MEGA_BYTE);
#endif

	String line;
	StringArray tokens;

	while (false == bufferedCSVInputStream.isExhausted())
	{
		if (threadShouldExit())
		{
			result = Result::fail("User canceled");
			return;
		}

		line = bufferedCSVInputStream.readNextLine();
		parseLine(line, tokens);

		remaining -= line.getNumBytesAsUTF8();
		int64 progress = bytes - remaining;
		setProgress(double(progress) / bytes);
	}
}

void CSVScanner::parseLine(String const &line, StringArray &tokens)
{
	tokens.clearQuick();

	//tokens.addTokens(line, comma, String::empty);
	
	int length = line.length();
	int tokenStart = 0, tokenEnd = 0;
	for (; tokenEnd < length; ++tokenEnd)
	{
		if (',' == line[tokenEnd])
		{
			String token(line.substring(tokenStart, tokenEnd));
			//DBG(token);
			tokens.add(token);
			tokenStart = tokenEnd + 1;
		}
	}
	tokens.add(line.substring(tokenStart, tokenEnd));

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

#if 1
	if (AVTPTransmit == tokens[3])
	{
		streamManager.handleAVTPTransmit(tokens, logFile);
		return;
	}
#endif

	if (AVTPReceive == tokens[3])
	{
		streamManager.handleAVTPReceive(tokens, logFile);
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

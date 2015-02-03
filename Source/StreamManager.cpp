#include "JuceHeader.h"
#include "StreamManager.h"

StreamManager::StreamManager()
{

}

StreamManager::~StreamManager()
{
	talkerStreams.clear();
}

void StreamManager::handleAVTPTransmit(StringArray & tokens, File &logFile)
{
	int64 streamID = tokens[4].getHexValue64();
	Stream& stream(findTalkerStream(streamID));

	uint64 egress = tokens[7].getLastCharacters(17).getHexValue64();
	double eventSeconds = tokens[1].getDoubleValue();
	if (stream.previousOK)
	{
		int64 egressInterval = egress - stream.previousReferenceTime;
		double eventInterval = eventSeconds - stream.previousEventSeconds;
		
		if (egressInterval < 0)
		{
			int eventIndex = tokens[0].getIntValue();
			String error("Negative AVTP egress interval ");
			error += String(egressInterval) + " for streamID " + String::toHexString(stream.streamID) + ", event " + String(eventIndex) + newLine + newLine;
			logFile.appendText(error);
		}
		else if (egressInterval > stream.maxReferenceInterval)
		{
			int eventIndex = tokens[0].getIntValue();
			String line("New max egress interval ");
			line += String(egressInterval) + " for streamID " + String::toHexString(stream.streamID) + ", event " + String(eventIndex) + newLine + newLine;
			logFile.appendText(line);

			stream.maxReferenceInterval = egressInterval;
		}

		if (eventInterval > stream.maxEventInterval)
		{
			int eventIndex = tokens[0].getIntValue();
			String line("New max event interval ");
			line += String(eventInterval) + " for streamID " + String::toHexString(stream.streamID) + ", event " + String(eventIndex) + newLine + newLine;
			logFile.appendText(line);

			stream.maxEventInterval = eventInterval;
		}
	}

	stream.previousReferenceTime = egress;
	stream.previousEventSeconds = eventSeconds;
	stream.previousOK = true;
}

StreamManager::Stream& StreamManager::findTalkerStream(int64 streamID)
{
	for (int i = 0; i < talkerStreams.size(); ++i)
	{
		if (streamID == talkerStreams[i].streamID)
			return talkerStreams.getReference(i);
	}

	Stream stream;
	stream.streamID = streamID;
	talkerStreams.add(stream);

	return talkerStreams.getReference( talkerStreams.size() - 1);
}

StreamManager::Stream& StreamManager::findListenerStream(int64 streamID)
{
	for (int i = 0; i < listenerStreams.size(); ++i)
	{
		if (streamID == listenerStreams[i].streamID)
			return listenerStreams.getReference(i);
	}

	Stream stream;
	stream.streamID = streamID;
	listenerStreams.add(stream);

	return listenerStreams.getReference(listenerStreams.size() - 1);
}

void StreamManager::handleAVTPReceive(StringArray & tokens, File logFile)
{
	int64 streamID = tokens[4].getHexValue64();
	Stream& stream(findTalkerStream(streamID));

	int32 ingress = tokens[7].getLastCharacters(8).getHexValue32();
	if (stream.previousOK)
	{
		int32 ingressInterval = ingress - (int32)stream.previousReferenceTime;

		if (ingressInterval < 0)
		{
			int eventIndex = tokens[0].getIntValue();
			String error("Negative AVTP ingress interval ");
			error += String(ingressInterval) + " for streamID " + String::toHexString(stream.streamID) + ", event " + String(eventIndex) + ", ingress time " + String::toHexString(ingress) + newLine + newLine;
			logFile.appendText(error);
		}
		else if (ingressInterval > stream.maxReferenceInterval)
		{
			int eventIndex = tokens[0].getIntValue();
			String line("New max ingress interval ");
			line += String(ingressInterval) + " for streamID " + String::toHexString(stream.streamID) + ", event " + String(eventIndex) + ", ingress time " + String::toHexString(ingress) + newLine + newLine;
			logFile.appendText(line);

			jassert(ingressInterval < 2000000);

			stream.maxReferenceInterval = ingressInterval;
		}
	}

	stream.previousReferenceTime = ingress;
	stream.previousOK = true;
}

StreamManager::Stream::Stream()
{
	maxReferenceInterval = 0;
	maxEventInterval = 0.0;
	previousOK = false;
}

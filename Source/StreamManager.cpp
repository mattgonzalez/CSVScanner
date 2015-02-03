#include "JuceHeader.h"
#include "StreamManager.h"

StreamManager::StreamManager()
{

}

StreamManager::~StreamManager()
{
	streams.clear();
}

void StreamManager::handleAVTPTransmit(StringArray & tokens, File &logFile)
{
	int64 streamID = tokens[4].getHexValue64();
	Stream& stream(findStream(streamID));

	uint64 egress = tokens[7].getLastCharacters(17).getHexValue64();
	if (stream.previousOK)
	{
		int64 egressInterval = egress - stream.previousEgressTime;
		
		if (egressInterval < 0)
		{
			int eventIndex = tokens[0].getIntValue();
			String error("Negative AVTP egress interval ");
			error += String(egressInterval) + " for streamID " + String(stream.streamID) + ", event " + String(eventIndex) + newLine + newLine;
			logFile.appendText(error);
		}
		else if (egressInterval > stream.maxEgressInterval)
		{
			int eventIndex = tokens[0].getIntValue();
			String line("New max egress interval ");
			line += String(egressInterval) + " for streamID " + String(stream.streamID) + ", event " + String(eventIndex) + newLine + newLine;
			logFile.appendText(line);

			stream.maxEgressInterval = egressInterval;
		}
	}

	stream.previousEgressTime = egress;
	stream.previousOK = true;
}

StreamManager::Stream& StreamManager::findStream(uint64 streamID)
{
	for (int i = 0; i < streams.size(); ++i)
	{
		if (streamID == streams[i].streamID)
			return streams.getReference(i);
	}

	Stream stream;
	stream.streamID = streamID;
	streams.add(stream);

	return streams.getReference( streams.size() - 1);
}

StreamManager::Stream::Stream()
{
	maxEgressInterval = 0;
	previousOK = false;
}

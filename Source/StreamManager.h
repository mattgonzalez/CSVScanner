#pragma once

class StreamManager
{
public:
	StreamManager();
	~StreamManager();

	void handleAVTPTransmit(StringArray & tokens, File &logFile);
	void handleAVTPReceive(StringArray & tokens, File logFile);

	struct Stream
	{
		Stream();

		int64 streamID;
		bool previousOK;
 		double previousEventSeconds;
// 		int8 previousSequenceNum;
// 		uint64 previousPresentationTime;
		uint64 previousReferenceTime;

		int64 maxReferenceInterval;
		double maxEventInterval;
	};

	Array<Stream> talkerStreams;
	Array<Stream> listenerStreams;

	Stream& findTalkerStream(int64 streamID);
	Stream& findListenerStream(int64 streamID);

	JUCE_LEAK_DETECTOR(StreamManager);
};


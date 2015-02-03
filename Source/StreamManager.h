#pragma once

class StreamManager
{
public:
	StreamManager();
	~StreamManager();

	void handleAVTPTransmit(StringArray & tokens, File &logFile);

	struct Stream
	{
		Stream();

		uint64 streamID;
		bool previousOK;
		double previousEventSeconds;
		int8 previousSequenceNum;
		uint64 previousPresentationTime;
		uint64 previousEgressTime;

		int64 maxEgressInterval;
	};

	Array<Stream> streams;
	Stream& findStream(uint64 streamID);

	JUCE_LEAK_DETECTOR(StreamManager);
};


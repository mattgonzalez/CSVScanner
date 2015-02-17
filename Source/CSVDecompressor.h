#pragma once

class CSVDecompressor : public ThreadWithProgressWindow
{
public:
	CSVDecompressor();

	Result decompress();

	File decompressedFile;

protected:
	virtual void run();

	File gzipFile;
	ScopedPointer<FileInputStream> gzipFileInputStream;
	Result result;

	void decompressToCSV();

	enum 
	{
		MEGA_BYTE = 1024 * 1024
	};

	JUCE_LEAK_DETECTOR(CSVDecompressor);
};


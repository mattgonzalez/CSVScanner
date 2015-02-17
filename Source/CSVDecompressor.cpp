#include "JuceHeader.h"
#include "CSVDecompressor.h"

CSVDecompressor::CSVDecompressor() :
result(Result::ok()),
ThreadWithProgressWindow("CSV Decompressor",true,true)
{
	
}

Result CSVDecompressor::decompress()
{
	File folder(File::getCurrentWorkingDirectory());
	FileChooser fc("Select the compressed log file...",
		File::getCurrentWorkingDirectory(),
		"*.gzip");

	if (false == fc.browseForFileToOpen())
	{
		return Result::fail(String::empty);
	}

	gzipFile = fc.getResult();
	gzipFileInputStream = new FileInputStream(gzipFile);
	if (false == gzipFileInputStream->openedOk())
	{
		return Result::fail("Could not open the specified file, quitting!");
	}

	if (runThread())
	{
		return result;
	}

	return Result::fail("User canceled");
}

void CSVDecompressor::run()
{
	int64 bytes = gzipFile.getSize();
	int64 remaining = bytes;
#ifdef _WIN64
	int bufferSize = 1024 * MEGA_BYTE;
#else
	int bufferSize = 128 * MEGA_BYTE;
#endif
	BufferedInputStream bufferedGzipFileInputStream(gzipFileInputStream, bufferSize, false);
	ScopedPointer<GZIPDecompressorInputStream> decompressorInputStream = new GZIPDecompressorInputStream(bufferedGzipFileInputStream);

	File outputFolder(gzipFile.getParentDirectory());
	String filename(gzipFile.getFileNameWithoutExtension());
	decompressedFile = outputFolder.getChildFile(filename).withFileExtension(".csv");
	if (decompressedFile.existsAsFile())
	{
		decompressedFile.deleteFile();
	}
	FileOutputStream outputStream(decompressedFile, bufferSize);

	while (remaining > 0)
	{
		int64 bytesWritten = outputStream.writeFromInputStream(*decompressorInputStream, bufferSize);
		if (0 == bytesWritten)
		{
			result = Result::fail("Unable to write - check disk space");
			return;
		}

		remaining -= bytesWritten;
		int64 progress = bytes - remaining;
		setProgress(double(progress) / bytes);
	}
}

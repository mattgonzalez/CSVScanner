#include <windows.h>
#include "base.h"
#include "BinaryScanner.h"

struct EventInfo
{
	int code;
	char * name;
	uint32 colour;
	char * prefixes[EVENT_LOG_DATA_VALUES];
	int8 radix[EVENT_LOG_DATA_VALUES];
	uint8 type;
};

EventInfo const eventInfoList[NUM_STREAMWARE_EVENTS] =
{
#define STREAMWARE_EVENT( code, name, colour, prefix0, prefix1, prefix2, prefix3, radix0, radix1, radix2, radix3, type)	\
	{ code, name, colour, {prefix0, prefix1, prefix2, prefix3}, {radix0, radix1, radix2, radix3}, type},
	STREAMWARE_EVENT_LIST
#undef STREAMWARE_EVENT
};

BinaryScanner::BinaryScanner(String filename) :
result(Result::ok()),
binaryFile(File::getCurrentWorkingDirectory().getChildFile(filename)),
binaryInputStream(binaryFile),
comma(","),
ThreadWithProgressWindow("Binary Scanner", true, true)
{
}

Result BinaryScanner::scan()
{
	File outputFolder(File::getCurrentWorkingDirectory());
	//outputFile = File(outputFolder.getChildFile(binaryFile.getFileNameWithoutExtension() + ".out.txt"));
	outputFile = File("d:/bose.csv");

	if (false == binaryInputStream.openedOk())
	{
		return Result::fail("Could not open the specified binary file, quitting!");
	}

	if (outputFile.existsAsFile())
	{
		outputFile.deleteFile();
		outputFile.create();
	}

	if (runThread())
	{
		return result;
	}

	return Result::ok();
}

void BinaryScanner::run()
{
	int64 bytes = binaryFile.getSize();
	int64 remaining = bytes;
#ifdef _WIN64
	BufferedInputStream bufferedInputStream(binaryInputStream, 1024 * MEGA_BYTE);
#else
	BufferedInputStream bufferedInputStream(binaryInputStream, 512 * MEGA_BYTE);
#endif
	FileOutputStream outputStream(outputFile);

	EventLogEntry entry;
	String line;
	while (false == bufferedInputStream.isExhausted())
	{
		if (threadShouldExit())
		{
			result = Result::fail("User canceled");
			break;
		}

		int bytesRead = bufferedInputStream.read(&entry, sizeof(entry));
		if (bytesRead != sizeof(entry))
			break;

		parseEntry(entry, line, outputStream);
		if (line.isEmpty())
			break;

		remaining -= bytesRead;
		int64 progress = bytes - remaining;
		setProgress(double(progress) / bytes);
	}
}

void BinaryScanner::parseEntry(EventLogEntry const &entry, String &line, FileOutputStream &outputStream)
{
	uint32 code = entry.code;

	if (INVALID_EVENT_CODE == code || code >= NUM_STREAMWARE_EVENTS)
	{
		line = String::empty;
		return;
	}

	line = String(entry.index) + comma;
	const uint64 freq = 1852220;
	line += String( double(entry.time) / freq, 6) + comma;
	line += String(entry.elapsed) + comma;
	line += String(eventInfoList[code].name) + comma;
	getEventText(entry, line);
	line += newLine;
	outputStream.writeText(line, false, false);
}

void BinaryScanner::getEventText(EventLogEntry const &entry, String &text)
{
	for (int i = 0; i < EVENT_LOG_DATA_VALUES; i++)
	{
		if (eventInfoList[entry.code].prefixes[i] == nullptr)
		{
			break;
		}

		text += eventInfoList[entry.code].prefixes[i];
		switch (eventInfoList[entry.code].radix[i])
		{
		case 10:
			{
				text += String((int64)entry.u.data[i]);
				break;
			}
		case 16:
			{
				LARGE_INTEGER n;

				n.QuadPart = entry.u.data[i];
				text += "0x";
				if (n.HighPart != 0)
				{
					text += String::formatted("%x.%08x", n.HighPart, n.LowPart);
				}
				else
				{
					text += String::toHexString((int32)n.LowPart);
				}
				break;
			}
		}

		if (i < EVENT_LOG_DATA_VALUES - 1)
			text += comma;
	}
}

/*
==============================================================================

Copyright (C) 2013 Echo Digital Audio Corporation.
This source code is considered to be proprietary and confidential information.

==============================================================================
*/
#pragma once

typedef struct
{
	uint64 field;
	uint64 value;
} ReceiveErrorData;

typedef struct
{
	uint64 message;
	uint64 field;
	uint64 value;
} ReceiveParameterData;

typedef struct
{
	uint64 grandmaster_identity;
}PTPGMData;

typedef struct
{
	uint64 avtp_timestamp;
	uint64 reference32;
}AVTPData;

typedef struct
{
	uint64 guid;
}ADPData;

typedef struct
{
	uint64 reference_64;
}PTPTimeStampData;

#define EVENT_LOG_DATA_VALUES 4
typedef union
{
	ReceiveParameterData receive_parameter_error;
	ReceiveErrorData receive_error;
	PTPGMData ptp_gm_data;
	AVTPData avtp_data;
	PTPTimeStampData ptp_time_stamp_data;
	ADPData adp_receive;
	uint64 data[EVENT_LOG_DATA_VALUES];
} EventLogData;

typedef struct
{
	uint64 time;
	uint32 code;
	uint32 index;
	int32 elapsed;
	uint32 reserved;
	EventLogData u;
} EventLogEntry;

enum
{
	AVTP_INVALID_SIZE,
	AVTP_INVALID_SV,
	AVTP_INVALID_VERSION,
	AVTP_INVALID_SUBTYPE
};

enum
{
	MAAP_INVALID_DESTINATION,
	MAAP_INVALID_SIZE,
	MAAP_INVALID_MESSAGE_TYPE,
	MAAP_INVALID_MAAP_VERSION,
	MAAP_INVALID_DATA_LENGTH,
	MAAP_INVALID_STREAM_ID,
	MAAP_INVALID_REQUESTED_START_ADDRESS,
	MAAP_INVALID_REQUESTED_COUNT,
	MAAP_INVALID_CONFLICT_START_ADDRESS,
	MAAP_INVALID_CONFLICT_COUNT
};

enum
{
	ADP_INVALID_DESTINATION,
	ADP_INVALID_SIZE,
	ADP_INVALID_MESSAGE_TYPE,
	ADP_INVALID_CONTROL_DATA_LENGTH
};

enum
{
	ACMP_INVALID_DESTINATION,
	ACMP_INVALID_SIZE,
	ACMP_INVALID_MESSAGE_TYPE,
	ACMP_INVALID_CONTROL_DATA_LENGTH,
	ACMP_INVALID_CONTROLLER_GUID,
	ACMP_INVALID_TALKER_GUID,
	ACMP_INVALID_LISTENER_GUID
};

enum
{
	EVENT_LOG_NUM_ENTRIES = 32768 * 16,
	EVENT_LOG_NUM_ENTRIES_MASK = EVENT_LOG_NUM_ENTRIES - 1
};
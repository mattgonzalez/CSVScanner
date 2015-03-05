#pragma once

enum
{
	INVALID_BASE = 0x0,
	PTP_BASE = 0x1,
	AVTP_BASE = 0x2,
	MSRP_BASE = 0x3,
	MVRP_BASE = 0x4,
	MRP_BASE = 0x5,
	MAAP_BASE = 0x6,
	ADP_BASE = 0x7,
	ACMP_BASE = 0x8,
	AECP_BASE = 0x9,
	LOG_ENGINE_BASE = 0xa,
	SEND_REC_BASE = 0xb,
	ASIO_BASE = 0xc,
	METRICS_BASE = 0xd,
	FAULT_INJECTION_BASE,
	FAULT_DETECTION_BASE,
	DEBUG_BASE,
	LINK_BASE
};

//
// This is a macro that is used in EventListComponent.cpp to make it easier to change the information displayed in the log section of the controller.
// Each column is as follows:
//
// The first column is the event code that is being sent or received.
// The second column is the same thing in a more readable format, or the event name.
// The third column is what color the row will show up as in the event log. Useful for making it easy to spot specific event types.
// The columns 4-7 are used to create strings for the names of up to four pieces of data that are being logged in relation to the event.
// The columns 8-11 are used to specify what number base the data being logged is in.
// The final column is used to specify what type of event it is within several defined groups.
//
// For columns 4-7, if there are less than four pieces of data being logged, nullptr is used instead.
// The same goes for columns 8-11, but with 0 instead of nullptr.
//
#define STREAMWARE_EVENT_LIST \
	STREAMWARE_EVENT(	INVALID_EVENT_CODE,	"Invalid Event Code",	0xffffffff,	nullptr,	nullptr,	nullptr,	nullptr,	0,	0,	0,	0,	INVALID_BASE)\
	STREAMWARE_EVENT(	PTP_RECEIVE_SYNC,	"PTP receive sync",	0xffffffff,	"Ingress:",	"   sequenceID:",	nullptr,	nullptr,	16,	10,	0,	0,	PTP_BASE)\
	STREAMWARE_EVENT(	PTP_RECEIVE_FOLLOW_UP,	"PTP receive follow up",	0xffffffff,	"Ingress:",	"   Seconds:",	"   Nanoseconds:",	"   sequenceID:",	16,	10,	10,	10,	PTP_BASE)\
	STREAMWARE_EVENT( 	PTP_RECEIVE_DELAY_REQUEST,	"PTP receive delay request",	0xffffffff,	"sequenceID:",	nullptr,	nullptr,	nullptr,	10,	0,	0,	0,	PTP_BASE)\
	STREAMWARE_EVENT( 	PTP_RECEIVE_DELAY_RESPONSE,	"PTP receive delay response",	0xffffffff,	"sequenceID:",	nullptr,	nullptr,	nullptr,	10,	0,	0,	0,	PTP_BASE)\
	STREAMWARE_EVENT( 	PTP_RECEIVE_DELAY_FOLLOW_UP,	"PTP receive delay follow-up",	0xffffffff,	"sequenceID:",	nullptr,	nullptr,	nullptr,	10,	0,	0,	0,	PTP_BASE)\
	STREAMWARE_EVENT( 	PTP_RECEIVE_SIGNALING,	"PTP receive signaling",	0x40ff0dff,	"linkDelayInterval:", "timeSyncInterval:",	nullptr,	nullptr,	10, 10,	0,	0,	PTP_BASE)\
	STREAMWARE_EVENT( 	PTP_SEND_DELAY_REQUEST,	"PTP transmit delay request",	0xffffffff,	"sequenceID:",	nullptr,	nullptr,	nullptr,	10,	0,	0,	0,	PTP_BASE)\
	STREAMWARE_EVENT( 	PTP_SEND_DELAY_RESPONSE,	"PTP transmit delay response",	0xffffffff,	"sequenceID:",	nullptr,	nullptr,	nullptr,	10,	0,	0,	0,	PTP_BASE)\
	STREAMWARE_EVENT( 	PTP_SEND_DELAY_FOLLOW_UP,	"PTP transmit delay follow-up",	0xffffffff,	"Egress:",	" sequenceID:",	nullptr,	nullptr,	16,	10,	0,	0,	PTP_BASE)\
	STREAMWARE_EVENT( 	PTP_SEND_SYNC,	"PTP transmit sync",	0xffffffff, "sequenceID:",	nullptr,	nullptr,	nullptr,	10,	0,	0,	0,	PTP_BASE)\
	STREAMWARE_EVENT( 	PTP_SEND_FOLLOW_UP,	"PTP transmit follow up",	0xffffffff,	"sequenceID:", "   Egress:",	"   Seconds:",	"   Nanoseconds:",	10, 16,	10,	10,	PTP_BASE)\
	STREAMWARE_EVENT( 	PTP_SEND_SIGNALING,	"PTP transmit signaling message",	0x40ff0dff,	"linkDelayInterval:", " timeSyncInterval:",	nullptr,	nullptr,	10, 10,	0,	0,	PTP_BASE)\
	STREAMWARE_EVENT( 	PTP_DISCONTINUITY,	"PTP discontinuity",	0xffffffff,	"Delta:",	"  ->",	" ",	nullptr,	0,	0,	0,	0,	PTP_BASE)\
	STREAMWARE_EVENT( 	PTP_GRANDMASTER_CHANGE,	"PTP grandmaster change",	0xffffffff,	"Clock Identity:",	nullptr,	nullptr,	nullptr,	16,	0,	0,	0,	PTP_BASE)\
	STREAMWARE_EVENT( 	PTP_NOT_LOCKED,	"PTP not locked",	0xffffffff,	nullptr,	nullptr,	nullptr,	nullptr,	0,	0,	0,	0,	PTP_BASE)\
	STREAMWARE_EVENT( 	PTP_SYNCED,	"PTP synced",	0xffffffff,	nullptr,	nullptr,	nullptr,	nullptr,	0,	0,	0,	0,	PTP_BASE)\
	STREAMWARE_EVENT( 	PTP_SYNC_TIMEOUT,	"PTP sync timeout",	0x80ff0000,	nullptr,	nullptr,	nullptr,	nullptr,	0,	0,	0,	0,	PTP_BASE)\
	STREAMWARE_EVENT( 	PTP_GM_TIMER,	"PTP GM timer",	0x88888888,	nullptr,	nullptr,	nullptr,	nullptr,	0,	0,	0,	0,	PTP_BASE)\
	STREAMWARE_EVENT( 	PTP_ERROR,	"PTP error",	0xc0ff0000,	"Reference:",	" GMNanoseconds:",	" Engine Reference:",	" Engine GMNanoseconds:",	16,	16,	16,	16,	PTP_BASE)\
	STREAMWARE_EVENT( 	PTP_ERROR2,	"PTP error 2",	0xc0ff0000,	"",	" ",	" ",	" ",	10,	10,	10,	10,	PTP_BASE)\
	STREAMWARE_EVENT( 	PTP_RESET,	"PTP reset",	0xffffffff,	nullptr,	nullptr,	nullptr,	nullptr,	0,	0,	0,	0,	PTP_BASE)\
	STREAMWARE_EVENT( 	PTP_TRANSMIT_ERROR,	"PTP transmit error",	0xc0ff0000,	"code:",	nullptr,	nullptr,	nullptr,	10,	0,	0,	0,	PTP_BASE)\
	STREAMWARE_EVENT( 	PTP_DELAY_REQUEST_SENT,	"PTP delay request sent",	0x60000060,	"sequenceID:",	nullptr,	nullptr,	nullptr,	16,	0,	0,	0,	PTP_BASE)\
	STREAMWARE_EVENT( 	PTP_DUPLICATE_EGRESS_TIME,	"PTP duplicate egress",	0x20202000,	"Time:",	nullptr,	nullptr,	nullptr,	16,	0,	0,	0,	PTP_BASE)\
	STREAMWARE_EVENT( 	PTP_RATIO,	"PTP ratio",	0xffffffff,	"referenceDifference64:",	" gmNanosecondsModDifference6:",	" ratio:",	" averageRatio:",	10,	10,	16,	16,	PTP_BASE)\
	STREAMWARE_EVENT( 	PTP_SYNC_FAULT_INJECTION,	"PTP sync fault injection",	0xffffffff,	"sequenceID:",	nullptr,	nullptr,	nullptr,	10,	0,	0,	0,	PTP_BASE)\
	STREAMWARE_EVENT( 	PTP_FOLLOWUP_FAULT_INJECTION,	"PTP followup fault injection",	0xffffffff,	"sequenceID:",	nullptr,	nullptr,	nullptr,	10,	0,	0,	0,	PTP_BASE)\
	STREAMWARE_EVENT( 	PTP_DEBUG,	"Debug",	0x80FF1100,	" ",	"   ",	"   ",	"  ",	10,	10, 10, 10, PTP_BASE) \
	STREAMWARE_EVENT(	AVTP_TRANSMIT,	"AVTP transmit",	0xffffffff,	"stream_id:",	"   sequence_num:", "   avtp_timestamp:",	"   egress:",	16,	10,	16,	16,	AVTP_BASE)\
	STREAMWARE_EVENT(	AVTP_TRANSMIT_ERROR,	"AVTP transmit error",	0xffffffff,	"stream_id:",	"   avtp_timestamp:",	"   egress:", "   error:",	16,	16,	16,	16,	AVTP_BASE)\
	STREAMWARE_EVENT(	AVTP_TRANSMIT_CONVERT,	"AVTP transmit convert",	0xffffffff,	nullptr,	nullptr,	nullptr,	nullptr,	0,	0,	0,	0,	AVTP_BASE)\
	STREAMWARE_EVENT( 	AVTP_TRANSMIT_SEND_COMPLETE,	"AVTP transmit send complete",	0xffffffff,	"index:",	" stream_id:",	" avtp_timestamp:",	" status:",	10,	16,	16,	16,	AVTP_BASE)\
	STREAMWARE_EVENT( 	AVTP_TRANSMIT_START,	"AVTP transmit start",	0x403eff36,	"stream_id:",	nullptr,	nullptr,	nullptr,	16,	0,	0,	0,	AVTP_BASE)\
	STREAMWARE_EVENT( 	AVTP_LAUNCH_TIME_ERROR,	"AVTP launch time error",	0xffffffff,	nullptr,	nullptr,	nullptr,	nullptr,	0,	0,	0,	0,	AVTP_BASE)\
	STREAMWARE_EVENT( 	AVTP_RECEIVE_ERROR,	"AVTP receive error",	0xffffffff,	nullptr,	nullptr,	nullptr,	nullptr,	0,	0,	0,	0,	AVTP_BASE)\
	STREAMWARE_EVENT( 	AVTP_RECEIVE,	"AVTP receive",	0x400000ff,	"stream_id:",	"   sequence_num:", "   avtp_timestamp:",	"   ingress:",	16,	10,	16,	16,	AVTP_BASE)\
	STREAMWARE_EVENT( 	AVTP_RECEIVE_CALLBACK,	"AVTP receive callback",	0x400000e0,	"stream_id:",	"   avtp_timestamp:", "   sequence_id:",	" ingress:",	16,	16,	10,	16,	AVTP_BASE)\
	STREAMWARE_EVENT( 	AVTP_RENDER_FILL,	"AVTP render fill",	0xffffffff,	"BufferPosition:",	" presentationTime:",	" startTime:",	" bufferStartPos:",	10,	16,	16,	10,	AVTP_BASE)\
	STREAMWARE_EVENT( 	AVTP_CAPTURE_FILL,	"AVTP capture fill",	0xffffffff,	nullptr,	nullptr,	nullptr,	nullptr,	0,	0,	0,	0,	AVTP_BASE)\
	STREAMWARE_EVENT( 	AVTP_RECEIVE_TIMESTAMP,	"AVTP receive timestamp",	0xffffffff,	"Diff:",	" curr:",	" next:",	" limit:",	10,	10,	10,	10,	AVTP_BASE)\
	STREAMWARE_EVENT( 	AVTP_RENDER_FILL_ERROR,	"AVTP render fill error",	0xffffffff,	"Code:",	"",	"",	"",	10,	10,	10,	10,	AVTP_BASE)\
	STREAMWARE_EVENT( 	AVTP_CAPTURE_FILL_ERROR,	"AVTP capture fill error",	0xffffffff,	"Code:",	"",	"",	"",	10,	10,	10,	10,	AVTP_BASE)\
	STREAMWARE_EVENT( 	AVTP_SYNC,	"AVTP sync",	0x80ffff00,	"DataBlocksDifference:",	" DatablocksOffset:",	" TimeOffset:", " CurrentGMLaunchTime:",	16,	16,	10,	16,	AVTP_BASE)\
	STREAMWARE_EVENT( 	AVTP_DISCARD,	"AVTP discard",	0xffffffff,	"Packets:",	" Data blocks:",	" Presentation Time:",	" ",	10,	10,	16,	10,	AVTP_BASE)\
	STREAMWARE_EVENT( 	AVTP_ADJUST,	"AVTP adjust",	0xffffffff,	"",	", ",	", ",	", ",	10,	16,	16,	10,	AVTP_BASE)\
	STREAMWARE_EVENT( 	AVTP_ERROR,	"AVTP error",	0xffffffff,	"Sequence gap:",	" Stream ID:",	" ",	" ",	10,	16,	10,	10,	AVTP_BASE)\
	STREAMWARE_EVENT( 	AVTP_CLONE,	"AVTP clone",	0xffffffff,	"",	" ",	" ",	" ",	16,	16,	16,	16,	AVTP_BASE)\
	STREAMWARE_EVENT( 	AVTP_ADD,	"AVTP add",	0xffffffff,	"",	" ",	" ",	" ",	16,	16,	16,	16,	AVTP_BASE)\
	STREAMWARE_EVENT( 	AVTP_DEBUG1,"AVTP Debug 1",	0x80FF1100,	" ",	"   ",	"   ",	"  ",	16,	16, 16, 16, AVTP_BASE) \
	STREAMWARE_EVENT( 	AVTP_DEBUG2,"AVTP Debug 2",	0x80FFEB11,	" ",	"   ",	"   ",	"  ",	16,	16, 16, 10, AVTP_BASE) \
	STREAMWARE_EVENT( 	AVTP_DEBUG3,"AVTP Debug 3",	0x80FF1100,	" ",	"   ",	"   ",	"  ",	16,	16, 10, 10, AVTP_BASE) \
	STREAMWARE_EVENT( 	MSRP_INDICATION_NEW,	"MSRP indication new",	0xffffffff,	"Type:",	" Listener:",	" Stream ID:",	nullptr,	10,	10,	16,	0,	MSRP_BASE)\
	STREAMWARE_EVENT( 	MSRP_INDICATION_JOIN,	"MSRP indication join",	0xffffffff,	"Type:",	" Listener:",	" Stream ID:",	nullptr,	10,	10,	16,	0,	MSRP_BASE)\
	STREAMWARE_EVENT( 	MSRP_INDICATION_LEAVE,	"MSRP indication leave",	0xffffffff,	"Type:",	" Listener:",	" Stream ID:",	nullptr,	10,	10,	16,	0,	MSRP_BASE)\
	STREAMWARE_EVENT( 	MSRP_REQUEST_NEW,	"MSRP request new",	0xffffffff,	"Type:",	" Listener:",	" Stream ID:",	nullptr,	10,	10,	16,	0,	MSRP_BASE)\
	STREAMWARE_EVENT( 	MSRP_REQUEST_JOIN,	"MSRP request join",	0xffffffff,	"Type:",	" Listener:",	" Stream ID:",	nullptr,	10,	10,	16,	0,	MSRP_BASE)\
	STREAMWARE_EVENT( 	MSRP_REQUEST_LEAVE,	"MSRP request leave",	0xffffffff,	"Type:",	" Listener:",	" Stream ID:",	nullptr,	10,	10,	16,	0,	MSRP_BASE)\
	STREAMWARE_EVENT( 	MVRP_INDICATION_NEW,	"MVRP indication new",	0xffffffff,	nullptr,	nullptr,	nullptr,	nullptr,	0,	0,	0,	0,	MVRP_BASE)\
	STREAMWARE_EVENT(	MVRP_INDICATION_JOIN,	"MVRP indication join",	0xffffffff,	nullptr,	nullptr,	nullptr,	nullptr,	0,	0,	0,	0,	MVRP_BASE)\
	STREAMWARE_EVENT(	MVRP_INDICATION_LEAVE,	"MVRP indication leave",	0xffffffff,	nullptr,	nullptr,	nullptr,	nullptr,	0,	0,	0,	0,	MVRP_BASE)\
	STREAMWARE_EVENT( 	MVRP_REQUEST_NEW,	"MVRP request new",	0xffffffff,	nullptr,	nullptr,	nullptr,	nullptr,	0,	0,	0,	0,	MVRP_BASE)\
	STREAMWARE_EVENT( 	MVRP_REQUEST_JOIN,	"MVRP request join",	0xffffffff,	nullptr,	nullptr,	nullptr,	nullptr,	0,	0,	0,	0,	MVRP_BASE)\
	STREAMWARE_EVENT( 	MVRP_REQUEST_LEAVE,	"MVRP request leave",	0xffffffff,	nullptr,	nullptr,	nullptr,	nullptr,	0,	0,	0,	0,	MVRP_BASE)\
	STREAMWARE_EVENT( 	MRP_RECEIVE_EVENT,	"MRP receive event",	0xffffffff,	"Ether Type:",	" Type:",	"-",	" Event:",	16,	10,	16,	10,	MRP_BASE)\
	STREAMWARE_EVENT( 	MRP_RECEIVE_LEAVE_ALL,	"MRP receive leave all",	0xffffffff,	"Ether Type:",	" Type:",	nullptr,	nullptr,	16,	10,	0,	0,	MRP_BASE)\
	STREAMWARE_EVENT( 	MRP_SEND_LEAVE_ALL,	"MRP send leave all",	0xffffffff,	"Ether Type:",	" Type:",	"-",	nullptr,	16,	10,	16,	0,	MRP_BASE)\
	STREAMWARE_EVENT( 	MRP_RECEIVE_MESSAGE,	"MRP receive message",	0xffffffff,	" Type:",	" Listener:",	"-",	nullptr,	10,	10,	16,	0,	MRP_BASE)\
	STREAMWARE_EVENT( 	MRP_REGISTRAR_TIMER_STATE_LV,	"MRP registrar timer LV",	0xffffffff,	"Ether Type:",	" Type:",	"-",	nullptr,	16,	10,	16,	0,	MRP_BASE)\
	STREAMWARE_EVENT( 	MRP_REGISTRAR_RLV,	"MRP registrar rLV",	0xffffffff,	"Ether Type:",	" Type:",	"-",	nullptr,	16,	10,	16,	0,	MRP_BASE)\
	STREAMWARE_EVENT( 	MRP_REGISTRAR_RLA,	"MRP registrar rLA",	0xffffffff,	"Ether Type:",	" Type:",	"-",	nullptr,	16,	10,	16,	0,	MRP_BASE)\
	STREAMWARE_EVENT( 	MRP_REGISTRAR_TXLA,	"MRP registrar txLA",	0xffffffff,	"Ether Type:",	" Type:",	"-",	nullptr,	16,	10,	16,	0,	MRP_BASE)\
	STREAMWARE_EVENT( 	MRP_REGISTRAR_TIMER_START,	"MRP registrar timer start",	0xffffffff,	"Ether Type:",	" Type:",	"-",	" Msec:",	16,	10,	16,	10,	MRP_BASE)\
	STREAMWARE_EVENT( 	MRP_ADD_MESSAGE,	"MRP add message",	0xffffffff,	"Ether Type:",	" Type:",	"-",	" Event:",	16,	10,	16,	10,	MRP_BASE)\
	STREAMWARE_EVENT( 	MRP_APPLICANT_STATE,	"MRP applicant state",	0xffffffff,	"Ether Type:",	" Type:",	"-",	"  ",	16,	10,	16,	10,	MRP_BASE)\
	STREAMWARE_EVENT( 	MRP_REGISTRAR_STATE,	"MRP registrar state",	0xffffffff,	"Ether Type:",	" Type:",	"-",	"  ",	16,	10,	16,	10,	MRP_BASE)\
	STREAMWARE_EVENT(	MAAP_RECEIVE_PROBE,	"MAAP receive probe",	0xffffffff,	"Requested Start Address:",	"  Requested Count:",	nullptr,	nullptr,	0,	0,	0,	0,	MAAP_BASE)\
	STREAMWARE_EVENT(	MAAP_RECEIVE_DEFEND,	"MAAP receive defend",	0xffffffff,	"Requested Start Address:",	"  Requested Count:",	" Conflict Start Address:",	" Conflict Count:",	0,	0,	0,	0,	MAAP_BASE)\
	STREAMWARE_EVENT( 	MAAP_RECEIVE_ANNOUNCE,	"MAAP receive announce",	0xffffffff,	"Requested Start Address:",	"  Requested Count:",	nullptr,	nullptr,	0,	0,	0,	0,	MAAP_BASE)\
	STREAMWARE_EVENT( 	MAAP_TRANSMIT_PROBE,	"MAAP transmit probe",	0xffffffff,	"Requested Start Address:",	"  Requested Count:",	nullptr,	nullptr,	0,	0,	0,	0,	MAAP_BASE)\
	STREAMWARE_EVENT( 	MAAP_TRANSMIT_DEFEND,	"MAAP transmit defend",	0xffffffff,	"Requested Start Address:",	"  Requested Count:",	" Conflict Start Address:",	" Conflict Count:",	0,	0,	0,	0,	MAAP_BASE)\
	STREAMWARE_EVENT( 	MAAP_TRANSMIT_ANNOUNCE,	"MAAP transmit announce",	0xffffffff,	"Requested Start Address:",	"  Requested Count:",	nullptr,	nullptr,	0,	0,	0,	0,	MAAP_BASE)\
	STREAMWARE_EVENT( 	MAAP_TIMER,	"MAAP timer",	0xffffffff,	"Elapsed Msec:",	nullptr,	nullptr,	nullptr,	10,	0,	0,	0,	MAAP_BASE)\
	STREAMWARE_EVENT( 	MAAP_RECEIVE_ERROR,	"MAAP receive error",	0xffffffff,	nullptr,	nullptr,	nullptr,	nullptr,	0,	0,	0,	0,	MAAP_BASE)\
	STREAMWARE_EVENT( 	MAAP_RECEIVE_PARAMETER_ERROR,	"MAAP receive parameter error",	0xffffffff,	nullptr,	nullptr,	nullptr,	nullptr,	0,	0,	0,	0,	MAAP_BASE)\
	STREAMWARE_EVENT( 	ADP_RECEIVE_ENTITY_AVAILABLE,	"ADP receive entity available",	0xffffffff,	"Entity:",	nullptr,	nullptr,	nullptr,	16,	10,	10,	10,	ADP_BASE)\
	STREAMWARE_EVENT( 	ADP_RECEIVE_ERROR,	"ADP receive error",	0xffffffff,	nullptr,	nullptr,	nullptr,	nullptr,	0,	0,	0,	0,	ADP_BASE)\
	STREAMWARE_EVENT( 	ACMP_SEND,	"ACMP send",	0xffffffff,	"Command:",	" Stream ID:",	" Status:",	" Sequence:",	10,	16,	10,	16,	ACMP_BASE)\
	STREAMWARE_EVENT( 	ACMP_RECEIVE,	"ACMP receive",	0xffffffff,	"Command:",	" Stream ID:",	" Status:",	" Sequence:",	10,	16,	10,	16,	ACMP_BASE)\
	STREAMWARE_EVENT( 	ACMP_RECEIVE_UNSUPPORTED_COMMAND,	"ACMP receive unsupported command",	0xffffffff,	"Command:",	nullptr,	nullptr,	nullptr,	10,	0,	0,	0,	ACMP_BASE)\
	STREAMWARE_EVENT( 	ACMP_QUEUED,	"ACMP queued",	0xffffffff,	"Command:",	" Stream ID:",	" Status:",	" Sequence:",	10,	16,	10,	16,	ACMP_BASE)\
	STREAMWARE_EVENT( 	ACMP_DEQUEUED,	"ACMP dequeued",	0xffffffff,	"Command:",	" Stream ID:",	" Status:",	" Sequence:",	10,	16,	10,	16,	ACMP_BASE)\
	STREAMWARE_EVENT( 	ACMP_TRANSMITTED,	"ACMP transmitted",	0xffffffff,	"Command:",	" Stream ID:",	" Status:",	" Sequence:",	10,	16,	10,	16,	ACMP_BASE)\
	STREAMWARE_EVENT( 	ACMP_TIMEOUT,	"ACMP timeout",	0xffffffff,	"Command:",	" Sequence:",	" Retry:",	nullptr,	16,	16,	10,	0,	ACMP_BASE)\
	STREAMWARE_EVENT( 	ACMP_RECEIVE_ERROR,	"ACMP receive error",	0xffffffff,	nullptr,	nullptr,	nullptr,	nullptr,	0,	0,	0,	0,	ACMP_BASE)\
	STREAMWARE_EVENT( 	ACMP_RECEIVE_PARAMETER_ERROR,	"ACMP receive parameter error",	0xffffffff,	nullptr,	nullptr,	nullptr,	nullptr,	0,	0,	0,	0,	ACMP_BASE)\
	STREAMWARE_EVENT( 	AECP_SEND_COMMAND,	"AECP send command",	0xffffa07a,	"Command:",	"  Sequence:",	"  Status:",	nullptr,	10,	16,	10,	0,	AECP_BASE)\
	STREAMWARE_EVENT( 	AECP_SEND_RESPONSE,	"AECP send response",	0xffffffff,	"Command:",	"  Sequence:",	"  Status:",	nullptr,	10,	16,	10,	0,	AECP_BASE)\
	STREAMWARE_EVENT( 	AECP_RECEIVE_RESPONSE,	"AECP receive response",	0xffffffff,	"Command:",	"  Sequence:",	"  Status:",	nullptr,	10,	16,	10,	0,	AECP_BASE)\
	STREAMWARE_EVENT( 	AECP_RECEIVE_COMMAND,	"AECP receive command",	0xffffffff,	nullptr,	nullptr,	nullptr,	nullptr,	0,	0,	0,	0,	AECP_BASE)\
	STREAMWARE_EVENT( 	AECP_RECEIVE_UNSUPPORTED_COMMAND,	"AECP receive unsupported command",	0xffffffff,	"Command:",	nullptr,	nullptr,	nullptr,	10,	0,	0,	0,	AECP_BASE)\
	STREAMWARE_EVENT( 	AECP_TIMEOUT,	"AECP timeout",	0xffffffff,	"Command:",	" Sequence:",	" Retry:",	nullptr,	16,	16,	10,	0,	AECP_BASE)\
	STREAMWARE_EVENT( 	AECP_ENUMERATION_FAILED,	"AECP enumeration failed",	0xffffffff,	"Entity:",	nullptr,	nullptr,	nullptr,	16,	0,	0,	0,	AECP_BASE)\
	STREAMWARE_EVENT( 	LOG_ENGINE_ADD_STREAM,	"Engine add stream",	0xffffffff,	nullptr,	nullptr,	nullptr,	nullptr,	0,	0,	0,	0,	LOG_ENGINE_BASE)\
	STREAMWARE_EVENT( 	LOG_ENGINE_REMOVE_STREAM,	"Engine remove stream",	0xffffffff,	nullptr,	nullptr,	nullptr,	nullptr,	0,	0,	0,	0,	LOG_ENGINE_BASE)\
	STREAMWARE_EVENT( 	LOG_ENGINE_START_STREAM,	"Engine start stream",	0xffffffff,	nullptr,	nullptr,	nullptr,	nullptr,	0,	0,	0,	0,	LOG_ENGINE_BASE)\
	STREAMWARE_EVENT( 	LOG_ENGINE_STOP_STREAM,	"Engine stop stream",	0xffffffff,	nullptr,	nullptr,	nullptr,	nullptr,	0,	0,	0,	0,	LOG_ENGINE_BASE)\
	STREAMWARE_EVENT( 	LOG_ENGINE_ALLOCATE_STREAM,	"Engine allocate stream",	0xffffffff,	nullptr,	nullptr,	nullptr,	nullptr,	0,	0,	0,	0,	LOG_ENGINE_BASE)\
	STREAMWARE_EVENT( 	LOG_ENGINE_FREE_STREAM,	"Engine free stream",	0xffffffff,	nullptr,	nullptr,	nullptr,	nullptr,	0,	0,	0,	0,	LOG_ENGINE_BASE)\
	STREAMWARE_EVENT( 	LOG_ENGINE_RUN,	"Engine run",	0xffffffff,	"RenderStreamCount:",	" BaseTime:", " ", " ",	10,	16,	10,	10, LOG_ENGINE_BASE)\
	STREAMWARE_EVENT( 	LOG_ENGINE_THREAD,	"Engine thread",	0xffffffff,	"min:",	" average:",	" max:",	nullptr,	10,	10,	10,	0,	LOG_ENGINE_BASE)\
	STREAMWARE_EVENT( 	LOG_ENGINE_NOTIFY,	"Engine notify",	0xffffffff,	"Position:",	" Difference:",	" TotalSamples:",	" Previous:",	16,	16,	16,	16,	LOG_ENGINE_BASE)\
	STREAMWARE_EVENT( 	LOG_ENGINE_SERVICE,	"Engine service",	0xffffffff,	" datablocks:",	" packets:",	nullptr,	nullptr,	16,	16,	0,	0,	LOG_ENGINE_BASE)\
	STREAMWARE_EVENT( 	LOG_ENGINE_TIMER,	"Engine timer",	0xffffffff,	nullptr,	nullptr,	nullptr,	nullptr,	0,	0,	0,	0,	LOG_ENGINE_BASE)\
	STREAMWARE_EVENT( 	SEND_COMPLETE,	"Send complete",	0xffffffff,	nullptr,	nullptr,	nullptr,	nullptr,	0,	0,	0,	0,	SEND_REC_BASE)\
	STREAMWARE_EVENT( 	ASIO_THREAD_NOTIFY,	"ASIO thread notify",	0xffffffff,	"Driver:",	" Client:",nullptr,nullptr,	16,	16,	16,	10,	ASIO_BASE)\
	STREAMWARE_EVENT( 	ASIO_THREAD_TIMEOUT_NOTIFY,	"ASIO thread timeout notify",	0xffffffff,	"Driver:",	" Client:",nullptr,nullptr,	16,	16,	16,	10,	ASIO_BASE)\
	STREAMWARE_EVENT( 	ASIO_THREAD_WAKE,	"ASIO thread wake",	0xffffffff,	"Driver:",	" Client:",	" Change:",	" Count:",	16,	16,	16,	10,	ASIO_BASE)\
	STREAMWARE_EVENT( 	ASIO_THREAD_RESYNC,	"ASIO thread resync",	0x40E80060,	" Change:",	" Driver:",	" Client:",	" Count:",	10,	16,	16,	10,	ASIO_BASE)\
	STREAMWARE_EVENT( 	ASIO_THREAD_HOST_NOTIFY,	"ASIO host notify",	0xff38F4FF,	"Driver:",	" Client:",	" Count:",	nullptr,	16,	16,	16,	0,	ASIO_BASE) \
	STREAMWARE_EVENT( 	ASIO_OUTPUT_READY,	"ASIO output ready",	0xff2AF4FF,	nullptr,	nullptr,	nullptr,	nullptr,	0,	0,	0,	0,	ASIO_BASE) \
	STREAMWARE_EVENT( 	METRICS_TIMER,	"Metrics",	0xffffffff,	"launch:",	" previous:",	" difference:",	" index:",	16,	16,	10,	10,	METRICS_BASE) \
	STREAMWARE_EVENT( 	RENDER_METRICS,	"Render metrics",	0xffffffff,	"difference64:",	" difference:",	" numerator:",	" presentationSampleRate:",	16,	16,	16,	10,	METRICS_BASE) \
	STREAMWARE_EVENT( 	METRICS_ERROR,	"Metrics error",	0x80800000,	"current:",	" previous:",	" delta:",	" ID:",	16,	16,	10,	16,	METRICS_BASE)\
	STREAMWARE_EVENT( 	FAULT_INJECTION_TIMESTAMP_JUMP,	"AVTP timestamp jump TX",	0x80FF880D,	"stream_id:",	"   avtp_timestamp:",	"",	"",	16,	16, 0, 0, FAULT_INJECTION_BASE)\
	STREAMWARE_EVENT( 	FAULT_INJECTION_DUPLICATE,	"AVTP duplicate packet TX",	0x80FF740D,	"stream_id:",	"   avtp_timestamp:",	"   sequence_num:",	"",	16,	16, 16, 0, FAULT_INJECTION_BASE)\
	STREAMWARE_EVENT( 	FAULT_INJECTION_CORRUPT_CD,	"AVTP corrupt CD TX",	0x80FF740D,	"stream_id:",	"   avtp_timestamp:",	nullptr,	nullptr,	16,	16, 0, 0, FAULT_INJECTION_BASE)\
	STREAMWARE_EVENT( 	FAULT_INJECTION_CORRUPT_SUBTYPE,	"AVTP corrupt subtype TX",	0x80FF740D,	"stream_id:",	"   avtp_timestamp:",	"   subtype:",	nullptr,	16,	16, 16, 0, FAULT_INJECTION_BASE)\
	STREAMWARE_EVENT( 	FAULT_INJECTION_CORRUPT_SV,	"AVTP corrupt SV TX",	0x80FF740D,	"stream_id:",	"   avtp_timestamp:",	nullptr,	nullptr,	16,	16, 0, 0, FAULT_INJECTION_BASE)\
	STREAMWARE_EVENT( 	FAULT_INJECTION_CORRUPT_VERSION,	"AVTP corrupt version TX",	0x80FF740D,	"stream_id:",	"   avtp_timestamp:",	"   version:",	nullptr,	16,	16, 16, 0, FAULT_INJECTION_BASE)\
	STREAMWARE_EVENT( 	FAULT_INJECTION_CORRUPT_TV,	"AVTP corrupt TV TX",	0x80FF740D,	"stream_id:",	"   avtp_timestamp:",	nullptr,	nullptr,	16,	16, 0, 0, FAULT_INJECTION_BASE)\
	STREAMWARE_EVENT( 	FAULT_INJECTION_CORRUPT_FORMAT,	"AVTP corrupt format TX",	0x80FF740D,	"stream_id:",	"   avtp_timestamp:",	"   format:",	nullptr,	16,	16, 16, 0, FAULT_INJECTION_BASE)\
	STREAMWARE_EVENT( 	FAULT_INJECTION_CORRUPT_RESERVED,	"AVTP corrupt reserved TX",	0x80FF740D,	"stream_id:",	"   avtp_timestamp:",	"   reserved:",	"   offset:",	16,	16, 16, 16, FAULT_INJECTION_BASE)\
	STREAMWARE_EVENT( 	FAULT_INJECTION_CORRUPT_NOMINAL_SAMPLE_RATE,	"AVTP corrupt nominal sample rate TX",	0x80FF740D,	"stream_id:",	"   avtp_timestamp:",	"   nominal_sample_rate:",	nullptr,	16,	16, 16, 0, FAULT_INJECTION_BASE)\
	STREAMWARE_EVENT( 	FAULT_INJECTION_CORRUPT_BIT_DEPTH,	"AVTP corrupt bit depth TX",	0x80FF740D,	"stream_id:",	"   avtp_timestamp:",	"   bit_depth:",	nullptr,	16,	16, 16, 0, FAULT_INJECTION_BASE)\
	STREAMWARE_EVENT( 	FAULT_INJECTION_CORRUPT_STREAM_DATA_LENGTH,	"AVTP corrupt stream data length TX",	0x80FF740D,	"stream_id:",	"   avtp_timestamp:",	"   stream_data_length:",	nullptr,	16,	16, 16, 0, FAULT_INJECTION_BASE)\
	STREAMWARE_EVENT( 	FAULT_INJECTION_CORRUPT_M3,	"AVTP corrupt M3 TX",	0x80FF740D,	"stream_id:",	"   avtp_timestamp:",	nullptr,	nullptr,	16,	16, 0, 0, FAULT_INJECTION_BASE)\
	STREAMWARE_EVENT( 	FAULT_INJECTION_CORRUPT_M2,	"AVTP corrupt M2 TX",	0x80FF740D,	"stream_id:",	"   avtp_timestamp:",	nullptr,	nullptr,	16,	16, 0, 0, FAULT_INJECTION_BASE)\
	STREAMWARE_EVENT( 	FAULT_INJECTION_CORRUPT_M1,	"AVTP corrupt M1 TX",	0x80FF740D,	"stream_id:",	"   avtp_timestamp:",	nullptr,	nullptr,	16,	16, 0, 0, FAULT_INJECTION_BASE)\
	STREAMWARE_EVENT( 	FAULT_INJECTION_CORRUPT_M0,	"AVTP corrupt M0 TX",	0x80FF740D,	"stream_id:",	"   avtp_timestamp:",	nullptr,	nullptr,	16,	16, 0, 0, FAULT_INJECTION_BASE)\
	STREAMWARE_EVENT( 	FAULT_INJECTION_CORRUPT_EVT, "AVTP corrupt evt TX",	0x80FF740D,	"stream_id:",	"   avtp_timestamp:",	"   evt:",	nullptr,	16,	16, 16, 0, FAULT_INJECTION_BASE)\
	STREAMWARE_EVENT( 	FAULT_INJECTION_CORRUPT_CHANNELS_PER_FRAME,	"AVTP corrupt channels per frame TX",	0x80FF740D,	"stream_id:",	"   avtp_timestamp:",	"   channels_per_frame:",	nullptr,	16,	16, 16, 0, FAULT_INJECTION_BASE)\
	STREAMWARE_EVENT( 	FAULT_INJECTION_CORRUPT_CRS_TYPE,	"AVTP corrupt CRS type TX",	0x80FF740D,	"stream_id:",	"   avtp_timestamp:",	"   type:",	nullptr,	16,	16, 16, 0, FAULT_INJECTION_BASE)\
	STREAMWARE_EVENT( 	FAULT_INJECTION_CORRUPT_CRS_NOMINAL_FREQUENCY,	"AVTP corrupt CRS nominal frequency TX",	0x80FF740D,	"stream_id:",	"   avtp_timestamp:",	"   nominal_frequency:",	nullptr,	16,	16, 16, 0, FAULT_INJECTION_BASE)\
	STREAMWARE_EVENT( 	FAULT_INJECTION_CORRUPT_CRS_TIMESTAMP_INTERVAL,	"AVTP corrupt CRS timestamp interval TX",	0x80FF740D,	"stream_id:",	"   avtp_timestamp:",	"   timestamp_interval:",	nullptr,	16,	16, 16, 0, FAULT_INJECTION_BASE)\
	STREAMWARE_EVENT( 	FAULT_INJECTION_PTP_GRANDMASTER_JUMP,	"PTP grandmaster jump",	0x88952DFF,	nullptr, nullptr, nullptr,	nullptr,	0,	0, 0, 0, FAULT_INJECTION_BASE)\
	STREAMWARE_EVENT( 	FAULT_INJECTION_PTP_SKIP_SYNC,	"PTP skip sync message TX",	0x80952DFF,	nullptr, nullptr, nullptr,	nullptr,	0,	0, 0, 0, FAULT_INJECTION_BASE)\
	STREAMWARE_EVENT( 	FAULT_INJECTION_PTP_SKIP_FOLLOW_UP,	"PTP skip followup message TX",	0x78952DFF,	nullptr, nullptr, nullptr,	nullptr,	0,	0, 0, 0, FAULT_INJECTION_BASE)\
	STREAMWARE_EVENT( 	FAULT_INJECTION_PTP_SKIP_DELAY_REQUEST,	"PTP skip pdelay request TX",	0x70952DFF,	nullptr, nullptr, nullptr,	nullptr,	0,	0, 0, 0, FAULT_INJECTION_BASE)\
	STREAMWARE_EVENT( 	AVTP_TIMESTAMP_FAULT,	"AVTP timestamp fault RX",	0x80FF2B00,	"stream_id:",	"   avtp_timestamp:",	"   AVTP timestamp difference:",	"",	16,	16, 10, 0, FAULT_DETECTION_BASE) \
	STREAMWARE_EVENT( 	AVTP_SEQUENCE_FAULT,	"AVTP sequence fault RX",	0x80fe2B00,	"stream_id:",	"   avtp_timestamp:",	"   sequence_num difference:",	"",	16,	16, 10, 0, FAULT_DETECTION_BASE) \
	STREAMWARE_EVENT( 	AVTP_DUPLICATE_FAULT,	"AVTP duplicate packet fault RX",	0x80fa2800,	"stream_id:",	"   avtp_timestamp:",	nullptr,	nullptr,	16,	16, 0, 0, FAULT_DETECTION_BASE) \
	STREAMWARE_EVENT( 	AVTP_CD_FIELD_FAULT,	"AVTP CD fault RX",	0x80fa2800,	"stream_id:",	"   avtp_timestamp:",	"   cd:",	nullptr,	16,	16, 10, 0, FAULT_DETECTION_BASE) \
	STREAMWARE_EVENT( 	AVTP_SUBTYPE_FIELD_FAULT,	"AVTP subtype fault RX",	0x80fa2800,	"stream_id:",	"   avtp_timestamp:",	"   subtype:",	nullptr,	16,	16, 16, 0, FAULT_DETECTION_BASE) \
	STREAMWARE_EVENT( 	AVTP_SV_FIELD_FAULT,	"AVTP SV fault RX",	0x80fa2800,	"stream_id:",	"   avtp_timestamp:",	"   sv:",	nullptr,	16,	16, 10, 0, FAULT_DETECTION_BASE) \
	STREAMWARE_EVENT( 	AVTP_VERSION_FIELD_FAULT,	"AVTP version fault RX",	0x80fa2800,	"stream_id:",	"   avtp_timestamp:",	"   version:",	nullptr,	16,	16, 16, 0, FAULT_DETECTION_BASE) \
	STREAMWARE_EVENT( 	AVTP_TV_FIELD_FAULT,	"AVTP TV fault RX",	0x80fa2800,	"stream_id:",	"   avtp_timestamp:",	"   tv:",	nullptr,	16,	16, 10, 0, FAULT_DETECTION_BASE) \
	STREAMWARE_EVENT( 	AVTP_FORMAT_FIELD_FAULT,	"AVTP format fault RX",	0x80fa2800,	"stream_id:",	"   avtp_timestamp:",	"   format:",	nullptr,	16,	16, 16, 0, FAULT_DETECTION_BASE) \
	STREAMWARE_EVENT( 	AVTP_RESERVED_FIELD_FAULT,	"AVTP reserved fault RX",	0x80fa2800,	"stream_id:",	"   avtp_timestamp:",	"   reserved:",	"   offset:",	16,	16, 16, 16, FAULT_DETECTION_BASE) \
	STREAMWARE_EVENT( 	AVTP_NOMINAL_SAMPLE_RATE_FIELD_FAULT,	"AVTP nominal sample rate fault RX",	0x80fa2800,	"stream_id:",	"   avtp_timestamp:",	"   nominal_sample_rate:",	nullptr,	16,	16, 16, 0, FAULT_DETECTION_BASE) \
	STREAMWARE_EVENT( 	AVTP_BIT_DEPTH_FIELD_FAULT,	"AVTP bit depth fault RX",	0x80fa2800,	"stream_id:",	"   avtp_timestamp:",	"   bit_depth:",	nullptr,	16,	16, 16, 0, FAULT_DETECTION_BASE) \
	STREAMWARE_EVENT( 	AVTP_STREAM_DATA_LENGTH_FIELD_FAULT,	"AVTP stream data length fault RX",	0x80fa2800,	"stream_id:",	"   avtp_timestamp:",	"   stream_data_length:",	nullptr,	16,	16, 16, 0, FAULT_DETECTION_BASE) \
	STREAMWARE_EVENT( 	AVTP_CRS_TYPE_FIELD_FAULT,	"AVTP CRS type fault RX",	0x80fa2800,	"stream_id:",	"   avtp_timestamp:",	"   type:",	nullptr,	16,	16, 16, 0, FAULT_DETECTION_BASE) \
	STREAMWARE_EVENT( 	AVTP_NOMINAL_FREQUENCY_FIELD_FAULT,	"AVTP nominal frequency fault RX",	0x80fa2800,	"stream_id:",	"   avtp_timestamp:",	"   nominal_frequency:",	nullptr,	16,	16, 16, 0, FAULT_DETECTION_BASE) \
	STREAMWARE_EVENT( 	AVTP_TIMESTAMP_INTERVAL_FIELD_FAULT,	"AVTP timestamp interval fault RX",	0x80fa2800,	"stream_id:",	"   avtp_timestamp:",	"   timestamp_interval:",	nullptr,	16,	16, 16, 0, FAULT_DETECTION_BASE) \
	STREAMWARE_EVENT( 	AVTP_CHANNELS_PER_FRAME_FIELD_FAULT,	"AVTP channels per frame fault RX",0x80FF740D,	"stream_id:",	"   avtp_timestamp:",	"  channels_per_frame:",	nullptr,	16,	16, 16, 0, FAULT_DETECTION_BASE)\
	STREAMWARE_EVENT( 	AVTP_M3_FIELD_FAULT,	"AVTP M3 fault RX",	0x80FF740D,	"stream_id:",	"   avtp_timestamp:",	"   M3:",	nullptr,	16,	16, 10, 0, FAULT_DETECTION_BASE)\
	STREAMWARE_EVENT( 	AVTP_M2_FIELD_FAULT,	"AVTP M2 fault RX",	0x80FF740D,	"stream_id:",	"   avtp_timestamp:",	"   M2:",	nullptr,	16,	16, 10, 0, FAULT_DETECTION_BASE)\
	STREAMWARE_EVENT( 	AVTP_M1_FIELD_FAULT,	"AVTP M1 fault RX",	0x80FF740D,	"stream_id:",	"   avtp_timestamp:",	"   M1:",	nullptr,	16,	16, 10, 0, FAULT_DETECTION_BASE)\
	STREAMWARE_EVENT( 	AVTP_M0_FIELD_FAULT,	"AVTP M0 fault RX",	0x80FF740D,	"stream_id:",	"   avtp_timestamp:",	"   M0:",	nullptr,	16,	16, 10, 0, FAULT_DETECTION_BASE)\
	STREAMWARE_EVENT( 	AVTP_EVT_FIELD_FAULT,	"AVTP evt fault RX",0x80FF740D,	"stream_id:",	"   avtp_timestamp:",	"   evt:",	nullptr,	16,	16, 10, 0, FAULT_DETECTION_BASE)\
	STREAMWARE_EVENT( 	AVTP_PACKET_SIZE_FAULT,	"AVTP packet size fault RX",	0x80f82600,	"stream_id:", "   Bytes:",	nullptr,	nullptr,	16, 10,	0, 0, FAULT_DETECTION_BASE) \
	STREAMWARE_EVENT( 	AVTP_STREAM_ID_FAULT,	"AVTP stream ID mismatch",	0x80FFFF00,	"Expected stream_id:",	"   Received stream_id:",	"  DestinationAddress:",	nullptr,	16,	16, 16, 0, FAULT_DETECTION_BASE) \
	STREAMWARE_EVENT( 	AVTP_PRESENTATION_OFFSET_FAULT,	"AVTP presentation offset fault RX",0x80FF3000,	"stream_id:",	"   avtp_timestamp:",	"   offset:",	nullptr,	16,	16, 10, 0, FAULT_DETECTION_BASE)\
	STREAMWARE_EVENT( 	PTP_MISSING_SYNC_FAULT,	"PTP missing sync RX",	0x80FFB427,	"Last sequenceID:",	nullptr, nullptr,	nullptr,	10,	0, 0, 0, FAULT_DETECTION_BASE) \
	STREAMWARE_EVENT( 	PTP_MISSING_FOLLOWUP_FAULT,	"PTP missing followup RX",	0x80FFB427,	"Last sequenceID:",	nullptr, nullptr,	nullptr,	10,	0, 0, 0, FAULT_DETECTION_BASE) \
	STREAMWARE_EVENT( 	PTP_FOLLOWUP_SEQUENCE_FAULT,	"PTP Followup sequence mismatch RX",	0x80FFB427,	"sequenceID:",	"   sequenceID:", nullptr,	nullptr,	10,	10, 0, 0, FAULT_DETECTION_BASE) \
	STREAMWARE_EVENT( 	PTP_SYNC_TRANSPORT_SPECIFIC_FAULT,	"PTP sync transport specific fault RX",	0x80FFB427,	"sequenceID:",	"   transportSpecific:", nullptr,	nullptr,	10,	10, 0, 0, FAULT_DETECTION_BASE) \
	STREAMWARE_EVENT( 	PTP_SYNC_PTP_VERSION_FAULT,	"PTP sync PTP version fault RX",	0x80FFB427,	"sequenceID:",	"   versionPTP:", nullptr,	nullptr,	10,	10, 0, 0, FAULT_DETECTION_BASE) \
	STREAMWARE_EVENT( 	PTP_SYNC_RESERVED_FAULT,	"PTP sync reserved fault RX",	0x80FFB427,	"sequenceID:",	"   reserved:", "   offset:",	nullptr,	10,	16, 10, 0, FAULT_DETECTION_BASE) \
	STREAMWARE_EVENT( 	PTP_SYNC_MESSAGE_LENGTH_FAULT,	"PTP sync message length fault RX",	0x80FFB427,	"sequenceID:",	"   messageLength:", nullptr,	nullptr,	10,	16, 0, 0, FAULT_DETECTION_BASE) \
	STREAMWARE_EVENT( 	PTP_SYNC_DOMAIN_NUMBER_FAULT,	"PTP sync domain number fault RX",	0x80FFB427,	"sequenceID:",	"   domainNumber:", nullptr,	nullptr,	10,	16, 0, 0, FAULT_DETECTION_BASE) \
	STREAMWARE_EVENT( 	PTP_SYNC_FLAGS_FAULT,	"PTP sync flags fault RX",	0x80FFB427,	"sequenceID:",	"   flags:", nullptr,	nullptr,	10,	16, 0, 0, FAULT_DETECTION_BASE) \
	STREAMWARE_EVENT( 	PTP_SYNC_CORRECTION_FIELD_FAULT,	"PTP sync correction field fault RX",	0x80FFB427,	"sequenceID:",	"   correctionField:", nullptr,	nullptr,	10,	16, 0, 0, FAULT_DETECTION_BASE) \
	STREAMWARE_EVENT( 	PTP_SYNC_PORT_IDENTITY_CLOCK_IDENTITY_FAULT,	"PTP sync clock identity fault RX",	0x80FFB427,	"sequenceID:",	"   clockIdentity:", nullptr,	nullptr,	10,	16, 0, 0, FAULT_DETECTION_BASE) \
	STREAMWARE_EVENT( 	PTP_SYNC_PORT_IDENTITY_PORT_NUMBER_FAULT,	"PTP sync port number fault RX",	0x80FFB427,	"sequenceID:",	"   portNumber:", nullptr,	nullptr,	10,	16, 0, 0, FAULT_DETECTION_BASE) \
	STREAMWARE_EVENT( 	PTP_SYNC_SEQUENCEID_FAULT,	"PTP sync sequenceId fault RX",	0x80FFB427,	"expected sequenceID:",	"   received sequenceId:", nullptr,	nullptr,	10,	10, 0, 0, FAULT_DETECTION_BASE) \
	STREAMWARE_EVENT( 	PTP_SYNC_CONTROL_FAULT,	"PTP sync control fault RX",	0x80FFB427,	"sequenceID:",	"   control:", nullptr,	nullptr,	10,	16, 0, 0, FAULT_DETECTION_BASE) \
	STREAMWARE_EVENT( 	PTP_FOLLOWUP_TRANSPORT_SPECIFIC_FAULT,	"PTP followup transport specific fault RX",	0x80FFB427,	"sequenceID:",	"   transportSpecific:", nullptr,	nullptr,	10,	10, 0, 0, FAULT_DETECTION_BASE) \
	STREAMWARE_EVENT( 	PTP_FOLLOWUP_PTP_VERSION_FAULT,	"PTP followup PTP version fault RX",	0x80FFB427,	"sequenceID:",	"   versionPTP:", nullptr,	nullptr,	10,	10, 0, 0, FAULT_DETECTION_BASE) \
	STREAMWARE_EVENT( 	PTP_FOLLOWUP_RESERVED_FAULT,	"PTP followup reserved fault RX",	0x80FFB427,	"sequenceID:",	"   reserved:", "   offset:",	nullptr,	10,	16, 10, 0, FAULT_DETECTION_BASE) \
	STREAMWARE_EVENT( 	PTP_FOLLOWUP_MESSAGE_LENGTH_FAULT,	"PTP followup message length fault RX",	0x80FFB427,	"sequenceID:",	"   messageLength:", nullptr,	nullptr,	10,	16, 0, 0, FAULT_DETECTION_BASE) \
	STREAMWARE_EVENT( 	PTP_FOLLOWUP_DOMAIN_NUMBER_FAULT,	"PTP followup domain number fault RX",	0x80FFB427,	"sequenceID:",	"   domainNumber:", nullptr,	nullptr,	10,	16, 0, 0, FAULT_DETECTION_BASE) \
	STREAMWARE_EVENT( 	PTP_FOLLOWUP_FLAGS_FAULT,	"PTP followup flags fault RX",	0x80FFB427,	"sequenceID:",	"   flags:", nullptr,	nullptr,	10,	16, 0, 0, FAULT_DETECTION_BASE) \
	STREAMWARE_EVENT( 	PTP_FOLLOWUP_CORRECTION_FIELD_FAULT,	"PTP followup correction field fault RX",	0x80FFB427,	"sequenceID:",	"   correctionField:", nullptr,	nullptr,	10,	16, 0, 0, FAULT_DETECTION_BASE) \
	STREAMWARE_EVENT( 	PTP_FOLLOWUP_PORT_IDENTITY_CLOCK_IDENTITY_FAULT,	"PTP followup clock identity fault RX",	0x80FFB427,	"sequenceID:",	"   clockIdentity:", nullptr,	nullptr,	10,	16, 0, 0, FAULT_DETECTION_BASE) \
	STREAMWARE_EVENT( 	PTP_FOLLOWUP_PORT_IDENTITY_PORT_NUMBER_FAULT,	"PTP followup port number fault RX",	0x80FFB427,	"sequenceID:",	"   portNumber:", nullptr,	nullptr,	10,	16, 0, 0, FAULT_DETECTION_BASE) \
	STREAMWARE_EVENT( 	PTP_FOLLOWUP_SEQUENCEID_FAULT,	"PTP followup sequenceId fault RX",	0x80FFB427,	"expected sequenceID:",	"   received sequenceId:", nullptr,	nullptr,	10,	10, 0, 0, FAULT_DETECTION_BASE) \
	STREAMWARE_EVENT( 	PTP_FOLLOWUP_CONTROL_FAULT,	"PTP followup control fault RX",	0x80FFB427,	"sequenceID:",	"   control:", nullptr,	nullptr,	10,	16, 0, 0, FAULT_DETECTION_BASE) \
	STREAMWARE_EVENT( 	PTP_FOLLOWUP_TLV_TYPE_FAULT,	"PTP followup tlv type fault RX",	0x80FFB427,	"sequenceID:",	"   tlv_type:", nullptr,	nullptr,	10,	16, 0, 0, FAULT_DETECTION_BASE) \
	STREAMWARE_EVENT( 	PTP_FOLLOWUP_TLV_LENGTH_FIELD_FAULT,	"PTP followup tlv length field fault RX",	0x80FFB427,	"sequenceID:",	"   length_field:", nullptr,	nullptr,	10,	16, 0, 0, FAULT_DETECTION_BASE) \
	STREAMWARE_EVENT( 	PTP_FOLLOWUP_TLV_ORGANIZATION_ID_FAULT,	"PTP followup tlv organization id fault RX",	0x80FFB427,	"sequenceID:",	"   organization_id:", nullptr,	nullptr,	10,	16, 0, 0, FAULT_DETECTION_BASE) \
	STREAMWARE_EVENT( 	PTP_FOLLOWUP_TLV_ORGANIZATION_SUBTYPE_FAULT,	"PTP followup tlv organization subtype fault RX",	0x80FFB427,	"sequenceID:",	"   organization_subtype:", nullptr,	nullptr,	10,	16, 0, 0, FAULT_DETECTION_BASE) \
	STREAMWARE_EVENT( 	LOG_DEBUG,	"Debug",	0x80FF1100,	" ",	"   ",	"   ",	"  ",	16,	16, 16, 16, DEBUG_BASE ) \
	STREAMWARE_EVENT(	LINK_DOWN, "Ethernet link down", 0xffffffff, nullptr, nullptr, nullptr, nullptr, 0, 0, 0, 0, LINK_BASE) \
	STREAMWARE_EVENT(	ETHERNET_LINK_UP, "Ethernet link up", 0xffffffff, "TX:", ",  RX:", nullptr, nullptr, 10, 10, 0, 0, LINK_BASE) \
	STREAMWARE_EVENT(	BR_LINK_UP, "BR link up", 0xffffffff, "TX:", ",  RX:", nullptr, nullptr, 10, 10, 0, 0, LINK_BASE)
typedef enum
{
#define STREAMWARE_EVENT( code, name, colour, prefix0, prefix1, prefix2, prefix3, radix0, radix1, radix2, radix3, type)	code,
	STREAMWARE_EVENT_LIST
#undef STREAMWARE_EVENT

	NUM_STREAMWARE_EVENTS
}Code;

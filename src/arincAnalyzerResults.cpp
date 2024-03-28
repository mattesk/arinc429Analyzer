#include "arincAnalyzerResults.h"
#include <AnalyzerHelpers.h>
#include "arincAnalyzer.h"
#include "arincAnalyzerSettings.h"
#include <iostream>
#include <fstream>

arincAnalyzerResults::arincAnalyzerResults( arincAnalyzer* analyzer, arincAnalyzerSettings* settings )
:	AnalyzerResults(),
	mSettings( settings ),
	mAnalyzer( analyzer )
{
}

arincAnalyzerResults::~arincAnalyzerResults()
{
}

unsigned int reverseBits(unsigned int num)
{
    unsigned int NO_OF_BITS = sizeof(num) * 8;
    unsigned int reverse_num = 0;
    int i;
    for (i = 0; i < NO_OF_BITS; i++) {
        if ((num & (1 << i)))
            reverse_num |= 1 << ((NO_OF_BITS - 1) - i);
    }
    return reverse_num;
}
 
void arincAnalyzerResults::GenerateBubbleText( U64 frame_index, Channel& channel, DisplayBase display_base )
{
	ClearResultStrings();
	Frame frame = GetFrame( frame_index );

	char raw_number_str[64];
	AnalyzerHelpers::GetNumberString( frame.mData1, display_base, 8, raw_number_str, 64 );
	//AddResultString( raw_number_str );

	char result_str[ 128 ];

	char label_str[10];
	int32_t iLabel = (frame.mData1 & 0xff000000) >> 24;
	AnalyzerHelpers::GetNumberString( iLabel, display_base, 8, label_str, 10 );

   // change ARINC data bit order for visibilty
	char data_str[20];
	uint32_t rData = frame.mData1;
   uint32_t uData = reverseBits(rData);
	uint8_t hsbData = uData >> 24;
	uint8_t msbData = uData >> 16;
	uint8_t lsbData = uData >> 8;
	uData = (lsbData << 16) | (msbData << 8) | hsbData;

	AnalyzerHelpers::GetNumberString( uData, display_base, 8, data_str, 20 );

	//snprintf( result_str, sizeof( result_str ), "label:data %s: %s  [raw%s]", label_str,data_str, raw_number_str );
	snprintf( result_str, sizeof( result_str ), "arinc %s: %s  [raw%s]", label_str,data_str, raw_number_str );
	AddResultString( result_str );

}

void arincAnalyzerResults::GenerateExportFile( const char* file, DisplayBase display_base, U32 export_type_user_id )
{
	std::ofstream file_stream( file, std::ios::out );

	U64 trigger_sample = mAnalyzer->GetTriggerSample();
	U32 sample_rate = mAnalyzer->GetSampleRate();

	file_stream << "Time [s],Value" << std::endl;

	U64 num_frames = GetNumFrames();
	for( U32 i=0; i < num_frames; i++ )
	{
		Frame frame = GetFrame( i );
		
		char time_str[128];
		AnalyzerHelpers::GetTimeString( frame.mStartingSampleInclusive, trigger_sample, sample_rate, time_str, 128 );

		char number_str[128];
		AnalyzerHelpers::GetNumberString( frame.mData1, display_base, 8, number_str, 128 );

		file_stream << time_str << "," << number_str << std::endl;

		if( UpdateExportProgressAndCheckForCancel( i, num_frames ) == true )
		{
			file_stream.close();
			return;
		}
	}

	file_stream.close();
}

void arincAnalyzerResults::GenerateFrameTabularText( U64 frame_index, DisplayBase display_base )
{
#ifdef SUPPORTS_PROTOCOL_SEARCH
	Frame frame = GetFrame( frame_index );
	ClearTabularText();

	char number_str[128];
	AnalyzerHelpers::GetNumberString( frame.mData1, display_base, 8, number_str, 128 );
	AddTabularText( number_str );
#endif
}

void arincAnalyzerResults::GeneratePacketTabularText( U64 packet_id, DisplayBase display_base )
{
	//not supported

}

void arincAnalyzerResults::GenerateTransactionTabularText( U64 transaction_id, DisplayBase display_base )
{
	//not supported
}

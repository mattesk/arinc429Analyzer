#ifndef ARINC_ANALYZER_RESULTS
#define ARINC_ANALYZER_RESULTS

#include <AnalyzerResults.h>

class arincAnalyzer;
class arincAnalyzerSettings;

class arincAnalyzerResults : public AnalyzerResults
{
public:
	arincAnalyzerResults( arincAnalyzer* analyzer, arincAnalyzerSettings* settings );
	virtual ~arincAnalyzerResults();

	virtual void GenerateBubbleText( U64 frame_index, Channel& channel, DisplayBase display_base );
	virtual void GenerateExportFile( const char* file, DisplayBase display_base, U32 export_type_user_id );

	virtual void GenerateFrameTabularText(U64 frame_index, DisplayBase display_base );
	virtual void GeneratePacketTabularText( U64 packet_id, DisplayBase display_base );
	virtual void GenerateTransactionTabularText( U64 transaction_id, DisplayBase display_base );

protected: //functions

protected:  //vars
	arincAnalyzerSettings* mSettings;
	arincAnalyzer* mAnalyzer;
};

#endif //ARINC_ANALYZER_RESULTS

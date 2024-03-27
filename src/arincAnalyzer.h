#ifndef ARINC_ANALYZER_H
#define ARINC_ANALYZER_H

#include <Analyzer.h>
#include "arincAnalyzerResults.h"
#include "arincSimulationDataGenerator.h"

class arincAnalyzerSettings;
class ANALYZER_EXPORT arincAnalyzer : public Analyzer2
{
public:
	arincAnalyzer();
	virtual ~arincAnalyzer();

	virtual void SetupResults();
	virtual void WorkerThread();

	virtual U32 GenerateSimulationData( U64 newest_sample_requested, U32 sample_rate, SimulationChannelDescriptor** simulation_channels );
	virtual U32 GetMinimumSampleRateHz();

	virtual const char* GetAnalyzerName() const;
	virtual bool NeedsRerun();

protected: //vars
	std::auto_ptr< arincAnalyzerSettings > mSettings;
	std::auto_ptr< arincAnalyzerResults > mResults;
	AnalyzerChannelData* mSerial;

	arincSimulationDataGenerator mSimulationDataGenerator;
	bool mSimulationInitilized;

	//Serial analysis vars:
	U32 mSampleRateHz;
	U32 mStartOfStopBitOffset;
	U32 mEndOfStopBitOffset;
};

extern "C" ANALYZER_EXPORT const char* __cdecl GetAnalyzerName();
extern "C" ANALYZER_EXPORT Analyzer* __cdecl CreateAnalyzer( );
extern "C" ANALYZER_EXPORT void __cdecl DestroyAnalyzer( Analyzer* analyzer );

#endif //ARINC_ANALYZER_H

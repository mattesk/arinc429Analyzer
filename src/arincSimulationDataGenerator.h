#ifndef ARINC_SIMULATION_DATA_GENERATOR
#define ARINC_SIMULATION_DATA_GENERATOR

#include <SimulationChannelDescriptor.h>
#include <string>
class arincAnalyzerSettings;

class arincSimulationDataGenerator
{
public:
	arincSimulationDataGenerator();
	~arincSimulationDataGenerator();

	void Initialize( U32 simulation_sample_rate, arincAnalyzerSettings* settings );
	U32 GenerateSimulationData( U64 newest_sample_requested, U32 sample_rate, SimulationChannelDescriptor** simulation_channel );

protected:
	arincAnalyzerSettings* mSettings;
	U32 mSimulationSampleRateHz;

protected:
	void CreateSerialByte();
	std::string mSerialText;
	U32 mStringIndex;

	SimulationChannelDescriptor mSerialSimulationData;

};
#endif //ARINC_SIMULATION_DATA_GENERATOR
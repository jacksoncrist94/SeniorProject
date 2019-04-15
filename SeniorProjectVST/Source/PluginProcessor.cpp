/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

	Oscillator, Envelope, and Filter programmed with assistance from TheAudioProgrammer tutorials

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
SeniorProjectVstAudioProcessor::SeniorProjectVstAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
	: AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
		.withInput("Input", AudioChannelSet::stereo(), true)
#endif
		.withOutput("Output", AudioChannelSet::stereo(), true)
#endif
	),
	tree(*this, nullptr)
#endif
{
	//envelope parameters
	NormalisableRange<float> attackParam(0.1f, 9000.0f);
	NormalisableRange<float> decayParam(1.0f, 86000.0f);
	NormalisableRange<float> sustainParam(0.1f, 1.0f);
	NormalisableRange<float> releaseParam(0.1f, 46000.0f);
	tree.createAndAddParameter("attack", "Attack", "Attack", attackParam, 0.1f, nullptr, nullptr);
	tree.createAndAddParameter("decay", "Decay", "Decay", decayParam, 1.0f, nullptr, nullptr);
	tree.createAndAddParameter("sustain", "Sustain", "Sustain", sustainParam, 0.8f, nullptr, nullptr);
	tree.createAndAddParameter("release", "Release", "Release", releaseParam, 0.1f, nullptr, nullptr);

	//oscillator param
	NormalisableRange<float> wavetypeParam(0, 4);
	tree.createAndAddParameter("wavetype", "WaveType", "wavetype", wavetypeParam, 0, nullptr, nullptr);

	//filter params
	NormalisableRange<float> filterTypeVal(0, 2);
	NormalisableRange<float> filterVal(20.0f, 10000.0f);
	NormalisableRange<float> resVal(1, 50);
	tree.createAndAddParameter("filterType", "FilterType", "FilterType", filterTypeVal, 0, nullptr, nullptr);
	tree.createAndAddParameter("filterCutoff", "FilterCutoff", "FilterCutoff", filterVal, 400.0, nullptr, nullptr);
	tree.createAndAddParameter("filterRes", "FilterRes", "FilterRes", resVal, 1, nullptr, nullptr);

	//lfo params
	NormalisableRange<float> depthVal(0.0f, 0.5f);
	NormalisableRange<float> depthVal2(0.0f, 0.5f);
	NormalisableRange<float> freqVal(1.0f, 20.f);
	NormalisableRange<float> freqVal2(1.0f, 20.f);
	NormalisableRange<float> assignVal(0, 2);
	NormalisableRange<float> assignVal2(0, 2);
	tree.createAndAddParameter("lfoDepth", "LfoDepth", "LfoDepth", depthVal, 0.0, nullptr, nullptr);
	tree.createAndAddParameter("lfoDepth2", "LfoDepth2", "LfoDepth2", depthVal2, 0.0, nullptr, nullptr);
	tree.createAndAddParameter("lfoFreq", "LfoFreq", "LfoFreq", freqVal, 1.0, nullptr, nullptr);
	tree.createAndAddParameter("lfoFreq2", "LfoFreq2", "LfoFreq2", freqVal2, 1.0, nullptr, nullptr);
	tree.createAndAddParameter("lfoAssign", "LfoAssign", "LfoAssign", assignVal, 0, nullptr, nullptr);
	tree.createAndAddParameter("lfoAssign2", "LfoAssign2", "LfoAssign2", assignVal2, 0, nullptr, nullptr);

	//arpeggiator params
	NormalisableRange<float> arpOn(0, 1);
	NormalisableRange<float> arpSpeed(0.0f, 1.0f);
	NormalisableRange<float> arpPattern(0, 2);
	tree.createAndAddParameter("arpOn", "ArpOn", "ArpOn", arpOn, 0, nullptr, nullptr);
	tree.createAndAddParameter("arpSpeed", "ArpSpeed", "ArpSpeed", arpSpeed, 0.5f, nullptr, nullptr);
	tree.createAndAddParameter("arpPattern", "ArpPattern", "ArpPattern", arpPattern, 0, nullptr, nullptr);

	mySynth.clearVoices();
	//add up to 8 voices
	for (int i = 0; i < 8; i++) {
		mySynth.addVoice(new SynthVoice());
	}

	mySynth.clearSounds();
	mySynth.addSound(new SynthSound());

	tree.state = ValueTree("savedParams");
}

SeniorProjectVstAudioProcessor::~SeniorProjectVstAudioProcessor()
{
}

//==============================================================================
const String SeniorProjectVstAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SeniorProjectVstAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SeniorProjectVstAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SeniorProjectVstAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SeniorProjectVstAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SeniorProjectVstAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SeniorProjectVstAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SeniorProjectVstAudioProcessor::setCurrentProgram (int index)
{
}

const String SeniorProjectVstAudioProcessor::getProgramName (int index)
{
    return {};
}

void SeniorProjectVstAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void SeniorProjectVstAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
	//sets sample rate
	ignoreUnused(samplesPerBlock);
	lastSampleRate = sampleRate;
	mySynth.setCurrentPlaybackSampleRate(lastSampleRate);

	//prep additional values for arpeggiator 
	notes.clear();
	currentNote = 0;
	lastNoteValue = -1;
	time = 0.0;
	rate = static_cast<float> (sampleRate);

	//process spec for filter
	dsp::ProcessSpec spec;
	spec.sampleRate = lastSampleRate;
	spec.maximumBlockSize = samplesPerBlock;
	spec.numChannels = getTotalNumOutputChannels();

	//prep filter
	stateVariableFilter.reset();
	stateVariableFilter.prepare(spec);
	updateFilter();
}

void SeniorProjectVstAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SeniorProjectVstAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void SeniorProjectVstAudioProcessor::updateFilter()
{
	//get filter params
	int menuChoice = *tree.getRawParameterValue("filterType");
	float freq = *tree.getRawParameterValue("filterCutoff");
	float res = *tree.getRawParameterValue("filterRes");
	//cutoff lfo params
	float lfoSignal = 1.0;
	float depth1 = *tree.getRawParameterValue("lfoDepth");
	float depth2 = *tree.getRawParameterValue("lfoDepth2");
	float freq1 = *tree.getRawParameterValue("lfoFreq") * 100.0;
	float freq2 = *tree.getRawParameterValue("lfoFreq2") * 100.0;

	//if "cutoff" is enabled on lfo, prep lfo signal to multiply to frequency
	if (*tree.getRawParameterValue("lfoAssign") == 2) {
		lfoSignal *= ((1.0 - depth1) + (depth1 * filterLfo.sinewave(freq1)));
	}

	if (*tree.getRawParameterValue("lfoAssign2") == 2) {
		lfoSignal *= ((1.0 - depth2) + (depth2 * filterLfo.sinewave(freq2)));
	}

	//sets either low, high, or band pass filter
	if (menuChoice == 0) {
		stateVariableFilter.state->type = dsp::StateVariableFilter::Parameters<float>::Type::lowPass;
		stateVariableFilter.state->setCutOffFrequency(lastSampleRate, freq * lfoSignal, res);
	}
	
	if (menuChoice == 1) {
		stateVariableFilter.state->type = dsp::StateVariableFilter::Parameters<float>::Type::highPass;
		stateVariableFilter.state->setCutOffFrequency(lastSampleRate, freq * lfoSignal, res);
	}
	
	if (menuChoice == 2) {
		stateVariableFilter.state->type = dsp::StateVariableFilter::Parameters<float>::Type::bandPass;
		stateVariableFilter.state->setCutOffFrequency(lastSampleRate, freq * lfoSignal, res);
	}
}

void SeniorProjectVstAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
	
	//update params per each voice
	for (int i = 0; i < mySynth.getNumVoices(); i++) {
		if (myVoice = dynamic_cast<SynthVoice*>(mySynth.getVoice(i))) {
			myVoice->getEnvelopeParams(tree.getRawParameterValue("attack"), tree.getRawParameterValue("decay"), tree.getRawParameterValue("sustain"), tree.getRawParameterValue("release"));
			
			myVoice->getOscType(tree.getRawParameterValue("wavetype"));

			myVoice->getLfoParams(tree.getRawParameterValue("lfoAssign"), tree.getRawParameterValue("lfoDepth"), tree.getRawParameterValue("lfoFreq"),
									tree.getRawParameterValue("lfoAssign2"), tree.getRawParameterValue("lfoDepth2"), tree.getRawParameterValue("lfoFreq2"));
		}
	}

	//ARPEGGIATOR BLOCK: full disclosure, this is based on JUCE arp example
	if (*tree.getRawParameterValue("arpOn") == 1) {
		auto numSamples = buffer.getNumSamples();

		//calculate length of each note based on speed of arp
		auto noteDuration = static_cast<int> (std::ceil(rate * 0.25 * (0.1f + (1.0f - (*tree.getRawParameterValue("arpSpeed"))))));

		MidiMessage msg;
		int ignore;

		//add incoming notes to a sorted list
		for (MidiBuffer::Iterator it(midiMessages); it.getNextEvent(msg, ignore);) {
			if (msg.isNoteOn()) {
				notes.add(msg.getNoteNumber());
			}
			else if (msg.isNoteOff()) {
				notes.removeValue(msg.getNoteNumber());
			}
		}

		//vector for output
		vector<int> notesOut;

		//generate new output based on selected pattern
		if (*tree.getRawParameterValue("arpPattern") == 0) {
			for (int i = 0; i < notes.size(); i++) {
				notesOut.push_back(notes[i]);
			}
		}
		else if (*tree.getRawParameterValue("arpPattern") == 1) {
			for (int i = notes.size() - 1; i >= 0; i--) {
				notesOut.push_back(notes[i]);
			}
		}
		else if (*tree.getRawParameterValue("arpPattern") == 2) {
			for (int i = 0; i < notes.size(); i++) {
				notesOut.push_back(notes[i]);
			}

			for (int i = notes.size() - 2; i > 0; i--) {
				notesOut.push_back(notes[i]);
			}
		}
		
		//clear out old midi messages to add sorted ones
		midiMessages.clear();


		if ((time + numSamples) >= noteDuration) {
			auto offset = jmax(0, jmin((int)(noteDuration - time), numSamples - 1));

			//add note-off data to midi
			if (lastNoteValue > 0) {
				midiMessages.addEvent(MidiMessage::noteOff(1, lastNoteValue), offset);
				lastNoteValue = -1;
			}

			//add note-on data to midi
			if (notes.size() > 0) {
				currentNote = (currentNote + 1) % notesOut.size();
				lastNoteValue = notesOut[currentNote];
				midiMessages.addEvent(MidiMessage::noteOn(1, lastNoteValue, (uint8)127), offset);
			}
		}

		time = (time + numSamples) % noteDuration;
	}

	//process midi, audio, filter
	buffer.clear();
	mySynth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
	updateFilter();
	dsp::AudioBlock<float> block(buffer);
	stateVariableFilter.process(dsp::ProcessContextReplacing<float>(block));
}

//==============================================================================
bool SeniorProjectVstAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* SeniorProjectVstAudioProcessor::createEditor()
{
    return new SeniorProjectVstAudioProcessorEditor (*this);
}

//==============================================================================
void SeniorProjectVstAudioProcessor::getStateInformation (MemoryBlock& destData)
{
	ScopedPointer<XmlElement>  xml(tree.state.createXml());
	copyXmlToBinary(*xml, destData);
}

void SeniorProjectVstAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
	ScopedPointer<XmlElement> stateParams(getXmlFromBinary(data, sizeInBytes));
	if (stateParams != nullptr) {
		if (stateParams->hasTagName(tree.state.getType())) {
			tree.state = ValueTree::fromXml(*stateParams);
		}
	}
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SeniorProjectVstAudioProcessor();
}

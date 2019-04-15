/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "Oscillator.h"
#include "Envelope.h"
#include "Filter.h"
#include "LFO.h"
#include "Arpeggiator.h"


//==============================================================================
/**
*/
class SeniorProjectVstAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    SeniorProjectVstAudioProcessorEditor (SeniorProjectVstAudioProcessor&);
    ~SeniorProjectVstAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

	


private:
    SeniorProjectVstAudioProcessor& processor;

	Oscillator oscGui;

	Envelope envGui;

	Filter filGui;

	LFO lfoGui;

	Arpeggiator arpGui;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SeniorProjectVstAudioProcessorEditor)
};

/*
  ==============================================================================

    Envelope.h
    Created: 13 Aug 2018 4:19:01pm
    Author:  Jackson Crist

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class Envelope    : public Component
{
public:
    Envelope(SeniorProjectVstAudioProcessor&);
    ~Envelope();

    void paint (Graphics&) override;
    void resized() override;

private:
	//control values
	ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> attackTree;
	ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> decayTree;
	ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> sustainTree;
	ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> releaseTree;

	//controls
	Slider attackSlider;
	Slider decaySlider;
	Slider sustainSlider;
	Slider releaseSlider;

	//labels
	Label attackLabel;
	Label decayLabel;
	Label sustainLabel;
	Label releaseLabel;

	//refrence to processor
	SeniorProjectVstAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Envelope)
};

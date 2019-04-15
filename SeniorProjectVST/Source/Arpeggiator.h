/*
  ==============================================================================

    Arpeggiator.h
    Created: 17 Aug 2018 5:17:47pm
    Author:  Jackson Crist

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class Arpeggiator    : public Component
{
public:
    Arpeggiator(SeniorProjectVstAudioProcessor&);
    ~Arpeggiator();

    void paint (Graphics&) override;
    void resized() override;

private:
	//controls
	ToggleButton enableSwitch;
	ComboBox patternMenu;
	Slider speedSlider;

	//values for controls
	ScopedPointer<AudioProcessorValueTreeState::ButtonAttachment> enableVal;
	ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> patternVal;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> speedVal;

	//labels
	Label enableLabel;
	Label patternLabel;
	Label speedLabel;

	//reference to processor
	SeniorProjectVstAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Arpeggiator)
};

/*
  ==============================================================================

    Filter.h
    Created: 14 Aug 2018 3:15:37pm
    Author:  Jackson Crist

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"


//==============================================================================
/*
*/
class Filter    : public Component
{
public:
    Filter(SeniorProjectVstAudioProcessor&);
    ~Filter();

    void paint (Graphics&) override;
    void resized() override;

private:
	//controls
	Slider filterCutoff;
	Slider filterResonance;

	ComboBox filterMenu;

	//labels
	Label cutoffLabel;
	Label resonanceLabel;
	Label menuLabel;

	//control values
	ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> filterTypeVal;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> filterVal;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> resVal;

    //processor reference
	SeniorProjectVstAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Filter)
};

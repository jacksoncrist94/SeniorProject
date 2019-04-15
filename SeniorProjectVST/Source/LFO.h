/*
  ==============================================================================

    LFO.h
    Created: 17 Aug 2018 9:51:21am
    Author:  Jackson Crist

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class LFO    : public Component
{
public:
    LFO(SeniorProjectVstAudioProcessor&);
    ~LFO();

    void paint (Graphics&) override;
    void resized() override;

private:
	//controls
	Slider lfoDepth;
	Slider lfoDepth2;
	Slider lfoFrequency;
	Slider lfoFrequency2;
	ComboBox lfoAssignMenu;
	ComboBox lfoAssignMenu2;

	//control values
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> depthVal;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> depthVal2;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> freqVal;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> freqVal2;
	ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> assignVal;
	ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> assignVal2;

	//labels
	Label depthLabel;
	Label depthLabel2;
	Label freqLabel;
	Label freqLabel2;
	Label assignLabel;
	Label assignLabel2;

	//processor reference
	SeniorProjectVstAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LFO)
};

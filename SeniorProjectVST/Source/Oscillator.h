/*
  ==============================================================================

    Oscillator.h
    Created: 13 Aug 2018 1:53:42pm
    Author:  Jackson Crist

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class Oscillator    : public Component
{
public:
    Oscillator(SeniorProjectVstAudioProcessor&);
    ~Oscillator();

    void paint (Graphics&) override;
    void resized() override;
private:
	ComboBox oscMenu;

	Label oscLabel;

	ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> waveSelection;

	SeniorProjectVstAudioProcessor& processor;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Oscillator)
};

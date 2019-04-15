/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
SeniorProjectVstAudioProcessorEditor::SeniorProjectVstAudioProcessorEditor (SeniorProjectVstAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p), oscGui(p), envGui(p), filGui(p), lfoGui(p), arpGui(p)
{
	//size of entire plugin
    setSize(600, 400);

	//add gui for each component
	addAndMakeVisible(&oscGui);
	addAndMakeVisible(&envGui);
	addAndMakeVisible(&filGui);
	addAndMakeVisible(&lfoGui);
	addAndMakeVisible(&arpGui);
}

SeniorProjectVstAudioProcessorEditor::~SeniorProjectVstAudioProcessorEditor()
{
}

//==============================================================================
void SeniorProjectVstAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}

void SeniorProjectVstAudioProcessorEditor::resized()
{
	//set bounds and placement for all component guis
	juce::Rectangle<int> area = getLocalBounds();

	const int componentWidth = 200;
	const int componentHeight = 200;

	oscGui.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
	envGui.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
	filGui.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));

	area = getLocalBounds();

	lfoGui.setBounds(area.removeFromLeft(componentWidth * 2).removeFromBottom(componentHeight));
	arpGui.setBounds(area.removeFromLeft(componentWidth * 2).removeFromBottom(componentHeight));
 
}

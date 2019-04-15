/*
  ==============================================================================

    LFO.cpp
    Created: 17 Aug 2018 9:51:21am
    Author:  Jackson Crist

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "LFO.h"

//==============================================================================
LFO::LFO(SeniorProjectVstAudioProcessor& p) : 
	processor(p)
{
	//component size
	setSize(400, 200);

	//slider properties
	lfoDepth.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	lfoDepth.setRange(0.0, 0.5);
	lfoDepth.setValue(0.0);
	lfoDepth.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	lfoDepth.setColour(Slider::ColourIds::rotarySliderFillColourId, Colours::white);
	depthLabel.setText("Depth", NotificationType::dontSendNotification);
	depthLabel.setJustificationType(Justification::centred);
	depthLabel.attachToComponent(&lfoDepth, false);
	addAndMakeVisible(&lfoDepth);
	addAndMakeVisible(&depthLabel);
	//link to processor value
	depthVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "lfoDepth", lfoDepth);

	//slider properties
	lfoDepth2.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	lfoDepth2.setRange(0.0, 0.5);
	lfoDepth2.setValue(0.0);
	lfoDepth2.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	lfoDepth2.setColour(Slider::ColourIds::rotarySliderFillColourId, Colours::white);
	depthLabel2.setText("Depth", NotificationType::dontSendNotification);
	depthLabel2.setJustificationType(Justification::centred);
	depthLabel2.attachToComponent(&lfoDepth2, false);
	addAndMakeVisible(&lfoDepth2);
	addAndMakeVisible(&depthLabel2);
	//link to processor value
	depthVal2 = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "lfoDepth2", lfoDepth2);

	//slider properties
	lfoFrequency.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	lfoFrequency.setRange(1.0, 20.0);
	lfoFrequency.setValue(1.0);
	lfoFrequency.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	lfoFrequency.setColour(Slider::ColourIds::rotarySliderFillColourId, Colours::white);
	freqLabel.setText("Freq", NotificationType::dontSendNotification);
	freqLabel.setJustificationType(Justification::centred);
	freqLabel.attachToComponent(&lfoFrequency, false);
	addAndMakeVisible(&lfoFrequency);
	addAndMakeVisible(&freqLabel);
	//link to processor value
	freqVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "lfoFreq", lfoFrequency);
	//skew controls, increments slower in first half
	lfoFrequency.setSkewFactorFromMidPoint(5.0);

	//slider properties
	lfoFrequency2.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	lfoFrequency2.setRange(1.0, 20.0);
	lfoFrequency2.setValue(1.0);
	lfoFrequency2.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	lfoFrequency2.setColour(Slider::ColourIds::rotarySliderFillColourId, Colours::white);
	freqLabel2.setText("Freq", NotificationType::dontSendNotification);
	freqLabel2.setJustificationType(Justification::centred);
	freqLabel2.attachToComponent(&lfoFrequency2, false);
	addAndMakeVisible(&lfoFrequency2);
	addAndMakeVisible(&freqLabel2);
	//link to processor value
	freqVal2 = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "lfoFreq2", lfoFrequency2);
	//skew controls, increments slower in first half
	lfoFrequency2.setSkewFactorFromMidPoint(5.0);

	//menu properties
	lfoAssignMenu.addItem("Pitch", 1);
	lfoAssignMenu.addItem("Volume", 2);
	lfoAssignMenu.addItem("Cutoff", 3);
	lfoAssignMenu.setJustificationType(Justification::centred);
	assignLabel.setText("Assign to:", NotificationType::dontSendNotification);
	assignLabel.setJustificationType(Justification::centred);
	assignLabel.attachToComponent(&lfoAssignMenu, false);
	addAndMakeVisible(&lfoAssignMenu);
	addAndMakeVisible(&assignLabel);
	//link to processor value
	assignVal = new AudioProcessorValueTreeState::ComboBoxAttachment(processor.tree, "lfoAssign", lfoAssignMenu);

	//menu properties
	lfoAssignMenu2.addItem("Pitch", 1);
	lfoAssignMenu2.addItem("Volume", 2);
	lfoAssignMenu2.addItem("Cutoff", 3);
	lfoAssignMenu2.setJustificationType(Justification::centred);
	assignLabel2.setText("Assign to:", NotificationType::dontSendNotification);
	assignLabel2.setJustificationType(Justification::centred);
	assignLabel2.attachToComponent(&lfoAssignMenu2, false);
	addAndMakeVisible(&lfoAssignMenu2);
	addAndMakeVisible(&assignLabel2);
	//link to processor value
	assignVal2 = new AudioProcessorValueTreeState::ComboBoxAttachment(processor.tree, "lfoAssign2", lfoAssignMenu2);
}

LFO::~LFO()
{
}

void LFO::paint (Graphics& g)
{
	//color background
	g.fillAll(Colours::darkblue);
	//draw outline
	g.setColour(Colours::white);
	float xPos = 10.0, yPos = 10.0;
	float height = getLocalBounds().reduced(10).getHeight();
	float width = getLocalBounds().reduced(10).getWidth();
	float cornerSize = 10.0;
	float thicc = 3.0;
	g.drawRoundedRectangle(xPos, yPos, width, height, cornerSize, thicc);
	//draw text
	g.setFont((float(20.0)));
	g.drawText("LFO", 15, 15, getLocalBounds().reduced(15).getWidth(), getLocalBounds().reduced(15).getHeight(), Justification::bottomLeft, true);
}

void LFO::resized()
{
	//creates a rectangle for each set of lfo controls
	juce::Rectangle<int> area = getLocalBounds();
	juce::Rectangle<int> area2 = area.removeFromRight(200);
	area = area.reduced(40);
	area2 = area2.reduced(40);

	//set bounds for controls
	lfoAssignMenu.setBounds(area.removeFromTop(20));
	lfoDepth.setBounds(30, 100, 70, 70);
	lfoFrequency.setBounds(100, 100, 70, 70);

	lfoAssignMenu2.setBounds(area2.removeFromTop(20));
	lfoDepth2.setBounds(230, 100, 70, 70);
	lfoFrequency2.setBounds(300, 100, 70, 70);
}

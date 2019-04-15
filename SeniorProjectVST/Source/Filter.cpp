/*
  ==============================================================================

    Filter.cpp
    Created: 14 Aug 2018 3:15:37pm
    Author:  Jackson Crist

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Filter.h"

//==============================================================================
Filter::Filter(SeniorProjectVstAudioProcessor& p) :
processor(p)
{
	//component size
	setSize(200, 200);

	//menu properties
	filterMenu.addItem("Low Pass", 1);
	filterMenu.addItem("High Pass", 2);
	filterMenu.addItem("Band Pass", 3);
	filterMenu.setJustificationType(Justification::centred);
	menuLabel.setText("Filter Type:", NotificationType::dontSendNotification);
	menuLabel.setJustificationType(Justification::centred);
	menuLabel.attachToComponent(&filterMenu, false);
	addAndMakeVisible(&filterMenu);
	addAndMakeVisible(&menuLabel);
	//link to processor value
	filterTypeVal = new AudioProcessorValueTreeState::ComboBoxAttachment(processor.tree, "filterType", filterMenu);

	//slider properties
	filterCutoff.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	filterCutoff.setRange(20.0, 10000.0);
	filterCutoff.setValue(400.0);
	filterCutoff.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	filterCutoff.setColour(Slider::ColourIds::rotarySliderFillColourId, Colours::white);
	cutoffLabel.setText("Cut", NotificationType::dontSendNotification);
	cutoffLabel.setJustificationType(Justification::centred);
	cutoffLabel.attachToComponent(&filterCutoff, false);
	addAndMakeVisible(&filterCutoff);
	addAndMakeVisible(&cutoffLabel);
	//link to processor value
	filterVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "filterCutoff", filterCutoff);
	//skew controls, increments slower in first half
	filterCutoff.setSkewFactorFromMidPoint(1000.0);
	
	//slider properties
	filterResonance.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	filterResonance.setRange(1, 50);
	filterResonance.setValue(1);
	filterResonance.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	filterResonance.setColour(Slider::ColourIds::rotarySliderFillColourId, Colours::white);
	resonanceLabel.setText("Res", NotificationType::dontSendNotification);
	resonanceLabel.setJustificationType(Justification::centred);
	resonanceLabel.attachToComponent(&filterResonance, false);
	addAndMakeVisible(&filterResonance);
	addAndMakeVisible(&resonanceLabel);
	//link to processor value
	resVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "filterRes", filterResonance);
}

Filter::~Filter()
{
}

void Filter::paint (Graphics& g)
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
	g.drawText("Filter", 15, 15, getLocalBounds().reduced(15).getWidth(), getLocalBounds().reduced(15).getHeight(), Justification::bottomLeft, true);
}

void Filter::resized()
{
	//set control bounds
	juce::Rectangle<int> area = getLocalBounds().reduced(40);

	filterMenu.setBounds(area.removeFromTop(20));
	filterCutoff.setBounds(30, 100, 70, 70);
	filterResonance.setBounds(100, 100, 70, 70);
}

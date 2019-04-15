/*
  ==============================================================================

    Envelope.cpp
    Created: 13 Aug 2018 4:19:01pm
    Author:  Jackson Crist

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Envelope.h"

//==============================================================================
Envelope::Envelope(SeniorProjectVstAudioProcessor& p) :
	processor(p)
{
	//set component size
	setSize(200, 200);

	//slider properties
	attackSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
	attackSlider.setRange(0.1f, 9000.0f);
	attackSlider.setValue(0.1f);
	attackSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	attackSlider.setColour(Slider::ColourIds::trackColourId, Colours::white);
	attackLabel.setText("A", NotificationType::dontSendNotification);
	attackLabel.setJustificationType(Justification::centred);
	attackLabel.attachToComponent(&attackSlider, false);
	addAndMakeVisible(&attackSlider);
	addAndMakeVisible(&attackLabel);
	//link slider to processor value
	attackTree = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "attack", attackSlider);

	//slider properties
	decaySlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
	decaySlider.setRange(1.0f, 86000.0f);
	decaySlider.setValue(1.0f);
	decaySlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	decaySlider.setColour(Slider::ColourIds::trackColourId, Colours::white);
	decayLabel.setText("D", NotificationType::dontSendNotification);
	decayLabel.setJustificationType(Justification::centred);
	decayLabel.attachToComponent(&decaySlider, false);
	addAndMakeVisible(&decaySlider);
	addAndMakeVisible(&decayLabel);
	//link slider to processor value
	decayTree = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "decay", decaySlider);
	//skews controls, increments slower in first half
	decaySlider.setSkewFactorFromMidPoint(9000.f);

	//slider properties
	sustainSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
	sustainSlider.setRange(0.1f, 1.0f);
	sustainSlider.setValue(0.8f);
	sustainSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	sustainSlider.setColour(Slider::ColourIds::trackColourId, Colours::white);
	sustainLabel.setText("S", NotificationType::dontSendNotification);
	sustainLabel.setJustificationType(Justification::centred);
	sustainLabel.attachToComponent(&sustainSlider, false);
	addAndMakeVisible(&sustainSlider);
	addAndMakeVisible(&sustainLabel);
	//link slider to processor value
	sustainTree = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "sustain", sustainSlider);

	//slider properties
	releaseSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
	releaseSlider.setRange(0.1f, 46000.0f);
	releaseSlider.setValue(0.1f);
	releaseSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	releaseSlider.setColour(Slider::ColourIds::trackColourId, Colours::white);
	releaseLabel.setText("R", NotificationType::dontSendNotification);
	releaseLabel.setJustificationType(Justification::centred);
	releaseLabel.attachToComponent(&releaseSlider, false);
	addAndMakeVisible(&releaseSlider);
	addAndMakeVisible(&releaseLabel);
	//link slider to processor value
	releaseTree = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "release", releaseSlider);
	//skews controls, increments slower in first half
	releaseSlider.setSkewFactorFromMidPoint(9000.0f);


}

Envelope::~Envelope()
{
}

void Envelope::paint(Graphics& g)
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
	//draw component text
	g.setFont((float(20.0)));
	g.drawText("Envelope", 15, 15, getLocalBounds().reduced(15).getWidth(), getLocalBounds().reduced(15).getHeight(), Justification::bottomLeft, true);
}

void Envelope::resized()
{
	//set bounds for controls
	juce::Rectangle<int> area = getLocalBounds().reduced(40);

	attackSlider.setBounds(5, 50, 40, 100);
	decaySlider.setBounds(55, 50, 40, 100);
	sustainSlider.setBounds(105, 50, 40, 100);
	releaseSlider.setBounds(155, 50, 40, 100);
}

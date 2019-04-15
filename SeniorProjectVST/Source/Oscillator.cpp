/*
  ==============================================================================

    Oscillator.cpp
    Created: 13 Aug 2018 1:53:42pm
    Author:  Jackson Crist

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Oscillator.h"

//==============================================================================
Oscillator::Oscillator(SeniorProjectVstAudioProcessor& p) :
	processor(p)
{
	//component size
	setSize(200, 200);

	//menu properties
	oscMenu.addItem("Sine", 1);
	oscMenu.addItem("Saw", 2);
	oscMenu.addItem("Square", 3);
	oscMenu.addItem("Triangle", 4);
	oscMenu.addItem("Noise", 5);
	oscMenu.setJustificationType(Justification::centred);
	oscLabel.setText("Wave Type:", NotificationType::dontSendNotification);
	oscLabel.setJustificationType(Justification::centred);
	oscLabel.attachToComponent(&oscMenu, false);
	addAndMakeVisible(&oscMenu);
	addAndMakeVisible(&oscLabel);
	//link to processor value
	waveSelection = new AudioProcessorValueTreeState::ComboBoxAttachment(processor.tree, "wavetype", oscMenu);

}

Oscillator::~Oscillator()
{
}

void Oscillator::paint(Graphics& g)
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
	g.drawText("Oscillator", 15, 15, getLocalBounds().reduced(15).getWidth(), getLocalBounds().reduced(15).getHeight(), Justification::bottomLeft, true);

	//draw logo
	Font logoType;
	logoType.setTypefaceName("Mars Police");
	logoType.setTypefaceStyle("Italic");
	logoType.setHeight((float(60.0)));
	g.setFont(logoType);
	g.drawText("ISS", getLocalBounds(), Justification::centred, true);
	g.setFont((float(18.0)));
	g.drawText("InterStella Synth", 0, 135, 200, 20, Justification::centredTop, true);
}

void Oscillator::resized()
{
	//set bounds for controls
	juce::Rectangle<int> area = getLocalBounds().reduced(40);

	oscMenu.setBounds(area.removeFromTop(25));
}


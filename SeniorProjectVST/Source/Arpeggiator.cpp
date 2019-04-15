/*
  ==============================================================================

    Arpeggiator.cpp
    Created: 17 Aug 2018 5:17:47pm
    Author:  Jackson Crist

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Arpeggiator.h"

//==============================================================================
Arpeggiator::Arpeggiator(SeniorProjectVstAudioProcessor& p) : 
	processor(p)
{
	//Set component size
	setSize(200, 200);

	//Setup arp On/Off toggle button properties
	enableSwitch.setToggleState(false, NotificationType::dontSendNotification);
	enableLabel.setText("On:", NotificationType::dontSendNotification);
	enableLabel.setJustificationType(Justification::centredLeft);
	enableLabel.attachToComponent(&enableSwitch, false);
	addAndMakeVisible(&enableSwitch);
	addAndMakeVisible(&enableLabel);
	//Link button to value in processor
	enableVal = new AudioProcessorValueTreeState::ButtonAttachment(processor.tree, "arpOn", enableSwitch);

	//Setup arp pattern menu properties
	patternMenu.addItem("Up", 1);
	patternMenu.addItem("Down", 2);
	patternMenu.addItem("Up/Down", 3);
	patternMenu.setJustificationType(Justification::centred);
	patternLabel.setText("Pattern:", NotificationType::dontSendNotification);
	patternLabel.setJustificationType(Justification::centred);
	patternLabel.attachToComponent(&patternMenu, false);
	addAndMakeVisible(&patternMenu);
	addAndMakeVisible(&patternLabel);
	//Link menu to value in processor
	patternVal = new AudioProcessorValueTreeState::ComboBoxAttachment(processor.tree, "arpPattern", patternMenu);

	//Setup arp speed slider properties
	speedSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	speedSlider.setRange(0.0f, 1.0f);
	//speedSlider.setValue(0.5f);
	speedSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	speedSlider.setColour(Slider::ColourIds::rotarySliderFillColourId, Colours::white);
	speedLabel.setText("Speed", NotificationType::dontSendNotification);
	speedLabel.setJustificationType(Justification::centred);
	speedLabel.attachToComponent(&speedSlider, false);
	addAndMakeVisible(&speedSlider);
	addAndMakeVisible(&speedLabel);
	//Link slider to value in processor
	speedVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "arpSpeed", speedSlider);
}

Arpeggiator::~Arpeggiator()
{
}

void Arpeggiator::paint (Graphics& g)
{
	//Colour background
	g.fillAll(Colours::darkblue);
	//Draw outline
	g.setColour(Colours::white);
	float xPos = 10.0, yPos = 10.0;
	float height = getLocalBounds().reduced(10).getHeight();
	float width = getLocalBounds().reduced(10).getWidth();
	float cornerSize = 10.0;
	float thicc = 3.0;
	g.drawRoundedRectangle(xPos, yPos, width, height, cornerSize, thicc);
	//Draw component label
	g.setFont((float(20.0)));
	g.drawText("Arpeggiator", 15, 15, getLocalBounds().reduced(15).getWidth(), getLocalBounds().reduced(15).getHeight(), Justification::bottomLeft, true);
}

void Arpeggiator::resized()
{
	//set sizes for controls
	juce::Rectangle<int> area = getLocalBounds().reduced(40);

	patternMenu.setBounds(area.removeFromTop(20));
	enableSwitch.setBounds(50, 100, 30, 50);
	speedSlider.setBounds(100, 100, 70, 70);

}

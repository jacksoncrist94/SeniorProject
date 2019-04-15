/*
  ==============================================================================

    SynthVoice.h
    Created: 22 Jul 2018 3:13:46pm
    Author:  Jackson Crist

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthSound.h"
#include "maximilian.h"

class SynthVoice : public SynthesiserVoice
{
public:
	bool canPlaySound (SynthesiserSound* sound)
	{
		return dynamic_cast<SynthSound*>(sound) != nullptr;
	}

	void getEnvelopeParams(float* attack, float* decay, float* sustain, float* release)
	{
		env1.setAttack(double(*attack));
		env1.setDecay(double(*decay));
		env1.setSustain(double(*sustain));
		env1.setRelease(double(*release));
		
	}

	double setEnvelope()
	{
		return env1.adsr(setOscType(), env1.trigger);
	}

	void getOscType(float* selection) 
	{
		waveIndex = *selection;
	}

	double setOscType()
	{
		if (waveIndex == 0) {
			return osc1.sinewave(frequency * setPitchLfo());
		}
		else if (waveIndex == 1) {
			return osc1.saw(frequency * setPitchLfo());
		}
		else if (waveIndex == 2) {
			return osc1.square(frequency * setPitchLfo());
		}
		else if (waveIndex == 3) {
			return osc1.triangle(frequency * setPitchLfo());
		}
		else if (waveIndex == 4) {
			return osc1.noise();
		}
		else {
			return osc1.sinewave(frequency * setPitchLfo());
		}
	}

	void getLfoParams(float* dest, float* depth, float* freq, float* dest2, float* depth2, float* freq2)
	{
		lfoDest = *dest;
		lfoDepth = *depth;
		lfoFreq = *freq;

		lfoDest2 = *dest2;
		lfoDepth2 = *depth2;
		lfoFreq2 = *freq2;
	}

	//returns value to multiply to osc frequency
	double setPitchLfo()
	{
		//all lfo functions work kinda like FizzBuzz
		double lfoSignal = 1;

		if (lfoDest == 0) {
			dcOffset = 1.0 - lfoDepth;
			lfoSignal *= (dcOffset + (lfoDepth * lfo1.sinewave(lfoFreq)));
		}

		if (lfoDest2 == 0) {
			dcOffset2 = 1.0 - lfoDepth2;
			lfoSignal *= (dcOffset2 + (lfoDepth2 * lfo2.sinewave(lfoFreq2)));
		}

		return lfoSignal;
	}

	//returns value to multiply to envelope signal
	double setVolumeLfo()
	{
		double lfoSignal = 1;

		if (lfoDest == 1) {
			dcOffset = 1.0 - lfoDepth;
			lfoSignal *= (dcOffset + (lfoDepth * lfo1.sinewave(lfoFreq)));
		}

		if (lfoDest2 == 1) {
			dcOffset2 = 1.0 - lfoDepth2;
			lfoSignal *= (dcOffset2 + (lfoDepth2 * lfo2.sinewave(lfoFreq2)));
		}

		return lfoSignal;
	}

	void startNote (int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition)
	{
		env1.trigger = 1;
		level = velocity;
		frequency = MidiMessage::getMidiNoteInHertz(midiNoteNumber - 2);
		//had to add the minus two to account for some weird off-key nonsense
		//kinda hacky, but hey
		//std::cout << midiNoteNumber << std::endl;
	}

	void stopNote (float velocity, bool allowTailOff)
	{
		env1.trigger = 0;
		allowTailOff = true;

		if (velocity == 0) {
			clearCurrentNote();
		}
	}

	void pitchWheelMoved (int newPitchWheelValue)
	{

	}

	void controllerMoved(int controllerNumber, int newControllerValue) 
	{

	}

	void renderNextBlock(AudioBuffer<float> &outputBuffer, int startSample, int numSamples)
	{
		
		for (int sample = 0; sample < numSamples; ++sample)
		{
			

			for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
			{

				outputBuffer.addSample(channel, startSample, setEnvelope() * setVolumeLfo() * 0.3f);
			}

			++startSample;
		}
	}

private:
	double level;
	double frequency;

	int waveIndex;

	int lfoDest;
	int lfoDest2;
	double lfoDepth;
	double lfoDepth2;
	double lfoFreq;
	double lfoFreq2;
	double dcOffset;
	double dcOffset2;

	maxiOsc osc1;
	maxiEnv env1;
	maxiOsc lfo1;
	maxiOsc lfo2;
	
};
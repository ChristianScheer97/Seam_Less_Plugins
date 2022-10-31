/*
  ==============================================================================

    SendFaderBox.h
    Created: 31 Mar 2021 12:13:37am
    Author:  anwaldt

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "../../Common/SeamLess.h"
#include "PluginProcessor.h"

#include "ReverbFader.h"


//==============================================================================
/*
*/
class ReverbFaderBox  : public juce::Component, juce::Slider::Listener
{
public:

    ReverbFaderBox(SeamLess_MainAudioProcessor &p, juce::AudioProcessorValueTreeState &apvts);
    /** @cond PRIVATE */
    ~ReverbFaderBox() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void sliderValueChanged (juce::Slider* slider) override;
    /** @endcond */

private:

    SeamLess_MainAudioProcessor& audioProcessor;
    juce::AudioProcessorValueTreeState& treeState;

    ReverbFader revGainFader;
    ReverbFader revFreq1Fader;
    ReverbFader revFreq2Fader;
    ReverbFader revRdelFader;
    ReverbFader revRgxyzFader;
    ReverbFader revT60dcFader;
    ReverbFader revT60mFader;
    ReverbFader revLpFreqFader;
    ReverbFader revLpRsFader;
    ReverbFader revLpDbFader;

    ReverbFader* faders[10] = { &revGainFader, &revFreq1Fader, &revFreq2Fader, &revRdelFader, &revRgxyzFader, &revT60dcFader, &revT60mFader, &revLpFreqFader, &revLpRsFader, &revLpDbFader};

    //    SendFader sendFaderLFE;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ReverbFaderBox)
};

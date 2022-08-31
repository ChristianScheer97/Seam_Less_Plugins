/*
==============================================================================

This file contains the basic framework code for a JUCE plugin processor.

==============================================================================
*/

#pragma once

// forward declaration
class ClientConnection;

#include <JuceHeader.h>

#include "../../Common/SeamLess.h"
#include "ClientConnection.h"


//==============================================================================
/**
*/

class SeamLess_ClientAudioProcessor  : public juce::AudioProcessor,
        juce::AudioProcessorValueTreeState::Listener, juce::HighResolutionTimer
{
public:
    //==============================================================================
    SeamLess_ClientAudioProcessor();
    ~SeamLess_ClientAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;


    float getXPos();
    float getYPos();
    float getZPos();

    void setXPos(float in);
    void setYPos(float in);
    void setZPos(float in);
    /*
    void xPosSend();
    void yPosSend();
    void zPosSend();
    */
    void xyzPosSend();

    ///
    /// \brief sendGainSend
    /// \param id The string identifier for the send channel.
    /// \param in The gain value.
    /// Send OSC messages for the send gains!
    void sendGainSend();

    //==============================================================================

    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    juce::AudioProcessorValueTreeState::ParameterLayout createParameters();


    void setSendGain(int sendIndex, float in);

    void setSourceIndex(int i);
    int getSourceIndex();

    void setOscTargetAddress(juce::String address);
    void setOscTargetPort(int port);

    juce::String  getOscTargetAddress();
    int getOscTargetPort();

    bool getConnectedToMain();
    void setConnectedToMain(bool b);

    bool getSendState();
    void setSendState(bool s);

    virtual void parameterChanged(const juce::String & id, float val) override;
    juce::AudioProcessorValueTreeState& getState();


private:

    // for the inter com
    const int port_nr = 52713;

    bool connectedToMain = false;

    // IP address and port are used by all instances
    juce::Value oscTargetAddress;
    juce::Value oscTargetPort;
    juce::Value sourceIdx;

    // used to detect play-state
    juce::AudioPlayHead::CurrentPositionInfo playInfo;

    // manual send state (used by all instances):
    static bool isSending;
    // play state depending (used by all instances):
    static bool playSending;

    /// \brief sender1
    /// @todo Make it non static!
    static juce::OSCSender sender1;

    // Use atomic parameters for thread-safety
    std::atomic<float>* xPos = nullptr;
    std::atomic<float>* yPos = nullptr;
    std::atomic<float>* zPos = nullptr;
    

    std::atomic<float>* sendGainWFS = nullptr;
    std::atomic<float>* sendGainHOA = nullptr;
    std::atomic<float>* sendGainREV = nullptr;
    std::atomic<float>* sendGainLFE = nullptr;


    //juce::AudioParameterInt* sourceIdx;

    // The AudioProcessorValueTreeState connects parameters to the GUI
    // and manages serialization
    juce::AudioProcessorValueTreeState parameters;
    juce::ValueTree settings;

    // std::unique_ptr<ClientConnection> client;    // no longer needed due to parameterAttachments

    virtual void hiResTimerCallback() override;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SeamLess_ClientAudioProcessor)


};

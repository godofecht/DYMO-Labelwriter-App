/*
  ==============================================================================

    General Label Component.h
    Created: 12 Aug 2023 8:42:54am
    Author:  Abhishek Shivakumar

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "TextAggregatorComponent.h"

class GeneralLabelComponent : public TextAggregatorComponent
{
    juce::TextEditor largeEditor;
    
public:
    
    GeneralLabelComponent()
    {
        addAndMakeVisible (largeEditor);
        largeEditor.onTextChange = [&]() {updateLabelPreview(); };
    }
    
    juce::String getTextAggregate() override
    {
        juce::String text = largeEditor.getText();
        return text;
    }
    
    void paint (juce::Graphics& g) override
    {
        g.drawSingleLineText ("Enter text for label:", 0, 0);
    }
    
    void resized() override
    {
        largeEditor.setBounds           (0, 0, getWidth(), 200);
        labelPreviewComponent.setBounds (0, 200, getWidth(), 200);
        printButton.setBounds           (0, 400, getWidth(), 100);
    }
};

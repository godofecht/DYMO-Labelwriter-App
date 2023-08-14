/*
  ==============================================================================

    NameBadgeComponent.h
    Created: 12 Aug 2023 8:42:38am
    Author:  Abhishek Shivakumar

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "TextAggregatorComponent.h"

class NameBadgeComponent : public TextAggregatorComponent
{
    juce::TextEditor nameEditor;
    juce::TextEditor commentEditor;
public:
    NameBadgeComponent()
    {
        addAndMakeVisible (printButton);
        addAndMakeVisible (nameEditor);
        addAndMakeVisible (commentEditor);

        nameEditor.onTextChange = [&]() { updateLabelPreview(); };
        commentEditor.onTextChange = [&]() { updateLabelPreview(); };
    }
    
    juce::String getTextAggregate() override
    {
        juce::String text = nameEditor.getText();
        juce::String commentText = commentEditor.getText();
        
        if (!commentText.isEmpty())
        {
            text += " " + commentText;
        }
        return text;
    }
    
    void paint (juce::Graphics& g) override
    {
        
    }
    
    //TODO: When editor is filled in, generate preview
    
    void resized() override
    {
        nameEditor.setBounds            (200, 0, getWidth() - 200, 50);
        commentEditor.setBounds         (200, 50, getWidth() - 200, 50);
        labelPreviewComponent.setBounds (0, 100, getWidth(), 200);
        printButton.setBounds           (0, 300, getWidth(), 100);
    }
};

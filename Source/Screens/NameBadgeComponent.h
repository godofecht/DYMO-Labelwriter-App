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
    LabelledFormField nameField { "Name" };
    LabelledFormField commentField { "Comments" };

public:
    NameBadgeComponent()
    {
        addAndMakeVisible(nameField);
        addAndMakeVisible(commentField);
        
        nameField.setTextChangeCallback([&]() { updateLabelPreview(); });
        commentField.setTextChangeCallback([&]() { updateLabelPreview(); });
    }
    
    juce::String getTextAggregate() override
    {
        juce::String text = nameField.getText().quoted();
        juce::String commentText = commentField.getText();
        
        if (!commentText.isEmpty())
        {
            text += " " + commentText;
        }
        return text;
    }
    
    void resized() override
    {
        auto area = getLocalBounds();
        
        nameField.setBounds(area.removeFromTop(50));
        commentField.setBounds(area.removeFromTop(50));
        
        labelPreviewComponent.setBounds(area.removeFromTop(200));
        printButton.setBounds(area.removeFromTop(100));
    }
};

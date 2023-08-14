/*
  ==============================================================================

    TextAggregatorComponent.h
    Created: 12 Aug 2023 10:31:15am
    Author:  Abhishek Shivakumar

  ==============================================================================
*/

#pragma once
#include "LabelPreviewComponent.h"

class TextAggregatorComponent : public juce::Component
{

public:
    LabelPreviewComponent labelPreviewComponent;
    juce::TextButton printButton {"print"};
    
    TextAggregatorComponent()
    {
        addAndMakeVisible (labelPreviewComponent);
        addAndMakeVisible (printButton);
        labelPreviewComponent.setLines();
        
        printButton.onClick = [&]()
        {
            juce::Image previewImage = labelPreviewComponent.getPreview();
            labelPreviewComponent.startPrintOperation (previewImage, "/Users/abhishekshivakumar/Downloads/pnglabel.png");
        };
    }
    
    void updateLabelPreview()
    {
        auto text = getTextAggregate();
        if (text.isNotEmpty())
            labelPreviewComponent.setLines (text);
        else
        {
            labelPreviewComponent.reset();
        }
    }
    
    virtual juce::String getTextAggregate()
    {
        juce::String text = "";
        return text;
    }
};

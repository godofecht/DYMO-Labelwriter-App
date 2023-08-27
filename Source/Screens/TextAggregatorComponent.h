/*
  ==============================================================================

    TextAggregatorComponent.h
    Created: 12 Aug 2023 10:31:15am
    Author:  Abhishek Shivakumar

  ==============================================================================
*/

#pragma once
#include "LabelPreviewComponent.h"

class FormField : public juce::TextEditor
{
public:
    
    FormField () : juce::TextEditor()
    {
        setFont (50.0f);
    }
};

class LabelledFormField : public juce::Component
{
    juce::Label label;
    FormField field;

public:
    LabelledFormField(const juce::String& labelText, const juce::String& initialText = "")
    {
        label.setText(labelText, juce::dontSendNotification);
        field.setText(initialText);
        
        addAndMakeVisible(label);
        addAndMakeVisible(field);
    }
    
    void resized() override
    {
        auto area = getLocalBounds();
        
        label.setBounds(area.removeFromLeft(200));
        field.setBounds(area);
    }
    
    juce::String getText() const
    {
        return field.getText();
    }
    
    void setText (juce::String text)
    {
        field.setText (text);
    }
    
    void setTextChangeCallback(std::function<void()> callback)
    {
        field.onTextChange = callback;
    }
};

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

/*
  ==============================================================================

    StorageLabelComponent.h
    Created: 12 Aug 2023 8:42:46am
    Author:  Abhishek Shivakumar

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "TextAggregatorComponent.h"

class StorageLabelComponent : public TextAggregatorComponent
{
    juce::TextButton printButton {"print"};
    
    juce::TextEditor nameEditor;
    juce::TextEditor contactEditor;
    juce::TextEditor useByEditor;
    
    juce::TextButton oneMonthButton;
    juce::TextButton threeMonthsButton;
    
public:
    StorageLabelComponent()
    {
        addAndMakeVisible (printButton);
        addAndMakeVisible (nameEditor);
        addAndMakeVisible (contactEditor);
        addAndMakeVisible (useByEditor);
        addAndMakeVisible (oneMonthButton);
        addAndMakeVisible (threeMonthsButton);
        addAndMakeVisible (labelPreviewComponent);
        
        oneMonthButton.onClick = [&]
        {
            juce::String useByText = getDateAfterNumMonthsAsString (1);
            useByEditor.setText (useByText);
            updateLabelPreview();
        };
        
        threeMonthsButton.onClick = [&]
        {
            juce::String useByText = getDateAfterNumMonthsAsString (3);
            useByEditor.setText (useByText);
            updateLabelPreview();
        };
        
        nameEditor.onTextChange = [&]() {updateLabelPreview();};
        contactEditor.onTextChange = [&]() {updateLabelPreview();};
        useByEditor.onTextChange = [&]() {updateLabelPreview();};
        
    }
    
    juce::String getDateAfterNumMonthsAsString (int numMonths)
    {
        // Get the current date and time
        juce::Time currentTime = juce::Time::getCurrentTime();

        // Calculate the new month and year
        int newMonth = (currentTime.getMonth() + numMonths) % 12;
        int newYear = currentTime.getYear() + (currentTime.getMonth() + numMonths) / 12;

        // Handle the case where adding months results in December of the previous year
        if (newMonth == 0)
        {
            newMonth = 12;
            newYear -= 1;
        }

        // Create a new Time object with the adjusted month and year
        juce::Time newTime(newYear, newMonth, currentTime.getDayOfMonth(),
                           currentTime.getHours(), currentTime.getMinutes(),
                           currentTime.getSeconds(), currentTime.getMilliseconds());

        // Convert the Time object to a string and return
        return newTime.toString(true, false, false, true); // Returns date in the format "YYYY-MM-DD"
    }
    
    juce::String getTextAggregate() override
    {
        juce::String text = nameEditor.getText() + " " + contactEditor.getText() + " " + useByEditor.getText();
        return text;
    }
    
    //TODO: When editor is filled in, generate preview
    
    void resized() override
    {
        nameEditor.setBounds            (200, 0, getWidth() - 200, 50);
        contactEditor.setBounds         (200, 50, getWidth() - 200, 50);
        useByEditor.setBounds         (200, 100, getWidth() - 200, 50);
        
        labelPreviewComponent.setBounds (0, 150, getWidth(), 200);
        printButton.setBounds           (0, 350, getWidth(), 100);
    }
};

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
    
    LabelledFormField nameField { "Name" };
    LabelledFormField contactField { "Contact" };
    LabelledFormField useByField { "Use By" };
    
    juce::TextButton oneMonthButton {"1 Month"};
    juce::TextButton threeMonthsButton {"3 Months"};
    
public:
    StorageLabelComponent()
    {
        addAndMakeVisible(printButton);
        addAndMakeVisible(nameField);
        addAndMakeVisible(contactField);
        addAndMakeVisible(useByField);
        addAndMakeVisible(oneMonthButton);
        addAndMakeVisible(threeMonthsButton);
        
        oneMonthButton.onClick = [&]
        {
            useByField.setText (getDateAfterNumMonthsAsString(1));
            updateLabelPreview();
        };
        
        threeMonthsButton.onClick = [&]
        {
            useByField.setText(getDateAfterNumMonthsAsString(3));
            updateLabelPreview();
        };
        
        nameField.setTextChangeCallback([&]() { updateLabelPreview(); });
        contactField.setTextChangeCallback([&]() { updateLabelPreview(); });
        useByField.setTextChangeCallback([&]() { updateLabelPreview(); });
    }

    juce::String getDateAfterNumMonthsAsString(int numMonths)
    {
        juce::Time currentTime = juce::Time::getCurrentTime();
        int newMonth = (currentTime.getMonth() + numMonths) % 12;
        int newYear = currentTime.getYear() + (currentTime.getMonth() + numMonths) / 12;
        if (newMonth == 0)
        {
            newMonth = 12;
            newYear -= 1;
        }
        juce::Time newTime(newYear, newMonth, currentTime.getDayOfMonth(), currentTime.getHours(), currentTime.getMinutes(), currentTime.getSeconds(), currentTime.getMilliseconds());
        return newTime.toString(true, false, false, true);
    }
    
    juce::String getTextAggregate() override
    {
        return nameField.getText().quoted() + " " + contactField.getText() + " " + useByField.getText();
    }
    
    void resized() override
    {
        auto area = getLocalBounds();
        
        nameField.setBounds(area.removeFromTop(50));
        contactField.setBounds(area.removeFromTop(50));
        useByField.setBounds(area.removeFromTop(50));
        oneMonthButton.setBounds(area.removeFromTop(50));
        threeMonthsButton.setBounds(area.removeFromTop(50));
        
        labelPreviewComponent.setBounds(area.removeFromTop(200));
        printButton.setBounds(area.removeFromTop(100));
    }
};

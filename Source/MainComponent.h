#pragma once

#include <JuceHeader.h>
#include "Screens/TabManager.h"



class OldProgramLookAndFeel : public juce::LookAndFeel_V4
{
public:
    OldProgramLookAndFeel()
    {
        // Set your custom colors here
        backgroundColor = juce::Colour(40, 40, 40);
        textColor = juce::Colours::white;
        buttonColor = juce::Colour(0, 120, 215);
        buttonHoverColor = juce::Colour(0, 160, 255);
        editorBackgroundColor = juce::Colour(60, 60, 60);
    }

    void drawButtonBackground(juce::Graphics& g, juce::Button& button, const juce::Colour& backgroundColour,
                              bool isMouseOverButton, bool isButtonDown) override
    {
        juce::Colour color = button.getToggleState() ? buttonHoverColor : buttonColor;
        if (isButtonDown)
            color = color.darker(0.1f);
        else if (isMouseOverButton)
            color = color.brighter(0.1f);

        g.setColour(color);
        g.fillRoundedRectangle(button.getLocalBounds().toFloat(), 5.0f);
    }

    void drawButtonText(juce::Graphics& g, juce::TextButton& button, bool isMouseOverButton, bool isButtonDown) override
    {
        g.setColour(textColor);
        g.setFont (14.0f);

        juce::String text = button.getButtonText();
        g.drawText(text, button.getLocalBounds(), juce::Justification::centred, true);
    }

    void drawTextEditorOutline (juce::Graphics& g, int width, int height, juce::TextEditor& textEditor) override
    {
        g.setColour (textColor);
        g.drawRect (0, 0, width, height);
    }

    void fillTextEditorBackground (juce::Graphics& g, int width, int height, juce::TextEditor &textEditor) override
    {
        g.setColour (editorBackgroundColor);
        g.fillRect (textEditor.getLocalBounds());
    }
    
private:
    juce::Colour backgroundColor;
    juce::Colour textColor;
    juce::Colour buttonColor;
    juce::Colour buttonHoverColor;
    juce::Colour editorBackgroundColor;
};

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::Component
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
    TabManager labelMakerTabManager;
    
    OldProgramLookAndFeel oldProgramLookAndFeel;

private:
    //==============================================================================
    // Your private member variables go here...


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};

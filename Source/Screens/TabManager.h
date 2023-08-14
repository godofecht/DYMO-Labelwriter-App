/*
  ==============================================================================

    TabManager.h
    Created: 12 Aug 2023 8:44:20am
    Author:  Abhishek Shivakumar

  ==============================================================================
*/

#pragma once
#include "EditTagComponent.h"
#include "GeneralLabelComponent.h"
#include "NameBadgeComponent.h"
#include "StorageLabelComponent.h"

class TabManager : public juce::Component
{
    enum TabType { EDIT_TAG, GENERAL_LABEL, NAME_BADGE, STORAGE_LABEL };
    
    EditTagComponent editTagComponent;
    GeneralLabelComponent generalLabelComponent;
    NameBadgeComponent nameBadgeComponent;
    StorageLabelComponent storageLabelComponent;
    
    juce::OwnedArray<juce::Component> tabs;
    
    juce::TextButton editTabButton {"Edit Tag"}, generalLabelTabButton {"General Label"}, nameBadgeTabButton {"Name Badge"}, storageLabelTabButton {"Storage Label"};
public:
    
    TabManager()
    {
        tabs.add (&editTagComponent);
        tabs.add (&generalLabelComponent);
        tabs.add (&nameBadgeComponent);
        tabs.add (&storageLabelComponent);
        
        addAndMakeVisible (editTabButton);
        addAndMakeVisible (generalLabelTabButton);
        addAndMakeVisible (nameBadgeTabButton);
        addAndMakeVisible (storageLabelTabButton);
        
        addChildComponent (editTagComponent);
        addChildComponent (generalLabelComponent);
        addChildComponent (nameBadgeComponent);
        addChildComponent (storageLabelComponent);
    
        switchToTab (NAME_BADGE);
        
        editTabButton.onClick = [&]() {switchToTab (EDIT_TAG); };
        generalLabelTabButton.onClick = [&]() {switchToTab (GENERAL_LABEL); };
        nameBadgeTabButton.onClick = [&]() {switchToTab (NAME_BADGE); };
        storageLabelTabButton.onClick = [&]() {switchToTab (STORAGE_LABEL); };
    }
    
    void switchToTab (TabType tabType)
    {
        for (auto tabComponent : tabs)
        {
            tabComponent->setVisible (false);
        }
        tabs[tabType]->setVisible (true);
    }
    
    void resized() override
    {
        for (auto tab : tabs)
        {
            tab->setBounds (getBounds().translated (0, 50));
        }
        
        int tabWidth = getWidth() / 4.0f;
        nameBadgeTabButton.setBounds (0, 0, tabWidth, 50);
        editTabButton.setBounds (tabWidth, 0, tabWidth, 50);
        storageLabelTabButton.setBounds (tabWidth * 2, 0, tabWidth, 50);
        generalLabelTabButton.setBounds (tabWidth * 3, 0, tabWidth, 50);
    }
};

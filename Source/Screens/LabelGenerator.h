/*
  ==============================================================================

    LabelGenerator.h
    Created: 12 Aug 2023 9:27:35am
    Author:  Abhishek Shivakumar

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class LabelGenerator
{
public:
    struct LabelLine
    {
        juce::Font font;
        juce::StringArray line;
        std::vector<juce::Rectangle<int>> boxes;
        int height;

        LabelLine(const juce::Font& f, const juce::StringArray& l, const std::vector<juce::Rectangle<int>>& b)
            : font(f), line(l), boxes(b)
        {
            int min_y = std::numeric_limits<int>::max();
            int max_y = std::numeric_limits<int>::min();

            for (const auto& box : boxes)
            {
                min_y = std::min(min_y, box.getY());
                max_y = std::max(max_y, box.getBottom());
            }

            height = max_y - min_y;
        }
    };

    LabelGenerator (const juce::StringArray& lines, int dpi = 300, juce::Point<int> size_mm = {87, 35}) //560, 200 are our labelPreview dimensions
        : dpi(dpi), res(mmToPx(size_mm))
    {
        //    lines - a juce::StringArray containing the lines of text
        //    linePortions - a juce::Array containing the portion of the height of the TextBox each line should take up
        //    res - a juce::Point containing the resolution of the TextBox
        
        for (const auto& line : lines)
            this->lines.addArray (juce::StringArray::fromTokens (line, " ", ""));

        if (this->lines.size() <= linePortions.size())
        {
            auto portions = linePortions[this->lines.size() - 1];
            for (auto portion : portions)
                maxLineHeights.add(static_cast<int>(portion * res.y));
        }
        else
        {
            int maxHeight = static_cast<int>(1.0 / this->lines.size() * res.y);
            for (int i = 0; i < this->lines.size(); ++i)
                maxLineHeights.add(maxHeight);
        }

        baseFont = juce::Font("Arial", static_cast<float>(maxLineHeights[0]), juce::Font::plain);
        
        linePortions = {
            { 0.9 },
            { 0.7, 0.2 },
            { 0.5, 0.2, 0.2 }
        };
    }

    juce::Image generateImage()
    {
        //10 mm offset because HAX?
        //TODO: Get to the bottom of this. It's a code smell
        int numPixelsFor10mmOffset = 10.0 / 24.5 * dpi;
        juce::Image img (juce::Image::RGB, res.x, res.y, true);
        juce::Graphics g (img);
        g.drawRect (0, 0, res.x, res.y, 15);

        
        DBG ("Generating image at resolution: (" + juce::String (res.x) + ", " + juce::String (res.y) + ")");

        std::vector<LabelLine> lineParams;
        for (int i = 0; i < lines.size(); ++i)
            lineParams.push_back (chooseLineSize (i));

        int totalHeight = 0;
        for (const auto& lp : lineParams)
            totalHeight += lp.height;

        int spareHeight = res.y - totalHeight;
        DBG ("SpareHeight: " + juce::String (spareHeight));
        
        int lineGap = spareHeight / lines.size();

        int lineTop = lineGap / 2;
        
        int lineCount = 0;
        for (const auto& lp : lineParams)
        {
            int colWidth = res.x / lp.line.size();
            int x = 0;

            for (const auto& elem : lp.line)
            {
                g.setFont (lp.font);
                g.drawText (elem, x, lineTop, colWidth, lp.height, juce::Justification::centredTop);
                
                x += colWidth;
            }

            lineTop += lp.height + lineGap;
            DBG ("Generated line: " + juce::String (lineCount));
            lineCount++;
        }
        

        return img;
    }

private:
    int dpi;
    juce::Point<int> res;
    juce::StringArray lines;
    juce::Array<int> maxLineHeights;
    juce::Font baseFont;

    std::vector<std::vector<double>> linePortions;


    juce::Point<int> mmToPx(juce::Point<int> mm)
    {
        return { static_cast<int>((mm.x / 25.4) * dpi), static_cast<int>((mm.y / 25.4) * dpi) };
    }

    LabelLine chooseLineSize(int idx)
    {
        int size = maxLineHeights[idx];
        auto line = lines[idx];

        int maxElemWidth = res.x / line.length();
        int gapWidth = 4; // TODO: Adjust as needed

        juce::Font font = baseFont.withHeight(static_cast<float>(size));
        std::vector<juce::Rectangle<int>> boxes;

        for (auto p = line.getCharPointer(); !p.isEmpty(); ++p)
        {
            auto bbox = font.getStringWidth (p);
            if (bbox > maxElemWidth)
            {
                // Adjust font size or handle the overflow
                // This is a simplified approach, you might need to adjust based on your requirements
                font.setHeight(font.getHeight() * (static_cast<float>(maxElemWidth) / bbox));
                bbox = font.getStringWidth (p);
            }
            boxes.push_back(juce::Rectangle<int>(0, 0, bbox, static_cast<int>(font.getHeight())));
        }

        return LabelLine(font, line, boxes);
    }
};


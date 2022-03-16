/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.1.0

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-13 by Raw Material Software Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
#include "UiSettings.h"
#include "PluginProcessor.h"
#include "UiMainWindow.h"
//[/Headers]

#include "UiEditorAbout.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
void UiEditorAbout::on_close_clicked()
{
    _app_instance_store->editor_config.about_winodow = nullptr;
}
#ifndef B_STEP_STANDALONE
static bool is_au;
#endif

#ifdef DEVELOPMENT
#include "FileIO.h"
struct Parser : public Timer
{
    String complete_data;
    String new_data;
    TextEditor*const _editor;
    CriticalSection append_lock;

    bool print_to_file;
    const File logfile;

    void append( const String& data_ ) {
        append_lock.enter();
        new_data+="\n"+data_;
        append_lock.exit();
    }

    CriticalSection parse_lock;
    void timerCallback() override {
        if( append_lock.tryEnter() )
        {
            // CLEAN BUFFER
            String new_data_copy;
            if( new_data != "" )
            {
                new_data_copy = new_data;
                new_data = "";
                append_lock.exit();
            }
            else
            {
                append_lock.exit();
                return;
            }

            // PARSE NEW STUFF
            if( parse_lock.tryEnter() )
            {
                complete_data+=new_data_copy;

#define LOGSIZE 500000
                if( complete_data.length() > LOGSIZE )
                    complete_data = complete_data.substring( complete_data.length()-LOGSIZE, complete_data.length() );

                _editor->setText( complete_data );
                _editor->moveCaretToEnd();

                if( print_to_file )
                    logfile.appendText( new_data_copy );

                parse_lock.exit();
            }
        }
    }


    Parser( TextEditor* editor_ ) :_editor( editor_ ), logfile( get_app_folder().getChildFile("debug.txt") ), print_to_file(true) {
        if( ! AlertWindow::showOkCancelBox( AlertWindow::QuestionIcon, "DELETE OLD LOG FILE?", "Delete the old log file? Else add the new stuff at the bottom", "Keep and append", "Delete and create new" ) )
            logfile.deleteFile();

        if( ! AlertWindow::showOkCancelBox( AlertWindow::QuestionIcon, "WRITE TO DEBUG FILE?", "Default ON", "YES", "NO, JUST PARSE" ) )
            print_to_file = false;

        logfile.appendText( "\n\n\n---- NEW LOG SESSION ----\n\n\n" );

        startTimer(50);
    }

    ~Parser() {
        stopTimer();

        parse_lock.exit();
        append_lock.exit();

        new_data = "";
    }
};
void UiEditorAbout::print_debug( String text ) {
    if( debug_parser && ! is_on_shutdown )
        debug_parser->append( text );
}
#endif
//[/MiscUserDefs]

//==============================================================================
UiEditorAbout::UiEditorAbout (AppInstanceStore* const app_instance_store_)
    : UiEditor("B-About"),_app_instance_store(app_instance_store_)
{
    addAndMakeVisible (au_button = new ImageButton (String()));

    au_button->setImages (false, true, true,
                          ImageCache::getFromMemory (au_logo_100x_png, au_logo_100x_pngSize), 1.000f, Colour (0x00000000),
                          Image(), 1.000f, Colour (0x00000000),
                          Image(), 1.000f, Colour (0x00000000));
    addAndMakeVisible (vst_button = new ImageButton (String()));

    vst_button->setImages (false, true, true,
                           ImageCache::getFromMemory (vst_logo_100x_png, vst_logo_100x_pngSize), 1.000f, Colour (0x00000000),
                           Image(), 1.000f, Colour (0x00000000),
                           Image(), 1.000f, Colour (0x00000000));
    addAndMakeVisible (hyperlinkButton8 = new HyperlinkButton (String(),
                                                               URL ("http://b-step.monoplugs.com")));
    hyperlinkButton8->setTooltip (TRANS("http://b-step.monoplugs.com"));
    hyperlinkButton8->setColour (HyperlinkButton::textColourId, Colour (0xffffdd00));

    addAndMakeVisible (video_1 = new HyperlinkButton (TRANS("http://B-Step.Monoplugs.com"),
                                                      URL ("http://b-step.monoplugs.com")));
    video_1->setTooltip (TRANS("http://b-step.monoplugs.com"));
    video_1->setButtonText (TRANS("http://B-Step.Monoplugs.com"));
    video_1->setColour (HyperlinkButton::textColourId, Colours::aliceblue);

    addAndMakeVisible (video_2 = new HyperlinkButton (TRANS("http://Forum.Monoplugs.com"),
                                                      URL ("http://forum.monoplugs.com")));
    video_2->setTooltip (TRANS("http://forum.monoplugs.com"));
    video_2->setButtonText (TRANS("http://Forum.Monoplugs.com"));
    video_2->setColour (HyperlinkButton::textColourId, Colours::aliceblue);

    addAndMakeVisible (video_3 = new HyperlinkButton (TRANS("http://B-Step.Monoplugs.com/Manual/"),
                                                      URL ("http://b-step-manual-redirect.monoplugs.com/")));
    video_3->setTooltip (TRANS("http://b-step-manual-redirect.monoplugs.com/"));
    video_3->setButtonText (TRANS("http://B-Step.Monoplugs.com/Manual/"));
    video_3->setColour (HyperlinkButton::textColourId, Colours::aliceblue);

    addAndMakeVisible (video_4 = new HyperlinkButton (TRANS("https://www.youtube.com/monoplugs"),
                                                      URL ("https://www.youtube.com/user/monotomys")));
    video_4->setTooltip (TRANS("https://www.youtube.com/user/monotomys"));
    video_4->setButtonText (TRANS("https://www.youtube.com/monoplugs"));
    video_4->setColour (HyperlinkButton::textColourId, Colours::aliceblue);

    addAndMakeVisible (video_5 = new HyperlinkButton (TRANS("info@Monoplugs.com : B-Step 2"),
                                                      URL ("mailto:info@monoplugs.com")));
    video_5->setTooltip (TRANS("mailto:info@monoplugs.com"));
    video_5->setButtonText (TRANS("info@Monoplugs.com : B-Step 2"));
    video_5->setColour (HyperlinkButton::textColourId, Colours::aliceblue);

    addAndMakeVisible (debug_out = new TextEditor (String()));
    debug_out->setMultiLine (true);
    debug_out->setReturnKeyStartsNewLine (false);
    debug_out->setReadOnly (false);
    debug_out->setScrollbarsShown (true);
    debug_out->setCaretVisible (true);
    debug_out->setPopupMenuEnabled (true);
    debug_out->setColour (TextEditor::textColourId, Colours::aqua);
    debug_out->setColour (TextEditor::backgroundColourId, Colours::black);
    debug_out->setColour (TextEditor::outlineColourId, Colours::red);
    debug_out->setColour (TextEditor::shadowColourId, Colours::red);
    debug_out->setColour (CaretComponent::caretColourId, Colours::aqua);
    debug_out->setText (TRANS("\n"));

    addAndMakeVisible (toolbar = new UiEditorToolbar (this, true, false, false));

    addAndMakeVisible (open_debug = new ImageButton (String()));
    open_debug->addListener (this);

    open_debug->setImages (false, true, true,
                           Image(), 1.000f, Colour (0x00000000),
                           Image(), 1.000f, Colour (0x00000000),
                           Image(), 1.000f, Colour (0x00000000));
    cachedImage_aboutbox_png = ImageCache::getFromMemory (aboutbox_png, aboutbox_pngSize);
    cachedImage_b_logo_png = ImageCache::getFromMemory (b_logo_png, b_logo_pngSize);

    //[UserPreSize]
#ifndef DEVELOPMENT
    debug_out->setEnabled(false);
#else
    is_on_shutdown = false;
#endif

#ifdef JUCE_ANDROID
    bool state = false;
    Font android_font = Font("oswald-regular", 21, Font::italic );
    Font oswald_font = Font( Typeface::createSystemTypefaceFor(reinterpret_cast<const void*>( &android_font ),21));
#else
    bool state = true;
    Font oswald_font = Font( Typeface::createSystemTypefaceFor(BinaryData::OswaldRegular_ttf,BinaryData::OswaldRegular_ttfSize) );
#endif
    video_1->setFont( oswald_font, state, Justification::left);
    video_2->setFont( oswald_font, state, Justification::left);
    video_3->setFont( oswald_font, state, Justification::left);
    video_4->setFont( oswald_font, state, Justification::left);
    video_5->setFont( oswald_font, state, Justification::left);

    setOpaque(true);

    is_demo = false;

    String additional_info;
#ifndef B_STEP_STANDALONE
    additional_info = PluginHostType().getHostDescription();
    additional_info += " ";
#endif
    additional_info += SystemStats::getOperatingSystemName();

    video_5->setButtonText (TRANS("info@Monoplugs.com : B-Step ")+ String(ProjectInfo::versionString));
    video_5->setURL(URL(String("mailto:info@monoplugs.com?subject=B-Step ") + ProjectInfo::versionString + String(" (") + additional_info + String( ") : " )));

    debug_out->setVisible(false);
    //[/UserPreSize]

    setSize (431, 540);


    //[Constructor] You can add your own custom stuff here..
#ifdef B_STEP_STANDALONE
    vst_button->setVisible(false);
    au_button->setVisible(false);
#else
    if( _app_instance_store->audio_processor->wrapperType == AudioProcessor::WrapperType::wrapperType_AudioUnit )
    {
        vst_button->setVisible(false);
        is_au = true;
    }
    else
    {
        au_button->setVisible(false);
        is_au = false;
    }
#endif

    center_relative_and_make_visible( _app_instance_store->editor );
    //[/Constructor]
}

UiEditorAbout::~UiEditorAbout()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
#ifdef DEVELOPMENT
    is_on_shutdown = true;
    debug_parser = nullptr;
#endif
    //[/Destructor_pre]

    au_button = nullptr;
    vst_button = nullptr;
    hyperlinkButton8 = nullptr;
    video_1 = nullptr;
    video_2 = nullptr;
    video_3 = nullptr;
    video_4 = nullptr;
    video_5 = nullptr;
    debug_out = nullptr;
    toolbar = nullptr;
    open_debug = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void UiEditorAbout::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    if( false)
    {
    //[/UserPrePaint]

    g.setColour (Colours::black);
    g.drawImage (cachedImage_aboutbox_png,
                 0, 0, proportionOfWidth (1.0000f), proportionOfHeight (1.0000f),
                 0, 0, cachedImage_aboutbox_png.getWidth(), cachedImage_aboutbox_png.getHeight());

    g.setColour (Colour (GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    g.drawRect (0, 0, getWidth() - 0, getHeight() - 0, 2);

    g.setColour (Colours::black);
    g.drawImageWithin (cachedImage_b_logo_png,
                       proportionOfWidth (-0.0394f), 0, proportionOfWidth (1.0789f), proportionOfHeight (0.3704f),
                       RectanglePlacement::centred | RectanglePlacement::onlyReduceInSize,
                       false);

    g.setColour (Colour (GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    g.setFont (Font (11.20f, Font::plain));
    g.drawText (TRANS("VST is a trademark of Steinberg Media Technologies GmbH"),
                (getWidth() / 2) - (proportionOfWidth (0.9002f) / 2), proportionOfHeight (0.9907f) - proportionOfHeight (0.0630f), proportionOfWidth (0.9002f), proportionOfHeight (0.0630f),
                Justification::centred, true);

    //[UserPaint] Add your own custom painting code here..
    }

    g.setColour (Colours::black);
    g.drawImage (cachedImage_aboutbox_png,
                 0, 0, proportionOfWidth (1.0000f), proportionOfHeight (1.0000f),
                 0, 0, cachedImage_aboutbox_png.getWidth(), cachedImage_aboutbox_png.getHeight());

    g.setColour (Colour (GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    g.drawRect (0, 0, getWidth() - 0, getHeight() - 0, 2);

    g.setColour (Colours::black);
    g.drawImageWithin (cachedImage_b_logo_png,
                       proportionOfWidth (-0.0394f), 0, proportionOfWidth (1.0789f), proportionOfHeight (0.3704f),
                       RectanglePlacement::centred | RectanglePlacement::onlyReduceInSize,
                       false);

    g.setColour (Colour( GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR ));
#ifdef B_STEP_STANDALONE
    g.drawText (BUILD_INFO+String("B-Step ") + ProjectInfo::versionString,
                proportionOfWidth (0.0500f), proportionOfHeight(0.9f), proportionOfWidth (0.9000f), 30,
                Justification::centred, true);
#else
    if( is_au )
    {
        g.drawText (BUILD_INFO+String("V") + ProjectInfo::versionString + " | AudioUnits is a trademark of Apple Computer, Inc.",
                    (getWidth() / 2) - ((proportionOfWidth (0.9002f)) / 2), proportionOfHeight (0.9907f) - proportionOfHeight (0.0630f), proportionOfWidth (0.9002f), proportionOfHeight (0.0630f),
                    Justification::centred, true);
    }
    else
    {
        g.drawText (BUILD_INFO+String("V") + ProjectInfo::versionString + " | VST is a trademark of Steinberg Media Technologies GmbH",
                    (getWidth() / 2) - ((proportionOfWidth (0.9002f)) / 2), proportionOfHeight (0.9907f) - proportionOfHeight (0.0630f), proportionOfWidth (0.9002f), proportionOfHeight (0.0630f),
                    Justification::centred, true);
    }
#endif
    return;

    g.setColour (Colour (0xff161616));
    g.fillRoundedRectangle (2.0f, 2.0f, static_cast<float> (getWidth() - 4), static_cast<float> (getHeight() - 4), 10.000f);

    g.setColour (Colour (GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    g.drawRoundedRectangle (2.0f, 2.0f, static_cast<float> (getWidth() - 4), static_cast<float> (getHeight() - 4), 10.000f, 2.000f);

    g.setColour (Colours::black);
    g.drawImageWithin (cachedImage_b_logo_png,
                       proportionOfWidth (0.5000f) - ((432) / 2), 92 - ((200) / 2), 432, 200,
                       RectanglePlacement::centred,
                       false);

    ResizableWindow::moved();
    //[/UserPaint]
}

void UiEditorAbout::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    au_button->setBounds ((getWidth() / 2) + 162 - (proportionOfWidth (0.1531f) / 2), proportionOfHeight (0.8148f), proportionOfWidth (0.1531f), proportionOfHeight (0.1111f));
    vst_button->setBounds (proportionOfWidth (0.8817f) - (proportionOfWidth (0.1670f) / 2), proportionOfHeight (0.8444f), proportionOfWidth (0.1670f), proportionOfHeight (0.0741f));
    hyperlinkButton8->setBounds (proportionOfWidth (0.0394f), proportionOfHeight (0.0000f), proportionOfWidth (0.9211f), proportionOfHeight (0.3333f));
    video_1->setBounds (proportionOfWidth (0.2784f), proportionOfHeight (0.3926f), proportionOfWidth (0.6125f), proportionOfHeight (0.0518f));
    video_2->setBounds (proportionOfWidth (0.2784f), proportionOfHeight (0.4389f), proportionOfWidth (0.6125f), proportionOfHeight (0.0518f));
    video_3->setBounds (proportionOfWidth (0.2784f), proportionOfHeight (0.4852f), proportionOfWidth (0.6125f), proportionOfHeight (0.0518f));
    video_4->setBounds (proportionOfWidth (0.2784f), proportionOfHeight (0.5315f), proportionOfWidth (0.6125f), proportionOfHeight (0.0518f));
    video_5->setBounds (proportionOfWidth (0.2784f), proportionOfHeight (0.5778f), proportionOfWidth (0.6125f), proportionOfHeight (0.0518f));
    debug_out->setBounds (0, 0, proportionOfWidth (0.8910f), proportionOfHeight (1.0000f));
    toolbar->setBounds (getWidth() - proportionOfWidth (0.1160f), 0, proportionOfWidth (0.1160f), proportionOfHeight (0.3704f));
    open_debug->setBounds (proportionOfWidth (0.0186f), proportionOfHeight (0.6963f), proportionOfWidth (0.8538f), proportionOfHeight (0.2963f));
    //[UserResized] Add your own custom resize handling here..
    ResizableWindow::resized();
    //[/UserResized]
}

void UiEditorAbout::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == open_debug)
    {
        //[UserButtonCode_open_debug] -- add your button handler code here..
#ifdef DEVELOPMENT
        if( debug_parser )
            return;

        debug_parser = new Parser(debug_out);
        debug_out->setVisible(true);
#endif
        //[/UserButtonCode_open_debug]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="UiEditorAbout" componentName=""
                 parentClasses="public UiEditor" constructorParams="AppInstanceStore* const app_instance_store_"
                 variableInitialisers="UiEditor(&quot;B-About&quot;),_app_instance_store(app_instance_store_)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="431" initialHeight="540">
  <BACKGROUND backgroundColour="161616">
    <IMAGE pos="0 0 100% 100%" resource="aboutbox_png" opacity="1" mode="0"/>
    <RECT pos="0 0 0M 0M" fill="solid: 161616" hasStroke="1" stroke="2, mitered, butt"
          strokeColour="solid: ffff3b00"/>
    <IMAGE pos="-3.944% 0 107.889% 37.037%" resource="b_logo_png" opacity="1"
           mode="2"/>
    <TEXT pos="0Cc 99.074%r 90.023% 6.296%" fill="solid: ffff3b00" hasStroke="0"
          text="VST is a trademark of Steinberg Media Technologies GmbH"
          fontname="Default font" fontsize="11.199999999999999289" bold="0"
          italic="0" justification="36"/>
  </BACKGROUND>
  <IMAGEBUTTON name="" id="98e4cda2c6c85ab4" memberName="au_button" virtualName=""
               explicitFocusOrder="0" pos="162Cc 81.481% 15.313% 11.111%" buttonText=""
               connectedEdges="0" needsCallback="0" radioGroupId="0" keepProportions="1"
               resourceNormal="au_logo_100x_png" opacityNormal="1" colourNormal="0"
               resourceOver="" opacityOver="1" colourOver="0" resourceDown=""
               opacityDown="1" colourDown="0"/>
  <IMAGEBUTTON name="" id="f354b69076d11424" memberName="vst_button" virtualName=""
               explicitFocusOrder="0" pos="88.167%c 84.444% 16.705% 7.407%"
               buttonText="" connectedEdges="0" needsCallback="0" radioGroupId="0"
               keepProportions="1" resourceNormal="vst_logo_100x_png" opacityNormal="1"
               colourNormal="0" resourceOver="" opacityOver="1" colourOver="0"
               resourceDown="" opacityDown="1" colourDown="0"/>
  <HYPERLINKBUTTON name="" id="8a6a29d1146c693d" memberName="hyperlinkButton8" virtualName=""
                   explicitFocusOrder="0" pos="3.944% 0% 92.111% 33.333%" tooltip="http://b-step.monoplugs.com"
                   textCol="ffffdd00" buttonText="" connectedEdges="0" needsCallback="0"
                   radioGroupId="0" url="http://b-step.monoplugs.com"/>
  <HYPERLINKBUTTON name="" id="f3ef165b08c75d01" memberName="video_1" virtualName=""
                   explicitFocusOrder="0" pos="27.842% 39.259% 61.253% 5.185%" tooltip="http://b-step.monoplugs.com"
                   textCol="fff0f8ff" buttonText="http://B-Step.Monoplugs.com" connectedEdges="0"
                   needsCallback="0" radioGroupId="0" url="http://b-step.monoplugs.com"/>
  <HYPERLINKBUTTON name="" id="2fc1a62b83ff7d1f" memberName="video_2" virtualName=""
                   explicitFocusOrder="0" pos="27.842% 43.889% 61.253% 5.185%" tooltip="http://forum.monoplugs.com"
                   textCol="fff0f8ff" buttonText="http://Forum.Monoplugs.com" connectedEdges="0"
                   needsCallback="0" radioGroupId="0" url="http://forum.monoplugs.com"/>
  <HYPERLINKBUTTON name="https://www.youtube.com/user/monotomys" id="9ad069b0cba063e0"
                   memberName="video_3" virtualName="" explicitFocusOrder="0" pos="27.842% 48.519% 61.253% 5.185%"
                   tooltip="http://b-step-manual-redirect.monoplugs.com/" textCol="fff0f8ff"
                   buttonText="http://B-Step.Monoplugs.com/Manual/" connectedEdges="0"
                   needsCallback="0" radioGroupId="0" url="http://b-step-manual-redirect.monoplugs.com/"/>
  <HYPERLINKBUTTON name="" id="52f795e4a8d88167" memberName="video_4" virtualName=""
                   explicitFocusOrder="0" pos="27.842% 53.148% 61.253% 5.185%" tooltip="https://www.youtube.com/user/monotomys"
                   textCol="fff0f8ff" buttonText="https://www.youtube.com/monoplugs"
                   connectedEdges="0" needsCallback="0" radioGroupId="0" url="https://www.youtube.com/user/monotomys"/>
  <HYPERLINKBUTTON name="" id="e25e325442ba9e0c" memberName="video_5" virtualName=""
                   explicitFocusOrder="0" pos="27.842% 57.778% 61.253% 5.185%" tooltip="mailto:info@monoplugs.com"
                   textCol="fff0f8ff" buttonText="info@Monoplugs.com : B-Step 2"
                   connectedEdges="0" needsCallback="0" radioGroupId="0" url="mailto:info@monoplugs.com"/>
  <TEXTEDITOR name="" id="5d61010bcec9502e" memberName="debug_out" virtualName=""
              explicitFocusOrder="0" pos="0 0 89.095% 100%" textcol="ff00ffff"
              bkgcol="ff000000" outlinecol="ffff0000" shadowcol="ffff0000"
              caretcol="ff00ffff" initialText="&#10;" multiline="1" retKeyStartsLine="0"
              readonly="0" scrollbars="1" caret="1" popupmenu="1"/>
  <GENERICCOMPONENT name="" id="b3ecc3f8f99fe16a" memberName="toolbar" virtualName="UiEditorToolbar"
                    explicitFocusOrder="0" pos="0Rr 0 11.601% 37.037%" class="Component"
                    params="this, true, false, false"/>
  <IMAGEBUTTON name="" id="a84f57d328d95b64" memberName="open_debug" virtualName=""
               explicitFocusOrder="0" pos="1.856% 69.63% 85.383% 29.63%" buttonText=""
               connectedEdges="0" needsCallback="1" radioGroupId="0" keepProportions="1"
               resourceNormal="" opacityNormal="1" colourNormal="0" resourceOver=""
               opacityOver="1" colourOver="0" resourceDown="" opacityDown="1"
               colourDown="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif

//==============================================================================
// Binary resources - be careful not to edit any of these sections!

// JUCER_RESOURCE: b_logo_png, 49419, "../Images/b_logo-new.png"
static const unsigned char resource_UiEditorAbout_b_logo_png[] = { 137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,2,128,0,0,1,46,8,6,0,0,0,30,51,163,32,0,0,0,6,98,75,71,68,0,255,0,255,0,255,160,189,
167,147,0,0,0,9,112,72,89,115,0,0,11,19,0,0,11,19,1,0,154,156,24,0,0,0,7,116,73,77,69,7,222,3,13,17,3,25,3,136,71,182,0,0,0,29,105,84,88,116,67,111,109,109,101,110,116,0,0,0,0,0,67,114,101,97,116,101,
100,32,119,105,116,104,32,71,73,77,80,100,46,101,7,0,0,32,0,73,68,65,84,120,218,236,125,119,152,28,87,149,253,169,170,206,61,221,61,51,61,57,104,102,164,81,176,36,43,88,89,178,44,89,150,163,108,108,3,
182,97,193,178,193,152,100,192,152,240,131,37,44,44,113,73,203,238,194,130,89,103,17,69,92,118,73,107,99,131,141,179,192,89,209,202,121,70,51,163,137,61,157,170,235,247,71,247,235,190,245,250,85,79,143,
21,145,238,249,190,250,186,123,166,99,133,247,206,59,247,222,115,1,6,131,193,96,48,24,12,6,131,193,96,48,24,12,6,131,193,96,48,24,12,6,131,193,96,48,24,12,6,131,193,96,48,24,12,6,131,193,96,48,24,12,6,
131,193,96,48,24,12,6,131,193,96,48,24,12,6,131,193,96,48,24,12,6,131,193,96,48,24,12,6,131,193,96,48,24,12,6,131,193,96,48,24,12,6,131,193,96,48,24,12,6,131,193,96,48,24,12,6,131,193,96,48,24,12,6,131,
193,96,48,24,12,6,131,193,96,48,24,12,6,131,193,96,48,24,12,6,131,193,96,48,24,12,6,131,193,96,48,24,12,6,131,193,96,48,24,12,6,131,193,96,48,24,12,6,131,193,96,48,24,12,6,131,193,96,48,24,12,6,131,193,
96,48,24,12,6,131,193,96,48,24,12,6,131,193,96,48,24,12,6,131,193,96,48,24,12,6,131,193,96,48,24,12,6,131,193,96,48,24,12,6,131,193,96,48,24,12,6,131,193,96,48,24,12,6,131,193,96,48,24,12,6,131,193,96,
48,24,12,6,131,193,96,48,24,12,6,131,193,96,48,24,12,6,131,193,96,48,24,12,6,131,193,96,48,24,12,6,131,241,119,10,141,119,193,25,117,220,44,222,53,12,6,131,193,96,48,152,0,242,49,98,82,200,96,48,24,12,
6,131,9,224,25,112,108,94,139,2,200,68,144,193,96,48,24,12,6,19,192,191,163,99,162,149,121,204,172,50,8,31,19,65,6,131,193,96,48,152,108,48,78,227,227,65,31,235,37,158,111,41,72,158,85,130,240,49,9,100,
48,24,12,6,131,9,7,227,52,38,127,186,244,88,67,233,16,176,37,17,188,76,9,146,200,96,48,24,12,6,131,73,7,227,52,56,14,50,209,147,55,167,227,38,43,126,25,5,41,100,18,200,96,48,24,12,6,131,9,224,105,74,254,
168,234,167,19,242,167,147,91,21,50,185,141,18,190,140,68,10,153,4,50,24,12,6,131,193,228,131,113,26,237,127,77,65,254,116,0,6,185,79,9,33,205,1,204,72,183,105,197,223,84,36,144,9,32,131,193,96,48,24,
103,25,92,188,11,78,43,50,72,201,159,65,110,197,230,34,127,215,21,4,48,67,136,159,6,192,204,109,148,248,201,133,35,26,147,64,6,131,193,96,48,152,0,50,78,30,225,163,247,53,5,249,115,145,205,0,224,6,224,
33,255,211,8,185,51,115,228,47,149,187,159,66,177,194,72,243,2,153,248,49,24,12,6,131,193,4,144,113,138,137,160,86,130,252,121,0,120,9,1,244,160,16,26,6,10,170,95,2,64,50,183,105,185,191,67,65,2,117,66,
6,193,100,144,193,96,48,24,12,38,128,140,147,71,250,32,145,63,157,144,64,87,142,240,185,1,248,114,155,63,119,43,8,161,120,31,51,71,250,18,0,226,0,70,115,239,49,154,251,63,45,10,161,100,143,137,31,131,
193,96,48,24,103,33,12,222,5,167,148,0,210,170,95,186,185,115,199,198,3,32,144,35,125,1,0,33,0,225,198,48,218,135,19,112,1,8,230,254,238,207,189,134,134,133,229,74,96,141,220,170,66,192,92,16,196,96,48,
24,12,198,89,2,86,0,79,15,50,72,55,131,144,63,15,33,129,97,0,17,0,21,183,44,199,157,0,80,89,55,169,231,35,247,237,248,10,178,249,126,113,0,195,40,132,144,129,66,97,136,40,0,49,144,85,11,89,5,100,48,24,
12,6,227,44,6,43,128,167,134,240,209,251,84,249,19,228,79,228,250,249,0,84,228,182,74,0,149,139,59,240,206,137,181,104,5,128,186,170,96,224,203,183,93,124,73,117,243,20,243,177,13,91,251,114,239,33,20,
63,81,1,156,33,183,64,161,42,152,193,96,48,24,12,198,89,10,157,119,193,41,37,130,114,245,175,142,226,194,15,65,2,67,0,170,86,78,197,34,241,6,123,247,239,71,119,79,15,214,174,136,172,249,233,183,62,116,
3,128,170,28,81,12,161,16,58,22,121,132,46,148,215,81,132,193,96,48,24,12,198,25,14,14,1,159,62,68,92,86,3,221,132,0,6,4,9,116,25,106,213,118,112,100,84,71,54,68,44,194,193,163,185,205,131,108,129,8,53,
148,118,42,6,225,112,48,131,193,96,48,24,103,9,241,96,156,90,80,85,78,40,128,162,8,196,139,108,129,71,16,64,40,232,69,29,125,225,164,214,86,180,180,181,1,0,158,127,233,213,24,178,202,159,40,12,17,213,
194,66,253,83,117,16,161,247,25,12,6,131,193,96,48,1,100,156,32,178,7,56,135,127,169,13,12,13,1,7,0,4,206,109,198,42,219,193,115,23,4,220,71,55,108,142,139,231,229,94,227,205,189,135,32,127,180,157,28,
152,248,49,24,12,6,131,193,4,144,113,234,8,161,76,2,69,17,8,205,3,244,3,8,204,108,66,51,125,113,107,75,107,254,254,43,175,30,72,229,158,235,37,228,143,170,127,178,2,200,4,144,193,96,48,24,12,38,128,140,
83,72,0,41,249,147,43,129,5,153,243,53,68,16,42,241,94,212,54,198,37,17,63,153,0,130,73,32,131,193,96,48,24,76,0,25,167,7,9,164,161,96,183,68,2,189,99,188,15,237,25,76,111,229,240,50,152,248,49,24,12,
6,131,193,4,144,113,234,136,31,80,220,6,206,37,145,57,170,2,150,130,80,14,169,146,168,145,191,49,249,99,48,24,12,6,131,193,4,240,20,19,191,82,36,144,246,2,118,1,112,7,220,168,160,111,50,177,181,21,45,
237,237,242,177,212,36,178,199,185,127,12,6,131,193,96,48,152,0,158,102,196,15,18,1,164,225,90,65,0,221,0,220,147,106,49,217,246,2,151,75,117,44,117,7,34,200,164,143,193,96,48,24,12,6,19,192,211,136,16,
202,106,29,205,221,203,135,131,235,35,168,25,199,251,142,165,244,49,33,100,48,24,12,6,131,9,32,227,52,35,129,180,37,156,11,128,171,33,108,15,1,151,65,236,44,148,174,248,101,18,200,96,48,24,12,6,19,64,
198,41,36,127,52,100,43,114,0,105,65,135,171,54,132,128,19,125,139,167,148,109,220,100,130,103,41,8,34,131,193,96,48,24,12,38,128,140,83,72,6,157,72,160,1,64,15,122,157,251,54,15,199,53,83,34,116,86,110,
203,228,30,103,164,191,51,24,12,6,131,193,96,2,200,56,133,196,79,245,55,155,250,151,219,28,95,56,146,210,50,18,249,131,130,232,169,158,195,96,48,24,12,6,131,9,32,227,20,16,64,185,2,88,149,15,88,116,156,
40,131,27,205,18,64,170,250,89,138,199,12,6,131,193,96,48,24,76,0,79,49,241,115,130,129,226,238,29,90,169,55,136,167,243,36,79,38,127,116,99,48,24,12,6,131,193,96,2,120,26,145,64,170,0,170,72,96,201,227,
148,176,43,128,130,8,102,164,167,89,99,60,102,48,24,12,6,131,193,4,144,113,18,137,160,92,17,172,218,28,49,154,214,50,18,241,163,143,1,86,2,25,12,6,131,193,96,48,1,60,45,200,158,211,177,144,201,160,161,
126,77,225,79,241,164,70,73,159,165,32,131,32,68,48,195,135,129,193,96,48,24,140,179,27,46,222,5,167,21,33,20,247,69,21,176,14,0,30,23,188,242,11,219,219,219,242,247,187,123,250,210,14,164,207,41,15,144,
149,64,6,227,248,95,203,175,21,124,61,50,24,12,38,128,103,233,228,64,255,175,75,228,80,175,15,161,74,126,129,219,40,28,186,131,221,189,41,50,145,8,2,104,98,236,66,16,158,120,24,140,147,119,109,91,99,60,
135,175,71,6,131,193,4,240,44,156,64,84,161,95,29,128,30,246,161,178,248,85,133,121,101,223,129,158,20,212,21,192,170,208,48,147,63,6,227,196,17,191,241,244,224,182,152,8,50,24,12,38,128,12,192,94,245,
155,87,0,189,110,169,15,176,102,159,71,118,31,236,73,162,60,27,24,158,88,24,140,19,67,254,52,197,98,174,20,74,85,229,107,124,173,50,24,12,38,128,103,238,4,162,178,129,145,77,161,13,0,90,192,11,55,125,
113,85,56,140,72,168,192,9,119,238,61,146,32,19,70,198,129,8,130,73,32,131,113,220,201,159,86,226,122,150,159,111,65,221,175,59,3,117,47,111,190,86,25,12,6,19,192,51,116,18,161,183,84,249,179,41,128,126,
151,253,56,85,87,87,195,19,44,16,64,51,147,1,212,225,95,140,65,252,120,130,97,48,142,15,249,163,29,124,84,207,165,127,163,139,53,250,154,140,244,127,38,129,12,6,131,9,224,89,54,169,216,218,192,121,221,
48,198,241,126,86,9,197,129,193,96,28,223,235,20,40,110,227,104,64,173,12,10,130,103,74,4,143,18,65,89,13,100,18,200,96,48,152,0,158,193,19,139,220,3,152,134,129,117,159,171,236,227,116,172,246,47,60,
209,48,24,229,95,179,242,245,106,144,199,212,191,147,146,56,43,247,63,43,71,4,51,18,17,100,18,200,96,48,152,0,158,197,42,3,37,133,186,111,124,10,224,88,196,142,85,65,6,227,181,93,151,64,113,184,151,230,
235,234,185,49,213,128,189,157,163,188,40,51,115,155,78,238,83,242,199,36,144,193,96,48,1,60,203,38,25,77,69,2,125,110,233,56,141,93,99,200,19,5,131,113,226,200,159,170,88,203,45,145,63,143,68,16,133,
194,103,2,72,147,91,241,255,84,25,36,144,193,96,48,152,0,158,193,4,80,40,11,249,162,16,143,75,106,217,119,124,167,3,158,92,24,140,241,95,167,58,33,127,174,220,230,6,224,205,221,122,8,33,20,215,181,9,32,
153,35,126,105,0,113,66,254,80,130,4,210,207,230,235,149,193,96,48,1,60,67,38,18,57,81,92,174,34,212,13,77,210,252,202,107,58,197,19,5,131,113,124,175,87,122,141,106,10,242,231,207,17,191,64,238,214,139,
66,104,216,202,145,190,20,128,4,33,127,137,220,123,201,36,80,118,10,224,235,153,193,96,48,1,60,3,39,20,153,16,218,242,135,116,125,220,10,160,234,25,25,38,139,140,211,236,156,63,221,23,50,242,247,213,225,
28,254,245,229,8,95,0,64,69,238,214,151,35,130,90,238,250,75,231,8,223,40,138,213,65,241,91,233,117,106,162,160,250,201,183,12,6,131,193,4,240,12,157,32,243,147,140,161,243,142,97,156,53,132,207,233,61,
172,211,232,186,4,10,185,126,52,244,27,0,16,2,80,241,15,11,241,213,137,181,152,166,251,27,14,125,247,225,161,255,56,114,116,100,4,217,240,111,28,192,8,10,57,131,114,145,8,189,175,170,34,102,48,24,140,
227,2,166,22,167,223,100,41,135,132,241,26,66,192,26,239,78,198,41,60,143,53,148,238,149,59,214,246,90,222,247,100,254,46,106,249,34,10,62,60,200,134,128,131,0,42,39,214,98,26,0,32,222,213,120,207,251,
167,126,185,173,57,218,14,160,30,64,13,128,40,128,202,28,89,12,230,94,231,149,222,83,246,25,228,235,155,193,96,48,1,60,67,136,222,88,36,48,63,233,232,218,107,26,240,121,146,96,156,106,210,167,170,152,
45,135,0,234,99,144,194,83,73,6,101,18,40,20,64,31,10,10,96,88,60,57,99,89,232,238,62,130,223,125,225,194,15,77,105,171,107,207,17,192,106,0,85,185,231,5,8,1,20,5,36,52,60,172,225,212,147,95,6,131,193,
4,144,113,42,136,162,161,75,3,63,7,131,24,167,23,241,43,69,250,228,170,89,186,25,100,83,253,95,182,69,210,78,225,66,71,245,91,40,1,244,228,72,160,31,217,28,192,60,246,236,219,135,238,35,71,240,155,175,
94,246,182,27,214,44,156,157,35,128,149,57,2,72,243,5,221,176,155,73,107,60,70,51,24,12,38,128,76,5,79,143,119,97,240,217,88,76,198,198,34,124,70,25,228,207,144,200,143,46,253,79,71,105,69,240,68,93,117,
154,226,51,100,21,80,228,0,138,60,192,160,188,94,19,107,182,107,47,158,119,110,142,252,69,8,1,20,10,160,59,183,9,67,105,237,36,255,102,6,131,113,22,129,139,64,254,30,96,105,128,102,29,235,208,63,86,232,
153,117,69,198,120,207,33,101,202,130,195,99,173,204,179,215,82,220,102,20,231,105,70,122,222,137,60,135,181,18,68,151,146,91,97,253,226,119,122,163,198,96,66,40,127,162,32,36,70,54,47,178,54,48,110,100,
43,128,69,203,56,121,31,242,181,202,96,48,152,0,158,13,200,64,183,116,152,90,209,20,57,246,196,204,96,156,44,226,167,75,36,73,47,65,154,244,49,200,95,134,16,63,106,125,66,201,224,169,108,151,166,106,255,
230,38,155,167,248,151,101,191,86,99,56,45,66,190,193,28,233,11,2,24,70,65,1,164,132,146,243,254,142,239,121,203,228,153,193,32,224,16,240,223,195,65,50,140,114,6,173,215,58,89,240,4,195,40,247,156,114,
106,131,70,141,145,69,94,156,65,200,144,80,198,124,40,120,227,249,164,205,75,254,71,11,34,168,93,10,173,144,117,170,146,213,78,193,126,161,33,108,15,0,247,140,169,83,75,189,62,128,66,241,135,159,252,126,
15,217,127,148,4,234,124,157,150,117,60,254,30,170,201,25,140,211,6,172,0,158,94,144,125,192,0,0,134,225,182,172,116,178,156,41,78,43,243,239,60,248,49,198,187,48,40,234,81,77,200,15,85,171,12,7,98,88,
100,112,158,123,76,207,251,12,10,253,114,173,220,248,148,206,221,23,189,115,105,232,215,169,103,238,201,8,7,3,197,85,203,249,219,121,139,22,97,227,214,173,78,239,225,149,136,47,37,188,30,100,195,195,78,
133,48,108,10,125,252,198,47,205,97,252,101,48,152,0,50,78,40,201,43,155,8,186,61,94,43,153,30,25,239,48,197,201,227,140,227,77,252,84,249,111,114,85,172,106,115,161,184,24,132,190,15,13,249,138,251,105,
105,75,229,94,103,194,185,103,238,169,36,68,186,180,47,208,210,216,136,253,135,14,169,158,235,129,93,25,165,106,167,170,40,38,35,237,47,38,125,229,143,103,99,237,47,203,225,189,152,12,50,206,120,112,8,
248,244,34,134,150,98,224,177,124,190,192,120,66,192,165,114,172,202,25,44,25,76,254,84,228,79,174,224,21,164,142,118,194,160,202,150,104,137,22,202,109,145,220,86,149,219,170,165,251,213,228,111,226,
53,65,20,66,165,34,60,108,16,162,36,171,111,39,251,92,46,25,74,156,59,123,86,254,254,222,253,251,242,247,63,122,235,149,205,18,249,19,155,11,106,43,152,49,63,235,12,62,31,203,169,56,87,165,37,168,42,204,
157,22,32,165,236,140,24,12,38,128,140,147,66,0,233,253,188,26,18,8,70,108,125,124,119,30,56,128,158,222,222,252,227,80,208,103,148,80,108,152,220,49,198,75,254,156,140,153,233,100,234,130,61,183,79,84,
191,6,9,129,11,33,107,121,82,137,108,247,139,40,178,70,200,53,0,106,145,237,140,81,75,54,241,191,40,236,94,121,78,102,201,167,19,73,18,202,165,9,192,58,60,228,30,170,170,171,71,71,219,132,236,5,77,174,
238,11,103,215,86,193,158,31,73,239,187,74,144,149,179,141,248,57,253,173,20,233,211,161,246,157,84,157,203,116,43,245,185,12,198,25,9,14,1,159,30,132,143,254,141,86,63,90,0,172,80,101,212,60,188,143,
60,41,153,4,82,169,252,227,115,38,54,122,159,125,121,151,74,165,81,37,144,203,247,57,212,193,208,28,22,16,242,196,41,54,90,228,225,66,113,177,135,40,104,240,147,251,244,57,116,178,22,16,161,94,19,64,2,
89,139,148,209,220,230,65,182,127,174,142,226,74,225,20,156,45,82,78,212,249,109,73,139,52,185,106,57,189,241,176,209,221,16,74,133,38,182,119,224,80,87,183,237,197,157,181,166,95,218,111,116,31,185,96,
87,88,85,74,213,153,156,7,168,149,113,110,234,40,174,68,215,203,36,108,242,249,35,246,159,14,123,15,102,139,199,73,6,19,64,198,137,36,128,170,176,175,236,111,134,154,154,70,243,213,18,236,177,163,181,
206,147,35,128,26,56,108,196,56,254,228,79,14,165,9,162,34,147,62,17,170,21,155,92,229,74,173,78,92,18,161,201,228,200,92,50,71,0,99,57,210,55,130,130,57,50,37,140,166,68,186,68,126,224,137,158,176,85,
239,107,74,91,230,35,95,124,224,229,231,239,191,97,82,115,91,27,106,119,236,64,60,153,0,76,19,48,12,58,246,122,36,18,173,170,122,22,91,70,186,166,173,51,248,60,196,24,4,175,84,213,175,94,38,249,211,164,
177,55,227,48,30,159,108,139,33,6,131,9,224,89,76,8,229,129,42,3,127,40,83,252,236,194,88,212,214,82,239,65,105,191,181,114,6,71,6,147,63,153,252,209,48,164,220,246,204,13,123,232,87,180,51,19,121,123,
65,242,119,154,195,151,15,115,214,85,160,202,235,134,215,237,245,165,118,29,142,31,177,178,10,160,80,255,70,144,245,199,27,36,132,136,146,173,52,138,171,134,53,137,44,29,235,245,168,41,174,77,192,174,
254,201,228,47,13,32,61,50,154,72,136,39,55,212,213,225,165,87,94,193,43,175,188,130,153,179,103,3,0,12,93,119,153,153,12,13,163,211,253,234,70,113,248,242,76,93,208,149,67,252,156,22,38,170,144,174,83,
78,159,76,246,76,216,213,91,77,34,129,178,66,200,36,144,193,4,144,113,66,9,32,85,255,196,0,101,37,77,61,93,234,133,45,77,117,46,168,67,117,242,36,94,106,224,101,156,221,228,79,182,117,145,137,159,28,178,
164,196,79,20,124,4,115,183,226,126,158,4,206,107,195,146,149,83,48,193,239,41,30,115,46,89,181,20,13,45,45,249,199,35,73,61,241,199,141,233,141,31,253,151,31,60,74,200,144,168,12,78,34,171,20,166,9,233,
210,75,76,204,199,58,105,203,68,16,80,27,86,203,21,203,249,28,141,166,166,70,236,217,187,23,131,67,131,249,55,253,198,39,111,110,253,224,231,239,29,130,61,52,238,145,246,181,156,215,166,157,161,231,95,
41,226,167,65,157,142,96,64,237,69,233,100,157,99,73,228,206,84,16,120,58,14,235,228,62,147,64,6,19,64,198,9,35,126,170,149,106,94,101,72,164,53,179,212,27,248,93,150,170,34,178,84,40,184,220,182,92,140,
179,139,252,201,126,125,178,161,179,92,229,43,72,94,40,71,250,194,132,0,86,204,104,194,220,215,205,198,44,67,119,62,207,234,235,234,160,105,246,127,7,61,25,239,213,115,245,243,174,94,191,246,188,191,29,
142,190,242,230,219,191,185,30,133,208,176,216,146,18,9,56,209,54,48,178,71,167,88,172,201,234,159,32,168,169,231,14,4,14,157,215,28,107,140,84,71,81,85,89,137,12,81,237,151,76,52,35,40,206,159,116,163,
184,16,100,44,147,227,191,199,60,192,114,60,38,157,20,62,85,69,47,45,76,114,50,206,22,251,39,45,17,118,83,113,171,17,66,120,42,59,206,48,24,76,0,207,2,2,152,65,113,239,211,188,186,16,55,245,116,169,17,
199,239,177,84,93,3,100,123,140,83,233,128,175,29,227,254,97,156,88,242,231,148,239,71,91,155,201,149,190,194,226,37,156,219,242,247,231,182,98,249,154,89,152,56,214,23,169,174,170,66,71,91,27,234,235,
235,29,159,227,209,147,130,88,138,156,64,85,203,52,85,21,231,137,44,0,145,137,96,70,34,127,73,0,169,247,126,238,251,207,61,253,189,55,172,1,128,218,154,26,116,245,244,228,223,164,42,96,81,165,79,86,1,
69,30,160,75,250,157,153,191,115,2,50,30,213,79,246,152,116,161,216,91,210,141,226,162,36,74,10,117,197,152,106,230,142,143,32,128,137,220,115,133,207,100,138,144,191,82,36,144,193,96,2,200,56,174,19,
139,92,1,156,1,96,245,245,199,226,154,166,193,162,94,18,68,53,9,122,45,57,108,167,26,4,113,146,8,160,118,130,223,143,7,224,19,79,254,92,68,137,162,109,219,132,226,39,8,95,132,16,192,200,236,22,44,185,
106,54,102,148,243,69,194,161,16,26,27,234,81,85,85,5,184,156,135,161,175,221,253,251,109,40,228,17,210,16,169,76,254,78,230,53,42,87,0,11,245,72,144,191,36,128,100,95,255,72,76,188,176,177,161,1,71,122,
122,240,236,147,79,98,225,210,165,0,128,138,128,215,51,28,75,8,15,69,31,212,42,160,220,254,238,239,53,20,92,174,234,39,167,175,208,20,4,153,52,187,165,253,69,55,241,122,16,50,151,38,68,61,137,108,174,
169,11,133,206,43,73,197,247,118,42,44,98,50,200,96,2,200,56,102,21,129,78,44,170,137,198,218,185,231,192,112,141,174,35,99,146,72,176,85,200,115,15,123,45,167,142,12,170,68,234,147,77,250,180,227,180,
175,84,239,199,3,240,107,35,126,128,186,171,7,37,127,98,98,21,149,188,212,223,47,156,35,127,149,0,34,53,21,104,123,247,10,92,89,238,151,169,175,173,69,99,99,35,90,155,155,80,85,91,87,242,185,79,191,184,
115,20,246,234,88,185,79,174,106,97,115,178,212,63,83,34,22,148,92,36,0,36,15,13,186,134,27,195,233,10,127,56,140,104,52,106,243,239,252,247,79,223,216,118,203,63,222,61,136,98,149,85,60,150,187,168,208,
124,199,99,177,131,209,142,241,26,60,94,231,31,29,155,116,168,67,186,114,254,41,53,29,23,133,72,114,1,13,237,71,13,216,45,131,68,10,1,181,25,138,145,243,63,153,251,62,73,137,4,82,5,150,67,193,12,38,128,
140,99,86,18,228,199,114,82,114,6,128,249,242,182,125,131,171,155,13,164,9,1,164,98,96,40,75,0,101,213,111,44,187,132,99,37,102,199,210,119,88,59,134,201,134,91,55,29,63,242,39,43,45,134,52,201,210,142,
30,21,40,40,126,162,131,71,229,69,211,112,217,146,73,104,41,231,139,116,78,156,8,93,211,16,79,36,224,118,185,96,232,70,201,231,111,238,114,15,56,156,203,250,73,188,78,157,114,191,228,176,162,8,39,166,
8,193,136,127,241,254,103,94,249,246,7,230,45,6,128,198,134,122,12,12,13,229,223,124,249,196,100,37,138,189,0,189,40,109,9,243,90,237,96,180,227,112,14,89,199,241,252,115,242,152,164,225,93,57,71,210,
7,123,30,42,77,75,240,162,184,138,90,86,0,233,177,17,22,67,195,185,231,15,195,30,50,166,155,176,24,58,219,123,48,51,152,0,50,78,240,132,35,63,206,60,243,226,206,129,203,219,61,72,36,11,139,82,154,80,30,
242,91,78,132,79,86,74,224,160,152,28,43,241,43,101,52,173,141,131,24,90,37,136,178,53,198,62,99,50,56,126,242,71,23,12,6,10,237,200,188,40,84,247,6,9,241,171,20,228,207,109,160,238,99,151,225,205,165,
62,124,82,123,59,160,107,208,0,76,158,212,137,218,198,70,0,192,214,77,155,208,212,208,128,80,117,117,201,47,127,245,7,238,217,4,117,184,213,60,69,199,152,86,255,82,227,96,186,104,163,133,42,137,7,159,
216,120,0,31,152,7,0,8,70,42,97,154,38,246,239,222,141,150,246,118,58,6,203,126,138,114,183,19,167,69,221,177,146,60,109,156,139,176,241,16,193,114,67,190,78,30,147,110,137,20,11,43,161,32,89,152,136,
212,0,218,37,70,78,19,208,200,49,162,30,147,67,57,210,231,33,243,160,6,123,254,181,37,45,4,192,228,143,193,4,144,113,34,38,21,167,238,2,136,39,82,105,159,55,132,225,145,145,252,139,118,236,218,137,134,
230,102,0,128,161,41,87,210,170,22,72,78,3,245,107,25,208,225,64,238,116,135,255,141,215,169,31,40,14,185,88,37,6,102,206,207,41,111,242,85,145,63,26,246,21,6,206,66,249,19,225,94,161,250,85,181,69,49,
227,198,197,184,208,233,195,59,218,219,161,1,88,118,193,5,202,255,79,158,216,1,221,231,47,249,3,126,249,55,243,8,72,62,29,10,137,251,38,236,109,215,228,201,250,68,47,0,84,118,34,180,2,56,73,84,166,4,128,
68,247,176,49,90,87,97,250,1,32,26,141,98,239,254,253,121,2,248,209,91,175,108,250,218,93,191,25,81,40,92,170,238,32,170,48,112,185,191,121,60,125,192,181,49,22,94,99,93,95,78,11,78,167,113,170,84,87,
25,74,244,68,14,170,176,25,162,62,147,222,128,27,225,89,173,152,119,110,51,106,107,67,8,232,26,52,175,166,225,138,75,47,69,168,174,144,106,48,243,173,63,186,59,153,74,7,1,12,192,238,49,9,20,231,96,103,
96,175,248,62,211,59,177,48,152,0,50,78,192,164,161,141,227,185,144,39,184,96,32,128,158,190,190,114,38,254,82,54,48,229,124,7,85,178,243,88,196,207,201,145,95,115,80,2,199,154,108,104,232,69,229,214,
15,20,251,38,106,14,138,224,217,62,56,171,148,23,74,254,104,184,145,146,63,154,235,87,45,200,223,156,22,172,188,114,54,166,171,62,168,173,181,21,154,166,97,185,3,241,203,175,16,198,32,127,59,122,140,248,
199,191,186,110,55,10,249,89,163,40,228,108,37,80,200,183,203,40,206,3,235,4,31,119,167,16,48,37,129,52,207,44,241,153,187,158,126,254,187,119,44,88,10,0,13,245,245,24,26,28,200,191,217,218,21,213,141,
95,187,11,187,80,28,218,164,21,193,238,220,251,201,97,96,185,251,137,234,252,87,141,15,229,16,58,77,49,110,101,202,80,3,181,50,198,36,149,205,144,11,118,115,113,47,33,124,116,49,66,189,38,3,179,91,176,
112,205,44,204,200,9,205,246,133,200,132,9,88,190,98,133,173,96,14,0,126,249,111,111,191,230,202,219,254,235,15,40,228,89,106,210,120,75,45,97,44,216,141,198,207,212,78,44,12,38,128,140,83,168,254,169,
84,192,124,37,112,36,28,30,47,249,163,249,93,42,37,174,212,170,191,220,48,175,238,64,250,156,12,92,53,168,251,120,202,202,138,92,17,157,145,38,35,217,165,95,38,130,103,171,26,88,42,212,239,84,93,41,8,
134,95,34,127,33,162,250,85,3,168,90,53,21,87,46,237,84,231,251,181,52,53,97,197,133,23,30,243,15,216,219,167,39,47,191,237,190,45,200,134,231,134,81,200,213,138,161,144,99,151,132,115,235,174,19,181,
120,179,74,168,128,162,141,93,138,124,191,184,32,173,15,63,189,249,16,176,0,0,16,12,133,224,241,120,243,97,96,175,27,26,236,225,95,153,4,10,133,202,149,35,37,244,250,206,64,237,9,168,58,31,244,18,11,56,
56,40,137,178,2,175,234,178,162,149,88,224,142,101,51,228,129,218,96,60,8,123,225,81,152,16,192,80,192,131,154,183,46,194,85,117,97,4,157,14,90,75,83,19,102,206,152,94,68,254,0,96,74,77,188,198,227,118,
213,37,83,105,65,254,132,141,79,138,144,120,241,56,147,251,174,52,236,207,21,193,140,51,2,220,26,236,228,19,62,107,12,18,168,122,174,85,19,141,142,37,223,57,53,72,87,133,127,203,201,199,131,131,122,167,
202,29,163,85,119,170,1,157,78,108,78,125,99,189,210,255,233,36,72,195,97,42,51,88,3,165,91,65,157,13,134,215,170,220,75,213,164,75,85,23,185,210,55,128,130,173,75,117,110,139,2,136,94,121,46,174,85,145,
191,154,104,20,75,23,45,194,170,21,43,28,191,216,83,59,245,228,77,95,126,226,232,148,27,214,117,79,185,97,93,183,211,243,30,223,233,30,90,253,158,251,55,33,219,254,77,108,3,40,228,107,9,53,48,37,41,52,
39,131,8,58,93,203,212,7,48,13,123,14,160,80,44,227,219,123,60,253,226,133,77,141,141,216,187,111,95,254,141,238,254,226,173,147,80,108,180,77,175,5,217,22,70,229,251,89,42,204,106,72,196,95,87,188,151,
170,165,154,170,29,157,94,198,194,195,105,65,74,85,103,185,210,92,168,124,17,20,82,14,106,0,212,230,182,122,175,11,173,183,44,195,77,31,186,24,111,42,69,254,34,145,8,154,26,27,81,89,89,229,120,240,30,
185,243,198,11,200,2,167,10,185,138,118,161,44,146,125,79,43,177,85,215,215,177,94,179,99,109,12,6,43,128,103,161,10,8,170,126,53,53,52,160,200,11,80,61,160,148,34,125,122,25,131,182,85,6,161,112,50,156,
86,77,46,50,89,115,114,234,135,52,161,219,42,161,97,15,183,209,91,13,14,254,137,14,191,231,76,88,169,151,99,187,83,74,121,161,36,157,118,246,8,147,9,88,16,192,234,235,231,227,13,83,234,81,84,177,17,12,
4,112,225,242,229,240,43,212,233,159,61,155,26,249,228,55,126,220,15,69,78,235,134,61,70,197,130,54,51,64,159,255,246,175,60,185,243,241,231,182,247,229,136,222,0,128,163,0,250,0,244,231,136,160,80,0,
229,92,64,19,39,39,244,139,18,10,160,220,15,56,65,20,192,24,128,248,219,63,243,179,103,30,251,207,171,47,5,128,202,104,20,208,11,151,226,5,157,137,106,137,136,251,200,45,173,10,78,229,142,157,156,247,
168,145,107,65,43,65,84,84,249,184,170,60,194,12,185,165,237,208,196,227,177,250,45,151,34,163,52,229,128,18,94,161,250,133,80,240,154,20,231,99,120,78,43,150,95,57,171,60,143,73,43,99,98,120,120,24,61,
61,61,249,194,35,25,117,21,166,239,237,111,184,96,242,189,191,120,108,11,81,108,105,202,129,176,31,82,117,89,50,79,224,245,123,44,207,117,82,114,25,12,38,128,167,41,241,147,7,94,57,185,61,3,32,163,251,
253,208,101,47,64,231,65,87,119,88,189,163,140,149,229,88,161,94,149,58,224,82,144,61,218,201,64,86,11,117,133,154,144,145,126,191,188,137,73,95,56,245,27,210,255,105,5,159,238,64,2,129,147,103,157,113,
42,213,63,148,56,78,116,2,166,100,67,24,59,87,162,144,243,23,189,126,62,94,175,34,127,237,141,141,88,190,98,5,52,143,199,246,247,47,252,104,71,255,186,95,63,49,8,187,55,30,37,240,248,216,55,126,53,250,
200,127,188,110,6,0,252,108,67,234,240,39,191,254,227,61,185,73,56,38,17,192,163,132,0,14,231,38,101,218,11,216,42,65,68,78,68,235,46,203,129,0,210,48,176,248,126,66,1,140,3,136,31,238,25,24,162,111,228,
245,122,241,212,227,143,99,201,249,231,3,0,166,77,108,12,111,217,121,104,132,144,113,89,17,79,144,107,74,85,252,98,72,191,87,115,88,12,24,99,168,88,25,20,231,55,66,34,126,165,72,160,86,98,60,162,196,79,
108,162,210,92,228,245,209,206,50,17,0,225,91,206,199,117,141,17,84,148,58,48,58,128,213,43,86,192,50,12,232,154,6,195,48,16,137,68,74,30,204,143,95,223,62,233,222,95,60,118,128,28,43,209,109,38,150,219,
247,130,4,210,86,113,78,121,128,165,206,49,237,24,199,155,99,181,223,97,114,200,96,2,120,154,146,63,89,245,131,172,254,137,255,25,134,221,11,176,4,9,148,201,159,225,160,4,104,99,172,230,157,136,159,161,
32,124,110,216,19,186,101,47,47,26,34,214,21,3,169,74,77,73,75,19,62,237,182,64,7,101,61,119,75,213,16,72,106,6,80,58,199,241,76,81,255,156,22,1,226,152,208,106,95,31,153,124,169,242,23,5,80,117,237,92,
92,163,34,127,211,166,76,198,194,197,75,108,127,123,106,167,17,191,233,31,239,235,134,212,13,3,246,112,109,6,128,181,191,171,31,83,110,88,119,136,168,190,212,159,109,8,133,208,239,209,220,99,49,41,199,
201,2,192,82,40,49,154,164,244,30,139,2,92,78,17,133,37,45,94,68,40,152,134,129,243,134,195,63,123,54,185,253,186,133,158,78,0,104,105,110,194,246,237,59,242,111,116,231,199,47,235,92,249,206,251,142,
74,138,172,32,231,177,220,113,75,74,42,32,164,235,71,254,174,78,161,92,85,129,150,106,17,42,22,90,105,114,125,57,145,64,167,46,51,134,3,249,163,41,7,148,248,217,148,191,15,95,130,235,253,110,56,26,70,
94,182,122,117,246,75,105,26,106,28,212,190,82,120,240,59,111,155,127,201,123,239,251,11,10,149,197,193,220,249,39,66,239,9,168,125,24,143,133,248,105,199,241,154,127,45,36,79,27,231,243,25,76,0,25,39,
129,8,22,21,127,136,191,197,83,154,233,118,187,13,225,5,184,99,215,110,76,157,50,5,53,117,217,62,170,109,77,81,207,158,131,189,42,235,23,167,86,112,218,24,138,137,83,123,38,151,66,229,163,118,21,114,79,
83,122,159,190,134,134,164,85,185,84,52,25,91,132,254,196,173,135,144,6,131,172,204,77,137,20,88,99,168,129,127,207,10,160,86,6,97,87,25,235,122,9,177,8,194,110,245,82,41,200,223,229,51,113,213,140,38,
212,200,31,48,165,179,179,136,252,93,255,153,63,117,189,176,101,223,8,33,61,34,164,150,144,72,32,181,212,160,214,26,105,162,194,136,226,15,154,7,56,12,123,248,151,42,83,165,114,62,75,85,135,99,156,11,
131,82,234,12,61,119,169,18,72,67,193,241,79,126,227,39,27,175,91,191,182,19,0,234,27,155,240,167,71,31,203,23,131,52,69,76,145,239,74,43,177,3,57,242,235,39,106,148,75,218,143,242,130,71,46,250,145,125,
4,105,151,32,57,58,64,199,156,36,249,45,226,125,83,37,246,175,19,241,212,164,115,144,246,147,22,74,95,37,57,255,196,185,24,250,224,69,184,90,69,254,58,218,219,49,117,242,100,104,176,80,219,216,52,230,
133,18,27,28,68,192,161,136,174,61,106,6,166,180,213,85,109,219,211,61,36,41,226,52,239,210,201,72,191,28,199,4,148,24,111,157,242,148,173,99,152,67,202,33,166,192,216,213,219,76,8,153,0,50,78,18,9,148,
173,78,138,242,155,122,99,70,220,235,245,6,243,94,128,150,5,100,10,215,232,37,203,207,173,184,107,253,159,123,20,131,62,125,12,56,219,195,88,18,41,147,27,178,203,133,30,130,76,208,129,157,134,172,104,
127,83,185,187,129,33,145,83,139,76,160,180,175,106,2,197,190,106,163,228,190,155,60,71,151,200,163,42,36,124,188,21,183,147,169,238,141,71,157,162,73,255,148,248,209,156,43,161,120,136,9,88,132,125,43,
23,119,96,245,188,54,212,203,31,112,197,37,151,160,166,161,33,255,120,127,191,150,94,245,174,7,14,194,94,245,74,91,108,137,227,148,146,148,187,140,130,0,38,115,175,17,106,31,85,254,4,177,52,37,50,175,
154,152,13,197,177,182,198,80,0,199,155,18,225,180,120,179,200,239,76,145,125,145,223,55,123,143,186,135,38,84,165,66,0,208,88,95,143,189,251,246,229,61,1,255,253,51,183,76,188,253,159,239,25,33,4,48,
136,66,21,180,159,236,3,186,184,49,165,223,235,20,250,55,36,242,71,211,54,52,233,26,20,42,163,220,22,77,140,73,78,225,117,149,234,72,171,125,197,248,16,68,177,191,100,229,121,19,112,249,156,86,116,252,
240,25,60,125,126,39,206,171,240,217,231,167,182,182,54,120,221,110,44,206,245,82,86,161,119,88,51,119,245,106,102,215,160,150,25,24,26,177,162,149,1,61,96,90,198,252,169,48,252,30,245,113,254,225,63,
95,62,119,193,205,15,116,65,109,193,99,160,56,130,50,158,60,192,241,86,98,143,215,46,76,133,204,107,36,149,22,19,66,38,128,140,83,136,213,164,237,0,0,32,0,73,68,65,84,171,0,202,97,37,19,128,217,23,115,
141,6,3,129,96,47,241,2,164,47,158,55,115,146,255,174,245,127,86,145,63,121,37,238,84,208,33,43,73,178,98,64,67,188,178,89,43,93,57,171,30,123,201,243,93,210,202,26,132,8,100,96,15,251,38,165,73,148,38,
104,139,251,130,144,198,165,65,58,45,237,87,29,199,215,240,250,116,83,2,229,227,105,72,170,44,13,45,82,123,13,161,188,84,2,168,158,217,140,69,171,167,163,109,44,242,247,208,102,99,244,182,207,222,215,
45,29,35,154,71,53,42,169,128,73,105,81,67,239,171,122,180,198,36,2,73,73,163,133,226,52,2,67,34,252,114,65,195,107,85,66,84,199,95,165,58,210,223,36,171,215,121,18,120,243,103,127,185,225,145,127,191,
106,21,0,52,54,52,160,187,171,43,255,6,151,79,79,213,222,94,184,110,232,22,200,189,222,47,237,135,164,244,91,117,66,130,117,133,90,47,247,201,85,93,131,84,189,212,164,69,42,245,229,28,203,126,70,142,24,
80,139,23,161,58,139,133,71,245,155,23,224,230,73,117,168,5,128,183,47,195,202,104,5,108,201,165,147,39,78,204,231,75,202,120,114,135,17,127,231,103,190,223,155,76,165,51,10,50,106,0,208,163,65,120,223,
179,18,17,32,155,74,179,116,209,34,116,116,118,2,0,34,126,203,173,32,124,186,98,188,28,111,79,117,39,19,124,167,226,156,99,13,245,138,99,99,140,49,199,148,163,16,150,34,132,76,6,153,0,50,78,160,18,40,
231,195,101,186,135,181,88,117,56,236,120,213,214,135,51,178,69,138,174,88,245,171,108,30,44,133,138,36,59,244,83,226,71,155,176,203,147,148,216,228,28,38,47,0,79,107,21,90,91,171,49,169,185,18,161,144,
23,30,120,61,184,236,226,203,77,35,216,24,219,126,112,104,224,75,223,249,213,214,129,161,88,92,154,132,232,4,58,76,212,33,127,142,104,120,114,255,23,223,55,65,126,71,138,220,87,117,140,24,139,252,141,
149,195,115,58,16,66,249,187,208,156,43,49,233,251,137,234,151,247,83,35,228,175,10,64,101,93,5,38,92,51,7,231,200,31,112,249,197,23,219,200,223,151,127,186,123,224,190,95,60,54,0,123,238,158,156,68,31,
35,202,23,205,219,84,85,117,155,40,238,162,145,36,106,154,42,183,81,140,95,154,164,76,201,57,165,6,156,109,98,172,50,8,159,54,6,217,86,229,178,90,14,191,41,177,255,240,209,188,11,116,67,125,61,158,222,
176,1,198,19,79,96,201,178,101,0,128,233,157,77,225,77,219,15,198,8,81,15,18,5,144,134,210,105,254,46,157,248,229,235,223,77,22,94,30,73,193,119,145,223,100,2,48,151,77,194,149,147,91,66,211,239,127,116,
232,67,176,27,36,83,130,173,65,157,95,57,86,232,151,86,155,139,116,131,232,155,22,224,38,65,254,0,64,38,127,151,94,116,17,234,115,93,143,40,238,253,211,224,208,191,220,249,223,125,176,59,6,80,50,156,255,
173,115,91,145,175,8,49,77,19,61,189,189,121,2,152,50,243,228,214,144,54,224,181,247,158,46,85,136,83,202,64,127,60,133,32,214,24,100,80,190,239,164,132,83,82,111,149,241,249,76,6,153,0,50,142,147,250,
103,73,3,23,164,9,50,3,192,252,195,159,158,237,250,192,197,209,9,212,10,198,178,10,226,70,93,69,158,0,170,194,62,242,196,41,79,168,150,66,77,161,225,94,234,197,231,83,144,190,10,50,97,137,252,30,127,117,
0,13,171,206,193,146,105,13,197,185,100,217,179,47,3,175,217,133,115,26,34,145,115,27,140,198,107,239,126,227,52,241,175,23,15,250,187,222,241,233,117,27,6,134,71,135,137,186,84,145,35,129,129,220,173,
220,51,85,165,204,200,197,33,86,137,193,90,53,192,29,175,68,238,99,37,120,229,78,56,180,224,131,146,191,144,68,252,170,228,219,119,174,64,145,153,223,146,69,139,108,86,26,55,124,246,207,125,207,111,222,
27,83,168,69,242,38,27,35,211,240,188,156,230,64,11,124,76,7,165,207,69,30,131,168,197,134,68,80,40,17,208,81,108,13,132,18,11,1,173,196,241,215,80,218,14,137,158,67,52,39,80,206,7,76,254,98,67,106,215,
27,22,184,59,194,185,94,200,153,76,225,58,190,243,99,151,76,185,224,214,251,251,97,111,125,22,132,61,151,146,134,247,233,239,162,202,95,169,156,92,218,43,87,175,10,162,226,234,89,120,127,75,53,218,207,
155,59,23,221,222,57,95,191,255,209,251,2,40,228,0,138,113,36,133,226,238,35,78,225,120,26,250,165,21,191,84,253,171,154,223,134,43,59,9,249,163,104,111,155,128,11,86,172,44,250,251,139,251,245,196,117,
31,190,255,16,217,31,114,85,120,145,221,209,226,73,240,2,128,161,235,104,106,106,66,52,90,168,109,186,243,247,135,15,56,140,5,229,122,137,170,200,240,88,102,248,170,60,204,241,246,27,86,217,31,89,40,221,
58,19,101,254,191,220,252,65,238,184,196,4,144,113,140,36,144,18,193,140,66,1,52,255,231,145,23,14,255,203,141,111,180,89,193,196,19,201,252,139,107,43,44,23,138,189,247,228,74,60,26,6,54,20,131,184,108,
236,44,148,62,89,241,163,19,83,133,252,120,229,84,172,58,191,19,173,99,254,250,116,26,71,14,29,68,200,235,69,75,155,61,234,56,187,105,180,126,195,61,215,93,9,0,63,248,203,200,150,207,125,251,23,27,115,
74,72,5,81,0,229,92,29,205,65,197,163,170,73,57,19,191,86,226,189,198,51,49,156,8,162,87,14,1,52,36,213,165,66,161,248,85,163,144,124,31,185,253,162,226,222,190,211,38,79,198,228,169,83,243,143,23,220,
242,179,163,3,195,163,73,162,10,165,97,175,218,206,40,38,19,85,65,145,5,231,252,61,51,247,221,101,2,40,251,24,82,75,32,83,34,93,150,244,55,74,6,75,245,14,30,203,67,79,245,88,78,185,128,68,58,41,9,76,2,
72,252,227,215,127,188,229,13,235,215,118,136,15,218,177,107,23,218,38,76,64,75,91,27,26,194,25,15,236,161,250,10,73,17,165,4,39,77,200,178,92,145,239,70,177,137,186,143,42,129,115,91,177,108,205,44,188,
14,0,38,180,180,96,233,162,69,56,224,154,241,200,187,215,126,238,169,220,235,4,113,165,99,137,172,180,170,66,191,42,211,103,241,155,68,151,153,74,191,11,245,151,205,196,52,213,201,220,54,65,77,254,110,
253,250,51,221,143,110,216,58,228,176,208,160,45,242,196,249,159,95,52,248,253,126,68,43,43,49,185,179,19,45,19,38,228,223,243,91,223,127,176,75,49,246,102,48,190,254,210,78,231,14,61,247,93,10,242,103,
160,116,85,246,88,115,134,252,55,85,135,156,140,52,199,160,196,130,200,169,181,98,134,137,32,19,64,198,137,87,3,233,132,154,127,108,89,86,198,240,251,109,86,48,251,246,239,195,132,92,2,185,52,0,203,57,
64,170,142,0,242,68,168,43,38,16,65,254,130,146,226,23,34,164,162,2,64,133,219,64,228,134,249,88,211,94,131,202,114,127,180,219,237,198,240,240,8,246,237,223,143,209,209,81,52,54,52,160,162,178,248,229,
111,93,30,156,246,214,229,107,167,173,127,42,254,234,167,255,237,167,47,129,52,128,47,65,254,100,117,66,38,40,114,114,182,83,15,99,160,116,47,227,241,18,184,227,89,133,172,202,95,51,136,250,162,82,93,
162,83,234,176,240,178,153,184,216,237,130,235,79,155,209,109,1,238,80,46,225,126,245,133,43,209,212,58,193,246,166,61,195,176,150,222,178,110,0,165,123,238,82,229,217,3,123,174,145,80,156,100,95,64,65,
34,197,98,35,153,187,159,34,127,75,75,147,124,74,34,159,78,183,22,236,149,199,114,1,3,221,74,29,103,85,174,172,86,130,0,234,10,178,153,150,127,71,239,136,158,136,6,51,94,177,143,247,236,219,151,95,4,125,
239,11,239,152,244,174,79,221,189,137,28,59,145,71,41,148,55,113,109,166,200,254,119,161,216,110,197,67,200,87,190,175,240,21,51,241,230,243,218,48,25,0,154,154,154,176,250,194,11,1,195,192,171,195,141,
207,174,89,251,185,159,192,222,130,78,71,121,33,74,57,68,79,115,255,220,228,183,136,133,72,228,221,43,241,102,213,27,117,78,156,136,165,82,190,95,50,13,107,230,91,214,237,133,61,229,128,166,11,152,132,
236,137,115,208,2,160,175,158,134,246,72,56,140,72,56,140,134,250,58,27,249,219,217,99,196,165,49,87,181,168,200,140,227,218,85,145,63,23,138,11,233,232,99,189,132,154,236,164,198,169,34,72,42,130,39,
111,166,226,117,114,79,109,93,241,126,90,9,50,200,68,144,9,32,163,140,201,186,156,42,66,72,19,7,157,44,225,118,187,33,172,96,20,144,19,188,101,187,22,217,195,143,146,36,67,82,142,104,184,151,26,181,82,
226,23,210,53,68,110,92,140,215,181,86,35,50,222,29,98,154,89,199,254,116,58,141,88,44,134,254,254,126,68,171,171,209,80,95,135,64,164,152,8,222,176,196,55,249,134,37,107,39,191,249,115,143,254,229,111,
27,247,28,132,221,126,70,119,24,24,233,96,44,231,8,1,234,4,111,85,143,99,122,11,135,199,199,2,189,196,32,239,228,109,39,79,16,178,2,72,243,200,194,0,42,231,180,226,178,43,103,97,153,120,241,21,179,144,
247,209,184,228,162,139,208,32,229,90,61,184,81,75,191,239,115,15,196,75,16,34,241,89,166,52,129,136,191,11,210,147,86,76,174,38,33,105,105,135,77,14,243,209,2,11,249,121,178,97,120,90,241,121,102,9,21,
208,201,68,219,73,209,145,139,46,232,181,230,70,113,42,66,254,119,252,211,221,207,110,249,207,219,231,207,206,167,116,144,48,240,133,147,147,85,40,120,52,82,107,29,161,254,121,200,62,160,196,159,42,127,
84,1,118,215,84,160,241,141,243,240,198,154,10,228,253,80,46,189,120,53,234,115,54,42,143,237,10,60,254,142,143,127,229,55,40,110,123,6,140,29,146,148,247,141,156,135,42,47,30,67,53,21,104,13,122,237,
185,126,0,208,217,209,81,68,254,246,244,106,233,139,223,251,192,126,216,115,77,99,132,4,210,222,208,110,66,254,92,0,204,197,147,16,170,174,170,66,77,52,138,9,45,246,110,134,111,251,204,47,247,194,30,166,
151,83,21,50,10,53,217,26,39,249,163,237,23,101,175,84,67,90,196,150,90,252,169,174,251,140,66,169,83,246,147,87,44,134,40,41,116,234,67,175,74,163,48,160,54,97,103,34,200,4,144,81,166,106,163,57,168,
41,22,138,115,164,242,147,171,215,235,197,200,200,136,211,85,165,90,129,59,21,133,200,223,133,38,140,123,201,128,29,36,164,79,228,144,133,0,132,175,154,133,43,102,183,22,219,133,168,80,29,137,96,225,130,
5,208,228,230,236,154,150,29,49,53,13,90,58,141,238,254,126,12,12,13,193,227,245,194,229,243,43,223,235,199,255,180,98,249,147,187,3,135,110,254,216,157,79,74,3,167,169,32,211,52,39,201,116,152,176,84,
157,83,156,136,161,211,0,61,86,135,149,241,26,179,194,65,133,84,13,246,242,74,93,40,47,98,226,21,38,207,149,148,252,201,120,240,225,135,209,62,113,34,150,44,90,4,183,219,141,71,95,213,204,35,253,49,220,
116,237,114,207,171,123,14,153,155,183,31,76,30,29,140,153,132,232,200,150,44,66,121,145,243,254,82,10,133,46,131,226,16,50,253,127,82,82,101,210,228,111,73,73,81,75,74,207,145,63,47,169,32,131,25,233,
124,81,21,73,57,245,203,85,217,130,104,146,10,39,84,88,122,62,229,63,247,161,39,55,245,226,246,249,240,122,60,136,39,18,216,177,123,55,52,195,192,210,92,49,200,162,217,19,171,159,121,113,39,253,109,25,
242,25,126,73,17,148,243,254,242,86,38,179,91,176,228,170,217,176,25,55,78,233,236,180,89,169,124,232,59,47,252,244,55,143,190,244,170,180,112,82,17,31,167,73,94,38,63,52,119,152,86,160,139,133,99,248,
166,165,88,163,58,7,207,157,57,211,246,120,227,33,61,121,237,7,239,63,8,123,145,209,112,238,86,168,127,73,242,29,60,68,37,205,204,109,69,59,0,212,214,214,160,169,190,161,104,97,121,168,103,128,218,12,
81,187,169,20,33,150,227,85,236,229,10,104,57,39,83,110,241,167,50,200,47,53,142,200,70,247,212,82,201,146,34,72,114,94,172,28,93,202,40,212,206,140,226,117,42,50,168,149,73,4,153,4,50,1,100,140,33,227,
171,164,122,170,146,152,150,5,43,24,8,104,71,143,30,133,101,89,56,218,219,135,228,200,8,60,193,108,95,116,67,215,117,51,147,145,139,0,232,125,177,9,235,13,139,76,108,30,5,249,171,32,132,47,34,136,223,
156,86,92,112,229,44,117,238,142,64,85,36,130,133,11,23,102,71,52,77,67,56,20,202,127,207,146,68,81,81,237,167,194,210,246,88,227,179,247,223,124,229,194,155,239,255,13,138,125,4,41,121,16,131,144,172,
80,201,166,184,50,81,6,138,189,16,143,87,179,246,82,121,136,150,130,240,169,58,92,100,28,38,106,154,128,47,8,124,0,64,232,146,233,184,126,172,47,182,123,231,78,236,222,185,19,19,154,155,113,206,180,105,
198,194,115,67,24,154,232,197,225,195,126,104,151,77,246,111,222,178,5,0,224,241,120,224,243,249,16,170,168,64,101,101,37,106,107,106,80,151,43,22,25,78,104,233,161,164,158,26,140,27,137,129,184,107,116,
95,215,192,200,99,207,188,210,253,224,227,27,123,204,76,38,137,98,227,100,26,178,77,75,228,141,170,123,178,10,152,146,38,107,106,39,67,255,231,86,16,193,140,226,156,128,226,92,176,21,76,160,184,189,162,
74,9,164,197,15,110,133,194,99,1,176,14,244,27,163,62,159,207,159,177,44,36,147,73,91,155,199,255,248,224,242,9,139,222,182,115,8,197,121,126,30,216,173,113,100,37,214,237,49,16,184,106,54,174,58,167,
17,182,214,24,23,95,116,17,26,201,245,213,51,226,30,88,250,246,123,126,154,35,83,25,178,143,83,10,5,213,41,55,14,10,245,207,201,248,57,0,32,84,29,64,163,223,93,60,247,92,121,197,21,8,85,85,229,31,15,142,
34,115,237,7,239,63,132,130,63,228,8,178,249,191,67,40,84,153,139,107,157,18,239,252,98,104,205,172,108,129,73,83,67,3,194,213,81,219,231,125,238,71,59,14,66,234,214,130,98,235,33,113,30,202,227,179,147,
130,175,82,133,229,190,199,98,159,136,226,24,170,6,170,90,119,58,21,113,168,148,59,213,34,135,230,197,166,21,226,2,125,77,10,234,158,235,178,55,173,54,14,34,200,36,144,9,32,99,12,18,32,19,191,140,20,134,
200,116,13,187,98,149,225,112,240,192,161,67,128,105,162,111,96,0,131,67,67,168,201,17,171,155,95,191,188,234,158,159,63,58,160,24,132,93,100,82,114,195,158,20,239,130,58,103,44,36,169,126,145,234,32,
154,223,187,18,215,150,250,81,147,38,118,96,74,231,100,68,202,36,124,199,130,74,127,198,123,197,138,89,29,191,123,244,37,11,197,225,66,217,52,88,174,44,149,195,227,114,63,99,217,64,91,149,15,229,228,11,
166,149,56,198,227,85,136,53,7,197,88,206,23,77,73,36,176,168,227,199,194,142,172,26,82,10,45,205,205,104,108,104,64,83,125,61,34,53,217,226,109,127,56,12,205,2,50,150,133,93,62,31,250,7,6,16,79,36,48,
56,52,132,238,35,71,236,18,144,166,65,211,117,151,97,232,46,183,203,237,247,122,61,149,85,254,0,110,92,16,238,188,253,210,197,104,172,175,135,63,20,178,125,102,95,204,24,237,141,185,71,186,134,221,67,
223,255,213,195,187,254,244,244,150,46,56,247,129,150,55,106,181,34,38,243,148,164,230,80,47,66,185,104,64,238,162,161,58,47,104,232,206,80,28,123,93,82,191,104,241,131,40,86,146,77,208,181,47,220,255,
204,254,55,206,8,76,118,187,92,24,142,197,178,185,189,166,9,24,6,170,2,150,145,59,126,244,28,22,234,94,2,197,118,48,198,172,102,204,189,114,22,230,233,186,253,156,84,121,232,125,231,247,93,27,254,237,
254,255,219,36,237,43,106,221,67,247,149,220,97,7,14,202,159,156,74,66,91,14,230,23,35,175,155,83,92,112,52,121,210,36,84,215,216,205,2,230,223,188,238,0,33,103,35,40,116,134,161,62,147,105,50,151,209,
227,97,92,59,7,231,137,247,146,201,31,0,252,224,215,79,28,65,193,102,138,26,118,211,243,69,46,42,26,107,17,39,167,71,80,21,212,143,66,209,92,64,34,132,242,66,163,212,216,33,231,249,201,173,8,205,18,247,
101,179,253,140,180,176,114,74,201,144,9,163,216,39,78,68,240,88,91,49,50,152,0,158,53,68,80,229,1,40,43,60,233,195,67,174,145,104,52,26,52,140,108,37,176,124,37,173,92,48,169,226,158,159,63,234,212,166,
141,230,106,65,10,41,201,228,79,16,64,209,154,41,124,233,116,92,177,160,3,142,242,220,234,85,171,224,49,140,178,251,113,30,30,208,210,7,7,245,244,192,168,102,198,146,86,38,147,177,172,144,95,55,162,1,
203,104,143,154,158,144,175,188,252,186,175,190,115,206,156,223,61,250,82,143,3,9,72,19,146,75,123,153,170,148,81,186,10,151,73,160,83,136,24,24,59,65,62,83,102,104,196,194,216,125,108,229,48,144,74,13,
19,159,71,67,111,254,230,170,98,115,103,27,153,174,172,196,185,211,207,65,99,67,35,124,21,21,69,255,175,109,202,230,138,53,236,221,139,209,209,81,101,30,170,5,100,243,217,76,19,166,105,34,153,76,97,36,
22,67,223,209,126,104,7,15,66,211,52,232,186,14,195,48,224,118,187,225,245,122,17,12,4,16,9,135,253,53,213,213,254,197,13,13,53,231,223,177,176,3,88,104,123,223,67,131,238,129,109,61,158,158,59,62,119,
239,243,195,163,137,56,138,195,191,178,127,160,173,251,6,33,17,73,137,220,208,130,17,72,228,207,139,226,86,134,212,59,207,40,161,212,210,115,140,182,118,243,146,133,152,254,240,83,155,70,222,190,100,42,
210,233,52,252,126,63,246,239,219,135,159,254,226,23,88,52,127,62,218,38,78,196,93,159,127,91,203,173,159,190,111,63,57,111,105,248,55,3,192,236,168,69,243,21,51,48,191,42,8,31,221,103,110,183,27,171,
47,188,16,181,196,191,17,0,182,245,248,122,174,188,237,191,30,37,100,79,54,239,166,102,235,114,232,220,132,58,20,76,201,179,202,62,138,18,192,96,75,21,138,250,178,213,75,223,115,241,59,127,113,144,144,
210,97,20,122,68,139,14,49,52,247,79,190,102,221,245,97,68,103,52,103,243,146,61,158,162,84,67,170,254,209,156,66,161,50,198,9,201,54,81,220,194,208,66,233,174,25,84,61,166,21,201,34,23,183,66,34,130,
178,157,149,94,198,124,1,73,145,149,85,189,180,116,95,149,87,91,84,156,148,123,126,66,161,188,167,20,239,171,195,94,92,69,83,18,88,13,100,2,200,120,141,74,96,70,146,236,211,0,204,167,95,217,223,115,235,
242,134,58,183,203,141,84,42,13,88,86,222,19,16,0,218,170,77,175,66,249,163,185,56,194,22,129,78,94,110,66,254,232,0,21,1,80,89,229,71,211,109,171,240,122,167,47,127,201,69,23,193,101,24,54,163,96,138,
237,71,244,228,163,47,247,197,190,126,215,111,122,205,172,225,153,156,100,44,15,14,54,117,238,183,223,186,185,105,114,93,198,243,196,227,143,99,199,206,157,0,128,115,38,79,198,130,37,217,180,38,143,11,
122,52,18,140,244,14,140,200,109,200,68,24,199,34,97,33,77,90,149,211,253,34,171,60,114,120,88,54,208,46,149,15,88,238,113,86,145,69,205,97,130,209,164,208,79,102,114,29,218,150,117,226,138,209,36,98,
235,255,138,47,17,162,107,17,18,227,1,224,190,160,19,23,8,165,165,115,210,36,104,0,94,221,185,51,123,14,1,152,59,107,86,145,50,167,86,120,39,194,235,245,226,240,145,35,168,138,68,48,56,52,4,0,24,29,29,
69,50,153,200,198,113,83,105,64,203,22,249,228,191,116,198,130,105,89,200,152,38,210,166,137,100,50,137,145,88,12,253,3,253,56,220,213,133,29,46,23,188,30,15,130,129,0,194,161,16,170,171,171,179,106,97,
36,130,198,112,42,210,24,78,69,158,187,255,134,73,226,123,108,57,226,235,254,212,183,126,255,252,75,91,247,245,41,84,64,170,232,200,164,70,85,61,74,67,172,170,182,121,94,233,28,113,41,136,191,42,231,148,
230,98,10,245,199,86,189,30,12,85,91,110,221,212,210,102,26,110,151,11,59,118,239,198,163,143,63,142,170,87,94,129,223,231,19,213,238,52,175,51,49,187,5,109,171,166,161,33,232,45,30,191,107,171,171,113,
254,178,101,182,80,42,0,244,12,27,163,151,125,224,199,143,14,142,196,169,81,183,76,172,68,223,101,26,94,165,42,152,165,80,76,85,185,180,180,18,89,16,31,63,128,192,180,6,204,80,169,127,19,39,229,15,45,
30,220,100,140,246,217,175,103,154,247,23,35,228,52,131,98,211,122,31,0,239,173,203,177,88,188,223,121,115,231,56,169,127,113,137,252,197,20,11,200,52,202,43,254,40,71,1,12,2,8,190,239,66,124,71,3,92,
137,52,210,241,52,204,120,10,233,88,18,102,56,82,155,190,236,178,215,153,195,166,158,60,212,213,19,219,185,239,240,240,230,29,7,7,95,222,186,127,56,149,54,229,177,146,62,86,229,139,83,213,220,84,16,63,
39,53,93,78,171,144,173,118,210,10,101,88,35,183,25,86,3,153,0,50,198,71,254,100,213,79,117,81,155,119,254,240,225,61,239,190,228,134,233,94,175,7,241,68,28,166,105,97,52,145,200,191,89,67,216,162,85,
101,148,0,136,1,72,92,164,105,66,254,60,36,76,72,195,190,145,243,38,96,213,21,231,102,237,34,138,137,64,7,230,205,153,171,84,139,30,219,238,26,121,215,167,239,63,108,102,50,170,176,131,83,114,185,220,
115,216,13,192,243,182,207,254,226,224,227,223,185,182,125,217,249,231,99,120,120,24,93,221,221,72,154,246,104,212,247,191,120,195,204,43,222,119,239,136,52,160,139,65,92,156,231,25,105,146,240,75,147,
187,7,197,173,178,232,247,129,130,4,170,8,160,230,176,90,87,29,115,160,180,215,152,5,0,77,17,212,54,70,48,185,163,6,181,29,53,168,245,186,225,153,57,125,58,206,155,119,30,160,101,191,198,250,27,214,85,
160,208,183,213,148,85,203,73,117,168,237,236,232,200,119,156,0,224,72,218,75,33,90,95,143,104,180,26,19,142,246,163,50,18,65,108,116,20,64,54,135,45,157,78,103,79,92,51,147,157,9,72,101,43,44,11,189,
3,253,232,235,237,131,219,237,182,179,222,76,6,22,128,195,135,14,101,21,195,254,126,28,234,238,198,206,61,123,16,14,133,114,149,225,245,8,70,10,133,230,211,106,227,117,63,255,220,133,151,2,192,112,66,
79,254,232,209,238,45,95,191,231,119,91,81,220,61,70,40,91,195,210,68,239,149,84,36,192,158,10,65,243,214,2,138,133,130,14,117,126,22,61,15,104,207,108,90,77,47,206,61,247,246,161,198,216,170,169,233,
96,38,147,65,101,40,12,143,215,139,205,91,183,226,104,127,63,142,2,104,169,66,164,49,130,232,188,9,240,212,132,178,231,161,199,237,70,36,28,206,229,94,70,179,197,13,149,106,247,165,131,67,174,145,55,124,
248,167,207,244,14,12,15,75,132,120,72,65,254,134,96,15,175,38,161,46,154,145,173,115,84,109,35,61,18,249,13,0,240,175,153,137,217,242,119,236,156,56,209,246,248,125,255,124,95,183,164,206,141,40,190,
23,245,119,164,161,102,223,218,37,88,69,223,111,202,84,123,186,242,245,159,253,243,78,73,93,20,68,88,174,44,78,73,99,176,53,198,245,234,228,17,153,87,66,111,91,137,239,84,6,80,173,190,186,142,96,219,147,
247,228,31,117,0,232,104,7,94,63,213,139,112,184,26,213,145,8,106,106,106,208,212,208,0,95,184,32,162,198,18,122,242,200,168,43,214,51,226,30,121,230,165,157,221,119,254,248,145,157,241,68,42,169,80,0,
229,130,170,148,116,155,80,220,38,164,197,64,66,122,189,48,10,151,187,246,200,125,216,199,234,52,194,96,2,120,214,43,128,150,66,198,207,95,188,177,120,34,5,0,65,127,0,195,195,35,200,152,25,149,23,160,
33,173,60,105,8,38,35,169,97,130,24,82,139,151,8,128,240,123,86,224,77,209,10,20,149,225,106,154,134,171,215,172,129,232,98,64,241,129,111,63,127,232,15,127,121,121,64,177,194,84,173,26,85,4,176,40,119,
168,187,119,40,223,211,119,217,146,197,248,229,175,255,7,59,118,238,196,148,73,147,242,29,42,58,107,211,65,242,27,133,146,41,84,2,170,120,210,144,156,152,220,243,147,177,32,206,1,15,42,26,34,168,15,249,
80,227,53,16,8,120,224,241,123,224,14,184,225,242,184,224,114,25,208,220,6,12,183,1,67,215,0,29,208,52,61,91,208,108,89,5,97,54,147,251,109,150,5,88,217,232,168,5,0,46,29,186,161,67,115,233,208,93,58,
116,191,7,46,77,211,96,24,6,92,46,23,188,94,47,2,126,63,66,161,16,162,85,85,168,175,171,67,168,186,122,172,243,200,135,226,162,134,188,53,206,188,57,115,48,99,214,172,227,52,106,184,81,85,155,109,222,
16,204,133,215,202,201,246,108,66,27,82,177,24,12,195,176,19,192,92,71,155,190,222,62,36,82,41,236,220,181,43,127,82,196,227,113,108,218,178,5,187,247,236,65,56,28,46,216,4,133,11,100,176,194,155,241,
188,243,146,154,89,239,188,100,237,172,193,184,158,248,196,247,158,253,235,131,79,110,58,72,20,191,97,20,186,200,12,75,132,34,65,38,119,67,94,16,213,135,209,22,112,163,62,5,111,234,64,95,50,102,89,150,
220,121,6,146,34,35,87,99,231,139,0,102,183,96,118,202,132,182,233,16,122,196,162,227,249,237,135,83,175,91,148,109,73,22,174,174,70,164,178,18,155,183,110,205,191,233,205,75,11,225,82,93,211,16,173,174,
70,109,77,13,26,234,235,209,210,220,12,72,100,90,96,107,183,167,255,154,219,239,125,222,204,100,70,21,161,206,97,133,250,71,21,54,85,152,220,116,80,190,84,197,31,180,218,149,154,199,7,252,146,106,169,
233,58,188,190,66,244,250,146,15,253,182,11,133,80,61,237,255,77,195,178,22,89,192,186,233,181,191,116,18,22,79,168,46,156,142,11,230,157,103,251,194,7,250,245,228,11,155,247,246,75,251,97,144,156,19,
49,135,223,174,242,203,67,137,40,128,46,169,202,158,101,147,112,75,85,16,209,241,94,110,241,68,2,241,35,71,208,125,228,8,180,29,59,96,232,58,92,46,23,60,30,55,124,94,31,42,42,42,60,149,145,136,167,181,
166,166,114,222,101,141,205,239,189,252,205,115,233,235,99,73,61,121,96,200,51,240,215,173,71,15,127,254,63,127,185,57,157,54,169,178,75,21,191,4,217,247,178,223,98,140,16,192,81,18,109,16,175,213,37,
130,73,137,160,188,24,230,112,48,19,64,134,130,8,170,242,0,101,21,13,225,112,24,189,71,143,34,149,78,171,46,31,85,255,77,63,9,135,122,200,100,231,35,68,40,12,32,212,82,133,73,55,47,197,37,170,47,120,245,
154,53,136,68,139,199,175,15,254,231,11,135,126,247,216,75,253,138,80,92,82,218,228,60,18,106,196,75,173,44,104,222,84,250,99,119,111,220,253,149,119,204,104,175,32,22,14,27,55,109,194,202,218,26,192,
229,206,133,190,66,21,71,250,134,98,146,226,32,114,226,68,200,206,51,173,17,231,53,69,176,172,61,138,166,250,16,162,134,113,92,189,252,198,141,66,225,132,150,189,205,217,226,64,211,160,101,255,153,221,
74,224,187,191,239,250,21,138,195,212,212,71,50,53,227,220,115,79,252,9,108,1,125,35,90,122,56,169,153,35,73,205,76,166,53,11,128,229,54,160,121,92,150,230,49,160,7,189,21,122,64,183,140,128,219,50,228,
153,178,46,87,161,90,95,87,103,215,69,122,122,96,89,22,146,169,20,122,122,122,208,211,219,171,84,5,1,32,236,203,120,191,125,251,252,101,184,125,62,254,178,43,184,255,150,143,127,247,175,57,85,123,132,
16,126,177,209,142,18,25,114,77,4,62,181,6,247,218,127,93,65,105,111,105,104,192,178,197,139,225,13,135,209,23,51,70,247,15,120,6,159,120,97,207,145,239,254,248,225,61,241,68,74,238,151,155,15,137,94,
53,27,147,0,224,245,192,68,0,152,49,125,58,230,205,239,180,125,74,32,28,206,30,239,92,106,135,199,227,65,56,20,66,85,101,37,106,162,81,71,179,116,129,223,190,172,31,188,227,11,247,111,147,212,155,152,
130,252,13,43,136,159,220,191,89,94,176,201,158,147,178,210,37,143,61,54,5,112,70,35,138,86,32,151,174,90,133,112,46,92,61,156,128,181,251,64,239,40,236,57,157,180,42,55,77,198,46,93,34,235,193,217,45,
88,176,106,90,33,79,57,224,247,227,156,25,118,91,153,139,223,251,253,87,137,50,76,247,193,48,236,185,163,212,198,40,83,134,250,7,105,191,64,90,36,232,186,39,176,183,177,62,132,150,166,38,88,154,134,238,
238,238,252,139,246,239,223,95,150,223,140,101,89,72,231,210,40,18,137,4,134,134,71,208,123,180,15,251,15,230,22,143,158,236,226,49,28,14,163,186,170,74,92,35,158,201,209,120,237,228,165,254,218,55,47,
125,75,126,32,216,63,224,233,255,239,199,247,110,255,143,117,15,110,37,42,96,92,34,224,170,20,10,47,33,130,70,238,249,226,150,26,239,67,33,110,128,73,224,233,3,141,119,193,169,153,243,201,0,33,39,158,
123,81,8,197,70,1,212,1,104,0,208,4,160,105,219,250,181,111,220,179,125,59,94,218,184,17,131,195,67,176,50,22,46,91,189,58,95,124,113,229,255,251,191,189,219,246,116,29,1,112,20,64,15,128,190,220,54,68,
86,208,26,33,90,121,163,224,229,157,88,189,98,42,38,168,190,244,218,181,107,139,254,246,203,191,153,253,31,255,234,15,15,73,147,141,188,201,100,144,134,130,101,91,22,26,202,177,133,164,183,173,95,187,
4,0,214,173,91,151,255,252,89,51,103,98,206,121,217,21,254,11,7,92,195,215,127,232,222,231,115,191,249,72,110,235,207,13,244,41,0,250,85,179,240,254,217,173,152,121,90,157,8,217,170,89,24,134,14,183,203,
5,143,199,139,64,46,15,78,165,118,81,152,25,88,239,249,215,167,127,244,231,13,219,118,17,37,71,228,49,137,253,89,129,108,49,79,245,141,87,47,157,251,161,55,76,89,30,244,102,60,175,229,251,118,15,106,230,
254,1,61,181,253,224,104,252,129,159,63,50,244,234,222,238,81,148,246,17,83,181,165,114,42,108,209,93,134,97,188,237,13,203,163,171,23,119,86,183,87,165,130,85,1,171,72,222,74,198,98,249,202,227,193,225,
33,164,146,73,180,52,183,32,42,145,70,138,39,118,7,14,190,237,99,119,62,139,66,37,233,144,180,191,68,55,8,93,156,123,159,90,131,127,63,214,227,155,177,96,117,13,34,209,59,140,84,127,12,230,210,78,68,116,
173,240,187,23,206,159,143,105,211,167,23,189,238,185,191,254,21,251,15,28,144,206,131,98,178,155,39,200,67,122,242,35,223,122,108,251,83,47,238,236,147,174,67,161,114,10,130,55,66,200,78,12,246,176,56,
173,126,77,40,174,85,185,115,10,245,126,164,138,159,24,79,170,0,212,144,241,171,241,195,171,241,102,89,1,188,252,226,139,243,74,254,213,255,248,80,215,230,157,135,134,136,42,55,128,66,94,226,8,236,225,
122,170,252,85,204,155,128,37,151,159,91,24,187,92,46,23,174,187,230,26,184,3,129,252,103,253,228,233,196,145,127,250,230,250,93,185,113,161,55,55,86,116,229,198,10,49,86,14,192,158,15,72,137,32,53,77,
118,82,251,104,5,56,45,252,168,2,16,245,186,93,141,143,222,125,203,199,170,125,163,245,201,88,44,79,244,143,244,244,228,195,5,54,150,153,201,224,207,143,63,254,154,198,19,151,203,13,175,199,83,56,143,
162,213,104,168,171,207,46,50,20,120,181,199,119,228,142,175,253,207,211,219,118,31,62,10,123,46,237,168,226,60,138,161,184,114,60,33,169,167,41,197,126,83,141,9,96,18,200,10,224,217,166,246,201,137,176,
42,199,246,34,147,220,190,152,158,104,168,175,247,190,186,107,23,70,98,49,152,48,145,38,185,86,31,189,117,77,245,173,159,186,183,95,82,210,68,162,158,23,133,188,140,124,94,146,6,132,63,116,9,174,83,121,
115,93,120,225,133,104,109,181,183,245,221,210,101,196,95,247,129,251,118,57,172,20,233,106,81,53,48,164,80,92,89,71,67,101,98,18,73,18,37,197,248,231,31,188,186,227,51,111,157,60,169,72,114,202,97,78,
115,186,2,246,170,77,65,166,211,66,25,115,187,224,61,254,44,78,131,230,114,161,181,190,254,53,189,86,7,80,87,87,151,171,140,117,33,224,15,160,50,18,113,180,208,73,166,53,243,165,174,138,253,55,253,191,
59,255,146,74,155,66,193,80,37,114,91,176,231,61,122,190,255,235,39,55,126,255,215,79,30,68,54,204,95,49,181,163,161,122,229,226,233,209,218,234,74,111,117,117,196,237,117,233,250,225,158,254,204,211,
127,221,60,250,167,103,183,198,114,45,7,101,255,55,149,37,68,26,234,202,117,85,161,143,188,248,204,147,137,180,105,106,119,253,244,207,3,119,253,244,207,187,233,226,168,163,165,214,255,165,15,94,221,49,
175,53,89,233,9,4,108,125,163,247,237,222,141,93,187,118,97,211,150,45,240,123,60,152,126,206,57,8,72,68,105,89,123,172,105,219,250,181,215,124,236,174,141,207,253,234,143,127,219,5,123,110,172,39,119,
206,166,200,53,226,175,171,173,181,89,220,188,22,232,26,180,198,8,124,141,17,123,133,174,248,209,13,14,164,245,188,185,115,243,109,203,130,17,103,181,239,215,47,88,253,31,253,242,247,247,74,11,46,185,
168,97,132,168,91,35,132,244,197,164,73,92,14,11,202,62,137,42,229,79,206,147,117,43,20,124,145,146,225,151,201,223,196,246,246,60,249,3,128,205,59,15,209,78,28,114,149,182,56,143,105,33,151,31,64,224,
170,89,88,53,187,21,54,15,153,107,175,186,202,70,254,246,247,235,137,127,250,230,250,189,176,123,9,14,16,5,144,22,151,80,210,231,212,57,166,212,120,238,52,150,167,18,169,244,232,226,155,190,247,45,0,209,
31,124,243,3,107,22,54,245,79,1,128,230,18,150,89,115,7,7,209,213,221,141,129,193,1,0,64,36,28,70,125,93,61,124,94,47,188,62,95,62,106,96,229,148,227,140,101,97,215,174,93,133,49,70,211,112,184,171,11,
131,131,131,232,233,113,86,207,39,215,196,107,127,243,149,75,174,2,128,23,14,6,15,92,127,199,119,255,130,226,74,113,154,147,57,146,59,14,35,176,59,40,200,214,64,34,141,135,86,14,171,10,67,152,4,50,1,60,
235,136,32,80,58,252,107,203,3,60,48,224,25,58,183,49,228,13,135,66,232,239,239,135,149,6,204,116,62,77,14,211,27,77,63,81,19,197,10,89,244,91,77,144,213,179,23,128,191,35,138,206,183,44,198,210,98,110,
162,225,198,27,111,44,250,194,111,255,234,83,123,31,255,219,171,3,10,222,104,237,134,0,0,32,0,73,68,65,84,210,71,7,6,153,4,210,65,53,41,13,168,212,53,95,168,8,52,47,75,3,224,250,225,255,62,117,80,38,128,
175,238,216,129,170,170,42,180,21,146,200,229,170,103,241,216,2,96,236,24,168,124,232,198,43,58,38,247,244,244,96,223,254,172,187,70,139,194,120,186,173,189,29,46,93,47,140,74,34,185,47,55,160,218,200,
103,142,0,214,86,86,22,135,106,45,171,16,206,35,255,211,115,249,126,154,219,237,24,222,61,60,104,196,14,14,185,71,158,219,114,168,247,206,31,62,180,103,112,36,78,195,114,42,251,138,24,138,147,228,169,
89,176,248,32,113,94,37,182,238,58,60,186,117,215,225,30,20,138,134,228,14,23,42,91,34,217,10,66,69,2,229,14,2,128,115,223,93,85,27,49,90,136,227,222,181,255,200,240,155,63,114,119,191,32,25,119,188,237,
138,150,91,47,174,105,118,25,208,90,219,219,209,154,203,129,253,243,35,143,224,231,191,254,53,154,27,27,177,120,225,130,34,242,244,149,91,103,156,247,190,235,102,79,185,232,93,247,62,2,123,181,183,184,
54,50,226,218,48,162,115,119,76,240,109,158,228,54,12,88,0,118,238,222,125,204,23,251,164,137,29,48,244,236,251,25,154,134,74,201,247,46,15,195,192,164,41,83,148,255,218,120,80,75,223,242,217,159,247,
244,13,140,208,130,133,81,216,115,27,71,20,143,71,164,5,26,13,117,38,20,164,199,116,32,239,114,231,28,106,167,164,178,125,169,0,16,88,50,209,222,141,4,176,23,127,220,251,200,192,176,226,92,162,158,157,
226,154,206,231,46,235,26,130,159,184,2,87,203,227,214,181,215,92,83,84,209,190,234,93,247,111,132,221,75,176,95,34,128,35,18,1,52,21,139,152,204,24,74,54,37,53,244,186,145,189,22,125,0,188,111,189,227,
63,254,15,192,211,0,42,166,180,215,215,124,242,189,215,76,157,82,147,140,68,131,166,109,193,112,206,180,105,136,86,87,163,183,183,23,0,80,93,93,141,230,182,146,174,78,104,148,22,164,221,71,142,192,178,
44,244,15,12,224,240,225,195,232,235,235,131,166,105,136,230,194,196,126,137,12,206,105,26,105,222,182,126,237,155,186,134,93,35,111,254,228,175,254,180,255,240,209,126,197,249,69,171,228,71,114,231,192,
72,238,120,141,74,95,137,146,64,218,154,147,137,31,19,64,38,130,114,244,8,118,179,205,60,9,220,176,165,171,247,220,198,72,77,180,186,26,93,185,28,146,84,42,149,127,97,109,133,69,157,231,253,228,194,75,
16,53,204,13,192,123,209,84,156,191,164,19,69,165,160,83,59,59,177,104,169,157,19,110,62,108,140,94,125,251,125,187,20,196,143,230,20,201,33,2,218,98,137,230,255,201,249,32,58,81,236,146,18,249,19,191,
195,247,243,13,169,67,64,161,187,129,223,239,67,216,94,133,44,219,223,8,18,97,2,208,94,220,209,127,32,213,176,234,133,165,147,246,204,57,146,155,124,106,114,197,12,20,30,162,28,28,183,3,108,101,59,100,
12,198,245,84,223,168,158,236,27,53,18,207,189,188,99,240,87,15,253,181,247,240,145,129,56,138,219,56,169,10,129,104,136,110,84,17,214,19,149,158,41,162,244,202,225,217,116,238,57,195,176,23,192,208,202,
103,249,220,52,29,84,63,211,97,163,197,76,78,228,15,80,91,136,200,197,4,114,127,91,207,55,239,251,221,232,55,239,195,30,67,215,189,191,250,183,155,207,153,86,159,14,2,192,202,229,203,177,121,203,22,108,
222,182,13,191,248,245,255,32,92,81,129,165,139,22,229,115,11,1,160,181,50,93,177,109,253,218,215,93,242,161,223,254,113,247,129,94,74,118,13,114,125,184,110,251,198,131,255,251,202,125,111,252,160,56,
23,166,118,118,98,52,153,196,190,253,251,148,87,174,133,172,81,246,110,7,162,168,185,221,88,118,254,242,194,203,156,251,121,59,226,218,79,254,113,104,227,246,131,180,64,131,86,178,14,18,101,107,88,65,
2,71,137,226,71,173,78,104,110,174,42,63,87,69,214,229,156,93,185,229,27,85,254,2,0,130,23,157,99,247,16,109,159,48,1,13,205,249,54,212,248,151,239,253,122,72,82,206,64,62,195,7,187,111,169,119,122,19,
206,121,253,92,216,226,231,46,195,192,63,188,229,45,69,251,109,202,13,235,158,87,40,127,3,228,190,216,63,41,178,248,76,195,185,255,175,229,160,0,202,161,205,12,236,133,22,130,168,211,206,48,22,128,212,
182,221,93,137,155,254,223,247,250,96,247,138,116,1,112,121,61,46,247,21,203,207,141,180,213,85,135,234,42,61,158,41,85,117,174,68,175,225,242,187,44,61,224,182,116,175,219,50,124,110,123,74,133,60,134,
9,213,188,21,217,52,10,13,64,111,111,47,116,195,192,238,189,123,17,8,248,209,88,223,0,143,228,234,80,95,145,14,62,242,239,87,93,121,100,216,53,114,213,135,215,63,210,215,63,34,246,23,53,178,246,72,99,
200,8,57,71,226,228,237,68,177,136,147,234,199,100,240,36,131,115,0,79,221,62,87,37,80,211,240,137,48,98,174,1,80,159,35,62,77,1,159,183,233,133,7,110,184,124,100,160,31,79,63,187,1,35,177,24,26,26,26,
176,112,222,60,192,229,18,3,222,30,105,181,54,74,73,129,161,193,251,241,203,113,169,74,124,90,115,249,229,136,74,164,232,75,235,119,117,221,255,203,191,116,195,158,7,66,43,232,100,2,72,213,63,185,47,172,
170,251,130,75,82,45,43,144,205,155,137,2,168,70,54,143,168,6,64,244,83,107,236,189,108,163,213,213,88,182,120,49,42,107,106,240,129,111,63,183,235,15,127,121,101,47,178,249,60,34,167,103,144,40,159,30,
0,193,107,46,154,123,206,87,223,121,238,27,203,57,88,169,52,172,88,82,51,69,97,67,44,169,167,135,147,154,57,20,183,210,59,118,237,143,191,178,109,111,108,195,203,187,134,135,70,226,38,212,249,110,84,61,
144,45,126,100,82,69,187,191,200,221,47,210,176,39,199,39,36,18,62,74,72,55,109,243,231,86,132,227,132,21,137,240,164,115,73,147,82,41,5,48,93,130,0,150,202,255,179,74,156,255,244,58,160,45,189,100,242,
167,108,167,165,105,154,239,15,223,190,121,70,71,77,86,57,217,182,121,51,158,222,176,33,123,126,68,163,88,113,254,249,168,144,20,142,180,9,107,250,63,172,251,31,100,115,101,251,115,251,80,84,141,123,0,
84,188,127,237,37,243,222,191,166,225,130,241,92,220,251,9,1,164,172,64,119,185,208,220,210,114,76,3,199,111,95,214,19,119,124,225,254,163,132,248,139,28,185,1,114,159,18,65,106,240,76,195,196,178,255,
155,124,12,85,225,78,167,241,74,92,183,1,233,186,21,227,86,125,117,16,147,222,187,18,43,232,155,173,88,182,12,109,57,239,191,209,20,172,217,111,93,119,72,161,106,143,194,222,243,216,5,192,251,238,11,112,
97,77,200,30,86,159,62,117,42,230,47,90,100,251,194,3,113,45,189,224,166,7,94,34,228,79,228,67,247,146,141,30,127,167,10,232,82,253,144,157,22,50,242,190,17,169,56,162,173,102,24,5,207,213,16,185,30,41,
161,242,192,222,39,88,246,38,149,243,201,157,8,42,206,63,175,179,226,198,215,175,170,157,24,77,5,219,170,77,155,187,67,50,22,195,209,163,71,145,76,167,81,225,247,193,235,243,59,230,9,110,234,246,245,92,
243,254,255,122,148,44,48,6,200,57,215,143,66,126,173,152,123,18,100,254,161,29,120,84,57,129,142,223,159,193,10,224,217,160,0,90,10,213,207,102,222,25,139,39,146,0,16,140,84,34,20,14,195,2,176,119,223,
94,116,29,62,140,233,231,156,131,230,198,70,116,182,214,250,182,239,59,66,123,136,186,115,239,131,206,58,52,189,105,1,138,226,75,85,117,117,184,252,226,139,225,146,44,58,230,189,253,167,219,134,178,230,
177,52,135,104,72,161,56,208,220,34,185,248,67,149,39,6,20,247,49,21,131,129,120,44,135,170,146,153,12,44,218,234,42,224,247,163,50,55,88,45,154,59,45,248,135,191,188,34,251,244,209,125,10,0,198,127,63,
252,252,246,7,159,216,248,93,11,168,24,141,39,229,85,44,29,100,1,117,11,54,217,172,27,10,194,147,113,248,187,138,236,169,66,169,212,196,149,230,79,202,5,55,180,74,143,238,239,12,81,80,168,2,33,138,3,124,
144,236,111,80,126,8,88,229,233,232,212,51,214,105,48,167,189,83,101,98,161,82,151,196,22,128,148,99,102,89,86,234,210,219,238,123,233,130,5,83,107,238,254,200,162,137,205,77,5,101,169,183,183,23,127,
253,219,223,176,114,229,74,64,215,137,90,4,45,71,134,229,2,165,124,216,238,91,235,30,220,180,117,199,140,228,183,63,48,111,117,185,23,114,139,221,146,201,17,163,41,88,7,251,245,212,254,126,205,220,188,
179,43,253,248,134,205,169,237,123,187,241,229,15,95,87,113,225,84,117,145,206,244,70,203,144,20,165,56,33,55,3,57,50,67,175,73,167,197,24,29,83,84,125,145,85,38,228,178,79,167,28,105,160,62,135,180,149,
100,197,27,231,97,145,252,91,104,39,153,167,119,234,41,168,189,243,68,5,191,5,64,159,213,130,105,175,155,93,92,164,54,117,202,148,34,242,247,231,237,158,254,119,126,242,238,237,40,120,30,138,144,111,63,
33,125,67,40,14,253,166,29,84,80,107,12,114,98,57,92,51,226,250,165,231,58,200,245,45,142,35,93,144,249,200,185,175,234,80,228,212,159,220,81,224,121,252,185,237,131,143,63,183,253,48,33,143,70,67,109,
196,251,173,79,188,177,115,118,83,32,82,79,20,195,3,123,246,160,183,175,15,219,118,236,192,210,69,139,224,39,170,224,244,186,120,205,182,245,107,223,240,205,255,62,240,210,119,127,252,240,22,242,125,233,
119,165,45,52,225,48,110,202,33,96,86,255,152,0,158,245,228,79,38,12,180,207,43,29,156,178,234,70,85,21,96,89,185,214,92,9,236,221,183,15,241,68,2,111,184,160,163,242,43,63,60,146,34,131,142,7,64,230,
154,57,152,60,179,25,54,141,223,48,116,172,56,127,185,45,177,30,0,118,245,232,201,75,111,187,127,59,156,141,99,105,254,12,53,81,149,109,20,82,176,23,37,152,138,137,133,182,168,211,81,92,141,152,31,156,
55,29,194,240,204,102,228,19,124,188,94,15,144,243,162,171,175,169,116,163,216,164,153,246,9,206,43,28,177,120,82,180,60,18,173,152,84,38,191,178,207,155,83,130,183,220,221,196,82,28,207,140,3,145,42,
165,170,201,139,0,149,95,151,170,200,134,154,176,234,40,110,151,38,155,95,211,65,219,169,237,156,37,173,220,83,10,53,211,146,38,78,149,103,154,86,66,5,52,164,5,1,205,253,146,139,11,132,162,146,79,47,120,
108,195,214,204,212,55,109,27,217,116,255,117,54,207,155,189,251,247,99,247,238,221,104,151,12,135,21,33,172,4,217,127,9,0,177,7,159,216,184,107,202,19,27,215,255,195,85,75,38,223,241,198,169,51,35,190,
242,43,168,187,135,180,212,222,163,70,226,175,91,186,98,119,253,228,225,190,156,74,76,197,65,250,187,93,0,140,119,253,211,253,137,109,235,215,54,2,192,171,91,183,226,197,23,95,196,5,231,159,143,186,166,
38,116,212,88,46,216,211,1,228,86,105,84,145,31,130,189,243,137,108,197,164,242,227,44,165,250,81,18,66,173,94,60,68,89,22,149,251,97,66,0,195,117,161,226,34,152,52,49,115,255,215,251,254,48,42,237,7,
55,37,5,213,65,4,223,187,18,115,229,247,240,135,195,184,104,197,10,84,147,174,39,253,49,45,125,249,29,63,223,214,219,63,50,44,169,84,253,57,245,239,40,33,131,98,95,81,101,84,165,250,101,202,36,127,154,
52,118,235,40,164,21,208,69,15,37,134,226,24,6,200,185,72,199,35,217,160,158,42,229,122,25,145,60,217,113,34,79,226,15,31,25,112,93,119,199,61,3,0,92,154,166,185,126,240,181,91,206,89,208,154,172,162,
249,133,71,142,28,193,225,141,27,49,255,188,243,160,19,207,201,59,174,105,158,245,134,21,183,116,172,126,247,61,15,195,222,235,90,151,126,167,5,117,245,175,156,94,192,228,143,9,224,89,67,248,156,170,159,
156,154,123,219,202,234,251,98,122,162,58,144,241,54,228,18,125,135,114,237,184,14,28,60,136,125,7,14,32,147,206,95,144,26,0,61,236,67,232,3,23,193,86,202,235,15,4,48,251,220,115,49,101,234,212,162,47,
248,208,22,247,224,109,159,185,103,47,236,57,102,52,212,68,7,79,89,105,72,72,97,203,52,212,21,161,180,146,48,63,47,160,184,79,165,109,27,28,213,82,89,107,188,92,95,89,189,240,242,160,199,146,205,121,197,
103,10,210,100,17,69,76,12,190,195,10,37,76,119,32,66,150,98,98,40,69,0,45,197,223,77,133,234,98,162,184,113,187,220,148,157,146,64,19,246,118,77,78,166,189,116,31,83,21,80,238,109,235,82,16,95,203,65,
65,53,37,162,167,34,17,78,158,95,182,181,135,34,132,86,52,73,17,101,65,76,142,52,199,140,22,47,152,0,44,203,178,244,115,110,250,233,198,79,92,142,25,68,240,195,99,143,63,142,160,223,111,171,58,69,113,
119,15,72,199,32,127,14,253,232,127,159,218,252,163,255,125,106,47,138,123,183,58,229,77,90,14,231,5,221,31,42,27,40,247,238,94,45,213,30,181,220,147,167,76,193,83,207,60,35,247,93,54,37,53,152,170,192,
148,244,200,6,202,242,245,104,66,109,201,65,201,185,1,69,81,14,138,67,242,52,252,27,33,91,232,154,57,197,197,31,213,149,149,8,250,253,48,227,113,24,62,31,182,238,58,108,193,30,86,206,167,170,220,184,4,
83,91,170,236,213,251,21,193,32,46,188,96,57,170,106,235,108,11,214,183,124,234,231,123,122,142,14,211,104,197,16,25,183,250,136,250,55,0,187,101,146,19,249,147,67,191,227,141,228,164,20,99,60,29,3,104,
62,239,136,164,166,169,22,105,110,105,161,166,59,124,174,138,4,234,80,87,108,187,1,184,45,203,242,190,229,35,119,63,7,192,115,221,229,11,235,191,120,243,180,41,162,184,106,66,71,7,254,244,200,35,56,112,
224,0,46,189,232,162,124,95,240,9,85,169,208,182,245,107,175,89,242,174,95,254,177,183,127,88,30,67,228,126,197,116,209,97,144,241,193,4,231,2,50,1,100,5,80,25,90,148,187,104,164,0,36,95,233,242,247,92,
208,49,210,28,140,68,208,0,11,125,71,143,2,200,22,131,12,143,140,192,235,202,171,106,250,130,54,84,95,58,179,208,209,195,237,118,99,82,71,7,166,159,51,13,21,10,139,137,47,252,100,103,215,186,95,61,222,
13,123,114,185,168,154,235,151,20,64,154,175,163,10,49,201,19,77,70,161,44,208,1,74,181,74,180,109,65,191,97,184,12,192,48,12,120,60,110,4,136,125,66,202,212,100,2,34,136,21,109,97,164,145,73,211,43,41,
76,178,18,166,57,168,179,153,50,200,159,138,16,149,34,129,105,216,109,86,104,21,175,220,211,179,104,81,128,226,220,26,75,218,207,41,216,43,94,229,102,245,78,161,36,167,230,243,114,88,91,85,209,238,52,
41,233,40,14,177,203,94,106,178,218,36,200,159,87,161,48,83,171,16,23,0,215,151,126,143,109,159,90,99,79,117,216,182,99,187,76,0,221,146,154,98,73,33,59,74,176,197,57,227,151,38,102,189,196,100,172,58,
79,228,253,96,200,191,239,214,47,252,102,239,67,223,92,51,9,154,134,246,182,9,232,58,116,40,95,233,236,243,184,17,79,166,228,243,128,230,133,198,81,92,128,229,212,217,98,44,242,231,82,40,126,244,187,82,
207,206,10,137,252,69,0,84,206,108,70,145,121,97,95,127,63,94,122,229,21,236,63,112,64,116,133,161,251,1,134,6,227,250,5,104,152,84,91,32,126,149,85,85,88,188,96,1,234,164,246,133,67,113,100,230,221,180,
110,183,131,34,58,152,35,124,226,246,40,89,188,142,144,69,107,170,68,232,87,181,136,113,170,0,150,85,64,21,193,161,100,136,30,163,81,66,254,60,146,58,77,21,54,67,17,94,205,64,157,122,65,23,26,114,213,
182,75,65,228,189,0,188,63,251,253,179,241,159,253,254,217,195,239,122,211,170,214,15,95,219,210,1,0,43,207,63,31,207,191,248,34,126,255,199,63,162,115,226,68,44,61,255,252,252,23,120,234,123,175,95,253,
174,111,60,251,236,159,158,221,178,91,186,14,84,61,137,229,5,164,230,48,214,50,152,0,158,181,68,80,38,11,105,170,244,220,241,249,251,54,253,237,222,235,155,129,108,46,96,52,215,38,44,147,201,96,120,100,
36,59,96,250,225,125,223,170,108,75,164,218,218,90,52,54,54,162,165,185,89,89,245,42,112,205,39,254,184,119,211,142,131,3,210,0,58,0,123,254,12,109,29,37,91,143,168,252,179,204,18,161,37,40,212,19,77,
241,188,252,214,94,235,246,185,221,217,14,9,126,159,15,85,164,43,194,211,47,110,143,149,32,128,113,18,182,164,133,39,114,14,156,156,95,163,10,1,91,10,98,155,145,20,206,76,137,99,234,100,158,108,42,238,
171,84,193,140,66,205,49,81,156,151,72,39,243,180,131,202,166,34,188,112,24,144,77,135,208,14,202,84,253,156,66,84,114,158,153,46,133,188,4,233,72,228,38,42,26,202,164,185,142,212,138,196,123,215,99,56,
124,235,5,164,202,189,248,27,233,138,144,85,74,90,44,36,36,133,141,18,64,67,17,142,43,53,41,155,138,207,167,6,240,1,0,193,61,7,123,243,251,113,98,123,7,30,121,244,81,52,52,53,161,165,173,13,95,255,228,
77,209,247,125,230,238,62,233,252,78,43,22,58,9,20,219,187,164,75,40,91,154,164,206,186,80,28,234,245,74,196,143,26,63,11,195,241,170,220,109,228,134,249,197,185,127,2,71,7,6,112,116,96,64,132,111,13,
0,240,185,160,253,195,66,212,52,85,21,8,78,192,235,197,228,73,147,48,115,250,116,24,138,234,252,144,47,159,226,32,200,223,144,20,169,56,74,198,45,161,252,81,75,156,4,138,83,68,202,45,80,176,20,11,38,218,
255,86,87,140,127,25,197,53,156,36,231,183,216,199,98,193,239,203,61,135,122,184,202,33,86,85,191,117,149,113,119,169,252,90,218,182,207,15,32,240,189,159,60,178,227,123,63,193,193,31,126,237,29,51,22,
76,64,229,121,243,231,99,223,129,3,216,190,115,39,118,236,218,133,43,46,189,52,111,192,254,189,15,47,92,248,150,207,199,205,13,175,236,134,20,185,162,189,134,233,126,166,45,73,89,245,99,2,120,214,147,
63,149,2,72,7,136,188,26,49,52,18,143,209,23,55,212,215,229,26,208,102,112,168,171,11,0,32,200,159,174,105,8,7,131,104,136,70,75,146,191,57,55,253,100,103,44,158,148,195,189,253,82,216,100,16,246,10,175,
184,68,174,210,138,48,10,20,42,131,174,32,27,242,42,213,45,109,46,0,70,91,173,199,171,107,26,124,126,63,194,161,10,155,153,238,207,126,255,76,159,34,220,144,146,38,68,186,242,148,195,91,6,138,243,210,
160,248,29,150,98,18,53,21,74,161,76,254,160,32,144,25,41,28,162,154,128,84,85,195,22,212,182,43,242,192,79,137,155,174,8,33,201,57,121,250,24,170,135,211,111,84,61,191,84,187,44,40,84,39,249,60,160,45,
191,228,243,75,174,184,20,197,8,121,181,171,107,8,182,235,36,158,76,0,166,9,72,133,78,146,50,147,38,106,154,149,35,9,242,68,41,219,94,200,161,115,107,12,101,134,18,115,154,219,24,23,191,111,195,94,79,
255,130,9,201,202,150,182,54,84,70,34,121,223,201,5,173,169,10,148,231,25,154,150,212,151,180,195,57,162,82,254,104,248,93,252,94,17,118,247,43,110,69,183,11,17,2,174,170,14,162,97,114,253,216,45,162,
61,110,55,162,65,184,111,90,130,64,192,11,205,48,116,248,125,126,4,131,65,84,134,195,249,238,21,70,9,107,166,139,151,78,119,63,244,228,166,30,216,211,84,142,146,251,162,224,131,22,125,80,242,151,84,236,
159,114,171,83,101,19,104,89,237,211,201,194,194,68,161,168,165,148,167,166,170,69,166,73,206,123,58,94,208,249,33,133,210,253,155,117,133,234,236,38,234,31,61,174,130,212,167,222,242,209,187,95,186,102,
245,121,141,95,189,117,230,228,153,211,167,227,137,167,159,134,101,89,248,221,67,15,101,73,96,206,207,242,135,159,190,96,201,165,31,26,74,238,58,208,107,74,234,57,45,90,19,230,252,6,25,215,84,41,81,76,
8,153,0,158,85,202,159,138,28,152,100,112,178,181,84,139,167,52,211,151,235,167,26,8,71,208,144,123,151,182,9,9,236,217,187,55,255,134,211,166,78,197,140,105,211,224,119,40,235,7,128,41,55,172,219,65,
86,207,52,220,219,71,212,63,90,244,33,6,80,185,123,128,202,57,223,42,49,241,211,48,36,245,240,163,33,143,252,125,93,131,215,239,247,195,208,117,84,84,84,160,185,169,9,46,127,193,209,96,96,104,148,14,124,
105,105,16,74,194,110,135,3,168,45,72,180,49,86,165,165,242,251,100,178,8,7,85,80,69,162,76,133,122,89,42,239,208,41,7,81,53,81,169,66,239,154,195,227,82,19,157,124,91,138,240,149,51,120,203,42,176,166,
56,30,66,69,241,72,19,163,32,41,62,149,250,28,13,192,251,158,11,97,171,250,152,61,99,166,138,252,21,117,107,32,170,159,73,20,49,67,58,47,229,240,177,230,112,142,80,229,79,54,63,55,96,207,163,19,231,166,
117,235,167,215,189,252,194,3,111,90,14,100,139,189,70,19,89,39,163,170,160,229,82,76,234,242,231,170,20,101,85,138,130,230,112,44,40,1,244,74,42,95,69,238,190,32,10,21,185,91,90,252,17,81,21,109,168,
224,246,120,240,158,149,200,23,214,24,134,145,221,116,29,154,174,67,211,116,248,3,126,199,215,155,22,172,193,145,248,48,236,149,208,71,97,79,89,17,139,86,81,240,49,42,145,63,167,253,116,172,227,57,20,
251,89,28,99,183,195,53,76,149,97,250,94,110,183,142,96,58,3,88,246,107,45,77,8,38,205,247,76,161,56,247,90,67,113,177,141,88,216,248,81,240,247,171,144,212,227,204,127,255,241,57,107,215,190,238,228,
15,62,186,96,70,254,135,154,38,182,108,221,138,101,196,208,252,255,254,117,205,138,41,55,172,251,45,236,33,121,74,186,83,210,53,35,111,76,250,152,0,158,21,164,143,174,116,232,42,40,163,8,239,208,162,133,
56,128,248,51,251,2,135,87,76,28,41,52,62,143,68,208,168,101,7,84,65,0,235,235,234,208,218,220,236,72,254,186,135,52,243,252,119,60,176,23,5,131,210,65,50,120,202,21,115,212,96,150,86,232,170,114,139,
100,50,162,57,132,221,232,196,234,129,212,60,94,82,29,124,215,207,199,188,112,56,4,151,110,160,178,178,18,245,117,69,138,166,76,254,168,127,94,82,34,10,42,245,67,87,132,37,75,145,29,85,174,91,41,162,52,
86,142,99,198,225,253,157,242,123,50,99,124,7,39,162,37,79,8,192,248,60,65,173,49,30,143,151,0,102,20,251,61,131,98,59,9,72,138,32,53,22,183,77,116,239,185,16,211,196,27,70,34,17,84,70,34,182,106,81,41,
28,39,171,237,180,48,128,126,55,185,104,70,35,99,168,14,117,75,48,21,161,208,36,229,82,238,126,227,138,197,147,249,146,203,218,218,90,28,60,120,16,109,173,173,194,224,87,149,67,11,233,179,157,122,175,
202,223,71,54,195,166,139,49,113,61,86,16,133,175,146,144,193,0,33,131,21,0,42,42,188,168,250,224,106,204,43,247,68,114,231,188,75,131,1,63,42,42,66,57,213,47,138,198,134,250,146,109,240,222,241,213,167,
247,61,246,183,109,189,82,196,162,79,34,128,242,184,37,59,20,208,142,31,25,135,235,169,156,243,89,21,10,118,90,132,233,138,5,1,85,95,139,250,164,47,238,192,218,213,211,179,254,167,243,231,206,197,19,135,
26,127,243,181,123,126,247,50,10,221,107,82,100,254,160,98,129,42,231,147,70,89,12,50,238,138,14,37,180,59,12,205,219,195,139,91,247,107,159,248,126,213,206,21,205,145,137,253,3,217,182,116,59,118,236,
128,110,89,88,66,114,2,31,250,238,45,23,92,252,158,123,30,36,243,138,216,255,222,220,223,92,132,8,106,96,63,98,38,128,12,229,164,161,82,178,70,1,196,111,253,199,239,190,176,109,253,90,155,187,190,63,28,
65,107,56,130,166,237,219,113,240,224,65,120,220,238,108,248,72,129,205,135,181,212,213,183,63,112,64,65,254,142,162,96,152,42,15,162,114,213,156,74,245,83,245,14,85,17,63,170,240,249,96,183,248,16,118,
18,66,109,8,52,85,162,169,179,14,21,209,170,106,184,12,3,181,181,53,112,249,10,202,192,190,163,122,18,197,198,201,41,5,249,163,86,31,150,66,73,41,149,11,39,147,43,39,213,45,83,66,57,83,189,215,88,170,
33,28,8,34,48,62,155,10,39,51,102,140,147,4,102,198,73,16,199,34,128,170,206,32,144,22,72,242,226,8,138,227,103,0,48,174,158,147,85,159,220,110,55,66,21,65,212,70,107,48,185,115,18,116,111,161,152,116,
251,17,61,1,117,14,29,173,204,76,16,130,169,234,127,75,149,188,82,231,138,172,184,201,97,214,128,164,54,122,0,184,55,118,121,123,103,212,39,162,141,13,13,216,188,117,43,186,143,28,65,75,91,27,62,121,219,
181,77,95,252,207,95,13,72,139,40,67,82,81,244,50,201,40,20,139,51,234,241,39,174,197,200,71,47,198,157,94,15,124,191,123,25,79,63,183,23,175,208,5,154,219,64,248,234,57,152,53,173,97,236,176,175,76,0,
155,26,234,17,170,8,161,165,185,25,181,181,181,37,59,241,252,250,69,109,240,163,95,122,224,0,81,150,104,186,202,81,66,2,85,227,150,108,72,108,162,60,203,23,171,204,243,88,181,192,7,236,190,119,162,88,
137,86,154,139,227,70,201,154,56,175,124,130,252,1,89,247,131,91,47,169,185,242,107,255,159,189,235,142,143,163,186,214,223,148,157,237,187,170,171,106,75,114,239,114,175,216,128,193,198,128,129,96,66,
192,128,77,9,161,164,240,18,90,40,73,200,75,242,72,94,26,47,15,94,32,16,192,166,67,40,1,67,0,19,140,193,133,96,192,96,170,113,149,229,110,117,173,182,239,204,125,127,204,220,217,187,119,103,87,146,171,
76,246,254,126,243,91,105,181,59,154,153,123,238,189,223,253,206,57,223,121,16,219,12,251,17,56,16,8,230,119,118,30,228,199,63,63,15,83,176,111,197,32,154,172,240,178,183,63,221,95,112,98,113,105,141,
39,37,197,181,121,219,54,12,26,56,208,76,176,170,41,74,120,57,150,152,15,155,160,146,75,18,115,221,121,16,152,7,128,121,240,103,193,76,168,72,215,125,163,153,107,225,96,76,140,123,237,153,186,100,211,
167,76,193,179,47,188,128,186,218,90,216,185,210,62,0,176,122,139,24,191,226,246,37,251,145,18,146,165,90,89,29,22,59,232,78,164,171,228,199,56,134,77,237,1,211,193,187,30,172,88,63,202,42,152,250,97,
48,20,243,37,1,190,43,102,232,172,66,121,89,25,108,146,4,59,87,235,243,209,229,91,155,145,25,119,146,150,61,141,244,96,100,62,65,165,183,64,72,203,1,136,178,197,206,101,115,153,146,30,0,199,222,48,141,
185,154,136,236,110,249,222,2,193,67,97,255,144,5,252,105,220,53,242,11,50,235,62,98,153,12,51,92,96,180,145,121,234,241,184,81,92,88,132,138,242,114,20,5,210,107,163,222,245,196,186,38,206,142,89,141,
69,94,127,210,138,49,19,45,0,171,208,77,255,2,153,217,152,118,110,161,53,99,2,127,112,231,179,31,175,248,211,89,167,120,11,11,225,118,185,64,140,154,223,115,199,22,20,255,87,38,248,227,65,96,111,251,130,
175,197,156,198,0,14,175,192,12,187,162,235,249,157,49,26,83,207,24,141,169,189,157,224,4,0,130,36,66,150,36,200,178,13,118,187,29,14,167,19,46,143,27,126,127,65,183,245,109,167,93,253,220,182,150,246,
80,136,3,127,157,72,23,119,230,231,45,86,8,155,141,247,179,74,136,209,122,241,204,132,94,254,141,88,48,222,188,87,128,47,143,41,3,80,92,14,7,194,81,189,162,218,254,3,7,48,48,28,198,75,247,92,187,224,236,
239,223,251,10,51,102,216,68,18,214,35,98,53,79,91,49,218,172,55,7,72,143,27,78,203,82,127,244,237,150,45,63,57,51,221,197,191,105,203,22,43,137,37,7,210,165,109,108,12,104,21,185,49,15,228,93,192,121,
0,248,111,12,254,0,235,192,110,58,128,35,44,248,3,16,190,225,158,119,215,223,127,195,148,140,137,216,229,245,162,174,166,191,149,240,45,158,88,19,137,254,252,127,255,214,138,84,41,49,86,37,191,13,153,
114,9,157,72,215,19,227,227,253,172,92,74,224,128,31,27,87,196,186,151,216,210,111,110,6,244,153,153,132,0,188,183,158,129,211,233,245,123,10,172,221,66,75,158,95,213,4,235,160,227,24,172,229,116,122,
82,173,130,103,117,208,13,179,151,141,29,235,137,164,68,111,128,99,119,32,35,87,83,115,44,94,7,179,11,23,14,146,5,228,89,62,171,236,111,158,57,150,153,159,249,196,12,7,0,229,212,225,152,76,79,82,224,47,
64,160,180,20,253,45,198,193,27,107,191,232,224,192,31,31,214,192,74,116,168,200,44,95,152,45,137,38,27,203,203,50,115,44,0,76,130,171,115,75,153,147,93,251,218,218,233,201,252,62,47,182,54,54,162,172,
162,2,21,62,151,3,153,238,104,246,16,187,233,227,108,90,113,124,141,95,154,24,224,58,115,52,22,31,202,4,39,8,2,108,178,12,89,150,161,40,10,92,46,23,124,94,47,202,74,75,81,22,8,64,80,178,235,107,191,246,
133,45,120,221,127,62,184,27,233,217,216,172,204,11,155,176,198,198,252,177,155,214,108,229,221,52,116,159,189,46,28,226,88,64,22,239,129,128,236,241,210,230,92,57,124,100,125,252,195,15,223,83,0,96,255,
254,253,104,107,107,195,176,42,87,181,32,8,62,66,8,203,0,210,121,79,70,102,56,128,149,215,131,50,224,50,172,99,66,41,240,11,35,61,52,39,249,81,35,66,227,250,231,100,123,217,114,118,188,214,168,152,103,
252,242,0,48,15,250,50,227,0,37,100,202,132,176,174,169,52,193,215,149,235,190,218,189,179,125,70,168,95,65,50,99,32,54,52,238,196,208,125,123,17,168,72,149,197,250,209,189,27,194,27,183,154,197,228,249,
201,148,77,246,96,165,94,172,38,208,164,197,174,153,93,68,132,44,172,31,27,88,174,48,19,10,101,252,104,140,81,33,128,66,73,64,241,173,103,224,172,238,30,228,71,187,100,54,46,145,130,100,190,146,8,239,
246,73,246,16,0,30,14,230,139,116,195,32,246,4,40,106,135,153,121,235,238,58,187,155,160,197,94,44,134,221,1,108,49,11,168,226,5,136,249,122,192,25,241,162,83,7,192,12,12,45,45,41,70,101,58,43,1,0,216,
214,44,198,185,5,147,175,168,194,191,178,182,146,141,41,238,13,72,16,153,251,33,204,92,76,235,54,135,140,13,81,164,169,75,10,151,122,84,87,113,81,49,34,123,246,88,157,199,74,204,91,202,194,80,230,36,231,
184,131,205,196,119,58,108,233,98,204,185,90,117,117,53,236,138,130,230,230,102,196,19,9,72,134,34,183,36,73,176,43,10,220,110,55,10,253,126,148,150,148,160,44,71,125,228,205,7,196,248,217,255,241,200,
14,85,211,168,231,35,196,204,75,108,134,111,39,199,250,177,224,47,10,235,36,53,43,233,166,195,181,249,201,246,247,108,177,130,86,33,26,102,150,184,82,53,121,71,81,195,150,193,173,45,45,136,37,18,72,36,
116,143,238,178,123,190,51,103,254,247,238,127,3,233,85,69,34,76,191,69,97,93,206,145,93,123,84,100,198,224,202,220,156,153,33,57,245,207,47,177,123,92,255,148,206,38,101,167,1,32,18,55,215,50,153,219,
148,240,44,181,128,131,143,67,206,183,60,0,252,90,130,66,186,19,227,19,26,88,197,120,58,17,186,78,185,250,161,119,54,61,189,248,244,140,19,17,130,173,219,182,155,0,240,205,141,66,226,174,107,235,93,154,
86,239,26,182,240,145,38,164,215,246,101,117,179,216,234,30,81,88,151,144,226,69,70,173,22,19,86,199,141,46,80,180,226,6,93,188,217,242,81,180,64,122,33,128,130,82,15,106,174,62,17,39,179,39,182,59,28,
150,15,237,162,155,150,108,231,192,95,56,203,245,243,242,24,218,65,48,104,64,207,235,130,246,20,108,29,108,82,197,225,202,84,236,9,227,9,228,142,213,57,152,201,219,10,248,89,177,197,54,14,240,121,144,
94,115,214,3,192,53,186,10,105,37,224,42,43,42,45,19,160,46,184,229,233,6,164,215,82,142,112,44,55,95,198,48,105,1,22,122,179,104,9,22,99,131,13,65,16,153,205,17,91,78,49,246,216,155,141,27,127,116,78,
213,248,242,178,0,62,223,184,17,251,155,154,208,175,166,6,151,45,152,89,177,228,249,85,65,164,103,207,91,149,11,19,122,112,77,60,168,204,16,14,238,95,93,13,155,162,231,165,180,182,180,162,205,72,2,224,
219,176,1,3,48,217,72,8,104,109,58,128,246,142,14,216,100,25,197,69,197,112,229,80,34,248,238,159,62,140,253,115,237,231,49,11,22,159,142,103,182,178,71,144,219,172,178,85,137,216,76,223,184,69,31,242,
245,170,123,51,142,122,243,44,123,2,4,179,37,147,165,141,183,91,255,248,247,85,143,222,124,226,224,13,159,125,138,77,155,54,67,53,62,50,164,36,90,98,216,62,171,117,202,30,50,210,99,155,173,146,205,216,
181,38,155,22,105,134,154,67,125,21,202,32,8,16,0,20,22,20,164,213,11,222,31,52,107,59,243,182,148,111,121,0,152,111,61,0,21,86,73,32,86,74,247,46,0,174,43,126,247,238,135,15,221,52,45,35,243,78,211,52,
116,68,64,58,194,130,118,202,48,98,211,217,50,41,204,76,144,236,142,58,196,28,124,241,248,100,150,201,32,219,226,33,113,192,143,87,156,103,193,159,143,99,255,252,245,85,152,114,214,216,244,42,14,0,112,
198,105,167,101,60,180,207,246,72,17,131,33,96,171,146,176,58,95,81,11,246,207,74,164,154,28,98,159,29,10,232,58,28,127,239,201,103,132,94,158,35,155,91,214,74,196,91,232,134,233,206,182,96,242,140,31,
15,254,88,1,98,202,22,243,118,227,5,224,62,103,108,74,246,101,232,160,65,240,101,102,253,98,119,187,144,232,8,70,162,220,70,129,101,139,248,88,209,238,42,68,244,6,56,208,251,101,245,224,168,144,177,140,
204,138,30,209,123,159,120,115,203,143,206,89,60,222,229,47,128,203,237,194,214,109,219,80,86,90,138,139,230,12,174,88,242,252,170,173,28,72,86,114,176,44,61,181,3,203,251,155,62,101,10,20,163,234,78,
60,212,133,15,62,250,40,237,195,181,53,181,80,100,57,45,14,172,168,52,128,162,210,0,64,52,64,200,190,254,55,182,130,48,224,143,157,231,194,220,28,21,228,64,95,144,155,191,194,28,248,75,162,123,13,196,
222,140,17,161,135,27,162,108,239,145,28,223,203,54,175,226,147,175,118,118,58,61,39,99,234,212,105,216,180,105,51,222,126,103,21,102,11,34,170,107,106,240,208,127,95,51,241,138,88,145,120,109,0,0,32,
0,73,68,65,84,31,223,247,47,142,32,160,177,119,108,229,144,36,231,73,96,215,25,17,217,53,33,69,158,197,171,45,66,201,133,211,125,126,197,229,132,211,225,68,121,105,41,6,15,31,110,94,111,83,72,76,228,96,
55,243,45,15,0,243,205,98,39,200,74,95,176,42,242,44,8,100,213,238,157,116,160,175,254,96,115,227,181,119,201,210,189,63,154,52,214,156,124,11,10,240,208,107,219,227,23,187,134,137,179,39,148,154,253,
124,233,109,143,238,68,186,62,19,91,59,51,194,45,130,9,88,139,11,139,176,14,138,103,165,49,120,61,63,186,128,179,250,97,172,188,132,31,128,127,209,84,156,89,83,12,47,255,160,38,143,27,7,175,69,70,243,
130,31,61,188,153,99,51,249,90,168,124,208,119,54,177,229,35,205,172,29,137,239,146,195,248,249,238,2,215,249,69,143,149,33,17,179,48,136,221,45,178,60,240,227,179,99,89,240,231,102,0,160,159,221,48,0,
240,78,174,195,36,246,31,140,171,175,183,252,199,167,94,251,232,86,142,85,10,49,182,66,99,254,88,119,161,213,230,71,67,239,92,190,108,156,163,85,176,191,196,1,192,8,243,179,89,8,216,239,245,161,171,171,
75,7,92,69,73,183,5,88,102,221,193,185,180,214,178,109,94,178,9,76,171,79,188,31,127,229,178,147,220,103,2,128,226,246,96,250,9,51,123,1,127,179,131,191,33,23,60,194,62,111,202,98,177,94,142,32,3,248,
88,246,143,2,66,118,211,199,62,51,94,227,47,87,178,90,79,199,132,152,195,134,123,50,246,196,110,128,33,96,93,89,72,219,27,84,218,42,188,241,194,153,211,167,99,213,218,181,166,48,248,9,181,225,10,102,124,
132,153,87,182,92,33,93,63,216,164,11,126,12,243,53,184,109,22,155,119,187,83,129,251,146,105,24,88,92,88,8,111,97,33,10,11,11,80,213,175,127,218,13,133,227,130,85,173,115,171,144,161,124,59,198,45,79,
203,246,93,96,72,44,192,31,203,220,177,130,205,237,111,254,235,203,157,99,22,63,185,166,53,36,36,0,224,47,111,107,7,182,181,160,107,120,121,220,4,127,31,237,148,194,241,68,146,117,49,89,197,63,177,37,
145,52,14,244,89,77,18,236,66,205,198,245,241,11,118,129,113,20,1,40,49,142,128,113,148,14,44,69,253,79,206,196,133,86,224,239,244,185,115,49,108,244,232,140,135,244,192,27,173,7,24,64,204,30,86,37,234,
84,11,64,107,37,182,220,109,61,98,100,215,233,35,135,112,244,212,38,122,243,157,131,177,185,238,18,4,120,91,176,113,182,96,227,222,227,203,236,73,89,236,135,181,35,23,210,171,17,240,201,65,133,0,138,41,
0,28,80,130,33,115,71,192,164,158,70,13,31,110,178,85,108,123,105,131,208,97,176,197,116,147,208,197,129,64,190,164,33,95,30,204,170,10,75,119,71,146,251,126,18,153,165,252,120,189,74,150,9,140,109,110,
118,52,1,64,81,113,17,127,75,60,99,74,15,1,153,101,13,123,194,252,177,160,48,205,251,112,231,189,203,222,191,254,222,143,95,56,220,19,221,247,23,157,38,34,179,100,35,235,238,165,25,190,109,0,90,140,131,
149,167,10,114,155,87,190,180,91,182,18,133,57,75,78,90,216,186,148,101,30,180,250,156,100,97,243,44,40,207,166,127,199,86,248,96,237,69,189,242,151,47,173,0,128,186,65,131,208,191,95,63,236,216,177,195,
252,210,236,41,195,202,185,57,215,197,16,4,148,5,204,54,14,69,14,236,177,73,85,236,57,157,0,28,55,204,193,116,0,8,148,150,162,186,186,42,3,252,1,64,161,139,176,85,62,18,22,155,111,13,221,187,191,243,45,
207,0,254,219,129,62,112,236,31,31,11,24,55,22,42,126,225,148,1,136,209,88,66,152,122,197,210,247,140,69,211,241,171,243,156,195,222,94,245,14,10,124,126,204,156,49,29,23,220,248,82,3,210,3,220,19,200,
212,197,226,21,233,41,219,39,101,97,254,120,119,47,157,76,104,150,175,19,153,229,133,104,236,150,15,128,247,130,137,56,125,112,25,44,211,123,79,63,237,52,148,150,149,101,188,255,228,191,162,205,191,251,
235,203,13,72,175,89,220,193,129,192,40,172,133,170,85,100,151,82,57,150,125,223,23,154,144,131,237,227,221,252,18,7,54,96,193,100,240,114,46,252,249,216,152,53,54,115,144,101,140,217,44,113,186,161,240,
3,240,207,24,136,25,39,15,75,129,63,155,205,134,241,147,38,101,220,212,174,118,33,113,227,157,75,119,49,128,175,139,3,16,209,44,246,98,181,112,245,166,223,172,194,36,192,44,244,180,44,22,43,87,20,103,
216,200,216,239,150,188,253,201,253,55,78,57,165,162,172,28,235,215,127,100,234,1,142,26,82,229,249,108,211,238,14,102,220,177,18,46,18,178,203,109,228,2,127,108,69,20,122,29,33,0,193,151,87,126,178,233,
229,149,159,252,85,18,197,146,123,127,117,245,196,50,79,220,91,226,86,157,177,36,72,91,72,208,246,5,5,245,103,119,61,211,213,210,222,37,206,155,57,218,245,191,223,31,231,233,238,225,44,158,93,38,223,243,
168,101,168,75,136,99,255,216,114,110,93,12,232,139,112,243,153,149,40,189,21,248,35,221,48,124,108,223,229,98,254,132,28,159,35,57,158,49,96,45,54,207,150,127,52,227,150,55,239,56,96,6,93,78,155,60,25,
79,63,247,28,106,118,236,64,117,77,13,126,115,205,212,145,147,223,219,120,0,169,208,154,16,3,0,157,220,220,78,56,230,62,91,98,30,27,95,235,3,224,249,201,153,41,53,134,202,138,10,56,45,66,44,0,192,99,39,
34,210,99,175,227,28,16,236,173,228,78,190,229,1,224,215,26,248,101,115,191,105,220,34,17,51,250,44,12,235,90,185,102,250,191,77,150,132,64,73,49,194,145,8,170,251,245,195,143,31,217,182,211,98,64,178,
241,125,236,196,69,229,41,232,238,144,159,204,4,198,126,178,185,237,216,184,45,30,252,121,0,120,70,87,97,210,57,99,49,194,234,161,12,170,171,195,244,169,83,1,155,45,237,253,132,10,50,249,202,167,55,133,
194,49,62,24,156,13,10,103,11,189,91,233,126,29,110,240,247,117,157,196,172,88,17,145,235,119,27,210,43,118,176,90,103,217,170,149,136,22,44,34,27,239,71,23,47,183,197,166,193,15,192,87,236,70,245,181,
39,97,54,127,193,243,231,205,179,188,145,217,87,47,221,202,176,126,188,75,49,196,216,75,204,130,253,211,14,129,125,37,22,207,133,125,182,236,6,143,30,172,4,77,124,229,251,95,237,5,166,192,233,241,160,
176,160,0,91,182,110,69,160,180,20,183,94,117,102,221,197,55,222,191,31,233,9,32,50,7,204,179,233,20,194,130,125,210,56,214,134,110,56,105,159,216,1,72,170,166,225,170,219,238,93,107,244,137,25,138,194,
140,127,219,107,171,62,77,194,2,0,170,209,40,36,38,153,171,192,149,230,22,103,129,39,31,166,194,198,107,178,238,250,56,50,227,148,179,129,139,158,184,107,173,98,93,121,128,199,190,90,133,68,8,89,54,246,
124,38,185,149,4,146,85,101,154,4,128,196,235,95,202,155,78,27,158,28,98,167,236,182,225,6,46,112,105,217,170,40,209,120,64,86,202,72,96,200,5,86,239,209,193,141,51,86,139,213,251,195,217,56,131,125,72,
217,192,31,0,204,251,238,195,159,49,253,19,133,117,157,98,114,144,27,170,124,203,3,192,127,27,22,144,101,3,41,32,139,34,221,189,102,165,181,36,221,253,243,111,15,42,139,125,128,80,56,140,2,175,23,203,
87,191,211,1,235,228,7,54,245,159,158,55,105,156,147,178,20,54,110,194,202,200,18,100,22,0,158,249,115,243,11,121,137,27,149,215,156,132,211,178,78,32,167,158,138,64,101,101,198,251,134,30,88,35,195,14,
240,234,255,188,124,77,182,197,129,32,119,217,167,127,215,38,116,195,4,138,12,224,83,24,208,207,198,157,177,155,23,43,161,93,193,194,118,40,243,199,178,22,46,100,102,250,122,5,192,127,209,20,156,86,87,
130,140,128,208,73,227,198,193,107,177,48,13,95,248,216,70,6,252,241,154,113,172,11,49,6,235,44,241,67,181,151,108,113,94,34,247,140,84,134,201,138,51,64,200,140,3,44,46,42,2,45,195,53,184,36,238,67,102,
214,180,204,177,179,86,160,198,138,153,162,49,200,84,23,142,74,69,241,174,101,182,238,108,132,233,43,118,211,231,0,144,88,182,65,8,158,85,79,210,66,58,36,139,76,254,165,191,190,204,123,233,173,75,194,
200,20,192,183,170,208,18,183,96,148,178,37,232,136,200,172,133,75,178,128,187,92,108,173,200,121,68,172,36,139,120,80,8,164,235,252,241,161,3,86,236,36,11,192,121,22,54,254,131,159,63,244,209,166,167,
23,15,161,27,228,21,239,188,131,217,130,128,234,154,26,252,246,199,151,12,185,249,191,31,251,4,233,37,52,93,28,171,205,86,33,97,107,81,211,176,11,54,92,199,212,98,189,124,58,78,247,56,205,53,0,37,197,
197,89,13,125,200,5,143,124,130,244,236,109,94,136,59,145,5,168,231,231,223,60,0,204,179,128,57,88,64,90,59,49,193,48,129,44,235,198,130,47,101,92,85,162,64,140,84,160,165,173,21,178,94,111,83,229,118,
160,66,22,230,78,227,254,102,37,251,194,199,30,41,22,236,13,15,254,220,14,25,69,139,166,97,110,153,15,150,181,158,170,43,43,49,251,164,147,0,57,211,44,79,248,238,11,219,15,180,4,41,187,23,100,22,242,22,
164,98,132,88,245,255,152,197,130,126,36,99,232,190,174,236,159,200,177,73,162,133,189,217,25,166,152,215,23,179,98,152,89,13,59,186,113,112,88,48,198,94,230,213,115,242,80,204,158,49,8,85,86,23,59,121,
252,120,12,27,53,42,227,253,73,87,254,109,179,170,105,172,224,57,95,45,130,143,255,203,198,82,28,202,102,193,170,52,24,201,2,120,120,22,44,6,32,182,177,201,185,127,88,105,164,172,44,16,48,1,96,129,83,
83,96,157,125,207,50,178,185,196,170,121,16,168,50,115,140,192,120,27,216,243,37,25,112,24,66,202,77,239,228,25,168,27,238,92,154,60,235,233,197,35,186,123,56,211,6,104,74,15,158,159,21,128,206,198,84,
243,46,111,9,221,39,64,9,200,29,11,152,45,99,93,204,2,4,217,107,229,199,2,237,107,193,130,17,100,99,231,50,66,2,118,118,216,58,250,249,19,254,177,99,70,99,203,246,237,38,11,248,141,241,98,229,205,192,
87,28,3,232,230,0,160,200,49,129,18,51,87,179,12,123,33,5,128,87,205,196,217,1,31,156,236,13,77,177,8,177,48,198,218,38,164,75,149,117,113,140,109,28,233,113,176,90,126,46,206,3,192,124,235,158,5,20,144,
233,10,230,133,149,131,236,2,90,232,82,29,112,21,67,20,69,4,187,130,248,253,109,139,43,111,188,243,145,6,164,43,253,179,160,45,201,252,79,122,94,118,160,178,110,16,94,156,215,129,244,0,254,52,113,94,155,
136,130,139,166,98,78,191,194,204,4,15,0,168,168,168,192,236,89,179,32,217,51,181,102,87,110,146,187,174,250,233,67,59,145,46,91,195,178,56,180,110,49,125,143,101,115,114,45,230,121,214,175,103,76,32,
207,18,179,130,204,46,0,142,179,199,224,191,21,151,63,254,236,191,58,238,98,88,151,108,89,180,2,183,121,224,133,157,41,83,76,25,9,239,184,126,56,225,204,49,24,104,117,161,118,69,193,233,115,230,192,103,
193,74,140,184,232,241,141,73,85,101,19,166,248,90,177,44,0,76,48,27,6,149,91,140,53,228,174,200,210,83,6,208,74,251,141,5,129,89,75,211,253,215,253,203,63,124,244,246,153,103,84,84,86,226,171,45,91,160,
17,194,51,85,18,50,117,215,196,30,204,53,252,53,81,16,152,52,192,3,15,78,40,24,233,66,202,5,204,130,64,26,175,25,7,144,188,235,197,221,123,127,116,78,85,69,119,15,232,201,223,93,94,186,240,166,135,195,
200,204,104,102,99,26,249,90,197,42,243,59,65,122,24,2,43,111,66,114,216,55,239,182,149,96,29,246,96,117,100,19,56,22,45,158,41,11,232,104,75,192,90,14,198,42,38,50,10,32,182,248,167,207,189,251,214,255,
158,61,207,229,215,67,166,247,236,223,143,234,218,90,253,6,4,193,78,8,113,112,12,32,173,127,172,49,224,158,222,55,221,188,185,145,153,172,87,248,253,147,176,160,192,157,46,0,62,97,252,120,20,7,2,25,253,
119,202,117,203,182,119,4,35,148,101,103,19,242,186,144,158,104,152,68,238,208,138,252,156,156,7,128,121,22,208,98,145,16,56,38,144,215,204,114,112,187,45,0,128,183,176,16,225,112,24,167,15,137,148,254,
177,212,191,111,79,83,71,146,97,92,88,215,128,192,0,63,150,57,99,1,160,104,1,32,173,170,51,184,0,56,125,14,148,92,48,17,39,151,249,173,25,63,1,186,219,206,42,195,23,0,78,187,225,31,219,183,239,106,14,
114,224,143,47,254,78,23,243,14,100,150,127,202,22,251,119,184,100,95,254,29,64,159,149,30,152,194,50,7,99,250,225,68,160,3,223,58,169,102,199,51,43,119,188,131,204,44,215,36,210,221,112,252,230,133,13,
23,48,93,191,163,171,48,225,156,177,24,147,237,130,103,205,152,129,218,129,153,184,112,111,135,144,56,241,170,165,155,25,22,130,221,40,180,115,108,113,136,97,219,172,0,107,174,77,218,193,48,128,217,92,
176,172,123,48,206,129,192,248,123,159,108,223,15,204,4,36,9,32,4,219,182,111,199,8,157,241,204,6,86,128,204,56,64,43,246,207,106,163,201,158,47,194,177,110,244,89,209,24,51,190,239,194,6,152,136,3,72,
222,251,196,155,13,223,158,123,105,169,207,73,114,174,53,19,250,171,142,51,79,174,247,191,242,214,134,8,199,8,59,141,107,112,100,25,211,44,8,86,153,249,44,215,120,207,166,105,41,114,94,14,62,155,90,226,
54,192,108,121,66,171,90,204,166,247,102,198,64,156,80,232,115,187,94,254,40,244,36,215,247,73,11,111,15,207,0,154,49,161,187,247,183,119,178,55,178,241,171,175,80,89,86,134,234,218,90,44,253,205,149,
195,22,255,248,129,143,153,254,96,89,55,86,128,28,12,147,207,38,124,152,224,239,182,211,241,45,81,76,183,151,1,3,234,48,210,130,101,63,237,134,127,108,223,185,191,173,3,153,9,121,236,24,99,117,101,213,
30,120,100,242,115,114,30,0,254,219,130,192,108,108,1,187,59,143,27,224,139,149,140,96,11,216,155,173,168,176,16,45,205,205,88,121,207,57,163,167,124,231,185,13,109,157,33,190,254,165,132,116,173,190,
24,50,179,233,248,210,83,124,224,190,89,169,97,96,9,6,46,156,130,41,185,110,116,226,184,113,24,145,5,248,189,249,149,45,120,237,207,30,220,133,244,114,117,124,197,18,190,246,39,59,209,100,139,55,201,179,
127,189,7,133,188,206,163,141,99,123,205,64,255,83,135,227,242,103,86,226,51,102,97,227,203,111,177,139,171,98,193,26,187,1,184,134,87,160,254,188,241,152,152,237,162,170,171,42,49,251,148,83,45,255,182,
98,147,173,243,154,159,154,113,162,93,140,157,180,112,108,49,27,46,192,139,133,231,138,21,61,156,99,157,5,95,86,110,96,86,215,206,28,211,101,101,1,52,55,53,35,25,137,192,227,118,200,93,161,40,44,88,192,
158,148,217,34,220,188,195,43,16,176,159,81,185,235,162,245,97,41,80,163,96,208,203,60,79,21,0,102,93,243,228,7,31,47,189,112,106,119,15,228,174,107,234,203,255,177,242,147,86,66,136,157,97,19,121,38,
31,12,219,199,134,162,240,66,239,185,68,222,179,185,120,37,88,215,47,231,127,102,147,110,120,137,23,51,185,199,173,64,57,171,30,183,12,46,19,198,140,29,59,78,93,248,155,79,102,50,204,101,18,233,33,19,
60,8,84,57,54,216,60,222,109,116,239,158,214,63,84,149,234,68,253,235,83,107,99,69,72,119,233,178,181,172,5,230,127,211,181,223,193,48,238,126,0,62,143,29,101,63,60,21,103,243,125,35,10,2,78,176,208,126,
156,119,253,63,118,108,223,221,220,137,76,217,158,118,134,1,100,67,44,172,116,88,243,45,15,0,243,45,199,34,33,32,179,68,28,43,13,147,17,32,221,22,145,67,133,78,189,70,176,205,229,66,203,214,173,40,239,
215,15,239,61,112,94,253,175,158,218,214,240,200,11,171,247,48,147,30,221,113,243,122,128,86,187,108,86,83,202,204,252,19,5,184,230,12,199,140,73,117,40,203,138,38,4,1,35,135,15,199,248,137,214,107,123,
36,14,109,214,119,255,182,181,35,24,9,35,179,86,49,159,233,75,119,154,86,181,63,123,179,152,231,129,96,118,38,144,175,96,193,46,132,172,203,214,120,146,154,4,93,231,17,200,204,108,101,207,201,107,142,
57,1,184,6,150,98,200,194,201,152,145,235,194,230,207,155,135,66,11,23,148,193,68,108,219,190,171,185,3,169,56,81,106,35,212,237,203,186,127,41,179,204,138,133,31,11,102,130,100,97,127,216,76,253,40,128,
216,151,77,238,93,195,75,67,213,85,21,149,216,127,160,9,26,33,56,127,238,164,146,135,95,88,213,204,174,213,22,44,87,79,174,129,101,4,193,48,105,176,152,115,98,140,167,128,206,1,97,102,243,24,103,55,142,
225,104,92,184,243,233,237,91,110,187,160,110,80,119,23,242,213,83,139,70,140,186,228,137,79,226,137,36,235,14,103,129,2,159,57,206,138,119,243,99,94,203,225,97,17,45,230,53,171,88,74,171,228,26,118,19,
44,240,0,112,74,29,78,155,51,2,11,232,70,183,255,200,25,91,199,47,188,231,251,200,172,217,204,219,128,192,49,193,60,248,139,2,136,95,122,211,189,235,55,61,189,184,202,166,40,72,196,227,120,107,213,106,
156,12,1,253,106,107,49,168,95,169,111,203,206,166,56,55,143,19,164,132,198,53,6,12,82,0,232,5,224,173,45,193,176,75,166,96,90,198,184,147,36,92,114,241,197,25,125,117,202,117,203,182,239,220,223,198,
170,49,180,50,224,143,221,100,229,82,100,0,242,238,223,60,0,204,183,172,44,32,63,64,120,182,192,202,85,144,216,214,230,60,48,193,25,172,163,39,45,46,44,196,187,107,214,96,218,140,25,248,201,133,3,106,
111,254,230,128,154,107,255,248,175,141,171,62,220,212,100,1,254,216,157,26,225,38,74,51,46,167,200,141,162,105,3,48,118,92,127,148,230,186,161,194,130,2,12,25,52,8,67,71,100,143,7,191,231,149,253,77,
255,251,200,235,251,145,94,6,42,136,204,242,79,108,236,22,171,225,22,225,22,130,36,172,197,157,143,228,98,254,117,99,254,0,235,100,16,133,99,140,1,0,177,88,12,208,93,72,108,176,121,146,179,35,137,99,143,
29,1,15,202,174,156,133,57,162,96,13,88,6,214,213,161,186,178,18,53,3,45,195,0,241,234,23,182,246,255,248,207,7,217,56,209,16,199,20,183,49,11,83,39,199,74,196,152,141,84,182,172,82,114,152,199,53,152,
133,152,112,54,202,203,193,152,165,225,110,250,221,115,107,95,254,237,188,111,249,138,138,96,183,201,208,146,73,204,156,58,186,240,225,23,86,245,164,172,153,208,13,11,8,11,16,8,6,60,16,166,63,105,246,
104,140,1,242,44,224,72,240,115,199,146,231,87,109,25,59,114,144,231,140,81,106,57,255,207,162,193,32,28,222,84,120,240,103,143,93,52,198,240,84,88,133,14,208,255,199,110,250,18,200,94,241,135,239,195,
108,73,29,124,13,101,158,237,179,89,128,65,19,204,141,239,143,19,102,15,197,105,14,69,79,152,56,249,196,19,209,175,166,6,239,238,244,60,55,126,225,61,207,112,140,37,251,191,249,231,206,199,131,38,57,207,
14,125,206,240,251,253,104,110,106,2,8,129,170,234,196,222,95,110,159,63,232,148,107,30,238,50,128,93,146,97,255,20,227,123,84,134,137,141,255,243,156,58,28,179,167,14,64,70,172,230,144,65,131,48,117,
250,244,12,3,25,179,232,201,173,209,120,34,200,120,102,218,152,77,22,235,157,9,115,115,51,159,5,157,159,151,243,0,48,223,122,201,2,178,147,68,134,92,0,128,216,226,155,238,91,253,249,227,23,155,0,176,188,
186,26,203,87,172,192,230,173,91,1,0,227,235,235,133,7,111,152,52,28,210,212,225,173,97,49,254,217,62,123,219,223,94,89,179,231,245,213,159,53,129,83,209,151,4,200,181,197,40,175,44,68,229,160,82,248,
171,10,145,83,224,213,110,183,163,180,164,4,101,129,0,170,42,43,81,144,67,54,96,253,78,41,124,225,141,15,55,48,236,29,91,165,161,19,153,154,109,65,164,215,45,142,90,44,62,86,139,64,94,120,244,224,88,64,
246,119,94,187,79,1,224,56,99,238,92,252,99,249,114,236,63,112,0,243,167,148,159,250,242,123,251,62,226,22,52,62,220,64,6,32,87,250,81,121,225,36,76,117,217,173,231,161,129,117,117,232,87,85,133,254,3,
6,88,94,228,199,187,228,208,183,110,120,136,183,157,32,199,24,183,113,204,49,95,41,198,170,106,196,209,98,139,179,185,129,85,11,6,48,186,105,199,129,22,250,69,143,199,139,237,141,141,40,14,4,156,22,27,
181,108,58,118,61,97,34,69,14,4,242,241,137,170,209,135,180,158,113,130,219,132,90,201,124,8,0,240,195,95,62,188,33,240,251,239,40,19,251,197,210,74,154,56,188,94,124,176,110,29,38,78,158,108,190,247,
222,3,231,213,223,183,188,101,231,31,31,124,101,43,172,195,15,168,110,29,207,250,243,213,91,120,55,55,31,219,106,37,110,46,35,189,66,6,251,179,9,252,198,246,195,148,147,135,226,20,183,29,14,58,56,78,159,
59,23,197,229,229,136,36,109,29,19,174,120,252,23,193,80,52,136,116,73,30,98,177,169,231,165,120,120,73,152,36,55,199,197,87,111,119,239,46,44,44,168,10,5,131,136,68,163,136,199,245,8,129,126,133,42,101,
212,85,142,53,117,50,108,160,41,255,34,9,240,223,114,58,206,17,44,44,228,244,185,115,81,90,158,142,215,85,2,50,252,194,71,54,33,83,141,161,149,57,218,144,238,254,229,171,49,229,217,191,60,0,204,183,67,
100,1,89,182,32,35,88,56,145,84,35,252,73,135,13,28,136,141,6,0,92,191,97,3,214,111,216,64,255,164,0,40,155,228,71,217,164,51,123,65,17,9,2,68,81,132,36,73,176,217,108,176,219,237,112,187,92,240,251,124,
232,87,85,133,146,138,236,201,127,239,55,202,161,75,110,126,184,145,16,66,139,152,71,178,128,191,32,183,112,243,210,2,81,110,167,108,85,251,51,91,221,211,124,235,61,43,200,199,71,217,74,202,203,65,65,
224,216,146,125,35,86,40,216,21,142,35,97,241,156,5,81,128,124,242,80,140,155,54,16,129,108,255,104,228,240,225,24,53,98,4,236,22,229,220,0,96,93,131,220,117,201,143,31,106,64,74,142,132,5,127,93,28,224,
235,96,22,42,62,84,128,103,172,178,85,252,56,210,246,194,199,249,242,130,208,102,201,198,184,42,36,21,137,200,213,85,85,56,208,212,4,167,146,86,118,203,10,244,160,151,76,166,198,128,64,21,214,218,142,
18,50,181,250,172,88,247,12,48,122,209,141,15,188,255,224,175,175,154,48,115,64,180,132,253,167,163,70,141,194,199,235,63,196,200,161,195,96,51,250,253,154,185,197,253,22,76,187,44,112,226,85,143,172,
83,53,141,186,92,105,204,168,27,185,5,161,85,88,235,3,138,22,140,54,207,0,74,22,44,159,36,137,176,207,28,132,249,39,12,78,23,175,63,109,238,92,148,49,64,233,207,255,216,247,204,255,44,93,254,17,82,110,
116,126,78,74,90,0,32,190,106,78,210,98,126,55,101,138,190,115,219,95,62,95,246,203,169,85,177,112,4,141,187,118,225,189,15,62,128,40,73,24,52,100,8,254,112,251,101,253,111,248,175,37,13,72,79,238,139,
49,255,95,2,160,76,232,143,73,167,143,70,70,45,183,234,234,106,76,30,55,14,30,78,83,243,203,125,82,244,156,255,120,120,187,5,248,163,101,250,90,145,169,175,217,19,113,245,60,251,151,7,128,249,214,195,
5,130,119,197,240,174,2,186,32,70,110,125,232,139,149,191,190,98,196,73,244,36,147,103,204,128,203,239,199,250,245,235,15,158,22,18,4,136,162,0,73,148,32,219,100,216,21,59,92,78,39,42,42,42,80,224,247,
35,80,82,2,217,233,204,122,142,23,63,38,237,55,253,250,209,61,220,194,198,42,254,179,98,206,212,93,199,86,107,8,35,61,56,158,221,245,103,115,251,230,227,254,142,28,32,148,90,163,246,150,146,242,242,226,
211,231,206,197,171,203,151,227,250,57,152,11,0,73,21,36,24,67,82,18,32,248,156,153,115,141,203,229,130,215,227,65,129,207,135,226,226,98,212,244,239,15,91,22,219,209,52,144,255,126,182,97,223,195,207,
189,211,132,204,12,120,126,227,192,102,36,90,213,251,229,25,163,158,108,24,142,196,152,230,1,0,95,6,44,193,129,192,200,167,7,10,182,76,168,104,27,86,88,90,10,13,4,9,89,147,144,221,173,166,229,184,151,
108,227,65,224,192,27,95,15,156,15,67,145,56,111,132,85,133,135,180,100,135,111,223,122,255,251,87,125,235,228,193,55,158,215,207,140,9,116,184,92,24,59,126,2,86,189,243,14,138,10,252,24,57,166,30,0,16,
240,106,246,47,159,188,100,230,150,102,91,240,172,31,60,252,161,170,105,84,123,48,130,204,36,25,43,15,0,223,167,44,227,199,186,127,249,250,190,146,34,193,49,177,22,167,76,169,195,64,202,242,209,54,251,
164,147,80,221,63,29,59,189,188,129,172,186,254,206,71,87,51,96,43,201,93,23,159,5,155,180,216,112,104,28,96,100,65,160,41,85,164,106,90,162,162,162,2,137,104,20,177,88,12,251,155,154,240,225,71,31,161,
179,179,19,245,37,197,133,0,246,51,247,170,176,44,183,223,9,239,15,102,99,166,149,81,78,26,91,143,225,198,179,103,219,179,31,36,219,111,251,221,35,187,152,177,198,75,43,81,240,199,150,227,228,55,90,201,
30,176,236,249,150,7,128,249,134,236,25,193,188,203,40,201,45,20,52,121,34,252,220,235,31,108,187,101,225,232,169,126,167,234,96,119,218,101,197,197,216,180,117,11,118,52,236,64,82,235,89,18,150,192,2,
63,89,134,221,110,71,101,121,57,220,110,55,6,212,213,65,113,185,114,126,255,174,23,247,236,191,247,137,127,210,197,155,186,109,195,220,2,206,106,71,5,153,247,35,220,110,146,101,253,216,184,18,171,202,
19,121,230,239,224,109,175,39,0,6,79,173,104,124,247,187,103,148,205,231,221,69,178,4,161,208,5,27,255,69,167,195,193,132,8,84,192,87,148,61,68,224,245,47,149,246,31,252,252,175,187,144,89,29,35,194,128,
186,144,133,237,116,49,108,113,136,25,27,49,110,65,61,154,108,49,63,166,41,155,198,199,247,90,85,130,136,2,136,44,190,241,158,215,63,127,252,226,97,0,80,92,26,64,75,216,212,118,227,25,150,158,108,126,
72,174,126,69,202,37,156,107,46,202,245,255,172,148,12,8,0,237,254,103,222,250,106,213,7,21,237,47,254,122,78,90,70,216,204,89,179,176,127,239,94,60,242,200,35,56,113,198,116,212,12,212,49,226,160,146,
132,247,203,39,47,57,41,146,16,212,39,86,181,109,255,239,191,188,180,5,233,9,32,188,136,183,21,184,34,200,148,204,17,0,136,110,5,174,225,21,152,50,178,18,149,253,138,144,97,144,149,21,21,152,62,101,10,
92,62,95,198,3,187,251,229,189,111,222,253,232,27,159,51,12,100,140,177,209,8,7,132,226,28,67,201,151,136,19,184,121,140,103,88,77,176,237,118,187,81,89,81,129,100,34,129,253,77,77,136,197,98,248,236,
139,47,244,235,245,163,104,79,7,218,25,246,47,41,139,16,47,155,142,209,229,126,100,148,99,169,40,46,198,156,51,173,221,63,139,127,189,166,241,95,31,111,109,69,122,92,118,27,210,51,126,91,145,30,166,195,
131,191,108,218,127,121,246,239,24,239,226,243,173,239,247,15,31,180,76,119,172,108,21,5,154,202,95,12,160,212,56,2,0,2,155,158,94,188,208,234,228,109,251,247,227,203,205,155,1,162,11,9,16,66,176,173,
161,33,227,115,85,85,149,112,40,118,40,54,27,170,42,43,33,73,18,236,118,59,10,74,74,114,94,124,67,139,24,187,230,206,151,119,110,219,213,220,101,177,120,243,18,47,33,14,248,177,140,31,91,240,61,206,77,
136,73,100,150,91,210,144,119,251,30,14,91,99,43,127,216,24,59,243,66,207,246,101,109,236,199,0,176,102,213,42,108,221,190,61,235,63,113,58,28,24,88,87,135,65,3,7,100,5,126,159,237,150,194,231,223,184,
180,65,213,52,150,245,136,51,139,74,132,177,141,46,142,1,236,226,128,97,148,99,138,216,5,213,106,195,112,164,217,226,108,207,153,213,88,164,50,40,110,232,245,88,139,160,87,102,40,1,80,184,233,233,197,
183,211,147,237,13,58,154,79,188,242,254,167,13,230,165,5,64,179,241,218,130,84,178,148,21,248,232,73,92,172,85,44,33,95,242,140,101,206,216,236,110,170,15,72,235,202,250,153,251,40,66,74,115,206,243,
248,239,175,28,55,169,95,60,205,223,184,127,239,94,108,221,186,5,91,182,165,108,105,200,144,193,24,58,120,8,10,153,152,226,150,144,20,221,210,98,111,91,253,225,166,3,175,174,252,120,111,227,190,214,46,
14,0,18,0,154,67,134,82,89,128,128,223,137,178,170,66,20,85,23,160,160,196,11,203,24,3,159,215,131,234,202,42,212,244,239,135,210,138,74,203,7,179,55,104,111,93,244,211,231,94,111,220,219,218,201,216,
103,132,243,102,4,185,13,46,159,16,193,206,95,236,243,101,99,29,217,103,87,6,160,220,56,42,54,61,189,248,92,0,104,59,112,0,159,126,241,5,26,26,27,211,174,241,87,175,96,39,128,132,44,66,91,48,30,213,67,
202,210,129,95,129,203,137,97,67,134,98,200,24,107,169,205,207,246,72,145,5,63,122,120,27,210,195,115,40,195,78,99,107,121,89,37,30,252,241,226,207,42,242,138,12,121,6,48,223,122,205,28,128,97,12,168,
139,134,150,247,161,11,37,141,133,114,48,135,125,232,133,143,62,251,254,146,75,207,246,57,210,75,46,21,150,149,97,122,89,186,106,75,45,235,214,48,34,131,171,251,245,3,68,177,219,139,220,217,38,198,223,
220,208,222,241,235,251,94,220,71,8,177,170,227,201,215,136,12,114,139,56,95,244,157,117,215,69,185,73,83,133,117,188,95,30,252,29,62,123,3,99,119,86,149,43,76,151,219,223,214,197,214,157,63,217,62,121,
198,204,153,208,0,108,183,0,129,101,129,0,198,142,30,141,178,42,203,106,110,216,184,95,138,156,125,221,195,219,145,94,5,35,202,1,63,118,145,229,65,32,187,97,136,32,123,130,80,46,187,57,154,54,147,45,33,
128,151,120,162,66,239,33,0,74,83,216,185,191,212,21,41,3,128,168,42,71,144,89,110,43,23,184,237,174,175,187,251,155,138,204,186,194,146,5,123,106,245,59,56,219,73,2,72,92,124,227,95,223,175,169,44,42,
124,227,174,249,102,141,177,178,138,10,148,85,84,0,16,208,218,222,142,214,214,86,108,218,180,25,155,54,109,230,175,199,1,160,162,20,168,88,60,1,245,221,33,111,65,16,32,176,158,12,69,129,203,229,130,207,
235,69,81,81,17,202,203,2,112,27,85,54,248,214,21,151,162,127,94,182,237,195,191,62,243,246,54,110,94,139,49,125,192,2,64,246,96,245,38,173,92,230,108,172,55,31,14,64,65,34,207,90,235,243,120,32,128,186,
112,56,3,0,142,40,71,241,188,81,112,186,236,250,185,123,195,188,95,243,199,117,141,43,222,219,216,10,107,17,254,238,116,88,35,200,172,172,147,7,127,121,6,48,223,142,0,99,64,235,176,186,141,29,55,45,231,
83,204,176,129,197,0,10,175,91,60,119,196,247,206,40,31,46,8,135,167,223,183,53,75,145,23,215,52,182,223,251,196,155,77,200,46,77,67,39,201,8,210,147,61,88,247,111,132,121,101,229,57,248,224,238,36,50,
75,9,101,99,111,242,147,203,193,207,5,185,152,41,26,128,95,96,176,18,1,122,124,176,244,242,43,125,14,213,9,0,107,87,175,6,33,233,143,221,237,118,99,236,248,241,150,255,124,206,143,94,217,186,99,79,75,
23,99,43,108,124,104,148,179,143,136,5,224,11,115,96,49,110,177,105,200,86,134,234,104,46,72,86,210,44,124,118,53,101,128,248,42,13,126,0,133,139,191,49,125,236,79,22,14,186,2,0,62,110,10,124,244,173,
239,255,254,37,99,1,230,43,157,80,25,14,86,70,36,151,52,18,233,102,109,200,198,8,242,137,65,188,119,194,172,238,98,48,154,133,204,60,229,55,14,47,0,215,21,231,205,170,185,229,91,181,105,122,63,145,96,
16,31,125,250,41,90,91,90,208,218,214,214,251,135,109,38,171,137,6,232,211,227,150,125,62,31,138,13,208,231,242,249,45,191,223,216,110,111,253,245,146,213,27,222,124,247,203,253,72,143,229,139,113,182,
106,101,151,188,109,178,153,221,236,6,150,31,119,50,210,117,250,124,12,227,94,6,160,202,96,0,47,96,175,245,173,21,43,176,115,215,46,88,179,154,94,84,87,85,161,166,95,63,148,230,72,206,123,234,95,177,150,
159,221,245,244,110,164,135,89,4,145,46,195,197,2,63,94,80,61,130,76,119,124,30,252,229,1,96,190,29,230,133,153,149,70,160,217,113,180,134,170,143,89,160,139,12,0,72,39,91,250,25,123,160,200,235,92,48,
111,114,201,240,65,53,110,167,93,148,236,50,17,21,9,162,70,64,8,1,73,104,2,137,37,5,173,181,189,43,185,181,97,79,244,217,215,215,181,119,4,35,172,48,171,138,220,113,75,60,243,23,229,38,198,16,199,10,242,
65,221,108,86,31,31,71,194,179,55,64,62,174,228,112,110,54,120,23,31,213,13,163,11,58,93,192,75,12,0,88,10,221,21,124,121,111,254,225,203,159,73,109,215,255,242,225,157,220,38,161,187,197,52,194,29,209,
44,182,195,235,169,17,14,0,101,179,27,114,20,159,51,255,172,173,170,164,176,110,212,2,0,158,77,79,47,254,19,0,156,125,203,242,223,110,220,190,175,25,169,216,43,150,153,97,235,98,103,115,123,119,151,240,
34,244,242,250,121,201,22,27,82,21,67,188,12,160,245,25,7,11,0,189,6,224,113,221,114,245,217,117,87,204,46,168,225,129,96,115,75,11,26,119,238,204,25,102,0,131,233,147,25,117,130,210,210,82,120,220,110,
20,250,253,168,172,168,128,160,40,214,94,140,14,91,199,163,255,248,106,243,146,191,175,110,228,230,30,171,13,173,149,87,131,183,75,54,124,37,91,146,10,125,254,130,197,134,139,2,103,26,2,80,193,0,192,139,
210,192,234,182,109,88,185,122,117,198,61,21,21,22,98,200,160,65,24,50,120,48,32,91,59,253,86,108,178,117,92,243,211,7,119,114,76,59,15,254,88,29,86,86,79,51,108,193,182,231,2,127,64,190,34,83,30,0,30,
15,141,16,82,4,224,116,0,103,1,24,5,88,199,141,28,201,166,25,137,26,132,232,200,76,85,85,129,16,130,100,50,25,138,70,163,27,119,237,218,181,252,193,7,31,92,125,207,61,247,208,114,76,30,110,114,165,241,
54,116,210,117,49,11,186,236,118,187,61,165,165,165,99,79,71,17,0,0,32,0,73,68,65,84,129,130,130,130,98,69,81,156,236,36,42,24,110,96,42,249,34,138,34,4,65,32,146,36,65,20,69,200,178,76,100,89,134,44,
203,68,81,20,200,178,172,41,138,2,187,221,78,20,69,129,195,225,32,118,187,93,115,58,157,196,229,114,17,135,195,65,28,14,7,113,58,157,112,187,221,170,221,110,7,125,207,248,14,177,217,108,176,217,108,68,
146,36,40,138,18,34,132,124,17,137,68,94,126,235,173,183,254,121,197,21,87,52,247,144,245,51,127,55,10,164,159,4,224,27,0,38,27,147,105,95,105,42,128,61,0,222,1,240,146,32,8,235,14,210,78,7,26,54,58,15,
192,64,28,68,120,135,149,157,169,170,10,85,85,145,76,38,17,143,199,197,112,56,140,112,56,44,118,118,118,10,173,173,173,98,91,91,155,212,212,212,36,54,53,53,137,205,205,205,82,107,107,171,116,253,252,82,
87,169,43,156,115,110,57,16,20,18,39,93,253,216,166,164,170,90,49,40,52,222,40,141,29,30,55,110,156,119,206,156,57,163,70,140,24,49,186,168,168,168,194,233,116,138,138,162,16,167,211,73,236,118,187,102,
216,13,20,69,161,182,67,36,73,130,36,73,196,176,85,211,166,37,73,34,172,109,211,38,246,32,212,33,75,11,1,248,12,192,75,0,94,23,4,161,165,135,0,16,20,64,253,236,103,63,115,95,118,217,101,39,58,28,142,115,
0,76,136,197,98,133,209,104,84,232,234,234,18,59,59,59,133,142,142,14,49,24,12,138,93,93,93,194,201,165,159,21,203,36,36,60,191,125,68,171,162,40,196,237,118,19,175,215,171,249,124,62,205,239,247,19,159,
207,167,186,92,46,24,207,134,40,138,66,100,89,134,36,73,230,248,101,239,189,7,247,173,106,154,182,7,192,59,170,170,46,83,20,101,29,210,101,94,68,238,160,241,128,50,195,4,218,191,241,141,111,12,153,62,
125,250,108,191,223,63,77,85,213,138,96,48,40,119,118,118,138,193,96,144,222,155,24,10,133,132,72,36,34,68,163,81,225,132,49,85,210,119,102,187,50,18,137,118,53,52,128,0,104,220,185,211,124,146,253,43,
42,177,117,199,14,64,16,160,40,10,60,110,55,74,138,138,80,217,191,127,22,123,7,54,119,20,169,47,174,105,72,54,236,237,82,1,168,209,104,180,189,169,169,105,87,99,99,99,99,36,18,9,33,229,138,103,61,18,81,
6,240,164,129,189,64,32,160,93,119,221,117,35,38,79,158,60,51,16,8,140,116,56,28,62,135,195,65,108,54,27,157,43,137,40,138,80,20,37,109,126,165,227,46,153,76,66,85,85,36,18,9,33,28,14,11,145,72,68,232,
236,236,20,91,90,90,196,166,166,38,105,239,222,189,226,254,253,251,101,143,216,165,44,154,28,203,72,153,127,255,95,255,194,151,155,54,153,191,143,28,58,20,35,134,15,135,211,34,121,37,169,130,220,241,232,
198,253,127,123,117,93,43,199,184,83,207,12,5,121,105,90,172,39,159,124,178,123,193,130,5,227,135,13,27,54,177,184,184,184,202,233,116,138,118,187,29,54,155,141,216,237,118,34,203,50,29,119,212,222,142,
196,120,59,28,227,48,15,0,243,143,32,231,162,90,3,224,54,0,23,26,192,233,88,93,71,218,171,166,105,105,71,34,145,232,106,109,109,253,251,146,37,75,254,247,23,191,248,69,11,82,1,228,44,115,224,101,118,147,
46,58,33,215,213,213,245,31,60,120,240,72,175,215,91,6,64,164,139,63,59,80,89,240,71,15,73,210,99,104,168,6,32,123,56,28,14,24,32,208,60,28,14,7,236,118,59,156,78,167,249,30,221,157,211,207,26,64,18,198,
100,105,78,32,162,40,130,16,210,9,224,217,173,91,183,254,106,236,216,177,187,144,25,192,158,13,252,21,1,248,17,128,197,0,250,247,101,115,3,240,9,128,223,10,130,240,68,47,237,227,84,0,55,25,32,87,57,220,
118,70,65,96,60,30,71,44,22,67,36,18,65,40,20,66,87,87,23,218,141,248,172,230,230,102,180,180,180,160,181,181,21,109,109,109,40,112,170,248,246,73,30,120,149,68,218,255,232,138,137,228,202,223,188,181,
117,253,23,59,90,57,6,133,5,125,124,76,95,248,146,75,46,25,60,111,222,188,179,203,202,202,70,187,92,46,155,1,244,76,59,202,102,59,220,198,197,252,221,106,49,18,132,195,50,29,118,2,120,6,192,127,10,130,
176,171,135,172,190,176,118,237,218,146,145,35,71,254,135,36,73,139,8,33,213,137,68,2,241,120,28,209,104,20,209,104,20,225,112,24,93,93,93,232,234,234,66,40,20,66,145,173,3,253,98,239,96,109,100,54,108,
54,27,92,46,23,92,46,23,60,30,15,60,30,15,220,110,55,156,78,39,20,69,129,162,40,176,217,108,105,207,129,125,6,189,185,119,77,211,8,128,79,8,33,191,147,101,249,137,30,128,64,42,160,172,220,119,223,125,
39,143,28,57,242,42,73,146,38,69,34,17,27,181,161,96,48,104,30,244,254,232,107,36,18,65,52,26,133,67,6,110,185,112,8,42,189,209,220,54,28,143,103,101,247,118,7,93,248,124,159,132,23,222,250,18,146,36,
155,54,67,237,134,30,162,40,198,155,154,154,182,172,93,187,118,117,115,115,115,171,5,248,99,213,8,76,54,112,226,196,137,202,109,183,221,246,173,186,186,186,249,30,143,167,130,61,39,107,147,212,46,89,0,
72,231,93,58,222,146,201,36,98,177,24,194,225,48,130,193,32,58,58,58,208,218,218,138,125,251,246,97,207,158,61,216,179,103,15,110,158,19,207,184,199,112,103,7,158,253,251,139,0,128,193,3,6,96,218,148,
41,128,45,29,63,175,217,110,199,207,255,252,106,188,189,35,216,210,209,209,209,132,76,41,174,46,134,65,102,51,123,131,223,251,222,247,134,204,159,63,255,155,129,64,96,156,203,229,178,209,249,155,191,207,
108,182,118,4,198,219,161,140,195,127,251,150,79,2,201,205,252,221,14,224,50,99,18,59,246,104,93,16,64,8,73,91,200,8,33,144,101,217,227,247,251,47,92,180,104,81,120,195,134,13,119,189,248,226,139,49,58,
95,51,46,12,118,144,59,1,56,234,234,234,170,78,58,233,164,65,5,5,5,21,116,145,231,227,182,104,163,131,154,125,165,224,79,150,101,115,18,48,88,192,52,144,71,23,106,118,193,166,64,209,102,179,165,157,135,
5,150,220,4,226,3,176,120,216,176,97,161,79,62,249,228,142,49,99,198,116,228,2,126,70,31,10,0,46,5,112,221,177,4,240,189,216,140,213,3,184,141,16,210,44,8,194,242,30,218,233,8,0,55,3,152,115,184,237,140,
101,129,233,132,110,179,217,76,64,152,72,36,224,114,185,144,72,36,76,230,130,238,234,59,59,59,241,95,47,180,33,106,232,148,177,182,21,133,91,177,217,108,237,137,68,34,196,177,126,108,182,164,25,60,127,
198,25,103,148,45,88,176,224,172,178,178,178,241,212,102,172,22,87,106,75,236,226,195,46,182,148,109,56,194,139,145,207,152,51,66,132,144,159,9,130,208,153,5,236,155,255,240,252,243,207,71,125,125,253,
34,73,146,190,71,8,241,81,32,64,199,21,5,5,116,236,75,146,132,112,220,129,6,231,92,248,108,46,19,228,81,16,200,130,98,118,28,241,172,254,193,220,187,40,138,2,128,122,77,211,110,77,36,18,205,54,155,141,
181,83,126,83,102,186,221,31,122,232,161,193,211,167,79,191,66,150,229,233,177,88,204,156,23,12,47,1,28,14,7,92,46,23,220,110,55,186,186,186,224,118,187,17,10,133,76,16,24,137,68,240,203,39,183,34,30,
143,227,212,73,181,56,119,130,8,135,156,57,87,81,240,183,179,211,129,79,119,139,120,102,249,6,72,82,250,70,213,237,246,100,216,16,59,127,41,138,162,84,85,85,13,43,42,42,106,127,254,249,231,95,233,236,
236,236,228,0,96,156,255,93,150,229,196,237,183,223,126,225,208,161,67,23,58,28,14,15,157,7,109,54,155,238,142,182,152,211,172,158,189,40,138,208,52,45,205,102,89,59,167,115,168,195,225,192,207,158,107,
195,47,206,75,119,72,185,124,126,140,24,56,16,19,103,164,151,212,94,183,93,194,247,127,243,2,243,125,167,82,81,225,41,148,36,169,173,181,181,149,214,84,167,7,253,61,200,28,225,243,207,63,191,244,236,179,
207,254,102,69,69,197,100,58,191,179,224,143,93,27,142,210,102,235,80,199,97,30,0,230,31,65,214,118,58,128,11,88,240,23,141,70,209,220,220,124,76,89,64,118,183,88,82,82,2,217,136,233,80,20,69,246,251,
253,11,110,190,249,230,53,47,190,248,226,155,72,143,151,75,48,59,213,16,0,135,36,73,142,121,243,230,77,31,50,100,72,109,34,145,48,217,30,202,54,240,147,18,227,58,203,0,129,252,2,76,39,0,122,206,100,50,
105,14,120,85,85,205,93,119,44,22,203,56,23,59,73,74,146,132,64,32,96,186,238,68,81,148,9,33,23,14,25,50,228,45,0,47,162,251,120,191,9,0,190,205,130,63,66,8,246,237,219,103,130,149,99,221,92,46,23,138,
138,210,42,99,141,0,112,37,33,100,157,32,8,237,221,216,132,4,224,98,30,252,133,66,33,180,245,50,88,222,138,5,164,64,196,112,7,155,160,143,178,83,116,97,142,70,163,72,36,18,230,70,129,46,234,20,196,120,
189,94,243,92,162,40,10,129,64,32,160,105,218,150,141,27,55,238,67,102,86,47,5,129,81,0,97,151,203,149,88,180,104,209,55,106,107,107,39,208,197,70,150,101,72,90,28,82,188,29,178,38,66,78,202,186,13,197,
37,136,162,1,112,4,1,162,36,1,130,160,163,45,81,4,161,139,14,101,93,88,192,123,72,136,89,132,224,41,129,32,41,236,188,122,17,128,149,0,254,222,221,35,95,178,100,201,68,89,150,47,23,4,193,71,221,240,162,
32,64,8,29,128,20,143,67,142,199,161,196,226,208,18,49,16,53,14,65,136,195,46,198,161,106,10,124,114,2,54,81,131,44,168,112,106,4,74,34,1,25,97,136,154,2,33,161,64,176,201,32,146,4,34,203,16,68,17,26,
221,56,102,1,194,89,111,81,113,65,112,21,177,115,194,8,0,223,110,111,111,95,87,80,80,208,142,244,186,198,180,22,52,0,160,190,190,94,156,61,123,246,55,156,78,231,172,68,34,145,26,239,36,1,49,26,131,44,
199,97,115,16,216,85,1,14,34,193,41,40,112,138,9,184,36,21,110,27,65,72,1,34,54,1,17,69,68,44,38,227,221,79,118,225,237,15,18,72,38,19,184,104,254,68,244,47,34,120,239,203,54,188,182,246,43,136,130,168,
235,149,74,34,100,73,134,199,169,192,38,203,176,201,50,100,155,12,197,102,131,205,166,192,102,147,97,179,201,176,219,12,0,99,87,96,119,251,97,119,152,128,90,12,4,2,163,163,209,232,7,79,61,245,212,86,164,
39,112,240,49,202,241,223,252,230,55,195,134,13,27,118,174,219,237,246,80,224,103,246,161,128,148,45,10,130,165,45,2,0,49,230,75,162,170,128,170,1,177,24,196,120,2,66,40,4,49,218,5,91,188,19,138,26,130,
157,196,96,23,18,16,161,225,143,203,218,113,253,89,233,89,203,253,107,107,209,188,111,31,74,24,93,78,183,93,131,104,204,169,116,243,237,241,120,236,110,183,187,40,20,10,109,142,197,98,108,226,16,47,162,
222,229,114,185,98,11,23,46,92,80,93,93,61,153,221,220,203,36,14,49,212,6,65,146,0,81,128,32,73,250,189,49,247,73,184,49,118,200,227,237,200,140,195,60,0,204,183,180,54,159,2,7,66,8,182,111,223,129,255,
251,191,255,195,91,111,189,105,214,93,60,150,32,208,227,241,224,228,147,79,198,149,87,94,137,170,170,42,72,146,4,135,195,81,82,83,83,115,218,89,103,157,245,214,178,101,203,162,12,3,200,38,99,216,1,216,
102,206,156,57,96,226,196,137,67,157,78,167,185,184,111,217,178,29,111,191,189,18,219,183,111,131,170,170,89,23,134,108,59,58,62,102,144,127,143,255,46,255,121,190,121,189,94,156,122,234,169,184,234,170,
171,208,175,95,63,250,249,82,81,20,207,222,189,123,247,235,85,85,85,145,44,192,15,132,16,17,192,41,0,134,209,247,58,58,58,241,196,227,79,226,153,191,61,133,166,166,166,99,110,96,162,40,98,208,160,65,88,
180,104,17,206,61,247,92,150,9,156,1,96,60,128,21,221,156,98,16,128,52,245,214,117,235,62,196,95,255,122,63,214,173,123,15,201,100,242,144,108,140,7,132,140,27,208,4,136,20,216,177,135,170,170,230,103,
100,89,70,77,77,13,70,140,24,1,143,199,67,227,70,29,138,162,148,52,52,52,172,137,70,163,65,164,39,124,80,166,58,6,32,114,241,197,23,87,14,30,60,120,170,215,235,53,23,47,109,215,122,8,27,158,6,246,111,
0,17,146,80,5,1,68,48,180,52,4,64,20,116,123,74,2,208,9,43,38,232,78,56,56,230,43,55,56,242,66,26,124,42,228,169,87,65,44,236,71,223,46,5,112,14,33,228,117,65,16,34,217,88,192,103,158,121,70,180,217,108,
179,69,81,28,74,8,129,40,138,72,118,181,32,185,238,49,168,159,255,29,137,96,51,52,141,0,42,129,168,18,200,42,160,168,26,68,13,80,13,176,40,137,34,100,65,128,40,11,128,12,16,81,128,38,139,72,24,233,24,
154,32,32,41,8,144,140,112,43,81,16,122,247,28,4,17,98,209,32,200,19,23,65,30,157,178,83,81,20,103,184,221,110,106,167,36,27,8,188,255,254,251,107,253,126,255,28,250,191,68,81,132,186,115,61,108,235,159,
132,186,251,83,144,100,2,66,156,64,72,16,200,73,21,114,2,80,226,26,28,9,21,142,56,129,51,65,16,142,19,68,18,26,98,9,13,177,36,65,76,37,72,104,4,203,30,251,2,26,33,208,136,30,228,44,8,128,100,220,171,36,
10,80,36,1,178,4,200,198,207,54,73,127,213,223,23,160,200,128,34,138,176,217,29,112,148,15,135,115,248,41,176,23,148,82,102,203,123,210,73,39,141,88,177,98,197,63,15,28,56,16,68,122,18,135,89,237,195,
231,243,169,179,102,205,154,224,245,122,7,40,138,2,73,146,128,104,7,200,134,103,65,54,190,4,45,210,140,36,189,119,33,101,131,34,11,254,0,16,2,104,132,64,213,8,84,13,72,168,4,137,36,65,50,161,129,196,53,
32,162,66,8,169,80,66,42,236,157,73,56,130,73,236,234,74,98,213,224,115,49,115,88,170,187,2,85,85,88,255,193,7,105,0,112,100,37,129,152,8,65,182,75,80,20,63,5,128,130,195,225,240,119,116,116,216,182,108,
217,194,214,204,230,133,212,195,139,23,47,46,175,171,171,155,225,114,185,76,47,15,118,173,135,246,241,19,208,246,125,4,13,73,136,2,144,20,4,211,190,142,228,152,235,237,56,204,3,192,60,0,236,109,51,235,
61,198,227,113,252,229,47,247,225,174,187,254,144,213,69,122,44,218,186,117,235,224,114,185,112,211,77,55,153,110,6,143,199,51,254,252,243,207,247,47,91,182,108,31,50,203,9,69,97,4,102,79,158,60,121,72,
255,254,253,11,41,43,215,214,214,134,55,222,120,13,239,189,247,94,159,234,132,15,62,248,0,62,159,15,55,220,112,131,201,118,18,66,166,20,22,22,150,2,216,145,139,92,3,48,82,95,2,245,246,202,43,175,224,167,
63,251,41,90,90,154,250,204,253,125,250,233,167,104,104,104,192,240,225,195,49,108,152,57,139,151,3,152,216,3,0,88,13,61,35,16,0,208,212,212,132,59,239,252,21,94,124,177,111,205,117,123,247,238,69,65,
65,1,102,205,154,101,186,180,138,139,139,203,214,173,91,23,222,188,121,243,1,100,86,76,48,43,60,76,153,50,197,87,88,88,88,70,23,29,49,210,134,196,123,255,7,97,211,114,136,146,145,61,33,164,94,5,6,4,166,
33,63,110,167,32,8,135,177,188,7,1,180,157,235,0,135,23,182,19,111,128,32,154,38,55,197,88,128,26,179,125,247,228,147,79,118,73,146,52,130,181,83,108,90,14,237,173,95,65,8,119,64,98,83,157,84,35,69,52,
9,168,36,189,220,134,36,0,178,164,191,218,140,87,73,4,4,35,63,151,222,175,32,0,36,109,65,238,217,115,80,247,124,10,210,214,0,177,108,56,196,64,202,78,101,89,158,192,216,169,37,8,172,174,174,46,151,101,
185,210,4,128,145,54,196,63,252,11,180,47,223,128,72,0,57,9,216,84,253,80,84,192,174,2,206,164,126,184,146,64,84,51,2,69,5,32,42,2,49,137,83,82,230,138,25,137,2,32,139,198,33,0,54,129,209,214,33,128,205,
56,20,13,80,146,250,115,179,69,1,121,231,14,56,43,2,112,214,13,131,98,119,208,249,116,240,164,73,147,240,202,43,175,116,32,83,195,47,9,32,121,202,41,167,216,75,74,74,6,57,157,78,137,122,48,180,47,222,
66,98,229,127,65,136,118,164,54,37,41,60,157,101,215,170,31,130,241,244,4,13,16,146,128,164,2,114,2,176,197,0,71,12,112,68,0,87,28,112,39,0,183,6,60,254,208,35,24,249,179,197,40,242,48,19,67,85,21,154,
246,238,77,147,124,209,89,243,14,40,98,49,28,14,7,156,78,39,10,11,11,29,181,181,181,222,45,91,182,176,218,126,52,251,215,204,34,159,52,105,146,191,176,176,48,96,198,106,199,218,145,88,251,39,96,211,107,
204,166,203,122,220,29,137,49,119,16,227,48,223,242,0,176,87,205,116,27,182,182,182,98,213,170,119,250,20,248,163,109,199,142,29,136,199,227,112,58,157,208,52,13,146,36,57,202,203,203,41,235,103,227,88,
64,155,177,176,202,53,53,53,164,168,168,72,0,128,100,50,137,72,36,130,93,187,250,94,172,44,33,4,187,118,237,50,93,199,6,115,230,112,230,168,55,76,231,59,3,4,154,109,219,182,173,125,10,252,209,182,111,
223,62,132,66,161,180,53,12,122,156,102,119,205,197,2,135,80,40,132,207,62,251,180,79,14,166,68,34,129,64,32,0,202,144,36,147,73,161,160,160,160,5,122,205,82,86,87,141,149,203,136,151,151,151,75,78,167,
83,48,51,88,35,9,160,117,19,32,229,6,126,166,135,205,146,193,62,220,212,3,0,162,129,180,239,4,180,36,144,90,120,28,200,157,104,71,100,89,150,0,184,210,146,1,90,182,67,136,117,64,20,1,153,145,79,22,37,
32,65,0,81,78,49,70,166,177,139,6,248,19,116,205,118,10,0,233,194,76,159,15,203,204,244,246,30,73,215,62,144,184,165,157,178,49,141,25,32,208,110,183,59,37,73,231,31,5,65,0,72,28,114,235,102,64,6,36,205,
16,15,148,82,0,48,174,2,14,9,112,201,64,212,6,196,84,32,154,0,98,26,16,77,234,191,199,147,58,240,75,104,128,65,144,154,125,43,26,207,195,70,159,137,104,156,95,50,192,160,164,131,67,27,61,36,227,243,2,
96,71,23,92,5,62,200,138,19,178,44,131,16,34,151,151,151,211,176,4,149,3,128,26,0,173,174,174,78,118,187,221,14,26,2,35,8,2,18,109,59,32,198,58,210,158,185,32,88,219,37,177,48,39,129,233,63,201,184,70,
69,6,156,170,254,92,60,50,16,182,3,145,36,16,177,1,55,252,236,17,60,252,199,197,41,22,176,162,2,111,188,249,38,198,10,2,104,137,198,177,35,106,177,117,219,78,200,146,104,134,105,184,92,46,193,231,243,
17,164,98,253,248,36,172,24,128,72,121,121,185,77,81,20,145,142,95,33,28,131,208,180,17,162,152,62,246,172,238,79,56,90,169,166,185,199,97,190,229,1,224,193,53,85,85,161,199,1,247,205,198,6,189,3,16,156,
78,39,173,33,73,107,121,210,221,120,210,0,12,98,121,121,121,216,227,241,152,1,255,193,96,176,207,196,197,229,28,227,198,61,30,204,119,15,198,37,122,52,129,238,225,104,125,245,30,93,46,87,26,0,76,36,18,
90,81,81,81,27,116,209,98,234,82,99,69,196,147,0,212,226,226,226,184,221,110,55,227,67,137,36,67,213,84,179,48,205,49,5,126,61,91,146,122,61,150,161,38,33,18,64,51,192,140,44,166,252,169,130,170,143,96,
149,1,128,20,244,136,20,252,65,127,53,89,153,44,224,239,224,158,7,201,245,7,193,226,67,154,211,233,212,216,100,0,73,148,96,35,73,136,6,240,18,1,72,36,5,206,20,21,176,107,64,92,3,28,73,29,248,37,108,64,
44,169,191,151,208,128,132,170,191,38,13,0,168,145,212,3,23,13,123,144,12,38,80,50,14,69,76,1,61,89,76,49,165,38,99,42,0,118,183,13,14,143,7,54,135,27,146,36,65,211,52,18,8,4,104,88,2,171,65,106,234,41,
22,22,22,218,13,249,19,115,142,18,137,154,254,220,133,236,70,97,22,89,54,250,74,37,169,212,106,89,210,127,151,69,64,145,0,135,12,56,109,128,91,1,188,170,14,136,195,73,253,245,55,15,188,139,91,190,51,205,
60,239,216,250,122,136,76,173,247,235,22,205,194,143,126,249,56,36,73,76,75,206,115,56,28,124,146,32,95,66,49,225,245,122,19,108,54,57,68,17,18,161,73,95,169,113,120,204,192,223,97,30,135,121,0,152,111,
199,77,163,113,53,52,123,172,160,160,128,45,208,78,1,32,43,50,42,20,21,21,197,61,30,143,70,193,135,195,225,56,18,154,76,135,245,30,5,33,63,142,143,215,102,183,219,81,84,84,4,69,81,168,173,106,129,64,128,
6,155,83,224,199,150,189,82,1,36,253,126,191,202,102,80,66,150,160,138,134,97,139,153,113,70,125,4,248,245,184,21,20,20,16,154,248,193,102,249,83,122,141,130,64,65,212,93,131,146,148,170,7,73,136,126,
72,98,38,248,17,56,240,119,148,86,65,98,69,110,73,146,68,36,73,2,33,68,143,143,147,68,72,162,0,65,4,68,131,209,84,9,144,84,83,64,48,9,221,61,155,20,117,214,51,161,2,113,57,5,250,18,42,144,36,41,246,79,
99,32,39,5,127,162,160,187,128,5,3,252,137,12,32,148,5,198,85,204,176,166,138,221,6,135,219,3,217,238,212,99,21,85,149,148,149,149,81,48,196,87,30,210,0,144,170,170,42,149,222,35,237,71,205,40,183,196,
78,169,66,119,228,21,210,1,61,65,138,5,148,141,123,176,203,128,83,6,220,54,32,170,234,12,160,63,169,179,166,219,55,109,198,206,150,105,232,103,84,120,43,45,41,193,110,198,171,51,184,220,176,17,81,48,19,
113,12,214,82,99,152,119,190,196,93,12,64,194,237,118,171,178,44,155,223,131,36,233,118,38,102,183,175,252,116,157,7,128,249,118,244,88,49,186,176,18,187,221,14,164,106,118,178,181,38,85,99,93,17,138,
138,138,18,198,231,64,8,129,221,110,239,179,0,43,15,252,190,30,0,208,231,243,193,225,208,189,49,154,166,105,165,165,165,52,216,156,101,85,210,170,36,184,92,46,85,146,36,66,51,193,137,40,234,193,243,226,
241,13,252,120,214,143,151,221,17,12,10,72,36,122,204,30,17,116,0,72,136,81,12,156,131,90,34,251,179,152,98,144,82,9,7,71,237,217,88,130,192,52,205,59,81,132,196,186,11,13,214,82,18,82,64,80,134,14,204,
52,98,184,121,165,20,248,75,18,93,196,57,97,188,154,218,51,132,185,95,164,220,168,18,210,221,169,20,252,153,76,161,152,250,188,221,46,195,225,116,64,82,28,230,166,186,180,180,148,2,35,75,241,249,178,178,
50,85,20,69,194,38,182,233,94,153,238,109,147,39,254,77,240,71,82,37,86,108,146,254,28,108,146,206,140,186,101,32,161,232,108,40,117,137,71,13,215,249,29,119,62,130,135,254,144,114,5,87,85,87,99,231,182,
109,232,55,96,128,62,14,21,9,2,210,175,83,150,229,140,218,222,224,234,14,59,28,14,53,77,226,69,212,179,173,145,7,127,121,0,152,111,125,3,36,209,29,182,207,231,99,75,238,104,204,38,147,110,44,225,241,120,
146,148,206,239,235,0,48,223,190,6,19,141,44,155,26,117,130,32,64,85,85,82,85,85,69,93,76,4,153,101,163,8,0,226,116,58,53,86,26,136,136,162,9,142,142,119,224,103,53,126,77,16,192,100,53,195,0,3,132,73,
224,16,115,48,73,60,43,122,20,193,95,26,232,163,151,98,85,117,132,94,167,36,48,59,84,6,8,106,0,100,77,87,67,145,69,253,213,6,253,149,144,20,8,36,72,177,127,172,75,220,116,139,139,41,247,184,192,130,61,
164,220,228,34,195,156,218,108,186,134,169,164,216,169,148,149,86,90,90,74,147,232,88,209,121,19,119,58,157,78,98,179,217,72,134,184,118,15,108,83,16,152,235,206,193,2,218,12,87,176,102,176,160,78,13,
136,217,0,159,162,3,191,152,193,2,198,85,224,201,215,118,96,225,188,84,21,189,210,146,18,243,231,91,175,187,16,255,243,204,250,180,44,126,195,238,8,115,240,181,214,181,12,13,67,131,225,228,209,126,126,
9,201,3,192,127,43,208,213,29,104,98,43,107,28,234,185,52,77,203,201,142,209,159,237,118,59,203,250,129,1,126,230,252,98,44,172,132,186,125,41,195,114,176,205,200,236,52,43,16,16,66,16,141,70,17,12,6,
209,210,210,114,92,196,23,90,245,67,79,251,143,103,116,186,235,183,190,202,210,241,125,24,137,68,208,217,217,121,200,125,40,203,178,89,5,134,62,218,242,242,114,234,106,210,184,5,200,60,104,9,51,218,47,
212,181,214,221,194,170,145,76,118,37,119,191,167,51,102,199,26,4,82,224,70,56,112,199,222,147,213,61,18,142,21,21,248,247,142,238,253,153,248,128,246,31,117,113,139,134,11,88,35,169,56,21,98,48,128,244,
125,24,46,70,145,24,177,144,4,80,37,253,158,109,4,32,34,165,23,51,159,3,101,65,137,150,2,83,48,146,62,68,230,239,60,91,170,200,122,124,156,152,74,56,131,207,231,83,145,89,183,215,220,92,15,28,56,80,205,
20,219,238,57,232,230,65,32,4,253,186,155,66,64,115,4,104,14,3,161,164,14,126,29,114,202,13,236,144,0,143,145,36,67,143,184,10,188,179,226,109,44,156,151,98,1,29,62,31,162,193,32,28,94,47,38,212,33,77,
186,41,153,76,66,211,52,26,30,196,51,183,38,227,105,48,156,38,203,73,44,64,110,111,109,43,161,2,173,81,160,43,174,187,178,53,162,223,151,71,1,138,157,122,204,99,190,229,1,96,159,109,179,103,207,198,169,
167,158,154,243,51,123,246,236,193,210,165,75,115,38,145,216,237,118,44,92,184,16,67,135,14,205,250,153,206,206,78,60,242,200,35,216,189,123,119,78,16,8,0,14,135,131,47,110,207,34,16,145,238,90,205,184,
42,28,124,77,198,218,218,90,204,156,57,19,83,167,78,197,216,177,99,81,94,94,78,179,231,144,76,38,177,115,231,78,172,95,191,30,107,215,174,197,154,53,107,176,111,223,190,227,170,79,247,238,221,139,151,
95,126,25,219,182,109,235,209,247,11,11,11,241,157,239,124,7,133,133,122,185,225,120,60,142,23,94,120,1,31,127,252,113,159,189,231,1,3,6,96,214,172,89,152,58,117,42,198,141,27,135,178,178,50,179,15,19,
137,4,26,27,27,177,126,253,122,172,89,179,230,160,251,144,214,63,165,49,128,170,170,18,11,102,133,47,22,175,41,138,162,101,234,75,166,51,37,25,27,37,2,252,115,59,176,170,135,73,237,52,118,206,171,0,99,
203,128,193,133,64,149,55,21,91,119,180,65,96,6,163,39,164,178,126,233,159,85,13,88,190,29,120,119,119,110,48,92,224,0,46,29,5,148,184,142,25,184,37,178,44,167,197,57,10,20,196,83,96,102,184,122,77,192,
42,0,187,131,192,147,95,0,193,184,17,235,200,24,134,106,252,66,0,204,168,2,102,84,91,223,91,103,28,120,242,115,253,21,2,80,160,0,151,140,2,10,29,41,86,84,228,128,191,196,148,186,164,98,246,69,69,69,26,
51,135,242,213,78,232,125,17,171,13,116,79,159,57,5,129,93,113,224,131,125,192,91,59,128,117,123,128,237,237,58,56,162,137,33,146,8,248,237,192,144,66,96,88,9,48,168,64,79,8,137,178,32,48,9,252,231,255,
188,129,59,126,56,199,114,83,42,234,12,188,89,189,71,85,85,10,254,104,9,63,129,35,147,137,36,73,132,181,207,204,106,50,61,55,136,253,33,96,205,46,221,118,63,57,0,236,10,234,238,108,24,201,46,229,30,160,
62,0,76,174,0,166,85,1,181,254,60,179,152,7,128,125,176,157,112,194,9,184,229,150,91,114,126,166,185,185,25,187,119,239,198,243,207,63,159,245,51,179,102,205,194,29,119,220,129,218,218,218,156,64,242,
245,215,95,183,4,128,236,128,228,216,42,43,14,68,5,32,40,138,162,81,102,197,168,208,208,171,123,47,45,45,197,55,191,249,77,44,92,184,16,227,198,141,131,211,233,180,44,49,53,96,192,0,156,120,226,137,184,
226,138,43,240,222,123,239,97,201,146,37,88,182,108,25,47,123,210,103,251,52,153,76,98,238,220,185,184,239,190,251,240,250,235,175,155,21,47,178,53,159,207,135,107,175,189,214,236,203,174,174,46,108,218,
180,169,79,2,192,64,32,128,243,207,63,31,23,93,116,145,217,135,86,173,174,174,14,179,102,205,194,229,151,95,126,208,125,72,43,198,208,76,73,227,89,229,100,86,172,22,30,210,131,5,135,16,96,245,46,224,174,
247,123,9,190,160,51,15,253,125,192,233,3,128,111,12,1,134,151,28,123,16,200,2,65,211,46,5,253,30,239,89,159,251,92,213,30,224,27,131,129,82,247,177,181,53,58,191,176,110,110,150,66,18,153,142,23,0,180,
68,128,7,55,0,7,34,185,207,235,146,129,83,106,211,53,230,232,169,15,132,129,39,190,0,118,119,233,191,87,121,128,111,14,211,89,64,62,118,84,52,1,96,170,236,165,193,92,19,35,164,198,10,248,17,195,142,137,
85,31,246,6,180,168,4,88,187,19,120,244,115,29,252,237,205,49,180,90,162,192,182,14,224,141,6,160,206,15,76,174,212,237,212,99,3,98,134,75,184,117,255,94,180,118,193,212,6,84,220,110,236,106,104,64,117,
109,45,110,88,60,11,247,190,180,17,201,100,146,30,34,12,125,88,131,9,20,145,37,202,128,138,149,19,244,94,215,47,174,2,175,111,3,30,254,20,248,215,110,3,152,91,180,157,65,224,253,189,192,227,159,3,163,
74,129,243,134,0,11,134,2,149,222,60,230,200,3,192,227,172,149,148,148,224,210,75,47,197,187,239,190,139,189,123,247,102,252,221,239,247,99,241,226,197,57,193,95,111,39,90,131,1,204,9,4,37,73,34,124,121,
183,158,186,128,135,15,31,142,27,110,184,1,231,159,127,62,60,30,79,214,69,139,191,207,211,78,59,13,227,198,141,195,196,137,19,113,247,221,119,99,199,142,29,125,127,128,200,50,206,60,243,76,140,26,53,10,
75,150,44,193,146,37,75,208,208,208,112,220,219,229,136,17,35,112,227,141,55,166,245,97,119,160,164,160,160,0,115,231,206,197,216,177,99,49,97,194,4,220,125,247,221,104,108,108,236,21,8,164,241,96,162,
40,246,132,89,33,188,93,242,46,168,195,74,85,193,112,185,69,128,13,7,128,149,59,129,107,199,2,231,12,57,250,12,4,141,115,204,230,198,22,122,113,158,190,196,158,88,49,156,86,64,80,236,225,53,139,66,58,
160,99,155,77,228,92,148,72,101,212,242,207,80,48,99,4,13,246,143,198,156,234,241,209,196,98,147,98,9,112,15,166,117,196,116,182,243,175,31,3,27,91,123,1,26,1,108,233,0,182,118,232,108,217,153,3,117,247,
105,204,136,9,252,197,111,159,198,255,252,226,2,243,243,90,76,47,17,95,95,209,101,150,117,140,199,227,136,197,98,34,82,90,217,178,113,136,221,129,193,222,180,80,2,120,224,99,224,190,143,116,198,175,39,
45,146,212,129,224,23,205,64,153,7,248,230,208,60,19,152,7,128,199,97,155,61,123,54,230,207,159,143,7,30,120,32,227,111,115,230,204,193,188,121,243,142,196,191,37,57,214,11,194,22,236,238,9,128,163,109,
204,152,49,184,227,142,59,216,210,101,25,237,192,129,3,232,236,236,52,235,220,178,204,82,32,16,192,15,127,248,67,148,150,150,226,142,59,238,56,110,192,84,77,77,13,110,187,237,54,76,154,52,9,247,221,119,
31,94,123,237,181,110,217,192,190,218,234,235,235,123,220,135,78,167,51,173,15,5,65,200,232,195,158,0,121,182,222,179,193,36,176,204,10,201,181,89,177,98,0,143,116,83,137,238,166,218,215,165,187,167,190,
53,252,88,1,38,202,188,124,125,230,67,43,16,207,3,193,158,2,87,42,250,156,22,71,71,217,60,193,26,48,178,154,145,66,150,107,99,231,67,139,144,154,180,185,180,160,160,224,160,123,167,53,2,252,241,125,96,
201,39,64,123,44,203,198,9,192,132,114,29,216,181,68,128,174,68,250,103,9,128,128,91,103,121,59,99,58,248,139,41,64,60,18,195,129,14,32,224,215,63,183,187,169,9,178,195,129,202,154,26,120,93,18,146,201,
36,226,241,56,18,137,132,12,163,68,168,193,4,242,224,79,80,85,85,224,203,66,246,212,38,85,77,191,191,187,222,215,175,159,109,138,164,179,238,54,3,98,106,68,207,108,110,137,164,30,248,188,1,186,43,56,15,
254,242,0,240,184,108,30,143,7,23,95,124,49,86,172,88,129,173,91,183,154,239,87,84,84,224,242,203,47,71,73,201,17,247,51,145,131,32,15,50,90,109,109,45,110,191,253,118,75,224,192,78,152,79,63,253,52,254,
244,167,63,161,160,160,0,19,39,78,196,188,121,243,112,226,137,39,162,168,168,200,100,130,46,190,248,98,4,131,65,220,113,199,29,104,105,105,57,46,250,209,102,179,225,140,51,206,192,200,145,35,241,240,195,
15,99,233,210,165,199,29,27,88,87,87,151,181,15,217,246,212,83,79,101,237,67,90,118,144,237,195,214,214,214,30,45,250,172,157,48,204,74,214,197,85,150,229,35,6,125,252,118,224,226,17,122,156,92,76,5,118,
116,0,159,53,1,155,218,82,153,165,91,219,129,63,189,175,199,33,77,174,60,150,160,169,111,51,123,135,11,220,10,189,156,164,4,67,243,143,205,12,71,22,22,81,96,244,1,115,63,215,156,9,121,135,205,30,147,26,
176,228,83,157,249,235,202,177,151,44,243,0,63,159,169,135,38,116,196,128,109,237,192,138,29,192,202,29,192,246,78,96,106,57,112,206,96,93,27,144,2,40,122,220,117,247,179,248,245,79,190,9,0,24,53,98,56,
218,90,219,0,0,63,56,119,40,254,248,220,54,36,18,9,36,18,9,201,0,126,44,8,148,24,16,40,104,154,38,16,66,4,51,41,174,23,59,146,247,246,0,15,126,146,9,254,0,160,210,3,92,57,6,56,99,16,96,151,244,107,222,
21,212,195,27,222,108,208,159,209,85,99,129,234,188,251,55,15,0,143,231,54,109,218,52,156,123,238,185,248,195,31,82,245,132,207,60,243,76,156,120,226,137,71,251,82,8,160,199,182,244,230,75,138,162,224,
154,107,174,193,130,5,11,186,101,11,67,161,16,26,26,26,160,105,26,214,175,95,143,231,158,123,14,243,231,207,199,247,190,247,61,76,154,52,201,4,129,139,23,47,198,23,95,124,129,63,255,249,207,199,85,95,
82,54,112,226,196,137,248,203,95,254,130,215,94,123,173,79,87,25,97,0,23,174,190,250,234,110,193,95,79,251,80,150,101,92,122,233,165,248,242,203,47,123,212,135,189,96,86,142,10,223,229,83,128,171,199,
1,3,11,245,133,51,9,73,248,234,0,0,32,0,73,68,65,84,156,0,182,182,233,113,88,143,127,174,39,32,0,192,134,38,224,217,175,128,250,50,125,145,202,183,35,7,110,123,203,116,242,37,200,120,0,216,29,112,238,
14,104,50,33,53,135,221,38,87,237,4,30,254,36,55,248,163,163,161,200,9,84,120,116,166,111,64,33,48,189,10,56,189,14,88,182,85,103,7,7,22,232,224,208,109,3,162,70,82,72,52,9,68,163,97,4,35,128,215,9,120,
139,138,241,225,199,27,80,94,81,129,58,63,120,6,208,97,0,64,187,1,0,169,59,88,4,32,39,18,9,225,96,170,21,17,2,188,221,8,108,206,178,63,108,232,208,193,97,103,28,184,112,4,48,180,88,63,78,234,15,156,55,
84,103,52,167,85,229,199,200,145,106,98,254,17,28,157,166,40,10,22,46,92,136,250,250,122,0,192,144,33,67,176,120,241,98,184,221,238,62,113,125,221,201,208,156,112,194,9,184,240,194,11,211,130,248,123,
218,90,90,90,176,116,233,82,220,124,243,205,88,189,122,181,249,190,215,235,197,101,151,93,134,17,35,70,28,151,253,57,127,254,124,220,125,247,221,184,237,182,219,80,83,83,211,231,175,121,198,140,25,125,
170,15,153,133,149,63,142,254,68,40,232,241,83,245,101,192,109,211,128,69,163,210,193,193,219,141,192,206,78,228,219,81,0,131,189,97,55,5,238,59,252,97,249,121,164,167,184,166,255,111,193,146,173,62,220,
45,148,0,158,254,18,216,222,209,139,251,68,202,39,235,144,129,73,149,192,127,76,212,193,146,93,214,19,98,156,50,224,178,233,98,209,110,69,255,249,127,238,125,217,60,143,170,170,216,215,164,215,67,31,63,
164,20,177,88,12,241,120,92,226,192,31,11,0,37,0,98,34,145,16,169,124,140,21,16,204,134,13,91,34,192,123,123,115,15,234,237,29,192,239,215,1,215,189,161,111,188,218,163,186,91,127,84,41,48,189,58,239,
250,205,3,192,175,73,171,175,175,199,5,23,92,0,187,221,142,243,206,59,15,83,167,78,61,46,174,91,146,36,156,126,250,233,232,223,191,255,33,157,103,229,202,149,184,235,174,187,210,50,153,235,235,235,49,
123,246,236,227,182,79,169,91,252,238,187,239,198,25,103,156,113,80,224,234,223,161,15,249,133,181,47,151,29,44,114,2,223,26,166,51,46,180,237,233,210,93,196,249,118,116,193,96,111,192,145,208,13,192,
203,6,52,143,133,59,253,171,22,221,205,217,171,197,90,76,23,180,182,73,186,173,42,18,96,55,106,5,187,100,29,252,185,12,240,231,148,129,112,123,138,126,27,87,95,143,109,219,182,33,30,14,227,146,19,156,
212,5,76,25,64,39,210,153,64,201,0,130,34,101,0,233,161,105,90,143,118,107,145,100,207,54,78,154,145,185,127,203,74,253,88,179,75,143,29,204,183,60,0,252,218,52,73,146,176,96,193,2,124,247,187,223,197,
5,23,92,0,155,205,118,92,92,119,117,117,53,102,207,158,125,88,118,196,175,190,250,42,150,47,95,110,254,174,40,10,102,205,154,5,159,207,119,220,246,171,162,40,56,235,172,179,112,247,221,119,227,246,219,
111,239,81,86,109,190,15,251,118,43,113,166,178,69,1,67,90,35,154,159,195,142,103,16,121,172,192,30,223,8,1,214,238,2,26,59,123,119,31,244,178,37,33,149,209,44,137,186,157,218,36,157,5,180,75,41,54,208,
101,212,12,118,201,192,242,119,15,232,155,155,64,192,188,8,167,172,107,1,26,49,128,118,3,252,57,144,98,0,105,44,160,28,141,70,69,150,253,235,169,59,152,38,121,244,180,181,69,129,199,62,215,217,192,223,
175,203,111,186,242,0,240,107,214,6,15,30,140,31,255,248,199,24,51,102,204,113,115,205,5,5,5,8,208,137,227,16,91,36,18,193,242,229,203,211,132,177,71,140,24,97,10,39,31,207,109,192,128,1,88,180,104,209,
209,72,234,201,247,225,17,110,209,100,186,91,75,22,245,197,52,223,250,30,192,235,141,11,184,47,180,164,6,52,6,83,137,70,189,90,176,197,84,9,61,209,72,106,145,13,16,168,136,153,174,96,151,77,119,23,191,
245,143,215,204,115,196,84,21,107,223,123,15,241,112,24,215,156,59,134,2,64,7,115,56,145,98,1,109,0,164,68,34,33,81,0,72,69,189,233,248,32,12,176,229,91,177,83,143,81,236,109,251,170,21,248,245,90,224,
166,183,244,100,151,124,59,50,45,159,4,114,24,91,99,99,35,2,129,128,89,240,222,122,194,18,80,86,86,102,254,158,72,36,208,218,218,154,246,94,95,107,21,21,21,112,185,92,135,237,124,159,127,254,57,58,58,
58,76,198,200,239,247,127,109,216,163,190,234,2,206,247,97,207,155,70,116,145,221,38,38,107,177,208,161,103,97,230,91,190,29,242,6,42,169,87,195,232,21,208,53,192,174,170,234,217,177,239,239,77,213,65,
78,106,250,33,66,143,11,44,115,235,160,207,105,3,28,113,253,103,135,12,52,30,0,250,7,128,177,99,198,224,203,207,63,7,8,193,152,146,102,90,9,196,110,0,63,23,82,110,96,217,0,128,182,68,34,33,168,170,154,
42,26,96,102,3,231,6,218,178,8,156,216,31,120,230,75,96,127,184,151,64,153,0,255,216,10,236,13,2,183,77,7,78,31,152,183,157,195,221,242,12,224,97,108,43,86,172,72,11,144,239,73,251,224,131,15,240,246,
219,111,247,233,251,242,122,189,135,21,216,196,98,177,52,23,2,173,19,219,23,91,48,24,60,110,106,249,230,251,240,208,91,75,68,215,44,187,239,35,157,5,164,109,124,121,30,0,230,219,225,105,73,77,47,249,118,
48,141,0,88,209,8,252,118,29,240,187,117,192,31,222,7,254,244,33,240,127,31,1,15,108,208,19,42,236,70,157,96,39,19,11,232,144,129,135,31,122,14,0,80,86,86,134,198,93,187,176,103,255,126,0,192,136,1,165,
46,164,24,63,214,21,236,48,0,160,233,2,86,85,53,45,6,176,39,109,102,63,224,252,97,128,124,144,140,236,71,7,128,187,63,212,227,38,243,237,48,19,22,249,71,112,248,90,67,67,3,86,174,92,137,73,147,38,193,
239,247,119,251,249,104,52,138,39,159,124,18,197,197,197,125,250,190,66,161,16,84,85,61,124,70,103,148,160,163,77,85,85,68,163,125,51,192,234,165,151,94,66,107,107,43,46,188,240,66,148,150,150,30,183,
182,249,239,220,135,185,22,226,245,251,128,166,176,46,67,241,85,11,176,118,183,46,207,193,10,237,86,122,128,243,135,2,62,123,126,142,203,183,195,48,118,68,189,238,116,79,27,95,182,46,87,19,5,61,30,208,
38,3,246,164,14,4,29,146,30,27,216,21,73,209,142,129,210,82,52,52,52,160,178,188,28,55,159,63,168,236,185,87,222,225,129,31,11,8,35,209,104,84,164,224,143,50,127,128,206,64,210,122,206,2,210,235,85,211,
230,182,1,223,155,160,203,221,60,254,57,144,56,136,253,244,154,93,192,203,91,128,65,133,199,166,70,247,215,181,229,31,229,97,110,175,190,250,42,222,124,243,205,30,125,118,245,234,213,88,182,108,25,72,
31,151,249,223,187,119,47,194,225,240,97,59,223,128,1,3,210,220,145,157,157,157,105,241,100,125,169,109,222,188,25,183,222,122,43,174,191,254,122,172,89,179,166,207,247,85,190,15,123,241,76,66,192,205,
43,129,139,94,2,174,252,7,240,211,85,192,178,45,233,224,207,99,3,46,27,13,204,173,203,207,109,71,27,36,29,106,12,95,52,121,112,113,118,71,186,185,108,64,249,17,82,255,146,4,192,38,164,178,130,169,251,
215,97,211,127,223,184,91,127,168,99,105,12,58,33,40,116,38,169,16,52,141,255,115,33,21,7,104,3,96,139,199,227,82,50,153,20,84,85,69,10,8,246,252,186,250,249,116,121,165,235,39,3,53,7,193,164,171,4,120,
171,81,79,18,201,183,60,0,236,179,237,192,129,3,88,186,116,41,246,237,219,151,243,115,29,29,29,120,236,177,199,142,139,74,18,237,237,237,221,86,122,232,241,196,46,203,56,245,212,83,211,88,207,141,27,55,
162,173,173,173,207,222,127,40,20,194,99,143,61,134,107,255,191,189,123,15,178,178,190,243,60,254,126,110,231,156,238,166,233,11,208,77,211,220,7,67,3,98,80,3,106,220,72,212,12,17,39,99,165,118,140,73,
109,105,166,146,204,120,171,154,173,73,149,178,107,216,221,201,78,169,155,114,204,238,230,182,86,50,102,172,200,148,76,24,73,212,101,194,204,70,137,160,162,68,36,160,40,226,5,20,26,144,139,72,219,167,
111,231,242,60,251,199,239,121,186,159,115,232,110,154,139,240,156,230,243,170,58,117,154,211,167,15,253,59,191,167,207,249,156,239,239,249,253,126,119,220,193,143,127,252,99,14,135,235,104,85,146,243,
189,15,135,114,184,27,14,117,155,25,190,133,178,202,196,164,49,240,215,11,225,246,139,205,176,154,156,61,53,158,169,92,157,142,55,142,152,133,132,35,85,238,200,247,24,254,36,57,150,57,157,192,177,78,237,
103,175,104,133,191,248,52,220,50,15,166,196,22,28,136,22,197,118,109,179,181,90,218,137,133,192,176,10,184,226,145,95,2,48,177,181,149,61,237,237,188,31,46,231,244,179,251,111,191,144,161,135,129,83,
189,189,189,78,161,80,32,58,15,48,8,2,179,135,227,32,33,112,168,96,56,169,22,254,211,229,240,191,190,96,118,46,169,58,201,191,169,247,59,70,176,104,182,40,0,158,107,235,214,173,99,237,218,181,195,86,139,
158,121,230,25,214,174,93,91,17,237,105,111,111,103,195,134,13,103,164,250,117,197,21,87,176,100,201,146,254,127,23,10,5,158,127,254,249,138,168,30,189,246,218,107,124,231,59,223,225,174,187,238,226,197,
23,95,172,168,99,82,125,56,114,227,171,224,186,25,240,224,53,240,237,133,102,173,53,57,187,78,183,74,214,87,132,245,123,205,208,126,100,90,157,121,220,115,205,178,204,2,199,211,234,78,238,103,192,12,127,
126,105,22,220,127,21,252,215,43,97,238,248,227,3,162,27,86,255,162,16,152,113,7,174,157,178,178,234,190,246,118,114,221,221,124,254,143,186,91,48,85,192,42,6,214,3,140,134,130,163,0,104,197,3,96,52,18,
236,135,59,195,141,228,149,37,229,152,106,250,131,215,192,223,126,14,22,156,196,220,199,66,48,186,246,196,86,0,28,165,178,217,44,143,62,250,40,187,119,239,30,244,251,7,15,30,228,209,71,31,229,208,161,
67,21,209,158,124,62,207,154,53,107,56,112,224,192,105,61,206,244,233,211,185,227,142,59,152,51,103,78,255,109,219,183,111,231,153,103,158,169,152,161,213,168,111,239,188,243,78,126,242,147,159,112,228,
200,17,245,97,133,245,97,196,181,225,178,22,88,60,197,4,190,175,95,8,255,249,114,248,251,165,240,208,117,112,195,5,170,252,157,43,141,25,184,236,52,246,94,94,243,54,252,235,174,210,96,244,185,201,102,
54,119,18,124,170,209,252,62,167,194,179,205,144,110,218,25,124,191,227,254,101,97,156,112,125,64,59,12,129,97,16,124,251,152,217,147,125,110,91,27,251,15,236,239,223,139,189,97,108,117,13,3,179,129,163,
33,224,20,144,234,238,238,118,163,225,223,254,16,56,194,105,32,65,96,182,88,124,118,15,244,133,19,171,90,198,152,202,250,143,254,216,92,183,140,32,236,55,164,77,155,68,1,48,241,94,124,241,69,158,120,226,
137,227,102,144,6,65,192,218,181,107,89,183,110,93,69,181,103,195,134,13,252,250,215,191,62,229,55,249,69,139,22,113,239,189,247,242,213,175,126,181,255,182,158,158,30,30,123,236,49,94,125,245,213,138,
235,223,173,91,183,114,207,61,247,176,108,217,50,54,109,218,84,17,225,71,125,88,170,165,6,238,255,60,252,226,75,38,244,125,255,26,179,220,196,31,207,128,9,213,163,231,181,200,15,78,124,73,218,225,235,
57,240,197,153,48,189,238,228,126,46,87,132,127,126,19,30,220,4,237,157,3,183,207,155,0,215,76,79,198,16,48,152,74,228,87,231,152,61,124,71,42,94,188,203,21,204,236,216,125,157,101,111,232,241,245,1,195,
240,231,133,67,193,105,7,82,174,197,47,255,223,14,243,156,204,153,67,161,232,147,239,51,227,228,143,220,247,31,230,51,48,4,92,178,36,76,95,95,159,27,31,2,54,85,192,145,29,59,31,116,193,255,252,61,220,
250,27,248,187,77,38,12,70,147,69,46,110,54,149,192,7,175,129,37,211,77,184,29,242,245,103,210,201,45,42,45,35,248,16,172,167,224,147,209,215,215,199,202,149,43,185,246,218,107,251,247,255,5,51,83,120,
197,138,21,116,118,118,86,84,123,186,187,187,121,232,161,135,152,49,99,6,215,95,127,253,176,247,77,165,82,212,215,215,147,78,167,153,52,105,18,75,151,46,229,203,95,254,50,151,94,122,105,201,253,86,174,
92,201,138,21,43,42,118,98,69,103,103,39,143,60,242,8,219,182,109,227,182,219,110,227,198,27,111,164,177,177,81,125,88,33,2,204,27,202,248,234,209,251,58,212,209,7,15,253,97,248,202,151,5,92,61,13,174,
156,156,172,223,125,81,139,169,194,254,112,243,208,247,201,230,205,100,30,63,172,50,173,121,7,158,122,27,246,101,7,238,211,152,129,111,93,4,243,19,54,137,255,179,147,205,185,124,15,108,58,241,228,134,
131,93,48,54,5,221,121,216,122,208,84,211,214,239,61,126,47,225,104,145,104,215,1,175,104,2,149,23,27,6,78,3,93,69,147,36,171,106,107,1,216,181,103,15,19,39,77,98,110,19,245,148,78,6,137,159,3,232,229,
114,57,162,16,232,4,126,201,230,221,67,205,6,238,202,153,37,149,86,238,48,225,252,251,191,55,91,190,93,63,211,172,15,56,161,218,220,111,225,36,179,23,119,103,14,94,220,127,124,251,167,215,153,161,239,
140,18,139,2,96,165,216,178,101,11,171,86,173,98,222,188,121,184,174,139,239,251,60,249,228,147,188,240,194,11,21,217,158,215,95,127,157,239,125,239,123,212,212,212,176,120,241,226,33,239,119,221,117,
215,113,193,5,23,208,210,210,194,248,241,227,153,58,117,42,142,51,80,187,247,125,159,85,171,86,241,192,3,15,156,112,178,76,165,244,243,178,101,203,120,233,165,151,184,253,246,219,89,184,112,225,39,186,
145,188,250,80,70,234,227,28,252,108,235,240,247,177,45,115,66,126,210,2,96,218,133,111,204,55,193,238,95,222,29,252,62,143,239,52,75,132,244,22,224,163,190,227,23,88,30,155,130,191,252,180,169,182,217,
9,251,147,116,109,248,243,249,38,244,60,244,135,161,67,224,7,93,176,236,119,38,88,117,23,224,96,22,186,10,131,7,249,180,23,110,15,231,15,108,17,151,114,204,46,33,41,39,220,227,45,229,113,184,119,12,19,
50,89,26,27,26,216,187,111,31,135,143,28,161,117,234,84,62,53,173,105,236,91,239,31,234,166,108,50,72,95,95,159,147,207,231,137,214,2,44,22,125,2,31,172,128,97,215,167,121,243,168,153,89,159,11,87,160,
202,251,38,0,190,180,207,76,10,169,77,153,144,90,12,76,184,141,7,247,72,67,6,110,93,0,159,159,170,191,231,51,77,67,192,159,32,223,247,89,189,122,53,155,54,109,2,224,141,55,222,96,229,202,149,244,245,245,
85,108,155,158,123,238,57,150,47,95,206,175,126,245,43,10,133,194,160,247,153,55,111,30,55,220,112,3,11,23,46,100,198,140,25,37,193,161,163,163,131,159,254,244,167,44,95,190,156,157,59,119,142,158,74,
75,71,7,143,60,242,8,119,222,121,39,63,255,249,207,233,232,232,80,31,74,197,72,106,253,246,130,70,184,251,50,248,210,31,13,158,51,14,118,193,214,67,38,104,148,135,191,169,99,97,217,229,240,87,159,49,213,
165,36,26,155,134,191,186,20,150,95,1,109,67,12,30,20,3,120,253,8,108,63,2,187,142,13,30,254,234,82,240,103,109,112,73,147,9,186,86,56,12,236,88,38,252,185,253,179,130,109,82,158,199,239,118,152,68,246,
169,89,179,74,182,119,251,225,178,63,157,139,201,137,81,248,75,3,169,158,158,30,183,175,175,207,202,231,243,225,48,176,153,5,12,195,15,3,207,110,132,219,22,152,235,184,66,96,246,66,126,253,136,233,191,
215,14,195,187,199,74,23,95,7,179,100,204,93,139,224,27,23,149,238,205,45,103,232,67,136,158,130,79,214,206,157,59,121,236,177,199,184,232,162,139,88,181,106,21,155,55,111,174,248,54,189,240,194,11,236,
219,183,143,109,219,182,241,149,175,124,133,217,179,103,227,121,195,79,175,235,233,233,97,203,150,45,252,226,23,191,224,241,199,31,175,200,37,67,70,226,149,87,94,225,238,187,239,102,211,166,77,220,118,
219,109,180,181,181,169,15,37,249,1,48,193,35,248,159,105,129,123,23,195,236,113,102,120,119,215,49,19,138,134,210,144,129,207,182,194,215,231,195,23,103,36,63,56,212,166,225,214,139,225,194,9,102,161,
228,103,222,135,253,217,145,253,236,184,12,92,218,2,55,205,134,207,79,51,65,55,87,12,195,159,109,134,130,163,9,33,174,13,169,0,82,158,203,107,187,143,113,211,197,105,62,117,193,5,188,244,242,203,188,187,
107,23,205,77,77,204,28,95,93,91,22,0,51,64,38,159,207,123,133,66,161,127,8,216,15,76,5,48,136,125,120,136,138,129,253,215,129,249,125,110,93,0,115,198,193,99,111,152,181,252,14,100,79,188,62,227,132,
106,184,178,21,110,158,7,95,152,161,240,167,0,152,64,207,62,251,44,223,253,238,119,75,254,61,152,167,158,122,138,230,230,102,86,175,94,61,232,182,98,229,143,51,152,206,206,206,211,158,193,121,38,189,247,
222,123,220,119,223,125,172,89,179,134,197,139,23,115,245,213,87,51,107,214,44,106,107,107,201,100,50,4,65,64,79,79,15,29,29,29,236,216,177,131,167,159,126,154,103,159,125,150,119,222,121,39,209,231,139,
141,180,79,135,115,236,216,49,30,126,248,97,182,109,219,198,205,55,223,76,54,155,77,100,91,71,107,31,90,150,121,51,60,209,249,66,99,211,230,252,176,74,100,3,215,78,59,185,29,37,134,115,69,107,178,219,
59,171,1,254,203,149,230,60,176,231,247,154,29,91,222,235,48,195,134,1,38,224,76,168,134,139,155,224,170,169,102,6,113,37,77,228,177,45,248,119,83,224,211,77,176,249,3,179,223,239,166,3,240,65,22,186,
242,225,94,191,150,57,166,171,93,104,173,53,19,40,62,219,106,150,82,105,72,155,231,161,24,196,38,130,216,102,251,181,104,40,56,237,64,202,178,72,165,60,82,197,48,81,185,46,105,207,163,189,189,157,195,
135,15,211,58,109,26,19,39,212,141,249,224,112,71,23,3,21,192,76,95,95,159,151,203,229,172,92,46,215,63,12,76,16,152,115,255,172,48,8,134,75,193,88,131,204,76,190,106,42,92,60,209,156,191,184,177,221,
180,113,207,199,166,109,126,96,2,99,149,103,214,222,92,208,100,158,139,207,76,212,18,76,10,128,9,182,126,253,250,17,237,227,219,222,222,206,15,126,240,131,33,23,226,29,233,227,36,77,177,88,100,203,150,
45,253,85,161,49,99,198,208,208,208,64,99,99,35,65,16,112,248,240,97,58,58,58,42,106,151,136,51,217,23,47,191,252,50,111,190,249,166,250,240,28,188,153,94,51,205,92,70,43,199,54,149,145,47,156,71,59,148,
120,54,44,108,49,193,224,207,231,67,79,97,96,241,110,219,50,33,176,33,83,217,75,133,212,166,205,132,156,207,77,49,251,82,119,229,224,72,143,57,79,48,237,152,53,42,107,82,102,97,231,134,12,216,54,253,179,
113,253,176,28,103,133,207,135,205,192,162,208,94,184,69,92,10,72,165,60,188,130,205,123,217,58,166,143,249,144,73,45,45,236,222,179,167,255,67,221,255,89,254,149,217,255,254,175,31,254,136,129,74,96,
58,151,203,185,209,240,111,62,159,199,243,125,172,104,253,191,19,156,7,216,223,182,148,105,215,149,147,225,88,111,105,255,69,199,116,198,129,250,140,42,126,10,128,163,204,153,218,133,33,201,237,59,122,
244,40,123,246,236,81,103,199,84,210,108,111,245,161,84,2,203,26,253,149,33,215,134,230,26,160,6,102,54,28,255,253,168,0,31,196,158,19,194,153,183,182,13,150,111,174,109,11,28,39,156,21,108,67,202,2,207,
117,73,165,92,158,218,116,136,255,120,173,195,228,214,86,19,0,195,71,187,176,37,87,143,217,2,46,154,17,156,202,229,114,94,62,159,39,159,207,155,97,224,66,17,43,218,13,132,129,42,222,72,130,160,109,169,
178,151,152,15,203,122,10,68,68,68,42,43,4,71,121,203,10,151,94,137,95,28,219,188,185,59,182,169,242,184,97,5,208,179,33,229,121,120,158,199,225,14,51,227,98,218,148,41,0,188,187,107,55,185,129,253,194,
163,0,152,10,3,160,155,203,229,172,129,153,192,190,169,58,250,165,65,84,27,117,40,0,138,136,136,200,217,14,134,101,33,48,154,12,18,109,13,231,57,182,57,7,48,149,34,149,50,39,144,218,153,12,174,235,178,
167,189,157,67,225,62,231,119,125,235,79,166,196,2,96,58,159,207,59,209,58,128,249,124,222,204,28,142,15,61,19,59,15,48,182,45,156,182,110,83,0,20,17,17,145,79,242,205,220,14,171,129,86,233,121,128,209,
114,48,81,21,48,229,185,164,82,41,60,207,227,189,172,89,159,101,92,184,128,125,116,30,224,159,92,214,52,17,83,60,244,128,84,161,80,112,163,89,192,190,239,147,47,22,74,3,159,130,158,2,224,104,229,186,30,
77,77,205,9,253,163,63,238,140,231,83,250,83,180,44,139,116,58,153,83,34,45,203,62,35,109,76,167,211,137,93,160,217,182,79,191,141,231,67,31,154,205,78,211,9,125,165,176,206,76,27,221,52,65,18,143,211,
96,208,183,140,64,125,120,238,251,48,62,36,28,133,65,219,2,43,92,3,208,118,6,150,132,241,60,19,254,60,207,227,223,94,49,231,166,143,31,55,174,228,241,90,235,138,85,177,0,232,22,10,5,55,159,207,91,81,5,
176,88,12,240,109,175,255,28,192,83,127,162,18,220,135,10,128,231,181,254,89,27,77,77,19,88,178,100,201,9,215,73,59,219,210,233,52,109,109,109,100,74,223,244,187,70,120,192,119,0,253,203,110,214,213,213,
177,104,209,162,196,117,66,38,147,97,214,172,89,229,207,253,72,218,152,7,74,166,173,206,157,59,151,73,147,38,37,174,141,51,103,206,164,190,190,100,83,80,63,108,227,249,222,135,199,181,209,170,170,195,
158,122,89,242,94,210,221,12,214,248,89,224,156,254,113,106,181,204,195,170,77,216,186,44,1,88,141,51,177,50,167,127,156,170,15,63,153,208,103,197,222,212,163,115,3,237,40,111,99,102,2,167,234,38,146,
170,174,237,31,2,222,123,164,55,0,152,216,108,10,28,239,238,218,21,63,15,48,10,128,94,54,155,45,228,114,185,162,217,5,164,72,144,174,38,104,89,0,193,192,90,128,137,168,4,14,221,135,50,216,211,165,167,
96,72,219,129,75,162,234,204,45,183,220,140,235,58,188,245,214,91,131,174,229,119,182,57,142,67,91,91,27,95,251,218,215,176,29,59,254,73,231,69,224,224,8,30,162,29,120,31,152,0,80,95,95,207,178,101,119,
51,125,250,116,14,28,216,159,136,14,112,28,135,185,115,231,114,211,77,55,197,43,100,1,176,113,4,109,236,1,94,11,223,120,92,128,37,75,150,112,255,253,255,131,141,27,55,82,40,228,19,209,198,186,186,58,150,
46,93,202,204,153,51,227,55,239,7,94,86,31,30,223,70,171,170,30,239,234,187,177,26,166,65,246,192,136,102,29,158,133,86,98,53,207,197,91,112,83,188,210,121,202,199,169,59,123,9,44,189,15,127,207,70,8,
10,137,8,127,100,234,112,219,150,98,143,63,253,227,84,125,120,6,187,38,76,92,230,188,187,0,171,24,244,95,91,190,79,144,243,241,243,5,10,189,121,50,197,52,85,245,23,210,155,158,76,42,127,144,84,42,69,16,
4,61,64,117,107,107,43,174,227,176,103,223,62,102,29,62,204,228,105,211,152,51,179,165,122,199,174,3,199,0,247,208,161,67,93,217,108,246,163,66,161,80,235,251,62,164,234,112,47,251,11,236,9,211,176,251,
62,196,77,57,56,182,101,46,142,133,133,53,16,80,207,90,37,116,216,62,20,5,192,147,242,36,176,52,122,209,106,109,109,229,219,223,254,118,162,182,113,203,100,50,229,67,135,7,129,127,177,44,107,36,191,228,
123,192,255,13,67,174,13,48,127,254,124,218,102,183,145,79,72,56,26,162,141,31,0,191,57,81,27,45,203,10,130,32,88,23,6,249,5,0,85,85,85,220,114,203,45,220,120,227,159,37,166,125,142,227,144,78,31,55,28,
246,28,176,237,124,239,195,161,218,232,76,154,143,221,52,59,25,225,40,122,139,241,50,229,195,220,39,115,156,254,46,126,156,90,94,6,119,225,45,176,224,198,132,132,35,192,114,176,142,31,182,125,254,84,143,
211,81,216,135,235,206,69,31,14,4,192,160,255,82,44,22,113,138,69,236,124,30,114,57,130,222,94,252,238,30,250,62,206,146,206,118,227,125,248,97,255,16,112,103,103,231,7,7,179,181,205,205,99,168,169,170,
170,162,51,155,237,47,227,221,245,151,127,58,245,91,247,252,236,32,224,236,223,191,63,187,123,247,238,215,103,206,156,57,217,247,125,219,247,125,236,166,217,120,147,231,225,165,28,188,116,26,215,117,113,
28,7,219,182,177,109,187,63,248,157,181,0,56,76,31,42,206,40,0,158,172,223,2,255,12,220,26,61,79,142,227,80,93,157,216,229,229,179,192,79,129,167,71,244,122,110,89,126,16,4,255,8,204,7,110,140,110,247,
82,30,94,202,75,106,27,59,79,178,141,219,130,32,120,8,248,239,192,68,115,27,73,238,195,40,252,253,216,178,172,14,245,225,208,109,180,220,104,130,226,168,104,227,214,227,143,83,11,82,137,62,78,159,63,221,
227,116,148,245,225,182,115,210,135,253,11,2,6,88,152,253,231,109,199,199,47,20,112,236,34,174,157,199,9,92,92,223,33,149,15,240,250,242,120,158,153,5,220,213,213,181,231,173,183,222,122,245,149,247,38,
206,185,254,66,102,143,169,169,161,51,155,237,31,239,158,222,80,168,9,3,187,29,4,129,181,126,253,250,63,180,181,181,141,107,108,108,92,100,246,3,246,9,108,23,203,171,2,55,5,174,139,229,186,96,89,88,225,
222,225,150,101,157,203,243,174,79,170,15,207,71,58,7,112,232,63,232,78,224,123,192,15,25,217,80,213,185,252,236,218,14,252,40,124,65,238,58,137,54,238,2,238,3,30,11,3,100,146,219,184,247,84,218,8,60,
26,182,113,7,224,39,184,141,185,240,67,199,189,150,101,109,84,31,234,56,77,240,113,250,116,120,156,190,160,62,60,183,125,88,94,101,139,95,71,151,168,34,231,56,78,84,165,43,116,116,116,188,177,121,243,
230,117,187,118,237,218,123,215,253,43,94,5,168,171,27,11,192,71,199,142,1,208,52,166,152,137,229,4,251,157,119,222,57,186,102,205,154,39,15,28,56,240,59,223,247,187,7,50,104,64,249,215,131,221,86,33,
125,120,94,81,5,112,248,63,174,189,65,16,252,77,88,149,185,14,184,2,24,147,144,224,92,196,156,220,186,17,120,2,88,111,89,86,239,41,180,113,107,16,4,119,133,225,227,139,192,69,152,213,223,147,210,198,78,
204,121,141,79,0,27,78,182,141,150,101,245,134,159,204,183,133,125,184,24,104,6,28,206,253,0,91,128,57,129,124,55,176,6,88,107,89,214,187,234,195,243,254,56,93,10,92,149,224,227,244,95,45,203,122,71,125,
152,140,215,154,242,97,96,223,247,173,240,26,223,247,173,98,177,104,21,139,69,10,133,130,159,205,102,15,108,223,190,253,15,171,87,175,222,181,109,219,54,11,104,46,20,139,189,0,227,27,199,1,111,115,244,
232,81,114,221,221,20,221,154,242,9,190,214,250,245,235,247,116,118,118,254,253,55,191,249,205,231,46,185,228,146,207,56,142,51,203,113,156,180,235,186,37,213,62,203,178,130,193,130,106,37,188,214,156,
87,25,71,79,129,136,136,72,197,191,143,151,172,3,29,22,120,92,6,246,244,173,1,106,129,6,96,60,208,20,94,154,223,250,229,215,191,213,221,209,193,234,167,158,98,74,107,43,159,189,252,114,246,247,142,205,
46,185,227,31,54,0,31,98,70,193,14,98,206,169,59,130,89,37,227,227,176,8,209,11,244,97,38,193,20,49,213,207,104,133,24,109,18,146,96,26,2,22,17,17,25,125,130,88,16,139,66,89,17,51,140,31,93,242,64,174,
253,227,212,71,213,117,117,184,206,192,186,178,187,143,166,58,203,194,92,50,151,253,19,5,64,17,17,145,243,52,232,69,215,229,95,199,131,91,17,83,165,243,195,235,124,20,4,55,191,219,179,23,192,243,60,179,
118,96,16,240,221,31,172,220,197,64,69,175,56,72,248,211,8,162,2,160,136,136,136,36,52,16,198,131,96,20,2,115,177,0,152,95,254,224,63,109,5,179,185,128,151,201,208,87,40,112,224,80,71,79,44,0,198,31,119,
48,10,131,10,128,34,34,34,146,128,16,24,5,182,120,240,11,24,168,2,70,33,176,47,95,48,19,65,170,171,171,233,232,232,224,232,209,163,80,90,253,43,31,74,86,8,84,0,20,17,17,145,4,6,192,120,16,12,98,225,175,
24,6,191,168,18,24,5,65,198,142,29,27,127,140,242,9,29,40,248,41,0,138,136,136,72,101,132,192,242,73,28,81,0,44,25,6,238,202,57,189,227,26,27,7,11,128,241,32,169,192,167,0,40,34,34,34,9,11,123,1,131,47,
191,18,133,191,2,3,85,192,146,74,224,222,143,171,14,77,108,110,230,195,163,31,210,213,213,197,61,183,223,48,189,236,255,176,40,93,114,166,252,123,162,0,40,34,34,34,9,9,134,67,77,6,201,199,2,97,254,183,
47,189,253,118,117,109,45,142,227,224,7,1,215,94,220,52,133,210,170,95,249,37,202,16,214,16,33,81,20,0,69,68,68,228,28,134,63,159,210,243,249,226,21,192,28,80,248,209,138,223,238,0,240,92,143,189,237,
237,240,209,206,250,65,194,159,29,187,12,22,244,20,254,20,0,69,68,68,36,65,162,0,24,31,2,46,31,10,38,149,74,97,15,108,221,22,133,62,39,22,250,236,178,175,69,1,80,68,68,68,18,32,96,232,225,223,232,92,192,
248,16,112,116,161,186,186,154,222,92,142,238,238,110,26,235,107,50,131,132,192,242,220,160,97,95,5,64,17,17,17,73,64,248,139,95,67,233,82,46,241,161,224,124,120,41,2,197,92,209,202,143,173,173,165,186,
170,138,32,8,248,254,242,111,204,167,180,218,87,94,9,28,238,92,64,73,56,87,79,129,136,136,200,168,8,126,214,9,190,31,95,216,57,79,233,34,209,133,131,93,85,71,198,141,107,108,137,146,226,180,186,190,6,
142,63,239,111,168,9,33,82,97,84,1,20,17,17,25,189,161,48,170,246,149,79,6,41,223,19,56,191,175,51,125,120,98,83,51,227,26,26,8,130,128,230,49,185,186,240,113,172,33,2,96,252,255,25,142,66,162,2,160,136,
136,136,156,3,241,32,24,77,254,40,57,7,240,129,135,30,255,125,245,216,177,76,108,110,166,161,190,14,207,46,58,148,14,29,203,40,162,33,96,17,17,145,209,171,124,95,224,242,69,161,163,243,0,115,219,223,222,
247,33,64,77,93,29,53,117,117,28,60,176,159,48,40,14,182,208,180,2,97,133,83,5,80,68,68,100,116,6,191,120,72,139,111,9,23,45,5,83,18,0,195,75,191,230,150,73,80,186,123,136,207,224,179,139,227,255,231,
80,191,139,40,0,138,136,136,200,39,20,250,24,36,148,13,118,14,96,124,8,56,10,127,125,131,60,102,60,32,230,99,65,208,31,36,16,42,236,41,0,138,136,136,72,2,3,162,79,233,240,111,95,120,233,5,122,243,69,43,
31,221,249,64,87,213,65,160,39,252,94,46,22,4,11,195,4,64,81,0,20,17,17,145,115,28,248,160,116,248,55,94,13,140,170,123,189,97,208,235,238,200,87,31,140,126,248,111,31,222,240,27,160,27,232,10,191,31,
175,2,22,98,65,80,33,80,1,80,68,68,68,18,20,254,6,219,13,36,190,253,91,60,0,118,117,20,235,247,70,15,240,204,198,29,111,3,157,177,0,24,85,3,251,24,24,10,46,114,252,144,179,38,136,40,0,138,136,136,72,66,
2,97,249,249,127,249,88,176,235,6,186,158,252,183,141,235,0,254,230,31,119,254,29,112,12,232,8,67,96,103,120,191,248,249,128,81,245,175,168,224,87,121,28,61,5,34,34,34,163,138,21,187,142,118,8,137,47,
222,28,223,217,35,190,191,111,176,249,245,247,15,95,181,248,106,231,191,253,239,213,207,98,42,125,221,12,12,3,119,133,95,247,81,182,141,28,199,79,4,209,112,112,133,28,36,34,34,34,50,250,222,219,173,65,
194,158,135,89,7,56,5,164,129,12,80,21,94,103,194,219,162,69,160,11,97,224,139,87,10,163,0,24,77,8,41,80,90,9,212,172,224,10,160,133,160,69,68,68,70,183,242,202,92,49,12,132,5,6,42,131,209,237,5,204,121,
126,118,236,182,40,236,245,198,66,95,121,245,207,47,251,63,68,1,80,68,68,68,206,114,224,179,202,194,159,53,72,0,140,223,39,90,30,38,135,169,254,69,195,194,197,88,8,140,38,127,104,41,24,5,64,17,17,17,169,
144,80,72,24,216,236,48,200,197,191,23,13,247,230,195,0,104,197,126,38,190,228,75,62,246,245,137,170,127,10,132,10,128,34,34,34,114,150,3,159,53,68,16,43,15,109,81,37,207,97,96,114,104,252,103,227,187,
127,148,47,255,162,115,253,20,0,69,68,68,36,193,129,48,18,85,1,203,67,96,145,129,9,35,148,221,191,60,8,6,156,218,190,192,146,16,154,5,44,34,34,114,254,188,207,219,177,219,203,191,182,202,46,193,48,151,
242,97,95,133,63,5,64,17,17,17,169,144,16,88,254,239,193,114,65,249,48,239,112,225,79,1,80,1,80,68,68,68,18,250,126,31,15,123,214,9,2,96,60,244,149,7,66,133,63,5,64,17,17,17,169,176,247,252,242,208,55,
84,46,40,31,226,13,78,112,31,81,0,20,17,17,145,132,191,239,91,195,124,255,68,51,125,21,252,20,0,69,68,68,228,60,122,255,87,248,83,0,20,17,17,145,243,32,7,40,244,41,0,138,136,136,200,121,146,7,20,252,68,
68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,
68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,
68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,
68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,47,102,233,85,0,0,0,39,73,68,65,84,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,
68,68,68,68,68,68,68,68,68,68,68,70,157,255,15,200,206,108,201,86,21,47,209,0,0,0,0,73,69,78,68,174,66,96,130,0,0};

const char* UiEditorAbout::b_logo_png = (const char*) resource_UiEditorAbout_b_logo_png;
const int UiEditorAbout::b_logo_pngSize = 49419;

// JUCER_RESOURCE: vst_logo_100x_png, 7586, "../Images/vst_logo_100x.png"
static const unsigned char resource_UiEditorAbout_vst_logo_100x_png[] = { 137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,0,100,0,0,0,58,8,6,0,0,0,70,102,252,211,0,0,0,6,98,75,71,68,0,255,0,255,0,255,
160,189,167,147,0,0,0,9,112,72,89,115,0,0,11,19,0,0,11,19,1,0,154,156,24,0,0,0,7,116,73,77,69,7,221,12,17,8,40,18,239,214,246,240,0,0,29,47,73,68,65,84,120,218,237,124,119,120,92,197,189,246,59,115,230,
148,45,146,44,89,178,44,185,91,198,116,12,152,216,198,190,198,38,166,36,132,123,115,129,16,18,146,56,4,18,46,229,33,95,42,45,16,146,75,62,190,75,117,128,0,54,6,28,122,18,115,109,99,140,59,198,13,87,108,
185,75,178,181,234,171,94,183,158,58,243,253,113,118,87,171,230,142,125,239,243,100,30,157,103,143,118,247,204,153,153,119,126,191,223,251,123,103,246,16,0,184,230,154,111,228,15,206,201,249,77,126,126,
254,183,101,89,206,194,73,21,1,128,156,129,107,78,229,186,179,81,63,1,192,251,173,143,115,30,107,107,111,223,84,93,89,245,220,134,77,235,246,1,0,155,53,235,250,194,9,19,38,172,159,114,229,148,115,98,177,
24,162,145,40,254,87,23,146,24,207,255,5,245,50,153,97,208,160,65,163,43,43,42,111,80,53,237,174,213,107,150,127,204,242,135,12,121,252,202,105,83,207,89,244,209,71,216,184,97,99,151,105,89,135,0,232,
221,136,138,180,214,144,4,222,98,192,249,211,61,183,72,226,85,184,253,32,36,209,161,180,217,71,0,8,49,96,175,251,206,173,244,54,245,30,47,146,120,183,191,250,250,27,205,163,125,54,16,34,253,89,79,127,
117,144,94,223,19,253,214,35,73,18,174,152,120,69,230,173,223,189,117,226,249,23,94,48,183,164,180,180,133,21,20,22,220,210,217,209,129,117,235,62,239,224,156,255,95,33,196,7,156,115,3,160,73,195,234,
117,3,2,2,14,126,76,3,165,9,40,92,240,4,165,238,7,224,112,235,22,199,4,36,189,190,163,1,226,94,149,222,222,100,161,105,247,227,167,8,72,239,241,72,7,164,119,253,36,237,125,244,243,153,219,43,93,215,81,
92,92,60,98,242,149,147,95,203,203,205,189,50,43,43,243,167,76,85,181,204,174,174,46,152,166,117,128,201,108,65,75,115,125,59,254,89,206,88,201,244,103,218,18,149,42,37,38,93,41,132,184,129,118,251,20,
97,56,182,173,255,115,136,206,108,161,52,101,70,16,66,248,105,183,37,17,16,73,34,255,211,59,32,132,56,233,235,250,187,182,188,190,181,207,123,14,231,103,18,146,158,129,62,173,197,192,25,109,200,177,75,
75,71,8,121,217,153,169,1,109,237,8,123,55,23,31,212,86,127,177,75,27,62,52,119,140,79,83,199,128,144,2,195,180,178,108,219,241,130,64,161,148,152,170,172,152,154,34,119,113,33,90,109,199,9,70,98,122,
101,113,105,69,123,94,118,150,37,132,48,1,152,0,44,66,136,24,87,152,139,93,71,106,207,203,207,206,252,57,161,52,171,48,219,255,10,33,100,203,153,235,37,239,17,29,217,87,195,17,79,221,10,222,250,120,45,
242,178,51,33,132,192,214,125,165,231,174,221,186,231,98,8,126,125,36,30,159,110,90,246,185,117,77,45,8,133,163,232,232,10,193,208,13,216,182,13,193,57,64,8,40,165,80,20,5,217,131,50,145,55,56,27,217,
89,25,240,104,154,19,211,245,146,182,174,112,137,44,75,165,66,144,178,61,135,171,131,150,195,149,142,112,244,137,80,220,152,42,203,50,10,179,253,171,0,108,57,227,125,238,6,132,124,165,244,253,68,203,202,
45,197,32,196,109,211,214,253,165,99,23,175,219,250,3,195,48,191,23,141,197,47,232,232,10,131,16,32,174,235,168,12,84,161,174,38,136,166,166,102,132,58,67,136,199,117,112,199,1,8,129,44,203,240,122,61,
200,204,202,196,224,188,193,200,31,58,4,35,71,143,148,134,230,231,93,68,37,233,34,191,207,139,65,153,126,120,53,13,142,0,108,1,200,92,128,18,10,0,206,217,74,159,122,186,172,255,1,229,237,101,235,241,141,
169,151,1,0,22,173,219,250,205,195,149,193,199,116,221,152,26,139,199,97,89,22,36,73,66,125,125,35,214,174,90,135,192,225,10,68,90,219,183,67,136,18,16,210,0,66,66,137,193,84,1,100,1,40,0,196,57,32,116,
130,150,225,87,243,134,230,225,156,115,199,225,170,171,255,5,138,60,20,141,45,237,80,20,5,170,170,66,83,85,151,168,83,114,22,128,32,3,196,144,179,108,33,115,222,89,130,31,223,56,19,0,240,215,165,235,190,
211,222,21,153,99,232,250,112,211,52,97,89,150,235,109,29,7,219,55,111,199,222,109,187,230,66,224,13,168,74,35,128,48,0,3,128,5,64,128,131,130,66,6,160,1,240,65,32,91,143,197,38,213,6,170,238,11,214,4,
39,22,239,220,131,153,215,94,133,111,220,112,29,28,219,134,69,41,40,37,32,137,215,51,53,12,66,8,16,66,82,41,182,232,15,16,89,146,78,251,141,35,186,1,159,170,164,220,80,73,93,11,198,23,230,66,234,53,27,
127,57,251,223,1,0,243,23,173,158,110,217,246,75,134,97,20,152,134,1,211,178,92,194,65,8,84,73,138,93,123,245,180,7,54,175,120,239,109,0,14,172,126,111,233,36,14,29,64,39,128,32,124,69,135,0,242,14,183,
237,235,99,209,216,43,27,63,219,60,170,173,185,13,223,251,225,173,32,212,181,12,74,41,168,68,1,192,43,132,80,19,150,246,85,121,167,48,33,132,167,187,170,62,46,75,0,104,106,10,90,7,42,155,46,81,25,185,
69,162,68,3,33,32,32,160,132,0,4,32,132,192,61,37,137,243,196,255,105,175,52,241,62,165,132,169,178,244,185,87,85,150,165,154,226,43,194,249,195,243,0,0,109,225,216,12,153,177,27,210,39,141,110,152,90,
77,67,211,245,142,195,11,28,199,129,109,219,169,15,163,177,56,186,194,97,231,150,111,206,236,124,226,193,123,157,244,89,118,28,17,147,35,86,206,1,124,218,208,162,191,89,211,208,132,35,129,106,236,47,57,
130,172,236,44,228,228,228,64,146,28,200,182,131,15,150,173,159,95,86,213,56,127,112,238,96,12,202,204,64,118,150,31,170,44,67,86,36,40,178,12,153,73,238,33,75,80,152,4,16,146,162,211,233,109,17,3,88,
69,134,166,64,97,210,249,0,74,211,191,215,199,66,136,203,191,242,126,249,251,57,191,42,24,62,236,199,170,166,193,163,121,224,207,244,129,73,18,36,201,109,72,242,85,102,12,146,68,193,18,13,100,76,130,17,
143,195,113,108,16,2,248,61,10,70,14,205,141,3,232,6,36,26,72,220,108,216,240,121,239,46,250,195,69,151,92,56,147,128,128,201,12,25,126,63,100,69,6,97,26,136,76,32,3,16,150,13,219,118,64,32,224,165,12,
213,193,134,140,234,96,227,125,66,136,35,0,14,38,103,217,49,193,137,5,146,121,241,226,80,36,154,15,16,196,77,11,237,157,33,212,4,27,240,181,137,151,130,49,9,182,109,99,223,129,50,172,221,82,140,236,156,
28,100,101,102,224,138,43,46,69,222,224,28,168,50,131,170,42,80,85,6,143,34,67,211,100,168,50,131,34,203,216,185,115,55,28,33,144,153,145,1,69,149,161,170,42,124,94,47,50,50,51,92,145,36,145,78,136,132,
90,228,85,228,62,180,55,21,67,72,55,34,22,245,141,153,177,102,201,162,127,215,60,26,124,25,25,24,146,63,20,23,79,188,28,231,95,124,49,152,68,65,9,129,148,244,185,128,107,234,9,139,241,123,20,188,252,236,
28,52,6,235,17,141,197,96,234,70,83,76,55,214,247,59,88,94,109,230,31,30,123,106,102,70,134,31,62,191,15,131,115,115,48,105,202,36,220,125,207,143,193,29,14,206,57,170,131,77,40,175,172,67,56,28,129,202,
8,188,170,4,219,177,197,145,234,250,89,170,166,45,202,205,206,122,61,22,55,190,240,104,74,25,33,164,173,199,236,28,16,28,117,180,224,2,67,6,103,99,244,136,66,132,34,81,124,242,233,26,236,221,119,0,211,
166,77,1,149,36,28,62,176,223,222,245,201,146,40,64,76,248,252,254,145,133,143,122,242,6,231,36,124,138,72,252,9,112,238,14,112,150,223,139,63,62,254,167,182,96,89,137,4,40,94,54,104,144,82,48,172,0,231,
157,119,14,166,76,155,140,203,39,78,192,152,49,163,96,26,102,202,14,142,150,220,166,199,16,38,73,98,23,55,237,95,234,102,104,184,222,217,89,208,86,83,51,185,188,180,228,114,253,230,155,49,249,95,166,117,
103,188,92,64,208,228,43,224,8,14,191,166,32,83,161,235,119,28,60,180,1,178,172,3,104,1,23,37,189,77,57,81,182,153,177,216,195,109,225,176,220,38,68,86,77,137,24,121,96,255,161,91,239,189,255,46,2,97,
163,170,166,30,91,119,236,133,105,153,80,152,4,213,175,129,11,10,77,83,137,3,160,178,190,121,156,45,240,140,205,69,131,223,235,221,17,138,25,187,124,170,188,157,82,178,131,16,210,57,32,56,132,217,137,
142,162,112,72,46,150,175,92,135,93,91,118,160,120,27,197,145,146,35,240,120,52,196,195,161,59,33,43,49,16,98,105,62,223,207,1,204,226,66,128,115,14,206,5,184,16,224,194,173,151,11,1,195,52,241,245,25,
211,30,121,183,188,166,21,170,156,101,199,245,220,218,178,242,209,181,135,202,174,88,179,116,197,228,75,38,95,129,31,223,249,3,92,123,221,213,136,199,226,125,84,242,62,44,43,133,149,32,210,96,45,90,221,
24,106,41,75,248,123,21,192,24,43,22,123,100,221,242,229,179,243,242,243,49,254,252,243,18,18,132,59,59,68,26,218,205,157,81,188,242,234,179,133,227,63,121,251,73,66,136,147,30,55,82,174,202,55,206,157,
37,209,64,57,128,167,1,160,232,252,235,72,160,100,181,118,219,15,238,250,87,137,16,79,56,22,71,117,117,13,178,252,10,84,213,235,106,163,137,184,228,209,60,200,244,251,145,149,145,1,66,36,24,182,40,208,
184,248,182,3,124,91,119,68,131,36,16,52,29,126,136,81,178,158,0,27,8,33,21,61,38,131,232,6,105,207,222,131,120,229,165,249,229,225,166,230,87,33,43,215,55,215,212,141,131,16,33,216,117,239,118,235,76,
57,55,91,182,13,193,147,22,225,202,47,46,56,9,128,184,131,119,230,61,189,230,221,215,159,169,66,44,113,161,167,72,129,130,66,64,92,177,111,231,238,103,158,105,108,26,163,40,10,174,186,106,106,50,214,144,
222,177,166,159,160,46,96,243,52,154,21,13,24,0,74,225,29,251,68,164,173,109,244,186,21,43,174,202,203,207,71,78,78,118,66,141,228,16,130,186,128,8,1,203,118,176,191,178,121,252,136,33,217,111,2,184,195,
182,29,48,38,117,131,1,0,209,114,164,3,85,29,41,199,40,66,196,77,63,125,232,154,187,239,190,195,211,21,10,97,239,222,253,176,45,3,30,77,238,49,115,100,198,224,245,104,240,122,53,248,125,30,100,102,120,
49,200,239,135,223,171,129,49,6,2,20,112,160,64,8,76,180,108,126,179,105,218,177,142,112,172,65,83,216,42,77,145,63,33,132,108,6,98,146,16,2,150,101,227,133,57,243,142,132,27,246,220,160,101,157,87,161,
91,214,2,48,73,1,192,209,205,35,100,206,57,149,18,65,155,115,14,39,1,130,224,0,23,194,85,6,220,17,117,27,235,45,114,227,85,60,96,2,168,2,80,5,95,209,142,166,186,134,101,239,253,245,131,139,47,190,228,
66,20,230,14,2,239,103,125,68,244,171,108,245,27,16,43,170,192,216,147,149,251,246,181,238,252,226,11,152,166,153,146,189,82,150,226,154,10,116,211,196,214,146,154,31,9,33,190,195,152,116,116,33,48,26,
192,40,119,162,168,179,103,127,119,158,199,163,225,208,129,82,252,234,255,60,140,61,197,251,64,41,237,209,100,69,113,131,165,71,85,225,245,104,240,123,52,100,248,60,144,93,48,186,253,187,0,33,160,126,
198,216,144,176,97,77,40,171,107,254,237,206,146,138,77,165,213,245,45,243,223,91,112,81,118,150,15,109,237,237,198,150,53,31,222,15,160,92,239,42,229,136,5,58,17,13,52,35,26,104,133,175,40,157,22,193,
180,109,112,206,83,214,33,4,119,221,22,23,112,146,66,121,31,242,144,240,12,46,9,175,129,109,205,46,47,175,16,197,187,246,66,98,236,168,185,14,77,247,101,188,55,62,201,74,163,129,181,80,148,151,63,251,
248,99,167,186,178,50,173,113,34,205,109,9,8,16,52,119,132,233,161,154,230,23,133,16,5,132,16,232,166,221,231,166,35,46,191,62,117,254,210,251,159,188,54,172,96,232,208,72,36,34,254,242,226,107,7,205,
246,174,21,127,127,119,33,86,175,90,135,72,36,234,198,0,74,33,203,50,152,204,92,96,20,5,154,170,186,22,216,71,124,112,139,68,41,60,170,10,85,150,137,97,217,56,20,168,201,37,30,175,252,238,226,85,168,109,
108,146,15,150,87,63,222,218,222,117,71,93,99,203,80,33,132,146,194,32,82,222,167,30,158,136,23,156,195,181,16,193,83,177,212,225,98,192,9,7,0,208,3,128,162,84,180,183,182,191,247,135,199,254,132,201,
83,174,63,114,201,165,179,34,3,177,44,154,206,156,73,111,25,39,26,72,129,66,132,244,60,132,88,253,183,183,22,160,171,163,195,93,146,5,79,129,226,6,58,215,132,143,212,182,20,52,118,132,95,20,66,72,154,
194,250,88,74,237,238,85,0,128,95,60,249,242,191,93,58,225,194,239,72,18,37,11,255,190,168,109,223,150,165,223,149,253,25,119,8,206,23,174,94,248,137,254,218,75,111,96,231,246,98,52,55,183,192,113,56,
52,69,5,99,50,152,68,33,39,193,32,3,167,95,178,68,33,73,52,65,213,25,36,73,130,105,89,216,87,26,160,75,63,251,98,250,146,207,54,47,8,212,212,31,58,88,94,245,68,76,215,39,244,38,32,18,99,112,82,214,1,112,
225,186,44,135,39,44,196,17,189,86,60,251,47,18,99,97,33,196,7,93,109,29,27,90,131,13,171,66,173,173,177,129,38,18,237,95,226,234,5,138,183,8,34,126,36,74,100,249,193,112,115,115,237,194,247,223,135,109,
59,16,130,116,179,174,132,239,18,0,76,219,33,165,181,45,223,138,196,141,159,38,59,153,4,101,246,175,158,4,0,204,250,222,125,133,51,175,154,250,104,134,223,159,177,125,235,14,188,250,252,107,79,1,56,100,
133,74,155,193,201,108,120,180,159,183,4,235,63,251,104,193,7,206,155,115,223,198,71,255,88,130,141,155,182,160,46,88,15,198,100,104,154,2,89,26,0,15,146,242,96,169,5,83,145,150,7,184,121,21,69,107,71,
8,155,118,237,207,222,182,167,228,209,29,251,15,47,171,107,106,251,141,16,194,219,71,32,231,233,44,139,167,24,150,72,48,174,163,22,95,17,156,208,97,129,104,96,37,244,202,153,48,170,31,128,81,221,222,195,
53,246,199,178,4,8,40,142,146,88,249,138,32,34,229,7,224,43,250,117,89,241,158,127,172,252,228,19,220,122,251,247,97,91,38,4,186,153,23,79,80,226,206,176,238,173,104,236,248,181,16,98,43,33,100,95,56,
106,32,115,212,36,188,243,194,227,0,32,125,255,182,155,239,29,50,36,111,82,107,91,43,94,249,203,27,43,97,86,207,73,11,140,58,128,249,240,21,125,10,198,166,182,53,52,221,176,118,233,202,27,55,125,254,69,
222,152,177,163,112,193,5,227,49,125,218,36,204,152,62,5,151,157,63,54,101,248,22,119,45,53,233,161,109,199,73,29,238,76,119,253,127,55,139,34,80,40,67,123,87,24,251,15,87,14,15,199,140,103,29,46,46,21,
66,252,140,16,98,128,32,21,200,83,64,36,172,35,89,151,16,199,88,67,74,39,53,253,190,47,6,22,23,143,75,87,139,6,22,194,87,244,236,23,159,173,251,237,232,177,99,48,121,234,149,112,108,59,1,72,50,174,8,216,
142,131,134,182,208,57,217,126,207,67,66,136,123,8,33,225,100,21,79,205,251,240,202,194,130,252,251,179,6,101,144,57,207,190,20,57,184,247,224,189,189,3,227,189,191,248,61,94,251,243,127,214,3,248,8,222,
162,213,96,120,198,136,197,175,40,221,119,232,214,210,3,165,55,174,90,245,57,29,156,147,141,161,249,121,152,58,109,18,174,157,53,29,51,166,79,130,143,81,8,0,113,75,32,166,155,48,76,11,166,101,193,178,
44,88,166,213,47,209,144,36,10,74,41,154,219,59,177,175,188,250,246,204,12,111,4,192,61,130,11,55,182,10,14,206,105,143,224,206,57,18,116,248,84,181,72,122,52,64,232,209,145,78,210,58,224,119,122,52,58,
99,197,162,37,147,70,142,30,141,161,67,243,221,25,3,10,41,109,35,73,84,183,80,223,22,190,221,239,81,86,10,33,222,39,132,240,7,159,126,61,187,176,96,232,227,35,134,23,102,47,249,239,101,56,112,160,228,
62,196,42,170,170,155,59,10,114,124,218,125,126,175,246,37,128,237,132,144,198,52,144,66,0,66,240,21,29,134,68,63,2,132,55,26,138,204,140,134,35,55,213,84,215,125,107,119,241,190,236,185,115,255,10,143,
215,131,41,147,39,226,134,111,204,194,140,171,167,34,35,35,3,134,105,67,215,45,24,134,11,78,191,67,66,40,40,113,99,77,52,110,144,3,129,218,111,233,145,200,213,222,225,95,51,45,219,114,7,61,97,121,233,
73,162,35,248,105,144,134,197,41,172,135,36,105,93,52,96,193,59,246,246,250,234,234,125,203,23,47,241,254,240,167,63,129,166,40,110,12,73,203,228,9,1,26,218,67,24,156,229,153,175,202,108,35,180,113,181,
94,159,231,214,113,227,198,94,23,172,171,199,250,207,54,46,41,217,241,233,82,192,235,127,232,247,207,252,241,218,235,191,254,51,34,56,46,44,26,185,92,8,113,39,33,164,169,185,171,11,67,178,178,146,247,
229,240,21,233,136,86,232,0,22,37,14,216,190,162,9,182,237,220,172,235,198,77,43,62,93,123,206,138,101,171,25,132,144,198,94,48,158,124,253,235,87,225,178,203,39,64,98,18,76,203,236,27,110,8,1,149,40,
40,147,92,197,151,82,196,13,59,183,190,51,50,157,27,166,37,81,6,33,220,28,196,17,220,181,10,145,100,90,20,142,195,79,11,32,253,152,132,0,112,156,149,251,138,64,40,173,128,16,247,124,185,101,43,182,109,
218,146,162,134,73,214,5,184,231,148,82,28,9,182,169,49,195,122,251,169,57,127,24,127,225,5,231,189,204,152,132,21,203,215,52,175,89,245,217,127,1,232,130,146,123,105,105,89,249,207,52,175,71,132,99,113,
52,180,180,127,179,186,190,105,50,128,110,48,250,243,201,221,180,124,47,162,129,39,16,13,92,2,74,70,65,146,238,2,99,11,43,74,142,84,189,49,103,110,199,253,119,62,32,230,60,247,10,2,129,74,56,142,211,11,
16,215,50,164,4,24,174,20,79,148,104,220,204,130,224,194,118,236,20,181,77,198,143,20,211,74,202,21,167,97,173,240,248,19,195,1,220,151,136,148,11,42,201,139,156,104,244,141,149,31,47,69,77,85,117,138,
217,136,148,222,227,158,59,92,160,188,190,109,198,196,203,47,93,89,80,48,84,217,83,188,143,175,93,189,238,101,196,42,182,39,90,227,72,148,66,162,18,81,20,5,117,77,173,164,185,173,243,81,33,68,193,81,197,
184,116,112,188,69,64,70,17,18,9,222,59,136,6,110,3,149,206,135,166,221,5,73,122,163,108,207,254,210,185,47,204,195,166,13,91,65,210,200,62,75,208,98,150,80,178,37,198,64,168,20,19,16,53,144,220,85,27,
193,5,28,39,65,10,146,217,186,112,51,246,147,221,5,115,116,218,43,144,200,43,78,96,9,211,91,4,30,61,18,37,154,246,116,91,117,117,241,146,191,47,132,97,24,61,181,174,132,197,16,0,157,17,29,76,243,142,10,
133,194,88,190,108,213,230,131,219,150,205,235,209,44,74,18,50,62,131,35,4,14,150,87,79,174,12,54,254,73,8,65,211,105,243,81,221,105,56,208,251,61,29,177,192,98,196,42,238,134,170,222,2,130,5,203,23,127,
138,198,198,102,80,74,33,81,234,230,53,137,28,69,98,12,140,49,24,166,217,241,246,130,15,119,200,154,198,146,121,136,27,208,19,253,226,73,41,69,244,96,109,167,207,101,157,194,14,7,17,41,47,135,166,253,
241,224,206,47,59,151,45,94,10,137,177,180,61,80,137,220,36,177,167,151,115,142,141,159,111,12,45,125,247,221,39,1,180,228,142,155,220,77,186,9,129,36,49,200,140,65,85,85,116,132,34,216,252,229,254,59,
91,218,59,223,232,157,203,156,80,73,186,181,72,249,33,166,40,247,192,118,118,212,215,54,184,107,57,137,236,159,201,44,5,6,165,20,243,94,121,179,249,249,167,30,254,146,49,73,6,72,66,183,18,238,210,64,202,
53,35,21,79,78,255,46,173,212,82,178,56,177,0,159,236,108,172,226,99,72,236,205,21,75,62,118,118,127,185,187,7,40,73,238,46,0,180,181,180,138,151,95,120,229,109,160,125,45,0,180,166,109,82,35,132,66,86,
220,193,145,101,25,154,166,161,173,43,130,69,107,54,255,184,188,58,184,81,8,81,148,204,162,79,8,152,132,91,187,245,39,191,132,221,85,102,130,73,235,199,141,31,11,66,92,64,100,217,181,16,69,81,224,241,
104,120,230,255,205,225,31,47,92,242,98,98,223,22,113,92,126,11,14,145,82,35,146,66,163,211,157,131,144,211,238,178,200,241,135,244,126,165,21,196,43,126,3,206,247,206,255,243,203,232,232,232,76,204,232,
36,5,230,144,101,25,207,60,245,92,77,180,121,255,47,122,40,163,105,73,154,44,203,80,152,2,69,150,19,98,162,2,221,48,233,210,117,91,166,175,221,178,107,87,36,22,127,82,8,145,117,34,192,36,191,179,112,129,
155,119,254,238,79,143,204,202,201,201,118,239,149,0,68,83,53,24,134,137,95,255,252,33,108,88,253,249,155,208,171,222,5,192,252,153,89,80,100,57,33,149,240,148,155,18,232,86,85,163,113,19,0,166,15,116,
223,19,45,61,214,212,233,73,6,120,248,198,185,210,58,33,55,69,35,145,131,175,190,240,103,255,239,158,124,2,0,129,128,0,99,50,150,44,92,132,221,235,215,220,14,128,247,88,35,73,229,2,46,32,76,97,224,9,129,
154,184,11,245,176,76,19,187,15,29,201,58,92,85,247,216,5,227,70,255,170,182,161,249,111,148,210,247,138,15,29,217,87,215,212,106,14,27,50,216,78,204,39,142,52,197,36,18,211,165,47,15,28,150,182,236,62,
168,90,182,61,243,80,160,250,89,195,178,199,200,138,12,85,81,33,203,174,106,190,109,219,78,204,127,245,45,206,168,180,80,196,42,30,62,16,8,94,214,208,210,254,181,207,191,44,189,194,226,72,37,132,73,23,
156,100,89,66,0,49,195,68,89,93,203,107,113,211,202,214,77,123,157,97,59,45,113,211,54,117,203,137,8,33,162,199,181,230,223,127,98,120,10,86,23,45,79,46,68,213,192,87,116,119,217,129,67,31,44,254,199,
127,227,187,183,223,6,69,81,80,81,30,192,187,11,222,127,30,232,218,210,31,24,16,0,165,20,170,170,64,211,52,56,182,131,214,150,6,132,67,97,112,33,32,81,10,89,102,136,234,6,118,30,40,243,238,62,120,228,
206,194,252,220,59,115,179,51,141,152,97,22,55,183,117,28,150,40,109,224,92,116,113,193,173,196,250,132,63,26,55,242,195,209,216,184,80,36,246,181,246,206,144,23,132,128,201,50,12,195,68,103,71,23,234,
106,235,177,110,237,6,81,182,107,79,32,123,196,200,13,207,188,244,220,93,127,249,199,186,219,66,49,29,173,157,97,88,54,135,87,83,82,132,71,128,0,84,2,165,46,35,163,148,66,102,12,85,77,33,185,53,98,60,
59,56,211,11,85,97,0,33,8,199,226,127,230,140,60,152,216,158,116,220,65,157,29,83,92,60,81,247,21,13,124,232,104,163,167,172,249,116,197,207,243,242,243,80,80,48,20,159,46,90,90,108,196,245,63,14,168,
237,16,128,59,28,122,76,135,169,27,216,190,117,39,222,127,231,111,104,106,108,134,230,209,48,104,80,22,242,135,14,65,222,144,92,12,202,206,130,215,235,69,153,166,66,85,21,85,85,213,41,178,44,79,81,21,
5,138,34,131,0,176,28,27,186,97,194,182,236,148,100,98,154,38,98,145,56,90,219,219,209,24,108,64,85,101,13,58,107,131,197,160,100,53,128,133,150,105,204,127,117,238,91,32,32,137,188,196,29,11,198,36,48,
201,61,100,89,134,170,200,174,122,44,75,144,21,217,221,228,33,73,80,85,37,165,66,75,146,4,85,66,185,143,157,120,20,72,219,117,34,122,47,183,156,2,85,144,158,236,106,239,152,240,215,185,111,204,208,52,
15,239,104,109,251,45,98,129,112,191,214,145,232,117,201,129,18,60,250,224,19,176,44,11,77,141,45,159,55,4,170,222,129,204,172,152,97,100,199,58,58,207,169,15,84,157,15,33,198,67,102,163,84,159,23,154,
71,131,170,170,80,20,25,76,150,33,81,154,98,98,174,84,238,192,177,29,88,150,5,67,55,161,235,58,226,225,72,35,76,243,16,64,138,65,233,151,240,122,138,17,171,40,163,25,227,125,145,206,206,208,238,213,171,
74,250,9,66,125,207,19,251,196,64,9,32,72,82,16,75,202,201,46,162,241,240,38,160,213,57,209,160,126,122,183,146,38,6,219,59,216,223,26,107,11,223,21,15,133,175,142,183,119,86,193,182,55,29,85,249,164,
180,178,163,181,237,31,219,214,55,57,0,186,192,249,27,112,130,187,82,203,51,190,34,47,128,76,0,153,224,194,103,68,99,121,70,36,54,60,177,93,52,7,64,70,98,167,162,4,119,103,187,9,32,10,129,78,0,45,128,
168,5,72,19,36,26,134,199,211,5,160,3,209,128,158,92,174,229,220,137,129,144,217,80,213,19,27,143,126,193,74,164,244,138,183,14,230,137,231,33,167,127,43,169,175,8,177,218,189,128,175,40,0,73,170,132,
36,9,216,181,162,55,171,234,85,234,65,233,29,80,148,148,146,142,104,26,19,139,6,98,0,98,0,92,193,113,112,17,160,131,38,0,32,105,71,122,87,68,74,15,18,224,136,5,250,118,175,123,211,133,0,80,115,218,247,
40,14,228,17,142,7,144,147,102,89,3,201,25,238,43,239,119,189,185,239,53,2,64,124,224,13,110,189,74,91,170,238,83,83,246,162,229,248,74,203,49,193,232,171,94,209,94,139,108,255,44,103,184,244,54,109,250,
207,33,57,187,165,55,149,162,233,46,235,76,255,58,162,30,99,79,71,29,110,179,231,78,58,249,230,255,235,208,179,108,35,95,21,203,58,65,48,10,81,145,60,255,133,128,49,75,32,226,28,255,204,34,52,3,131,143,
12,66,224,215,195,134,141,34,193,123,118,8,58,111,202,245,220,138,253,4,86,220,115,76,15,76,64,16,33,187,178,31,59,252,116,199,39,141,6,110,46,4,22,213,159,21,27,57,235,128,244,2,227,47,128,184,67,251,
246,53,62,255,35,255,1,97,218,199,142,102,132,64,18,54,62,154,249,131,48,70,142,94,18,172,170,218,4,0,60,222,62,246,71,23,127,239,223,126,56,238,122,15,163,236,168,115,50,230,24,152,191,119,209,141,31,
223,27,31,135,165,245,15,96,81,125,215,217,177,143,158,187,123,217,217,2,163,30,99,51,0,188,9,224,22,128,80,227,147,205,48,150,111,29,112,0,105,47,140,100,16,4,169,237,247,113,117,124,20,112,243,28,109,
16,127,191,124,181,243,97,96,77,159,77,204,253,249,110,46,4,197,69,249,63,130,164,141,68,48,122,27,22,215,55,97,214,96,224,179,182,51,106,31,226,108,0,18,196,24,12,67,101,18,140,177,0,230,2,184,54,245,
5,46,0,110,247,11,198,167,36,34,94,202,226,33,143,16,238,15,117,40,97,2,160,81,10,225,101,16,105,143,203,145,184,224,56,161,141,32,18,5,38,228,204,0,35,219,240,189,225,223,196,223,234,74,1,0,215,229,1,
171,91,206,176,195,2,24,231,220,97,50,3,161,84,196,227,198,87,246,67,245,97,168,76,90,200,149,0,94,5,112,233,241,94,43,131,24,251,114,50,31,70,69,197,92,0,192,107,147,110,186,98,232,37,23,103,83,70,242,
32,134,129,144,199,133,128,85,220,90,122,101,216,138,42,39,76,79,28,1,92,148,51,26,94,182,11,63,28,117,43,222,171,94,137,213,45,103,228,71,251,132,0,92,112,175,36,36,8,206,9,235,104,107,223,115,217,196,
203,166,157,123,206,120,223,150,173,27,51,251,77,208,78,159,187,250,62,128,231,93,201,227,248,137,157,0,136,228,112,37,21,241,137,115,235,185,89,133,223,247,72,74,247,166,56,193,81,23,105,68,216,140,158,
28,93,180,57,48,38,195,11,31,91,138,255,40,122,8,243,2,115,1,124,229,207,170,58,255,188,243,166,13,202,202,154,90,95,95,143,184,174,135,88,48,24,252,207,250,186,250,85,247,63,112,255,132,27,110,188,225,
77,219,178,155,136,251,227,194,254,237,235,68,59,75,41,172,150,22,92,248,230,98,153,68,113,179,0,188,39,41,45,167,125,95,50,151,84,172,231,132,144,30,155,197,77,110,37,164,242,147,44,142,0,114,53,9,154,
244,95,158,95,95,50,243,22,49,165,233,220,172,49,180,199,179,143,78,229,153,107,105,189,16,66,128,49,166,14,27,54,108,138,16,124,200,166,77,155,161,235,250,114,182,117,251,214,207,52,143,118,247,240,17,
35,94,47,42,42,250,150,170,170,3,175,118,157,76,58,79,41,248,160,44,176,236,76,104,209,8,226,167,73,15,136,218,241,99,114,250,147,118,234,25,140,13,202,205,186,113,180,60,10,5,153,67,211,151,106,79,94,
210,232,231,201,82,66,112,84,84,84,96,195,134,13,8,4,2,173,132,144,183,88,91,91,179,179,117,219,182,5,254,3,7,154,132,16,47,0,40,58,90,91,79,182,203,28,113,108,81,35,120,196,200,128,115,194,125,34,253,
59,223,163,70,201,227,109,109,175,239,17,64,250,178,11,98,85,19,254,174,188,215,231,231,120,167,43,129,118,247,125,8,88,150,5,219,178,182,10,33,126,211,208,80,187,133,13,27,54,10,193,96,181,13,96,41,128,
165,133,133,35,125,132,16,79,234,9,112,164,87,39,123,252,68,76,244,63,80,201,235,56,122,108,63,223,148,169,178,217,45,214,139,185,96,223,149,78,168,91,189,238,99,57,28,186,195,33,146,55,75,180,75,231,
64,150,76,160,72,39,48,108,189,50,229,45,237,60,103,105,116,163,234,243,206,142,198,226,81,2,208,190,63,60,195,0,15,149,235,249,244,189,212,123,61,158,166,215,115,66,113,33,34,13,193,106,29,0,134,13,27,
5,22,12,86,35,249,15,0,4,131,213,209,175,42,152,5,1,68,81,240,67,5,164,197,15,233,62,249,56,29,62,5,80,100,138,140,50,140,207,4,184,252,253,167,91,62,44,107,213,101,75,8,82,79,120,27,1,40,49,132,29,189,
210,119,177,126,203,144,233,66,129,114,98,110,21,128,201,33,175,107,119,114,215,198,151,205,175,40,189,233,198,220,172,51,166,181,22,14,27,133,250,96,53,130,193,234,51,43,95,237,193,8,92,138,90,124,128,
60,101,2,60,191,243,65,250,173,2,226,57,214,117,71,96,10,78,73,211,133,92,105,181,33,168,12,216,30,16,179,19,252,192,112,84,254,36,245,197,191,77,187,29,93,214,171,16,56,254,39,171,50,2,210,97,66,91,211,
110,14,218,105,191,222,208,17,124,32,125,144,206,116,145,206,228,205,230,34,132,221,24,129,235,208,224,16,24,27,39,192,215,73,128,25,50,136,146,190,202,212,251,24,2,70,134,8,201,111,67,12,33,64,30,7,242,
29,144,194,165,114,124,252,167,35,115,183,163,179,211,77,114,174,41,248,26,128,111,224,120,31,139,193,8,72,131,14,239,138,142,112,230,126,231,137,198,182,224,227,73,111,113,54,192,232,161,246,158,169,
114,57,106,177,27,35,240,10,116,126,17,170,255,18,129,51,59,12,39,6,8,200,137,131,165,157,203,16,32,224,32,224,61,62,87,33,208,6,199,235,229,24,222,51,135,20,10,168,112,181,22,146,124,77,104,47,189,14,
90,25,131,127,105,123,75,70,169,115,127,99,75,221,115,73,48,130,103,9,140,179,38,46,94,142,90,236,194,8,76,68,45,46,65,237,162,35,24,17,184,43,35,254,100,136,73,215,16,8,107,0,234,222,39,20,119,82,9,25,
28,122,50,224,177,90,99,189,103,101,251,98,24,60,31,169,199,161,38,226,167,232,67,17,8,179,73,151,22,34,243,26,154,235,86,165,226,220,89,4,3,0,254,63,137,4,77,165,141,226,8,11,0,0,0,0,73,69,78,68,174,
66,96,130,0,0};

const char* UiEditorAbout::vst_logo_100x_png = (const char*) resource_UiEditorAbout_vst_logo_100x_png;
const int UiEditorAbout::vst_logo_100x_pngSize = 7586;

// JUCER_RESOURCE: au_logo_100x_png, 4848, "../Images/au_logo_100x.png"
static const unsigned char resource_UiEditorAbout_au_logo_100x_png[] = { 137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,0,121,0,0,0,120,8,3,0,0,0,225,120,173,222,0,0,2,238,80,76,84,69,255,255,255,254,
254,254,255,254,253,253,254,254,252,252,252,255,252,250,255,251,248,255,248,243,249,250,249,255,247,234,254,245,241,245,246,246,255,244,227,249,243,242,244,244,244,254,243,236,255,242,216,242,243,243,
241,241,242,252,238,236,240,240,240,255,239,207,239,239,239,254,236,226,245,238,230,237,237,238,254,235,219,247,234,234,254,235,195,235,235,235,253,231,226,253,229,209,253,228,219,255,231,183,231,232,
233,245,227,228,254,232,142,230,230,231,227,229,229,228,228,228,253,222,211,254,226,169,254,230,131,223,228,235,227,227,227,226,226,226,253,222,194,254,227,118,223,223,223,252,217,202,222,224,224,255,
224,107,254,220,151,252,216,183,255,224,97,219,219,219,250,211,208,252,211,195,255,221,89,255,220,82,254,215,136,255,219,99,215,215,215,214,216,217,252,208,168,220,214,207,211,215,218,255,217,76,255,215,
90,254,210,123,255,215,71,237,209,170,251,204,184,211,211,211,255,211,82,255,211,68,254,207,113,255,210,76,250,199,196,251,203,157,204,208,214,207,207,207,255,206,66,253,202,99,250,194,171,255,203,73,
232,201,144,237,195,195,204,203,203,199,203,209,251,195,140,255,201,62,252,198,84,201,200,200,249,188,182,240,199,93,196,200,204,208,199,181,255,196,59,199,198,198,232,195,132,250,186,161,250,189,132,
253,194,75,247,192,90,254,193,67,196,195,195,254,192,56,222,193,134,188,195,207,254,189,54,228,192,105,250,184,121,253,189,63,253,188,57,193,192,192,231,181,181,253,186,51,249,177,147,253,184,53,253,185,
47,188,188,188,214,187,122,253,183,41,250,177,109,181,188,199,246,171,165,252,178,61,253,181,36,197,184,152,253,180,33,252,178,51,246,168,153,189,183,165,248,168,136,183,182,182,249,171,99,229,167,168,
251,171,48,249,165,87,178,177,177,248,159,122,250,165,47,244,157,137,226,159,161,173,172,172,242,153,153,248,159,76,249,160,46,246,153,117,248,155,69,170,168,169,248,156,44,247,150,106,248,153,64,167,
165,166,247,153,43,243,143,142,248,150,60,247,148,86,247,148,55,163,162,163,247,147,51,246,149,42,246,141,97,246,146,42,243,139,109,247,143,46,247,144,48,246,142,67,159,157,158,245,143,41,246,141,53,244,
141,42,247,140,41,245,138,47,245,133,87,247,137,35,244,136,45,153,152,152,245,137,40,218,134,137,245,133,77,235,129,130,245,133,41,246,134,29,244,133,49,243,130,60,244,128,40,146,145,145,244,123,72,242,
119,84,142,140,140,243,120,41,244,116,62,237,109,106,243,111,40,244,109,53,134,131,132,242,103,76,239,101,94,243,104,45,211,106,110,243,100,40,243,97,36,241,93,62,243,94,33,123,121,121,242,90,26,240,89,
45,234,85,88,212,89,94,115,113,113,240,83,40,112,110,110,220,78,84,110,108,108,239,73,55,239,72,39,205,78,84,107,104,105,239,68,69,103,101,101,101,98,99,238,61,39,98,95,96,95,92,93,196,60,67,238,49,31,
89,86,87,236,45,41,208,47,55,80,77,78,232,30,36,73,70,71,234,26,29,213,30,38,68,64,65,187,30,39,64,61,62,62,58,59,55,52,53,196,12,23,51,47,48,46,43,43,41,37,38,35,31,32,29,25,26,24,20,21,14,10,11,22,235,
138,14,0,0,0,1,98,75,71,68,0,136,5,29,72,0,0,0,9,112,72,89,115,0,0,11,19,0,0,11,19,1,0,154,156,24,0,0,0,7,116,73,77,69,7,222,4,6,12,49,21,150,145,52,222,0,0,15,136,73,68,65,84,104,222,237,154,127,76,83,
247,22,192,129,75,3,22,165,8,17,94,157,10,178,17,96,11,88,51,28,115,111,50,222,30,230,169,241,199,26,220,166,4,77,22,3,4,217,80,146,133,64,102,36,75,124,192,164,93,130,48,160,16,160,54,52,197,255,52,36,
132,191,88,165,133,169,55,147,100,79,140,113,27,129,4,180,105,150,20,104,122,111,238,127,239,156,243,189,183,220,210,162,110,35,239,229,189,112,16,40,237,189,223,207,247,156,239,57,231,123,190,231,26,
197,253,183,36,106,147,188,73,222,36,111,146,255,207,200,71,234,55,24,18,87,127,240,149,200,25,227,110,115,202,70,130,211,44,252,248,158,87,32,235,134,220,110,247,96,206,198,129,115,70,121,158,183,188,
2,185,158,7,242,67,139,118,163,192,186,161,135,48,160,187,254,165,228,131,147,120,221,248,6,234,204,70,156,216,255,18,114,10,155,225,105,120,25,19,183,1,190,133,63,42,220,145,172,184,150,124,154,192,102,
124,153,127,57,253,207,130,243,47,231,227,47,244,28,183,251,200,11,201,25,19,184,202,227,232,218,233,109,119,58,242,255,28,248,64,215,157,214,173,56,42,218,155,31,79,123,1,89,211,252,80,153,157,230,178,
221,106,239,45,214,252,113,174,166,204,106,179,218,43,87,237,93,241,2,50,77,206,61,132,184,226,225,97,171,213,222,166,251,227,228,173,29,118,43,176,15,192,75,237,32,57,89,218,186,100,77,51,218,154,71,
191,78,239,176,193,109,93,235,155,91,19,187,45,229,181,148,148,109,177,209,235,175,114,175,21,38,223,138,188,131,52,112,69,204,122,228,52,50,74,51,168,172,169,188,3,119,89,79,225,187,91,194,45,190,237,
245,79,251,93,63,255,6,242,243,131,254,79,95,143,15,159,215,22,252,89,6,179,183,222,193,65,180,102,92,198,137,148,245,200,245,228,131,25,56,221,1,188,169,21,153,73,229,185,107,208,175,125,249,224,183,
149,149,223,158,147,192,171,159,31,124,250,218,154,96,42,40,69,207,138,107,67,195,245,98,136,228,184,149,96,141,68,214,78,160,202,102,136,65,237,21,59,170,140,183,196,29,175,173,125,127,139,154,251,205,
191,86,86,158,255,228,234,191,118,237,218,55,215,174,245,187,126,122,190,178,226,250,114,155,234,146,164,195,13,13,239,147,189,113,148,59,149,48,115,29,41,61,26,19,153,124,4,167,197,99,174,201,71,176,
189,12,117,205,173,173,169,105,56,158,20,188,232,164,11,184,174,27,231,79,158,103,114,242,228,213,27,174,231,43,191,61,120,55,120,201,142,210,218,186,186,186,189,20,32,54,69,131,35,20,53,57,145,201,22,
74,53,58,229,134,94,116,141,164,42,28,165,90,33,107,251,159,175,44,184,110,156,190,170,150,243,87,111,220,123,182,242,243,55,138,175,237,170,1,169,45,199,123,210,7,72,5,80,53,109,144,87,82,84,24,57,109,
28,201,184,20,59,7,200,51,208,211,222,111,0,112,93,174,2,126,240,108,97,174,255,218,213,102,148,122,252,2,129,151,87,175,186,230,86,158,245,43,254,80,128,247,212,22,196,160,167,218,21,29,234,81,233,241,
184,72,228,211,147,152,104,114,100,159,180,117,237,68,195,225,24,117,199,229,33,181,174,133,133,57,87,179,153,4,128,102,250,7,127,195,47,215,220,194,179,7,242,50,106,74,235,20,67,165,247,0,217,134,49,
189,31,189,104,242,72,36,178,133,71,255,194,173,162,3,85,46,35,149,209,214,117,178,173,183,33,248,251,239,64,44,12,222,106,86,4,222,251,97,97,225,89,191,140,222,193,148,134,17,226,72,233,54,156,182,5,
149,110,142,64,214,141,226,66,84,200,25,192,102,197,36,146,84,131,35,228,202,227,245,47,44,44,252,120,123,8,164,205,210,166,22,139,197,50,244,221,237,167,160,245,151,178,210,52,227,106,140,172,124,114,
153,157,242,198,207,143,106,194,201,7,39,148,125,185,18,189,226,10,120,90,76,1,146,171,182,178,11,206,131,198,79,239,223,30,29,28,28,236,82,164,3,190,219,224,27,222,187,125,31,208,207,79,202,113,85,167,
76,121,103,171,93,78,73,171,128,53,100,76,35,15,41,101,99,252,223,41,198,236,85,5,247,127,37,171,156,246,43,128,103,238,143,223,186,117,171,171,107,0,254,245,118,245,210,11,250,190,117,107,220,61,3,232,
123,178,210,5,232,153,229,232,79,101,144,13,109,173,104,84,244,238,201,211,225,100,12,117,30,151,57,189,203,6,137,7,141,189,23,195,67,137,168,126,4,243,147,19,183,110,89,173,3,161,114,107,192,10,228,73,
30,209,215,228,149,38,7,217,33,167,67,91,7,122,55,46,52,223,28,70,214,98,49,66,51,42,238,197,60,143,155,212,97,184,185,225,48,11,132,140,95,23,158,62,229,239,79,142,57,48,55,88,7,66,190,80,198,238,242,
128,94,184,199,118,183,45,199,17,93,128,33,138,38,36,69,200,170,150,48,242,30,116,176,9,90,102,52,54,110,171,49,104,236,134,189,236,243,27,160,50,207,187,239,202,228,48,113,140,221,157,116,243,51,115,
11,87,217,245,185,95,161,185,241,213,229,144,133,30,221,179,150,204,214,31,141,210,106,31,24,176,225,50,39,85,163,127,49,99,167,221,91,152,153,1,240,93,135,195,97,99,98,181,118,118,14,116,118,210,203,
225,97,7,160,193,152,51,11,46,205,106,96,209,74,149,217,209,97,89,33,15,228,140,181,100,74,218,163,232,8,109,193,101,6,114,237,113,182,91,156,68,239,2,141,199,28,142,225,97,2,119,170,101,24,208,99,160,
245,125,126,238,87,150,192,183,98,242,174,222,133,53,17,120,130,29,183,61,221,168,58,151,4,201,148,220,44,114,77,96,235,192,36,255,62,122,118,1,251,248,218,2,104,60,9,224,59,164,115,231,90,1,242,29,212,
250,254,204,220,121,230,221,135,107,229,180,155,143,3,182,97,104,142,170,11,193,80,50,58,94,126,151,109,128,57,216,113,76,252,44,101,235,92,115,51,247,39,209,212,160,221,48,177,190,149,133,254,232,233,
177,219,237,104,112,158,159,187,193,162,176,0,23,250,176,236,98,54,42,38,105,75,170,95,75,166,253,19,223,45,38,227,224,221,229,24,83,187,216,50,187,158,146,119,57,236,61,61,61,106,174,2,239,65,113,56,
192,222,79,93,172,242,216,91,43,187,152,14,28,135,213,85,205,145,200,26,36,211,26,20,91,101,135,216,130,228,170,29,44,166,126,156,193,128,114,144,157,25,174,41,40,65,56,121,217,140,139,21,122,187,170,
225,246,82,28,154,178,216,129,87,32,163,206,72,222,90,5,183,150,51,215,126,87,86,217,70,220,235,215,155,214,8,177,123,236,168,52,255,189,138,92,142,254,73,5,78,177,18,208,230,152,151,147,203,85,228,57,
126,82,1,175,114,235,224,75,141,182,217,112,165,127,96,17,155,68,38,219,170,38,227,62,252,208,172,121,37,114,109,105,80,103,36,51,48,145,235,130,18,100,3,26,148,14,146,49,172,202,67,200,71,126,7,89,209,
57,103,230,254,93,135,173,7,201,161,88,21,28,208,176,212,99,110,197,218,180,88,33,228,138,63,64,206,248,193,125,215,97,149,77,45,227,170,101,81,163,193,220,252,80,138,106,157,99,212,100,242,176,230,136,
30,86,161,38,107,212,81,117,219,61,6,171,76,26,203,216,143,101,81,177,65,105,219,152,251,59,153,92,23,140,42,155,245,5,81,165,202,36,189,112,14,107,197,13,170,20,55,73,182,97,232,190,227,199,172,214,32,
88,193,158,80,224,12,141,74,143,241,245,204,156,185,184,67,31,71,219,5,51,137,121,125,178,57,152,236,112,173,14,3,88,201,158,21,64,38,149,21,238,137,160,16,91,70,119,90,199,220,114,31,136,106,131,130,
96,58,198,122,104,80,125,206,8,146,79,195,22,200,15,134,36,187,92,32,55,28,102,26,236,119,143,89,7,86,193,39,78,252,93,37,178,218,140,44,111,70,108,131,206,149,141,104,107,213,194,242,225,70,28,190,99,
160,199,187,71,177,204,199,101,233,61,64,62,2,123,149,28,86,105,150,187,54,70,174,102,250,254,85,17,153,77,228,166,206,225,49,51,235,74,36,85,41,245,204,41,27,86,26,216,9,25,87,247,75,130,228,156,113,
94,174,207,112,39,183,151,225,180,209,134,181,187,100,115,223,181,118,94,191,14,111,16,24,136,239,129,188,3,223,132,63,65,90,55,93,239,181,142,21,179,235,247,162,177,171,208,181,177,238,181,85,42,21,247,
104,250,90,50,157,62,38,208,20,167,40,113,163,145,177,96,111,40,96,230,206,24,116,244,94,39,149,101,133,223,145,5,103,128,90,51,178,163,45,69,174,123,27,228,173,74,135,105,187,87,9,103,126,72,27,86,1,
90,148,205,42,191,11,182,29,218,160,113,161,89,50,64,23,116,12,92,111,170,38,91,171,184,50,156,236,93,141,100,217,129,200,216,20,24,249,88,80,118,165,43,174,109,14,175,61,177,69,66,245,153,150,218,5,184,
208,91,107,84,230,222,217,102,237,104,98,42,191,7,180,183,65,246,193,23,136,140,70,178,173,85,163,50,118,29,238,23,197,88,245,182,225,25,107,136,87,119,228,86,201,232,98,60,213,103,87,172,114,9,168,193,
218,160,166,84,62,61,31,176,126,139,58,19,24,168,251,222,68,217,247,230,62,134,62,1,62,214,212,213,43,183,55,104,135,173,193,184,136,163,2,240,50,121,82,72,67,46,74,221,104,85,229,79,86,15,237,106,80,
41,205,85,14,16,185,164,4,193,64,125,227,205,55,64,128,14,232,146,19,168,115,167,236,94,49,84,22,212,238,8,118,31,112,66,167,241,116,62,170,139,112,162,67,99,80,86,77,195,206,138,124,200,32,165,229,163,
103,220,229,142,234,186,42,34,239,35,40,19,66,151,28,251,184,170,250,219,50,121,239,165,195,73,29,221,119,10,27,46,29,26,229,40,97,137,116,150,196,125,155,31,194,57,93,198,147,39,149,98,123,191,82,31,
159,211,174,52,85,87,29,43,41,121,251,237,55,85,228,55,128,124,168,228,88,85,85,83,165,114,58,166,243,88,3,218,42,141,156,166,146,108,202,203,59,67,24,153,194,141,74,67,106,111,216,243,149,218,85,169,
185,97,156,202,166,170,242,146,146,67,97,58,35,185,233,148,210,78,217,65,137,128,234,229,3,184,202,182,116,74,146,74,65,31,70,142,25,87,54,177,184,54,10,105,173,82,199,49,187,225,165,127,57,133,74,31,
10,81,90,81,185,56,65,30,142,182,215,154,154,29,114,241,110,181,93,9,182,104,134,34,247,73,42,168,59,153,161,204,148,148,102,101,115,21,6,102,116,108,66,98,162,254,31,165,10,90,246,47,25,92,154,159,154,
152,16,79,227,229,226,206,76,205,10,174,216,166,12,148,51,185,166,45,165,38,167,77,42,141,18,29,174,142,181,67,203,90,52,181,4,142,226,226,19,147,245,89,111,253,237,147,210,99,199,14,29,66,247,6,7,223,
7,65,5,224,210,79,12,111,237,78,221,158,192,58,130,185,112,15,53,196,116,189,65,227,85,80,43,78,187,78,39,206,66,39,28,92,138,3,232,145,54,106,1,238,173,41,165,202,23,84,222,158,186,59,219,80,248,225,
103,159,95,42,133,197,6,248,219,135,0,91,82,122,233,147,207,62,48,228,101,233,147,101,165,185,93,229,117,20,138,149,65,149,247,80,19,185,121,189,30,224,126,94,81,122,43,213,200,20,134,220,94,230,95,104,
236,228,221,89,121,134,162,179,103,27,191,254,252,210,165,82,146,75,159,127,254,245,197,179,31,126,96,200,206,4,157,149,62,100,18,21,20,249,212,99,66,149,99,104,251,119,103,172,71,142,163,22,56,117,183,
243,241,172,104,107,83,247,225,9,173,207,204,54,124,112,244,236,23,95,180,52,254,243,107,144,127,54,54,126,113,246,163,34,208,120,55,129,67,86,143,53,31,243,149,133,228,205,154,117,187,204,164,52,95,31,
108,100,217,42,85,215,70,69,199,198,3,59,117,119,86,150,161,176,168,232,35,38,31,22,129,161,179,51,245,122,224,198,114,234,198,175,230,10,217,26,247,219,24,51,175,180,23,215,33,235,176,51,229,158,220,
163,180,153,89,61,166,98,115,177,9,9,9,219,183,167,166,238,6,126,54,74,102,102,166,62,57,57,17,252,58,54,58,116,48,106,22,176,179,97,6,245,53,205,218,23,60,77,160,62,52,29,102,185,3,80,196,92,14,107,172,
35,60,54,62,30,248,16,98,36,9,9,241,241,177,177,240,73,216,99,160,180,43,114,205,169,101,15,50,114,94,244,28,35,142,226,157,53,112,202,122,79,69,126,150,16,133,178,206,95,161,93,238,202,222,83,171,15,
19,234,53,47,124,118,179,127,18,181,158,64,39,140,203,255,19,15,49,100,52,13,145,67,105,121,60,227,37,79,202,42,120,68,15,233,184,13,147,20,234,242,242,167,95,246,140,142,186,83,170,182,213,159,22,45,
243,107,139,230,165,207,37,247,99,182,121,88,191,145,100,62,210,227,198,8,190,81,129,46,166,217,56,107,199,85,132,63,160,91,231,201,183,121,60,39,102,35,159,63,199,28,156,104,126,181,103,238,58,29,183,
193,178,71,179,249,63,28,54,201,155,228,77,242,38,249,63,76,222,94,88,4,197,116,116,252,239,27,62,254,21,201,241,166,190,246,172,117,46,188,224,241,25,184,212,233,217,139,225,31,37,155,186,207,208,139,
115,125,166,132,144,79,186,231,71,94,141,108,8,4,196,190,117,46,108,17,164,66,174,69,146,158,132,91,201,176,20,152,162,23,211,130,55,59,228,19,191,180,108,164,67,194,203,200,35,162,32,61,74,136,76,110,
244,3,217,224,151,34,40,97,88,22,24,249,145,232,11,37,63,17,23,147,185,196,246,249,190,151,144,163,60,126,175,232,59,26,177,206,101,228,168,228,212,248,224,59,42,157,133,48,157,217,199,9,250,68,142,51,
250,196,145,240,155,66,200,133,1,223,136,79,234,198,5,191,104,50,192,47,125,203,197,221,184,142,141,78,231,81,19,146,19,90,90,10,233,202,190,169,145,70,125,100,114,161,201,152,104,28,113,182,0,147,51,
182,156,227,178,156,203,194,163,150,11,241,92,236,69,167,179,175,48,34,249,166,224,201,252,69,122,148,204,113,89,62,178,234,69,113,249,2,199,29,245,136,146,40,46,45,3,57,91,146,156,184,42,1,73,16,37,207,
209,136,100,167,228,121,34,73,162,244,120,59,199,205,75,30,248,59,16,144,164,165,212,196,71,34,44,166,55,34,121,81,120,194,221,148,252,48,173,76,47,145,47,136,190,115,92,252,162,24,152,30,153,15,8,98,
33,151,37,34,25,220,225,81,159,115,73,242,102,69,34,247,1,96,118,26,102,11,198,155,21,61,177,23,60,126,193,243,196,201,117,139,254,169,155,211,206,72,100,112,81,19,119,110,89,106,95,37,11,64,238,14,224,
50,109,127,44,74,50,57,111,73,156,199,136,9,122,91,40,185,197,47,78,115,92,145,79,122,156,140,100,61,103,244,138,55,241,195,224,76,195,200,35,129,229,188,132,188,121,244,110,53,121,90,90,2,187,113,38,
65,50,48,242,77,127,160,17,222,200,242,136,243,81,17,200,228,16,92,252,148,52,191,155,145,207,49,15,27,145,132,233,11,145,201,139,66,96,126,113,113,73,88,206,84,145,207,112,179,210,98,130,18,85,68,30,
17,252,20,121,191,72,243,44,78,11,85,228,60,36,231,193,184,78,105,86,31,66,206,94,132,213,126,156,23,129,92,228,21,4,73,146,132,128,216,18,66,158,15,35,7,2,100,182,89,50,58,138,79,152,150,195,215,19,133,
228,108,34,207,135,146,57,125,159,87,20,231,147,195,201,35,66,224,130,94,159,8,171,242,8,201,168,69,31,179,246,50,94,221,46,40,228,110,127,160,5,222,200,243,136,191,200,185,201,3,142,4,191,18,189,226,
44,39,235,204,77,5,117,62,227,19,152,67,68,37,58,5,191,41,156,252,68,244,82,150,120,44,46,39,234,23,37,79,17,151,229,21,124,23,184,155,1,193,153,28,101,88,12,122,88,145,79,92,132,88,118,138,162,105,117,
210,35,209,177,177,206,64,160,155,11,215,25,28,98,42,33,158,75,76,141,226,140,130,191,47,140,92,4,106,70,179,168,22,219,193,29,68,239,244,146,31,227,57,121,81,20,61,211,94,49,32,53,202,241,60,18,16,61,
221,211,96,185,68,249,222,84,48,163,103,202,35,162,202,232,138,160,115,244,20,146,33,158,245,92,204,162,36,204,142,112,211,75,35,55,23,37,111,97,24,185,197,187,116,142,121,234,188,111,138,203,154,245,
11,130,183,207,183,8,9,255,220,188,63,32,120,157,191,44,195,250,47,249,201,77,189,2,164,150,233,96,18,227,140,139,203,130,32,248,30,165,162,67,120,151,193,13,162,70,2,211,169,64,155,133,183,76,62,63,88,
105,42,32,138,1,143,41,220,195,242,206,24,99,217,59,133,198,34,204,152,237,237,133,156,177,8,3,42,181,209,100,42,226,12,70,61,23,107,52,162,115,69,21,181,155,186,207,133,236,175,141,237,166,118,35,217,
44,245,168,17,87,45,235,12,228,95,131,145,84,60,211,222,125,49,90,15,151,152,178,54,171,161,77,242,38,121,147,188,73,222,36,255,239,144,255,13,146,159,133,80,37,28,6,136,0,0,0,0,73,69,78,68,174,66,96,
130,0,0};

const char* UiEditorAbout::au_logo_100x_png = (const char*) resource_UiEditorAbout_au_logo_100x_png;
const int UiEditorAbout::au_logo_100x_pngSize = 4848;

// JUCER_RESOURCE: aboutbox_png, 8767, "../../Artwork/aboutbox.png"
static const unsigned char resource_UiEditorAbout_aboutbox_png[] = { 137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,1,175,0,0,2,28,8,6,0,0,0,65,221,33,71,0,0,0,6,98,75,71,68,0,255,0,255,0,255,160,189,
167,147,0,0,0,9,112,72,89,115,0,0,11,19,0,0,11,19,1,0,154,156,24,0,0,0,7,116,73,77,69,7,222,11,26,14,46,41,239,191,237,95,0,0,0,29,105,84,88,116,67,111,109,109,101,110,116,0,0,0,0,0,67,114,101,97,116,
101,100,32,119,105,116,104,32,71,73,77,80,100,46,101,7,0,0,32,0,73,68,65,84,120,218,237,221,123,148,151,245,97,239,251,207,220,97,64,16,101,48,130,4,212,236,25,196,66,64,67,48,70,27,91,47,153,216,194,
142,214,236,46,47,209,30,21,179,226,74,218,68,151,199,115,78,143,154,146,70,183,145,109,98,170,173,23,220,70,186,60,53,222,182,61,233,214,28,110,67,228,26,43,140,9,74,156,1,185,168,1,69,68,110,129,97,
174,231,15,156,31,76,65,24,80,179,25,125,189,214,114,57,254,158,203,60,191,239,122,214,188,253,62,207,51,191,41,74,210,17,0,232,65,138,13,1,0,226,5,0,226,5,0,226,5,128,120,1,128,120,1,128,120,1,32,94,
0,32,94,0,32,94,0,136,23,0,136,23,0,136,23,0,226,5,0,226,5,0,226,5,128,120,1,128,120,1,128,120,1,128,120,1,32,94,0,32,94,0,32,94,0,136,23,0,136,23,0,136,23,0,226,5,0,226,5,0,226,5,128,120,1,128,120,1,
128,120,1,32,94,0,32,94,0,32,94,0,32,94,0,136,23,0,136,23,0,136,23,0,226,5,0,226,5,0,226,5,192,199,78,233,49,3,7,26,5,0,122,86,188,142,236,211,199,40,0,208,163,20,77,249,229,244,14,195,0,64,143,154,121,
53,239,216,97,20,0,232,81,60,176,1,128,120,1,128,120,1,128,120,1,32,94,0,32,94,0,32,94,0,136,23,0,136,23,0,136,23,0,226,5,0,226,5,0,226,5,128,120,1,128,120,1,128,120,1,32,94,0,32,94,0,32,94,0,32,94,0,
136,23,0,136,23,0,136,23,0,226,5,0,226,5,0,226,5,128,120,1,128,120,1,128,120,1,32,94,0,32,94,0,32,94,0,136,23,0,136,23,0,136,23,0,136,23,0,226,5,0,226,5,0,226,5,128,120,1,128,120,1,128,120,1,32,94,0,32,
94,0,32,94,0,136,23,0,136,23,0,136,23,0,226,5,0,226,5,0,226,5,128,120,1,128,120,1,128,120,1,128,120,1,32,94,0,32,94,0,32,94,0,136,23,0,136,23,0,136,23,0,31,99,165,29,198,0,128,158,22,175,182,182,54,163,
0,64,207,138,87,107,135,185,23,0,102,94,0,240,17,207,188,218,219,141,2,0,61,108,230,213,238,178,33,0,61,46,94,46,27,2,208,195,226,213,218,230,178,33,0,61,45,94,238,121,1,208,211,226,213,38,94,0,152,121,
1,128,153,23,0,136,23,0,61,60,94,46,27,2,208,243,226,229,81,121,0,122,90,188,92,54,4,160,231,205,188,196,11,0,51,47,0,16,47,0,232,26,47,151,13,1,16,47,0,248,168,227,229,178,33,0,61,47,94,126,207,11,128,
158,22,47,151,13,1,232,121,51,47,241,2,192,204,11,0,196,11,0,186,198,203,101,67,0,196,11,0,62,234,120,249,147,40,0,152,121,1,192,71,62,243,18,47,0,204,188,0,224,163,158,121,185,231,5,64,143,155,121,117,
136,23,0,61,109,230,229,178,33,0,61,46,94,46,27,2,96,230,5,0,31,113,188,6,188,246,186,81,0,160,103,197,107,240,138,149,70,1,128,30,165,232,136,35,142,232,48,12,0,244,168,153,87,81,81,145,81,0,160,71,41,
54,4,0,136,23,0,136,23,0,136,23,0,226,5,0,226,5,0,226,5,128,120,1,128,120,1,128,120,1,32,94,0,32,94,0,32,94,0,136,23,0,136,23,0,136,23,0,226,5,0,226,5,0,226,5,0,226,5,64,143,85,122,184,29,208,164,83,122,
229,179,159,42,73,146,76,254,229,142,172,255,125,123,151,229,119,156,215,39,189,223,59,234,182,142,228,237,223,119,100,229,187,109,249,121,99,115,182,238,236,216,107,127,149,101,201,127,30,81,145,209,
199,148,164,87,105,113,214,110,105,203,255,247,106,75,126,243,86,107,97,157,138,210,162,252,183,243,42,147,36,175,190,219,158,31,45,220,81,88,118,245,41,189,50,102,143,227,185,249,75,189,247,123,252,255,
247,236,237,217,212,212,241,190,203,171,143,46,201,95,143,239,149,36,153,255,122,107,254,101,233,206,46,203,111,250,82,101,142,233,83,148,214,246,162,124,231,23,219,246,122,223,211,126,189,51,207,255,
110,215,177,127,253,179,21,25,63,100,215,96,252,215,121,59,242,198,150,246,189,198,104,79,115,95,107,205,207,94,218,217,237,113,1,16,175,110,250,218,31,85,100,104,191,93,19,194,255,183,161,57,211,95,237,
26,175,179,134,151,165,111,121,209,94,219,93,127,122,101,110,169,251,125,254,173,177,185,240,218,49,125,139,243,200,95,28,145,33,71,236,57,193,44,203,149,167,244,202,29,243,119,228,191,215,55,37,73,74,
138,58,114,246,9,229,73,146,1,235,186,254,240,30,117,76,105,206,62,161,44,73,114,231,194,166,194,122,239,231,251,191,220,190,223,229,231,87,151,23,246,177,231,177,118,250,194,113,165,57,126,64,73,154,
219,58,246,249,190,203,74,138,242,252,239,118,69,109,100,85,73,97,95,119,63,223,116,192,49,218,176,163,227,160,198,5,224,112,117,88,93,54,60,178,87,81,33,92,73,50,250,152,247,111,235,142,214,93,113,123,
254,119,173,105,109,239,72,101,89,242,253,63,173,76,85,229,238,237,111,56,189,119,225,7,244,187,59,58,178,98,99,91,218,223,107,194,119,191,208,187,203,247,234,142,142,36,155,154,58,178,169,169,35,219,
91,118,191,222,212,186,251,245,246,20,237,119,31,231,28,191,43,132,205,109,29,121,110,77,203,65,143,209,25,159,46,203,177,125,187,119,220,59,90,147,167,95,217,89,248,231,197,117,109,31,201,184,0,124,162,
103,94,157,177,234,72,82,148,100,212,49,37,239,187,238,187,59,218,115,227,140,223,39,73,206,59,177,44,119,125,165,111,122,149,22,229,244,79,151,230,95,95,105,78,105,113,81,206,121,111,198,244,198,150,
246,76,248,127,54,167,169,117,215,165,182,255,235,204,202,148,22,39,95,254,76,121,166,46,233,254,44,163,173,189,35,95,152,186,41,73,50,177,166,60,183,159,219,39,73,242,15,191,234,222,108,229,248,1,37,
57,241,168,93,239,105,193,235,173,93,2,216,237,255,219,40,74,190,118,114,69,126,242,171,29,7,92,247,221,29,237,249,63,103,118,157,9,126,20,227,2,240,137,158,121,117,198,107,213,187,187,102,8,127,52,168,
44,197,69,7,222,110,217,219,109,133,175,251,87,236,218,224,184,126,197,169,40,221,245,245,175,223,108,77,211,123,87,3,23,190,190,251,178,224,137,71,253,97,223,254,185,239,69,35,73,102,174,108,57,228,253,
92,120,82,121,74,138,14,109,219,195,113,92,0,122,116,188,58,103,90,47,190,185,235,7,105,101,89,242,153,163,75,14,184,221,31,13,218,189,206,186,109,29,133,109,59,237,104,221,125,255,104,71,203,238,175,
251,148,21,253,65,223,223,57,39,238,186,63,213,214,145,204,90,217,124,200,251,57,166,111,113,206,58,190,252,144,182,61,28,199,5,224,96,29,86,151,13,71,13,218,117,56,175,108,104,75,83,107,71,122,149,22,
101,244,160,210,52,110,104,219,107,221,94,165,187,102,50,199,15,40,201,149,99,119,61,189,183,118,107,123,126,185,122,215,140,166,59,51,182,226,63,224,207,232,99,250,20,21,34,187,120,109,235,126,159,72,
236,142,255,114,114,121,54,238,104,223,239,58,189,74,147,115,222,123,160,99,245,166,182,172,216,216,118,216,141,11,64,143,158,121,13,237,95,156,1,189,119,253,212,124,115,107,123,222,218,182,235,7,243,
232,79,237,187,175,71,245,46,206,79,206,239,155,239,126,161,119,250,247,218,181,221,255,49,115,251,94,79,233,29,46,206,61,177,188,240,40,199,140,87,15,125,214,213,244,222,108,233,140,79,151,101,240,17,
251,159,149,30,213,187,56,255,112,126,159,252,195,249,125,242,159,71,84,56,219,1,241,250,176,237,249,100,225,155,219,218,243,214,239,59,222,123,189,164,219,251,184,225,139,189,83,122,152,222,174,57,247,
189,75,134,29,31,48,94,27,119,116,228,133,181,173,41,46,74,198,13,41,117,6,3,159,72,135,205,79,191,81,123,220,183,26,81,85,90,184,116,117,226,128,146,244,42,77,225,193,130,78,107,183,182,231,220,105,155,
51,180,127,113,254,238,172,62,25,127,92,105,70,13,42,201,159,85,151,231,95,95,105,62,172,6,249,200,94,69,57,117,240,174,161,126,105,125,91,33,204,135,234,127,252,182,57,159,27,92,154,3,93,221,91,187,181,
61,103,63,188,217,89,14,152,121,125,84,62,187,199,229,193,201,127,82,153,207,189,247,195,190,180,56,249,163,65,251,110,108,123,71,178,102,83,123,238,220,227,19,49,198,189,183,93,71,55,250,208,185,74,75,
251,251,103,160,40,187,119,212,220,118,104,239,237,79,143,223,253,116,224,140,21,31,60,172,207,46,223,121,72,143,217,31,236,184,0,136,215,254,166,127,197,201,73,3,223,255,242,224,168,99,246,63,65,220,
243,193,133,1,189,119,189,165,157,123,132,166,108,143,39,16,202,246,120,198,124,231,123,179,185,150,182,142,194,189,164,255,248,201,20,253,42,118,15,209,166,166,246,67,122,127,231,236,241,136,252,140,
15,240,136,124,167,29,173,201,47,86,236,60,164,109,15,102,92,0,196,107,63,170,143,46,41,252,238,209,163,47,237,204,73,119,191,155,63,253,233,238,203,93,163,15,16,175,154,129,187,151,191,253,222,103,33,
174,221,218,86,152,65,28,63,96,247,219,60,97,143,175,223,216,186,59,70,171,54,237,250,122,248,145,197,57,226,189,223,21,171,40,45,202,73,85,187,162,250,230,182,246,189,46,93,118,71,239,210,228,244,161,
187,142,111,197,198,182,172,222,212,246,161,140,217,255,248,237,161,205,224,14,118,92,0,14,71,135,197,61,175,61,227,244,242,250,93,63,220,215,109,107,207,187,59,58,50,160,119,209,62,31,218,232,124,84,
254,184,254,37,249,223,198,236,126,146,110,214,123,51,155,237,45,201,11,191,107,201,184,33,101,25,125,76,105,238,252,114,159,188,182,165,61,95,173,217,253,251,81,115,247,248,120,166,186,85,45,57,105,96,
73,202,75,138,242,208,87,143,200,188,53,45,249,252,144,210,244,123,47,100,179,87,29,218,140,233,143,135,151,21,194,60,243,67,152,117,117,122,97,109,107,214,108,106,203,176,35,75,14,106,187,131,29,23,0,
241,122,223,120,237,254,1,252,210,250,221,211,155,151,223,110,125,239,145,240,226,28,93,89,156,119,182,239,158,17,116,62,42,191,167,255,217,216,156,185,175,237,254,193,251,227,69,77,249,233,87,75,83,86,
82,148,175,252,167,174,191,212,59,253,213,150,44,94,187,251,123,253,247,37,77,249,234,136,242,12,62,162,56,39,87,149,228,228,170,221,199,244,206,246,246,220,253,252,142,67,122,111,231,238,241,65,190,31,
228,41,195,247,155,125,125,231,11,189,15,122,187,131,25,23,128,195,209,97,113,217,176,243,158,86,115,91,71,86,108,108,223,35,94,187,47,177,237,249,52,226,158,154,219,58,210,184,161,45,255,117,222,142,
252,239,239,125,214,97,167,37,235,90,115,197,211,219,50,247,181,150,108,221,217,145,150,182,142,172,222,212,150,127,248,213,142,220,48,189,235,186,191,111,233,200,101,79,110,205,191,190,210,156,183,183,
183,167,181,125,215,189,180,95,172,104,201,165,79,109,205,187,59,14,254,49,134,178,146,162,124,105,248,174,251,93,107,183,182,119,249,24,171,15,195,211,175,236,44,124,160,238,193,56,152,113,1,56,28,21,
245,235,215,207,195,101,0,152,121,1,128,120,1,128,120,1,32,94,0,32,94,0,32,94,0,136,23,0,136,23,0,136,23,0,226,5,0,226,5,0,226,5,128,120,1,128,120,1,128,120,1,32,94,0,32,94,0,32,94,0,32,94,0,136,23,0,
136,23,0,136,23,0,226,5,0,226,5,0,226,5,128,120,1,128,120,1,128,120,1,32,94,0,32,94,0,32,94,0,136,23,0,136,23,0,136,215,7,240,228,147,79,102,230,204,153,133,255,158,60,121,114,234,235,235,115,250,233,
167,39,73,78,61,245,212,212,215,215,231,234,171,175,126,223,125,140,28,57,50,245,245,245,249,238,119,191,235,236,1,16,175,143,94,99,99,99,142,62,250,232,28,113,196,17,73,146,227,143,63,190,203,191,79,
56,225,132,36,201,242,229,203,157,25,0,226,117,120,104,104,104,232,18,171,225,195,135,239,51,98,141,141,141,206,12,0,241,58,60,116,206,168,134,15,31,158,170,170,170,244,237,219,55,107,215,174,205,176,
97,195,10,175,111,221,186,53,235,214,173,75,146,156,118,218,105,121,234,169,167,178,112,225,194,220,123,239,189,25,48,96,64,97,95,85,85,85,121,240,193,7,51,111,222,188,124,235,91,223,114,38,1,136,215,
71,27,175,227,143,63,190,16,172,127,255,247,127,239,50,243,234,156,117,149,151,151,231,182,219,110,75,81,81,81,158,124,242,201,140,31,63,62,215,94,123,109,97,95,163,71,143,206,11,47,188,144,53,107,214,
228,170,171,174,202,9,39,156,144,170,170,170,76,155,54,45,147,38,77,114,102,1,136,87,87,37,37,37,135,180,221,250,245,235,179,105,211,166,12,27,54,44,195,135,15,79,91,91,91,22,47,94,156,163,143,62,58,131,
6,13,202,49,199,28,83,8,220,136,17,35,114,228,145,71,230,137,39,158,200,148,41,83,178,118,237,218,140,29,59,182,176,175,89,179,102,229,159,254,233,159,50,117,234,212,36,201,201,39,159,156,178,178,178,
140,26,53,42,67,135,14,117,102,1,124,132,74,123,226,65,63,251,236,179,89,180,104,81,102,205,154,149,133,11,23,166,185,185,249,160,102,95,199,29,119,92,142,59,238,184,188,245,214,91,89,179,102,77,146,100,
220,184,113,41,42,42,42,196,107,224,192,129,73,146,73,147,38,229,210,75,47,77,101,101,101,154,154,154,246,218,223,150,45,91,146,36,3,6,12,216,43,112,0,136,87,65,255,254,253,51,97,194,132,76,152,48,33,
219,183,111,207,115,207,61,151,153,51,103,102,254,252,249,251,12,204,158,26,26,26,114,225,133,23,102,200,144,33,89,189,122,117,86,175,94,93,136,87,231,242,36,41,43,43,75,146,220,125,247,221,121,226,137,
39,10,219,143,28,57,114,159,251,45,47,47,119,54,1,136,87,247,84,86,86,166,182,182,54,181,181,181,105,106,106,202,252,249,243,51,125,250,244,204,156,57,51,237,237,237,123,173,223,216,216,152,202,202,202,
140,28,57,50,115,230,204,201,150,45,91,178,113,227,198,140,27,55,46,237,237,237,89,177,98,69,146,20,102,115,197,197,187,174,172,94,114,201,37,41,47,47,207,243,207,63,223,101,127,157,151,48,155,155,155,
51,112,224,192,220,113,199,29,153,55,111,94,30,124,240,65,103,23,192,71,228,99,243,192,70,123,123,123,150,45,91,150,197,139,23,231,197,23,95,220,103,184,58,227,149,36,131,7,15,206,170,85,171,146,36,171,
86,173,202,224,193,131,243,218,107,175,101,231,206,157,73,82,120,226,176,170,170,42,73,114,197,21,87,164,182,182,118,175,253,13,26,52,168,176,126,121,121,121,198,140,25,83,120,24,4,0,51,175,189,180,181,
181,101,201,146,37,153,49,99,70,234,234,234,178,97,195,134,3,110,179,106,213,170,180,181,181,165,164,164,164,16,175,53,107,214,228,212,83,79,237,242,251,93,203,151,47,207,250,245,235,51,113,226,196,244,
237,219,55,131,6,13,202,244,233,211,11,203,207,60,243,204,108,223,190,61,231,157,119,94,90,90,90,178,120,241,226,108,220,184,209,61,47,0,241,218,183,5,11,22,100,238,220,185,153,61,123,118,54,109,218,116,
80,219,54,55,55,103,213,170,85,249,204,103,62,83,120,88,99,229,202,149,133,96,237,25,198,155,110,186,41,55,222,120,99,38,78,156,152,57,115,230,100,234,212,169,25,50,100,72,146,100,197,138,21,57,253,244,
211,115,236,177,199,230,206,59,239,204,198,141,27,157,77,0,127,32,69,253,250,245,235,48,12,0,244,36,62,85,30,0,241,2,0,241,2,0,241,2,64,188,0,64,188,0,64,188,0,16,47,0,16,47,0,16,47,0,196,11,0,196,11,
0,196,235,32,124,254,243,159,207,35,143,60,146,133,11,23,230,23,191,248,69,174,187,238,186,84,84,84,28,86,199,248,192,3,15,164,190,190,222,217,9,32,94,201,177,199,30,155,187,238,186,43,71,29,117,84,126,
250,211,159,102,229,202,149,249,250,215,191,158,27,111,188,209,153,0,32,94,135,167,207,125,238,115,233,213,171,87,254,241,31,255,49,247,221,119,95,190,253,237,111,231,141,55,222,200,87,190,242,149,195,
98,246,85,82,82,226,140,4,232,134,210,79,210,155,109,105,105,73,146,156,120,226,137,73,118,253,193,201,219,111,191,61,77,77,77,105,109,109,205,232,209,163,243,240,195,15,231,167,63,253,105,238,186,235,
174,220,115,207,61,57,253,244,211,115,218,105,167,229,196,19,79,204,35,143,60,146,186,186,186,12,26,52,40,195,135,15,207,163,143,62,154,187,239,190,59,35,71,142,124,223,101,73,82,91,91,155,111,125,235,
91,25,48,96,64,22,47,94,156,91,110,185,37,239,190,251,110,97,187,199,31,127,60,199,28,115,76,74,75,75,243,206,59,239,228,115,159,251,92,146,164,190,190,62,215,93,119,93,234,234,234,156,169,0,159,212,153,
215,188,121,243,178,126,253,250,92,118,217,101,185,240,194,11,11,175,189,240,194,11,105,107,107,235,214,62,6,15,30,156,7,30,120,32,175,188,242,74,174,186,234,170,156,112,194,9,251,93,54,96,192,128,124,
239,123,223,203,206,157,59,243,244,211,79,231,204,51,207,204,55,190,241,141,46,251,188,240,194,11,211,167,79,159,252,238,119,191,203,163,143,62,90,248,203,206,55,220,112,67,94,126,249,229,84,85,85,101,
218,180,105,153,52,105,146,51,22,160,167,198,235,80,47,175,109,219,182,45,127,253,215,127,157,205,155,55,231,166,155,110,202,247,191,255,253,244,234,213,235,160,246,241,171,95,253,42,191,252,229,47,243,
212,83,79,37,73,70,143,30,189,223,101,39,157,116,82,42,42,42,242,216,99,143,229,142,59,238,200,134,13,27,50,102,204,152,46,251,156,57,115,102,174,190,250,234,220,122,235,173,89,182,108,89,54,110,220,88,
120,125,253,250,245,41,43,43,203,168,81,163,50,116,232,80,103,44,64,122,232,101,195,103,159,125,54,139,22,45,202,172,89,179,178,112,225,194,52,55,55,119,123,219,134,134,134,92,124,241,197,185,253,246,
219,243,231,127,254,231,57,225,132,19,242,205,111,126,51,91,182,108,57,168,99,232,12,76,191,126,253,246,187,172,243,216,58,47,89,54,53,53,101,192,128,1,93,214,127,235,173,183,246,251,189,214,174,93,155,
177,99,199,58,91,1,122,242,204,171,127,255,254,153,48,97,66,126,252,227,31,167,174,174,46,183,221,118,91,206,62,251,236,110,207,162,214,175,95,159,171,175,190,58,143,63,254,120,70,142,28,153,27,110,184,
225,160,143,161,243,50,99,121,121,249,126,151,21,21,21,57,203,0,196,171,171,202,202,202,212,214,214,102,202,148,41,169,171,171,203,148,41,83,114,222,121,231,165,184,120,239,183,54,122,244,232,220,127,
255,253,249,242,151,191,156,182,182,182,220,122,235,173,89,190,124,121,106,107,107,15,250,105,195,206,40,237,107,214,183,231,178,142,142,142,15,252,30,7,14,28,152,135,30,122,40,87,93,117,149,51,22,32,
31,163,7,54,218,219,219,179,108,217,178,44,94,188,56,47,190,248,98,218,219,219,247,126,179,197,197,25,55,110,92,206,56,227,140,194,107,175,189,246,90,74,75,75,15,250,222,215,167,62,245,169,36,201,155,
111,190,185,223,101,155,55,111,78,146,148,149,149,37,73,42,42,42,178,105,211,166,110,133,177,51,192,229,229,229,25,51,102,76,134,13,27,230,140,5,72,15,127,84,190,173,173,45,75,150,44,201,140,25,51,82,
87,87,151,13,27,54,236,119,253,223,252,230,55,249,237,111,127,155,63,251,179,63,75,75,75,75,182,108,217,146,51,207,60,51,13,13,13,217,188,121,115,90,91,91,147,236,250,20,142,43,175,188,50,167,156,114,
202,94,251,56,251,236,179,179,115,231,206,156,125,246,217,105,105,105,201,11,47,188,80,136,213,190,150,117,206,192,46,186,232,162,12,25,50,36,85,85,85,153,51,103,206,126,143,243,157,119,222,73,146,92,
127,253,245,121,252,241,199,179,122,245,106,247,188,0,122,122,188,22,44,88,144,185,115,231,102,246,236,217,7,156,197,252,199,217,217,119,190,243,157,92,127,253,245,249,210,151,190,148,242,242,242,44,90,
180,40,63,252,225,15,147,36,175,190,250,106,26,26,26,242,233,79,127,58,125,250,244,201,175,127,253,235,140,31,63,190,203,62,150,45,91,150,83,78,57,37,199,30,123,108,238,188,243,206,108,220,184,177,16,
175,125,45,75,146,201,147,39,231,155,223,252,102,46,186,232,162,204,159,63,63,247,221,119,223,126,143,243,159,255,249,159,115,242,201,39,231,107,95,251,90,22,46,92,152,213,171,87,59,83,1,246,80,212,175,
95,191,14,195,112,96,157,191,80,60,109,218,180,252,232,71,63,234,246,50,0,62,124,62,85,30,0,51,47,0,48,243,2,0,241,2,64,188,0,64,188,0,64,188,0,16,47,0,16,47,0,16,47,0,196,11,0,196,11,0,196,171,155,6,
15,30,156,250,250,250,212,215,215,231,194,11,47,44,188,126,206,57,231,20,94,175,169,169,249,131,31,87,77,77,77,234,235,235,15,233,47,58,3,136,215,39,72,117,117,117,225,235,17,35,70,56,19,0,196,235,240,
214,218,218,218,101,134,85,83,83,83,248,67,148,0,136,215,97,105,213,170,85,169,174,174,78,81,81,81,97,22,182,106,213,170,46,235,76,152,48,33,207,60,243,76,230,206,157,155,31,252,224,7,233,221,187,119,
146,93,127,187,171,190,190,62,127,255,247,127,159,219,111,191,61,243,230,205,43,252,49,203,209,163,71,167,190,190,62,127,243,55,127,147,36,185,231,158,123,82,95,95,159,138,138,138,253,238,19,0,241,58,
160,149,43,87,166,162,162,34,67,135,14,205,81,71,29,149,65,131,6,165,161,161,161,176,124,216,176,97,185,229,150,91,178,110,221,186,60,250,232,163,57,255,252,243,115,205,53,215,116,217,199,103,63,251,217,
60,255,252,243,217,182,109,91,206,61,247,220,66,160,222,79,119,246,153,36,85,85,85,153,54,109,90,38,77,154,228,236,4,248,56,197,171,164,164,228,3,109,223,220,220,156,213,171,87,167,166,166,38,53,53,53,
89,191,126,125,182,108,217,82,88,126,236,177,199,166,190,190,62,247,223,127,127,238,185,231,158,108,223,190,61,167,156,114,74,151,125,204,158,61,59,79,62,249,100,26,27,27,119,13,100,241,254,135,178,59,
251,76,146,178,178,178,140,26,53,42,67,135,14,117,118,2,188,143,210,158,120,208,207,62,251,108,22,45,90,148,89,179,102,101,225,194,133,105,110,110,62,232,125,52,52,52,164,166,166,38,219,182,109,203,43,
175,188,210,101,217,162,69,139,178,104,209,162,84,84,84,228,130,11,46,72,105,105,105,250,244,233,243,129,142,185,187,251,92,187,118,109,198,142,29,235,204,4,248,184,197,171,127,255,254,153,48,97,66,38,
76,152,144,237,219,183,231,185,231,158,203,204,153,51,51,127,254,252,52,53,53,117,107,31,141,141,141,25,55,110,92,182,109,219,150,198,198,198,84,86,86,118,89,126,198,25,103,228,230,155,111,206,214,173,
91,211,222,222,254,161,28,247,71,177,79,128,79,162,30,127,207,171,178,178,50,181,181,181,153,50,101,74,234,234,234,50,101,202,148,156,119,222,121,7,188,140,215,216,216,152,234,234,234,84,87,87,23,46,253,
117,26,56,112,96,238,184,227,142,44,95,190,60,23,95,124,113,118,238,220,249,129,143,179,187,251,28,56,112,96,30,122,232,161,92,117,213,85,206,78,128,143,107,188,58,181,183,183,103,217,178,101,89,188,120,
113,94,124,241,197,3,206,108,26,26,26,82,85,85,149,225,195,135,119,121,88,35,73,78,61,245,212,244,234,213,43,207,60,243,204,33,93,146,220,151,238,238,179,188,188,60,99,198,140,201,176,97,195,156,157,0,
239,163,180,39,31,124,91,91,91,150,44,89,146,25,51,102,164,174,174,46,27,54,108,232,246,182,27,55,110,204,134,13,27,210,167,79,159,188,241,198,27,93,150,117,206,138,46,190,248,226,140,30,61,58,229,229,
229,41,47,47,63,224,62,59,127,87,236,243,159,255,124,174,188,242,202,46,15,100,116,119,159,238,121,1,124,76,227,181,96,193,130,204,157,59,55,179,103,207,206,166,77,155,14,121,63,141,141,141,233,219,183,
239,94,179,180,206,125,143,31,63,62,63,255,249,207,11,151,24,59,127,47,236,253,188,250,234,171,105,104,104,200,167,63,253,233,244,233,211,39,191,254,245,175,51,126,252,248,15,180,79,0,246,86,212,175,95,
191,14,195,0,64,79,226,83,229,1,16,47,0,16,47,0,16,47,0,196,11,0,196,11,0,196,11,0,241,2,0,241,2,0,241,2,64,188,0,64,188,0,64,188,186,233,103,63,251,89,230,204,153,211,229,181,135,31,126,56,11,22,44,200,
113,199,29,151,250,250,250,76,158,60,121,159,219,94,116,209,69,169,175,175,207,151,191,252,101,103,13,128,120,253,225,44,93,186,52,253,251,247,207,144,33,67,146,36,37,37,37,169,174,174,206,203,47,191,
156,157,59,119,102,233,210,165,121,253,245,215,157,21,0,226,117,248,248,205,111,126,147,36,25,57,114,100,146,228,248,227,143,79,175,94,189,242,210,75,47,229,237,183,223,206,229,151,95,158,7,30,120,192,
89,1,32,94,135,215,204,107,207,120,157,116,210,73,133,168,13,30,60,120,175,203,134,127,249,151,127,153,121,243,230,229,241,199,31,207,137,39,158,216,101,95,167,157,118,90,158,122,234,169,44,92,184,48,
247,222,123,111,6,12,24,144,36,169,173,173,205,191,253,219,191,101,254,252,249,249,201,79,126,82,120,189,184,184,56,215,95,127,125,102,207,158,157,57,115,230,228,186,235,174,243,135,40,1,196,235,192,86,
175,94,157,45,91,182,20,226,213,249,239,206,168,237,169,111,223,190,185,238,186,235,178,121,243,230,204,156,57,51,99,199,142,45,44,43,47,47,207,109,183,221,150,162,162,162,60,249,228,147,25,63,126,124,
174,189,246,218,12,24,48,32,223,251,222,247,178,115,231,206,60,253,244,211,57,243,204,51,243,141,111,124,163,16,181,203,46,187,44,43,87,174,204,156,57,115,242,245,175,127,61,23,92,112,65,170,170,170,50,
109,218,180,76,154,52,201,217,8,208,77,165,61,241,160,75,74,74,210,214,214,118,208,219,117,116,116,228,165,151,94,202,168,81,163,10,51,175,117,235,214,101,195,134,13,25,60,120,112,151,117,171,171,171,
83,94,94,158,199,30,123,44,15,63,252,112,222,121,231,157,252,237,223,254,109,146,100,196,136,17,57,242,200,35,51,117,234,212,60,242,200,35,249,147,63,249,147,140,29,59,54,39,157,116,82,42,42,42,242,216,
99,143,229,103,63,251,89,206,59,239,188,140,25,51,38,73,10,251,255,151,127,249,151,204,154,53,43,239,190,251,110,222,121,231,157,148,149,149,101,212,168,81,89,189,122,181,179,17,224,227,28,175,103,159,
125,54,139,22,45,202,172,89,179,178,112,225,194,52,55,55,119,123,219,165,75,151,230,244,211,79,207,113,199,29,151,234,234,234,204,157,59,119,159,235,117,94,238,219,186,117,235,94,203,6,14,28,152,36,153,
52,105,82,46,189,244,210,84,86,86,166,169,169,41,71,30,121,100,146,164,165,165,37,73,210,212,212,84,216,207,204,153,51,115,229,149,87,230,230,155,111,78,91,91,91,238,186,235,174,194,254,246,156,213,1,
112,96,61,242,178,97,255,254,253,51,97,194,132,252,248,199,63,78,93,93,93,110,187,237,182,156,125,246,217,233,213,171,215,1,183,237,124,104,227,11,95,248,66,122,247,238,93,248,239,189,170,94,250,254,93,
47,43,43,75,146,220,125,247,221,57,255,252,243,115,214,89,103,229,47,254,226,47,246,123,15,107,245,234,213,185,252,242,203,179,97,195,134,252,232,71,63,202,183,191,253,109,103,31,192,39,105,230,181,167,
202,202,202,212,214,214,166,182,182,54,77,77,77,153,63,127,126,166,79,159,158,153,51,103,166,189,189,125,175,245,95,122,233,165,116,116,116,228,172,179,206,42,204,196,246,165,115,246,84,92,188,119,223,
59,103,122,157,203,46,185,228,146,148,151,151,103,253,250,245,251,61,214,21,43,86,228,178,203,46,203,228,201,147,115,229,149,87,102,205,154,53,89,176,96,65,238,184,227,142,204,155,55,47,15,62,248,160,
51,18,224,227,58,243,218,151,246,246,246,44,91,182,44,139,23,47,206,139,47,190,184,207,112,37,201,150,45,91,178,102,205,154,140,27,55,46,45,45,45,121,229,149,87,246,185,222,155,111,190,153,100,247,37,
194,61,173,91,183,46,73,82,85,85,149,36,185,226,138,43,82,91,91,155,205,155,55,119,153,153,85,84,84,100,211,166,77,73,118,221,95,187,249,230,155,211,210,210,146,31,254,240,135,73,146,63,254,227,63,78,
121,121,121,198,140,25,147,97,195,134,57,27,1,62,9,51,175,182,182,182,44,89,178,36,51,102,204,72,93,93,93,54,108,216,208,173,237,150,46,93,154,225,195,135,103,233,210,165,239,123,191,172,161,161,33,27,
55,110,204,5,23,92,144,246,246,246,124,241,139,95,44,44,91,190,124,121,214,175,95,159,137,19,39,166,111,223,190,25,52,104,80,166,79,159,158,223,254,246,183,105,110,110,206,69,23,93,148,33,67,134,164,170,
170,170,240,137,30,197,197,197,249,234,87,191,154,170,170,170,108,223,190,61,73,242,198,27,111,100,237,218,181,238,121,1,124,18,102,94,11,22,44,200,247,191,255,253,156,115,206,57,185,230,154,107,242,248,
227,143,119,59,92,201,238,251,94,239,119,201,176,51,140,127,247,119,127,151,138,138,138,212,214,214,102,197,138,21,93,150,221,116,211,77,217,182,109,91,38,78,156,152,57,115,230,100,234,212,169,217,184,
113,99,38,79,158,156,222,189,123,231,162,139,46,202,252,249,243,115,223,125,247,37,73,94,126,249,229,220,122,235,173,169,169,169,201,23,191,248,197,204,156,57,51,83,167,78,117,6,2,28,130,162,126,253,250,
117,24,6,0,204,188,0,64,188,0,64,188,0,16,47,0,16,47,0,16,47,0,196,11,0,196,11,0,196,11,0,241,2,0,241,2,0,241,2,64,188,62,65,6,15,30,156,250,250,250,212,215,215,231,194,11,47,44,188,126,206,57,231,20,
94,175,169,169,233,214,62,38,79,158,156,36,169,169,169,73,125,125,125,110,184,225,6,3,12,32,94,31,173,234,234,234,194,215,35,70,140,232,246,118,45,45,45,89,186,116,105,94,127,253,117,131,8,240,17,43,53,
4,187,181,182,182,118,153,97,213,212,212,164,181,181,53,165,165,7,30,166,183,223,126,59,151,95,126,185,65,4,48,243,250,240,157,118,218,105,121,234,169,167,178,112,225,194,220,123,239,189,25,48,96,64,97,
217,170,85,171,82,93,93,157,162,162,162,194,44,108,213,170,85,93,182,159,48,97,66,158,121,230,153,204,157,59,55,63,248,193,15,210,187,119,239,36,123,95,54,4,64,188,62,20,229,229,229,185,237,182,219,82,
84,84,148,39,159,124,50,227,199,143,207,181,215,94,91,88,190,114,229,202,84,84,84,100,232,208,161,57,234,168,163,50,104,208,160,52,52,52,20,150,15,27,54,44,183,220,114,75,214,173,91,151,71,31,125,52,231,
159,127,126,174,185,230,154,3,126,223,170,170,170,76,155,54,45,147,38,77,114,198,1,124,82,227,85,82,82,114,72,219,141,24,49,34,71,30,121,100,158,120,226,137,76,153,50,37,107,215,174,205,216,177,99,11,
203,155,155,155,179,122,245,234,212,212,212,164,166,166,38,235,215,175,207,150,45,91,10,203,143,61,246,216,212,215,215,231,254,251,239,207,61,247,220,147,237,219,183,231,148,83,78,57,224,247,45,43,43,
203,168,81,163,50,116,232,80,103,28,192,135,160,71,222,243,122,246,217,103,179,104,209,162,204,154,53,43,11,23,46,76,115,115,115,183,182,27,56,112,96,146,100,210,164,73,185,244,210,75,83,89,89,153,166,
166,166,46,235,52,52,52,164,166,166,38,219,182,109,203,43,175,188,210,101,217,162,69,139,178,104,209,162,84,84,84,228,130,11,46,72,105,105,105,250,244,233,115,192,239,251,31,35,9,192,39,48,94,253,251,
247,207,132,9,19,50,97,194,132,108,223,190,61,207,61,247,92,102,206,156,153,249,243,231,239,21,163,255,56,3,74,146,187,239,190,59,79,60,241,68,225,245,193,131,7,23,190,110,108,108,204,184,113,227,178,
109,219,182,52,54,54,166,178,178,178,203,62,206,56,227,140,220,124,243,205,217,186,117,107,218,219,219,157,65,0,255,11,244,248,123,94,149,149,149,169,173,173,205,148,41,83,82,87,87,151,41,83,166,228,188,
243,206,75,113,241,222,111,173,115,134,214,185,236,146,75,46,201,95,253,213,95,117,89,167,177,177,49,213,213,213,169,174,174,78,99,99,227,94,51,183,59,238,184,35,203,151,47,207,197,23,95,156,157,59,119,
118,123,198,247,208,67,15,229,170,171,174,114,198,1,136,215,110,237,237,237,89,182,108,89,22,47,94,156,23,95,124,113,159,179,162,117,235,214,37,217,245,0,69,146,92,113,197,21,169,173,173,237,178,78,67,
67,67,170,170,170,50,124,248,240,46,15,107,36,201,169,167,158,154,94,189,122,229,153,103,158,233,246,165,202,100,215,131,34,99,198,140,201,176,97,195,156,113,0,31,130,30,253,123,94,109,109,109,89,178,
100,73,102,204,152,145,186,186,186,108,216,176,97,191,235,47,95,190,60,235,215,175,207,196,137,19,211,183,111,223,12,26,52,40,211,167,79,239,178,206,198,141,27,179,97,195,134,244,233,211,39,111,188,241,
70,151,101,157,51,173,139,47,190,56,163,71,143,78,121,121,121,202,203,203,15,120,156,238,121,1,136,87,22,44,88,144,185,115,231,102,246,236,217,217,180,105,211,65,197,238,166,155,110,202,141,55,222,152,
137,19,39,102,206,156,57,153,58,117,234,94,15,93,52,54,54,166,111,223,190,123,205,222,58,191,231,248,241,227,243,243,159,255,188,112,137,177,243,247,194,0,248,195,40,234,215,175,95,135,97,0,160,39,241,
217,134,0,136,23,0,136,23,0,136,23,0,226,5,0,226,5,0,226,5,128,120,1,128,120,1,128,120,1,32,94,0,32,94,0,32,94,0,136,23,0,136,23,0,136,23,0,226,5,0,226,5,0,226,5,0,226,5,128,120,1,128,120,1,128,120,1,
32,94,0,32,94,0,32,94,0,136,23,0,136,23,0,136,23,0,226,5,0,226,5,0,226,5,128,120,1,128,120,1,128,120,1,128,120,1,32,94,0,240,7,80,58,244,83,159,50,10,0,152,121,1,192,71,169,168,119,239,222,29,134,1,0,
51,47,0,16,47,0,16,47,0,196,11,0,196,11,0,196,11,0,241,2,0,241,2,0,241,2,64,188,0,64,188,0,64,188,0,16,47,0,16,47,0,16,47,0,196,11,0,196,11,0,196,11,0,196,11,0,241,2,0,241,2,0,241,2,64,188,0,64,188,0,
64,188,0,16,47,0,16,47,0,16,47,0,196,11,0,196,11,0,196,198,142,68,151,0,0,1,151,73,68,65,84,11,0,241,2,0,241,2,0,241,2,64,188,0,64,188,0,64,188,0,64,188,0,16,47,0,16,47,0,16,47,0,196,11,0,196,11,0,196,
11,0,241,2,0,241,2,0,241,2,64,188,0,64,188,0,64,188,0,16,47,0,16,47,0,16,47,0,16,47,0,196,11,0,196,11,0,196,11,0,241,2,0,241,2,0,241,2,64,188,0,64,188,0,64,188,0,16,47,0,16,47,0,16,47,0,196,11,0,196,11,
0,196,11,0,196,11,0,241,2,0,241,2,0,241,2,64,188,0,64,188,0,64,188,0,16,47,0,16,47,0,16,47,0,196,11,0,196,11,0,196,11,0,241,2,0,241,2,0,241,2,64,188,0,64,188,0,64,188,0,64,188,0,16,47,0,16,47,0,16,47,
0,196,11,0,196,11,0,196,11,0,241,2,0,241,2,0,241,2,64,188,0,64,188,0,64,188,0,16,47,0,16,47,0,16,47,0,16,47,0,196,11,0,196,11,0,196,11,0,241,2,0,241,2,0,241,2,64,188,0,64,188,0,64,188,0,16,47,0,16,47,
0,16,47,0,196,11,0,196,11,0,196,11,0,241,2,0,241,2,0,241,2,0,241,2,64,188,0,64,188,0,64,188,0,16,47,0,16,47,0,16,47,0,196,11,0,196,11,0,196,11,0,241,2,0,241,2,0,241,2,64,188,0,64,188,0,64,188,0,64,188,
0,16,47,0,16,47,0,16,47,0,196,11,0,196,11,0,196,11,0,241,2,0,241,2,0,241,2,64,188,0,64,188,0,64,188,0,16,47,0,16,47,0,16,47,0,16,47,0,196,11,0,196,11,0,196,11,0,241,2,0,241,2,0,241,2,64,188,0,64,188,0,
64,188,0,16,47,0,16,47,0,248,64,254,127,188,226,221,84,178,5,193,241,0,0,0,0,73,69,78,68,174,66,96,130,0,0};

const char* UiEditorAbout::aboutbox_png = (const char*) resource_UiEditorAbout_aboutbox_png;
const int UiEditorAbout::aboutbox_pngSize = 8767;


//[EndFile] You can add extra defines here...
//[/EndFile]

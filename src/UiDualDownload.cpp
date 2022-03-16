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
#include "CoreAudioPlayer.h"
#include "UiEditorFileManager.h"
#include "UiSettings.h"
#include "UiNotificationAnimation.h"
//[/Headers]

#include "UiDualDownload.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
void UiDualDownload::timerCallback()
{
    // UPDATE UI
    data_progress->setValue( _listener->get_data_percentage(), dontSendNotification );
    audio_progress->setValue( _listener->get_audio_percentage(), dontSendNotification );

    data_percent->setText( String(int(_listener->get_data_percentage()*100))+"%", dontSendNotification );
    audio_percent->setText( String(int(_listener->get_audio_percentage()*100))+"%", dontSendNotification );

    bool is_all_complete = _listener->is_complete();
    if( is_all_complete )
    {
        ok->setEnabled(_listener->is_date_success());
        close->setEnabled(is_all_complete);
    }
    cancel_data->setEnabled( ! _listener->is_data_complete() );
    chancel_audio->setEnabled( ! _listener->is_audio_complete() );

    if( is_all_complete )
    {
        bool is_success = _listener->is_success();
        if( _app_instance_store->editor_config.file_manager )
            SHOW_NOTIFICATION( is_success );

        stopTimer();

        if( _listener->perform_done() )
            delete this;
        return;
    }
}
//[/MiscUserDefs]

//==============================================================================
UiDualDownload::UiDualDownload (AppInstanceStore*app_instance_store_, UiDualDownloadListener*const listener_)
    : UiEditor("B-Downloader"),_app_instance_store(app_instance_store_), _listener(listener_)
{
    addAndMakeVisible (ok = new TextButton (String()));
    ok->setExplicitFocusOrder (2);
    ok->setButtonText (TRANS("OK / LOAD PROJECT"));
    ok->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight | Button::ConnectedOnTop | Button::ConnectedOnBottom);
    ok->addListener (this);
    ok->setColour (TextButton::buttonColourId, Colours::black);
    ok->setColour (TextButton::buttonOnColourId, Colour (0x004444ff));
    ok->setColour (TextButton::textColourOnId, Colours::chartreuse);
    ok->setColour (TextButton::textColourOffId, Colours::chartreuse);

    addAndMakeVisible (close = new TextButton (String()));
    close->setExplicitFocusOrder (3);
    close->setButtonText (TRANS("CLOSE"));
    close->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight | Button::ConnectedOnTop | Button::ConnectedOnBottom);
    close->addListener (this);
    close->setColour (TextButton::buttonColourId, Colours::black);
    close->setColour (TextButton::buttonOnColourId, Colour (0x004444ff));
    close->setColour (TextButton::textColourOnId, Colours::cornflowerblue);
    close->setColour (TextButton::textColourOffId, Colours::cornflowerblue);

    addAndMakeVisible (data_progress = new Slider (String()));
    data_progress->setRange (0, 1, 0);
    data_progress->setSliderStyle (Slider::LinearHorizontal);
    data_progress->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    data_progress->setColour (Slider::trackColourId, Colours::aquamarine);
    data_progress->addListener (this);

    addAndMakeVisible (cancel_data = new TextButton (String()));
    cancel_data->setExplicitFocusOrder (2);
    cancel_data->setButtonText (TRANS("CANCEL"));
    cancel_data->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight | Button::ConnectedOnTop | Button::ConnectedOnBottom);
    cancel_data->addListener (this);
    cancel_data->setColour (TextButton::buttonColourId, Colours::black);
    cancel_data->setColour (TextButton::buttonOnColourId, Colour (0x004444ff));
    cancel_data->setColour (TextButton::textColourOnId, Colours::chartreuse);
    cancel_data->setColour (TextButton::textColourOffId, Colours::red);

    addAndMakeVisible (audio_progress = new Slider (String()));
    audio_progress->setRange (0, 1, 0);
    audio_progress->setSliderStyle (Slider::LinearHorizontal);
    audio_progress->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    audio_progress->setColour (Slider::trackColourId, Colours::aquamarine);
    audio_progress->addListener (this);

    addAndMakeVisible (data_info = new Label (String(),
            TRANS("DOWNLOADING DATA FILE:")));
    data_info->setFont (Font ("Oswald", 18.00f, Font::plain));
    data_info->setJustificationType (Justification::centredLeft);
    data_info->setEditable (false, false, false);
    data_info->setColour (Label::textColourId, Colour (GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    data_info->setColour (TextEditor::textColourId, Colours::black);
    data_info->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (data_name = new Label (String(),
            TRANS("XYZ")));
    data_name->setFont (Font ("Oswald", 18.00f, Font::plain));
    data_name->setJustificationType (Justification::centred);
    data_name->setEditable (false, false, false);
    data_name->setColour (Label::textColourId, Colours::aqua);
    data_name->setColour (TextEditor::textColourId, Colours::black);
    data_name->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (old_info_2 = new Label (String(),
            TRANS("After download you will find this project in \"Presets (downloads)\"")));
    old_info_2->setFont (Font ("Oswald", 18.00f, Font::plain));
    old_info_2->setJustificationType (Justification::topLeft);
    old_info_2->setEditable (false, false, false);
    old_info_2->setColour (Label::textColourId, Colours::red);
    old_info_2->setColour (TextEditor::textColourId, Colours::black);
    old_info_2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (old_info_3 = new Label (String(),
            TRANS("NOTE:")));
    old_info_3->setFont (Font ("Oswald", 18.00f, Font::plain));
    old_info_3->setJustificationType (Justification::topLeft);
    old_info_3->setEditable (false, false, false);
    old_info_3->setColour (Label::textColourId, Colours::red);
    old_info_3->setColour (TextEditor::textColourId, Colours::black);
    old_info_3->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (titel7 = new Label (String(),
                                           TRANS("DOWNLOADING FILES TO \"PRESETS (downloads)\"")));
    titel7->setFont (Font ("Oswald", 25.00f, Font::bold));
    titel7->setJustificationType (Justification::centredLeft);
    titel7->setEditable (false, false, false);
    titel7->setColour (Label::textColourId, Colour (GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    titel7->setColour (TextEditor::textColourId, Colours::black);
    titel7->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (chancel_audio = new TextButton (String()));
    chancel_audio->setExplicitFocusOrder (2);
    chancel_audio->setButtonText (TRANS("CANCEL"));
    chancel_audio->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight | Button::ConnectedOnTop | Button::ConnectedOnBottom);
    chancel_audio->addListener (this);
    chancel_audio->setColour (TextButton::buttonColourId, Colours::black);
    chancel_audio->setColour (TextButton::buttonOnColourId, Colour (0x004444ff));
    chancel_audio->setColour (TextButton::textColourOnId, Colours::red);
    chancel_audio->setColour (TextButton::textColourOffId, Colours::red);

    addAndMakeVisible (audio_info = new Label (String(),
            TRANS("DOWNLOADING AUDIO FILE:")));
    audio_info->setFont (Font ("Oswald", 18.00f, Font::plain));
    audio_info->setJustificationType (Justification::centredLeft);
    audio_info->setEditable (false, false, false);
    audio_info->setColour (Label::textColourId, Colour (GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    audio_info->setColour (TextEditor::textColourId, Colours::black);
    audio_info->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (audio_name = new Label (String(),
            TRANS("XYZ")));
    audio_name->setFont (Font ("Oswald", 18.00f, Font::plain));
    audio_name->setJustificationType (Justification::centred);
    audio_name->setEditable (false, false, false);
    audio_name->setColour (Label::textColourId, Colours::aqua);
    audio_name->setColour (TextEditor::textColourId, Colours::black);
    audio_name->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (data_percent = new Label (String(),
            TRANS("0%")));
    data_percent->setFont (Font ("Oswald", 18.00f, Font::plain));
    data_percent->setJustificationType (Justification::centred);
    data_percent->setEditable (false, false, false);
    data_percent->setColour (Label::textColourId, Colours::aqua);
    data_percent->setColour (TextEditor::textColourId, Colours::black);
    data_percent->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (audio_percent = new Label (String(),
            TRANS("0%")));
    audio_percent->setFont (Font ("Oswald", 18.00f, Font::plain));
    audio_percent->setJustificationType (Justification::centred);
    audio_percent->setEditable (false, false, false);
    audio_percent->setColour (Label::textColourId, Colours::aqua);
    audio_percent->setColour (TextEditor::textColourId, Colours::black);
    audio_percent->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (toolbar = new UiEditorToolbar (this, false, true, false));


    //[UserPreSize]
    /*
    project_name->setText(project_name_,dontSendNotification);

    if( ! _listener->get_old_audio_file().existsAsFile() )
    {
      audio_thumb_old->setEnabled(false);
      play_old->setEnabled(false);
      old_info_1->setEnabled(false);
      old_info_2->setEnabled(false);
      old_info_3->setEnabled(false);
    }
    */
    //[/UserPreSize]

    setSize (440, 305);


    //[Constructor] You can add your own custom stuff here..
    center_relative_and_make_visible( reinterpret_cast< Component*const >( _app_instance_store->editor ) );
    //setAlwaysOnTop(true);
    enterModalState( true );
    //[/Constructor]
}

UiDualDownload::~UiDualDownload()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    MessageManagerLock mmLock;
    //[/Destructor_pre]

    ok = nullptr;
    close = nullptr;
    data_progress = nullptr;
    cancel_data = nullptr;
    audio_progress = nullptr;
    data_info = nullptr;
    data_name = nullptr;
    old_info_2 = nullptr;
    old_info_3 = nullptr;
    titel7 = nullptr;
    chancel_audio = nullptr;
    audio_info = nullptr;
    audio_name = nullptr;
    data_percent = nullptr;
    audio_percent = nullptr;
    toolbar = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void UiDualDownload::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    g.setColour (Colour (0xff161616));
    g.fillRect (0, 0, getWidth() - 0, getHeight() - 0);

    g.setColour (Colour (GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    g.drawRect (0, 0, getWidth() - 0, getHeight() - 0, 2);

    //[UserPaint] Add your own custom painting code here..
    ResizableWindow::moved();
    //[/UserPaint]
}

void UiDualDownload::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    ok->setBounds (proportionOfWidth (0.7273f) - proportionOfWidth (0.3182f), proportionOfHeight (0.8525f), proportionOfWidth (0.3182f), proportionOfHeight (0.0820f));
    close->setBounds (proportionOfWidth (0.9546f) - proportionOfWidth (0.2045f), proportionOfHeight (0.8525f), proportionOfWidth (0.2045f), proportionOfHeight (0.0820f));
    data_progress->setBounds (proportionOfWidth (0.0455f), proportionOfHeight (0.2951f), proportionOfWidth (0.7500f), proportionOfHeight (0.0787f));
    cancel_data->setBounds (proportionOfWidth (0.9546f) - proportionOfWidth (0.1364f), proportionOfHeight (0.2951f), proportionOfWidth (0.1364f), proportionOfHeight (0.0820f));
    audio_progress->setBounds (proportionOfWidth (0.0455f), proportionOfHeight (0.5246f), proportionOfWidth (0.7500f), proportionOfHeight (0.0787f));
    data_info->setBounds (proportionOfWidth (0.0455f), proportionOfHeight (0.1803f), proportionOfWidth (0.3409f), proportionOfHeight (0.0984f));
    data_name->setBounds (proportionOfWidth (0.3864f), proportionOfHeight (0.1803f), proportionOfWidth (0.4318f), proportionOfHeight (0.0984f));
    old_info_2->setBounds (proportionOfWidth (0.1364f), proportionOfHeight (0.6885f), proportionOfWidth (0.8182f), proportionOfHeight (0.0984f));
    old_info_3->setBounds (proportionOfWidth (0.0455f), proportionOfHeight (0.6885f), proportionOfWidth (0.0909f), proportionOfHeight (0.0984f));
    titel7->setBounds (proportionOfWidth (0.0455f), proportionOfHeight (0.0328f), proportionOfWidth (0.8000f), proportionOfHeight (0.1312f));
    chancel_audio->setBounds (proportionOfWidth (0.9546f) - proportionOfWidth (0.1364f), proportionOfHeight (0.5246f), proportionOfWidth (0.1364f), proportionOfHeight (0.0820f));
    audio_info->setBounds (proportionOfWidth (0.0455f), proportionOfHeight (0.4098f), proportionOfWidth (0.3409f), proportionOfHeight (0.0984f));
    audio_name->setBounds (proportionOfWidth (0.3864f), proportionOfHeight (0.4098f), proportionOfWidth (0.4318f), proportionOfHeight (0.0984f));
    data_percent->setBounds (proportionOfWidth (0.8409f), proportionOfHeight (0.1803f), proportionOfWidth (0.1136f), proportionOfHeight (0.0984f));
    audio_percent->setBounds (proportionOfWidth (0.8409f), proportionOfHeight (0.4098f), proportionOfWidth (0.1136f), proportionOfHeight (0.0984f));
    toolbar->setBounds (getWidth() - proportionOfWidth (0.1136f), proportionOfHeight (-0.1738f), proportionOfWidth (0.1136f), proportionOfHeight (0.6557f));
    //[UserResized] Add your own custom resize handling here..
    ResizableWindow::resized();
    //[/UserResized]
}

void UiDualDownload::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == ok)
    {
        //[UserButtonCode_ok] -- add your button handler code here..
        _listener->perform_ok();
        delete this;
        //[/UserButtonCode_ok]
    }
    else if (buttonThatWasClicked == close)
    {
        //[UserButtonCode_close] -- add your button handler code here..
        _listener->perform_close();
        delete this;
        //[/UserButtonCode_close]
    }
    else if (buttonThatWasClicked == cancel_data)
    {
        //[UserButtonCode_cancel_data] -- add your button handler code here..
        _listener->chancel_data_download();
        //[/UserButtonCode_cancel_data]
    }
    else if (buttonThatWasClicked == chancel_audio)
    {
        //[UserButtonCode_chancel_audio] -- add your button handler code here..
        _listener->chancel_audio_download();
        //[/UserButtonCode_chancel_audio]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void UiDualDownload::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == data_progress)
    {
        //[UserSliderCode_data_progress] -- add your slider handling code here..
        //[/UserSliderCode_data_progress]
    }
    else if (sliderThatWasMoved == audio_progress)
    {
        //[UserSliderCode_audio_progress] -- add your slider handling code here..
        //[/UserSliderCode_audio_progress]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}




//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="UiDualDownload" componentName=""
                 parentClasses="public UiEditor, public Timer" constructorParams="AppInstanceStore*app_instance_store_, UiDualDownloadListener*const listener_"
                 variableInitialisers="UiEditor(&quot;B-Downloader&quot;),_app_instance_store(app_instance_store_), _listener(listener_)"
                 snapPixels="10" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="440" initialHeight="305">
  <BACKGROUND backgroundColour="ffffffff">
    <RECT pos="0 0 0M 0M" fill="solid: ff161616" hasStroke="1" stroke="2, mitered, butt"
          strokeColour="solid: ffff3b00"/>
  </BACKGROUND>
  <TEXTBUTTON name="" id="ca3c487198c8aedc" memberName="ok" virtualName=""
              explicitFocusOrder="2" pos="72.727%r 85.246% 31.818% 8.197%"
              bgColOff="ff000000" bgColOn="4444ff" textCol="ff7fff00" textColOn="ff7fff00"
              buttonText="OK / LOAD PROJECT" connectedEdges="15" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="" id="6733db43b3f162a6" memberName="close" virtualName=""
              explicitFocusOrder="3" pos="95.455%r 85.246% 20.455% 8.197%"
              bgColOff="ff000000" bgColOn="4444ff" textCol="ff6495ed" textColOn="ff6495ed"
              buttonText="CLOSE" connectedEdges="15" needsCallback="1" radioGroupId="0"/>
  <SLIDER name="" id="66c725f390624925" memberName="data_progress" virtualName=""
          explicitFocusOrder="0" pos="4.545% 29.508% 75% 7.869%" trackcol="ff7fffd4"
          min="0" max="1" int="0" style="LinearHorizontal" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <TEXTBUTTON name="" id="7398184a5468e9a8" memberName="cancel_data" virtualName=""
              explicitFocusOrder="2" pos="95.455%r 29.508% 13.636% 8.197%"
              bgColOff="ff000000" bgColOn="4444ff" textCol="ff7fff00" textColOn="ffff0000"
              buttonText="CANCEL" connectedEdges="15" needsCallback="1" radioGroupId="0"/>
  <SLIDER name="" id="e3e27d63145b9b" memberName="audio_progress" virtualName=""
          explicitFocusOrder="0" pos="4.545% 52.459% 75% 7.869%" trackcol="ff7fffd4"
          min="0" max="1" int="0" style="LinearHorizontal" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="" id="e95009284c62ddb2" memberName="data_info" virtualName=""
         explicitFocusOrder="0" pos="4.545% 18.033% 34.091% 9.836%" textCol="ffff3b00"
         edTextCol="ff000000" edBkgCol="0" labelText="DOWNLOADING DATA FILE:"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Oswald" fontsize="18" bold="0" italic="0" justification="33"/>
  <LABEL name="" id="a5336083f9083049" memberName="data_name" virtualName=""
         explicitFocusOrder="0" pos="38.636% 18.033% 43.182% 9.836%" textCol="ff00ffff"
         edTextCol="ff000000" edBkgCol="0" labelText="XYZ" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Oswald"
         fontsize="18" bold="0" italic="0" justification="36"/>
  <LABEL name="" id="440c9352c749361c" memberName="old_info_2" virtualName=""
         explicitFocusOrder="0" pos="13.636% 68.852% 81.818% 9.836%" textCol="ffff0000"
         edTextCol="ff000000" edBkgCol="0" labelText="After download you will find this project in &quot;Presets (downloads)&quot;"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Oswald" fontsize="18" bold="0" italic="0" justification="9"/>
  <LABEL name="" id="5cfc7980beb0813" memberName="old_info_3" virtualName=""
         explicitFocusOrder="0" pos="4.545% 68.852% 9.091% 9.836%" textCol="ffff0000"
         edTextCol="ff000000" edBkgCol="0" labelText="NOTE:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Oswald"
         fontsize="18" bold="0" italic="0" justification="9"/>
  <LABEL name="" id="bba892cccd5fe810" memberName="titel7" virtualName=""
         explicitFocusOrder="0" pos="4.545% 3.279% 80% 13.115%" textCol="ffff3b00"
         edTextCol="ff000000" edBkgCol="0" labelText="DOWNLOADING FILES TO &quot;PRESETS (downloads)&quot;"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Oswald" fontsize="25" bold="1" italic="0" justification="33"/>
  <TEXTBUTTON name="" id="3ece3d591639661d" memberName="chancel_audio" virtualName=""
              explicitFocusOrder="2" pos="95.455%r 52.459% 13.636% 8.197%"
              bgColOff="ff000000" bgColOn="4444ff" textCol="ffff0000" textColOn="ffff0000"
              buttonText="CANCEL" connectedEdges="15" needsCallback="1" radioGroupId="0"/>
  <LABEL name="" id="a94ebb9afe451bac" memberName="audio_info" virtualName=""
         explicitFocusOrder="0" pos="4.545% 40.984% 34.091% 9.836%" textCol="ffff3b00"
         edTextCol="ff000000" edBkgCol="0" labelText="DOWNLOADING AUDIO FILE:"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Oswald" fontsize="18" bold="0" italic="0" justification="33"/>
  <LABEL name="" id="158dd24433322e1e" memberName="audio_name" virtualName=""
         explicitFocusOrder="0" pos="38.636% 40.984% 43.182% 9.836%" textCol="ff00ffff"
         edTextCol="ff000000" edBkgCol="0" labelText="XYZ" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Oswald"
         fontsize="18" bold="0" italic="0" justification="36"/>
  <LABEL name="" id="c3658c15e6b4f287" memberName="data_percent" virtualName=""
         explicitFocusOrder="0" pos="84.091% 18.033% 11.364% 9.836%" textCol="ff00ffff"
         edTextCol="ff000000" edBkgCol="0" labelText="0%" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Oswald"
         fontsize="18" bold="0" italic="0" justification="36"/>
  <LABEL name="" id="8b6545123b76d66b" memberName="audio_percent" virtualName=""
         explicitFocusOrder="0" pos="84.091% 40.984% 11.364% 9.836%" textCol="ff00ffff"
         edTextCol="ff000000" edBkgCol="0" labelText="0%" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Oswald"
         fontsize="18" bold="0" italic="0" justification="36"/>
  <GENERICCOMPONENT name="" id="b3ecc3f8f99fe16a" memberName="toolbar" virtualName="UiEditorToolbar"
                    explicitFocusOrder="0" pos="0Rr -17.377% 11.364% 65.574%" class="Component"
                    params="this, false, true, false"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

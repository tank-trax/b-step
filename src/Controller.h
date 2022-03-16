/*
  ==============================================================================

    Controller.h
    Created: 18 May 2014 11:29:52am
    Author:  monotomy

  ==============================================================================
*/

#ifndef CONTROLLER_H_INCLUDED
#define CONTROLLER_H_INCLUDED

#include "App.h"
#define HAS_NO_TEXT_VALUE "xX"

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
class UIBase;
class UiButton;
class UISlider;
class ModelBase;
class SourceDetails;
class MidiMappingControllerPeer;
class AppStyle;
class AppInstanceStore;
class SliderWrapper;

class MONO_Controller
{
    friend class MidiMappingControllerPeer;
    friend class UiButton;
    friend class UISlider;
    friend class ModelBase;

protected:
    ModelBase* _model;
    AppInstanceStore*const _app_instance_store;
private:
    void set_model( ModelBase* model_ );

    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // CONFIG
protected:
    enum UI_VIEW_TYPES
    {
        UI_BUTTON,
        UI_SLIDER,
        UI_LABEL,

        UI_UNDEFINED
    };
private:
    virtual UI_VIEW_TYPES get_view_type() = 0;
    virtual bool is_rect_style_else_fill_area() const {
        return true;
    }

    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // VALUE, SETUP COMUNICATION
private:
    friend class SliderWrapper;
    virtual bool on_pre_mouse_down_escape(const MouseEvent&);
    virtual void on_mouse_down(const MouseEvent&) {}
    virtual void on_mouse_up(const MouseEvent&) {}
    virtual void on_mouse_move (const MouseEvent&) {}
    virtual void on_mouse_enter (const MouseEvent&) {}
    virtual void on_mouse_exit (const MouseEvent&) {}
    virtual void on_mouse_drag (const MouseEvent&) {}
    virtual void on_mouse_double_click (const MouseEvent&) {}
    virtual void on_mouse_wheel_move (const MouseEvent&, const MouseWheelDetails&) {}
    virtual void on_trigger_click() {}
    void on_clicked(bool do_realy_click_ = true);
    virtual bool is_click_blocked() {
        return false;
    }
    virtual void handle_blocked_click() {}
    virtual void on_clicked_top() {}

    // MULTI DRAG
    virtual void on_long_mouse_down();
    virtual bool use_default_multi_drag() {
        return false;
    }
    
public:
    virtual void on_param_via_changed() const {}
private:
#define USE_DEFAULT_MULTI_DRAG \
    bool use_default_multi_drag() override { \
        return true; \
    }
    virtual bool should_start_multi_drag();
public:
    virtual const char* get_controller_type_ident() const = 0;

    String _no_conroller;
    virtual const String& get_controller_name() const {
        return _no_conroller;
    }
private:
    virtual int get_range_max() = 0;
    virtual int get_range_min() = 0;

    // DRAG'N'DROP
    virtual bool is_interested_in_drag_source ( const DragAndDropTarget::SourceDetails& dragSourceDetails_ );
    void item_dropped ( const DragAndDropTarget::SourceDetails& dragSourceDetails_ );
    virtual void item_dropped_top ( const DragAndDropTarget::SourceDetails& ) {}
    virtual bool are_you_rubberable() {
        return false;
    }
    virtual void rubber_droped() {}
    virtual const String get_help_url();
    virtual bool are_you_simple_dragable() {
        return false;
    }

    String _dragNdrop_ident;
    virtual String& get_dragNdrop_ident() {
        return _dragNdrop_ident;
    }
    String _multidrag_ident;
    virtual String& get_multi_dragNdrop_ident() {
        return _multidrag_ident;
    };
    virtual Component* get_dragNdrop_source() {
        return nullptr;
    }

protected:
    virtual void on_value_changed( int ) {}
public:
    virtual int get_value() const {
        return 0;
    };
    void get_label_text( String& string_ ) const;
    virtual void get_label_text_top( String& string_ ) const {
        string_ = String(HAS_NO_TEXT_VALUE);
    };
    virtual bool do_you_need_a_text_popup() {
        return false;
    }
    virtual bool paint_popup_above() const {
        return true;
    }

    virtual AppStyle* get_custom_label_style() const {
        return nullptr;
    }
private:

    // IMAGE BUTTON THINGS ONLY
    virtual const Image* get_current_image() {
        return nullptr;
    }
    virtual const Drawable* get_current_drawable() {
        return nullptr;
    }

    // STYLE THINGS
    friend class UIBase;
    // return true if there are some changes
    virtual void prepare_current_ui_states() {}
    uint32 get_current_color_low();
#define IS_NOT_MIDI_LEARNABLE \
    bool is_learnable() const override { \
    return false; \
    }

    virtual bool using_caching() const {
        return true;
    }

protected:
    virtual bool is_learnable() const {
        return true;
    }
public:
    virtual uint32 get_current_color() const = 0;
    virtual void setup_view( void*const ) {};

public:
    const Component* get_ui_peer() const;
    const ModelBase* get_model() const;
    virtual PodParameterBase* get_parameter() const {
        return nullptr;
    }
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // MIDI COMUNICATION MIDI -> CONTROLLER
public:
    enum MIDI_HANDLE_TYPES
    {
        BUTTON_TOGGLE,
        PERCENTAGE_VALUE,

        HAS_OWN_IMPL,

        HAS_NO_IMPL
    };
    virtual MIDI_HANDLE_TYPES get_midi_handling_type() const {
        return HAS_NO_IMPL;
    };

protected:
    MONO_Controller( AppInstanceStore*const app_instance_store_ );

public:
    virtual ~MONO_Controller() {};

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MONO_Controller)
};
// IDENT TO CHECK IF IT IS A MULTIDRAG
struct MultidragSource : public Component
{
    Array< MONO_Controller* > alreay_handled_controllers;
    int source_state;
    const char*const controller_type_ident;
    const MONO_Controller* controller;

    bool is_drag_started;

    MultidragSource( const char*const controller_type_ident_, const MONO_Controller*const controller_ )
        : source_state(0),
          controller_type_ident( controller_type_ident_ ),
          controller( controller_ ),
          is_drag_started( false )
    {
    }

    ~MultidragSource() {
        OUT( "DELETE MULTIDRAG SOURCE ");
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MultidragSource)
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
class ModelBase : public Component
{
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------

    // PROPERTIES
private:
    UIBase* _view;
    friend class UiButton;
    friend class UISlider;
    friend class UiLabel;

    MONO_Controller* _controller;
    AppStyle* _style;
    AppStyle* _background_style;
    uint32 _background_color;
    bool should_repaint;
public:
    Image& get_drag_image( Image& ) const;
private:
    bool _is_manual_opaque;

    MONO_Controller::UI_VIEW_TYPES _current_view_type;

    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------

    //// CTORS
public:
    ModelBase( MONO_Controller*const controller_ = nullptr, AppStyle*const style_ = nullptr );
    ~ModelBase();

    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------

private:
    void resized() override;
public:
    void get_components_to_repaint( Array< Component* >& components_to_repaint_ );
    void get_controllers_for_paint_popup( Array< MONO_Controller* >& controllers_for_popup_ );

    void set_controller( MONO_Controller*const controller_ );
private:
    void setup_view();
    void delete_view();
    void set_view( UIBase*const ui_element_ );

public:
    void set_style( AppStyle*const style_ );
    void set_background_style( AppStyle*const style_ );
    void set_manual_opaque( bool state_ );

private:
    void refresh_background();
    void paint( Graphics& g_ ) override;

public:
    AppStyle* get_style() const;
    Component* get_view();
    const MONO_Controller* get_controller() const;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ModelBase)
};

#endif  // CONTROLLER_H_INCLUDED


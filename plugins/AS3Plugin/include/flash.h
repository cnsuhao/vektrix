/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is [Open Source Virtual Machine].
 *
 * The Initial Developer of the Original Code is
 * Adobe System Incorporated.
 * Portions created by the Initial Developer are Copyright (C) 2008
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *   Adobe AS3 Team
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */

/* machine generated file -- do not edit */

#define AVMTHUNK_VERSION 5

namespace avmplus {
    class String; //String
}

namespace vtx { namespace as3 {
    class DisplayObject; //flash.display::DisplayObject
    class DisplayObjectClass; //flash.display::DisplayObject$
    class DisplayObjectContainer; //flash.display::DisplayObjectContainer
    class DisplayObjectContainerClass; //flash.display::DisplayObjectContainer$
    class Event; //flash.events::Event
    class EventClass; //flash.events::Event$
    class EventDispatcher; //flash.events::EventDispatcher
    class EventDispatcherClass; //flash.events::EventDispatcher$
    class EventHandler; //vektrix::EventHandler
    class EventHandlerClass; //vektrix::EventHandler$
    class InteractiveObject; //flash.display::InteractiveObject
    class InteractiveObjectClass; //flash.display::InteractiveObject$
    class MovieClip; //flash.display::MovieClip
    class MovieClipClass; //flash.display::MovieClip$
    class SimpleButton; //flash.display::SimpleButton
    class SimpleButtonClass; //flash.display::SimpleButton$
    class Sprite; //flash.display::Sprite
    class SpriteClass; //flash.display::Sprite$
    class StaticText; //flash.text::StaticText
    class StaticTextClass; //flash.text::StaticText$
    class TextField; //flash.text::TextField
    class TextFieldClass; //flash.text::TextField$
} }

namespace avmplus { namespace NativeID {

extern const uint32_t flash_abc_class_count;
extern const uint32_t flash_abc_script_count;
extern const uint32_t flash_abc_method_count;
extern const uint32_t flash_abc_length;
extern const uint8_t flash_abc_data[];
AVMTHUNK_DECLARE_NATIVE_INITIALIZER(flash)

/* classes */
const uint32_t abcclass_flash_display_IBitmapDrawable = 0;
const uint32_t abcclass_flash_events_Event = 1;
const uint32_t abcclass_flash_events_IEventDispatcher = 2;
const uint32_t abcclass_vektrix_EventHandler = 3;
const uint32_t abcclass_flash_events_FocusEvent = 4;
const uint32_t abcclass_flash_events_MouseEvent = 5;
const uint32_t abcclass_flash_events_EventDispatcher = 6;
const uint32_t abcclass_flash_display_DisplayObject = 7;
const uint32_t abcclass_flash_media_Camera = 8;
const uint32_t abcclass_flash_net_LocalConnection = 9;
const uint32_t abcclass_flash_net_NetConnection = 10;
const uint32_t abcclass_flash_net_NetStream = 11;
const uint32_t abcclass_flash_net_SharedObject = 12;
const uint32_t abcclass_flash_net_Socket = 13;
const uint32_t abcclass_flash_display_InteractiveObject = 14;
const uint32_t abcclass_flash_media_Video = 15;
const uint32_t abcclass_flash_text_StaticText = 16;
const uint32_t abcclass_flash_display_DisplayObjectContainer = 17;
const uint32_t abcclass_flash_display_SimpleButton = 18;
const uint32_t abcclass_flash_text_TextField = 19;
const uint32_t abcclass_flash_display_Sprite = 20;
const uint32_t abcclass_flash_display_MovieClip = 21;

/* methods */
const uint32_t vektrix_EventHandler_add = 31;
const uint32_t vektrix_EventHandler_handle = 32;
const uint32_t flash_events_EventDispatcher_addEventListener = 45;
const uint32_t flash_events_EventDispatcher_dispatchEvent = 46;
const uint32_t flash_display_DisplayObject_x_get = 52;
const uint32_t flash_display_DisplayObject_x_set = 53;
const uint32_t flash_display_DisplayObject_y_get = 54;
const uint32_t flash_display_DisplayObject_y_set = 55;
const uint32_t flash_display_DisplayObject_rotation_get = 56;
const uint32_t flash_display_DisplayObject_rotation_set = 57;
const uint32_t flash_display_DisplayObject_scaleX_get = 58;
const uint32_t flash_display_DisplayObject_scaleX_set = 59;
const uint32_t flash_display_DisplayObject_scaleY_get = 60;
const uint32_t flash_display_DisplayObject_scaleY_set = 61;
const uint32_t flash_text_StaticText_text_get = 135;
const uint32_t flash_text_TextField_htmlText_get = 146;
const uint32_t flash_text_TextField_htmlText_set = 147;
const uint32_t flash_text_TextField_getLineIndexAtPoint = 148;
const uint32_t flash_text_TextField_setSelection = 149;

extern AvmBox vektrix_EventHandler_add_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
extern AvmBox vektrix_EventHandler_handle_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
extern AvmBox flash_events_EventDispatcher_addEventListener_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
extern AvmBox flash_events_EventDispatcher_dispatchEvent_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
extern double flash_display_DisplayObject_x_get_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
extern AvmBox flash_display_DisplayObject_x_set_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
extern double flash_display_DisplayObject_y_get_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
extern AvmBox flash_display_DisplayObject_y_set_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
extern double flash_display_DisplayObject_rotation_get_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
extern AvmBox flash_display_DisplayObject_rotation_set_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
extern double flash_display_DisplayObject_scaleX_get_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
extern AvmBox flash_display_DisplayObject_scaleX_set_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
extern double flash_display_DisplayObject_scaleY_get_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
extern AvmBox flash_display_DisplayObject_scaleY_set_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
extern AvmBox flash_text_StaticText_text_get_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
extern AvmBox flash_text_TextField_htmlText_get_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
extern AvmBox flash_text_TextField_htmlText_set_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
extern AvmBox flash_text_TextField_getLineIndexAtPoint_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
extern AvmBox flash_text_TextField_setSelection_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);

#ifdef VMCFG_INDIRECT_NATIVE_THUNKS

extern AvmBox flash_v2a_od_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_display_DisplayObject_scaleY_set_thunk  flash_v2a_od_thunk
#define flash_display_DisplayObject_y_set_thunk  flash_v2a_od_thunk
#define flash_display_DisplayObject_scaleX_set_thunk  flash_v2a_od_thunk
#define flash_display_DisplayObject_rotation_set_thunk  flash_v2a_od_thunk
#define flash_display_DisplayObject_x_set_thunk  flash_v2a_od_thunk

extern AvmBox flash_v2a_osobib_optbfalse_opti0_optbfalse_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_events_EventDispatcher_addEventListener_thunk  flash_v2a_osobib_optbfalse_opti0_optbfalse_thunk

extern AvmBox flash_v2a_oo_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define vektrix_EventHandler_handle_thunk  flash_v2a_oo_thunk

extern AvmBox flash_b2a_oo_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_events_EventDispatcher_dispatchEvent_thunk  flash_b2a_oo_thunk

extern AvmBox flash_i2a_odd_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_text_TextField_getLineIndexAtPoint_thunk  flash_i2a_odd_thunk

extern AvmBox flash_v2a_os_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_text_TextField_htmlText_set_thunk  flash_v2a_os_thunk

extern AvmBox flash_v2a_oii_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_text_TextField_setSelection_thunk  flash_v2a_oii_thunk

extern AvmBox flash_s2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_text_TextField_htmlText_get_thunk  flash_s2a_o_thunk
#define flash_text_StaticText_text_get_thunk  flash_s2a_o_thunk

extern AvmBox flash_i2a_oii_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define vektrix_EventHandler_add_thunk  flash_i2a_oii_thunk

extern double flash_d2d_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_display_DisplayObject_rotation_get_thunk  flash_d2d_o_thunk
#define flash_display_DisplayObject_x_get_thunk  flash_d2d_o_thunk
#define flash_display_DisplayObject_scaleX_get_thunk  flash_d2d_o_thunk
#define flash_display_DisplayObject_scaleY_get_thunk  flash_d2d_o_thunk
#define flash_display_DisplayObject_y_get_thunk  flash_d2d_o_thunk

#endif // VMCFG_INDIRECT_NATIVE_THUNKS

class SlotOffsetsAndAsserts;
// flash.events::Event$
//-----------------------------------------------------------
class _vtx_as3_EventClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
    REALLY_INLINE AvmString get_ACTIVATE() const { return m_ACTIVATE; }
    REALLY_INLINE AvmString get_ADDED() const { return m_ADDED; }
    REALLY_INLINE AvmString get_ADDED_TO_STAGE() const { return m_ADDED_TO_STAGE; }
    REALLY_INLINE AvmString get_CANCEL() const { return m_CANCEL; }
    REALLY_INLINE AvmString get_CHANGE() const { return m_CHANGE; }
    REALLY_INLINE AvmString get_CLEAR() const { return m_CLEAR; }
    REALLY_INLINE AvmString get_CLOSE() const { return m_CLOSE; }
    REALLY_INLINE AvmString get_CLOSING() const { return m_CLOSING; }
    REALLY_INLINE AvmString get_COMPLETE() const { return m_COMPLETE; }
    REALLY_INLINE AvmString get_CONNECT() const { return m_CONNECT; }
    REALLY_INLINE AvmString get_COPY() const { return m_COPY; }
    REALLY_INLINE AvmString get_CUT() const { return m_CUT; }
    REALLY_INLINE AvmString get_DEACTIVATE() const { return m_DEACTIVATE; }
    REALLY_INLINE AvmString get_DISPLAYING() const { return m_DISPLAYING; }
    REALLY_INLINE AvmString get_ENTER_FRAME() const { return m_ENTER_FRAME; }
    REALLY_INLINE AvmString get_EXIT_FRAME() const { return m_EXIT_FRAME; }
    REALLY_INLINE AvmString get_EXITING() const { return m_EXITING; }
    REALLY_INLINE AvmString get_FRAME_CONSTRUCTED() const { return m_FRAME_CONSTRUCTED; }
    REALLY_INLINE AvmString get_FULLSCREEN() const { return m_FULLSCREEN; }
    REALLY_INLINE AvmString get_HTML_BOUNDS_CHANGE() const { return m_HTML_BOUNDS_CHANGE; }
    REALLY_INLINE AvmString get_HTML_DOM_INITIALIZE() const { return m_HTML_DOM_INITIALIZE; }
    REALLY_INLINE AvmString get_HTML_RENDER() const { return m_HTML_RENDER; }
    REALLY_INLINE AvmString get_ID3() const { return m_ID3; }
    REALLY_INLINE AvmString get_INIT() const { return m_INIT; }
    REALLY_INLINE AvmString get_LOCATION_CHANGE() const { return m_LOCATION_CHANGE; }
    REALLY_INLINE AvmString get_MOUSE_LEAVE() const { return m_MOUSE_LEAVE; }
    REALLY_INLINE AvmString get_NETWORK_CHANGE() const { return m_NETWORK_CHANGE; }
    REALLY_INLINE AvmString get_OPEN() const { return m_OPEN; }
    REALLY_INLINE AvmString get_PASTE() const { return m_PASTE; }
    REALLY_INLINE AvmString get_REMOVED() const { return m_REMOVED; }
    REALLY_INLINE AvmString get_REMOVED_FROM_STAGE() const { return m_REMOVED_FROM_STAGE; }
    REALLY_INLINE AvmString get_RENDER() const { return m_RENDER; }
    REALLY_INLINE AvmString get_RESIZE() const { return m_RESIZE; }
    REALLY_INLINE AvmString get_SAMPLE_DATA() const { return m_SAMPLE_DATA; }
    REALLY_INLINE AvmString get_SCROLL() const { return m_SCROLL; }
    REALLY_INLINE AvmString get_SELECT() const { return m_SELECT; }
    REALLY_INLINE AvmString get_SELECT_ALL() const { return m_SELECT_ALL; }
    REALLY_INLINE AvmString get_SOUND_COMPLETE() const { return m_SOUND_COMPLETE; }
    REALLY_INLINE AvmString get_TAB_CHILDREN_CHANGE() const { return m_TAB_CHILDREN_CHANGE; }
    REALLY_INLINE AvmString get_TAB_ENABLED_CHANGE() const { return m_TAB_ENABLED_CHANGE; }
    REALLY_INLINE AvmString get_TAB_INDEX_CHANGE() const { return m_TAB_INDEX_CHANGE; }
    REALLY_INLINE AvmString get_UNLOAD() const { return m_UNLOAD; }
    REALLY_INLINE AvmString get_USER_IDLE() const { return m_USER_IDLE; }
    REALLY_INLINE AvmString get_USER_PRESENT() const { return m_USER_PRESENT; }
private:
    DRCWB(AvmString) m_ACTIVATE;
    DRCWB(AvmString) m_ADDED;
    DRCWB(AvmString) m_ADDED_TO_STAGE;
    DRCWB(AvmString) m_CANCEL;
    DRCWB(AvmString) m_CHANGE;
    DRCWB(AvmString) m_CLEAR;
    DRCWB(AvmString) m_CLOSE;
    DRCWB(AvmString) m_CLOSING;
    DRCWB(AvmString) m_COMPLETE;
    DRCWB(AvmString) m_CONNECT;
    DRCWB(AvmString) m_COPY;
    DRCWB(AvmString) m_CUT;
    DRCWB(AvmString) m_DEACTIVATE;
    DRCWB(AvmString) m_DISPLAYING;
    DRCWB(AvmString) m_ENTER_FRAME;
    DRCWB(AvmString) m_EXIT_FRAME;
    DRCWB(AvmString) m_EXITING;
    DRCWB(AvmString) m_FRAME_CONSTRUCTED;
    DRCWB(AvmString) m_FULLSCREEN;
    DRCWB(AvmString) m_HTML_BOUNDS_CHANGE;
    DRCWB(AvmString) m_HTML_DOM_INITIALIZE;
    DRCWB(AvmString) m_HTML_RENDER;
    DRCWB(AvmString) m_ID3;
    DRCWB(AvmString) m_INIT;
    DRCWB(AvmString) m_LOCATION_CHANGE;
    DRCWB(AvmString) m_MOUSE_LEAVE;
    DRCWB(AvmString) m_NETWORK_CHANGE;
    DRCWB(AvmString) m_OPEN;
    DRCWB(AvmString) m_PASTE;
    DRCWB(AvmString) m_REMOVED;
    DRCWB(AvmString) m_REMOVED_FROM_STAGE;
    DRCWB(AvmString) m_RENDER;
    DRCWB(AvmString) m_RESIZE;
    DRCWB(AvmString) m_SAMPLE_DATA;
    DRCWB(AvmString) m_SCROLL;
    DRCWB(AvmString) m_SELECT;
    DRCWB(AvmString) m_SELECT_ALL;
    DRCWB(AvmString) m_SOUND_COMPLETE;
    DRCWB(AvmString) m_TAB_CHILDREN_CHANGE;
    DRCWB(AvmString) m_TAB_ENABLED_CHANGE;
    DRCWB(AvmString) m_TAB_INDEX_CHANGE;
    DRCWB(AvmString) m_UNLOAD;
    DRCWB(AvmString) m_USER_IDLE;
    DRCWB(AvmString) m_USER_PRESENT;
};
#define DECLARE_SLOTS_EventClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
    protected: \
        REALLY_INLINE AvmString get_ACTIVATE() const { return m_slots_EventClass.get_ACTIVATE(); } \
        REALLY_INLINE AvmString get_ADDED() const { return m_slots_EventClass.get_ADDED(); } \
        REALLY_INLINE AvmString get_ADDED_TO_STAGE() const { return m_slots_EventClass.get_ADDED_TO_STAGE(); } \
        REALLY_INLINE AvmString get_CANCEL() const { return m_slots_EventClass.get_CANCEL(); } \
        REALLY_INLINE AvmString get_CHANGE() const { return m_slots_EventClass.get_CHANGE(); } \
        REALLY_INLINE AvmString get_CLEAR() const { return m_slots_EventClass.get_CLEAR(); } \
        REALLY_INLINE AvmString get_CLOSE() const { return m_slots_EventClass.get_CLOSE(); } \
        REALLY_INLINE AvmString get_CLOSING() const { return m_slots_EventClass.get_CLOSING(); } \
        REALLY_INLINE AvmString get_COMPLETE() const { return m_slots_EventClass.get_COMPLETE(); } \
        REALLY_INLINE AvmString get_CONNECT() const { return m_slots_EventClass.get_CONNECT(); } \
        REALLY_INLINE AvmString get_COPY() const { return m_slots_EventClass.get_COPY(); } \
        REALLY_INLINE AvmString get_CUT() const { return m_slots_EventClass.get_CUT(); } \
        REALLY_INLINE AvmString get_DEACTIVATE() const { return m_slots_EventClass.get_DEACTIVATE(); } \
        REALLY_INLINE AvmString get_DISPLAYING() const { return m_slots_EventClass.get_DISPLAYING(); } \
        REALLY_INLINE AvmString get_ENTER_FRAME() const { return m_slots_EventClass.get_ENTER_FRAME(); } \
        REALLY_INLINE AvmString get_EXIT_FRAME() const { return m_slots_EventClass.get_EXIT_FRAME(); } \
        REALLY_INLINE AvmString get_EXITING() const { return m_slots_EventClass.get_EXITING(); } \
        REALLY_INLINE AvmString get_FRAME_CONSTRUCTED() const { return m_slots_EventClass.get_FRAME_CONSTRUCTED(); } \
        REALLY_INLINE AvmString get_FULLSCREEN() const { return m_slots_EventClass.get_FULLSCREEN(); } \
        REALLY_INLINE AvmString get_HTML_BOUNDS_CHANGE() const { return m_slots_EventClass.get_HTML_BOUNDS_CHANGE(); } \
        REALLY_INLINE AvmString get_HTML_DOM_INITIALIZE() const { return m_slots_EventClass.get_HTML_DOM_INITIALIZE(); } \
        REALLY_INLINE AvmString get_HTML_RENDER() const { return m_slots_EventClass.get_HTML_RENDER(); } \
        REALLY_INLINE AvmString get_ID3() const { return m_slots_EventClass.get_ID3(); } \
        REALLY_INLINE AvmString get_INIT() const { return m_slots_EventClass.get_INIT(); } \
        REALLY_INLINE AvmString get_LOCATION_CHANGE() const { return m_slots_EventClass.get_LOCATION_CHANGE(); } \
        REALLY_INLINE AvmString get_MOUSE_LEAVE() const { return m_slots_EventClass.get_MOUSE_LEAVE(); } \
        REALLY_INLINE AvmString get_NETWORK_CHANGE() const { return m_slots_EventClass.get_NETWORK_CHANGE(); } \
        REALLY_INLINE AvmString get_OPEN() const { return m_slots_EventClass.get_OPEN(); } \
        REALLY_INLINE AvmString get_PASTE() const { return m_slots_EventClass.get_PASTE(); } \
        REALLY_INLINE AvmString get_REMOVED() const { return m_slots_EventClass.get_REMOVED(); } \
        REALLY_INLINE AvmString get_REMOVED_FROM_STAGE() const { return m_slots_EventClass.get_REMOVED_FROM_STAGE(); } \
        REALLY_INLINE AvmString get_RENDER() const { return m_slots_EventClass.get_RENDER(); } \
        REALLY_INLINE AvmString get_RESIZE() const { return m_slots_EventClass.get_RESIZE(); } \
        REALLY_INLINE AvmString get_SAMPLE_DATA() const { return m_slots_EventClass.get_SAMPLE_DATA(); } \
        REALLY_INLINE AvmString get_SCROLL() const { return m_slots_EventClass.get_SCROLL(); } \
        REALLY_INLINE AvmString get_SELECT() const { return m_slots_EventClass.get_SELECT(); } \
        REALLY_INLINE AvmString get_SELECT_ALL() const { return m_slots_EventClass.get_SELECT_ALL(); } \
        REALLY_INLINE AvmString get_SOUND_COMPLETE() const { return m_slots_EventClass.get_SOUND_COMPLETE(); } \
        REALLY_INLINE AvmString get_TAB_CHILDREN_CHANGE() const { return m_slots_EventClass.get_TAB_CHILDREN_CHANGE(); } \
        REALLY_INLINE AvmString get_TAB_ENABLED_CHANGE() const { return m_slots_EventClass.get_TAB_ENABLED_CHANGE(); } \
        REALLY_INLINE AvmString get_TAB_INDEX_CHANGE() const { return m_slots_EventClass.get_TAB_INDEX_CHANGE(); } \
        REALLY_INLINE AvmString get_UNLOAD() const { return m_slots_EventClass.get_UNLOAD(); } \
        REALLY_INLINE AvmString get_USER_IDLE() const { return m_slots_EventClass.get_USER_IDLE(); } \
        REALLY_INLINE AvmString get_USER_PRESENT() const { return m_slots_EventClass.get_USER_PRESENT(); } \
    private: \
        avmplus::NativeID::_vtx_as3_EventClassSlots m_slots_EventClass
//-----------------------------------------------------------

// flash.events::Event
//-----------------------------------------------------------
class _vtx_as3_EventSlots
{
    friend class SlotOffsetsAndAsserts;
public:
    REALLY_INLINE AvmBool32 get_flash_events_Event_mBubbles() const { return m_flash_events_Event_mBubbles; }
    void set_flash_events_Event_mBubbles(AvmBool32 newVal);
    REALLY_INLINE AvmBool32 get_flash_events_Event_mCancelable() const { return m_flash_events_Event_mCancelable; }
    void set_flash_events_Event_mCancelable(AvmBool32 newVal);
    REALLY_INLINE AvmString get_flash_events_Event_mType() const { return m_flash_events_Event_mType; }
    void set_flash_events_Event_mType(::vtx::as3::Event* obj, AvmString newVal);
    REALLY_INLINE ::vtx::as3::EventDispatcher* get_flash_events_Event_mEventDispatcher() const { return m_flash_events_Event_mEventDispatcher; }
    void set_flash_events_Event_mEventDispatcher(::vtx::as3::Event* obj, ::vtx::as3::EventDispatcher* newVal);
private:
    AvmBool32 m_flash_events_Event_mBubbles;
    AvmBool32 m_flash_events_Event_mCancelable;
    DRCWB(AvmString) m_flash_events_Event_mType;
    DRCWB(::vtx::as3::EventDispatcher*) m_flash_events_Event_mEventDispatcher;
};
REALLY_INLINE void _vtx_as3_EventSlots::set_flash_events_Event_mBubbles(AvmBool32 newVal) { m_flash_events_Event_mBubbles = newVal; }
REALLY_INLINE void _vtx_as3_EventSlots::set_flash_events_Event_mCancelable(AvmBool32 newVal) { m_flash_events_Event_mCancelable = newVal; }
REALLY_INLINE void _vtx_as3_EventSlots::set_flash_events_Event_mType(::vtx::as3::Event* obj, AvmString newVal)
{
    m_flash_events_Event_mType.set(((ScriptObject*)obj)->gc(), obj, newVal);
}
REALLY_INLINE void _vtx_as3_EventSlots::set_flash_events_Event_mEventDispatcher(::vtx::as3::Event* obj, ::vtx::as3::EventDispatcher* newVal)
{
    m_flash_events_Event_mEventDispatcher.set(((ScriptObject*)obj)->gc(), obj, newVal);
}
#define DECLARE_SLOTS_Event \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
    protected: \
        REALLY_INLINE AvmBool32 get_flash_events_Event_mBubbles() const { return m_slots_Event.get_flash_events_Event_mBubbles(); } \
        REALLY_INLINE void set_flash_events_Event_mBubbles(AvmBool32 newVal) { m_slots_Event.set_flash_events_Event_mBubbles(newVal); } \
        REALLY_INLINE AvmBool32 get_flash_events_Event_mCancelable() const { return m_slots_Event.get_flash_events_Event_mCancelable(); } \
        REALLY_INLINE void set_flash_events_Event_mCancelable(AvmBool32 newVal) { m_slots_Event.set_flash_events_Event_mCancelable(newVal); } \
        REALLY_INLINE AvmString get_flash_events_Event_mType() const { return m_slots_Event.get_flash_events_Event_mType(); } \
        REALLY_INLINE void set_flash_events_Event_mType(AvmString newVal) { m_slots_Event.set_flash_events_Event_mType(this, newVal); } \
        REALLY_INLINE ::vtx::as3::EventDispatcher* get_flash_events_Event_mEventDispatcher() const { return m_slots_Event.get_flash_events_Event_mEventDispatcher(); } \
        REALLY_INLINE void set_flash_events_Event_mEventDispatcher(::vtx::as3::EventDispatcher* newVal) { m_slots_Event.set_flash_events_Event_mEventDispatcher(this, newVal); } \
    private: \
        avmplus::NativeID::_vtx_as3_EventSlots m_slots_Event
//-----------------------------------------------------------

// vektrix::EventHandler$
//-----------------------------------------------------------
class _vtx_as3_EventHandlerClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_EventHandlerClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::_vtx_as3_EventHandlerClassSlots EmptySlotsStruct_EventHandlerClass
//-----------------------------------------------------------

// vektrix::EventHandler
//-----------------------------------------------------------
class _vtx_as3_EventHandlerSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_EventHandler \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::_vtx_as3_EventHandlerSlots EmptySlotsStruct_EventHandler
//-----------------------------------------------------------

// flash.events::EventDispatcher$
//-----------------------------------------------------------
class _vtx_as3_EventDispatcherClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_EventDispatcherClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::_vtx_as3_EventDispatcherClassSlots EmptySlotsStruct_EventDispatcherClass
//-----------------------------------------------------------

// flash.events::EventDispatcher
//-----------------------------------------------------------
class _vtx_as3_EventDispatcherSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_EventDispatcher \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::_vtx_as3_EventDispatcherSlots EmptySlotsStruct_EventDispatcher
//-----------------------------------------------------------

// flash.display::DisplayObject$
//-----------------------------------------------------------
class _vtx_as3_DisplayObjectClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_DisplayObjectClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::_vtx_as3_DisplayObjectClassSlots EmptySlotsStruct_DisplayObjectClass
//-----------------------------------------------------------

// flash.display::DisplayObject
//-----------------------------------------------------------
class _vtx_as3_DisplayObjectSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_DisplayObject \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::_vtx_as3_DisplayObjectSlots EmptySlotsStruct_DisplayObject
//-----------------------------------------------------------

// flash.display::InteractiveObject$
//-----------------------------------------------------------
class _vtx_as3_InteractiveObjectClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_InteractiveObjectClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::_vtx_as3_InteractiveObjectClassSlots EmptySlotsStruct_InteractiveObjectClass
//-----------------------------------------------------------

// flash.display::InteractiveObject
//-----------------------------------------------------------
class _vtx_as3_InteractiveObjectSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_InteractiveObject \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::_vtx_as3_InteractiveObjectSlots EmptySlotsStruct_InteractiveObject
//-----------------------------------------------------------

// flash.text::StaticText$
//-----------------------------------------------------------
class _vtx_as3_StaticTextClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_StaticTextClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::_vtx_as3_StaticTextClassSlots EmptySlotsStruct_StaticTextClass
//-----------------------------------------------------------

// flash.text::StaticText
//-----------------------------------------------------------
class _vtx_as3_StaticTextSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_StaticText \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::_vtx_as3_StaticTextSlots EmptySlotsStruct_StaticText
//-----------------------------------------------------------

// flash.display::DisplayObjectContainer$
//-----------------------------------------------------------
class _vtx_as3_DisplayObjectContainerClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_DisplayObjectContainerClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::_vtx_as3_DisplayObjectContainerClassSlots EmptySlotsStruct_DisplayObjectContainerClass
//-----------------------------------------------------------

// flash.display::DisplayObjectContainer
//-----------------------------------------------------------
class _vtx_as3_DisplayObjectContainerSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_DisplayObjectContainer \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::_vtx_as3_DisplayObjectContainerSlots EmptySlotsStruct_DisplayObjectContainer
//-----------------------------------------------------------

// flash.display::SimpleButton$
//-----------------------------------------------------------
class _vtx_as3_SimpleButtonClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_SimpleButtonClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::_vtx_as3_SimpleButtonClassSlots EmptySlotsStruct_SimpleButtonClass
//-----------------------------------------------------------

// flash.display::SimpleButton
//-----------------------------------------------------------
class _vtx_as3_SimpleButtonSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_SimpleButton \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::_vtx_as3_SimpleButtonSlots EmptySlotsStruct_SimpleButton
//-----------------------------------------------------------

// flash.text::TextField$
//-----------------------------------------------------------
class _vtx_as3_TextFieldClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_TextFieldClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::_vtx_as3_TextFieldClassSlots EmptySlotsStruct_TextFieldClass
//-----------------------------------------------------------

// flash.text::TextField
//-----------------------------------------------------------
class _vtx_as3_TextFieldSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_TextField \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::_vtx_as3_TextFieldSlots EmptySlotsStruct_TextField
//-----------------------------------------------------------

// flash.display::Sprite$
//-----------------------------------------------------------
class _vtx_as3_SpriteClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_SpriteClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::_vtx_as3_SpriteClassSlots EmptySlotsStruct_SpriteClass
//-----------------------------------------------------------

// flash.display::Sprite
//-----------------------------------------------------------
class _vtx_as3_SpriteSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_Sprite \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::_vtx_as3_SpriteSlots EmptySlotsStruct_Sprite
//-----------------------------------------------------------

// flash.display::MovieClip$
//-----------------------------------------------------------
class _vtx_as3_MovieClipClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_MovieClipClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::_vtx_as3_MovieClipClassSlots EmptySlotsStruct_MovieClipClass
//-----------------------------------------------------------

// flash.display::MovieClip
//-----------------------------------------------------------
class _vtx_as3_MovieClipSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_MovieClip \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::_vtx_as3_MovieClipSlots EmptySlotsStruct_MovieClip
//-----------------------------------------------------------

} }
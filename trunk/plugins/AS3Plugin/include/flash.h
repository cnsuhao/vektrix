#ifndef __FLASH_GLUE_H__
#define __FLASH_GLUE_H__

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
    class ScriptObject; //flash.utils::FlashUtils
    class String; //String
}

namespace vtx { namespace as3 {
    class Dictionary; //flash.utils::Dictionary
    class DictionaryClass; //flash.utils::Dictionary$
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
    class ExternalInterfaceClass; //flash.external::ExternalInterface$
    class FlashUtilsClass; //flash.utils::FlashUtils$
    class InteractiveObject; //flash.display::InteractiveObject
    class InteractiveObjectClass; //flash.display::InteractiveObject$
    class Loader; //flash.display::Loader
    class LoaderClass; //flash.display::Loader$
    class LoaderContext; //flash.system::LoaderContext
    class LoaderContextClass; //flash.system::LoaderContext$
    class Mouse; //flash.ui::Mouse
    class MouseClass; //flash.ui::Mouse$
    class MouseEvent; //flash.events::MouseEvent
    class MouseEventClass; //flash.events::MouseEvent$
    class MovieClip; //flash.display::MovieClip
    class MovieClipClass; //flash.display::MovieClip$
    class SimpleButton; //flash.display::SimpleButton
    class SimpleButtonClass; //flash.display::SimpleButton$
    class Sprite; //flash.display::Sprite
    class SpriteClass; //flash.display::Sprite$
    class Stage; //flash.display::Stage
    class StageClass; //flash.display::Stage$
    class StaticText; //flash.text::StaticText
    class StaticTextClass; //flash.text::StaticText$
    class TextField; //flash.text::TextField
    class TextFieldClass; //flash.text::TextField$
    class Timer; //flash.utils::Timer
    class TimerClass; //flash.utils::Timer$
    class URLRequest; //flash.net::URLRequest
    class URLRequestClass; //flash.net::URLRequest$
} }

namespace avmplus { namespace NativeID {

extern const uint32_t flash_abc_class_count;
extern const uint32_t flash_abc_script_count;
extern const uint32_t flash_abc_method_count;
extern const uint32_t flash_abc_length;
extern const uint8_t flash_abc_data[];
AVMTHUNK_DECLARE_NATIVE_INITIALIZER(flash)

/* classes */
const uint32_t abcclass_flash_accessibility_Accessibility = 0;
const uint32_t abcclass_flash_accessibility_AccessibilityProperties = 1;
const uint32_t abcclass_flash_display_BitmapData = 2;
const uint32_t abcclass_flash_display_Graphics = 3;
const uint32_t abcclass_flash_display_IBitmapDrawable = 4;
const uint32_t abcclass_flash_display_Scene = 5;
const uint32_t abcclass_flash_events_Event = 6;
const uint32_t abcclass_flash_events_IEventDispatcher = 7;
const uint32_t abcclass_flash_external_ExternalInterface = 8;
const uint32_t abcclass_flash_filters_BitmapFilter = 9;
const uint32_t abcclass_flash_geom_ColorTransform = 10;
const uint32_t abcclass_flash_geom_Matrix = 11;
const uint32_t abcclass_flash_geom_Point = 12;
const uint32_t abcclass_flash_geom_Rectangle = 13;
const uint32_t abcclass_flash_geom_Transform = 14;
const uint32_t abcclass_flash_media_SoundTransform = 15;
const uint32_t abcclass_flash_net_URLRequest = 16;
const uint32_t abcclass_flash_system_ApplicationDomain = 17;
const uint32_t abcclass_flash_system_LoaderContext = 18;
const uint32_t abcclass_flash_text_TextFieldAutoSize = 19;
const uint32_t abcclass_flash_text_TextFieldType = 20;
const uint32_t abcclass_flash_text_TextFormat = 21;
const uint32_t abcclass_flash_text_TextFormatAlign = 22;
const uint32_t abcclass_flash_text_TextLineMetrics = 23;
const uint32_t abcclass_flash_text_TextSnapshot = 24;
const uint32_t abcclass_flash_ui_Keyboard = 25;
const uint32_t abcclass_flash_ui_Mouse = 26;
const uint32_t abcclass_flash_utils_ByteArray = 27;
const uint32_t abcclass_flash_utils_Dictionary = 28;
const uint32_t abcclass_flash_utils_Endian = 29;
const uint32_t abcclass_flash_utils_FlashUtils = 30;
const uint32_t abcclass_vektrix_EventHandler = 31;
const uint32_t abcclass_vektrix_Movie = 32;
const uint32_t abcclass_flash_events_FocusEvent = 33;
const uint32_t abcclass_flash_events_KeyboardEvent = 34;
const uint32_t abcclass_flash_events_MouseEvent = 35;
const uint32_t abcclass_flash_events_TimerEvent = 36;
const uint32_t abcclass_flash_events_EventDispatcher = 37;
const uint32_t abcclass_flash_display_DisplayObject = 38;
const uint32_t abcclass_flash_display_LoaderInfo = 39;
const uint32_t abcclass_flash_media_Camera = 40;
const uint32_t abcclass_flash_media_Microphone = 41;
const uint32_t abcclass_flash_net_LocalConnection = 42;
const uint32_t abcclass_flash_net_NetConnection = 43;
const uint32_t abcclass_flash_net_NetStream = 44;
const uint32_t abcclass_flash_net_SharedObject = 45;
const uint32_t abcclass_flash_net_Socket = 46;
const uint32_t abcclass_flash_text_StyleSheet = 47;
const uint32_t abcclass_flash_utils_Timer = 48;
const uint32_t abcclass_flash_display_InteractiveObject = 49;
const uint32_t abcclass_flash_media_Video = 50;
const uint32_t abcclass_flash_text_StaticText = 51;
const uint32_t abcclass_flash_display_DisplayObjectContainer = 52;
const uint32_t abcclass_flash_display_SimpleButton = 53;
const uint32_t abcclass_flash_text_TextField = 54;
const uint32_t abcclass_flash_display_Loader = 55;
const uint32_t abcclass_flash_display_Sprite = 56;
const uint32_t abcclass_flash_display_Stage = 57;
const uint32_t abcclass_flash_display_MovieClip = 58;

/* methods */
const uint32_t flash_external_ExternalInterface_available_get = 97;
const uint32_t flash_external_ExternalInterface_addCallback = 99;
const uint32_t flash_external_ExternalInterface_call = 100;
const uint32_t flash_ui_Mouse_hide = 252;
const uint32_t flash_ui_Mouse_show = 253;
const uint32_t flash_utils_Dictionary_private_ctor = 300;
const uint32_t flash_utils_FlashUtils_flash_utils_getClass = 318;
const uint32_t vektrix_EventHandler_add = 322;
const uint32_t vektrix_EventHandler_handle = 323;
const uint32_t flash_events_EventDispatcher_private_ctor = 364;
const uint32_t flash_display_DisplayObject_private_ctor = 373;
const uint32_t flash_display_DisplayObject_private__height_get = 385;
const uint32_t flash_display_DisplayObject_private__height_set = 387;
const uint32_t flash_display_DisplayObject_private__parent_get = 398;
const uint32_t flash_display_DisplayObject_private__root_get = 400;
const uint32_t flash_display_DisplayObject_rotation_get = 402;
const uint32_t flash_display_DisplayObject_rotation_set = 403;
const uint32_t flash_display_DisplayObject_scaleX_get = 406;
const uint32_t flash_display_DisplayObject_scaleX_set = 407;
const uint32_t flash_display_DisplayObject_scaleY_get = 408;
const uint32_t flash_display_DisplayObject_scaleY_set = 409;
const uint32_t flash_display_DisplayObject_stage_get = 412;
const uint32_t flash_display_DisplayObject_private__visible_get = 415;
const uint32_t flash_display_DisplayObject_private__visible_set = 417;
const uint32_t flash_display_DisplayObject_width_get = 419;
const uint32_t flash_display_DisplayObject_width_set = 420;
const uint32_t flash_display_DisplayObject_x_get = 421;
const uint32_t flash_display_DisplayObject_x_set = 422;
const uint32_t flash_display_DisplayObject_y_get = 423;
const uint32_t flash_display_DisplayObject_y_set = 424;
const uint32_t flash_utils_Timer_private_ctor = 546;
const uint32_t flash_utils_Timer_private__reset = 548;
const uint32_t flash_utils_Timer_private__start = 550;
const uint32_t flash_utils_Timer_private__stop = 552;
const uint32_t flash_text_StaticText_text_get = 573;
const uint32_t flash_display_DisplayObjectContainer_private_ctor = 577;
const uint32_t flash_display_DisplayObjectContainer_numChildren_get = 581;
const uint32_t flash_display_DisplayObjectContainer_addChild = 585;
const uint32_t flash_display_DisplayObjectContainer_addChildAt = 586;
const uint32_t flash_display_DisplayObjectContainer_contains = 588;
const uint32_t flash_display_DisplayObjectContainer_getChildAt = 589;
const uint32_t flash_display_DisplayObjectContainer_getChildByName = 590;
const uint32_t flash_display_DisplayObjectContainer_getChildIndex = 591;
const uint32_t flash_display_DisplayObjectContainer_removeChild = 593;
const uint32_t flash_display_DisplayObjectContainer_removeChildAt = 594;
const uint32_t flash_display_DisplayObjectContainer_setChildIndex = 595;
const uint32_t flash_text_TextField_private_ctor = 603;
const uint32_t flash_text_TextField_htmlText_get = 631;
const uint32_t flash_text_TextField_htmlText_set = 632;
const uint32_t flash_text_TextField_getLineIndexAtPoint = 676;
const uint32_t flash_text_TextField_setSelection = 686;
const uint32_t flash_display_Loader_load = 690;
const uint32_t flash_display_Stage_stageHeight_get = 734;
const uint32_t flash_display_Stage_stageWidth_get = 736;
const uint32_t flash_display_MovieClip_private_ctor = 748;
const uint32_t flash_display_MovieClip__currentFrame_get = 750;

extern avmplus::AvmBox flash_v2a_odi_thunk(AvmMethodEnv env, uint32_t argc, avmplus::AvmBox* argv);
#define flash_utils_Timer_private_ctor_thunk  flash_v2a_odi_thunk

extern double flash_d2d_o_thunk(AvmMethodEnv env, uint32_t argc, avmplus::AvmBox* argv);
#define flash_display_DisplayObject_scaleY_get_thunk  flash_d2d_o_thunk
#define flash_display_DisplayObject_width_get_thunk  flash_d2d_o_thunk
#define flash_display_DisplayObject_rotation_get_thunk  flash_d2d_o_thunk
#define flash_display_DisplayObject_x_get_thunk  flash_d2d_o_thunk
#define flash_display_DisplayObject_y_get_thunk  flash_d2d_o_thunk
#define flash_display_DisplayObject_private__height_get_thunk  flash_d2d_o_thunk
#define flash_display_DisplayObject_scaleX_get_thunk  flash_d2d_o_thunk

extern avmplus::AvmBox flash_a2a_os_thunk(AvmMethodEnv env, uint32_t argc, avmplus::AvmBox* argv);
#define flash_display_DisplayObjectContainer_getChildByName_thunk  flash_a2a_os_thunk
#define flash_utils_FlashUtils_flash_utils_getClass_thunk  flash_a2a_os_thunk

extern avmplus::AvmBox flash_a2a_ooi_thunk(AvmMethodEnv env, uint32_t argc, avmplus::AvmBox* argv);
#define flash_display_DisplayObjectContainer_addChildAt_thunk  flash_a2a_ooi_thunk

extern avmplus::AvmBox flash_v2a_ooo_optakAvmThunkNull_thunk(AvmMethodEnv env, uint32_t argc, avmplus::AvmBox* argv);
#define flash_display_Loader_load_thunk  flash_v2a_ooo_optakAvmThunkNull_thunk

extern avmplus::AvmBox flash_a2a_oi_thunk(AvmMethodEnv env, uint32_t argc, avmplus::AvmBox* argv);
#define flash_display_DisplayObjectContainer_getChildAt_thunk  flash_a2a_oi_thunk
#define flash_display_DisplayObjectContainer_removeChildAt_thunk  flash_a2a_oi_thunk

extern avmplus::AvmBox flash_a2a_oo_thunk(AvmMethodEnv env, uint32_t argc, avmplus::AvmBox* argv);
#define flash_display_DisplayObjectContainer_addChild_thunk  flash_a2a_oo_thunk
#define flash_display_DisplayObjectContainer_removeChild_thunk  flash_a2a_oo_thunk

extern avmplus::AvmBox flash_s2a_o_thunk(AvmMethodEnv env, uint32_t argc, avmplus::AvmBox* argv);
#define flash_text_TextField_htmlText_get_thunk  flash_s2a_o_thunk
#define flash_text_StaticText_text_get_thunk  flash_s2a_o_thunk

extern avmplus::AvmBox flash_v2a_ooi_thunk(AvmMethodEnv env, uint32_t argc, avmplus::AvmBox* argv);
#define flash_display_DisplayObjectContainer_setChildIndex_thunk  flash_v2a_ooi_thunk

extern avmplus::AvmBox flash_i2a_o_thunk(AvmMethodEnv env, uint32_t argc, avmplus::AvmBox* argv);
#define flash_display_Stage_stageWidth_get_thunk  flash_i2a_o_thunk
#define flash_display_MovieClip__currentFrame_get_thunk  flash_i2a_o_thunk
#define flash_display_DisplayObjectContainer_numChildren_get_thunk  flash_i2a_o_thunk
#define flash_display_Stage_stageHeight_get_thunk  flash_i2a_o_thunk

extern avmplus::AvmBox flash_v2a_oso_thunk(AvmMethodEnv env, uint32_t argc, avmplus::AvmBox* argv);
#define flash_external_ExternalInterface_addCallback_thunk  flash_v2a_oso_thunk

extern avmplus::AvmBox flash_a2a_os_rest_thunk(AvmMethodEnv env, uint32_t argc, avmplus::AvmBox* argv);
#define flash_external_ExternalInterface_call_thunk  flash_a2a_os_rest_thunk

extern avmplus::AvmBox flash_b2a_oo_thunk(AvmMethodEnv env, uint32_t argc, avmplus::AvmBox* argv);
#define flash_display_DisplayObjectContainer_contains_thunk  flash_b2a_oo_thunk

extern avmplus::AvmBox flash_a2a_o_thunk(AvmMethodEnv env, uint32_t argc, avmplus::AvmBox* argv);
#define flash_display_DisplayObject_stage_get_thunk  flash_a2a_o_thunk
#define flash_display_DisplayObject_private__root_get_thunk  flash_a2a_o_thunk
#define flash_display_DisplayObject_private__parent_get_thunk  flash_a2a_o_thunk

extern avmplus::AvmBox flash_v2a_oii_thunk(AvmMethodEnv env, uint32_t argc, avmplus::AvmBox* argv);
#define flash_text_TextField_setSelection_thunk  flash_v2a_oii_thunk

extern avmplus::AvmBox flash_i2a_oii_thunk(AvmMethodEnv env, uint32_t argc, avmplus::AvmBox* argv);
#define vektrix_EventHandler_add_thunk  flash_i2a_oii_thunk

extern avmplus::AvmBox flash_i2a_oo_thunk(AvmMethodEnv env, uint32_t argc, avmplus::AvmBox* argv);
#define flash_display_DisplayObjectContainer_getChildIndex_thunk  flash_i2a_oo_thunk

extern avmplus::AvmBox flash_v2a_od_thunk(AvmMethodEnv env, uint32_t argc, avmplus::AvmBox* argv);
#define flash_display_DisplayObject_private__height_set_thunk  flash_v2a_od_thunk
#define flash_display_DisplayObject_rotation_set_thunk  flash_v2a_od_thunk
#define flash_display_DisplayObject_scaleY_set_thunk  flash_v2a_od_thunk
#define flash_display_DisplayObject_y_set_thunk  flash_v2a_od_thunk
#define flash_display_DisplayObject_width_set_thunk  flash_v2a_od_thunk
#define flash_display_DisplayObject_scaleX_set_thunk  flash_v2a_od_thunk
#define flash_display_DisplayObject_x_set_thunk  flash_v2a_od_thunk

extern avmplus::AvmBox flash_v2a_ob_thunk(AvmMethodEnv env, uint32_t argc, avmplus::AvmBox* argv);
#define flash_display_DisplayObject_private__visible_set_thunk  flash_v2a_ob_thunk
#define flash_utils_Dictionary_private_ctor_thunk  flash_v2a_ob_thunk

extern avmplus::AvmBox flash_v2a_oo_thunk(AvmMethodEnv env, uint32_t argc, avmplus::AvmBox* argv);
#define vektrix_EventHandler_handle_thunk  flash_v2a_oo_thunk

extern avmplus::AvmBox flash_v2a_o_thunk(AvmMethodEnv env, uint32_t argc, avmplus::AvmBox* argv);
#define flash_display_DisplayObjectContainer_private_ctor_thunk  flash_v2a_o_thunk
#define flash_ui_Mouse_hide_thunk  flash_v2a_o_thunk
#define flash_utils_Timer_private__start_thunk  flash_v2a_o_thunk
#define flash_display_DisplayObject_private_ctor_thunk  flash_v2a_o_thunk
#define flash_ui_Mouse_show_thunk  flash_v2a_o_thunk
#define flash_display_MovieClip_private_ctor_thunk  flash_v2a_o_thunk
#define flash_utils_Timer_private__reset_thunk  flash_v2a_o_thunk
#define flash_text_TextField_private_ctor_thunk  flash_v2a_o_thunk
#define flash_utils_Timer_private__stop_thunk  flash_v2a_o_thunk

extern avmplus::AvmBox flash_b2a_o_thunk(AvmMethodEnv env, uint32_t argc, avmplus::AvmBox* argv);
#define flash_external_ExternalInterface_available_get_thunk  flash_b2a_o_thunk
#define flash_display_DisplayObject_private__visible_get_thunk  flash_b2a_o_thunk

extern avmplus::AvmBox flash_i2a_odd_thunk(AvmMethodEnv env, uint32_t argc, avmplus::AvmBox* argv);
#define flash_text_TextField_getLineIndexAtPoint_thunk  flash_i2a_odd_thunk

extern avmplus::AvmBox flash_v2a_os_thunk(AvmMethodEnv env, uint32_t argc, avmplus::AvmBox* argv);
#define flash_text_TextField_htmlText_set_thunk  flash_v2a_os_thunk

extern avmplus::AvmBox flash_v2a_oo_optakAvmThunkNull_thunk(AvmMethodEnv env, uint32_t argc, avmplus::AvmBox* argv);
#define flash_events_EventDispatcher_private_ctor_thunk  flash_v2a_oo_optakAvmThunkNull_thunk

class SlotOffsetsAndAsserts;
// flash.events::Event$
//-----------------------------------------------------------
class _vtx_as3_EventClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
    REALLY_INLINE avmplus::AvmString get_ACTIVATE() const { return m_ACTIVATE; }
    REALLY_INLINE avmplus::AvmString get_ADDED() const { return m_ADDED; }
    REALLY_INLINE avmplus::AvmString get_ADDED_TO_STAGE() const { return m_ADDED_TO_STAGE; }
    REALLY_INLINE avmplus::AvmString get_CANCEL() const { return m_CANCEL; }
    REALLY_INLINE avmplus::AvmString get_CHANGE() const { return m_CHANGE; }
    REALLY_INLINE avmplus::AvmString get_CLEAR() const { return m_CLEAR; }
    REALLY_INLINE avmplus::AvmString get_CLOSE() const { return m_CLOSE; }
    REALLY_INLINE avmplus::AvmString get_CLOSING() const { return m_CLOSING; }
    REALLY_INLINE avmplus::AvmString get_COMPLETE() const { return m_COMPLETE; }
    REALLY_INLINE avmplus::AvmString get_CONNECT() const { return m_CONNECT; }
    REALLY_INLINE avmplus::AvmString get_COPY() const { return m_COPY; }
    REALLY_INLINE avmplus::AvmString get_CUT() const { return m_CUT; }
    REALLY_INLINE avmplus::AvmString get_DEACTIVATE() const { return m_DEACTIVATE; }
    REALLY_INLINE avmplus::AvmString get_DISPLAYING() const { return m_DISPLAYING; }
    REALLY_INLINE avmplus::AvmString get_ENTER_FRAME() const { return m_ENTER_FRAME; }
    REALLY_INLINE avmplus::AvmString get_EXIT_FRAME() const { return m_EXIT_FRAME; }
    REALLY_INLINE avmplus::AvmString get_EXITING() const { return m_EXITING; }
    REALLY_INLINE avmplus::AvmString get_FRAME_CONSTRUCTED() const { return m_FRAME_CONSTRUCTED; }
    REALLY_INLINE avmplus::AvmString get_FULLSCREEN() const { return m_FULLSCREEN; }
    REALLY_INLINE avmplus::AvmString get_HTML_BOUNDS_CHANGE() const { return m_HTML_BOUNDS_CHANGE; }
    REALLY_INLINE avmplus::AvmString get_HTML_DOM_INITIALIZE() const { return m_HTML_DOM_INITIALIZE; }
    REALLY_INLINE avmplus::AvmString get_HTML_RENDER() const { return m_HTML_RENDER; }
    REALLY_INLINE avmplus::AvmString get_ID3() const { return m_ID3; }
    REALLY_INLINE avmplus::AvmString get_INIT() const { return m_INIT; }
    REALLY_INLINE avmplus::AvmString get_LOCATION_CHANGE() const { return m_LOCATION_CHANGE; }
    REALLY_INLINE avmplus::AvmString get_MOUSE_LEAVE() const { return m_MOUSE_LEAVE; }
    REALLY_INLINE avmplus::AvmString get_NETWORK_CHANGE() const { return m_NETWORK_CHANGE; }
    REALLY_INLINE avmplus::AvmString get_OPEN() const { return m_OPEN; }
    REALLY_INLINE avmplus::AvmString get_PASTE() const { return m_PASTE; }
    REALLY_INLINE avmplus::AvmString get_REMOVED() const { return m_REMOVED; }
    REALLY_INLINE avmplus::AvmString get_REMOVED_FROM_STAGE() const { return m_REMOVED_FROM_STAGE; }
    REALLY_INLINE avmplus::AvmString get_RENDER() const { return m_RENDER; }
    REALLY_INLINE avmplus::AvmString get_RESIZE() const { return m_RESIZE; }
    REALLY_INLINE avmplus::AvmString get_SAMPLE_DATA() const { return m_SAMPLE_DATA; }
    REALLY_INLINE avmplus::AvmString get_SCROLL() const { return m_SCROLL; }
    REALLY_INLINE avmplus::AvmString get_SELECT() const { return m_SELECT; }
    REALLY_INLINE avmplus::AvmString get_SELECT_ALL() const { return m_SELECT_ALL; }
    REALLY_INLINE avmplus::AvmString get_SOUND_COMPLETE() const { return m_SOUND_COMPLETE; }
    REALLY_INLINE avmplus::AvmString get_TAB_CHILDREN_CHANGE() const { return m_TAB_CHILDREN_CHANGE; }
    REALLY_INLINE avmplus::AvmString get_TAB_ENABLED_CHANGE() const { return m_TAB_ENABLED_CHANGE; }
    REALLY_INLINE avmplus::AvmString get_TAB_INDEX_CHANGE() const { return m_TAB_INDEX_CHANGE; }
    REALLY_INLINE avmplus::AvmString get_UNLOAD() const { return m_UNLOAD; }
    REALLY_INLINE avmplus::AvmString get_USER_IDLE() const { return m_USER_IDLE; }
    REALLY_INLINE avmplus::AvmString get_USER_PRESENT() const { return m_USER_PRESENT; }
private:
    DRCWB(avmplus::AvmString) m_ACTIVATE;
    DRCWB(avmplus::AvmString) m_ADDED;
    DRCWB(avmplus::AvmString) m_ADDED_TO_STAGE;
    DRCWB(avmplus::AvmString) m_CANCEL;
    DRCWB(avmplus::AvmString) m_CHANGE;
    DRCWB(avmplus::AvmString) m_CLEAR;
    DRCWB(avmplus::AvmString) m_CLOSE;
    DRCWB(avmplus::AvmString) m_CLOSING;
    DRCWB(avmplus::AvmString) m_COMPLETE;
    DRCWB(avmplus::AvmString) m_CONNECT;
    DRCWB(avmplus::AvmString) m_COPY;
    DRCWB(avmplus::AvmString) m_CUT;
    DRCWB(avmplus::AvmString) m_DEACTIVATE;
    DRCWB(avmplus::AvmString) m_DISPLAYING;
    DRCWB(avmplus::AvmString) m_ENTER_FRAME;
    DRCWB(avmplus::AvmString) m_EXIT_FRAME;
    DRCWB(avmplus::AvmString) m_EXITING;
    DRCWB(avmplus::AvmString) m_FRAME_CONSTRUCTED;
    DRCWB(avmplus::AvmString) m_FULLSCREEN;
    DRCWB(avmplus::AvmString) m_HTML_BOUNDS_CHANGE;
    DRCWB(avmplus::AvmString) m_HTML_DOM_INITIALIZE;
    DRCWB(avmplus::AvmString) m_HTML_RENDER;
    DRCWB(avmplus::AvmString) m_ID3;
    DRCWB(avmplus::AvmString) m_INIT;
    DRCWB(avmplus::AvmString) m_LOCATION_CHANGE;
    DRCWB(avmplus::AvmString) m_MOUSE_LEAVE;
    DRCWB(avmplus::AvmString) m_NETWORK_CHANGE;
    DRCWB(avmplus::AvmString) m_OPEN;
    DRCWB(avmplus::AvmString) m_PASTE;
    DRCWB(avmplus::AvmString) m_REMOVED;
    DRCWB(avmplus::AvmString) m_REMOVED_FROM_STAGE;
    DRCWB(avmplus::AvmString) m_RENDER;
    DRCWB(avmplus::AvmString) m_RESIZE;
    DRCWB(avmplus::AvmString) m_SAMPLE_DATA;
    DRCWB(avmplus::AvmString) m_SCROLL;
    DRCWB(avmplus::AvmString) m_SELECT;
    DRCWB(avmplus::AvmString) m_SELECT_ALL;
    DRCWB(avmplus::AvmString) m_SOUND_COMPLETE;
    DRCWB(avmplus::AvmString) m_TAB_CHILDREN_CHANGE;
    DRCWB(avmplus::AvmString) m_TAB_ENABLED_CHANGE;
    DRCWB(avmplus::AvmString) m_TAB_INDEX_CHANGE;
    DRCWB(avmplus::AvmString) m_UNLOAD;
    DRCWB(avmplus::AvmString) m_USER_IDLE;
    DRCWB(avmplus::AvmString) m_USER_PRESENT;
};
#define DECLARE_SLOTS_EventClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
    protected: \
        REALLY_INLINE avmplus::AvmString get_ACTIVATE() const { return m_slots_EventClass.get_ACTIVATE(); } \
        REALLY_INLINE avmplus::AvmString get_ADDED() const { return m_slots_EventClass.get_ADDED(); } \
        REALLY_INLINE avmplus::AvmString get_ADDED_TO_STAGE() const { return m_slots_EventClass.get_ADDED_TO_STAGE(); } \
        REALLY_INLINE avmplus::AvmString get_CANCEL() const { return m_slots_EventClass.get_CANCEL(); } \
        REALLY_INLINE avmplus::AvmString get_CHANGE() const { return m_slots_EventClass.get_CHANGE(); } \
        REALLY_INLINE avmplus::AvmString get_CLEAR() const { return m_slots_EventClass.get_CLEAR(); } \
        REALLY_INLINE avmplus::AvmString get_CLOSE() const { return m_slots_EventClass.get_CLOSE(); } \
        REALLY_INLINE avmplus::AvmString get_CLOSING() const { return m_slots_EventClass.get_CLOSING(); } \
        REALLY_INLINE avmplus::AvmString get_COMPLETE() const { return m_slots_EventClass.get_COMPLETE(); } \
        REALLY_INLINE avmplus::AvmString get_CONNECT() const { return m_slots_EventClass.get_CONNECT(); } \
        REALLY_INLINE avmplus::AvmString get_COPY() const { return m_slots_EventClass.get_COPY(); } \
        REALLY_INLINE avmplus::AvmString get_CUT() const { return m_slots_EventClass.get_CUT(); } \
        REALLY_INLINE avmplus::AvmString get_DEACTIVATE() const { return m_slots_EventClass.get_DEACTIVATE(); } \
        REALLY_INLINE avmplus::AvmString get_DISPLAYING() const { return m_slots_EventClass.get_DISPLAYING(); } \
        REALLY_INLINE avmplus::AvmString get_ENTER_FRAME() const { return m_slots_EventClass.get_ENTER_FRAME(); } \
        REALLY_INLINE avmplus::AvmString get_EXIT_FRAME() const { return m_slots_EventClass.get_EXIT_FRAME(); } \
        REALLY_INLINE avmplus::AvmString get_EXITING() const { return m_slots_EventClass.get_EXITING(); } \
        REALLY_INLINE avmplus::AvmString get_FRAME_CONSTRUCTED() const { return m_slots_EventClass.get_FRAME_CONSTRUCTED(); } \
        REALLY_INLINE avmplus::AvmString get_FULLSCREEN() const { return m_slots_EventClass.get_FULLSCREEN(); } \
        REALLY_INLINE avmplus::AvmString get_HTML_BOUNDS_CHANGE() const { return m_slots_EventClass.get_HTML_BOUNDS_CHANGE(); } \
        REALLY_INLINE avmplus::AvmString get_HTML_DOM_INITIALIZE() const { return m_slots_EventClass.get_HTML_DOM_INITIALIZE(); } \
        REALLY_INLINE avmplus::AvmString get_HTML_RENDER() const { return m_slots_EventClass.get_HTML_RENDER(); } \
        REALLY_INLINE avmplus::AvmString get_ID3() const { return m_slots_EventClass.get_ID3(); } \
        REALLY_INLINE avmplus::AvmString get_INIT() const { return m_slots_EventClass.get_INIT(); } \
        REALLY_INLINE avmplus::AvmString get_LOCATION_CHANGE() const { return m_slots_EventClass.get_LOCATION_CHANGE(); } \
        REALLY_INLINE avmplus::AvmString get_MOUSE_LEAVE() const { return m_slots_EventClass.get_MOUSE_LEAVE(); } \
        REALLY_INLINE avmplus::AvmString get_NETWORK_CHANGE() const { return m_slots_EventClass.get_NETWORK_CHANGE(); } \
        REALLY_INLINE avmplus::AvmString get_OPEN() const { return m_slots_EventClass.get_OPEN(); } \
        REALLY_INLINE avmplus::AvmString get_PASTE() const { return m_slots_EventClass.get_PASTE(); } \
        REALLY_INLINE avmplus::AvmString get_REMOVED() const { return m_slots_EventClass.get_REMOVED(); } \
        REALLY_INLINE avmplus::AvmString get_REMOVED_FROM_STAGE() const { return m_slots_EventClass.get_REMOVED_FROM_STAGE(); } \
        REALLY_INLINE avmplus::AvmString get_RENDER() const { return m_slots_EventClass.get_RENDER(); } \
        REALLY_INLINE avmplus::AvmString get_RESIZE() const { return m_slots_EventClass.get_RESIZE(); } \
        REALLY_INLINE avmplus::AvmString get_SAMPLE_DATA() const { return m_slots_EventClass.get_SAMPLE_DATA(); } \
        REALLY_INLINE avmplus::AvmString get_SCROLL() const { return m_slots_EventClass.get_SCROLL(); } \
        REALLY_INLINE avmplus::AvmString get_SELECT() const { return m_slots_EventClass.get_SELECT(); } \
        REALLY_INLINE avmplus::AvmString get_SELECT_ALL() const { return m_slots_EventClass.get_SELECT_ALL(); } \
        REALLY_INLINE avmplus::AvmString get_SOUND_COMPLETE() const { return m_slots_EventClass.get_SOUND_COMPLETE(); } \
        REALLY_INLINE avmplus::AvmString get_TAB_CHILDREN_CHANGE() const { return m_slots_EventClass.get_TAB_CHILDREN_CHANGE(); } \
        REALLY_INLINE avmplus::AvmString get_TAB_ENABLED_CHANGE() const { return m_slots_EventClass.get_TAB_ENABLED_CHANGE(); } \
        REALLY_INLINE avmplus::AvmString get_TAB_INDEX_CHANGE() const { return m_slots_EventClass.get_TAB_INDEX_CHANGE(); } \
        REALLY_INLINE avmplus::AvmString get_UNLOAD() const { return m_slots_EventClass.get_UNLOAD(); } \
        REALLY_INLINE avmplus::AvmString get_USER_IDLE() const { return m_slots_EventClass.get_USER_IDLE(); } \
        REALLY_INLINE avmplus::AvmString get_USER_PRESENT() const { return m_slots_EventClass.get_USER_PRESENT(); } \
    private: \
        avmplus::NativeID::_vtx_as3_EventClassSlots m_slots_EventClass
//-----------------------------------------------------------

// flash.events::Event
//-----------------------------------------------------------
class _vtx_as3_EventSlots
{
    friend class SlotOffsetsAndAsserts;
public:
    REALLY_INLINE avmplus::AvmBool32 get_flash_events_DEBUG_EVENT() const { return m_flash_events_DEBUG_EVENT; }
    REALLY_INLINE avmplus::AvmBool32 get_flash_events_Event_mBubbles() const { return m_flash_events_Event_mBubbles; }
    void set_flash_events_Event_mBubbles(avmplus::AvmBool32 newVal);
    REALLY_INLINE avmplus::AvmBool32 get_flash_events_Event_mCancelable() const { return m_flash_events_Event_mCancelable; }
    void set_flash_events_Event_mCancelable(avmplus::AvmBool32 newVal);
    REALLY_INLINE avmplus::AvmString get_flash_events_Event_mType() const { return m_flash_events_Event_mType; }
    void set_flash_events_Event_mType(::vtx::as3::Event* obj, avmplus::AvmString newVal);
    REALLY_INLINE avmplus::AvmBox get_flash_events_Event_mCurrentTarget() const { return m_flash_events_Event_mCurrentTarget; }
    void set_flash_events_Event_mCurrentTarget(::vtx::as3::Event* obj, avmplus::AvmBox newVal);
    REALLY_INLINE avmplus::AvmBox get_flash_events_Event_mTarget() const { return m_flash_events_Event_mTarget; }
    void set_flash_events_Event_mTarget(::vtx::as3::Event* obj, avmplus::AvmBox newVal);
private:
    avmplus::AvmBool32 m_flash_events_DEBUG_EVENT;
    avmplus::AvmBool32 m_flash_events_Event_mBubbles;
    avmplus::AvmBool32 m_flash_events_Event_mCancelable;
    DRCWB(avmplus::AvmString) m_flash_events_Event_mType;
    ATOM_WB m_flash_events_Event_mCurrentTarget;
    ATOM_WB m_flash_events_Event_mTarget;
};
REALLY_INLINE void _vtx_as3_EventSlots::set_flash_events_Event_mBubbles(avmplus::AvmBool32 newVal) { m_flash_events_Event_mBubbles = newVal; }
REALLY_INLINE void _vtx_as3_EventSlots::set_flash_events_Event_mCancelable(avmplus::AvmBool32 newVal) { m_flash_events_Event_mCancelable = newVal; }
REALLY_INLINE void _vtx_as3_EventSlots::set_flash_events_Event_mType(::vtx::as3::Event* obj, avmplus::AvmString newVal)
{
    m_flash_events_Event_mType.set(((ScriptObject*)obj)->gc(), obj, newVal);
}
REALLY_INLINE void _vtx_as3_EventSlots::set_flash_events_Event_mCurrentTarget(::vtx::as3::Event* obj, avmplus::AvmBox newVal)
{
    m_flash_events_Event_mCurrentTarget.set(((ScriptObject*)obj)->gc(), obj, newVal);
}
REALLY_INLINE void _vtx_as3_EventSlots::set_flash_events_Event_mTarget(::vtx::as3::Event* obj, avmplus::AvmBox newVal)
{
    m_flash_events_Event_mTarget.set(((ScriptObject*)obj)->gc(), obj, newVal);
}
#define DECLARE_SLOTS_Event \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
    protected: \
        REALLY_INLINE avmplus::AvmBool32 get_flash_events_DEBUG_EVENT() const { return m_slots_Event.get_flash_events_DEBUG_EVENT(); } \
        REALLY_INLINE avmplus::AvmBool32 get_flash_events_Event_mBubbles() const { return m_slots_Event.get_flash_events_Event_mBubbles(); } \
        REALLY_INLINE void set_flash_events_Event_mBubbles(avmplus::AvmBool32 newVal) { m_slots_Event.set_flash_events_Event_mBubbles(newVal); } \
        REALLY_INLINE avmplus::AvmBool32 get_flash_events_Event_mCancelable() const { return m_slots_Event.get_flash_events_Event_mCancelable(); } \
        REALLY_INLINE void set_flash_events_Event_mCancelable(avmplus::AvmBool32 newVal) { m_slots_Event.set_flash_events_Event_mCancelable(newVal); } \
        REALLY_INLINE avmplus::AvmString get_flash_events_Event_mType() const { return m_slots_Event.get_flash_events_Event_mType(); } \
        REALLY_INLINE void set_flash_events_Event_mType(avmplus::AvmString newVal) { m_slots_Event.set_flash_events_Event_mType(this, newVal); } \
        REALLY_INLINE avmplus::AvmBox get_flash_events_Event_mCurrentTarget() const { return m_slots_Event.get_flash_events_Event_mCurrentTarget(); } \
        REALLY_INLINE void set_flash_events_Event_mCurrentTarget(avmplus::AvmBox newVal) { m_slots_Event.set_flash_events_Event_mCurrentTarget(this, newVal); } \
        REALLY_INLINE avmplus::AvmBox get_flash_events_Event_mTarget() const { return m_slots_Event.get_flash_events_Event_mTarget(); } \
        REALLY_INLINE void set_flash_events_Event_mTarget(avmplus::AvmBox newVal) { m_slots_Event.set_flash_events_Event_mTarget(this, newVal); } \
    private: \
        avmplus::NativeID::_vtx_as3_EventSlots m_slots_Event
//-----------------------------------------------------------

// flash.external::ExternalInterface$
//-----------------------------------------------------------
class _vtx_as3_ExternalInterfaceClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
    REALLY_INLINE avmplus::AvmBool32 get_marshallExceptions() const { return m_marshallExceptions; }
    void set_marshallExceptions(avmplus::AvmBool32 newVal);
private:
    avmplus::AvmBool32 m_marshallExceptions;
};
REALLY_INLINE void _vtx_as3_ExternalInterfaceClassSlots::set_marshallExceptions(avmplus::AvmBool32 newVal) { m_marshallExceptions = newVal; }
#define DECLARE_SLOTS_ExternalInterfaceClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
    protected: \
        REALLY_INLINE avmplus::AvmBool32 get_marshallExceptions() const { return m_slots_ExternalInterfaceClass.get_marshallExceptions(); } \
        REALLY_INLINE void set_marshallExceptions(avmplus::AvmBool32 newVal) { m_slots_ExternalInterfaceClass.set_marshallExceptions(newVal); } \
    private: \
        avmplus::NativeID::_vtx_as3_ExternalInterfaceClassSlots m_slots_ExternalInterfaceClass
//-----------------------------------------------------------

// flash.net::URLRequest$
//-----------------------------------------------------------
class _vtx_as3_URLRequestClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_URLRequestClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::_vtx_as3_URLRequestClassSlots EmptySlotsStruct_URLRequestClass
//-----------------------------------------------------------

// flash.net::URLRequest
//-----------------------------------------------------------
class _vtx_as3_URLRequestSlots
{
    friend class SlotOffsetsAndAsserts;
public:
    REALLY_INLINE avmplus::AvmString get_private_mURL() const { return m_private_mURL; }
    void set_private_mURL(::vtx::as3::URLRequest* obj, avmplus::AvmString newVal);
private:
    DRCWB(avmplus::AvmString) m_private_mURL;
};
REALLY_INLINE void _vtx_as3_URLRequestSlots::set_private_mURL(::vtx::as3::URLRequest* obj, avmplus::AvmString newVal)
{
    m_private_mURL.set(((ScriptObject*)obj)->gc(), obj, newVal);
}
#define DECLARE_SLOTS_URLRequest \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
    protected: \
        REALLY_INLINE avmplus::AvmString get_private_mURL() const { return m_slots_URLRequest.get_private_mURL(); } \
        REALLY_INLINE void set_private_mURL(avmplus::AvmString newVal) { m_slots_URLRequest.set_private_mURL(this, newVal); } \
    private: \
        avmplus::NativeID::_vtx_as3_URLRequestSlots m_slots_URLRequest
//-----------------------------------------------------------

// flash.system::LoaderContext$
//-----------------------------------------------------------
class _vtx_as3_LoaderContextClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_LoaderContextClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::_vtx_as3_LoaderContextClassSlots EmptySlotsStruct_LoaderContextClass
//-----------------------------------------------------------

// flash.system::LoaderContext
//-----------------------------------------------------------
class _vtx_as3_LoaderContextSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_LoaderContext \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::_vtx_as3_LoaderContextSlots EmptySlotsStruct_LoaderContext
//-----------------------------------------------------------

// flash.ui::Mouse$
//-----------------------------------------------------------
class _vtx_as3_MouseClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_MouseClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::_vtx_as3_MouseClassSlots EmptySlotsStruct_MouseClass
//-----------------------------------------------------------

// flash.ui::Mouse
//-----------------------------------------------------------
class _vtx_as3_MouseSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_Mouse \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::_vtx_as3_MouseSlots EmptySlotsStruct_Mouse
//-----------------------------------------------------------

// flash.utils::Dictionary$
//-----------------------------------------------------------
class _vtx_as3_DictionaryClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_DictionaryClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::_vtx_as3_DictionaryClassSlots EmptySlotsStruct_DictionaryClass
//-----------------------------------------------------------

// flash.utils::Dictionary
//-----------------------------------------------------------
class _vtx_as3_DictionarySlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_Dictionary \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::_vtx_as3_DictionarySlots EmptySlotsStruct_Dictionary
//-----------------------------------------------------------

// flash.utils::FlashUtils$
//-----------------------------------------------------------
class _vtx_as3_FlashUtilsClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_FlashUtilsClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::_vtx_as3_FlashUtilsClassSlots EmptySlotsStruct_FlashUtilsClass
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

// flash.events::MouseEvent$
//-----------------------------------------------------------
class _vtx_as3_MouseEventClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
    REALLY_INLINE avmplus::AvmString get_CLICK() const { return m_CLICK; }
    REALLY_INLINE avmplus::AvmString get_DOUBLE_CLICK() const { return m_DOUBLE_CLICK; }
    REALLY_INLINE avmplus::AvmString get_MOUSE_DOWN() const { return m_MOUSE_DOWN; }
    REALLY_INLINE avmplus::AvmString get_MOUSE_MOVE() const { return m_MOUSE_MOVE; }
    REALLY_INLINE avmplus::AvmString get_MOUSE_OUT() const { return m_MOUSE_OUT; }
    REALLY_INLINE avmplus::AvmString get_MOUSE_OVER() const { return m_MOUSE_OVER; }
    REALLY_INLINE avmplus::AvmString get_MOUSE_UP() const { return m_MOUSE_UP; }
    REALLY_INLINE avmplus::AvmString get_MOUSE_WHEEL() const { return m_MOUSE_WHEEL; }
    REALLY_INLINE avmplus::AvmString get_ROLL_OUT() const { return m_ROLL_OUT; }
    REALLY_INLINE avmplus::AvmString get_ROLL_OVER() const { return m_ROLL_OVER; }
private:
    DRCWB(avmplus::AvmString) m_CLICK;
    DRCWB(avmplus::AvmString) m_DOUBLE_CLICK;
    DRCWB(avmplus::AvmString) m_MOUSE_DOWN;
    DRCWB(avmplus::AvmString) m_MOUSE_MOVE;
    DRCWB(avmplus::AvmString) m_MOUSE_OUT;
    DRCWB(avmplus::AvmString) m_MOUSE_OVER;
    DRCWB(avmplus::AvmString) m_MOUSE_UP;
    DRCWB(avmplus::AvmString) m_MOUSE_WHEEL;
    DRCWB(avmplus::AvmString) m_ROLL_OUT;
    DRCWB(avmplus::AvmString) m_ROLL_OVER;
};
#define DECLARE_SLOTS_MouseEventClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
    protected: \
        REALLY_INLINE avmplus::AvmString get_CLICK() const { return m_slots_MouseEventClass.get_CLICK(); } \
        REALLY_INLINE avmplus::AvmString get_DOUBLE_CLICK() const { return m_slots_MouseEventClass.get_DOUBLE_CLICK(); } \
        REALLY_INLINE avmplus::AvmString get_MOUSE_DOWN() const { return m_slots_MouseEventClass.get_MOUSE_DOWN(); } \
        REALLY_INLINE avmplus::AvmString get_MOUSE_MOVE() const { return m_slots_MouseEventClass.get_MOUSE_MOVE(); } \
        REALLY_INLINE avmplus::AvmString get_MOUSE_OUT() const { return m_slots_MouseEventClass.get_MOUSE_OUT(); } \
        REALLY_INLINE avmplus::AvmString get_MOUSE_OVER() const { return m_slots_MouseEventClass.get_MOUSE_OVER(); } \
        REALLY_INLINE avmplus::AvmString get_MOUSE_UP() const { return m_slots_MouseEventClass.get_MOUSE_UP(); } \
        REALLY_INLINE avmplus::AvmString get_MOUSE_WHEEL() const { return m_slots_MouseEventClass.get_MOUSE_WHEEL(); } \
        REALLY_INLINE avmplus::AvmString get_ROLL_OUT() const { return m_slots_MouseEventClass.get_ROLL_OUT(); } \
        REALLY_INLINE avmplus::AvmString get_ROLL_OVER() const { return m_slots_MouseEventClass.get_ROLL_OVER(); } \
    private: \
        avmplus::NativeID::_vtx_as3_MouseEventClassSlots m_slots_MouseEventClass
//-----------------------------------------------------------

// flash.events::MouseEvent
//-----------------------------------------------------------
class _vtx_as3_MouseEventSlots
{
    friend class SlotOffsetsAndAsserts;
public:
    REALLY_INLINE double get_private_mLocalX() const { return m_private_mLocalX; }
    void set_private_mLocalX(double newVal);
    REALLY_INLINE double get_private_mLocalY() const { return m_private_mLocalY; }
    void set_private_mLocalY(double newVal);
private:
    double m_private_mLocalX;
    double m_private_mLocalY;
};
REALLY_INLINE void _vtx_as3_MouseEventSlots::set_private_mLocalX(double newVal) { m_private_mLocalX = newVal; }
REALLY_INLINE void _vtx_as3_MouseEventSlots::set_private_mLocalY(double newVal) { m_private_mLocalY = newVal; }
#define DECLARE_SLOTS_MouseEvent \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
    protected: \
        REALLY_INLINE double get_private_mLocalX() const { return m_slots_MouseEvent.get_private_mLocalX(); } \
        REALLY_INLINE void set_private_mLocalX(double newVal) { m_slots_MouseEvent.set_private_mLocalX(newVal); } \
        REALLY_INLINE double get_private_mLocalY() const { return m_slots_MouseEvent.get_private_mLocalY(); } \
        REALLY_INLINE void set_private_mLocalY(double newVal) { m_slots_MouseEvent.set_private_mLocalY(newVal); } \
    private: \
        avmplus::NativeID::_vtx_as3_MouseEventSlots m_slots_MouseEvent
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
    REALLY_INLINE avmplus::AvmBox get_flash_events_DEBUG_EVENTDISPATCHER() const { return m_flash_events_DEBUG_EVENTDISPATCHER; }
    REALLY_INLINE avmplus::AvmObject get_private_mTarget() const { return m_private_mTarget; }
    void set_private_mTarget(::vtx::as3::EventDispatcher* obj, avmplus::AvmObject newVal);
    REALLY_INLINE ::vtx::as3::Dictionary* get_private_mHandlers() const { return m_private_mHandlers; }
    void set_private_mHandlers(::vtx::as3::EventDispatcher* obj, ::vtx::as3::Dictionary* newVal);
private:
    ATOM_WB m_flash_events_DEBUG_EVENTDISPATCHER;
    DRCWB(avmplus::AvmObject) m_private_mTarget;
    DRCWB(::vtx::as3::Dictionary*) m_private_mHandlers;
};
REALLY_INLINE void _vtx_as3_EventDispatcherSlots::set_private_mTarget(::vtx::as3::EventDispatcher* obj, avmplus::AvmObject newVal)
{
    m_private_mTarget.set(((ScriptObject*)obj)->gc(), obj, newVal);
}
REALLY_INLINE void _vtx_as3_EventDispatcherSlots::set_private_mHandlers(::vtx::as3::EventDispatcher* obj, ::vtx::as3::Dictionary* newVal)
{
    m_private_mHandlers.set(((ScriptObject*)obj)->gc(), obj, newVal);
}
#define DECLARE_SLOTS_EventDispatcher \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
    protected: \
        REALLY_INLINE avmplus::AvmBox get_flash_events_DEBUG_EVENTDISPATCHER() const { return m_slots_EventDispatcher.get_flash_events_DEBUG_EVENTDISPATCHER(); } \
        REALLY_INLINE avmplus::AvmObject get_private_mTarget() const { return m_slots_EventDispatcher.get_private_mTarget(); } \
        REALLY_INLINE void set_private_mTarget(avmplus::AvmObject newVal) { m_slots_EventDispatcher.set_private_mTarget(this, newVal); } \
        REALLY_INLINE ::vtx::as3::Dictionary* get_private_mHandlers() const { return m_slots_EventDispatcher.get_private_mHandlers(); } \
        REALLY_INLINE void set_private_mHandlers(::vtx::as3::Dictionary* newVal) { m_slots_EventDispatcher.set_private_mHandlers(this, newVal); } \
    private: \
        avmplus::NativeID::_vtx_as3_EventDispatcherSlots m_slots_EventDispatcher
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
    REALLY_INLINE avmplus::AvmBool32 get_flash_display_DEBUG_DISPLAYOBJECT() const { return m_flash_display_DEBUG_DISPLAYOBJECT; }
private:
    avmplus::AvmBool32 m_flash_display_DEBUG_DISPLAYOBJECT;
};
#define DECLARE_SLOTS_DisplayObject \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
    protected: \
        REALLY_INLINE avmplus::AvmBool32 get_flash_display_DEBUG_DISPLAYOBJECT() const { return m_slots_DisplayObject.get_flash_display_DEBUG_DISPLAYOBJECT(); } \
    private: \
        avmplus::NativeID::_vtx_as3_DisplayObjectSlots m_slots_DisplayObject
//-----------------------------------------------------------

// flash.utils::Timer$
//-----------------------------------------------------------
class _vtx_as3_TimerClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_TimerClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::_vtx_as3_TimerClassSlots EmptySlotsStruct_TimerClass
//-----------------------------------------------------------

// flash.utils::Timer
//-----------------------------------------------------------
class _vtx_as3_TimerSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_Timer \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::_vtx_as3_TimerSlots EmptySlotsStruct_Timer
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

// flash.display::Loader$
//-----------------------------------------------------------
class _vtx_as3_LoaderClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_LoaderClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::_vtx_as3_LoaderClassSlots EmptySlotsStruct_LoaderClass
//-----------------------------------------------------------

// flash.display::Loader
//-----------------------------------------------------------
class _vtx_as3_LoaderSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_Loader \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::_vtx_as3_LoaderSlots EmptySlotsStruct_Loader
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

// flash.display::Stage$
//-----------------------------------------------------------
class _vtx_as3_StageClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_StageClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::_vtx_as3_StageClassSlots EmptySlotsStruct_StageClass
//-----------------------------------------------------------

// flash.display::Stage
//-----------------------------------------------------------
class _vtx_as3_StageSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_Stage \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::_vtx_as3_StageSlots EmptySlotsStruct_Stage
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
    REALLY_INLINE avmplus::AvmBox get_flash_display_DEBUG_MOVIECLIP() const { return m_flash_display_DEBUG_MOVIECLIP; }
    REALLY_INLINE ::vtx::as3::Dictionary* get_private_mFrameScripts() const { return m_private_mFrameScripts; }
    void set_private_mFrameScripts(::vtx::as3::MovieClip* obj, ::vtx::as3::Dictionary* newVal);
private:
    ATOM_WB m_flash_display_DEBUG_MOVIECLIP;
    DRCWB(::vtx::as3::Dictionary*) m_private_mFrameScripts;
};
REALLY_INLINE void _vtx_as3_MovieClipSlots::set_private_mFrameScripts(::vtx::as3::MovieClip* obj, ::vtx::as3::Dictionary* newVal)
{
    m_private_mFrameScripts.set(((ScriptObject*)obj)->gc(), obj, newVal);
}
#define DECLARE_SLOTS_MovieClip \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
    protected: \
        REALLY_INLINE avmplus::AvmBox get_flash_display_DEBUG_MOVIECLIP() const { return m_slots_MovieClip.get_flash_display_DEBUG_MOVIECLIP(); } \
        REALLY_INLINE ::vtx::as3::Dictionary* get_private_mFrameScripts() const { return m_slots_MovieClip.get_private_mFrameScripts(); } \
        REALLY_INLINE void set_private_mFrameScripts(::vtx::as3::Dictionary* newVal) { m_slots_MovieClip.set_private_mFrameScripts(this, newVal); } \
    private: \
        avmplus::NativeID::_vtx_as3_MovieClipSlots m_slots_MovieClip
//-----------------------------------------------------------

} }

#endif // __FLASH_GLUE_H__

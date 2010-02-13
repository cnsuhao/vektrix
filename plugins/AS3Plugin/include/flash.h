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
    class ArrayObject; //Array
}

namespace vtx { namespace as3 {
    class DisplayObject; //flash.display::DisplayObject
    class DisplayObjectClass; //flash.display::DisplayObject$
    class DisplayObjectContainer; //flash.display::DisplayObjectContainer
    class DisplayObjectContainerClass; //flash.display::DisplayObjectContainer$
    class EventDispatcher; //flash.events::EventDispatcher
    class EventDispatcherClass; //flash.events::EventDispatcher$
    class EventHandler; //EventHandler
    class EventHandlerClass; //EventHandler$
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
const uint32_t abcclass_flash_events_Event = 0;
const uint32_t abcclass_flash_events_IEventDispatcher = 1;
const uint32_t abcclass_flash_events_NetStatusEvent = 2;
const uint32_t abcclass_flash_events_MouseEvent = 3;
const uint32_t abcclass_flash_events_EventDispatcher = 4;
const uint32_t abcclass_EventHandler = 5;
const uint32_t abcclass_flash_display_ActionScriptVersion = 6;
const uint32_t abcclass_flash_display_IBitmapDrawable = 7;
const uint32_t abcclass_flash_display_BitmapDataChannel = 8;
const uint32_t abcclass_flash_display_BlendMode = 9;
const uint32_t abcclass_flash_display_CapsStyle = 10;
const uint32_t abcclass_flash_display_ColorCorrection = 11;
const uint32_t abcclass_flash_display_ColorCorrectionSupport = 12;
const uint32_t abcclass_flash_display_FocusDirection = 13;
const uint32_t abcclass_flash_display_FrameLabel = 14;
const uint32_t abcclass_flash_display_GradientType = 15;
const uint32_t abcclass_flash_display_Graphics = 16;
const uint32_t abcclass_flash_display_IGraphicsFill = 17;
const uint32_t abcclass_flash_display_IGraphicsData = 18;
const uint32_t abcclass_flash_display_IGraphicsPath = 19;
const uint32_t abcclass_flash_display_GraphicsPathCommand = 20;
const uint32_t abcclass_flash_display_GraphicsPathWinding = 21;
const uint32_t abcclass_flash_display_IGraphicsStroke = 22;
const uint32_t abcclass_flash_display_IDrawCommand = 23;
const uint32_t abcclass_flash_display_InterpolationMethod = 24;
const uint32_t abcclass_flash_display_JointStyle = 25;
const uint32_t abcclass_flash_display_LineScaleMode = 26;
const uint32_t abcclass_flash_display_LoaderInfo = 27;
const uint32_t abcclass_flash_display_NativeMenu = 28;
const uint32_t abcclass_flash_display_NativeMenuItem = 29;
const uint32_t abcclass_flash_display_NativeWindow = 30;
const uint32_t abcclass_flash_display_NativeWindowDisplayState = 31;
const uint32_t abcclass_flash_display_NativeWindowInitOptions = 32;
const uint32_t abcclass_flash_display_NativeWindowResize = 33;
const uint32_t abcclass_flash_display_NativeWindowSystemChrome = 34;
const uint32_t abcclass_flash_display_NativeWindowType = 35;
const uint32_t abcclass_flash_display_PixelSnapping = 36;
const uint32_t abcclass_flash_display_Scene = 37;
const uint32_t abcclass_flash_display_Screen = 38;
const uint32_t abcclass_flash_display_Shader = 39;
const uint32_t abcclass_flash_display_ShaderData = 40;
const uint32_t abcclass_flash_display_ShaderInput = 41;
const uint32_t abcclass_flash_display_ShaderJob = 42;
const uint32_t abcclass_flash_display_ShaderParameter = 43;
const uint32_t abcclass_flash_display_ShaderParameterType = 44;
const uint32_t abcclass_flash_display_ShaderPrecision = 45;
const uint32_t abcclass_flash_display_SpreadMethod = 46;
const uint32_t abcclass_flash_display_StageAlign = 47;
const uint32_t abcclass_flash_display_StageDisplayState = 48;
const uint32_t abcclass_flash_display_StageQuality = 49;
const uint32_t abcclass_flash_display_StageScaleMode = 50;
const uint32_t abcclass_flash_display_SWFVersion = 51;
const uint32_t abcclass_flash_display_TriangleCulling = 52;
const uint32_t abcclass_flash_display_BitmapData = 53;
const uint32_t abcclass_flash_display_DisplayObject = 54;
const uint32_t abcclass_flash_display_GraphicsBitmapFill = 55;
const uint32_t abcclass_flash_display_GraphicsEndFill = 56;
const uint32_t abcclass_flash_display_GraphicsGradientFill = 57;
const uint32_t abcclass_flash_display_GraphicsShaderFill = 58;
const uint32_t abcclass_flash_display_GraphicsSolidFill = 59;
const uint32_t abcclass_flash_display_GraphicsPath = 60;
const uint32_t abcclass_flash_display_GraphicsTrianglePath = 61;
const uint32_t abcclass_flash_display_GraphicsStroke = 62;
const uint32_t abcclass_flash_display_AVM1Movie = 63;
const uint32_t abcclass_flash_display_Bitmap = 64;
const uint32_t abcclass_flash_display_InteractiveObject = 65;
const uint32_t abcclass_flash_display_MorphShape = 66;
const uint32_t abcclass_flash_display_Shape = 67;
const uint32_t abcclass_flash_display_DisplayObjectContainer = 68;
const uint32_t abcclass_flash_display_SimpleButton = 69;
const uint32_t abcclass_flash_display_Loader = 70;
const uint32_t abcclass_flash_display_Sprite = 71;
const uint32_t abcclass_flash_display_Stage = 72;
const uint32_t abcclass_flash_display_MovieClip = 73;
const uint32_t abcclass_flash_text_AntiAliasType = 74;
const uint32_t abcclass_flash_text_AttributeRange = 75;
const uint32_t abcclass_flash_text_CSMSettings = 76;
const uint32_t abcclass_flash_text_Font = 77;
const uint32_t abcclass_flash_text_FontStyle = 78;
const uint32_t abcclass_flash_text_FontType = 79;
const uint32_t abcclass_flash_text_GridFitType = 80;
const uint32_t abcclass_flash_text_StaticText = 81;
const uint32_t abcclass_flash_text_StyleSheet = 82;
const uint32_t abcclass_flash_text_TextColorType = 83;
const uint32_t abcclass_flash_text_TextDisplayMode = 84;
const uint32_t abcclass_flash_text_TextExtent = 85;
const uint32_t abcclass_flash_text_TextField = 86;
const uint32_t abcclass_flash_text_TextFieldAutoSize = 87;
const uint32_t abcclass_flash_text_TextFieldType = 88;
const uint32_t abcclass_flash_text_TextFormat = 89;
const uint32_t abcclass_flash_text_TextFormatAlign = 90;
const uint32_t abcclass_flash_text_TextLineMetrics = 91;
const uint32_t abcclass_flash_text_TextRenderer = 92;
const uint32_t abcclass_flash_text_TextSnapshot = 93;

/* methods */
const uint32_t EventHandler_handle = 41;
const uint32_t flash_display_DisplayObject_x_get = 141;
const uint32_t flash_display_DisplayObject_x_set = 142;
const uint32_t flash_display_DisplayObject_y_get = 143;
const uint32_t flash_display_DisplayObject_y_set = 144;
const uint32_t flash_display_DisplayObject_rotation_get = 145;
const uint32_t flash_display_DisplayObject_rotation_set = 146;
const uint32_t flash_text_StaticText_text_get = 203;
const uint32_t flash_text_TextField_htmlText_get = 214;
const uint32_t flash_text_TextField_htmlText_set = 215;

extern AvmBox EventHandler_handle_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
extern double flash_display_DisplayObject_x_get_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
extern AvmBox flash_display_DisplayObject_x_set_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
extern double flash_display_DisplayObject_y_get_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
extern AvmBox flash_display_DisplayObject_y_set_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
extern double flash_display_DisplayObject_rotation_get_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
extern AvmBox flash_display_DisplayObject_rotation_set_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
extern AvmBox flash_text_StaticText_text_get_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
extern AvmBox flash_text_TextField_htmlText_get_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
extern AvmBox flash_text_TextField_htmlText_set_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);

#ifdef VMCFG_INDIRECT_NATIVE_THUNKS

extern AvmBox flash_v2a_oo_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define EventHandler_handle_thunk  flash_v2a_oo_thunk

extern AvmBox flash_v2a_od_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_display_DisplayObject_y_set_thunk  flash_v2a_od_thunk
#define flash_display_DisplayObject_rotation_set_thunk  flash_v2a_od_thunk
#define flash_display_DisplayObject_x_set_thunk  flash_v2a_od_thunk

extern AvmBox flash_v2a_os_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_text_TextField_htmlText_set_thunk  flash_v2a_os_thunk

extern double flash_d2d_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_display_DisplayObject_rotation_get_thunk  flash_d2d_o_thunk
#define flash_display_DisplayObject_x_get_thunk  flash_d2d_o_thunk
#define flash_display_DisplayObject_y_get_thunk  flash_d2d_o_thunk

extern AvmBox flash_s2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_text_TextField_htmlText_get_thunk  flash_s2a_o_thunk
#define flash_text_StaticText_text_get_thunk  flash_s2a_o_thunk

#endif // VMCFG_INDIRECT_NATIVE_THUNKS

class SlotOffsetsAndAsserts;
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
    REALLY_INLINE ArrayObject* get_private_mListeners() const { return m_private_mListeners; }
    void set_private_mListeners(::vtx::as3::EventDispatcher* obj, ArrayObject* newVal);
private:
    DRCWB(ArrayObject*) m_private_mListeners;
};
REALLY_INLINE void _vtx_as3_EventDispatcherSlots::set_private_mListeners(::vtx::as3::EventDispatcher* obj, ArrayObject* newVal)
{
    m_private_mListeners.set(((ScriptObject*)obj)->gc(), obj, newVal);
}
#define DECLARE_SLOTS_EventDispatcher \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
    protected: \
        REALLY_INLINE ArrayObject* get_private_mListeners() const { return m_slots_EventDispatcher.get_private_mListeners(); } \
        REALLY_INLINE void set_private_mListeners(ArrayObject* newVal) { m_slots_EventDispatcher.set_private_mListeners(this, newVal); } \
    private: \
        avmplus::NativeID::_vtx_as3_EventDispatcherSlots m_slots_EventDispatcher
//-----------------------------------------------------------

// EventHandler$
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

// EventHandler
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

} }

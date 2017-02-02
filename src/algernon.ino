/* -*- mode: c++ -*-
 * Model01-Sketch -- algernon's Model01 Sketch
 * Copyright (C) 2016, 2017  Gergely Nagy
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#define AKELA_HOSTOS_GUESSER 1

#include <Keyboardio-Macros.h>
#include <Keyboardio-MouseKeys.h>
#include <Keyboardio-LEDControl.h>
#include <KeyboardioFirmware.h>

#include <Akela-KeyLogger.h>

#include "LED-Off.h"
#include <Keyboardio-LEDEffect-Chase.h>
#include <Keyboardio-LEDEffect-Rainbow.h>

#include <Akela-LangPack-Hungarian.h>
#include <Akela-LED-ActiveModColor.h>
#include <Akela-LED-Stalker.h>
#include <Akela-Escape-OneShot.h>

#include "Layers.h"

#include "Colormap.h"
#include "Leader.h"
#include "OneShot.h"
#include "TapDance.h"
#include "ShapeShifter.h"
#include "MagicCombo.h"
#include "Syster.h"

using namespace Akela::LangPack;

#define R(n) (Key){.raw = n}
#define MW(d) Key_mouseWarp ## d
#define MM(d) Key_mouse ## d

enum {
  APPSEL_MUSIC,
  APPSEL_CHAT,
  APPSEL_EMACS,
  APPSEL_TERM,
  APPSEL_WEB
};

const Key keymaps[][ROWS][COLS] PROGMEM = {
  [_DVORAK] = KEYMAP_STACKED
  (
    Key_F11       ,Key_9     ,Key_7     ,Key_5      ,Key_3 ,Key_1 ,TD(TMUX)
   ,Key_Backtick  ,Key_Quote ,Key_Comma ,Key_Period ,Key_P ,Key_Y ,TD(LPB)
   ,Key_Tab       ,Key_A     ,Key_O     ,Key_E      ,Key_U ,Key_I
   ,Key_playPause ,Key_Slash ,Key_Q     ,Key_J      ,Key_K ,Key_X ,Key_LAlt

   ,TD(COLON) ,Key_Backspace ,Key_LShift ,Key_Esc
   ,MO(_NAV)

   ,TD(TMUXP) ,Key_0 ,Key_2 ,Key_4 ,Key_6 ,Key_8 ,TD(MNP)
   ,TD(RPB)   ,Key_F ,Key_G ,Key_C ,Key_R ,Key_L ,Key_Backslash
              ,Key_D ,Key_H ,Key_T ,Key_N ,Key_S ,Key_Equals
   ,Key_LCtrl ,Key_B ,Key_M ,Key_W ,Key_V ,Key_Z ,LEAD(MAIN)

   ,TD(GUI) ,Key_Enter ,Key_Space ,Key_Minus
   ,MO(_HUN)
  ),

  [_ADORE] = KEYMAP_STACKED
  (
    Key_F11       ,Key_9 ,Key_7 ,Key_5      ,Key_3     ,Key_1       ,TD(TMUX)
   ,Key_Backslash ,Key_X ,Key_W ,Key_C      ,Key_H     ,Key_F       ,TD(LPB)
   ,Key_Tab       ,Key_A ,Key_O ,Key_E      ,Key_I     ,Key_U
   ,Key_playPause ,Key_Z ,Key_Q ,Key_Quote  ,Key_Comma ,Key_Period  ,Key_LAlt

   ,TD(COLON) ,Key_Backspace ,Key_LShift ,Key_Esc
   ,MO(_NAV)

   ,TD(TMUXP) ,Key_0 ,Key_2 ,Key_4 ,Key_6 ,Key_8     ,TD(MNP)
   ,TD(RPB)   ,Key_M ,Key_G ,Key_L ,Key_P ,Key_Slash ,Key_Backslash
              ,Key_D ,Key_R ,Key_T ,Key_N ,Key_S     ,Key_Equals
   ,Key_LCtrl ,Key_B ,Key_K ,Key_V ,Key_Y ,Key_J     ,LEAD(MAIN)

   ,Key_LGUI ,Key_Enter ,Key_Space ,Key_Minus
   ,MO(_HUN)
  ),

  [_NAV] = KEYMAP_STACKED
  (
    ___ ,Key_F9 ,Key_F7 ,Key_F5 ,Key_F3 ,Key_F1 ,XXX
   ,XXX ,XXX    ,MM(Up) ,XXX    ,XXX    ,XXX    ,XXX
   ,XXX ,MM(L)  ,MM(Dn) ,MM(R)  ,XXX    ,XXX
   ,XXX ,XXX    ,XXX    ,XXX    ,XXX    ,XXX    ,___

   ,Key_volumeDown ,Key_volumeUp ,___ ,Key_volumeMute
   ,___

   ,LGUI(Key_L) ,Key_F10 ,Key_F2     ,Key_F4      ,Key_F6     ,Key_F8 ,XXX
   ,XXX         ,XXX     ,Key_Home   ,Key_UpArrow ,Key_End    ,XXX  ,XXX
                ,XXX     ,Key_LArrow ,Key_DnArrow ,Key_RArrow ,XXX  ,XXX
   ,___         ,XXX     ,XXX        ,XXX         ,XXX        ,XXX  ,XXX

   ,MM(BtnL) ,Key_PageDn ,Key_PageUp ,MM(BtnR)
   ,MO(_EMPTY)
  ),

  [_HUN] = KEYMAP_STACKED
  (
    XXX ,XXX       ,XXX        ,XXX       ,XXX        ,XXX       ,XXX
   ,XXX ,XXX       ,R(HUN_ODA) ,XXX       ,R(HUN_UDA) ,XXX       ,XXX
   ,XXX ,R(HUN_AA) ,R(HUN_OA)  ,R(HUN_EA) ,R(HUN_UA)  ,R(HUN_IA)
   ,XXX ,XXX       ,R(HUN_OU)  ,XXX       ,R(HUN_UU)  ,XXX       ,XXX

   ,XXX ,___ ,___ ,___
   ,MO(_EMPTY)

   ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX
   ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX
        ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX
   ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX

   ,XXX ,XXX ,XXX ,XXX
   ,___
  ),

  [_EMPTY] = KEYMAP_STACKED
  (
    XXX ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX
   ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX
   ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX
   ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX
   ,XXX ,XXX ,XXX ,XXX
   ,___

   ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX
   ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX
        ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX
   ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX

   ,XXX ,XXX ,XXX ,XXX
   ,___
   ),

  [_APPSEL] = KEYMAP_STACKED
  (
    XXX ,M(APPSEL_MUSIC) ,M(APPSEL_CHAT) ,M(APPSEL_EMACS) ,M(APPSEL_TERM) ,M(APPSEL_WEB) ,XXX
   ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX
   ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX
   ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX
   ,XXX ,XXX ,XXX ,XXX
   ,XXX

   ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX
   ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX
   ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX
   ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX

   ,XXX ,XXX ,XXX ,XXX
   ,XXX
   ),

};

const macro_t *macroAction(uint8_t macroIndex, uint8_t keyState) {
  if (!key_toggled_on (keyState))
    return MACRO_NONE;

  switch (macroIndex) {
  case APPSEL_MUSIC:
    Serial.println (F("appsel:music"));
    break;
  case APPSEL_CHAT:
    Serial.println (F("appsel:chat"));
    break;
  case APPSEL_EMACS:
    Serial.println (F("appsel:emacs"));
    break;
  case APPSEL_TERM:
    Serial.println (F("appsel:term"));
    break;
  case APPSEL_WEB:
    Serial.println (F("appsel:web"));
    break;
  }
  return MACRO_NONE;
}

void setup () {
  Serial.begin(9600);

  Mouse.begin();
  AbsoluteMouse.begin();

  StalkerEffect.configure (STALKER (BlazingTrail, NULL));

  Keyboardio.use (&LEDControl,
                  //&KeyLogger,
                  &StalkerEffect,
                  NULL);

  algernon::Leader::configure ();
  algernon::Syster::configure ();
  algernon::TapDance::configure ();
  algernon::OneShot::configure ();
  algernon::ShapeShifter::configure ();
  algernon::MagicCombo::configure ();

  Keyboardio.use (&EscapeOneShot,
                  &Macros,
                  &Hungarian,
                  &MouseKeys,
                  &LEDOff, &LEDRainbowWaveEffect, &LEDChaseEffect,
                  //&HeatmapEffect,

                  NULL);

  Keyboardio.setup (KEYMAP_SIZE);

  algernon::Colormap::configure ();
  Keyboardio.use (&ActiveModColorEffect, NULL);
}

void loop () {
  Keyboardio.loop();
}

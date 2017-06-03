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

#include "00-config.h"

#include <Kaleidoscope-LED-Palette-Theme.h>
#include <Kaleidoscope-Colormap.h>
#include <Kaleidoscope-Focus.h>

#include "Layers.h"

namespace algernon {
  namespace Colormap {

    void
    configure (void) {
      Kaleidoscope.use (&ColormapEffect, &LEDPaletteTheme, NULL);

      ColormapEffect.max_layers (LAYER_MAX);
      ColormapEffect.activate ();

      Focus.addHook (FOCUS_HOOK_LEDPALETTETHEME);
      Focus.addHook (FOCUS_HOOK_COLORMAP);
    }
  };
};

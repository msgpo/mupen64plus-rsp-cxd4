/*
 * mupen64plus-rsp-cxd4 - RSP Interpreter
 * Copyright (C) 2012-2013  RJ 'Iconoclast' Swedlow
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include "vu.h"

static void VEQ(int vd, int vs, int vt, int e)
{
    int eq; /* equal, unless (NOTEQUAL) */
    register int i;

    VCC = 0x0000;
    VCO >>= 8; /* We don't use the CARRY bits of VCO.  VCO will be cleared. */
    for (i = 0; i < 8; i++)
    {
        const short VS = VR[vs][i];
        const short VT = VR[vt][ei[e][i]];

        eq = (VS == VT) & !(VCO & 1);
        VCC |= eq << i;
        VACC[i].s[LO] = VT;
        VCO >>= 1;
    }
    for (i = 0; i < 8; i++)
        VR[vd][i] = VACC[i].s[LO];
    /* VCO = 0x0000; /* We already cleared VCO by `VCO >>= 1` 16 times. */
    return;
}

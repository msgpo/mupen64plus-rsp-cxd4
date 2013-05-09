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

static void VMADM(int vd, int vs, int vt, int e)
{
    register int i;

    for (i = 0; i < 8; i++)
        VACC[i].DW += VR[vs][i] * (unsigned short)VR[vt][ei[e][i]];
    SIGNED_CLAMP(vd, 0);
    for (i = 0; i < 8; i++) /* Sign-clamp bits 31..16 of ACC to dest. VR. */
        if (CLAMP_BASE(i, 16) < -32768)
            VR[vd][i] = -32768; /* element underflow */
        else if (CLAMP_BASE(i, 16) > +32767)
            VR[vd][i] = +32767; /* element overflow */
        else
            VR[vd][i] = CLAMP_BASE(i, 16) & 0x0000FFFF;
    return;
}

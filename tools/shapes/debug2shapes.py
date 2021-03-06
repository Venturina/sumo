#!/usr/bin/env python
# Eclipse SUMO, Simulation of Urban MObility; see https://eclipse.org/sumo
# Copyright (C) 2010-2018 German Aerospace Center (DLR) and others.
# This program and the accompanying materials
# are made available under the terms of the Eclipse Public License v2.0
# which accompanies this distribution, and is available at
# http://www.eclipse.org/legal/epl-v20.html
# SPDX-License-Identifier: EPL-2.0

# @file    debug2shapes.py
# @author  Jakob Erdmann
# @date    2016-02-20
# @version $Id$


"""build polygon/poi file from cmdline geometry input as generated by sumo debug output
"""
from __future__ import print_function
import sys
from collections import defaultdict

COLORS = ["red", "green", "blue", "yellow", "cyan", "magenta"]

outfile = sys.argv[1]
shapesParts = sys.argv[2].split()
if len(sys.argv) == 4:
    fill = bool(sys.argv[3])
else:
    fill = False

shapes = []
shape = []
ids = defaultdict(lambda: 0)
id = ""
for p in shapesParts:
    if "=" in p:
        if shape:
            shapes.append((id, shape))
            shape = []
        id, pos = p.split("=")
        ids[id] += 1
        if ids[id] > 1:
            id += "_%s" % ids[id]
        shape.append(pos)
    else:
        shape.append(p)

if shape:
    shapes.append((id, shape))


with open(outfile, 'w') as outf:
    numPoly = 0
    numPoi = 0
    if shapes:
        outf.write("<shapes>\n")
        for i, (id, shape) in enumerate(shapes):
            if len(shape) > 1:
                outf.write('    <poly id="%s" shape="%s" color="%s" fill="%s"/>\n' % (
                    id, " ".join(shape), COLORS[i % len(COLORS)], fill))
                numPoly += 1
            else:
                xyz = shape[0].split(',')
                if len(xyz) >= 2:
                    x = xyz[0]
                    y = xyz[1]
                    outf.write('    <poi id="%s" x="%s" y="%s" color="%s"/>\n' % (
                        id, x, y, COLORS[i % len(COLORS)]))
                    numPoi += 1
        outf.write("</shapes>\n")
    print("wrote %s polygons and %s POIs to '%s'" % (numPoly, numPoi, outfile))

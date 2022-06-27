<!--
SPDX-FileCopyrightText: 2022 Ignacy Kajdan <ignacy.kajdan@gmail.com>
SPDX-License-Identifier: GPL-3.0-or-later
-->

# Lychee Picture of the Day Provider Plugin

Plasma POTD plugin that will fetch a random picture from your self-hosted Lychee instance.

## Installation

1. Clone this repository:

    `git clone https://invent.kde.org/verahawk/lychee-potd-provider && cd lychee-potd-provider`

1. Install required build dependencies:

    `TODO`

1. Build:

    `cmake -B build/ . && cmake --build build/`

1. Install:

    `sudo cmake --install build/`

1. Restart Plasma:

    `plasmashell --replace`

To uninstall run: `cd build/ && sudo make uninstall`

## Configuration

Right-click the desktop → Provide: Lychee

## License

    Lychee Picture of the Day Provider Plugin
    Copyright © 2022 Ignacy Kajdan

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program. If not, see <https://www.gnu.org/licenses/>.

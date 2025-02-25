<!--
SPDX-FileCopyrightText: 2022 Ignacy Kajdan <ignacy.kajdan@gmail.com>
SPDX-License-Identifier: GPL-3.0-or-later
-->

# Lychee Picture of the Day Provider Plugin

Plasma POTD plugin that will fetch a random picture from your self-hosted Lychee instance.

## Build & Install

Run the following commands to build and install the plasmoid:

```
cmake -B build/ .
cmake --build build/
sudo cmake --install build/
```

Restart your session, or run the following command to reload Plasma: `plasmashell --replace`.

## License

This project is licensed under the terms of the GNU General Public License version 3 or later. See the [LICENSE](LICENSE) file for details.

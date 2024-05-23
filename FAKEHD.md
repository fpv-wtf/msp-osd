# FakeHD

Betaflight's (before 4.4) OSD supports a 30 * 16 Grid, which looks large/blocky when displayed in the DJI Goggles.

For versions of Betaflight before 4.4 (or other FC firmwares without HD support), as a workaround, we have a mode called "FakeHD". It chops up the OSD into sections and positions them evenly around an HD grid (with gaps between) - the way this is done is configurable, explained below. This then allows the use of smaller fonts - so it looks nicer/more in keeping with the built in Goggles OSD (but you still only have 30 columns / 16 rows to configure.... and you have the gaps to contend with).

A diagram to help...

| Before (in Configurator)                               | After (in Goggles)                                  |
| ------------------------------------------------------ | --------------------------------------------------- |
| ![FakeHD Before](/docs/img/fakehd_before.png "Before") | ![FakeHD After](/docs/img/fakehd_after.png "After") |

##### To configure/enable:

Visit https://fpv.wtf/package/fpv-wtf/msp-osd with your goggles connected, and check "Fake HD"

Optionally, place custom fonts in the root of your sd card, using the names `font_bf_hd.png`

Configuration of the grid is also possible; see below.

No air unit/vista config is required.

##### Menu Switching - Getting rid of gaps when displaying Menu / Post Flight Stats + displaying centered:

In order to have menus (accessible in Betaflight using stick commands) and post-flight stats appear in the center of the screen while using FakeHD, rather than having gaps + looking broken, you should set up menu switching.

FakeHD can use the presence/absence of a character in the OSD as a switch to indicate when you are in regular OSD mode or in the menu/stats and switch to centering temporarily when needed.

By default, the `Throttle Position` icon is used (character 4) - but you can set any character you want. It needs to be something that doesn't flash or change in the regular OSD, and ideally (but not essential) something that is never in the menu/post flight stats. The icons next to various elements are obvious choices here. You can set this using the `fakehd_menu_switch` configuration parameter.

Betaflight has a list here: https://github.com/betaflight/betaflight/blob/master/docs/osd.md


If you want to use FakeHD with some other Flight Controller, you will need to find an appropriate icon. (Let us know - we can include the information here).

Finally, if you don't have anything in your OSD that works for menu switching, you can hide the menu switching character and the subsequent 5 characters, allowing you to add the `Throttle Position` element but not have to see it on screen. This is enabled by setting `fakehd_hide_menu_switch` to true.

Notes:

 - Because of this switching feature, if you change to a different quad or OSD config (specifically the switch element is in a different place), FakeHD will center - you will need to reboot your Goggles to get it to recognise the switch element in a different location.

 - Also because of this switching, if you are editing OSD in the configurator with the goggles on to preview and you move the switching element around, it will cause the gaps to be disabled and everything to center. The new location of the switching element will be found next time you reboot the goggles and it'll work as normal.

##### I don't want gaps at all...

Set config `fakehd_lock_center` to true and the center locking used for the menu / post flight stats will be enabled permanently (ie: you fly with it as well) - basically it places your 30 x 16 SD grid into the middle of an HD grid, there's never any gaps - see diagram below + compare to diagrams above.

| After/Centered (in Goggles) `fakehd_lock_center`                               |
| ------------------------------------------------------------------------------ |
| <img src="/docs/img/fakehd_centered.png" alt="After / Centered"  height=200 /> |

##### Customising the default FakeHD grid.

By default, FakeHD positions your SD grid into the HD grid as per the before/after diagram above.

If this doesn't work for you for whatever reason, some customisation is available. It's necessarily a little complicated.

Each row can be set to one of:

| Code | Description                                                                                                                    |
| ---- | ------------------------------------------------------------------------------------------------------------------------------ |
| L    | Left aligned, the SD row occupies cell 1-30, no gaps                                                                           |
| C    | Center aligned, the SD row occupies cell 16-45, no gaps                                                                        |
| R    | Right aligned, , the SD row occupies cell 31-60, no gaps                                                                       |
| W    | Split A - Row is split in 3, the FakeHD default, filling cells 1-10, 26-35, 51-60                                              |
| T    | Split B - Row is split in 2, touching the sides - filling cells 1-15 + 46-60                                                   |
| F    | Split C - Row is split in 2 and away from the sides - filling cells 11-25 + 36-50                                              |
| D    | DJI Special - Row is centered but pushed a little left; used to posiution the bottom row between the existing DJI OSD elements |

<img src="/docs/img/fakehd_rows.png" alt="Columns"  height=200 />

And then the columns as a whole can be set to one of:

| Code | Description                                                                 |
| ---- | --------------------------------------------------------------------------- |
| T    | Top aligned, OSD occupies rows 1-16                                         |
| M    | Center aligned, OSD occupies cells 4-19, no gaps                            |
| B    | Bottom aligned, , the OSD occupies rows 7-22                                |
| S    | Split - FakeHD default - split in 3, OSD occupies rows 1 - 5, 9 - 13, 17-22 |

Using the default row config; here's what they all look like:

| T                                                    | M                                                    | B                                                    | S                                                |
| ---------------------------------------------------- | ---------------------------------------------------- | ---------------------------------------------------- | ------------------------------------------------ |
| <img src="/docs/img/fakehd_columns_t.png" alt="T" /> | <img src="/docs/img/fakehd_columns_m.png" alt="M" /> | <img src="/docs/img/fakehd_columns_b.png" alt="B" /> | <img src="/docs/img/fakehd_after.png" alt="S" /> |

###### To configure rows

Rows config accepts a 16 character long string; each character configuring it's corresponding row. The default FakeHD config would be set like this:

`fakehd_rows = WWWWWWCCWWWWWWWD`

The characters are case sensitive, but the configurator will reject invalid characters.

###### To configure columns

Columns accepts a single character configuring how the whole grid is aligned. The default would be set like this:

`fakehd_columns = S`

The characters are case sensitive, but the configurator will reject invalid characters.


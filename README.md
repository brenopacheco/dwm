# DWM 6.1 compatible patches
![picture](./screenshot.png)  

This repository contains my personal use patched  DWM and 
the diff files found in suckless.org, modified to fit the 6.1 version.  
* The patches in ./patches folder are cross-compatible and may all be
applied together in the standard distribution of DWM 6.1 without 
reject hunks. These are:  

1.  activetagindicatorbar: changes bar icon for tags in status bar
2.  attachabove:           new clients attach above currently selected client
4.  center:                floating windows are spawn in the center of the screen
5.  fakefullscreen:        fullscreen only fills the client
6.  fsignal:               allows sending signals to dwm via xsetroot
7.  pertag-tab:            (pertag + tab) allows each tag to have a layout andmonocle show tabs
8.  push:                  adds bindings to move clients up/down the stac
9.  restartsig:            added signal for restarting dwm
10. ru-gaps-bottomstack:   (ru gaps + bottomstack) adds two new layouts and gaps around windows
10. staticmonoclesymbol:   keeps the monocle symbol always it is on
11. transparency:          adds transparency (requires transset-df)
12. xrdb:                  reads colors from .Xresources
13. zoomswap:              when swapping back stack to master remembers old position

* The patches in ./other_patches you can find the bottomstack patch 
without push and and other patches which will not conflict with others,
but will fail to patch properly, generating reject files for manual
handling. These are:

1. alternativetags: adds an alternative number tag list
2. bottomstack:     adds two new stack layouts
3. resizecorners:   snaps mouse to corners for resizing
4. systray:         adds a systray to dwm's bar

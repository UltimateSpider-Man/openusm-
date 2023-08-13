#!/bin/bash

export WINEPREFIX=/home/anzor/Games/USM
export WINEDEBUG=fixme-all
/home/anzor/.local/share/lutris/runners/wine/lutris-6.10-7-x86_64/bin/wine "/home/anzor/Games/USM/drive_c/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Utilities/bin/x86/fxc.exe" /nologo /T vs_1_1 /Ni /LD /Fx us_frontend_VS.txt us_frontend_VS.hlsl 



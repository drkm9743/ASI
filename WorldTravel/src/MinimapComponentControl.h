#pragma once

void InitMinimapComponentControl();

void SetMinimapComponentPosition(const char* name, const char* alignX, const char* alignY,
                                 float posX, float posY, float sizeX, float sizeY);

void RestoreMinimapComponents();

void RegisterMinimapNatives();

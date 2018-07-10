#pragma once

#include <Urho3D/Urho3DAll.h>

/// User defined event
namespace MyEvents
{
    // Start new level
    URHO3D_EVENT(E_SET_LEVEL, SetLevel)
    {
        URHO3D_PARAM(P_NAME, Name);
        URHO3D_PARAM(P_MESSAGE, Message);
    }


    // Open UI Window
    URHO3D_EVENT(E_OPEN_WINDOW, OpenWindow)
    {
        URHO3D_PARAM(P_NAME, Name);
    }
    // Close UI Window
    URHO3D_EVENT(E_CLOSE_WINDOW, CloseWindow)
    {
        URHO3D_PARAM(P_NAME, Name);
    }
    // When specific UI window is closed
    URHO3D_EVENT(E_WINDOW_CLOSED, WindowClosed)
    {
        URHO3D_PARAM(P_NAME, Name);
    }
    // Close all active UI Windows
    URHO3D_EVENT(E_CLOSE_ALL_WINDOWS, CloseAllWindows)
    {
        URHO3D_PARAM(P_NAME, Name);
    }

	URHO3D_EVENT(E_CONSOLE_COMMAND_ADD, ConsoleCommandAdd)
	{
		URHO3D_PARAM(P_NAME, ConsoleCommandName);
		URHO3D_PARAM(P_EVENT, ConsoleCommandEvent);
		URHO3D_PARAM(P_DESCRIPTION, ConsoleCommandDescription);
	}

	URHO3D_EVENT(E_CONSOLE_GLOBAL_VARIABLE_CHANGE, ConsoleGlobalVariableChange)
	{
		URHO3D_PARAM(P_NAME, GlobalVariableName);
		URHO3D_PARAM(P_VALUE, GlobalVariableValue);
	}

	URHO3D_EVENT(E_CONSOLE_GLOBAL_VARIABLE_CHANGED, ConsoleGlobalVariableChanged)
	{
		URHO3D_PARAM(P_NAME, GlobalVariableName);
		URHO3D_PARAM(P_VALUE, GlobalVariableValue);
	}

    // Save configuration JSON file
    URHO3D_EVENT(E_SAVE_CONFIG, SaveConfig)
    {
    }

    URHO3D_EVENT(E_ADD_CONFIG, AddConfig)
    {
        URHO3D_PARAM(P_NAME, Name);
    }

    URHO3D_EVENT(E_LOAD_CONFIG, LoadConfig)
    {
        URHO3D_PARAM(P_FILEPATH, Filepath);
        URHO3D_PARAM(P_PREFIX, Prefix);
    }

	URHO3D_EVENT(E_START_INPUT_MAPPING, StartInputMapping)
	{
		URHO3D_PARAM(P_CONTROL_ACTION, ControlAction);
	}

    static const unsigned COLLISION_TERRAIN_LEVEL = 1;
    static const unsigned COLLISION_PLAYER_LEVEL = 2;
    static const unsigned COLLISION_STATIC_OBJECTS = 4;
    static const unsigned COLLISION_DYNAMIC_OBJECTS = 8;
    static const unsigned COLLISION_PICKABLES = 16;
    static const unsigned COLLISION_ITEM_PICKER = 32;
}
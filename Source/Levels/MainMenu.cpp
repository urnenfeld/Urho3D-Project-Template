#include <Urho3D/Input/Input.h>
#include <Urho3D/Resource/Localization.h>
#include <Urho3D/UI/UIEvents.h>
#include <Urho3D/Input/Input.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/UI/UI.h>
#include <Urho3D/UI/Font.h>
#include "MainMenu.h"
#include "../Global.h"
#include "../MyEvents.h"
#include "../Audio/AudioManagerDefs.h"
#include "../Messages/Achievements.h"
#include "../AndroidEvents/ServiceCmd.h"

using namespace Levels;

const static int BUTTON_WIDTH = 180;
const static int BUTTON_HEIGHT = 40;
const static int BUTTON_SPACING = 10;
const static int BUTTON_FONT_SIZE = 16;

    /// Construct.
MainMenu::MainMenu(Context* context) :
    BaseLevel(context)
{
}

MainMenu::~MainMenu()
{
}

void MainMenu::Init()
{
    // Disable achievement showing for this level
    GetSubsystem<Achievements>()->SetShowAchievements(true);

    // Create the scene content
    CreateScene();

    // Create the UI content
    CreateUI();
}

void MainMenu::CreateScene()
{
    
}

void MainMenu::CreateUI()
{
    Input* input = GetSubsystem<Input>();
    if (!input->IsMouseVisible()) {
        input->SetMouseVisible(true);
    }

    if (data_.Contains("Message")) {
        auto* localization = GetSubsystem<Localization>();

        VariantMap& data = GetEventDataMap();
        data["Title"] = localization->Get("WARNING");
        data["Message"] = data_["Message"].GetString();
        data["Name"] = "PopupMessageWindow";
        data["Type"] = "warning";
        data["ClosePrevious"] = true;
        SendEvent(MyEvents::E_OPEN_WINDOW, data);
    }
    auto* localization = GetSubsystem<Localization>();

    int marginBottom = -4 * (BUTTON_HEIGHT + BUTTON_SPACING) - BUTTON_SPACING;
    _newGameButton = CreateButton(localization->Get("NEW_GAME"), BUTTON_WIDTH, IntVector2(-BUTTON_SPACING, marginBottom));
    _newGameButton->SetAlignment(HA_RIGHT, VA_BOTTOM);
    SubscribeToEvent(_newGameButton, E_RELEASED, [&](StringHash eventType, VariantMap& eventData) {
        VariantMap& data = GetEventDataMap();
        data["Name"] = "NewGameSettingsWindow";
        SendEvent(MyEvents::E_OPEN_WINDOW, data);

    });

    marginBottom += BUTTON_HEIGHT + BUTTON_SPACING;
    _settingsButton = CreateButton(localization->Get("SETTINGS"), BUTTON_WIDTH, IntVector2(-BUTTON_SPACING, marginBottom));
    _settingsButton->SetAlignment(HA_RIGHT, VA_BOTTOM);
    SubscribeToEvent(_settingsButton, E_RELEASED, [&](StringHash eventType, VariantMap& eventData) {
        VariantMap& data = GetEventDataMap();
        data["Name"] = "SettingsWindow";
        SendEvent(MyEvents::E_OPEN_WINDOW, data);
    });

    marginBottom += BUTTON_HEIGHT + BUTTON_SPACING;
    _achievementsButton = CreateButton(localization->Get("ACHIEVEMENTS"), BUTTON_WIDTH, IntVector2(-BUTTON_SPACING, marginBottom));
    _achievementsButton->SetAlignment(HA_RIGHT, VA_BOTTOM);
    SubscribeToEvent(_achievementsButton, E_RELEASED, [&](StringHash eventType, VariantMap& eventData) {
        VariantMap& data = GetEventDataMap();
        data["Name"] = "AchievementsWindow";
        SendEvent(MyEvents::E_OPEN_WINDOW, data);

        GetSubsystem<ServiceCmd>()->SendCmdMessage(10, 1);
    });

    marginBottom += BUTTON_HEIGHT + BUTTON_SPACING;
    _creditsButton = CreateButton(localization->Get("CREDITS"), BUTTON_WIDTH, IntVector2(-BUTTON_SPACING, marginBottom));
    _creditsButton->SetAlignment(HA_RIGHT, VA_BOTTOM);
    SubscribeToEvent(_creditsButton, E_RELEASED, [&](StringHash eventType, VariantMap& eventData) {
        VariantMap& data = GetEventDataMap();
        data["Name"] = "Credits";
        SendEvent(MyEvents::E_SET_LEVEL, data);
    });

    marginBottom += BUTTON_HEIGHT + BUTTON_SPACING;
    _exitButton = CreateButton(localization->Get("EXIT"), BUTTON_WIDTH, IntVector2(-BUTTON_SPACING, marginBottom));
    _exitButton->SetAlignment(HA_RIGHT, VA_BOTTOM);
    SubscribeToEvent(_exitButton, E_RELEASED, [&](StringHash eventType, VariantMap& eventData) {
        VariantMap& data = GetEventDataMap();
        data["Name"] = "QuitConfirmationWindow";
        SendEvent(MyEvents::E_OPEN_WINDOW, data);
    });
}

Button* MainMenu::CreateButton(const String& text, int width, IntVector2 position)
{
    auto* cache = GetSubsystem<ResourceCache>();
    auto* font = cache->GetResource<Font>(APPLICATION_FONT);

    auto* button = GetSubsystem<UI>()->GetRoot()->CreateChild<Button>();
    button->SetStyleAuto();
    button->SetFixedWidth(width);
    button->SetFixedHeight(BUTTON_HEIGHT);
    button->SetPosition(position);

    auto* buttonText = button->CreateChild<Text>();
    buttonText->SetFont(font, BUTTON_FONT_SIZE);
    buttonText->SetAlignment(HA_CENTER, VA_CENTER);
    buttonText->SetText(text);

    return button;
}
#include <iostream>
using namespace std;

#include <unistd.h>

#include <QDir>
#include <QApplication>

#include "gameui.h"
#include "gamehandler.h"
#include "rominfo.h"
#include "gamesettings.h"
#include "dbcheck.h"

#include <mythtv/mythcontext.h>
#include <mythtv/mythdbcon.h>
#include <mythtv/mythversion.h>
#include <mythtv/lcddevice.h>
#include <mythtv/libmythui/myththemedmenu.h>
#include <mythtv/mythpluginapi.h>
#include <mythtv/libmythui/mythuihelper.h>

#define LOC_ERR QString("MythGame:MAIN Error: ")
#define LOC QString("MythGame:MAIN: ")

struct GameData
{
};

void GameCallback(void *data, QString &selection)
{
    GameData *ddata = (GameData *)data;
    QString sel = selection.lower();

    (void)ddata;

    if (sel == "game_settings")
    {
        MythGameGeneralSettings settings;
        settings.exec();
    }

    if (sel == "game_players")
    {
        MythGamePlayerEditor mgpe;
        mgpe.exec();
    }
    else if (sel == "search_for_games")
    {
        GameHandler::processAllGames();
    }
    if (sel == "clear_game_data")
    {
        GameHandler::clearAllGameData();
    }

}

int runMenu(QString which_menu)
{
    QString themedir = GetMythUI()->GetThemeDir();

    MythThemedMenu *menu = new MythThemedMenu(
        themedir, which_menu, GetMythMainWindow()->GetMainStack(), "game menu");

    GameData data;

    menu->setCallback(GameCallback, &data);
    menu->setKillable();

    if (menu->foundTheme())
    {
        if (LCD * lcd = LCD::Get())
            lcd->switchToTime();

        GetMythMainWindow()->GetMainStack()->AddScreen(menu);
        return 0;
    }
    else
    {
        VERBOSE(VB_IMPORTANT, QString("Couldn't find menu %1 or theme %2")
                              .arg(which_menu).arg(themedir));
        delete menu;
        return -1;
    }
}

void runGames(void);
int  RunGames(void);

void setupKeys(void)
{
    REG_JUMP("MythGame", "Game frontend", "", runGames);

    REG_KEY("Game", "TOGGLEFAV",     "Toggle the current game as a favorite",
            "?,/");
    REG_KEY("Game", "INCSEARCH",     "Show incremental search dialog",
            "Ctrl+S");
    REG_KEY("Game", "INCSEARCHNEXT", "Incremental search find next match",
            "Ctrl+N");

}

int mythplugin_init(const char *libversion)
{
    if (!gContext->TestPopupVersion("mythgame", libversion,
                                    MYTH_BINARY_VERSION))
    {
        VERBOSE(VB_IMPORTANT,
                QString("libmythgame.so/main.o: binary version mismatch"));
        return -1;
    }

    gContext->ActivateSettingsCache(false);
    if (!UpgradeGameDatabaseSchema())
    {
        VERBOSE(VB_IMPORTANT,
                "Couldn't upgrade database to new schema, exiting.");
        return -1;
    }
    gContext->ActivateSettingsCache(true);

    MythGamePlayerSettings settings;
//    settings.Load();
//    settings.Save();

    setupKeys();

    return 0;
}

void runGames()
{
    RunGames();
}

int RunGames(void)
{
    MythScreenStack *mainStack = GetMythMainWindow()->GetMainStack();
    GameUI *game = new GameUI(mainStack);

    if (game->Create())
    {
        mainStack->AddScreen(game);
        return 0;
    }
    else
    {
        delete game;
        return -1;
    } 
}

int mythplugin_run(void)
{
    return RunGames();
}

int mythplugin_config(void)
{
    return runMenu("game_settings.xml");
}


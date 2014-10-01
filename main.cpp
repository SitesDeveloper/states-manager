#include <irrlicht.h>

using namespace irr;

//подключаем менеджер состояний
#include "StateManager/CStateManager.h"
CStateManager* sm;

// подключаем состояния
#include "st_loader.h"
#include "st_mainmenu.h"
#include "st_game.h"
#include "st_editor.h"
#include "st_options.h"

int main()
{
        irr::IrrlichtDevice *device = irr::createDevice( irr::video::EDT_OPENGL, irr::core::dimension2d<irr::u32>(640, 480), 16, false, false, false, 0);

        if (!device) return 1;

        device->setWindowCaption(L"State Manager");

        irr::video::IVideoDriver* driver = device->getVideoDriver();
        irr::scene::ISceneManager* smgr = device->getSceneManager();
        irr::gui::IGUIEnvironment* guienv = device->getGUIEnvironment();
        //irr::io::IFileSystem* filesys = device->getFileSystem();


        // создаем менеджер состояний и регистрируем в нем состояния
        sm = new CStateManager(device);
        sm->registerState( game::STATE_LOADER, new CLoader(device) );
        sm->registerState( game::STATE_MAINMENU, new CMainMenu(device) );
        sm->registerState( game::STATE_GAME, new CGame(device) );
        sm->registerState( game::STATE_EDITOR, new CEditor(device) );
        sm->registerState( game::STATE_OPTIONS, new COptions(device) );
        sm->setNextState( game::STATE_MAINMENU ); // следующее за загрузчиком будет главное меню
        sm->switchState( game::STATE_LOADER ); // переключаемся на загрузчик

        device->setEventReceiver(sm);

        while(device->run())
        {
                driver->beginScene(true, true, irr::video::SColor(255,100,101,140));
                smgr->drawAll();
                guienv->drawAll();
                driver->endScene();

                if (!sm->update()) break;

        }

        delete sm;
        device->drop();

        return 0;
}

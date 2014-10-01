#ifndef ST_LOADER_H_INCLUDED
#define ST_LOADER_H_INCLUDED

#include "StateManager/sm_conf.h"
#include "StateManager/CState.h"

class CLoader : public CState
{
    public:
        CLoader(irr::IrrlichtDevice* device) : CState(device)
        {
            irr::gui::IGUIEnvironment* guienv = device->getGUIEnvironment();

            //скролбар будет вместо прогресс бара
            bar = guienv->addScrollBar( true, irr::core::rect<irr::s32>(10, 10, 630, 30));
            bar->setMin(0);
            bar->setMax(100);

            label = guienv->addStaticText(L"Atention! Loading Resources!", irr::core::rect<irr::s32>(10, 40, 200, 55));

            timeshift = 0;

            // по умолчанию самодеактивируемся
            deactivate();
        }

        ~CLoader()
        {
            //dtor
        }

        // обработчик событий
        virtual bool OnEvent(const irr::SEvent& event)
        {
            // ну какие в загрузчики события???
            return false;
        }//OnEvent

        virtual void activate()
        {
            bar->setVisible(true);
            label->setVisible(true);
        }

        virtual void deactivate()
        {
            bar->setVisible(false);
            label->setVisible(false);
        }

        virtual void update(irr::f32 timediff)
        {
            if (bar->getPos() == 100)
            {
                // генерим событие для передачи основному обработчику (менеджеру состояний)
                irr::SEvent se;
                se.EventType = irr::EET_USER_EVENT;
                se.UserEvent.UserData1 = game::EVENT_SWITCH_NEXTSTATE; // событие которое указано следующим
                Device->getEventReceiver()->OnEvent(se);
                return;
            }

            timeshift += timediff;
            if (timeshift > 0.1f )
            {
                /**
                    вот в этом замечательном месте можно очень даже замечательно
                    вызвать загрузку следующего по списку игрового ресурса
                */
                bar->setPos( bar->getPos() + 3 );
                timeshift = 0;
            }
        }

    private:
        irr::gui::IGUIScrollBar* bar;
        irr::gui::IGUIStaticText* label;

        irr::f32 timeshift;
};

#endif // ST_LOADER_H_INCLUDED

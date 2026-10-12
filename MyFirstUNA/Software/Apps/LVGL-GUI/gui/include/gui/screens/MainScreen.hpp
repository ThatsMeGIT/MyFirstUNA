
/**
 * @file MainScreen.hpp
 * @brief MyFirstUNA - Interaktiver Zaehler
 */

#ifndef MAIN_SCREEN_HPP
#define MAIN_SCREEN_HPP

#include <cstdint>
#include <memory>

#include "lvgl.h"

#include "SDK/GUI/LVGL/Buttons.hpp"

#include "gui/model/Model.hpp"
#include "gui/model/ModelListener.hpp"

class MainScreen : public ModelListener
{
public:
    explicit MainScreen(Model& model);
    ~MainScreen();

    MainScreen(const MainScreen&) = delete;
    MainScreen& operator=(const MainScreen&) = delete;

    // LVGL-Bildschirm zurueckgeben
    lv_obj_t* root() const
    {
        return mRoot;
    }

private:
    // Tasteneingaben verarbeiten
    void onKey(uint8_t code);

    // Callback fuer LVGL-Tastenereignisse
    static void keyEventCb(lv_event_t* e);

    // Verbindung zur Anwendungslogik
    Model& mModel;

    // Hauptbildschirm
    lv_obj_t* mRoot = nullptr;

    // UNA-Tastenindikatoren
    std::unique_ptr<SDK::LVGL::Buttons> mButtons;

    // Zählerstand
    int mCounter = 0;

    // LVGL-Label fuer den Zaehler
    lv_obj_t* mCounterLabel = nullptr;
};

#endif // MAIN_SCREEN_HPP

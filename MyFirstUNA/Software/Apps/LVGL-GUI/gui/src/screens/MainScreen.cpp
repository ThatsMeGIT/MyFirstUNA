
#include "gui/screens/MainScreen.hpp"

#include "SDK/GUI/Button.hpp"
#include "SDK/GUI/Color.hpp"
#include "SDK/GUI/LVGL/Draw.hpp"

#include "gui/Assets.hpp"

namespace Draw = SDK::LVGL::Draw;

MainScreen::MainScreen(Model& model)
    : mModel(model)
{
    // Bildschirm erstellen
    mRoot = lv_obj_create(nullptr);
    Draw::applyScreen(mRoot);

    // Tasteneingaben registrieren
    lv_obj_add_event_cb(
        mRoot,
        &MainScreen::keyEventCb,
        LV_EVENT_KEY,
        this
    );

    // Überschrift
    Draw::label(
        mRoot,
        &poppins_regular_18,
        "MyFirstUNA",
        19, 50, 203,
        LV_TEXT_ALIGN_CENTER,
        SDK::GUI::Color::WHITE
    );

    // Zähleranzeige
    mCounterLabel = lv_label_create(mRoot);

    lv_label_set_text(mCounterLabel, "0");
    lv_obj_set_width(mCounterLabel, 203);
    lv_obj_set_pos(mCounterLabel, 19, 105);

    lv_obj_set_style_text_align(
        mCounterLabel,
        LV_TEXT_ALIGN_CENTER,
        0
    );

    lv_obj_set_style_text_color(
        mCounterLabel,
        lv_color_white(),
        0
    );

    lv_obj_set_style_text_font(
        mCounterLabel,
        &poppins_regular_18,
        0
    );

    // Bedienungshinweis
    Draw::label(
        mRoot,
        &poppins_regular_18,
        "L1: +1",
        19, 165, 203,
        LV_TEXT_ALIGN_CENTER,
        SDK::GUI::Color::WHITE
    );

    // Tastenindikatoren
    mButtons = std::make_unique<SDK::LVGL::Buttons>(mRoot);

    mButtons->set(
        SDK::LVGL::Buttons::NONE,
        SDK::LVGL::Buttons::NONE,
        SDK::LVGL::Buttons::WHITE,
        SDK::LVGL::Buttons::WHITE
    );

    // Model verbinden
    bind(&mModel);
    mModel.bind(this);
}

MainScreen::~MainScreen()
{
    mModel.bind(nullptr);
    lv_obj_delete(mRoot);
}

void MainScreen::keyEventCb(lv_event_t* e)
{
    auto* self = static_cast<MainScreen*>(
        lv_event_get_user_data(e)
    );

    self->onKey(
        static_cast<uint8_t>(lv_event_get_key(e))
    );
}

void MainScreen::onKey(uint8_t code)
{
    namespace Btn = SDK::GUI::Button;

    switch (code) {

        case Btn::L1:
            // Zähler erhöhen
            mCounter = mCounter + 1;

            // Zähleranzeige aktualisieren
            lv_label_set_text_fmt(
                mCounterLabel,
                "%d",
                mCounter
            );
            break;
        case Btn::L2:
            break;
        case Btn::R1:
            break;
        case Btn::R2:
            // App verlassen
            mModel.exitApp();
            break;

        default:
            break;
    }
}

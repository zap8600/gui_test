#include <furi.h>
#include <furi_hal.h>
#include <gui/gui.h>
#include <gui/view.h>
#include <gui/view_dispatcher.h>
#include <gui/modules/text_box.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct {
    Gui* gui;
    ViewDispatcher* view_dispatcher;
    TextBox* text_box;
} mpApp;

typedef enum {
    mpViewTextBox,
} mpView;

int32_t gt_app() {
    mpApp* app = malloc(sizeof(mpApp));
    app->view_dispatcher = view_dispatcher_alloc();
    app->text_box = text_box_alloc();
    text_box_set_font(app->text_box, TextBoxFontText);
    app->gui = furi_record_open(RECORD_GUI);
    view_dispatcher_add_view(app->view_dispatcher, mpViewTextBox, text_box_get_view(app->text_box));
    view_dispatcher_attach_to_gui(app->view_dispatcher, app->gui, ViewDispatcherTypeFullscreen);
    view_dispatcher_switch_to_view(app->view_dispatcher, mpViewTextBox);
    furi_delay_ms(5000);
    view_dispatcher_remove_view(app->view_dispatcher, mpViewTextBox);
    text_box_free(app->text_box);
    view_dispatcher_free(app->view_dispatcher);
    furi_record_close(RECORD_GUI);
    app->gui = NULL;
    free(app);
    return 0;
}

#include <furi.h>
#include <furi_hal.h>
#include <gui/gui.h>
#include <gui/view.h>
#include <gui/view_dispatcher.h>
#include <gui/modules/text_box.h>
#include <stdint.h>
#include <stdlib.h>

typedef enum {
    mpViewTextBox,
} mpView;

int32_t gt_app() {
    ViewDispatcher* view_dispatcher = view_dispatcher_alloc();
    TextBox* text_box = text_box_alloc();
    text_box_set_font(text_box, TextBoxFontText);
    Gui* gui = furi_record_open(RECORD_GUI);
    view_dispatcher_add_view(view_dispatcher, mpViewTextBox, text_box_get_view(text_box));
    view_dispatcher_attach_to_gui(view_dispatcher, gui, ViewDispatcherTypeFullscreen);
    view_dispatcher_switch_to_view(view_dispatcher, mpViewTextBox);
    furi_delay_ms(5000);
    view_dispatcher_remove_view(view_dispatcher, mpViewTextBox);
    text_box_free(text_box);
    view_dispatcher_free(view_dispatcher);
    furi_record_close(RECORD_GUI);
    return 0;
}

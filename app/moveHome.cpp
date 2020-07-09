#include "moveHome.hpp"

Home::Home()
{
}

void Home::execute(EditorModel& model)
{
    int old_col = model.moveHome();
    rem_cursor = old_col;
}

void Home::undo(EditorModel& model)
{
    model.setCursor(rem_cursor);
}

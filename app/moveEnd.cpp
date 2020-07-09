#include "moveEnd.hpp"

End::End()
{
}

void End::execute(EditorModel& model)
{
    int old_col = model.moveEnd();
    rem_cursor = old_col;
}

void End::undo(EditorModel& model)
{
    model.setCursor(rem_cursor);
}

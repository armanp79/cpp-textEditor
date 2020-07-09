#include "cursorRight.hpp"
Right::Right()
{
}

void Right::execute(EditorModel& model)
{
    model.moveRight();
}

void Right::undo(EditorModel& model)
{
    model.moveLeft();
}

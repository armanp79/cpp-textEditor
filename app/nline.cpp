#include "nline.hpp"

Nline::Nline()
{
}

void Nline::execute(EditorModel& model)
{
    model.newLine();
}

void Nline::undo(EditorModel& model)
{
    model.joinLines();
}

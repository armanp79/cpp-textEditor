#include "moveDown.hpp"
#include <utility>

Down::Down()
{
}

void Down::execute(EditorModel& model)
{
    std::pair<int,int> cl =model.moveDown();
    rem_cursor = cl.first;
    rem_line = cl.second;
}

void Down::undo(EditorModel& model)
{
    model.setCursor(rem_cursor);
    model.setLine(rem_line);
}

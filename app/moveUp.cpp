#include "moveUp.hpp"
#include <utility>

Up::Up()
{
}

void Up::execute(EditorModel& model)
{
    std::pair<int,int> cl = model.moveUp();
    rem_cursor = cl.first;
    rem_line = cl.second;
}

void Up::undo(EditorModel& model)
{
    model.setCursor(rem_cursor);
    model.setLine(rem_line);
}

#include "dline.hpp"
#include <string>

Dline::Dline()
{
}

void Dline::execute(EditorModel& model)
{
    std::vector<std::string> info = model.delLine();
    words = info[0];
    column = std::stoi(info[1]);
    line = std::stoi(info[2]);
    //delete info;
}

void Dline::undo(EditorModel& model)
{
    model.insertLine(line, words);
    model.setCursor(column);
    model.setLine(line);
}

#include "back.hpp"

Back::Back()
{
}

void Back::execute(EditorModel& model)
{   
    deleted = model.backspace();
}       
        
void Back::undo(EditorModel& model)
{
    if (deleted == 0)
    {
        model.newLine();
    }
    else
    {
        model.addText(deleted);
    }
}

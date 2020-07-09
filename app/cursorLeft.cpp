#include "cursorLeft.hpp"

Left::Left()
{
}

void Left::execute(EditorModel& model)
{   
    model.moveLeft();
}       
        
void Left::undo(EditorModel& model)
{
    model.moveRight();
}

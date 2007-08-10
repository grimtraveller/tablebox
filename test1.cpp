#include <fltk/run.h>
#include <fltk/Button.h>
#include <fltk/Input.h>
#include <fltk/DoubleBufferWindow.h>
#include "TableBox.h"

using namespace fltk;

int main (int argc, char ** argv) {
	DoubleBufferWindow * win = new DoubleBufferWindow (420, 420, "Test 1");
	win->set_double_buffer ();
	win->begin ();
	
	TableBox * table1 = new TableBox (10, 10, win->w () - 20, win->h () - 20);
	table1->Size (6, 3);
	table1->box (fltk::BORDER_BOX);
	table1->begin ();
	
	// row 0
	table1->Attach ((Widget *) new Button (0, 0, 0, 0, "Button 1"), 0, 0, 100, 25, FILL, FILL, 1, 1, 0.0f, 0.5f);
	table1->Attach ((Widget *) new Input (0, 0, 0, 0), 1, 0, 200, 25, EXPAND, EXPAND, 1, 1, 0.5f, 0.5f);
	table1->Attach ((Widget *) new Button (0, 0, 0, 0, "Button 2"), 2, 0, 100, 25, FILL, FILL, 1, 1, 0.5f, 0.5f);
	
	// row 1
	table1->Attach ((Widget *) new Input (0, 0, 0, 0), 0, 1, 100, 25, EXPAND | FILL, EXPAND | FILL, 1, 2);
	table1->Attach ((Widget *) new Input (0, 0, 0, 0), 1, 1, 100, 25, EXPAND, EXPAND, 1, 2, 0.5f, 0.5f);
	table1->Attach ((Widget *) new Input (0, 0, 0, 0), 2, 1, 100, 25, EXPAND, EXPAND, 1, 2, 0.5f, 1.0f);
	
	// row 2
	table1->Attach ((Widget *) new Input (0, 0, 0, 0), 0, 3, 100, 25, FILL, FILL, 2, 1);	
	table1->Attach ((Widget *) new Input (0, 0, 0, 0), 2, 3, 100, 25, FILL, FILL, 1, 2);	
	
	// row 3
	table1->Attach ((Widget *) new Button (0, 0, 0, 0, "Button 6"), 0, 4, 100, 25, FILL, FILL, 2, 1);
	
	// row 4
	table1->Attach ((Widget *) new Button (0, 0, 0, 0, "Button 7"), 1, 5, 100, 25, FILL, FILL, 1, 1);
	
	table1->end ();
	
	win->end ();
	win->resizable (table1);
	win->show (argc, argv);
	return run ();
}

#include "w.h"

// запуск окна
IMPLEMENT_APP(Begin)

bool Begin::OnInit()
{
  MyWin *wind=new MyWin(wxT("Easy Debut - developed by A. ILenko, M. Kuimov, V. Ugnivenko, N. Kubrakov. Copyright 2018. All rights reserved."));
  wind->Show(true);
  
  return true;
};

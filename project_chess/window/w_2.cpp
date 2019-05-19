#include "w.h"
//#include <iostream>

// Конструктор фрейма
MyWin::MyWin(const wxString& title):wxFrame(NULL,wxID_ANY,title,wxDefaultPosition,wxSize(1000,1000)){
  // создали полоску для менюшки
    menubar = new wxMenuBar;
// создали менюшку
    file = new wxMenu;
    //добавили обработчик изображений
	//jpegLoader = new wxJPEGHandler();
// закинули менюшку на полоску
// пока не работает (для "красоты")
   
    file->Append(wxID_ANY, wxT("&New"));
    
    file->AppendSeparator();
// Для всех пунктор меню указывем идентификатор чтобы
// связать обработчик событие с конкретным элементом
// добавили к менюшке раздел quit
    quit = new wxMenuItem(file, wxID_EXIT, wxT("&Quit"));
// добавили раздел load
    load = new wxMenuItem(file, ID_MENU_LOAD, wxT("&Load"));
    file->Append(load);
    file->Append(quit);
// Это еще один пункт меню
// пока тоже не работает
     //im = new wxMenu;
     //im->Append(wxID_ANY, wxT("Edit figure"));
     //im->Append(wxID_ANY, wxT("Rotate 90"));
// добавили оба пункта меню на полску меню    
     menubar->Append(file, wxT("&File"));
    // menubar->Append(im, wxT("&Edit"));

 // установили полоску в окно
    SetMenuBar(menubar);
// подключили менюшку exit
  Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyWin::OnQuit));
// подключили load (идентификаторы такие же как и при создании каждого элемента)
   Connect(ID_MENU_LOAD, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyWin::OnLoad));

// создание панельки для текста, кнопок и рисовалки
    m_pan= new wxPanel(this,wxID_ANY);
// это тоже панель, но наша.
// помещаем ее нна панель m_pan и задаем указатель на главный фрейм
    dp=new Draw(m_pan,this);
// это окошко для текста. Тоже помещаем на m_pan
    //tc =  new wxTextCtrl(m_pan, -1, wxT(""), wxPoint(200, 10),wxSize(200,50)); 
// статус-бар будет внизу окна
    sb=CreateStatusBar();
    sb->SetStatusText(wxString(wxT("что-то напишем и здесь")));

	Connect(wxEVT_TIMER, wxCommandEventHandler(MyWin::OnTimer));
	Connect(wxEVT_LEFT_DOWN,wxMouseEventHandler(MyWin::OnMouse));
	Centre();
	tm = new wxTimer(this, 1);
    Maximize(true); 
};



void MyWin::OnLoad(wxCommandEvent& event){
// специальный класс для листания файлов 
  wxFileDialog * openFileDialog = new wxFileDialog(this);
// если все открывается, выберем имя файла
// Только имя!!!
  if (openFileDialog->ShowModal() == wxID_OK){
// Что выбрали, то и будет именем файла
// Запоминаем в строку
      wxString fileName = openFileDialog->GetPath();
// Загружаем содержимое в окно текста
      //tc->LoadFile(fileName);
// Теперь нужно получить данные из файла
// Создаем объект - файловый поток
      wxFileInputStream input(fileName);
// Чтобы он работал как текстовый файл, превращаем его в поток-текст
      wxTextInputStream intext(input);
    //int  x1,y1,x2,y2; 
// "обычным" образом считываем данные
	i = 0;
	while (1){
	 
     intext>>x1[i];
     if (x1[i] == -1) break;
     intext>>y1[i]>>x2[i]>>y2[i]; 
	  intext>>cr[i]>>cg[i]>>cb[i];
	  
		i++;
	}
// Это нужно для перерисовки окна, когда будем рисовать фигуру
      dp->Refresh();
  }

};

void MyWin::OnQuit(wxCommandEvent& event){
  Close(true);
};

// Конструктор нашего Draw
Draw::Draw(wxPanel *parent, MyWin *fr):wxPanel(parent, -1,wxPoint(600,100),wxSize(500,500),wxBORDER_SUNKEN){
// подключили панель к событиям рисования
    Connect(wxEVT_PAINT,wxPaintEventHandler(Draw::OnPaint));
    handler = new wxJPEGHandler;
    handler2 = new wxPNGHandler;
	wxImage::AddHandler(handler);
	wxImage::AddHandler(handler2);
	image1 = new wxStaticBitmap( this, wxID_ANY, wxBitmap("1.jpg", wxBITMAP_TYPE_JPEG), wxPoint(-80,-80), wxSize(650, 650));
	image2 = new wxStaticBitmap( this, wxID_ANY, wxBitmap("2.png", wxBITMAP_TYPE_PNG), wxPoint(200,420), wxSize(40, 40));
	
    mn = fr;
};

// Свободная функция рисования прямоугольника
// Для рисования есть абстрактный класс wxDC
// У него много разных наследников
// Самый простой wxPaintDC
// Но мы сделаем функцию для всех наследников wxDC
void DrRec(wxPoint p1, wxPoint p2, wxDC * dc){
    dc->DrawRectangle(p1, wxSize (abs(p1.x-p2.x),abs(p1.y-p2.y)));
};

// Функция OnPaint() сработает при любом рисовании окна:
// первое рисование, сложил-разложили
// или вызов функции Refresh()

void Draw::OnPaint(wxPaintEvent& event){
// положили планшет wxPaintDC на нашу панель
   //wxPaintDC dc(this);
	//mn->image = new wxStaticBitmap( this, wxID_ANY, wxBitmap("1.jpg", wxBITMAP_TYPE_JPEG), wxPoint(50,100), wxSize(500, 500)); 
// Установили цвет заливки
/*for(int k = 0; k < mn->i; k++){
   dc.SetBrush(wxBrush(wxColour(mn->cr[k],mn->cg[k],mn->cb[k])));
      mn->a.x = mn->x1[k];
      mn->a.y = mn->y1[k];
      mn->b.x = mn->x2[k];
      mn->b.y = mn->y2[k];
// передали свободной функции координаты и указатель на планшет
   DrRec(mn->a,mn->b,&dc);
 }*/
//image2 = new wxStaticBitmap( this, wxID_ANY, wxBitmap("2.png", wxBITMAP_TYPE_PNG), wxPoint(200 + mn->p.x,420), wxSize(40, 40));
      //Refresh();
      //Update();
      wxString str;
      str<<wxT("x=")<<mn->p.x<<wxT("y=")<<mn->p.y;
      mn->sb->SetStatusText(str);
};
 void MyWin::OnMouse(wxMouseEvent &event){
    // получение координат мыши
    mx=event.GetX();
    my=event.GetY();
    p.x=mx;
    p.y=my;
};

void MyWin::OnTimer(wxCommandEvent& event){
  // остановка таймера (при перерисовке запустится снова)   
    tm->Stop();
   // директивная перерисовка 
      Refresh();
      Update();
};

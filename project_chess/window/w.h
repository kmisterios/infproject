#include <wx/wx.h>
#include <wx/file.h>
#include <wx/wfstream.h>
#include <wx/txtstrm.h>
#include <wx/sstream.h>
#include <wx/string.h>
#include <wx/sizer.h>
#include "pole.h"
#include <fstream>
 
class Begin: public wxApp{
    public:
        virtual bool OnInit();
};

wxDEFINE_EVENT(Record, wxCommandEvent);
// Нужен еще класс Draw
class Draw;
class MyWin;

class MyWin:public wxFrame{
    wxMenuBar *menubar; // полоска для меню
    wxMenu *file,*im; // менюшка  на полоске
    wxMenuItem *load,*quit, *record; // открывалка  файла
    
// Указатель на объект Draw  
    Draw *dp;
// панель 
// если элемнты помещать сразу на фрейм, то первый же объект
// займет весь фрейм
// для различных элементов есть wxPanel 
    wxPanel *m_pan;
// строка (для всех типов кодировки)
    wxString ss;
 public:
//  конструктор
	
	Pole *etalon, *play;
	// Это в "подвале" окошка
    wxStatusBar *sb; // статус бар
    MyWin(const wxString& title);
// две координаты для рисования     

	int khod, khod1,per, per1;
    // Функция закрытия окна
    void OnQuit(wxCommandEvent& event);
// Загрузка файла с данными
    void OnLoad(wxCommandEvent& event);
                                       
    void OnSaveAs(wxCommandEvent& event);
    
    
    void OnPaint(wxPaintEvent& event);
    
    void PaintBackground(wxDC& dc);   // рисование фона
	void OnEraseBackground(wxEraseEvent& event);  // очистка фона
    int CheckDebut(string );
	wxString fileName;
	
}; 


// класс для рисования
// наследник wxPanel
class Draw: public wxPanel{
// указатель на верхнее окно
// это нужно для доступа к элементам (к a и b)
		MyWin *mn; 
		public:
		int end,h;
		void OnMouse(wxMouseEvent& event);  // вызывается при обработке сигнала от мыши
		void OnTimer(wxCommandEvent& event); // изменение параметров при истечении 
		wxBitmap *image1;
		wxBitmap *image2;
		wxPoint p1;
		wxPoint p2;
	    int ch,ch1;
	   int mx,my;
	   wxButton *button, *ht;
	    wxButton *hn;
// в конструкторе указывается адрес объекта, который ее содержит
        Draw(wxPanel *parent, MyWin *main);
 // рисовалка
        void OnPaint(wxPaintEvent & event);
		int ScreenPrint(Pole);
		Hod Coords_To_Hod(int ,int , int , int );
		int PlayDebut(Pole *	etalon, Hod hod);
		int RecordMove(Pole * pole, Hod hod);
		void OnEnder(wxCommandEvent & event);
		void OnHn(wxCommandEvent& event);
		wxTextCtrl *m_readonly;
		wxTextCtrl *m_readonly1;
		void OnHt(wxCommandEvent& event);
		
};

    

//иднтификаторы 
// загрузка
const int ID_MENU_LOAD =1002;
// редактирование
const int ID_MENU_EDIT =1003;

const int ID_MENU_RECORD =1004;

const int ID_BUTTON =1005;

const int ID_BUTTONN =1006;
const int ID_BUTTONNN =1007;

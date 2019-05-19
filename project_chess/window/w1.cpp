#include "w.h"


MyWin::MyWin(const wxString& title):wxFrame(NULL,wxID_ANY,title,wxDefaultPosition,wxSize(1000,700)){

    menubar = new wxMenuBar;

    file = new wxMenu;


    quit = new wxMenuItem(file, wxID_EXIT, wxT("&Quit"));

    load = new wxMenuItem(file, ID_MENU_LOAD, wxT("&Load"));

	record = new wxMenuItem(file, ID_MENU_RECORD, wxT("&Record"));
    file->Append(load);
    file->Append(record);
    file->Append(quit);
 
     menubar->Append(file, wxT("&File"));

    SetMenuBar(menubar);
// подключили менюшку exit
  Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyWin::OnQuit));
// подключили load (идентификаторы такие же как и при создании каждого элемента)
   Connect(ID_MENU_LOAD, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyWin::OnLoad));
   Connect(ID_MENU_RECORD, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyWin::OnSaveAs));
// создание панельки для текста, кнопок и рисовалки
    m_pan= new wxPanel(this,wxID_ANY);
// это тоже панель, но наша.
// помещаем ее нна панель m_pan и задаем указатель на главный фрейм
    dp=new Draw(m_pan,this);
    sb=CreateStatusBar();

	per = 0;
	per1 = 0;

};


void MyWin::OnSaveAs(wxCommandEvent& WXUNUSED(event))
{
    wxFileDialog 
        saveFileDialog(this, _("Save txt file"), "", "",
                       "txt files (*.txt)|*.txt", wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
    if (saveFileDialog.ShowModal() == wxID_CANCEL)
        return;     // the user changed idea...

    fileName = saveFileDialog.GetPath();
    wxFileOutputStream output(saveFileDialog.GetPath());
    if (!output.IsOk())
    {
        wxLogError("Cannot save current contents in file '%s'.", saveFileDialog.GetPath());
        return;
    }
    wxTextOutputStream out(output);
    out<<fileName;
    play = new Pole;
    per = 1;
    per1 = 0;
    khod1=1;
    khod = 0;
    
    wxString str,str1;
	str<<wxT(" Ходы :")<<wxT("\n");
	dp->m_readonly = new wxTextCtrl( this, wxID_ANY, str,
	wxPoint(600, 0), wxSize(150,490), wxTE_MULTILINE | wxTE_READONLY );
	str1<<wxT(" Подсказки :")<<wxT("\n");
	dp->m_readonly1 = new wxTextCtrl( this, wxID_ANY, str1,
	wxPoint(770, 0), wxSize(150,490), wxTE_MULTILINE | wxTE_READONLY );
    dp->Refresh();
    dp->Update();
    dp->ScreenPrint(*(play));

    
}



void MyWin::OnLoad(wxCommandEvent& event){
  wxFileDialog * openFileDialog = new wxFileDialog(this);

  if (openFileDialog->ShowModal() == wxID_OK){
      fileName = openFileDialog->GetPath();
      wxFileInputStream input(fileName);
      wxTextInputStream intext(input);

	 int x1,x2,y1,y2;
	char a,b;
	int check = 1;
	etalon = new Pole;
	while (1)
	{
		intext>>a>>y1>>b>>y2;
		if (y1==228)
			break;
		x1=a-96;
		x2=b-96;
		etalon->next = new Pole;
		*(etalon->next) = *(etalon);
		etalon->next->next = 0;
		etalon->next->prev = etalon;
		etalon->hod.a = a;
		etalon->hod.b = b;
		etalon->hod.y1 = y1;
		etalon->hod.y2 = y2;
		etalon = etalon->next;
		check=etalon->maketurn(x1-1,y1-1,x2-1,y2-1);
		if (check == 0) break;
	}
	while (etalon->prev!=0)
	etalon=etalon->prev;
	wxString se;
	if (check == 0){
	se<<wxT("Записанный дебют испорчен!");
    sb->SetStatusText(se);
	}
	else
	{
	se<<wxT("Дебют успешно загружен");
    sb->SetStatusText(se);
	}
    per1 = 1;
    per = 0;
    khod1 = 0;

     dp->ScreenPrint(*etalon);
    khod = check;
    
}
};

void MyWin::OnQuit(wxCommandEvent& event){
  Close(true);
};

Draw::Draw(wxPanel *parent, MyWin *fr):wxPanel(parent, -1,wxPoint(0,0),wxSize(1000,700),wxBORDER_SUNKEN){

    Connect(wxEVT_PAINT,wxPaintEventHandler(Draw::OnPaint));

	Connect(wxEVT_LEFT_DOWN,wxMouseEventHandler(Draw::OnMouse));
	p1.x = 0;
	p1.y = 0;
	p2.x = 0;
	p2.y = 0;
	ch = 0;
	ch1 = 0;
    mn = fr;
    h = 0;
    wxString str,str1;
	str<<wxT(" Ходы :")<<wxT("\n");
	m_readonly = new wxTextCtrl( this, wxID_ANY, str,
	wxPoint(600, 0), wxSize(150,490), wxTE_MULTILINE | wxTE_READONLY | wxTE_NO_VSCROLL );
	str1<<wxT(" Подсказки :")<<wxT("\n");
	m_readonly1 = new wxTextCtrl( this, wxID_ANY, str1,
	wxPoint(770, 0), wxSize(150,490), wxTE_MULTILINE | wxTE_READONLY | wxTE_NO_VSCROLL );
	
	wxTextCtrl* m_text = new wxTextCtrl( this, wxID_ANY, wxT("Учи дебют - становись гроссмейстером!"),wxPoint(100,550), wxSize(300,50),wxTE_READONLY |
	 wxALIGN_CENTRE_HORIZONTAL);
	m_text->SetForegroundColour(*wxBLACK);
	m_text->SetBackgroundColour(*wxLIGHT_GREY);
	m_text->SetSelection(0,0);
	m_text->SetDefaultStyle(wxTextAttr( *wxBLACK, *wxWHITE,
	wxFont( 70,
	wxFONTFAMILY_SWISS,
	wxFONTSTYLE_ITALIC,
	wxFONTWEIGHT_BOLD),
	wxTEXT_ALIGNMENT_CENTER));
	
};



void Draw::OnPaint(wxPaintEvent& event){

   wxPaintDC dc(this);
      Pole pole;
     wxPoint g;
	g.x = 0;
	g.y = 0;
	image1 = new wxBitmap("/home/mistrio/Desktop/project/window/1.jpg", wxBITMAP_TYPE_JPEG);
	dc.DrawBitmap(*(image1),g,false);


};

 void Draw::OnMouse(wxMouseEvent &event){
    wxString str,str1;
    wxPoint g;
    wxPaintDC dc(this);
    if (mn->khod == 1){
    if (ch % 2 == 0){
    mx=event.GetX();
    my=event.GetY();
    if ((mx<500)and(my<500))
    {
    p1.x=mx;
    p1.y=my;
    ch++;
    Hod hod2 = Coords_To_Hod(p1.x,p1.y, p1.x, p1.y);
	g.x = (hod2.a - 97)*55+27;
	g.y = (7-(hod2.y1 - 1))*55+26;
	
	image2 = new wxBitmap("/home/mistrio/Desktop/project/window/frame.png", wxBITMAP_TYPE_PNG);
	dc.DrawBitmap(*(image2),g,false);
}
	}
	else{
    mx=event.GetX();
    my=event.GetY();
    p2.x=mx;
    p2.y=my;
    ch++;
    mn->khod = 0;
    Hod hod = Coords_To_Hod(p1.x,p1.y, p2.x, p2.y);
    int jk = PlayDebut(mn->etalon, hod);
    if (jk==1) {
		 ScreenPrint(*(mn->etalon));
		str1<<wxT("Дебют закончен!")<<wxT("\n");
		 mn->sb->SetStatusText(str1);
		 mn->per1 == 0;
		 Pole * tmp;
		 while (mn->etalon->next!=0)
		 {
			 tmp=mn->etalon->next;
			 delete mn->etalon;
			 mn->etalon=tmp;
		 }
		 delete mn->etalon;
	}
    if (jk == 2){
		 mn->khod = 1;
		 ScreenPrint(*(mn->etalon));
		}
    if (jk == 3){
		 
		 mn->khod = 1;
		 str1<<hod.a<<wxT(" ")<<hod.y1<<wxT(" -> ")<<hod.b<<wxT(" ")<<hod.y2<<wxT("\n");
		 m_readonly->AppendText(str1);
		 h = 0;
		 ScreenPrint(*(mn->etalon));
	}
	}
	
	
}

 if ((mn->khod1 == 1)and(end == 0)){
    if (ch % 2 == 0){
    mx=event.GetX();
    my=event.GetY();
    if ((mx<500)and(my<500))
    {
    p1.x=mx;
    p1.y=my;
    ch++;
    Hod hod2 = Coords_To_Hod(p1.x,p1.y, p1.x, p1.y);
	g.x = (hod2.a - 97)*55+27;
	g.y = (7-(hod2.y1 - 1))*55+26;
	
	image2 = new wxBitmap("/home/mistrio/Desktop/project/window/frame.png", wxBITMAP_TYPE_PNG);
	dc.DrawBitmap(*(image2),g,false);
}
	}
	else{
    mx=event.GetX();
    my=event.GetY();
    p2.x=mx;
    p2.y=my;
    ch++;
    mn->khod1 = 0;
    Hod hod1 = Coords_To_Hod(p1.x,p1.y, p2.x, p2.y);
    str<<wxT("")<<hod1.a<<wxT(" ")<<hod1.y1; 
    mn->sb->SetStatusText(str); 
    int kj = RecordMove(mn->play, hod1);
    if (kj == 1){
	if (mn->play->check(*mn->play->next)==0)
	{
		mn->play->next=0;
		ScreenPrint(*(mn->play));
		mn->khod1 = 1;
	}
	else
	{
	mn->play = mn->play->next;
    ScreenPrint(*(mn->play));
    mn->khod1 = 1;
	}
	}
	else 
	{
		mn->khod1 = 1;
		ScreenPrint(*(mn->play));
		
	}
 }   
}   
    
};


int Draw::ScreenPrint( Pole pole ){	
	wxPaintDC dc(this);
	dc.Clear();
	wxPoint g;
	int i,j;
		g.x = 0;
		g.y = 0;
	image1 = new wxBitmap("/home/mistrio/Desktop/project/window/1.jpg", wxBITMAP_TYPE_JPEG);
	dc.DrawBitmap(*(image1),g,false);
	
	button = new wxButton(this , ID_BUTTON, wxT("Stop") , wxPoint (550 , 600)) ;
	Connect(ID_BUTTON, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Draw::OnEnder));
	
	hn = new wxButton(this , ID_BUTTONN, wxT("Return") , wxPoint (650 , 600)) ;
	Connect(ID_BUTTONN, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Draw::OnHn));

		ht = new wxButton(this , ID_BUTTONNN, wxT("Hint") , wxPoint (750 , 600)) ;
		Connect(ID_BUTTONNN, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Draw::OnHt));
		
	for(int i = 0;i < 8;i++){
		for (int j = 0; j< 8; j++){
			if ((pole.kl[i][j].figura == 4) and (pole.kl[i][j].color == 0) ){
			wxPoint f;
			f.x = 28 + 55*i;
			f.y = 25 + 55*(7-j) ;
			image2 = new wxBitmap("/home/mistrio/Desktop/project/window/bR.png", wxBITMAP_TYPE_PNG);
			dc.DrawBitmap(*(image2),f,false);
			}
			if ((pole.kl[i][j].figura == 4) and (pole.kl[i][j].color == 1) ){
			wxPoint f;
			f.x = 28 + 55*i;
			f.y = 25 + 55*(7-j) ;
			image2 = new wxBitmap("/home/mistrio/Desktop/project/window/wR.png", wxBITMAP_TYPE_PNG);
			dc.DrawBitmap(*(image2),f,false);
			}
			if ((pole.kl[i][j].figura == 1) and (pole.kl[i][j].color == 1) ){
			wxPoint f;
			f.x = 28 + 55*i;
			f.y = 25 + 55*(7-j) ;
			image2 = new wxBitmap("/home/mistrio/Desktop/project/window/wP.png", wxBITMAP_TYPE_PNG);
			dc.DrawBitmap(*(image2),f,false);
			}
			if ((pole.kl[i][j].figura == 1) and (pole.kl[i][j].color == 0) ){
			wxPoint f;
			f.x = 28 + 55*i;
			f.y = 25 + 55*(7-j) ;
			image2 = new wxBitmap("/home/mistrio/Desktop/project/window/bP.png", wxBITMAP_TYPE_PNG);
			dc.DrawBitmap(*(image2),f,false);
			}
			if ((pole.kl[i][j].figura == 2) and (pole.kl[i][j].color == 1) ){
			wxPoint f;
			f.x = 28 + 55*i;
			f.y = 25 + 55*(7-j) ;
			image2 = new wxBitmap("/home/mistrio/Desktop/project/window/wN.png", wxBITMAP_TYPE_PNG);
			dc.DrawBitmap(*(image2),f,false);
			}
			if ((pole.kl[i][j].figura == 2) and (pole.kl[i][j].color == 0) ){
			wxPoint f;
			f.x = 28 + 55*i;
			f.y = 25 + 55*(7-j) ;
			image2 = new wxBitmap("/home/mistrio/Desktop/project/window/bN.png", wxBITMAP_TYPE_PNG);
			dc.DrawBitmap(*(image2),f,false);
			}
			if ((pole.kl[i][j].figura == 3) and (pole.kl[i][j].color == 0) ){
			wxPoint f;
			f.x = 28 + 55*i;
			f.y = 25 + 55*(7-j) ;
			image2 = new wxBitmap("/home/mistrio/Desktop/project/window/bB.png", wxBITMAP_TYPE_PNG);
			dc.DrawBitmap(*(image2),f,false);
			}
			if ((pole.kl[i][j].figura == 3) and (pole.kl[i][j].color == 1) ){
			wxPoint f;
			f.x = 28 + 55*i;
			f.y = 25 + 55*(7-j) ;
			image2 = new wxBitmap("/home/mistrio/Desktop/project/window/wB.png", wxBITMAP_TYPE_PNG);
			dc.DrawBitmap(*(image2),f,false);
			}
			if ((pole.kl[i][j].figura == 5) and (pole.kl[i][j].color == 0) ){
			wxPoint f;
			f.x = 28 + 55*i;
			f.y = 25 + 55*(7-j) ;
			image2 = new wxBitmap("/home/mistrio/Desktop/project/window/bK.png", wxBITMAP_TYPE_PNG);
			dc.DrawBitmap(*(image2),f,false);
			}
			if ((pole.kl[i][j].figura == 5) and (pole.kl[i][j].color == 1) ){
			wxPoint f;
			f.x = 28 + 55*i;
			f.y = 25 + 55*(7-j) ;
			image2 = new wxBitmap("/home/mistrio/Desktop/project/window/wK.png", wxBITMAP_TYPE_PNG);
			dc.DrawBitmap(*(image2),f,false);
			}
			if ((pole.kl[i][j].figura == 6) and (pole.kl[i][j].color == 1) ){
			wxPoint f;
			f.x = 28 + 55*i;
			f.y = 25 + 55*(7-j) ;
			image2 = new wxBitmap("/home/mistrio/Desktop/project/window/wQ.png", wxBITMAP_TYPE_PNG);
			dc.DrawBitmap(*(image2),f,false);
			}
			
			if ((pole.kl[i][j].figura == 6) and (pole.kl[i][j].color == 0) ){
			wxPoint f;
			f.x = 28 + 55*i;
			f.y = 25 + 55*(7-j) ;
			image2 = new wxBitmap("/home/mistrio/Desktop/project/window/bQ.png", wxBITMAP_TYPE_PNG);
			dc.DrawBitmap(*(image2),f,false);
			}
	}
	}

};



Hod Draw::Coords_To_Hod(int x1,int y1, int x2, int y2)
{
Hod hod;
hod.a=(x1-29)/55+97;
hod.b=(x2-29)/55+97;
hod.y1=7-((y1-26)/55)+1;
hod.y2=7-((y2-26)/55)+1;
return hod;
}

int Draw::PlayDebut(Pole *etalon, Hod hod)//имя дебюта
    {
    if (etalon->next==0)
    return 1;//дебют закончился
    else
    {
    if (((etalon->hod.a==hod.a)&&(etalon->hod.b==hod.b)&&(etalon->hod.y1==hod.y1)&&(etalon->hod.y2==hod.y2))!=1)
    {
    return 2;//Ход некоректен

    }
    }
    *etalon=*etalon->next;
    if (etalon->next==0)
		return 1;
    return 3;//Ход удался

}


int Draw::RecordMove(Pole * pole, Hod hod){
pole->next=new Pole;
*(pole->next)=*pole;
pole->next->prev=pole;
pole->next->next = 0;
int check = pole->next->maketurn(hod.a-97,hod.y1-1,hod.b-97,hod.y2-1);
if (check==1)
{
pole->hod=hod;
return 1;
}
else
{
delete pole->next;
pole->next=0;
return 0;
}
};

void Draw::OnEnder(wxCommandEvent& event){
	wxString str1;
	if (mn->per == 1){
	while(mn->play->prev != 0 ){
	mn->play = mn->play->prev;
}

	wxFileOutputStream output(mn->fileName);
    wxTextOutputStream outs(output);
    
    while (mn->play->next != 0){
		
		outs<<mn->play->hod.a<<wxT(" ")<<mn->play->hod.y1<<wxT(" ")<<mn->play->hod.b<<wxT(" ")<<mn->play->hod.y2<<"\n";
		mn->play = mn->play->next;
	}
	
	outs<<wxT("b 228 b 228");
	str1<<wxT("Дебют закончен!")<<wxT("\n");
	mn->sb->SetStatusText(str1);
	mn->per == 0;
	Pole * tmp;
		 while (mn->play->next!=0)
		 {
			 tmp=mn->play->next;
			 delete mn->etalon;
			 mn->play=tmp;
		 }
		 delete mn->play;
}
};

void Draw::OnHn(wxCommandEvent& event){
	if (mn->per == 1){
	if (mn->play->prev != 0){
	int end1 = 1;
			mn->play = mn->play->prev;
			mn->play->next=0;
			ScreenPrint(*mn->play);
	wxString str;
	str<<end1;
	mn->sb->SetStatusText(str);
	}
}
};
void Draw::OnHt(wxCommandEvent& event){
	if (mn->per1 == 1){
	if (h == 0){
	wxString str1;
	str1<<mn->etalon->hod.a<<wxT(" ")<<mn->etalon->hod.y1<<wxT(" ")<<mn->etalon->hod.b<<wxT(" ")<<mn->etalon->hod.y2<<"\n";
	m_readonly1->AppendText(str1);
	h++;
	}
}
	
};





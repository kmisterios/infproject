#include <string.h>
#include <iostream>
#include "pole.h"
#include <sstream>
#include <math.h>
#include <fstream>

Pole::Pole()//Конструктор
{
	last_move_maker = 0 ;//Обеспечит то, что первым ходят белые

	//Верхняя строка с чёрными фигурами
	kl[0][7].figura = 4 ;
	kl[0][7].color = 0 ;

	kl[1][7].figura = 2 ;
	kl[1][7].color = 0 ;

	kl[2][7].figura = 3 ;
	kl[2][7].color = 0 ;

	kl[3][7].figura = 6 ;
	kl[3][7].color = 0 ;

	kl[4][7].figura = 5 ;
	kl[4][7].color = 0 ;

	kl[5][7].figura = 3 ;
	kl[5][7].color = 0 ;

	kl[6][7].figura = 2 ;
	kl[6][7].color = 0 ;

	kl[7][7].figura = 4 ;
	kl[7][7].color = 0 ;

	// Нижняя строка с белыми фигурами 

	kl[0][0].figura = 4 ;
	kl[0][0].color = 1 ;

	kl[1][0].figura = 2 ;
	kl[1][0].color = 1 ;

	kl[2][0].figura = 3 ;
	kl[2][0].color = 1 ;

	kl[3][0].figura = 6 ;
	kl[3][0].color = 1 ;

	kl[4][0].figura = 5 ;
	kl[4][0].color = 1 ;

	kl[5][0].figura = 3 ;
	kl[5][0].color = 1 ;

	kl[6][0].figura = 2 ;
	kl[6][0].color = 1 ;

	kl[7][0].figura = 4 ;
	kl[7][0].color = 1 ;

	int i=0,j=0;


	//Середина поля с  пустыми полями 

	for(i=2;i<6;i++)
	{
		for(j=0;j<8;j++)
		{
			kl[j][i].figura = 0;
			kl[j][i].color = 2;
		}
	}

	//Строка с чёрными пешками

	i=6;
	for(j=0;j<8;j++)
	{
		kl[j][i].figura = 1;
		kl[j][i].color = 0;
	}
	
	//Строка сбелыми пешками
	
	i=1;
	for(j=0;j<8;j++)
	{
		kl[j][i].figura = 1;
		kl[j][i].color = 1;
	}
	next=0;
	prev=0;
	type=0;
};


int Pole::maketurnplus( int x1,int y1,int x2,int y2)//Функция совершения хода
{
    int krb = 1, drb = 1, krch = 1, drch = 1;
    int t;
	//Проверка на непокидание поля
	if ((x1>=0)and(x1<=7)and(x2>=0)and(x2<=7)and(y1>=0)and(y1<=7)and(y2>=0)and(y2<=7))
	{
		if (kl[x1][y1].figura==0)//Присутсвие фигуры в точке отправления
			return 0;
		else
		{
			if (last_move_maker==kl[x1][y1].color)//Возможность хода этой стороны
				return 0;
			else
			{
				//Отсутсвие союзной фигуры в точке прибытия
				if (kl[x1][y1].color==kl[x2][y2].color)
					return 0;
				else //Непосредственно ходы каждой из фигур
				{
					if (kl[x1][y1].figura==1) //ПЕШКА
					{
						if (last_move_maker==0)
						{
                            if ((y1==6)&&(((x1+1)==x2)||((x1-1)==x2)))
                            {
                                if (kl[x2][7].figura!=0)
                                {
                                    
                                    return 1;
                                }
                            }
                            if ((y1==6)&&(x1==x2))
                            {
                                if (kl[x2][7].figura==0)
                                {
                                    
                                    return 1;
                                }
                            }
							if (y1==1)
								if ((y2==3)&&(kl[x1][y1+1].figura==0)&&
								(kl[x1][y1+2].figura==0)&&(x1==x2))
								{
									
									return 1;
								}
								if ((y2==2)and(((x1+1)==x2)or((x1-1)==x2)))
								{
									if (kl[x2][y2].figura!=0)
										return 1;
								}
								if ((y2==2)&&(x1==x2)&&(kl[x1][y1+1].figura==0))
								{
									
									return 1;
								}
								if ((y1==0)||(y1==7))
									return 0;
								if ((y1==2)||(y1==3)||(y1==4)||(y1==5))
								{
									if ((kl[x1][y1+1].figura==0)&&(x1==x2)
									&&(y2-y1<2))
									{
										
										return 1;
									}
									if (((x2==x1+1)||(x2==x1-1))&&(y2==y1+1)
									&&(kl[x2][y2].figura!=0))
									{
										
										return 1;
									}
								}
							}
							if (last_move_maker==1)
							{
                                if ((y1==1)&&(((x1+1)==x2)||((x1-1)==x2)))
                                {
                                    if (kl[x2][0].figura!=0)
                                    {
                                        
                                        return 1;
                                    }
                                }
                                if ((y1==1)&&(x1==x2))
                                {
                                    if (kl[x1][0].figura==0)
                                    {
                                        
                                        return 1;
                                    }
                                }
								if (y1==6)
								if ((y2==4)&&(kl[x1][y1-1].figura==0)
								&&(kl[x1][y1-2].figura==0)&&(x1==x2))
								{
									
									return 1;
								}
								if ((y2==5)and(((x1+1)==x2)or((x1-1)==x2)))
								{
									if (kl[x2][y2].figura!=0)
										return 1;
								}
								if ((y2==5)&&(x1==x2)&&(kl[x1][y1-1].figura==0))
								{
									
									return 1;
								}
								if ((y1==0)||(y1==7))
										return 0;
								if ((y1==2)||(y1==3)||(y1==4)||(y1==5))
								{
									if ((kl[x1][y1-1].figura==0)
									&&(x1==x2)&&(y1-y2<2))
									{
										
										return 1;
									}
									if (((x2==x1+1)||(x2==x1-1))&&(y2==y1-1)&&(kl[x2][y2].figura!=0))
									{
										
										return 1;
									}
								}
							}
							return 0;
						}


						if(kl[x1][y1].figura == 6)//КОРОЛЕВА
						{ 
		
							int i,j;

							//Если мы ходим на право 

							if((x2>x1) && (y2==y1))
							{ 

								for(i=x1+1;i<x2;i++)
								{
							   			
							   		if(kl[i][y1].figura!=0)
							   		{
								  		return 0;
								  	}
							  
							    }
							}	

							//Если мы ходим на лево 

							if(x2<x1 && y2==y1)
							{ 

								for(i=x1-1;i>x2;i--)
								{
							   			
							   		if(kl[i][y1].figura!=0)
							   		{
								  		return 0;
								  	}
							    }
							}	
							//Если мы ходим  вверх
							if(y2>y1 && x2==x1)
							{
								for(j=y1+1;j<y2;j++)
								{
							   		if(kl[x1][j].figura!=0)
								  		return 0;
							    }
							}	

							//Если мы ходим  вниз

							if(y2<y1 && x2==x1)
							{ 

								for(j=y1-1;j>y2;j--)
								{
							   			
							   		if(kl[x1][j].figura!=0)
							   		{
								  		return 0;
								  	}
							    }
							}	


							//Если мы ходим по диагонали вверх и вправо 

                            if((y2>y1) && (x2>x1))
                            {
                                for (i=1;i<y2-y1;i++)
                                    if (kl[x1+i][y1+i].figura!=0)
                                        return 0;
                            }

							//Если мы ходим по диагонали вниз и вправо 

                            if((y2<y1) && (x2>x1))
                            {
                                for (i=1;i<x2-x1;i++)
                                    if (kl[x1+i][y1-i].figura!=0)
                                        return 0;
                                
                            }

							 //Если мы ходим по диагонали вверх и влево

                            if((y2>y1) && (x2<x1))
                            {
                                for (i=1;i<y2-y1;i++)
                                    if (kl[x1-i][y1+i].figura!=0)
                                        return 0;
                                
                            }

							//Если мы ходим по диагонали вниз и влево

                            if ((y2<y1) && (x2<x1))
                            {
                                for (i=1;i<x1-x2;i++)
                                    if (kl[x1-i][y1-i].figura!=0)
                                        return 0;
                                
                            }



							//Меняем значение полей
							if((x1==x2)||(y1==y2) || ((abs(y2-y1))==(abs(x2-x1))))
							{
								
								return 1;
							}

							return 0;
						}


						if(kl[x1][y1].figura == 3)//СЛОН
						{ 
		
							int i,j;

							//Если мы ходим по диагонали вверх и вправо 

                            if((y2>y1) && (x2>x1))
                            {
                                for (i=1;i<y2-y1;i++)
                                    if (kl[x1+i][y1+i].figura!=0)
                                        return 0;
                            }
                            
							//Если мы ходим по диагонали вниз и вправо 

                            if((y2<y1) && (x2>x1))
                            {
                                for (i=1;i<x2-x1;i++)
                                    if (kl[x1+i][y1-i].figura!=0)
                                        return 0;
                                
                            }
                            
			 //Если мы ходим по диагонали вверх и влево

                            if((y2>y1) && (x2<x1))
                            {
                                for (i=1;i<y2-y1;i++)
                                    if (kl[x1-i][y1+i].figura!=0)
                                        return 0;
                                
                            }
                            
                            

							//Если мы ходим по диагонали вниз и влево

                            if ((y2<y1) && (x2<x1))
                            {
                                for (i=1;i<x1-x2;i++)
                                    if (kl[x1-i][y1-i].figura!=0)
                                        return 0;
                                
                            }


							//Меняем значение полей
							if(((abs(y2-y1))==(abs(x2-x1))))
							{
								
								return 1;
							}

							return 0;
						}

						if ((kl[x1][y1].figura == 5)&&(x1==4)&&(y1==0)&&(x2==6)&&(y2==0)&&(last_move_maker==0)) //КОРОТКАЯ РОКИРОВКА БЕЛЫХ
						if ((krb==1)&&(kl[7][0].figura==4)&&(kl[6][0].figura==0)&&(kl[5][0].figura==0))
						{
							
							krb=0;
							drb=0;
                            
							return 1;
						}
						
						if ((kl[x1][y1].figura == 5)&&(x1==4)&&(y1==0)&&(x2==2)&&(y2==0)&&(last_move_maker==0)) //ДЛИННАЯ РОКИРОВКА БЕЛЫХ
						if ((drb==1)&&(kl[0][0].figura==4)&&(kl[1][0].figura==0)&&(kl[2][0].figura==0)&&(kl[3][0].figura==0))
						{
							
							krb=0;
							drb=0;
                            
							return 1;
						}
						
						if ((kl[x1][y1].figura == 5)&&(x1==4)&&(y1==7)&&(x2==6)&&(y2==7)&&(last_move_maker==1)) //КОРОТКАЯ РОКИРОВКА ЧЕРНЫХ
						if ((krch==1)&&(kl[7][7].figura==4)&&(kl[6][7].figura==0)&&(kl[5][7].figura==0))
						{
							
							krch=0;
							drch=0;
                            
							return 1;
						}
						
						if ((kl[x1][y1].figura == 5)&&(x1==4)&&(y1==7)&&(x2==2)&&(y2==7)&&(last_move_maker==1)) //ДЛИННАЯ РОКИРОВКА ЧЕРНЫХ
						if ((drch==1)&&(kl[7][0].figura==4)&&(kl[1][7].figura==0)&&(kl[2][7].figura==0)&&(kl[3][7].figura==0))
						{
							
							krch=0;
							drch=0;
                            
							return 1;
						}
					
						if(kl[x1][y1].figura == 4)//Ладья
						{ 
		
							int i,j;
							if ((last_move_maker==0)&&(x1==0)&&(y1==0))
							drb=0;
							if ((last_move_maker==0)&&(x1==7)&&(y1==0))
							krb=0;
							if ((last_move_maker==1)&&(x1==0)&&(y1==7))
							drch=0;
							if ((last_move_maker==1)&&(x1==7)&&(y1==7))
							krch=0;
					//Если мы ходим на право 

									if((x2>x1) && (y2==y1)){ 

										for(i=x1+1;i<x2;i++){
						   			
						   			if(kl[i][y1].figura!=0){
							  	return 0;
							  	}
						  
					        			}
					        		}	

					//Если мы ходим на лево 

						       if(x2<x1 && y2==y1){ 

										for(i=x1-1;i>x2;i--){
						   			
						   			if(kl[i][y1].figura!=0){
							  	return 0;
							  	}
					        			}
					        		}	
					//Если мы ходим  вверх
							if(y2>y1 && x2==x1){
								for(j=y1+1;j<y2;j++)
								{
						   			if(kl[x1][j].figura!=0)
							  			return 0;
					        			}
					        		}	

					//Если мы ходим  вниз

							if(y2<y1 && x2==x1){ 

								for(j=y1-1;j>y2;j--)
								{
						   			
						   			if(kl[x1][j].figura!=0)
						   			{
							  			return 0;
							  		}
					        			}
					        		}	

					//Меняем значение полей
					if ((x1==x2)or(y1==y2))
					{
					

					return 1;
					}
					return 0;
					}
				
					if (kl[x1][y1].figura == 5){//КОРОЛЬ

						if (last_move_maker==0)
						{
							krb=0;
							drb=0;
						}
						if (last_move_maker==1)
						{
							krch=0;
							drch=0;
						}

						if (((x1 + 1 == x2) && (y1==y2)) || ((x1 + 1 == x2) && 
						(y1 + 1==y2)) || ((x1 + 1 == x2) && (y1 - 1==y2)) || 
						((x1 == x2) && (y1 + 1 ==y2)) || ((x1 == x2) && 
						(y1 - 1==y2)) || ((x1 - 1 == x2) && (y1==y2)) || 
						((x1 - 1 == x2) && (y1 + 1==y2)) || ((x1 - 1 == x2) && 
						(y1 - 1==y2))){
							
							return 1;
						}

						}
				
					if (kl[x1][y1].figura==2)//КОНЬ
					{
						if ((((x1-x2)==1)and((y1-y2)==2))or(((x2-x1)==1)and
						((y1-y2)==2))or(((x1-x2)==2)and((y1-y2)==1))or
						(((x2-x1)==2)and((y1-y2)==1))or(((x1-x2)==1)and
						((y2-y1)==2))or(((x2-x1)==1)and((y2-y1)==2))or
						(((x1-x2)==2)and((y2-y1)==1))or(((x2-x1)==2)
						and((y2-y1)==1)))
						{
							
							return 1;
						}
					return 0;
					
					
					
					
					}
					else
						return 0;
				
				
				
				
				
				}			
			
			}
		}
	}
	else
		return 0;
};


int Pole::maketurn( int x1,int y1,int x2,int y2)//Функция совершения хода
{
	int krb = 1, drb = 1, krch = 1, drch = 1;
	Pole a=(*this);
	//Проверка на непокидание поля
	if ((x1>=0)and(x1<=7)and(x2>=0)and(x2<=7)and(y1>=0)and(y1<=7)and(y2>=0)and(y2<=7))
	{
		if (kl[x1][y1].figura==0)//Присутсвие фигуры в точке отправления
			return 0;
		else
		{
			if (last_move_maker==kl[x1][y1].color)//Возможность хода этой стороны
				return 0;
			else
			{
				//Отсутсвие союзной фигуры в точке прибытия
				if (kl[x1][y1].color==kl[x2][y2].color)
					return 0;
				else //Непосредственно ходы каждой из фигур
				{
					if (kl[x1][y1].figura==1) //ПЕШКА
					{
						if (last_move_maker==0)
						{
                            if ((y1==6)&&(((x1+1)==x2)||((x1-1)==x2)))
                            {
                                if (kl[x2][7].figura!=0)
                                {
                                    kl[x1][y1].figura=0;
                                    kl[x1][y1].color=2;
                                    kl[x2][y2].figura=6;
                                    kl[x2][y2].color=1;
                                    last_move_maker=1;
                                    if (tupocheck(x1,y1,x2,y2)==0)
                                    	*this=a;

                                    return tupocheck(x1,y1,x2,y2);
                                }
                            }
                            if ((y1==6)&&(x1==x2))
                            {
                                if (kl[x2][7].figura==0)
                                {
                                    kl[x1][y1].figura=0;
                                    kl[x1][y1].color=2;
                                    kl[x2][y2].figura=6;
                                    kl[x2][y2].color=1;
                                    last_move_maker=1;
                                    if (tupocheck(x1,y1,x2,y2)==0)
                                    	*this=a;
                                    return tupocheck(x1,y1,x2,y2);
                                }
                            }
							if (y1==1)
								if ((y2==3)&&(kl[x1][y1+1].figura==0)&&
								(kl[x1][y1+2].figura==0)&&(x1==x2))
								{
									kl[x1][y1].figura=0;
									kl[x1][y1].color=2;
									kl[x2][y2].figura=1;
									kl[x2][y2].color=1;
									last_move_maker=1;
									if (tupocheck(x1,y1,x2,y2)==0)
                                    	*this=a;
									return tupocheck(x1,y1,x2,y2);
								}
								if ((y2==2)and(((x1+1)==x2)or((x1-1)==x2)))
								{
									if (kl[x2][y2].figura!=0)
									{
										kl[x1][y1].figura=0;
										kl[x1][y1].color=2;
										kl[x2][y2].figura=1;
										kl[x2][y2].color=1;
										last_move_maker=1;
										if (tupocheck(x1,y1,x2,y2)==0)
                                    		*this=a;
										return tupocheck(x1,y1,x2,y2);
									}
								}
								if ((y2==2)&&(x1==x2)&&(kl[x1][y1+1].figura==0))
								{
									kl[x1][y1].figura=0;
									kl[x1][y1].color=2;
									kl[x2][y2].figura=1;
									kl[x2][y2].color=1;
									last_move_maker=1;
									if (tupocheck(x1,y1,x2,y2)==0)
                                    	*this=a;
									return tupocheck(x1,y1,x2,y2);
								}
								if ((y1==0)||(y1==7))
									return 0;
								if ((y1==2)||(y1==3)||(y1==4)||(y1==5))
								{
									if ((kl[x1][y1+1].figura==0)&&(x1==x2)
									&&(y2-y1<2))
									{
										kl[x1][y1].figura=0;
										kl[x1][y1].color=2;
										kl[x2][y2].figura=1;
										kl[x2][y2].color=1;
										last_move_maker=1;
										if (tupocheck(x1,y1,x2,y2)==0)
                                    	*this=a;
										return tupocheck(x1,y1,x2,y2);
									}
									if (((x2==x1+1)||(x2==x1-1))&&(y2==y1+1)
									&&(kl[x2][y2].figura!=0))
									{
										kl[x1][y1].figura=0;
										kl[x1][y1].color=2;
										kl[x2][y2].figura=1;
										kl[x2][y2].color=1;
										last_move_maker=1;
										if (tupocheck(x1,y1,x2,y2)==0)
                                    	*this=a;
										return tupocheck(x1,y1,x2,y2);
									}
								}
							}
							if (last_move_maker==1)
							{
                                if ((y1==1)&&(((x1+1)==x2)||((x1-1)==x2)))
                                {
                                    if (kl[x2][0].figura!=0)
                                    {
                                        kl[x1][y1].figura=0;
                                        kl[x1][y1].color=2;
                                        kl[x2][y2].figura=6;
                                        kl[x2][y2].color=0;
                                        last_move_maker=0;
                                        if (tupocheck(x1,y1,x2,y2)==0)
                                    	*this=a;
                                        return tupocheck(x1,y1,x2,y2);
                                    }
                                }
                                if ((y1==1)&&(x1==x2))
                                {
                                    if (kl[x1][0].figura==0)
                                    {
                                        kl[x1][y1].figura=0;
                                        kl[x1][y1].color=2;
                                        kl[x2][y2].figura=6;
                                        kl[x2][y2].color=0;
                                        last_move_maker=0;
                                        if (tupocheck(x1,y1,x2,y2)==0)
                                    	*this=a;
                                        return tupocheck(x1,y1,x2,y2);
                                    }
                                }
								if (y1==6)
								if ((y2==4)&&(kl[x1][y1-1].figura==0)
								&&(kl[x1][y1-2].figura==0)&&(x1==x2))
								{
									kl[x1][y1].figura=0;
									kl[x1][y1].color=2;
									kl[x2][y2].figura=1;
									kl[x2][y2].color=0;
									last_move_maker=0;
									if (tupocheck(x1,y1,x2,y2)==0)
                                    	*this=a;
									return tupocheck(x1,y1,x2,y2);
								}
								if ((y2==5)and(((x1+1)==x2)or((x1-1)==x2)))
								{
									if (kl[x2][y2].figura!=0)
									{
										kl[x1][y1].figura=0;
										kl[x1][y1].color=2;
										kl[x2][y2].figura=1;
										kl[x2][y2].color=0;
										last_move_maker=1;
										if (tupocheck(x1,y1,x2,y2)==0)
                                    		*this=a;
										return tupocheck(x1,y1,x2,y2);
									}
								}
								if ((y2==5)&&(x1==x2)&&(kl[x1][y1-1].figura==0))
								{
									kl[x1][y1].figura=0;
									kl[x1][y1].color=2;
									kl[x2][y2].figura=1;
									kl[x2][y2].color=0;
									last_move_maker=0;
									if (tupocheck(x1,y1,x2,y2)==0)
                                    	*this=a;
									return tupocheck(x1,y1,x2,y2);
								}
								if ((y1==0)||(y1==7))
										return 0;
								if ((y1==2)||(y1==3)||(y1==4)||(y1==5))
								{
									if ((kl[x1][y1-1].figura==0)
									&&(x1==x2)&&(y1-y2<2))
									{
										kl[x1][y1].figura=0;
										kl[x1][y1].color=2;
										kl[x2][y2].figura=1;
										kl[x2][y2].color=0;
										last_move_maker=0;
										if (tupocheck(x1,y1,x2,y2)==0)
                                    	*this=a;
										return tupocheck(x1,y1,x2,y2);
									}
									if (((x2==x1+1)||(x2==x1-1))&&(y2==y1-1)&&(kl[x2][y2].figura!=0))
									{
										kl[x1][y1].figura=0;
										kl[x1][y1].color=2;
										kl[x2][y2].figura=1;
										kl[x2][y2].color=0;
										last_move_maker=0;
										if (tupocheck(x1,y1,x2,y2)==0)
                                    	*this=a;
										return tupocheck(x1,y1,x2,y2);
									}
								}
							}
							return 0;
						}


						if(kl[x1][y1].figura == 6)//КОРОЛЕВА
						{ 
		
							int i,j;

							//Если мы ходим на право 

							if((x2>x1) && (y2==y1))
							{ 

								for(i=x1+1;i<x2;i++)
								{
							   			
							   		if(kl[i][y1].figura!=0)
							   		{
								  		return 0;
								  	}
							  
							    }
							}	

							//Если мы ходим на лево 

							if(x2<x1 && y2==y1)
							{ 

								for(i=x1-1;i>x2;i--)
								{
							   			
							   		if(kl[i][y1].figura!=0)
							   		{
								  		return 0;
								  	}
							    }
							}	
							//Если мы ходим  вверх
							if(y2>y1 && x2==x1)
							{
								for(j=y1+1;j<y2;j++)
								{
							   		if(kl[x1][j].figura!=0)
								  		return 0;
							    }
							}	

							//Если мы ходим  вниз

							if(y2<y1 && x2==x1)
							{ 

								for(j=y1-1;j>y2;j--)
								{
							   			
							   		if(kl[x1][j].figura!=0)
							   		{
								  		return 0;
								  	}
							    }
							}	


							//Если мы ходим по диагонали вверх и вправо 

                            if((y2>y1) && (x2>x1))
                            {
                                for (i=1;i<y2-y1;i++)
                                    if (kl[x1+i][y1+i].figura!=0)
                                        return 0;
                            }
                            
							//Если мы ходим по диагонали вниз и вправо 

                            if((y2<y1) && (x2>x1))
                            {
                                for (i=1;i<x2-x1;i++)
                                    if (kl[x1+i][y1-i].figura!=0)
                                        return 0;
                                
                            }
                            

							 //Если мы ходим по диагонали вверх и влево

                            if((y2>y1) && (x2<x1))
                            {
                                for (i=1;i<y2-y1;i++)
                                    if (kl[x1-i][y1+i].figura!=0)
                                        return 0;
                                
                            }

							//Если мы ходим по диагонали вниз и влево

                            if ((y2<y1) && (x2<x1))
                            {
                                for (i=1;i<x1-x2;i++)
                                    if (kl[x1-i][y1-i].figura!=0)
                                        return 0;
                                
                            }
                            


							//Меняем значение полей
							if((x1==x2)||(y1==y2) || ((abs(y2-y1))==(abs(x2-x1))))
							{
								kl[x2][y2].color=kl[x1][y1].color;
								kl[x2][y2].figura=kl[x1][y1].figura;
								last_move_maker=kl[x1][y1].color;
								kl[x1][y1].figura=0;
								kl[x1][y1].color=2;
								if (tupocheck(x1,y1,x2,y2)==0)
                                    	*this=a;
								return tupocheck(x1,y1,x2,y2);
							}

							return 0;
						}


						if(kl[x1][y1].figura == 3)//СЛОН
						{ 
		
							int i,j;

							//Если мы ходим по диагонали вверх и вправо 

                            if((y2>y1) && (x2>x1))
                            {
                                for (i=1;i<y2-y1;i++)
                                    if (kl[x1+i][y1+i].figura!=0)
                                        return 0;
                            }
                            

							//Если мы ходим по диагонали вниз и вправо 

                            if((y2<y1) && (x2>x1))
                            {
                                for (i=1;i<x2-x1;i++)
                                    if (kl[x1+i][y1-i].figura!=0)
                                        return 0;
                               
                            }
                            

			 //Если мы ходим по диагонали вверх и влево

						    
                            if((y2>y1) && (x2<x1))
                            {
                                for (i=1;i<y2-y1;i++)
                                    if (kl[x1-i][y1+i].figura!=0)
                                        return 0;
                                
                            }
                            


							//Если мы ходим по диагонали вниз и влево

                            if ((y2<y1) && (x2<x1))
                            {
                                for (i=1;i<x1-x2;i++)
                                    if (kl[x1-i][y1-i].figura!=0)
                                        return 0;
                                
                            }
                            


							//Меняем значение полей
							if(((abs(y2-y1))==(abs(x2-x1))))
							{
								kl[x2][y2].color=kl[x1][y1].color;
								kl[x2][y2].figura=kl[x1][y1].figura;
								last_move_maker=kl[x1][y1].color;
								kl[x1][y1].figura=0;
								kl[x1][y1].color=2;
								if (tupocheck(x1,y1,x2,y2)==0)
                                    	*this=a;
								return tupocheck(x1,y1,x2,y2);
							}

							return 0;
						}

						if ((kl[x1][y1].figura == 5)&&(x1==4)&&(y1==0)&&(x2==6)&&(y2==0)&&(last_move_maker==0)) //КОРОТКАЯ РОКИРОВКА БЕЛЫХ
						if ((krb==1)&&(kl[7][0].figura==4)&&(kl[6][0].figura==0)&&(kl[5][0].figura==0))
						{
							kl[7][0].figura=0;
							kl[7][0].color=2;
							kl[6][0].figura=5;
							kl[6][0].color=1;
							kl[5][0].figura=4;
							kl[5][0].color=1;
							kl[4][0].figura=0;
							kl[4][0].color=2;
							krb=0;
							drb=0;
                            last_move_maker=1;
                            if (tupocheck(x1,y1,x2,y2)==0)
                                    	*this=a;
							return tupocheck(x1,y1,x2,y2);
						}
						
						if ((kl[x1][y1].figura == 5)&&(x1==4)&&(y1==0)&&(x2==2)&&(y2==0)&&(last_move_maker==0)) //ДЛИННАЯ РОКИРОВКА БЕЛЫХ
						if ((drb==1)&&(kl[0][0].figura==4)&&(kl[1][0].figura==0)&&(kl[2][0].figura==0)&&(kl[3][0].figura==0))
						{
							kl[0][0].figura=0;
							kl[0][0].color=2;
							kl[2][0].figura=5;
							kl[2][0].color=1;
							kl[3][0].figura=4;
							kl[3][0].color=1;
							kl[4][0].figura=0;
							kl[4][0].color=2;
							krb=0;
							drb=0;
                            last_move_maker=1;
                            if (tupocheck(x1,y1,x2,y2)==0)
                                    	*this=a;
							return tupocheck(x1,y1,x2,y2);
						}
						
						if ((kl[x1][y1].figura == 5)&&(x1==4)&&(y1==7)&&(x2==6)&&(y2==7)&&(last_move_maker==1)) //КОРОТКАЯ РОКИРОВКА ЧЕРНЫХ
						if ((krch==1)&&(kl[7][7].figura==4)&&(kl[6][7].figura==0)&&(kl[5][7].figura==0))
						{
							kl[7][7].figura=0;
							kl[7][7].color=2;
							kl[6][7].figura=5;
							kl[6][7].color=0;
							kl[5][7].figura=4;
							kl[5][7].color=0;
							kl[4][7].figura=0;
							kl[4][7].color=2;
							krch=0;
							drch=0;
                            last_move_maker=0;
                            if (tupocheck(x1,y1,x2,y2)==0)
                                    	*this=a;
							return tupocheck(x1,y1,x2,y2);
						}
						
						if ((kl[x1][y1].figura == 5)&&(x1==4)&&(y1==7)&&(x2==2)&&(y2==7)&&(last_move_maker==1)) //ДЛИННАЯ РОКИРОВКА ЧЕРНЫХ
						if ((drch==1)&&(kl[7][0].figura==4)&&(kl[1][7].figura==0)&&(kl[2][7].figura==0)&&(kl[3][7].figura==0))
						{
							kl[0][7].figura=0;
							kl[0][7].color=2;
							kl[2][7].figura=5;
							kl[2][7].color=0;
							kl[3][7].figura=4;
							kl[3][7].color=0;
							kl[4][7].figura=0;
							kl[4][7].color=2;
							krch=0;
							drch=0;
                            last_move_maker=0;
                            if (tupocheck(x1,y1,x2,y2)==0)
                                    	*this=a;
							return tupocheck(x1,y1,x2,y2);
						}
					
						if(kl[x1][y1].figura == 4)//Ладья
						{ 
		
							int i,j;
							if ((last_move_maker==0)&&(x1==0)&&(y1==0))
							drb=0;
							if ((last_move_maker==0)&&(x1==7)&&(y1==0))
							krb=0;
							if ((last_move_maker==1)&&(x1==0)&&(y1==7))
							drch=0;
							if ((last_move_maker==1)&&(x1==7)&&(y1==7))
							krch=0;
					//Если мы ходим на право 

									if((x2>x1) && (y2==y1)){ 

										for(i=x1+1;i<x2;i++){
						   			
						   			if(kl[i][y1].figura!=0){
							  	return 0;
							  	}
						  
					        			}
					        		}	

					//Если мы ходим на лево 

						       if(x2<x1 && y2==y1){ 

										for(i=x1-1;i>x2;i--){
						   			
						   			if(kl[i][y1].figura!=0){
							  	return 0;
							  	}
					        			}
					        		}	
					//Если мы ходим  вверх
							if(y2>y1 && x2==x1){
								for(j=y1+1;j<y2;j++)
								{
						   			if(kl[x1][j].figura!=0)
							  			return 0;
					        			}
					        		}	

					//Если мы ходим  вниз

							if(y2<y1 && x2==x1){ 

								for(j=y1-1;j>y2;j--)
								{
						   			
						   			if(kl[x1][j].figura!=0)
						   			{
							  			return 0;
							  		}
					        			}
					        		}	

					//Меняем значение полей
					if ((x1==x2)or(y1==y2))
					{
					kl[x2][y2].color=kl[x1][y1].color;
					kl[x2][y2].figura=kl[x1][y1].figura;
					last_move_maker=kl[x1][y1].color;
					kl[x1][y1].figura=0;
					kl[x1][y1].color=2;

					if (tupocheck(x1,y1,x2,y2)==0)
                                    	*this=a;
					return tupocheck(x1,y1,x2,y2);
					}
					return 0;
					}
				
					if (kl[x1][y1].figura == 5){//КОРОЛЬ

						if (last_move_maker==0)
						{
							krb=0;
							drb=0;
						}
						if (last_move_maker==1)
						{
							krch=0;
							drch=0;
						}

						if (((x1 + 1 == x2) && (y1==y2)) || ((x1 + 1 == x2) && 
						(y1 + 1==y2)) || ((x1 + 1 == x2) && (y1 - 1==y2)) || 
						((x1 == x2) && (y1 + 1 ==y2)) || ((x1 == x2) && 
						(y1 - 1==y2)) || ((x1 - 1 == x2) && (y1==y2)) || 
						((x1 - 1 == x2) && (y1 + 1==y2)) || ((x1 - 1 == x2) && 
						(y1 - 1==y2))){
							kl[x2][y2].color = kl[x1][y1].color;
							kl[x2][y2].figura = kl[x1][y1].figura;
							kl[x1][y1].color = 2;
							kl[x1][y1].figura = 0;
							last_move_maker = abs(last_move_maker - 1);
	
							if (tupocheck(x1,y1,x2,y2)==0)
                                    	*this=a;
							return tupocheck(x1,y1,x2,y2);
						}

						}
				
					if (kl[x1][y1].figura==2)//КОНЬ
					{
						if ((((x1-x2)==1)and((y1-y2)==2))or(((x2-x1)==1)and
						((y1-y2)==2))or(((x1-x2)==2)and((y1-y2)==1))or
						(((x2-x1)==2)and((y1-y2)==1))or(((x1-x2)==1)and
						((y2-y1)==2))or(((x2-x1)==1)and((y2-y1)==2))or
						(((x1-x2)==2)and((y2-y1)==1))or(((x2-x1)==2)
						and((y2-y1)==1)))
						{
							kl[x1][y1].color=2;
							kl[x1][y1].figura=0;
							if (last_move_maker==0)
								last_move_maker=1;
							else
								last_move_maker=0;
							kl[x2][y2].color=last_move_maker;
							kl[x2][y2].figura=2;
							if (tupocheck(x1,y1,x2,y2)==0)
                                    	*this=a;
							return tupocheck(x1,y1,x2,y2);
						}
					return 0;
					
					
					
					
					}
					else
						return 0;
				
				
				
				
				
				}			
			
			}
		}
	}
	else
		return 0;
};



int Pole::poiskkorx( int x1,int y1,int x2,int y2)
{
	int i,j,n,m;
	if (last_move_maker==0)
	{
		for (i=0;i<8;i++)
			for (j=0;j<8;j++)
			{
				if ((kl[i][j].figura==5)&&(kl[i][j].color==0))
					return i;
			}
	}
	if (last_move_maker==1)
	{
		for (n=0;n<8;n++)
			for (m=0;m<8;m++)
			{
				if ((kl[n][m].figura==5)&&(kl[n][m].color==1))
					return n;
			}
	}
}

int Pole::poiskkory( int x1,int y1,int x2,int y2)
{
	int i,j,n,m;
	if (last_move_maker==0)
	{
		for (i=0;i<8;i++)
			for (j=0;j<8;j++)
			{
				if ((kl[i][j].figura==5)&&(kl[i][j].color==0))
					return j;
			}
	}
	if (last_move_maker==1)
	{
		for (n=0;n<8;n++)
			for (m=0;m<8;m++)
			{
				if ((kl[n][m].figura==5)&&(kl[n][m].color==1))
					return m;
			}
	}
}

int Pole::tupocheck( int x1,int y1,int x2,int y2)	
{
	int n,m;
		for (n=0;n<8;n++)
			for (m=0;m<8;m++)
			{
				if (maketurnplus(n,m,poiskkorx(x1,y1,x2,y2),poiskkory(x1,y1,x2,y2)))
					return 0;
			}	
	
	return 1;
}	
	
	






Pole Pole::operator=(Pole pole)
{
last_move_maker=pole.last_move_maker;
type=pole.type;
hod=pole.hod;
prev=pole.prev;
next=pole.next;
int i,e;
for (i=0;i<8;++i)
for (e=0;e<8;++e)
kl[i][e]=pole.kl[i][e];

}

int Pole::check(Pole pole)
{
	int check=0,i,j;
	for (i=0;i<8;++i)
		for (j=0;j<8;++j)
			if (kl[i][j].figura!=pole.kl[i][j].figura)
				check=1;
	return check;
	
	
}


	
	




